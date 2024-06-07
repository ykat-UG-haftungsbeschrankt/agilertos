/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_NULL_H
#define ZRTOS_VFS_MODULE_NULL_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/zrtos_vfs_plugin.h>
#include <zrtos/zrtos_mem.h>


ssize_t zrtos_vfs_module_null__write(
	 zrtos_file_t *thiz
	,void *buf
	,size_t len
){
	return len;
}

zrtos_vfs_plugin_t zrtos_vfs_module_null = {
	,.write = zrtos_vfs_module_null__write
};


#ifdef __cplusplus
}
#endif
#endif
