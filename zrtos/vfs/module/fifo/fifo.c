/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_FIFO_H
#define ZRTOS_VFS_MODULE_FIFO_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/vfs_module.h>
#include <zrtos/cbuffer.h>
#include <zrtos/cast.h>

typedef struct _zrtos_vfs_module_fifo_file_t{
	zrtos_cbuffer_t                  cbuffer;
}zrtos_vfs_module_fifo_file_t;

zrtos_error_t zrtos_vfs_module_fifo__on_read(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *out
){
	zrtos_vfs_module_fifo_file_t *mod = ZRTOS_CAST(
		 zrtos_vfs_module_fifo_file_t *
		,zrtos_vfs_file__get_data(
			thiz
		)
	);
	return zrtos_cbuffer__get_ex(
		 &mod->cbuffer
		,buf
		,len
		,out
	);
}

zrtos_error_t zrtos_vfs_module_fifo__on_write(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *out
){
	zrtos_vfs_module_fifo_file_t *mod = ZRTOS_CAST(
		 zrtos_vfs_module_fifo_file_t *
		,zrtos_vfs_file__get_data(
			thiz
		)
	);
	return zrtos_cbuffer__put_ex(
		 &mod->cbuffer
		,1
		,out
		,buf
		,len
	);
}

zrtos_error_t zrtos_vfs_module_fifo__on_can_read(
	 zrtos_vfs_file_t *thiz
){
	zrtos_vfs_module_fifo_file_t *mod = ZRTOS_CAST(
		 zrtos_vfs_module_fifo_file_t *
		,zrtos_vfs_file__get_data(
			thiz
		)
	);
	return zrtos_cbuffer__can_read(&mod->cbuffer);
}

zrtos_error_t zrtos_vfs_module_fifo__on_can_write(
	 zrtos_vfs_file_t *thiz
){
	zrtos_vfs_module_fifo_file_t *mod = ZRTOS_CAST(
		 zrtos_vfs_module_fifo_file_t *
		,zrtos_vfs_file__get_data(
			thiz
		)
	);
	return zrtos_cbuffer__can_write(&mod->cbuffer);
}

ZRTOS_VFS_PLUGIN__INIT(fifo,
	ZRTOS_VFS_PLUGIN__0_ON_OPEN_DEFAULT()
	ZRTOS_VFS_PLUGIN__1_ON_CLOSE_DEFAULT()
	ZRTOS_VFS_PLUGIN__2_ON_MOUNT_DEFAULT()
	ZRTOS_VFS_PLUGIN__3_ON_UMOUNT_DEFAULT()
	ZRTOS_VFS_PLUGIN__4_ON_READ(zrtos_vfs_module_fifo__on_read)
	ZRTOS_VFS_PLUGIN__5_ON_WRITE(zrtos_vfs_module_fifo__on_write)
	ZRTOS_VFS_PLUGIN__6_ON_CAN_READ(zrtos_vfs_module_fifo__on_can_read)
	ZRTOS_VFS_PLUGIN__7_ON_CAN_WRITE(zrtos_vfs_module_fifo__on_can_write)
	ZRTOS_VFS_PLUGIN__8_ON_SEEK_DEFAULT()
	ZRTOS_VFS_PLUGIN__9_ON_IOCTL_DEFAULT()
);

#ifdef __cplusplus
}
#endif
#endif