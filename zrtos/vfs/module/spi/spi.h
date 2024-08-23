/* Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_SPI_H
#define ZRTOS_VFS_MODULE_SPI_H
#ifdef __cplusplus
extern "C" {
#endif

#include <zrtos/vfs_module.h>
#include <zrtos/malloc.h>
#include <zrtos/cbuffer.h>
#include <zrtos/clist.h>
#include <zrtos/gpio.h>
#include <zrtos/binary.h>
#include <zrtos/va.h>

typedef enum{
	 ZRTOS_VFS_MOULE_SPI_IOCTL__CONTROL
	,ZRTOS_VFS_MOULE_SPI_IOCTL__PIN_CS
}zrtos_vfs_module_spi_ioctl_t;

typedef enum{
	 ZRTOS_VFS_MODULE_SPI_CONTROL__MIN              = ZRTOS_TYPES__UINT8_MIN

	,ZRTOS_VFS_MODULE_SPI_CONTROL__CLOCK_RATE_4     = ZRTOS_BINARY__00000000 ///< chip clock/4
	,ZRTOS_VFS_MODULE_SPI_CONTROL__CLOCK_RATE_16    = ZRTOS_BINARY__00000001 ///< chip clock/16
	,ZRTOS_VFS_MODULE_SPI_CONTROL__CLOCK_RATE_64    = ZRTOS_BINARY__00000010 ///< chip clock/64
	,ZRTOS_VFS_MODULE_SPI_CONTROL__CLOCK_RATE_128   = ZRTOS_BINARY__00000011 ///< chip clock/128
	/*
	,ZRTOS_VFS_MODULE_SPI_CONTROL__CLOCK_RATE_2     = ZRTOS_BINARY__00000100 ///< chip clock/2
	,ZRTOS_VFS_MODULE_SPI_CONTROL__CLOCK_RATE_8     = ZRTOS_BINARY__00000101 ///< chip clock/8
	,ZRTOS_VFS_MODULE_SPI_CONTROL__CLOCK_RATE_32    = ZRTOS_BINARY__00000110 ///< chip clock/32
	,ZRTOS_VFS_MODULE_SPI_CONTROL__CLOCK_RATE_64x   = ZRTOS_BINARY__00000111 ///< chip clock/32
	*/
	,ZRTOS_VFS_MODULE_SPI_CONTROL__CLOCK_RATE_MASK  = ZRTOS_BINARY__00000011 ///< mask

	,ZRTOS_VFS_MODULE_SPI_CONTROL__MODE_MASTER      = ZRTOS_BINARY__00010000
	,ZRTOS_VFS_MODULE_SPI_CONTROL__MODE_SLAVE       = ZRTOS_BINARY__00000000
	,ZRTOS_VFS_MODULE_SPI_CONTROL__MODE_MASK        = ZRTOS_BINARY__00010000 ///< mask

	,ZRTOS_VFS_MODULE_SPI_CONTROL__BITORDER_LSB     = ZRTOS_BINARY__00100000 ///< send least significant bit (bit 0) first
	,ZRTOS_VFS_MODULE_SPI_CONTROL__BITORDER_MSB     = ZRTOS_BINARY__00000000 ///< send most significant bit (bit 7) first
	,ZRTOS_VFS_MODULE_SPI_CONTROL__BITORDER_MASK    = ZRTOS_BINARY__00100000 ///< mask

	,ZRTOS_VFS_MODULE_SPI_CONTROL__PP_0             = ZRTOS_BINARY__00000000 ///< Sample (Rising) Setup (Falling) CPOL=0, CPHA=0
	,ZRTOS_VFS_MODULE_SPI_CONTROL__PP_1             = ZRTOS_BINARY__00000100 ///< Setup (Rising) Sample (Falling) CPOL=0, CPHA=1
	,ZRTOS_VFS_MODULE_SPI_CONTROL__PP_2             = ZRTOS_BINARY__00001000 ///< Sample (Falling) Setup (Rising) CPOL=1, CPHA=0
	,ZRTOS_VFS_MODULE_SPI_CONTROL__PP_3             = ZRTOS_BINARY__00001100 ///< Setup (Falling) Sample (Rising) CPOL=1, CPHA=1
	,ZRTOS_VFS_MODULE_SPI_CONTROL__PP_MASK          = ZRTOS_BINARY__00001100 ///< mask

	,ZRTOS_VFS_MODULE_SPI_CONTROL__ENABLE           = ZRTOS_BINARY__01000000 ///< enable spi
	,ZRTOS_VFS_MODULE_SPI_CONTROL__ENABLE_INTERRUPT = ZRTOS_BINARY__10000000 ///< enable interrupt

	,ZRTOS_VFS_MODULE_SPI_CONTROL__MAX              = ZRTOS_TYPES__UINT8_MAX
}zrtos_vfs_module_spi_control_t;

