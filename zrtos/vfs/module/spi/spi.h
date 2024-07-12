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

#ifndef ZRTOS_VFS_MODULE_SPI__CFG_TRANSFER_LENGTH
#define ZRTOS_VFS_MODULE_SPI__CFG_TRANSFER_LENGTH ZRTOS_CBUFFER__CFG_DATA_LENGTH
#endif

typedef enum{
	 ZRTOS_VFS_MOULE_SPI_IOCTL__CONTROL
	,ZRTOS_VFS_MOULE_SPI_IOCTL__PIN_SS
}zrtos_vfs_module_spi_ioctl_t;

typedef enum{
	 ZRTOS_VFS_MODULE_SPI_CONTROL__MIN             = ZRTOS_TYPES__UINT8_MIN

	,ZRTOS_VFS_MODULE_SPI_CONTROL__CLOCK_RATE_4    = ZRTOS_BINARY__00000000 ///< chip clock/4
	,ZRTOS_VFS_MODULE_SPI_CONTROL__CLOCK_RATE_16   = ZRTOS_BINARY__00000001 ///< chip clock/16
	,ZRTOS_VFS_MODULE_SPI_CONTROL__CLOCK_RATE_64   = ZRTOS_BINARY__00000010 ///< chip clock/64
	,ZRTOS_VFS_MODULE_SPI_CONTROL__CLOCK_RATE_128  = ZRTOS_BINARY__00000011 ///< chip clock/128
	,ZRTOS_VFS_MODULE_SPI_CONTROL__CLOCK_RATE_2    = ZRTOS_BINARY__00000100 ///< chip clock/2
	,ZRTOS_VFS_MODULE_SPI_CONTROL__CLOCK_RATE_8    = ZRTOS_BINARY__00000101 ///< chip clock/8
	,ZRTOS_VFS_MODULE_SPI_CONTROL__CLOCK_RATE_32   = ZRTOS_BINARY__00000110 ///< chip clock/32
	,ZRTOS_VFS_MODULE_SPI_CONTROL__CLOCK_RATE_64x  = ZRTOS_BINARY__00000111 ///< chip clock/32
	,ZRTOS_VFS_MODULE_SPI_CONTROL__CLOCK_RATE_MASK = ZRTOS_BINARY__00000111 ///< mask

	,ZRTOS_VFS_MODULE_SPI_CONTROL__MODE_MASTER     = ZRTOS_BINARY__00010000
	,ZRTOS_VFS_MODULE_SPI_CONTROL__MODE_SLAVE      = ZRTOS_BINARY__00000000
	,ZRTOS_VFS_MODULE_SPI_CONTROL__MODE_MASK       = ZRTOS_BINARY__00010000 ///< mask

	,ZRTOS_VFS_MODULE_SPI_CONTROL__BITORDER_LSB    = ZRTOS_BINARY__00100000 ///< send least significant bit (bit 0) first
	,ZRTOS_VFS_MODULE_SPI_CONTROL__BITORDER_MSB    = ZRTOS_BINARY__00000000 ///< send most significant bit (bit 7) first
	,ZRTOS_VFS_MODULE_SPI_CONTROL__BITORDER_MASK   = ZRTOS_BINARY__00100000 ///< mask

	,ZRTOS_VFS_MODULE_SPI_CONTROL__PP_0            = ZRTOS_BINARY__00000000 ///< Sample (Rising) Setup (Falling) CPOL=0, CPHA=0
	,ZRTOS_VFS_MODULE_SPI_CONTROL__PP_1            = ZRTOS_BINARY__01000000 ///< Setup (Rising) Sample (Falling) CPOL=0, CPHA=1
	,ZRTOS_VFS_MODULE_SPI_CONTROL__PP_2            = ZRTOS_BINARY__10000000 ///< Sample (Falling) Setup (Rising) CPOL=1, CPHA=0
	,ZRTOS_VFS_MODULE_SPI_CONTROL__PP_3            = ZRTOS_BINARY__11000000 ///< Setup (Falling) Sample (Rising) CPOL=1, CPHA=1
	,ZRTOS_VFS_MODULE_SPI_CONTROL__PP_MASK         = ZRTOS_BINARY__11000000 ///< mask

	,ZRTOS_VFS_MODULE_SPI_CONTROL__MAX             = ZRTOS_TYPES__UINT8_MAX
}zrtos_vfs_module_spi_control_t;

