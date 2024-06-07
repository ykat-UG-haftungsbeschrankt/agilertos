/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_INODE_H
#define ZRTOS_VFS_INODE_H
#ifdef __cplusplus
extern "C" {
#endif


#include "zrtos_vfs_plugin.h"


typedef struct _zrtos_vfs_inode_t{
	zrtos_vfs_plugin_t         *plugin;
	void                       *ctx;
}zrtos_vfs_inode_t;

bool zrtos_vfs_inode__init(
	 zrtos_vfs_inode_t  *thiz
	,zrtos_vfs_plugin_t *plugin
	,void               *ctx
){
	thiz->plugin = plugin;
	thiz->ctx = ctx;
	return true;
}

void zrtos_vfs_inode__deinit(
	 zrtos_vfs_inode_t  *thiz
){
	thiz->plugin = 0;
	thiz->ctx = 0;
}

zrtos_vfs_plugin_t *zrtos_vfs_inode__get_plugin(
	 zrtos_vfs_inode_t  *thiz
){
	return thiz->plugin;
}

void *zrtos_vfs_inode__get_ctx(
	 zrtos_vfs_inode_t  *thiz
){
	return thiz->ctx;
}

#ifdef __cplusplus
}
#endif
#endif