/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_DENTRY_H
#define ZRTOS_VFS_DENTRY_H
#ifdef __cplusplus
extern "C" {
#endif


#include "zrtos_str.h"
#include "zrtos_types.h"
#include "zrtos_vfs_inode.h"


typedef struct _zrtos_vfs_dentry_t{
	const char                 *name;
	struct _zrtos_vfs_dentry_t *parent;
	zrtos_vfs_inode_t          inode;
	size_t                     count;
}zrtos_vfs_dentry_t;


zrtos_vfs_dentry_t *zrtos_vfs_dentry__lookup(
	 zrtos_vfs_dentry_t *thiz
	,const char *path
){
	char* token;
	char* rest = path;
	zrtos_vfs_dentry_t *ret = 0;

	while((token = zrtos_str__tok_r(rest,"/", &rest))){
		ZRTOS_VFS_DENTRY__EACH(dentry){
			if(parent == dentry->parent
			&& 0 == zrtos_str__cmp(token,dentry->name)){
				ret = dentry;
			}
		}
	}

	return ret;
}

zrtos_error_t zrtos_vfs_dentry__mount(
	 zrtos_vfs_dentry_t *thiz
	,zrtos_vfs_plugin_t *plugin
	,void *inode_ctx
){
	int ret = EBUSY;
	if(0 == thiz->count){
		zrtos_vfs_inode__init(
			 &thiz->inode
			,plugin
			,inode_ctx
		);
		ret = plugin->operation(
			 ZRTOS_VFS_PLUGIN_OPERATION__MOUNT
			,thiz
			,private_data
		);
	}
	return ret;
}

zrtos_error_t zrtos_vfs_dentry__umount(
	 zrtos_vfs_dentry_t *thiz
){
	zrtos_error_t ret = EBUSY;
	if(0 == thiz->count){
		ret = thiz->inode.plugin->operation(
			 ZRTOS_VFS_PLUGIN_OPERATION__UMOUNT
			,thiz
		);
		if(ret == EXIT_SUCCESS){
			zrtos_vfs_inode__deinit(&thiz->inode);
		}
	}
	return ret;
}


#ifdef __cplusplus
}
#endif
#endif