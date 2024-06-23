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


#include <zrtos/cast.h>
#include <zrtos/vfs_plugin.h>
#include <zrtos/vfs_file.h>


zrtos_error_t zrtos_vfs_module_random__on_open(
	 zrtos_vfs_file_t *thiz
){
	zrtos_vfs_file__set_offset(
		 thiz
		,(zrtos_vfs_offset_t)0xACE1
	);

	return ESUCCESS;
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
	uint8_t  *buffer = ZRTOS_CAST(uint8_t*,buf);

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

	return ESUCCESS;
}

ZRTOS_VFS_PLUGIN__INIT(random,
	ZRTOS_VFS_PLUGIN__0_ON_OPEN(zrtos_vfs_module_random__on_open)
	ZRTOS_VFS_PLUGIN__1_ON_CLOSE_DEFAULT()
	ZRTOS_VFS_PLUGIN__2_ON_MOUNT_DEFAULT()
	ZRTOS_VFS_PLUGIN__3_ON_UMOUNT_DEFAULT()
	ZRTOS_VFS_PLUGIN__4_ON_READ(zrtos_vfs_module_random__on_read)
	ZRTOS_VFS_PLUGIN__5_ON_WRITE_DEFAULT()
	ZRTOS_VFS_PLUGIN__6_ON_CAN_READ_DEFAULT()
	ZRTOS_VFS_PLUGIN__7_ON_CAN_WRITE_DEFAULT()
	ZRTOS_VFS_PLUGIN__8_ON_SEEK_DEFAULT()
	ZRTOS_VFS_PLUGIN__9_ON_IOCTL_DEFAULT()
);


#ifdef __cplusplus
}
#endif
#endif
