/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_AVR_SPI_SYNC_H
#define ZRTOS_VFS_MODULE_AVR_SPI_SYNC_H
#ifdef __cplusplus
extern "C" {
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

#include <zrtos/cast.h>
#include <zrtos/types.h>
#include <zrtos/vfs/module/spi/sync.h>


zrtos_error_t zrtos_vfs_module_avr_spi_sync__on_write_callback(
	 zrtos_vfs_module_spi_sync_args_t *inode_data
	,zrtos_vfs_module_spi_sync_file_t *file_data
	,void *buf
	,size_t len
	,size_t *l
){
	zrtos_error_t ret = ZRTOS_ERRROR__SUCCESS;
	uint8_t *data_out = ZRTOS_CAST(uint8_t*,buf);
	SPCR = file_data->control;
	while(len--){
		SPDR = *data_out;
		while(!(SPSR & (1<<SPIF))){
			continue;
		}
		*data_out++ = SPDR;
	}
	SPCR = 0;
	*l = zrtos_types__ptr_get_byte_distance(data_out,buf);
	return ret;
}

zrtos_error_t zrtos_vfs_module_avr_spi_sync__on_write(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *out
){
	return zrtos_vfs_module_spi_sync__on_write_helper(
		 thiz
		,path
		,buf
		,len
		,offset
		,out
		,zrtos_vfs_module_avr_spi_sync__on_write_callback
	);
}

ZRTOS_VFS_PLUGIN__INIT(spi,
	ZRTOS_VFS_PLUGIN__0_ON_OPEN(zrtos_vfs_module_spi_sync__on_open)
	ZRTOS_VFS_PLUGIN__1_ON_CLOSE(zrtos_vfs_module_spi_sync__on_close)
	ZRTOS_VFS_PLUGIN__2_ON_MOUNT(zrtos_vfs_module_spi_sync__on_mount)
	ZRTOS_VFS_PLUGIN__3_ON_UMOUNT(zrtos_vfs_module_spi_sync__on_umount)
	ZRTOS_VFS_PLUGIN__4_ON_READ_DEFAULT()
	ZRTOS_VFS_PLUGIN__5_ON_WRITE(zrtos_vfs_module_avr_spi_sync__on_write)
	ZRTOS_VFS_PLUGIN__6_ON_CAN_READ_DEFAULT()
	ZRTOS_VFS_PLUGIN__7_ON_CAN_WRITE_DEFAULT()
	ZRTOS_VFS_PLUGIN__8_ON_SEEK_DEFAULT()
	ZRTOS_VFS_PLUGIN__9_ON_IOCTL_DEFAULT()
);


#ifdef __cplusplus
}
#endif
#endif
