/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_UART_H
#define ZRTOS_VFS_MODULE_UART_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/vfs_plugin.h>
#include <zrtos/cbuffer.h>
#include <zrtos/binary.h>
#include <zrtos/types.h>

typedef enum{
	 ZRTOS_VFS_MODULE_UART_BAUDRATE__MIN             = ZRTOS_TYPES__UINT32_MIN
	,ZRTOS_VFS_MODULE_UART_BAUDRATE__DOUBLE_SPEED    = 1
	,ZRTOS_VFS_MODULE_UART_BAUDRATE__300             = 300
	,ZRTOS_VFS_MODULE_UART_BAUDRATE__600             = 600
	,ZRTOS_VFS_MODULE_UART_BAUDRATE__1200            = 1200
	,ZRTOS_VFS_MODULE_UART_BAUDRATE__2400            = 2400
	,ZRTOS_VFS_MODULE_UART_BAUDRATE__4800            = 4800
	,ZRTOS_VFS_MODULE_UART_BAUDRATE__9600            = 9600
	,ZRTOS_VFS_MODULE_UART_BAUDRATE__14400           = 14400
	,ZRTOS_VFS_MODULE_UART_BAUDRATE__19200           = 19200
	,ZRTOS_VFS_MODULE_UART_BAUDRATE__28800           = 28800
	,ZRTOS_VFS_MODULE_UART_BAUDRATE__38400           = 38400
	,ZRTOS_VFS_MODULE_UART_BAUDRATE__57600           = 57600
	,ZRTOS_VFS_MODULE_UART_BAUDRATE__76800           = 76800
	,ZRTOS_VFS_MODULE_UART_BAUDRATE__115200          = 115200
	,ZRTOS_VFS_MODULE_UART_BAUDRATE__MASK            = (~((uint32_t)1))
	,ZRTOS_VFS_MODULE_UART_BAUDRATE__MAX             = ZRTOS_TYPES__UINT32_MAX
}zrtos_vfs_module_uart_baudrate_t;

typedef enum{
	 ZRTOS_VFS_MODULE_UART_MODE__MIN             = ZRTOS_TYPES__UINT8_MIN
	,ZRTOS_VFS_MODULE_UART_MODE__PARITY_DISABLED = ZRTOS_BINARY__00000000
	,ZRTOS_VFS_MODULE_UART_MODE__PARITY_EVEN     = ZRTOS_BINARY__00100000
	,ZRTOS_VFS_MODULE_UART_MODE__PARITY_ODD      = ZRTOS_BINARY__00110000
	,ZRTOS_VFS_MODULE_UART_MODE__STOP_BITS_1     = ZRTOS_BINARY__00000000
	,ZRTOS_VFS_MODULE_UART_MODE__STOP_BITS_2     = ZRTOS_BINARY__00001000
	,ZRTOS_VFS_MODULE_UART_MODE__CHAR_SIZE_5     = ZRTOS_BINARY__00000000
	,ZRTOS_VFS_MODULE_UART_MODE__CHAR_SIZE_6     = ZRTOS_BINARY__00000001
	,ZRTOS_VFS_MODULE_UART_MODE__CHAR_SIZE_7     = ZRTOS_BINARY__00000010
	,ZRTOS_VFS_MODULE_UART_MODE__CHAR_SIZE_8     = ZRTOS_BINARY__00000011
	,ZRTOS_VFS_MODULE_UART_MODE__CHAR_SIZE_9     = ZRTOS_BINARY__00000111
	,ZRTOS_VFS_MODULE_UART_MODE__8N1             = (
		  ZRTOS_VFS_MODULE_UART_MODE__CHAR_SIZE_8
		| ZRTOS_VFS_MODULE_UART_MODE__PARITY_DISABLED
		| ZRTOS_VFS_MODULE_UART_MODE__STOP_BITS_1
	)
	,ZRTOS_VFS_MODULE_UART_MODE__MAX             = ZRTOS_TYPES__UINT8_MAX
}zrtos_vfs_module_uart_mode_t;

struct _zrtos_vfs_module_uart_args_t;

typedef void (*zrtos_vfs_module_uart_callback_t)(
	struct _zrtos_vfs_module_uart_args_t *args
);

typedef struct _zrtos_vfs_module_uart_args_t{
	zrtos_cbuffer_t                  cbuffer_in;
	zrtos_cbuffer_t                  cbuffer_out;
	zrtos_error_t                    error;
	zrtos_vfs_module_uart_baudrate_t baudrate;
	zrtos_vfs_module_uart_mode_t     mode;
	zrtos_vfs_module_uart_callback_t on_send;
	zrtos_vfs_module_uart_callback_t on_recv;
}zrtos_vfs_module_uart_args_t;