typedef struct _zrtos_vfs_module_spi_file_t{
	zrtos_clist_node_t             node;
	zrtos_cbuffer_t                cbuffer_in;
	zrtos_cbuffer_t                cbuffer_out;
	zrtos_error_t                  error;
	zrtos_vfs_module_spi_control_t control;
	zrtos_gpio_pin_t               pin_ss;
	void                           *data;
}zrtos_vfs_module_spi_file_t;

typedef struct _zrtos_vfs_module_spi_args_t{
	zrtos_gpio_t                    *gpio;
	zrtos_gpio_pin_t                pin_sck;
	zrtos_gpio_pin_t                pin_mosi;
	zrtos_gpio_pin_t                pin_miso;
	zrtos_clist_t                   root;
	zrtos_vfs_module_spi_file_t     *last;
	size_t                          count;
}zrtos_vfs_module_spi_args_t;

bool zrtos_vfs_module_spi_args__init(
	 zrtos_vfs_module_spi_args_t *thiz
	,zrtos_gpio_t                *gpio
	,zrtos_gpio_pin_t            pin_sck
	,zrtos_gpio_pin_t            pin_mosi
	,zrtos_gpio_pin_t            pin_miso
){
	thiz->gpio = gpio;
	thiz->pin_sck = pin_sck;
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
	 zrtos_vfs_module_spi_file_t *thiz
	,zrtos_vfs_module_spi_args_t *ctx
	,void                        *data
){
	zrtos_clist_node__init(&thiz->node);
	thiz->error = ESUCCESS;
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
	 zrtos_vfs_module_spi_args_t *ctx
	,void                        *data
){
	zrtos_vfs_module_spi_file_t *thiz = ZRTOS_CAST(
		 zrtos_vfs_module_spi_file_t *
		,kmalloc(sizeof(zrtos_vfs_module_spi_file_t))
	);
	if(thiz){
		if(!zrtos_vfs_module_spi_file__init(thiz,ctx,data)){
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
	free(thiz);
}

zrtos_error_t zrtos_vfs_module_spi__on_before_file_transfer(
	 zrtos_vfs_module_spi_file_t *thiz_
){
/*
	zrtos_vfs_file_t *thiz = ((zrtos_vfs_module_avr_spi_file_t *)thiz_)->thiz;
	zrtos_vfs_module_spi_file_t *file = zrtos_vfs_file__get_data(thiz);
	zrtos_vfs_module_avr_spi_args_t *inode = zrtos_vfs_file__get_inode_data(thiz);
	zrtos_gpio_t *gpio = inode->gpio;

	zrtos_gpio__set_mode_ex(
		 gpio
		,inode->pin_miso
		,ZRTOS_GPIO_MODE__OUTPUT
		,file->pin_ss
		,ZRTOS_GPIO_MODE__INPUT
		,inode->pin_mosi
		,ZRTOS_GPIO_MODE__INPUT
		,inode->pin_sck
		,ZRTOS_GPIO_MODE__INPUT
	);

	zrtos_gpio__set_low(
		 gpio
		,file->pin_ss
	);

	SPCR = file->spcr;


*/
	return ESUCCESS;
}

zrtos_error_t zrtos_vfs_module_spi__on_after_file_transfer(
	 zrtos_vfs_module_spi_file_t *thiz_
){
/*
	zrtos_vfs_file_t *thiz = ((zrtos_vfs_module_avr_spi_file_t *)thiz_)->thiz;
	zrtos_vfs_module_spi_file_t *file_data = ZRTOS_CAST(
		 zrtos_vfs_module_spi_file_t*
		,zrtos_vfs_file__get_data(thiz)
	);
	zrtos_vfs_module_spi_args_t *inode_data = ZRTOS_CAST(
		 zrtos_vfs_module_spi_args_t*
		,zrtos_vfs_file__get_inode_data(thiz)
	);
	zrtos_gpio_t *gpio = inode_data->gpio;

	zrtos_gpio__set_high(
		 gpio
		,file_data->pin_ss
	);


*/
	return ESUCCESS;
}

static void zrtos_vfs_module_spi__get(
	 zrtos_vfs_module_spi_args_t *thiz
	,void                   *data
	,size_t                 len
){
/*
	zrtos_clist_node_t *node = zrtos_clist__get_first_node(&thiz->root);
	if(node){
		zrtos_vfs_module_spi_file_t *first = zrtos_types__get_container_of(
			 node
			,zrtos_vfs_module_spi_file_t
			,node
		);
		zrtos_vfs_module_spi.last = first;

		if(zrtos_cbuffer__is_empty(&first->cbuffer_out)
		|| ++count > ZRTOS_VFS_MODULE_SPI__CFG_TRANSFER_LENGTH){
			count = 0;
			zrtos_clist__shift_and_push(&thiz->root);
		}
		ZRTOS_CLIST__EACH_BEGIN(
			 &thiz->root
			,node
			,zrtos_vfs_module_spi_file_t
			,node
		){
			if(!zrtos_cbuffer__is_empty(&first->cbuffer_out)){
				first->error = zrtos_cbuffer__get_ex(
					 &last->cbuffer_out
					 1
					,outlen
					,data
					,len
				);
			}
		}ZRTOS_CLIST__EACH_END;
	}
*/
}

static void zrtos_vfs_module_spi__put(
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

void zrtos_vfs_module_spi__transfer(
	 zrtos_vfs_module_spi_args_t *thiz
	,void                   *data_in
	,void                   *data_out
	,size_t                 len
){
	zrtos_vfs_module_spi__put(thiz,data_in,len);
	zrtos_vfs_module_spi__get(
		 thiz
		,data_out
		,len
	);
}

zrtos_error_t zrtos_vfs_module_spi__on_open(
	 zrtos_vfs_file_t *thiz
	,char             *path
){
	zrtos_error_t ret = ENOMEM;
	zrtos_vfs_module_spi_args_t *inode_data = ZRTOS_CAST(
		 zrtos_vfs_module_spi_args_t*
		,zrtos_vfs_file__get_inode_data(thiz)
	);
	zrtos_vfs_module_spi_file_t *file_data = zrtos_vfs_module_spi_file__new(
		 inode_data
		,0
	);
	if(file_data){
		zrtos_vfs_file__set_data(thiz,file_data);
		ret = ESUCCESS;
	}
	return ret;
}

zrtos_error_t zrtos_vfs_module_spi__on_close(
	 zrtos_vfs_file_t *thiz
	,char             *path
){
	zrtos_vfs_module_spi_args_t *inode_data = ZRTOS_CAST(
		 zrtos_vfs_module_spi_args_t*
		,zrtos_vfs_file__get_inode_data(thiz)
	);
	zrtos_vfs_module_spi_file_t *file_data = ZRTOS_CAST(
		 zrtos_vfs_module_spi_file_t*
		,zrtos_vfs_file__get_data(thiz)
	);
	zrtos_vfs_module_spi_file__free(file_data,inode_data);
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
	,char *path
){
	zrtos_vfs_module_spi_file_t *file_data = ZRTOS_CAST(
		 zrtos_vfs_module_spi_file_t*
		,zrtos_vfs_file__get_data(thiz)
	);
	return zrtos_cbuffer__can_read(&file_data->cbuffer_in);
}

zrtos_error_t zrtos_vfs_module_spi__on_can_write(
	 zrtos_vfs_file_t *thiz
	,char *path
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
		case ZRTOS_VFS_MOULE_SPI_IOCTL__PIN_SS:
			file_data->pin_ss = zrtos_va__arg(args,zrtos_gpio_pin_t);
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
