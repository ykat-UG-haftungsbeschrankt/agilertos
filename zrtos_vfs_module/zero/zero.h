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


#include <zrtos/zrtos_vfs_plugin.h>
#include <zrtos/zrtos_mem.h>


ZRTOS_VFS_PLUGIN__INIT(zero,{
	ZRTOS_VFS_PLUGIN__ON_READ(ret,data,len,{
		zrtos_mem__zero(data,len);
		*ret = len;
		ZRTOS_VFS_PLUGIN__RETURN(EXIT_SUCCESS);
	});
});


#ifdef __cplusplus
}
#endif
#endif