void zrtos_vfs_module_uart_args__callback(zrtos_vfs_module_uart_args_t *args){}

bool zrtos_vfs_module_uart_args__init(
	 zrtos_vfs_module_uart_args_t *thiz
	,zrtos_vfs_module_uart_baudrate_t baudrate
	,zrtos_vfs_module_uart_mode_t mode
){
	thiz->error = ZRTOS_ERROR__SUCCESS;
	thiz->baudrate = baudrate;
	thiz->mode = mode;
	thiz->on_send = zrtos_vfs_module_uart_args__callback;
	thiz->on_recv = zrtos_vfs_module_uart_args__callback;
	if(zrtos_cbuffer__init(&thiz->cbuffer_in)){
		if(zrtos_cbuffer__init(&thiz->cbuffer_out)){
			return true;
		}
	}
	return false;
}

zrtos_cbuffer_t *zrtos_vfs_module_uart_args__get_cbuffer_in(
	zrtos_vfs_module_uart_args_t *thiz
){
	return &thiz->cbuffer_in;
}

zrtos_cbuffer_t *zrtos_vfs_module_uart_args__get_cbuffer_out(
	zrtos_vfs_module_uart_args_t *thiz
){
	return &thiz->cbuffer_out;
}

void zrtos_vfs_module_uart_args__set_error(
	 zrtos_vfs_module_uart_args_t *thiz
	,zrtos_error_t error
){
	thiz->error = error;
}

zrtos_error_t zrtos_vfs_module_uart_args__get_error(
	zrtos_vfs_module_uart_args_t *thiz
){
	return thiz->error;
}

zrtos_vfs_module_uart_baudrate_t zrtos_vfs_module_uart_args__get_baudrate(
	zrtos_vfs_module_uart_args_t *thiz
){
	return thiz->baudrate;
}

zrtos_vfs_module_uart_mode_t zrtos_vfs_module_uart_args__get_mode(
	zrtos_vfs_module_uart_args_t *thiz
){
	return thiz->mode;
}

zrtos_error_t zrtos_vfs_module_uart__on_read(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *out
){
	zrtos_vfs_module_uart_args_t *mod = ZRTOS_CAST(
		 zrtos_vfs_module_uart_args_t *
		,zrtos_vfs_file__get_inode_data(
			thiz
		)
	);
	zrtos_error_t ret = zrtos_vfs_module_uart_args__get_error(mod);
	if(zrtos_error__is_success(ret)){
		ret = zrtos_cbuffer__get_ex(
			&mod->cbuffer_in
			,buf
			,len
			,out
		);
	}
	return ret;
}

zrtos_error_t zrtos_vfs_module_uart__on_write(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *out
){
	zrtos_vfs_module_uart_args_t *mod = ZRTOS_CAST(
		 zrtos_vfs_module_uart_args_t *
		,zrtos_vfs_file__get_inode_data(
			thiz
		)
	);
	zrtos_error_t ret = zrtos_vfs_module_uart_args__get_error(mod);
	if(zrtos_error__is_success(ret)){
		ret = zrtos_cbuffer__put_ex(
			&mod->cbuffer_out
			,1
			,out
			,buf
			,len
		);
	}
	return ret;
}

zrtos_error_t zrtos_vfs_module_uart__on_can_read(
	 zrtos_vfs_file_t *thiz
){
	zrtos_vfs_module_uart_args_t *mod = ZRTOS_CAST(
		 zrtos_vfs_module_uart_args_t *
		,zrtos_vfs_file__get_inode_data(
			thiz
		)
	);
	return zrtos_cbuffer__can_read(&mod->cbuffer_in);
}

zrtos_error_t zrtos_vfs_module_uart__on_can_write(
	 zrtos_vfs_file_t *thiz
){
	zrtos_vfs_module_uart_args_t *mod = ZRTOS_CAST(
		 zrtos_vfs_module_uart_args_t *
		,zrtos_vfs_file__get_inode_data(
			thiz
		)
	);
	return zrtos_cbuffer__can_write(&mod->cbuffer_out);
}
/*
ZRTOS_VFS_PLUGIN__INIT(uart,
	ZRTOS_VFS_PLUGIN__ON_READ(zrtos_vfs_module_uart__on_read)
	ZRTOS_VFS_PLUGIN__ON_WRITE(zrtos_vfs_module_uart__on_write)
	ZRTOS_VFS_PLUGIN__ON_CAN_READ(zrtos_vfs_module_uart__on_can_read)
	ZRTOS_VFS_PLUGIN__ON_CAN_WRITE(zrtos_vfs_module_uart__on_can_write)
);
*/

#ifdef __cplusplus
}
#endif
#endif
