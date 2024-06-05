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
	void                       *private_data;
}zrtos_vfs_inode_t;


#ifdef __cplusplus
}
#endif
#endif