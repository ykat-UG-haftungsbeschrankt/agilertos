/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_MODBUS_RTU_H
#define ZRTOS_VFS_MODULE_MODBUS_RTU_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/vfs_plugin.h>
#include <zrtos/cbuffer.h>
#include <zrtos/msg_queue.h>

typedef struct _zrtos_vfs_module_modbus_rtu_args_t{
	zrtos_msg_queue_t  msg_queue_in;
	zrtos_msg_queue_t  msg_queue_out;
	zrtos_error_t      error;
}zrtos_vfs_module_modbus_rtu_args_t;


bool zrtos_vfs_module_modbus_rtu_args__init(
	zrtos_vfs_module_modbus_rtu_args_t *thiz
){
	thiz->error = ZRTOS_ERROR__SUCCESS;
	if(zrtos_msg_queue__init(&thiz->msg_queue_in)){
		if(zrtos_msg_queue__init(&thiz->msg_queue_out)){
			return true;
		}
		zrtos_msg_queue__deinit(&thiz->msg_queue_in);
	}
	return false;
}

zrtos_msg_queue_t *zrtos_vfs_module_modbus_rtu_args__get_msg_queue_in(
	zrtos_vfs_module_modbus_rtu_args_t *thiz
){
	return &thiz->msg_queue_in;
}

zrtos_msg_queue_t *zrtos_vfs_module_modbus_rtu_args__get_msg_queue_in(
	zrtos_vfs_module_modbus_rtu_args_t *thiz
){
	return &thiz->msg_queue_out;
}

void zrtos_vfs_module_modbus_rtu_args__set_error(
	 zrtos_vfs_module_modbus_rtu_args_t *thiz
	,zrtos_error_t error
){
	thiz->error = error;
}

zrtos_error_t zrtos_vfs_module_modbus_rtu_args__get_error(
	zrtos_vfs_module_modbus_rtu_args_t *thiz
){
	return thiz->error;
}

zrtos_error_t zrtos_vfs_module_modbus_rtu__on_read(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *out
){
	zrtos_vfs_module_modbus_rtu_args_t *mod = zrtos_vfs_file__get_inode_data(
		thiz
	);
	zrtos_error_t ret = mod->error;
	if(zrtos_error__is_success(ret)){
		ret = zrtos_msg_queue__get(
			 &mod->msg_queue_in
			,buf
			,len
			,out
		);
	}
	return ret;
}

zrtos_error_t zrtos_vfs_module_modbus_rtu__on_write(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *out
){
	zrtos_vfs_module_modbus_rtu_args_t *mod = zrtos_vfs_file__get_inode_data(
		thiz
	);
	zrtos_error_t ret = mod->error;
	if(zrtos_error__is_success(ret)){
		ret = zrtos_msg_queue__put(
			 &mod->msg_queue_out
			,buf
			,len
			,out
		);
	}
	return ret; 
}

zrtos_error_t zrtos_vfs_module_modbus_rtu__on_can_read(
	 zrtos_vfs_file_t *thiz
	,char *path
){
	zrtos_vfs_module_modbus_rtu_args_t *mod = zrtos_vfs_file__get_inode_data(
		thiz
	);
	return zrtos_msg_queue__is_empty(&mod->msg_queue_in)
	     ? ZRTOS_ERROR__AGAIN
	     : ZRTOS_ERROR__SUCCESS
	;
}

zrtos_error_t zrtos_vfs_module_modbus_rtu__on_can_write(
	 zrtos_vfs_file_t *thiz
	,char *path
){
	return ZRTOS_ERROR__SUCCESS;
}
/*
ZRTOS_VFS_PLUGIN__INIT(modbus_rtu,
	ZRTOS_VFS_PLUGIN__ON_READ(zrtos_vfs_module_modbus_rtu__on_read)
	ZRTOS_VFS_PLUGIN__ON_WRITE(zrtos_vfs_module_modbus_rtu__on_write)
	ZRTOS_VFS_PLUGIN__ON_CAN_READ(zrtos_vfs_module_modbus_rtu__on_can_read)
	ZRTOS_VFS_PLUGIN__ON_CAN_WRITE(zrtos_vfs_module_modbus_rtu__on_can_write)
);
*/

#ifdef __cplusplus
}
#endif
#endif
