/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_AVR_SPI_H
#define ZRTOS_VFS_MODULE_AVR_SPI_H
#ifdef __cplusplus
extern "C" {
#endif

#include <avr/interrupt.h>

#include <zrtos/vfs_plugin.h>
#include <zrtos/vfs/module/spi/spi.h>
#include <zrtos/gpio.h>
#include <zrtos/malloc.h>
#include <zrtos/cbuffer.h>
#include <zrtos/binary.h>

#ifdef ZRTOS_MALLOC__CFG_DISABLE_FREE
#error
#endif





zrtos_error_t zrtos_vfs_module_spi__on_mount(
	 zrtos_vfs_dirent_t *thiz
){
	zrtos_error_t ret = EFAULT;
	return ret;
}

zrtos_vfs_module_spi_t zrtos_vfs_module_spi;



void zrtos_vfs_module_avr_spi__on_interrupt(){
	if(zrtos_error__is_error(zrtos_vfs_module_spi__transfer(
		 &zrtos_vfs_module_spi
		,(void*)SPDR
		,(void*)SPDR
		,sizeof(uint8_t)
	))){
		SPCR &= ~_BV(SPIE);
	}else{
		SPCR |= _BV(SPIE);
	}
}

ISR(SPI__STC_vect){
	zrtos_vfs_module_avr_spi__on_interrupt();
}

zrtos_error_t zrtos_vfs_module_avr_spi__on_write(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *out
){
	zrtos_error_t ret = zrtos_vfs_module_avr_spi__on_write(
		 thiz
		,path
		,buf
		,len
		,offset
		,out
	);
	if(zrtos_error__is_success(ret)){
		zrtos_vfs_module_avr_spi__on_interrupt();
	}
	return ret;
}

ZRTOS_VFS_PLUGIN__INIT(avr_spi,
	ZRTOS_VFS_PLUGIN__0_ON_OPEN(zrtos_vfs_module_spi__on_open)
	ZRTOS_VFS_PLUGIN__1_ON_CLOSE(zrtos_vfs_module_spi__on_close)
	ZRTOS_VFS_PLUGIN__2_ON_MOUNT(zrtos_vfs_module_spi__on_mount)
	ZRTOS_VFS_PLUGIN__3_ON_UMOUNT(zrtos_vfs_module_spi__on_umount)
	ZRTOS_VFS_PLUGIN__4_ON_READ(zrtos_vfs_module_spi__on_read)
	ZRTOS_VFS_PLUGIN__5_ON_WRITE(zrtos_vfs_module_avr_spi__on_write)
	ZRTOS_VFS_PLUGIN__6_ON_CAN_READ(zrtos_vfs_module_spi__on_can_read)
	ZRTOS_VFS_PLUGIN__7_ON_CAN_WRITE(zrtos_vfs_module_spi__on_can_write)
	ZRTOS_VFS_PLUGIN__8_ON_SEEK_DEFAULT()
	ZRTOS_VFS_PLUGIN__9_ON_IOCTL_DEFAULT()
);


#ifdef __cplusplus
}
#endif
#endif
