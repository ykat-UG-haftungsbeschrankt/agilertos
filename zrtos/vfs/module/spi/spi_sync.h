/* Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_SPI_SYNC_H
#define ZRTOS_VFS_MODULE_SPI_SYNC_H
#ifdef __cplusplus
extern "C" {
#endif

#include <zrtos/vfs_module.h>
#include <zrtos/gpio.h>
#include <zrtos/binary.h>
#include <zrtos/va.h>
#include <zrtos/task_mutex.h>

typedef enum{
	 ZRTOS_VFS_MODULE_SPI_SYNC_CONTROL__MIN              = ZRTOS_TYPES__UINT8_MIN

	,ZRTOS_VFS_MODULE_SPI_SYNC_CONTROL__CLOCK_RATE_4     = ZRTOS_BINARY__00000000 ///< chip clock/4
	,ZRTOS_VFS_MODULE_SPI_SYNC_CONTROL__CLOCK_RATE_16    = ZRTOS_BINARY__00000001 ///< chip clock/16
	,ZRTOS_VFS_MODULE_SPI_SYNC_CONTROL__CLOCK_RATE_64    = ZRTOS_BINARY__00000010 ///< chip clock/64
	,ZRTOS_VFS_MODULE_SPI_SYNC_CONTROL__CLOCK_RATE_128   = ZRTOS_BINARY__00000011 ///< chip clock/128
	/*
	,ZRTOS_VFS_MODULE_SPI_SYNC_CONTROL__CLOCK_RATE_2     = ZRTOS_BINARY__00000100 ///< chip clock/2
	,ZRTOS_VFS_MODULE_SPI_SYNC_CONTROL__CLOCK_RATE_8     = ZRTOS_BINARY__00000101 ///< chip clock/8
	,ZRTOS_VFS_MODULE_SPI_SYNC_CONTROL__CLOCK_RATE_32    = ZRTOS_BINARY__00000110 ///< chip clock/32
	,ZRTOS_VFS_MODULE_SPI_SYNC_CONTROL__CLOCK_RATE_64x   = ZRTOS_BINARY__00000111 ///< chip clock/32
	*/
	,ZRTOS_VFS_MODULE_SPI_SYNC_CONTROL__CLOCK_RATE_MASK  = ZRTOS_BINARY__00000011 ///< mask

	,ZRTOS_VFS_MODULE_SPI_SYNC_CONTROL__MODE_MASTER      = ZRTOS_BINARY__00010000
	,ZRTOS_VFS_MODULE_SPI_SYNC_CONTROL__MODE_SLAVE       = ZRTOS_BINARY__00000000
	,ZRTOS_VFS_MODULE_SPI_SYNC_CONTROL__MODE_MASK        = ZRTOS_BINARY__00010000 ///< mask

	,ZRTOS_VFS_MODULE_SPI_SYNC_CONTROL__BITORDER_LSB     = ZRTOS_BINARY__00100000 ///< send least significant bit (bit 0) first
	,ZRTOS_VFS_MODULE_SPI_SYNC_CONTROL__BITORDER_MSB     = ZRTOS_BINARY__00000000 ///< send most significant bit (bit 7) first
	,ZRTOS_VFS_MODULE_SPI_SYNC_CONTROL__BITORDER_MASK    = ZRTOS_BINARY__00100000 ///< mask

	,ZRTOS_VFS_MODULE_SPI_SYNC_CONTROL__PP_0             = ZRTOS_BINARY__00000000 ///< Sample (Rising) Setup (Falling) CPOL=0, CPHA=0
	,ZRTOS_VFS_MODULE_SPI_SYNC_CONTROL__PP_1             = ZRTOS_BINARY__00000100 ///< Setup (Rising) Sample (Falling) CPOL=0, CPHA=1
	,ZRTOS_VFS_MODULE_SPI_SYNC_CONTROL__PP_2             = ZRTOS_BINARY__00001000 ///< Sample (Falling) Setup (Rising) CPOL=1, CPHA=0
	,ZRTOS_VFS_MODULE_SPI_SYNC_CONTROL__PP_3             = ZRTOS_BINARY__00001100 ///< Setup (Falling) Sample (Rising) CPOL=1, CPHA=1
	,ZRTOS_VFS_MODULE_SPI_SYNC_CONTROL__PP_MASK          = ZRTOS_BINARY__00001100 ///< mask

	,ZRTOS_VFS_MODULE_SPI_SYNC_CONTROL__ENABLE           = ZRTOS_BINARY__01000000 ///< enable spi

	,ZRTOS_VFS_MODULE_SPI_SYNC_CONTROL__MAX              = ZRTOS_TYPES__UINT8_MAX
}zrtos_vfs_module_spi_sync_control_t;

