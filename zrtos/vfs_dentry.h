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

#include <zrtos/vfs_module/null/null.h>

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

zrtos_vfs_dentry_t *zrtos_vfs_dentry__get_first_node(){
	zrtos_clist_node_t *node = zrtos_clist__get_first_node(&zrtos_vfs_dentry__index);
	return zrtos_types__get_container_of_ex(node,zrtos_vfs_dentry_t,node);
}

zrtos_vfs_dentry_t *zrtos_vfs_dentry__get_next_node(zrtos_vfs_dentry_t *thiz){
	zrtos_clist_node_t *node = zrtos_clist_node__get_next_node(&thiz->node);
	return zrtos_types__get_container_of(node,zrtos_vfs_dentry_t,node);
}

#define ZRTOS_VFS_DENTRY__EACH(node)                                  \
	for(zrtos_vfs_dentry_t *node = zrtos_vfs_dentry__get_first_node(&zrtos_vfs_dentry__index) \
		,*sentinel = node                                             \
		,*next                                                        \
		;node && ({                                                           \
			next = zrtos_vfs_dentry__get_next_node(node);                   \
			node != sentinel;                                         \
		})                                                            \
		;node = next                                                  \
	)


zrtos_vfs_dentry_t *zrtos_vfs_dentry__lookup(
	 zrtos_vfs_dentry_t *thiz
	,char *path
){
	char *token;
	char *rest = path;
	zrtos_vfs_dentry_t *ret = 0;
	zrtos_vfs_dentry_t *parent = thiz;

	while((token = zrtos_str__tok_r(rest,"/", &rest))){
		zrtos_vfs_dentry_t *node = zrtos_vfs_dentry__get_first_node(&zrtos_vfs_dentry__index);
		zrtos_vfs_dentry_t *sentinel = node;
		if(node){
			do{
				if(parent == node->parent
				&& 0 == zrtos_str__cmp(token,node->name)){
					parent = ret = node;
					break;
				}
				node = zrtos_vfs_dentry__get_next_node(node);
			}while(node != sentinel);
		}
/*
		ZRTOS_VFS_DENTRY__EACH(dentry){
			if(parent == dentry->parent
			&& 0 == zrtos_str__cmp(token,dentry->name)){
				parent = ret = dentry;
			}
		}
*/
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


#ifdef __cplusplus
}
#endif
#endif