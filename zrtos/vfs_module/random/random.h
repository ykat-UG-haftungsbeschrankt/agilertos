/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_RANDOM_H
#define ZRTOS_VFS_MODULE_RANDOM_H
#ifdef __cplusplus
extern "C" {
#endif


#include "../../zrtos_vfs_plugin.h"
#include "../../zrtos_vfs_file.h"


zrtos_error_t zrtos_vfs_module_random__on_open(
	 zrtos_vfs_file_t *thiz
){
	zrtos_vfs_file__set_offset(
		 thiz
		,(zrtos_vfs_offset_t)0xACE1
	);

	return EXIT_SUCCESS;
}

zrtos_error_t zrtos_vfs_module_random__on_read(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *ret
){
	uint16_t lfsr = (uint16_t)zrtos_vfs_file__get_offset(thiz);
	uint8_t  *buffer = buf;

	*ret = len;

	while(len--){
		lfsr ^= lfsr >> 7;
		lfsr ^= lfsr << 9;
		lfsr ^= lfsr >> 13;

		*buffer++ = (lfsr >> 4);
	}

	zrtos_vfs_file__set_offset(
		 thiz
		,(zrtos_vfs_offset_t)lfsr
	);

	return EXIT_SUCCESS;
}

ZRTOS_VFS_PLUGIN__INIT(random,
	ZRTOS_VFS_PLUGIN__ON_OPEN(zrtos_vfs_module_random__on_open)
	ZRTOS_VFS_PLUGIN__ON_READ(zrtos_vfs_module_random__on_read)
);


#ifdef __cplusplus
}
#endif
#endif
