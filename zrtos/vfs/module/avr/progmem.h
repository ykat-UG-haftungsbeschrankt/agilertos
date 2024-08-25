/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_AVR_PROGMEM_H
#define ZRTOS_VFS_MODULE_AVR_PROGMEM_H
#ifdef __cplusplus
extern "C" {
#endif


#include <avr/pgmspace.h >

#include <zrtos/error.h>
#include <zrtos/types.h>
#include <zrtos/vfs_plugin.h>


typedef struct _zrtos_vfs_module_avr_progmem_args_t{
	uint32_t start_addr;
	uint32_t end_addr;
}zrtos_vfs_module_avr_progmem_args_t;


zrtos_error_t zrtos_vfs_module_avr_progmem__on_read(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *out
){
	zrtos_error_t ret = ZRTOS_ERROR__FAULT;
	zrtos_vfs_module_avr_progmem_args_t *mod = zrtos_vfs_file__get_inode_data(
		thiz
	);
	uint32_t addr = offset;
	uint8_t *data_ptr = data;

	if(offset > ZRTOS_TYPES__UINT32_MAX){
		ret = ZRTOS_ERROR__INVAL;
		goto L_OUT;
	}

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
		ret = ZRTOS_ERROR__SUCCESS;
	}

L_OUT:
	return ret;
}

ZRTOS_VFS_PLUGIN__INIT(zero,
	ZRTOS_VFS_PLUGIN__ON_READ(zrtos_vfs_module_avr_progmem__on_read)
);


#ifdef __cplusplus
}
#endif
#endif
