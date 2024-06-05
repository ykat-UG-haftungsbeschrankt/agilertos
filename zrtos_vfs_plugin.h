/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_PLUGIN_H
#define ZRTOS_VFS_PLUGIN_H
#ifdef __cplusplus
extern "C" {
#endif


#include "zrtos_types.h"


struct _zrtos_file_t;

typedef struct{
	ssize_t (*init)(struct _zrtos_file_t *thiz);
	void    (*deinit)(struct _zrtos_file_t *thiz);
	ssize_t (*read)(struct _zrtos_file_t *thiz,void *buf,size_t len);
	ssize_t (*write)(struct _zrtos_file_t *thiz,void *buf,size_t len);
	size_t  (*can_read)(struct _zrtos_file_t *thiz);
	size_t  (*can_write)(struct _zrtos_file_t *thiz);
	off_t   (*seek)(int fd, off_t offset, int whence);
	int     (*ioctl)(struct _zrtos_file_t *thiz, int whence, va_list args);
}zrtos_vfs_plugin_t;


#ifdef __cplusplus
}
#endif
#endif