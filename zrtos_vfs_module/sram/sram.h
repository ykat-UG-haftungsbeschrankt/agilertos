/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_SRAM_H
#define ZRTOS_VFS_MODULE_SRAM_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/zrtos_error.h>
#include <zrtos/zrtos_types.h>
#include <zrtos/zrtos_vfs_plugin.h>


typedef struct _zrtos_vfs_module_sram_args_t{
	uint8_t *start_addr;
	uint8_t *end_addr;
}zrtos_vfs_module_sram_args_t;


zrtos_error_t zrtos_vfs_module_sram__read(struct _zrtos_vfs_file_t *thiz,char *path,void *buf,size_t len,off_t offset,size_t *out){
	zrtos_vfs_module_progmem_args_t *mod = zrtos_vfs_file__get_inode_data(
	thiz
	);
	uint8_t *addr = offset;
	uint8_t *data_ptr = data;
	if(zrtos_types__uint32_is_valid_address_range(
	mod->start_addr
	,mod->end_addr
	,addr
	,&len
	)){
		*ret = len;
		for(;len--;addr++){
			*data_ptr++ = pgm_read_byte_far(addr);
		}
		ZRTOS_VFS_PLUGIN__RETURN(EXIT_SUCCESS);
		}else{
		ZRTOS_VFS_PLUGIN__RETURN(EFAULT);
	}
}

zrtos_error_t zrtos_vfs_module_sram__write(struct _zrtos_vfs_file_t *thiz,char *path,void *buf,size_t len,off_t offset,size_t *out){
	zrtos_vfs_module_sram_args_t *mod = zrtos_vfs_file__get_inode_data(
	thiz
	);
	uint32_t addr = offset;
	uint8_t *data_ptr = data;
	if(addr >= mod->start_addr
	&& addr <= mod->end_addr){
		size_t i = *ret = ZRTOS_TYPES__MIN(
		len
		,mod->end_addr - addr
		);
		for(;i--;addr++){
			*data_ptr++ = pgm_read_byte_far(addr);
		}
		ZRTOS_VFS_PLUGIN__RETURN(EXIT_SUCCESS);
		}else{
		ZRTOS_VFS_PLUGIN__RETURN(EFAULT);
	}
}

ZRTOS_VFS_PLUGIN__INIT(zero,
	ZRTOS_VFS_PLUGIN__ON_READ(zrtos_vfs_module_sram__read)
	ZRTOS_VFS_PLUGIN__ON_WRITE(zrtos_vfs_module_sram__write)
);


#ifdef __cplusplus
}
#endif
#endif
