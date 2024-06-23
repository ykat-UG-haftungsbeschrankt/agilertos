/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_UART_H
#define ZRTOS_VFS_MODULE_UART_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/vfs_plugin.h>
#include <zrtos/cbuffer.h>


typedef struct _zrtos_vfs_module_uart_args_t{
	zrtos_cbuffer_t              cbuffer_in;
	zrtos_cbuffer_t              cbuffer_out;
	zrtos_error_t                error;
}zrtos_vfs_module_uart_args_t;


bool zrtos_vfs_module_uart_args__init(zrtos_vfs_module_uart_args_t *thiz){
	thiz->error = ESUCCESS;
	if(zrtos_cbuffer__init(&thiz->cbuffer_in)){
		if(zrtos_cbuffer__init(&thiz->cbuffer_out)){
			return true;
		}
	}
	return false;
}

zrtos_cbuffer_t *zrtos_vfs_module_uart_args__get_cbuffer_in(
	zrtos_vfs_module_uart_args_t *thiz
){
	return &thiz->cbuffer_in;
}

zrtos_cbuffer_t *zrtos_vfs_module_uart_args__get_cbuffer_out(
	zrtos_vfs_module_uart_args_t *thiz
){
	return &thiz->cbuffer_out;
}

void zrtos_vfs_module_uart_args__set_error(
	 zrtos_vfs_module_uart_args_t *thiz
	,zrtos_error_t error
){
	thiz->error = error;
}

zrtos_error_t zrtos_vfs_module_uart_args__get_error(
	zrtos_vfs_module_uart_args_t *thiz
){
	return thiz->error;
}

zrtos_error_t zrtos_vfs_module_uart__on_read(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *out
){
	zrtos_vfs_module_uart_args_t *mod = zrtos_vfs_file__get_inode_data(
		thiz
	);
	return zrtos_cbuffer__get_ex(
		 &mod->cbuffer_in
		,buf
		,len
		,out
	);
}

zrtos_error_t zrtos_vfs_module_uart__on_write(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *out
){
	zrtos_vfs_module_uart_args_t *mod = zrtos_vfs_file__get_inode_data(
		thiz
	);
	return zrtos_cbuffer__put_ex(
		 &mod->cbuffer_out
		,1
		,buf
		,len
		,out
	);
}

zrtos_error_t zrtos_vfs_module_uart__on_can_read(
	 zrtos_vfs_file_t *thiz
	,char *path
){
	zrtos_vfs_module_uart_args_t *mod = zrtos_vfs_file__get_inode_data(
		thiz
	);
	return zrtos_cbuffer__can_read(&mod->cbuffer_in);
}

zrtos_error_t zrtos_vfs_module_uart__on_can_write(
	 zrtos_vfs_file_t *thiz
	,char *path
){
	zrtos_vfs_module_uart_args_t *mod = zrtos_vfs_file__get_inode_data(
		thiz
	);
	return zrtos_cbuffer__can_write(&mod->cbuffer_out);
}
/*
ZRTOS_VFS_PLUGIN__INIT(uart,
	ZRTOS_VFS_PLUGIN__ON_READ(zrtos_vfs_module_uart__on_read)
	ZRTOS_VFS_PLUGIN__ON_WRITE(zrtos_vfs_module_uart__on_write)
	ZRTOS_VFS_PLUGIN__ON_CAN_READ(zrtos_vfs_module_uart__on_can_read)
	ZRTOS_VFS_PLUGIN__ON_CAN_WRITE(zrtos_vfs_module_uart__on_can_write)
);
*/

#ifdef __cplusplus
}
#endif
#endif
