/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_SPI_H
#define ZRTOS_VFS_MODULE_SPI_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/vfs_plugin.h>
#include <zrtos/gpio.h>
#include <zrtos/malloc.h>

#ifdef ZRTOS_MALLOC__CFG_DISABLE_FREE
#error
#endif

typedef enum{
	// SPI clock modes
	 ZRTOS_VFS_MODULE_SPI_MODE__0 = 0x00 ///< Sample (Rising) Setup (Falling) CPOL=0, CPHA=0
	,ZRTOS_VFS_MODULE_SPI_MODE__1 = 0x01 ///< Setup (Rising) Sample (Falling) CPOL=0, CPHA=1
	,ZRTOS_VFS_MODULE_SPI_MODE__2 = 0x02 ///< Sample (Falling) Setup (Rising) CPOL=1, CPHA=0
	,ZRTOS_VFS_MODULE_SPI_MODE__3 = 0x03 ///< Setup (Falling) Sample (Rising) CPOL=1, CPHA=1
}zrtos_vfs_module_spi_mode_t;

typedef enum{
	// SPI clock modes
	 ZRTOS_VFS_MODULE_SPI_BITORDER__LSB = 1 ///< send least significant bit (bit 0) first
	,ZRTOS_VFS_MODULE_SPI_BITORDER__MSB = 0 ///< send most significant bit (bit 7) first
}zrtos_vfs_module_spi_bitorder_t;

typedef enum{
	 ZRTOS_VFS_MODULE_SPI_CLOCK__SLAVE = 0xF0
	,ZRTOS_VFS_MODULE_SPI_CLOCK__MSTR_CLK4 = 0x00 ///< chip clock/4
	,ZRTOS_VFS_MODULE_SPI_CLOCK__MSTR_CLK16 = 0x01 ///< chip clock/16
	,ZRTOS_VFS_MODULE_SPI_CLOCK__MSTR_CLK64 = 0x02 ///< chip clock/64
	,ZRTOS_VFS_MODULE_SPI_CLOCK__MSTR_CLK128 = 0x03 ///< chip clock/128
	,ZRTOS_VFS_MODULE_SPI_CLOCK__MSTR_CLK2 = 0x04 ///< chip clock/2
	,ZRTOS_VFS_MODULE_SPI_CLOCK__MSTR_CLK8 = 0x05 ///< chip clock/8
	,ZRTOS_VFS_MODULE_SPI_CLOCK__MSTR_CLK32 = 0x06 ///< chip clock/32
}zrtos_vfs_module_spi_clock_t;

typedef struct _zrtos_vfs_module_spi_args_t{
	zrtos_gpio_pin_t ss_pin;
	zrtos_gpio_pin_t sck_pin;
	zrtos_gpio_pin_t mosi_pin;
	zrtos_gpio_pin_t miso_pin;
	zrtos_vfs_module_spi_mode_t mode;
	zrtos_vfs_module_spi_bitorder_t bitorder;
	zrtos_vfs_module_spi_clock_t clock;
}zrtos_vfs_module_spi_args_t;

typedef struct _zrtos_vfs_module_spi_file_t{
	zrtos_gpio_pin_t           ss_pin;
	uint8_t                    spcr;
	uint8_t                    data[ZRTOS_VFS_MODULE_SPI__CFG_DATA_LENGTH];
	size_t                     offset;
	size_t                     write_offset;
	size_t                     read_offset;
}zrtos_vfs_module_spi_file_t;

zrtos_error_t zrtos_vfs_module_spi__on_mount(
	 zrtos_vfs_dirent_t *thiz
){
	zrtos_error_t ret = EFAULT;
	return ret;
}

typedef struct _zrtos_vfs_module_spi_t{
	zrtos_vfs_module_spi_file_t *active;
}zrtos_vfs_module_spi_t;

zrtos_vfs_module_spi_t zrtos_vfs_module_spi;

ISR(SPI_STC_vect){
	SPDR = zrtos_vfs_module_spi.data[zrtos_vfs_module_spi.offset];
	zrtos_vfs_module_spi.data[zrtos_vfs_module_spi.offset++] = SPDR;
	if(offset >= length){
		SPCR &= (~SPIE);
	}
}