typedef struct _zrtos_vfs_module_spi_file_t{
	zrtos_clist_node_t             node;
	zrtos_cbuffer_t                cbuffer_in;
	zrtos_cbuffer_t                cbuffer_out;
	zrtos_error_t                  error;
	zrtos_vfs_module_spi_control_t control;
	zrtos_gpio_pin_t               pin_cs;
	void                           *data;
}zrtos_vfs_module_spi_file_t;

typedef struct _zrtos_vfs_module_spi_args_t{
	zrtos_gpio_t                    *gpio;
	zrtos_gpio_pin_t                pin_sclk;
	zrtos_gpio_pin_t                pin_mosi;
	zrtos_gpio_pin_t                pin_miso;
	zrtos_clist_t                   root;
	zrtos_vfs_module_spi_file_t     *last;
	size_t                          count;
}zrtos_vfs_module_spi_args_t;

bool zrtos_vfs_module_spi_args__init(
	 zrtos_vfs_module_spi_args_t *thiz
	,zrtos_gpio_t                *gpio
	,zrtos_gpio_pin_t            pin_sclk
	,zrtos_gpio_pin_t            pin_mosi
	,zrtos_gpio_pin_t            pin_miso
){
	thiz->gpio = gpio;
	thiz->pin_sclk = pin_sclk;
	thiz->pin_mosi = pin_mosi;
	thiz->pin_miso = pin_miso;
	zrtos_clist__init(&thiz->root);
	thiz->last = 0;
	thiz->count = 0;
	return true;
}

void zrtos_vfs_module_spi_args__deinit(zrtos_vfs_module_spi_file_t *thiz){
}

bool zrtos_vfs_module_spi_file__init(
	 zrtos_vfs_module_spi_file_t    *thiz
	,zrtos_vfs_module_spi_args_t    *ctx
	,zrtos_vfs_module_spi_control_t control
	,zrtos_gpio_pin_t               pin_cs
	,void                           *data
){
	zrtos_clist_node__init(&thiz->node);
	thiz->error = ESUCCESS;
	thiz->control = control;
	thiz->pin_cs = pin_cs;
	thiz->data = data;
	if(zrtos_cbuffer__init(&thiz->cbuffer_in)){
		if(zrtos_cbuffer__init(&thiz->cbuffer_out)){
			zrtos_clist__push(&ctx->root,&thiz->node);
			return true;
		}
		zrtos_cbuffer__deinit(&thiz->cbuffer_in);
	}
	return false;
}

void zrtos_vfs_module_spi_file__deinit(
	 zrtos_vfs_module_spi_file_t *thiz
	,zrtos_vfs_module_spi_args_t *ctx
){
	zrtos_cbuffer__deinit(&thiz->cbuffer_in);
	zrtos_cbuffer__deinit(&thiz->cbuffer_out);
	zrtos_clist__delete(&ctx->root,&thiz->node);
}

zrtos_vfs_module_spi_file_t *zrtos_vfs_module_spi_file__new(
	 zrtos_vfs_module_spi_args_t    *ctx
	,zrtos_vfs_module_spi_control_t control
	,zrtos_gpio_pin_t               pin_cs
	,void                           *data
){
	zrtos_vfs_module_spi_file_t *thiz = ZRTOS_CAST(
		 zrtos_vfs_module_spi_file_t *
		,kmalloc(sizeof(zrtos_vfs_module_spi_file_t))
	);
	if(thiz){
		if(!zrtos_vfs_module_spi_file__init(thiz,ctx,control,pin_cs,data)){
			kfree(thiz);
			thiz = 0;
		}
	}
	return thiz;
}

void zrtos_vfs_module_spi_file__free(
	 zrtos_vfs_module_spi_file_t *thiz
	,zrtos_vfs_module_spi_args_t *ctx
){
	zrtos_vfs_module_spi_file__deinit(thiz,ctx);
	kfree(thiz);
}

