/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_MODBUS_ASCII_H
#define ZRTOS_VFS_MODULE_MODBUS_ASCII_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/vfs_plugin.h>
#include <zrtos/malloc.h>
#include <zrtos/str.h>


static uint8_t zrtos_vfs_module_modbus_ascii__lcr8(
	 uint8_t *buffer
	,size_t length
){
	uint8_t lcr = 0; 

	while(length--){
		lcr += *buffer++;
	}

	return -lcr;
}

size_t zrtos_vfs_module_modbus_ascii__get_required_buffer_length(size_t len){
	return len * 2 + 9;
}

zrtos_error_t zrtos_vfs_module_modbus_ascii__serialize(uint8_t *dest,uint8_t *src,size_t len,size_t *out_len){
	zrtos_error_t ret = EXIT_SUCCESS;
	if(len >= 2){
		uint8_t lrc = zrtos_vfs_module_modbus_ascii__lcr8(src,len);
		*dest++ = ':';
		dest += zrtos_str__from_hex(dest,src,len);
		dest += zrtos_str__to_hex(dest,&lrc,1);
		*dest++ = '\r';
		*dest++ = '\n';
		*out_len = len * 2 + 9;
	}else{
		ret = EINVAL;
	}
	return ret;
}

uint16_t zrtos_vfs_module_modbus_ascii__deserialize(size_t len){
	return len * 2 + 9;
}

zrtos_error_t zrtos_vfs_module_modbus_ascii__read(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *out
){
	
}

zrtos_error_t zrtos_vfs_module_modbus_ascii__write(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *out
){
	zrtos_vfs_module_sram_args_t *mod = zrtos_vfs_file__get_inode_data(
		thiz
	);
	uint8_t lrc = zrtos_vfs_module_modbus_ascii__lcr8(src,len);
	*dest++ = ':';
	dest += zrtos_str__from_to_hex(buf,len); 
	dest += zrtos_str__from_to_hex(dest,lrc,1);
	*dest++ = '\r';
	*dest++ = '\n';
	*out = len * 2 + 5;
}

ZRTOS_VFS_PLUGIN__INIT(modbus_ascii,ZRTOS_VFS_PLUGIN_TYPE__FILE,
	ZRTOS_VFS_PLUGIN__ON_READ(zrtos_vfs_module_modbus_ascii__read)
	ZRTOS_VFS_PLUGIN__ON_WRITE(zrtos_vfs_module_modbus_ascii__write)
);


#ifdef __cplusplus
}
#endif
#endif
