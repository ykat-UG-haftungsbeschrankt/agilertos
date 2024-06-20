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


#include <zrtos/str.h>
#include <zrtos/types.h>
#include <zrtos/clist.h>
#include <zrtos/vfs_inode.h>

#include <zrtos/vfs/module/null/null.h>

typedef struct _zrtos_vfs_dentry_t{
	zrtos_clist_node_t         node;
	char                       *name;
	struct _zrtos_vfs_dentry_t *parent;
	zrtos_vfs_inode_t          inode;
	size_t                     count;
}zrtos_vfs_dentry_t;

zrtos_clist_t zrtos_vfs_dentry__index = {};

bool zrtos_vfs_dentry__init(
	 zrtos_vfs_dentry_t         *thiz
	,char                       *name
	,struct _zrtos_vfs_dentry_t *parent
){
	zrtos_clist_node__init(&thiz->node);
	thiz->name = name;
	thiz->parent = parent;
	zrtos_vfs_inode__init(
		 &thiz->inode
		,ZRTOS_VFS_PLUGIN(null)
		,0
	);
	thiz->count = 0;

	zrtos_clist__push(&zrtos_vfs_dentry__index,&thiz->node);

	return true;
}

bool zrtos_vfs_dentry__is_filesystem(zrtos_vfs_dentry_t *node){
	return ZRTOS_VFS_PLUGIN_TYPE__FILESYSTEM == node->inode.plugin->type;
}
/*
zrtos_vfs_dentry_t *zrtos_vfs_dentry__get_first_node(){
	zrtos_clist_node_t *node = zrtos_clist__get_first_node(&zrtos_vfs_dentry__index);
	return zrtos_types__get_container_of_ex(node,zrtos_vfs_dentry_t,node);
}

zrtos_vfs_dentry_t *zrtos_vfs_dentry__get_next_node(zrtos_vfs_dentry_t *thiz){
	zrtos_clist_node_t *node = zrtos_clist_node__get_next_node(&thiz->node);
	return zrtos_types__get_container_of(node,zrtos_vfs_dentry_t,node);
}
*/
typedef struct _zrtos_vfs_dentry__each_child_cb_args_t{
	zrtos_vfs_dentry_t *parent;
	bool (*callback)(zrtos_vfs_dentry_t *node,void *arg);
	void *callback_arg;
	bool (*filter)(zrtos_vfs_dentry_t *node,void *arg);
	void *filter_arg;
}zrtos_vfs_dentry__each_child_cb_args_t;

static bool zrtos_vfs_dentry__each_child_cb(zrtos_clist_node_t *node,void *arg){
	bool ret = true;
	zrtos_vfs_dentry_t *dentry = zrtos_types__get_container_of_ex(
		 node
		,zrtos_vfs_dentry_t
		,node
	);
	zrtos_vfs_dentry__each_child_cb_args_t *args = arg;
	if(args->parent == dentry->parent
	&& args->filter(dentry,args->filter_arg)){
		ret = args->callback(dentry,args->callback_arg);
	}
	return ret;
}

bool zrtos_vfs_dentry__each_child(
	 zrtos_vfs_dentry_t *thiz
	,bool (*callback)(zrtos_vfs_dentry_t *node,void *arg)
	,void *callback_arg
	,bool (*filter)(zrtos_vfs_dentry_t *node,void *arg)
	,void *filter_arg
){
	zrtos_vfs_dentry__each_child_cb_args_t args = {
		 .parent = thiz
		,.callback = callback
		,.callback_arg = callback_arg
		,.filter = filter
		,.filter_arg = filter_arg
	};
	return zrtos_clist__each(
		 &zrtos_vfs_dentry__index
		,zrtos_vfs_dentry__each_child_cb
		,&args
	);
}

bool zrtos_vfs_dentry__each_child_filter_name_cb(
	 zrtos_vfs_dentry_t *node
	,void *arg
){
	return 0 == zrtos_str__cmp(dentry->name,(char*)arg);
}

static bool zrtos_vfs_dentry__lookup_callback_cb(zrtos_vfs_dentry_t *node,void *arg){
	zrtos_vfs_dentry_t **args = (zrtos_vfs_dentry_t **)arg;
	*args = node;
	return false;
}

zrtos_vfs_dentry_t *zrtos_vfs_dentry__lookup(
	 zrtos_vfs_dentry_t *thiz
	,char *path
){
	char               *token;
	zrtos_vfs_dentry_t *ret = 0;

	while((token = zrtos_str__tok_r(path,"/", &path))){
		zrtos_vfs_dentry__each_child(
			 thiz
			,zrtos_vfs_dentry__lookup_callback_cb
			,&thiz
			,zrtos_vfs_dentry__each_child_filter_name_cb
			,token
		);
		if(thiz){
			ret = thiz;
		}else{
			if(!zrtos_vfs_dentry__is_filesystem(ret)){
				ret = 0;
			}
			break;
		}
	}

	return ret;
}

zrtos_error_t zrtos_vfs_dentry__mount(
	 zrtos_vfs_dentry_t *thiz
	,zrtos_vfs_plugin_t *plugin
	,void *inode_ctx
){
	zrtos_error_t ret = EBUSY;
	if(0 == thiz->count){
		zrtos_vfs_inode__init(
			 &thiz->inode
			,plugin
			,inode_ctx
		);
		ret = ZRTOS_VFS_PLUGIN__INVOKE(
			 plugin
			,ZRTOS_VFS_PLUGIN_OPERATION__MOUNT
			,thiz
		);
	}
	return ret;
}

zrtos_error_t zrtos_vfs_dentry__umount(
	 zrtos_vfs_dentry_t *thiz
){
	zrtos_error_t ret = EBUSY;
	if(0 == thiz->count){
		ret = ZRTOS_VFS_PLUGIN__INVOKE(
			 thiz->inode.plugin
			,ZRTOS_VFS_PLUGIN_OPERATION__UMOUNT
			,thiz
		);
		if(ret == EXIT_SUCCESS){
			zrtos_vfs_inode__deinit(&thiz->inode);
		}
	}
	return ret;
}

void zrtos_vfs_dentry__set_inode_data(zrtos_vfs_dentry_t *thiz,void *ctx){
	thiz->inode.ctx = ctx;
}

void *zrtos_vfs_dentry__get_inode_data(zrtos_vfs_dentry_t *thiz){
	return thiz->inode.ctx;
}

#ifdef __cplusplus
}
#endif
#endif