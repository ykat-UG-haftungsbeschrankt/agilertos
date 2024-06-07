/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_ZERO_H
#define ZRTOS_VFS_MODULE_ZERO_H
#ifdef __cplusplus
extern "C" {
#endif


#include "../../zrtos_vfs_plugin.h"
#include "../../zrtos_vfs_file.h"
#include "../../zrtos_mem.h"


zrtos_error_t zrtos_vfs_module_zero__on_read(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *ret
){
	zrtos_mem__zero(buf,len);
	*ret = len;
	return EXIT_SUCCESS;
}

ZRTOS_VFS_PLUGIN__INIT(zero
	,ZRTOS_VFS_PLUGIN__ON_READ(zrtos_vfs_module_zero__on_read)
);


#ifdef __cplusplus
}
#endif
#endif