typedef struct _zrtos_vfs_module_spi_sync_file_t{
	zrtos_vfs_module_spi_sync_control_t control;
	zrtos_gpio_pin_t                    pin_cs;
}zrtos_vfs_module_spi_sync_file_t;

typedef struct _zrtos_vfs_module_spi_sync_args_t{
	zrtos_gpio_t                    *gpio;
	zrtos_gpio_pin_t                pin_sclk;
	zrtos_gpio_pin_t                pin_mosi;
	zrtos_gpio_pin_t                pin_miso;
	zrtos_task_mutex_t              mutex;
	uint8_t                         count;
}zrtos_vfs_module_spi_sync_args_t;

bool zrtos_vfs_module_spi_sync_args__init(
	 zrtos_vfs_module_spi_sync_args_t *thiz
	,zrtos_gpio_t                *gpio
	,zrtos_gpio_pin_t            pin_sclk
	,zrtos_gpio_pin_t            pin_mosi
	,zrtos_gpio_pin_t            pin_miso
){
	thiz->gpio = gpio;
	thiz->pin_sclk = pin_sclk;
	thiz->pin_mosi = pin_mosi;
	thiz->pin_miso = pin_miso;
	thiz->count = 0;
	return zrtos_task_mutex__init(&thiz->mutex);
}

void zrtos_vfs_module_spi_sync_args__deinit(zrtos_vfs_module_spi_sync_file_t *thiz){
}

bool zrtos_vfs_module_spi_sync_file__init(
	 zrtos_vfs_module_spi_sync_file_t    *thiz
	,zrtos_vfs_module_spi_sync_args_t    *ctx
	,zrtos_vfs_module_spi_sync_control_t control
	,zrtos_gpio_pin_t               pin_cs
	,void                           *data
){
	thiz->control = control;
	thiz->pin_cs = pin_cs;
	thiz->data = data;
	return true;
}

zrtos_error_t zrtos_vfs_module_spi_sync__on_open(
	 zrtos_vfs_file_t *thiz
){
	zrtos_vfs_module_spi_sync_args_t *inode_data = ZRTOS_CAST(
		 zrtos_vfs_module_spi_sync_args_t*
		,zrtos_vfs_file__get_inode_data(thiz)
	);
	zrtos_vfs_module_spi_sync_file_t *file_data = ZRTOS_CAST(
		 zrtos_vfs_module_spi_sync_file_t*
		,zrtos_vfs_file__get_data(thiz)
	);
	zrtos_error_t ret = zrtos_gpio__set_mode(
		 inode_data->gpio
		,file_data->pin_cs
		,ZRTOS_GPIO_MODE__OUTPUT
	);

	return zrtos_error__is_success(ret)
	     ? zrtos_gpio__set_high(
	          inode_data->gpio
	         ,file_data->pin_cs
	       )
	     : ret
	;
}

zrtos_error_t zrtos_vfs_module_spi_sync__on_close(
	 zrtos_vfs_file_t *thiz
){
	return zrtos_vfs_module_spi_sync__on_open(thiz);
}