void zrtos_vfs_module_spi__transfer_out_before(
	 zrtos_vfs_module_spi_args_t *thiz
	,zrtos_vfs_module_spi_file_t *file
){
	zrtos_gpio_mode_t input;
	zrtos_gpio_mode_t output;

	if(file->control & ZRTOS_VFS_MODULE_SPI_CONTROL__MODE_MASTER){
		input = ZRTOS_GPIO_MODE__INPUT;
		output = ZRTOS_GPIO_MODE__OUTPUT;
	}else{
		input = ZRTOS_GPIO_MODE__OUTPUT;
		output = ZRTOS_GPIO_MODE__INPUT;
	}

	file->error = zrtos_gpio__set_mode_ex(
		 thiz->gpio
		,4
		,thiz->pin_miso
		,input
		,file->pin_cs
		,output
		,thiz->pin_mosi
		,output
		,thiz->pin_sclk
		,output
	);

	if(zrtos_error__is_success(file->error)){
		file->error = zrtos_gpio__set_low(
			 thiz->gpio
			,file->pin_cs
		);
	}
}

void zrtos_vfs_module_spi__transfer_out_after(
	 zrtos_vfs_module_spi_args_t *thiz
	,zrtos_vfs_module_spi_file_t *file
){
	//@todo fix error code
	file->error = zrtos_gpio__set_high(
		 thiz->gpio
		,file->pin_cs
	);
}

void zrtos_vfs_module_spi__transfer_out(
	 zrtos_vfs_module_spi_args_t *thiz
	,void                   *data
	,size_t                 len
){
	size_t outlen;
	zrtos_vfs_module_spi_file_t *last = thiz->last;

	if(thiz->count == 0){
		if(last){
			zrtos_vfs_module_spi__transfer_out_after(thiz,last);
			zrtos_clist__set_root(
				&thiz->root
				,zrtos_clist_node__get_next_node(&last->node)
			);
			last = thiz->last = 0;
		}

		ZRTOS_CLIST__EACH_BEGIN(
			 &thiz->root
			,node
			,zrtos_vfs_module_spi_file_t
			,node
		){
			if(zrtos_error__is_success(node->error)
			&& !zrtos_cbuffer__is_empty(&node->cbuffer_out)){
				last = thiz->last = node;

				last->error = zrtos_cbuffer__get_ex(
					 &last->cbuffer_out
					,&thiz->count
					,sizeof(thiz->count)
					,&outlen
				);
				zrtos_vfs_module_spi__transfer_out_before(thiz,last);

				break;
			}
		}ZRTOS_CLIST__EACH_END;
	}

	if(last
	&& zrtos_error__is_success(last->error)){
		last->error = zrtos_cbuffer__get_ex(
			 &last->cbuffer_out
			,data
			,len
			,&outlen
		);
	}
}

void zrtos_vfs_module_spi__transfer_in(
	 zrtos_vfs_module_spi_args_t *thiz
	,void                   *data
	,size_t                 len
){
	zrtos_vfs_module_spi_file_t *last = thiz->last;
	if(last
	&& zrtos_error__is_success(last->error)){
		size_t outlen;
		last->error = zrtos_cbuffer__put_ex(
			 &last->cbuffer_in
			,1
			,&outlen
			,data
			,len
		);
	}
}

zrtos_error_t zrtos_vfs_module_spi__transfer(
	 zrtos_vfs_module_spi_args_t *thiz
	,void                   *data_in
	,void                   *data_out
	,size_t                 len
){
	zrtos_vfs_module_spi_file_t *last;
	zrtos_vfs_module_spi__transfer_in(thiz,data_in,len);
	zrtos_vfs_module_spi__transfer_out(
		 thiz
		,data_out
		,len
	);
	last = thiz->last;
	return last ? last->error : ENODATA;
}

zrtos_error_t zrtos_vfs_module_spi__on_open(
	 zrtos_vfs_file_t *thiz
){
/*
	zrtos_error_t ret = ENOMEM;
	zrtos_vfs_module_spi_args_t *inode_data = ZRTOS_CAST(
		 zrtos_vfs_module_spi_args_t*
		,zrtos_vfs_file__get_inode_data(thiz)
	);
	zrtos_vfs_module_spi_file_t *file_data = zrtos_vfs_module_spi_file__new(
		 inode_data
		,(zrtos_vfs_module_spi_control_t)0
		,0
		,0
	);
	if(file_data){
		zrtos_vfs_file__set_data(thiz,file_data);
		ret = ESUCCESS;
	}
	return ret;
*/
	return ESUCCESS;
}