zrtos_error_t zrtos_vfs_module_spi__on_open(
	 zrtos_vfs_file_t *thiz
	,char *path
){
	zrtos_error_t ret = ENOMEM;
	zrtos_vfs_module_spi_file_t *file_data = malloc(
		sizeof(zrtos_vfs_module_spi_file_t)
	);
	if(file_data){
		file_data->ss_pin = 0;
		file_data->write_offset = 0;
		file_data->read_offset = 0;
		zrtos_vfs_file__set_data(thiz,file_data);
		ret = EXIT_SUCCESS;
	}
	return ret;
}

zrtos_error_t zrtos_vfs_module_spi__on_close(
	 zrtos_vfs_file_t *thiz
	,char *path
){
	zrtos_error_t ret = EBUSY;
	zrtos_vfs_module_spi_file_t *file_data = zrtos_vfs_file__get_data(thiz);
	free(file_data);
	if(file_data){
		file_data->ss_pin = 0;
		file_data->write_offset = 0;
		file_data->read_offset = 0;
		zrtos_vfs_file__set_data(thiz,file_data);
		ret = EXIT_SUCCESS;
	}
	return ret;
}

zrtos_error_t zrtos_vfs_module_spi__on_umount(
	 zrtos_vfs_dentry_t *thiz
){
	zrtos_error_t ret = EXIT_SUCCESS;

	ZRTOS_VFS_FILE__EACH_BEGIN(fd,file){
		if(file->dentry == thiz){
			ret = EBUSY;
			break;
		}
	}ZRTOS_VFS_FILE__EACH_END;

	return ret;
}

zrtos_error_t zrtos_vfs_module_spi__on_read(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *out
){
	zrtos_error_t ret = EFAULT;
	zrtos_vfs_module_spi_args_t *mod = zrtos_vfs_file__get_inode_data(
		thiz
	);
	zrtos_vfs_module_spi.data = 
	SPCR |= SPIE;

	return ret;
}

zrtos_error_t zrtos_vfs_module_spi__on_write(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *out
){
	zrtos_vfs_module_spi_file_t *file_data = zrtos_vfs_file__get_data(
		thiz
	);
	size_t length = ZRTOS_TYPES__MIN(len,ZRTOS_VFS_MODULE_SPI__CFG_DATA_LENGTH);

	if(offset != 0){
		return EINVAL;
	}

	zrtos_mem__cpy(file_data->data,buf,length);
	file_data->len = length;
	file_data->offset = 0;

	*out = len;

	return zrtos_vfs_module_spi__start_send();
}

zrtos_error_t zrtos_vfs_module_spi__on_can_read(
	 zrtos_vfs_file_t *thiz
	,char *path
){
	zrtos_vfs_module_spi_file_t *file_data = zrtos_vfs_file__get_data(
		thiz
	);
	return file_data->read_offset < file_data->length
	     ? EXIT_SUCCESS
	     : EAGAIN
	;
}

zrtos_error_t zrtos_vfs_module_spi__on_can_write(
	 zrtos_vfs_file_t *thiz
	,char *path
){
	zrtos_vfs_module_spi_file_t *file_data = zrtos_vfs_file__get_data(
		thiz
	);
	return file_data->length < ZRTOS_VFS_MODULE_SPI__CFG_DATA_LENGTH
	     ? EXIT_SUCCESS
	     : EAGAIN
	;
}

ZRTOS_VFS_PLUGIN__INIT(spi,ZRTOS_VFS_PLUGIN_TYPE__FILE,
	ZRTOS_VFS_PLUGIN__ON_OPEN(zrtos_vfs_module_spi__on_open)
	ZRTOS_VFS_PLUGIN__ON_CLOSE(zrtos_vfs_module_spi__on_close)
	ZRTOS_VFS_PLUGIN__ON_MOUNT(zrtos_vfs_module_spi__on_mount)
	ZRTOS_VFS_PLUGIN__ON_UMOUNT(zrtos_vfs_module_spi__on_umount)
	ZRTOS_VFS_PLUGIN__ON_READ(zrtos_vfs_module_spi__on_read)
	ZRTOS_VFS_PLUGIN__ON_WRITE(zrtos_vfs_module_spi__on_write)
	ZRTOS_VFS_PLUGIN__ON_CAN_READ(zrtos_vfs_module_spi__on_can_read)
	ZRTOS_VFS_PLUGIN__ON_CAN_WRITE(zrtos_vfs_module_spi__on_can_write)
);


#ifdef __cplusplus
}
#endif
#endif