zrtos_error_t zrtos_vfs_module_spi_sync__on_mount(zrtos_vfs_dentry_t *thiz){
	zrtos_vfs_module_spi_sync_args_t *inode_data = ZRTOS_CAST(
		 zrtos_vfs_module_spi_sync_args_t*
		,zrtos_vfs_file__get_inode_data(thiz)
	);
	return zrtos_gpio__set_mode_ex(
		 inode_data->gpio
		,3
		,inode_data->pin_miso
		,ZRTOS_GPIO_MODE__INPUT
		,inode_data->pin_mosi
		,ZRTOS_GPIO_MODE__OUTPUT
		,inode_data->pin_sclk
		,ZRTOS_GPIO_MODE__OUTPUT
	);
}

zrtos_error_t zrtos_vfs_module_spi_sync__on_umount(zrtos_vfs_dentry_t *thiz){
	return ZRTOS_ERROR__SUCCESS;
}

zrtos_error_t zrtos_vfs_module_spi_sync__on_write_helper(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *out
	,zrtos_error_t (*callback)(
		zrtos_vfs_module_spi_sync_args_t *inode_data
		,zrtos_vfs_module_spi_sync_file_t *file_data
		,void *buf
		,size_t len
		,size_t *l
	)
){
	zrtos_vfs_module_spi_sync_args_t *inode_data = ZRTOS_CAST(
		 zrtos_vfs_module_spi_sync_args_t*
		,zrtos_vfs_file__get_inode_data(thiz)
	);
	zrtos_vfs_module_spi_sync_file_t *file_data = ZRTOS_CAST(
		 zrtos_vfs_module_spi_sync_file_t*
		,zrtos_vfs_file__get_data(thiz)
	);
	uint8_t *data = ZRTOS_CAST(uint8_t*,buf);
	zrtos_error_t ret = zrtos_task_mutex__lock(inode_data->mutex);
	if(zrtos_error__is_success(ret)){
		*out = len;
		while(len){
			if(inode_data->count == 0){
				ret = zrtos_gpio__set_low(
					inode_data->gpio
					,file_data->pin_cs
				);
				inode_data->count = *data++;
				len--;
			}

			while(len && inode_data->count && zrtos_error__is_success(ret)){
				//transfer
				size_t l;
				ret = callback(inode_data,file_data,buf,len,l);
				buf += l;
				len -= l;
				inode_data->count -= l;
			}

			if(inode_data->count == 0){
				ret = zrtos_gpio__set_high(
					inode_data->gpio
					,file_data->pin_cs
				);
			}
		}
		zrtos_task_mutex__unlock(inode_data->mutex);
	}
	return ret;
}

/*
zrtos_error_t zrtos_vfs_module_spi_sync__on_write(
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
		,zrtos_error_t (*callback)(
			zrtos_vfs_module_spi_sync_args_t *inode_data
			,zrtos_vfs_module_spi_sync_file_t *file_data
			,void *buf
			,size_t len
			,size_t l
		)
	);
}


ZRTOS_VFS_PLUGIN__INIT(spi,
	ZRTOS_VFS_PLUGIN__0_ON_OPEN(zrtos_vfs_module_spi_sync_sync__on_open)
	ZRTOS_VFS_PLUGIN__1_ON_CLOSE(zrtos_vfs_module_spi_sync_sync__on_close)
	ZRTOS_VFS_PLUGIN__2_ON_MOUNT(zrtos_vfs_module_spi_sync_sync__on_mount)
	ZRTOS_VFS_PLUGIN__3_ON_UMOUNT(zrtos_vfs_module_spi_sync_sync__on_umount)
	ZRTOS_VFS_PLUGIN__4_ON_READ_DEFAULT()
	ZRTOS_VFS_PLUGIN__5_ON_WRITE(zrtos_vfs_module_spi_sync_sync__on_write)
	ZRTOS_VFS_PLUGIN__6_ON_CAN_READ_DEFAULT()
	ZRTOS_VFS_PLUGIN__7_ON_CAN_WRITE_DEFAULT()
	ZRTOS_VFS_PLUGIN__8_ON_SEEK_DEFAULT()
	ZRTOS_VFS_PLUGIN__9_ON_IOCTL_DEFAULT()
);
*/

#ifdef __cplusplus
}
#endif
#endif