zrtos_error_t zrtos_vfs_module_spi__on_close(
	 zrtos_vfs_file_t *thiz
){
/*
	zrtos_vfs_module_spi_args_t *inode_data = ZRTOS_CAST(
		 zrtos_vfs_module_spi_args_t*
		,zrtos_vfs_file__get_inode_data(thiz)
	);
	zrtos_vfs_module_spi_file_t *file_data = ZRTOS_CAST(
		 zrtos_vfs_module_spi_file_t*
		,zrtos_vfs_file__get_data(thiz)
	);
	zrtos_vfs_module_spi_file__free(file_data,inode_data);
*/
	return ESUCCESS;
}

zrtos_error_t zrtos_vfs_module_spi__on_read(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *outlen
){
	zrtos_vfs_module_spi_file_t *file_data = ZRTOS_CAST(
		 zrtos_vfs_module_spi_file_t*
		,zrtos_vfs_file__get_data(thiz)
	);
	return zrtos_cbuffer__get_ex(
		 &file_data->cbuffer_in
		,buf
		,len
		,outlen
	);
}

zrtos_error_t zrtos_vfs_module_spi__on_write(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *out
){
	zrtos_vfs_module_spi_file_t *file_data = ZRTOS_CAST(
		 zrtos_vfs_module_spi_file_t*
		,zrtos_vfs_file__get_data(thiz)
	);
	size_t outlen;
	Serial.println("##SPI WRITE CBUFFER##");
	return zrtos_cbuffer__put_ex(
		 &file_data->cbuffer_out
		,1
		,&outlen
		,buf
		,len
	);
}

zrtos_error_t zrtos_vfs_module_spi__on_can_read(
	 zrtos_vfs_file_t *thiz
){
	zrtos_vfs_module_spi_file_t *file_data = ZRTOS_CAST(
		 zrtos_vfs_module_spi_file_t*
		,zrtos_vfs_file__get_data(thiz)
	);
	return zrtos_cbuffer__can_read(&file_data->cbuffer_in);
}

zrtos_error_t zrtos_vfs_module_spi__on_can_write(
	 zrtos_vfs_file_t *thiz
){
	zrtos_vfs_module_spi_file_t *file_data = ZRTOS_CAST(
		 zrtos_vfs_module_spi_file_t*
		,zrtos_vfs_file__get_data(thiz)
	);
	return zrtos_cbuffer__can_write(&file_data->cbuffer_out);
}

zrtos_error_t zrtos_vfs_module_spi__on_ioctl(
	 zrtos_vfs_file_t *thiz
	,char *path
	,int request
	,va_list args
){
	zrtos_vfs_module_spi_file_t *file_data = ZRTOS_CAST(
		zrtos_vfs_module_spi_file_t*
		,zrtos_vfs_file__get_data(thiz)
	);
	switch(request){
		case ZRTOS_VFS_MOULE_SPI_IOCTL__CONTROL:
			file_data->control = zrtos_va__arg(args,zrtos_vfs_module_spi_control_t);
		break;
		case ZRTOS_VFS_MOULE_SPI_IOCTL__PIN_CS:
			file_data->pin_cs = zrtos_va__arg(args,zrtos_gpio_pin_t);
		break;
	}
	return ESUCCESS;
}

/*
ZRTOS_VFS_PLUGIN__INIT(spi,
	ZRTOS_VFS_PLUGIN__0_ON_OPEN_DEFAULT()
	ZRTOS_VFS_PLUGIN__1_ON_CLOSE_DEFAULT()
	ZRTOS_VFS_PLUGIN__2_ON_MOUNT_DEFAULT()
	ZRTOS_VFS_PLUGIN__3_ON_UMOUNT_DEFAULT()
	ZRTOS_VFS_PLUGIN__4_ON_READ(zrtos_vfs_module_spi__on_read)
	ZRTOS_VFS_PLUGIN__5_ON_WRITE(zrtos_vfs_module_spi__on_write)
	ZRTOS_VFS_PLUGIN__6_ON_CAN_READ(zrtos_vfs_module_spi__on_can_read)
	ZRTOS_VFS_PLUGIN__7_ON_CAN_WRITE(zrtos_vfs_module_spi__on_can_write)
	ZRTOS_VFS_PLUGIN__8_ON_SEEK_DEFAULT()
	ZRTOS_VFS_PLUGIN__9_ON_IOCTL(zrtos_vfs_module_spi__on_ioctl)
);
*/

#ifdef __cplusplus
}
#endif
#endif
