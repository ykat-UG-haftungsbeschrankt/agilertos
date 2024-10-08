/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_MODBUS_RTU_H
#define ZRTOS_VFS_MODULE_MODBUS_RTU_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/vfs_plugin.h>
#include <zrtos/cbuffer.h>
#include <zrtos/msg_queue.h>
#include <zrtos/error_count.h>

#include <zrtos/vfs/module/uart/uart.h>


#ifndef ZRTOS_VFS_MODULE_MODBUS_RTU__CFG_RESPONSE_TIMEOUT_US
# define ZRTOS_VFS_MODULE_MODBUS_RTU__CFG_RESPONSE_TIMEOUT_US 1000000
#endif

typedef enum{
	 ZRTOS_VFS_MODULE_MODBUS_RTU_IOCTL__GET_RX_ERROR_COUNT
	,ZRTOS_VFS_MODULE_MODBUS_RTU_IOCTL__GET_TX_ERROR_COUNT
}zrtos_vfs_module_modbus_rtu_ioctl_t;

typedef struct _zrtos_vfs_module_modbus_rtu_inode_t{
	zrtos_msg_queue_t                       msg_queue_in;
	zrtos_msg_queue_t                       msg_queue_out;
	zrtos_error_count_t                     rx_error_count;
	zrtos_error_count_t                     tx_error_count;
	zrtos_vfs_module_uart_inode_t           *uart;
	zrtos_vfs_fd_t                          timeout_fd;
	zrtos_vfs_module_timeout_microseconds_t timeout_frame_us;
	zrtos_vfs_module_timeout_microseconds_t timeout_response_us;
}zrtos_vfs_module_modbus_rtu_inode_t;


static void zrtos_vfs_module_modbus_rtu__crc(void *callback_args,uint8_t ch){
	uint16_t *crc_ptr = ZRTOS_CAST(uint16_t*,callback_args);
	uint16_t crc = *crc_ptr;

	crc ^= (uint16_t)ch;

	for(size_t i = 8; i--;){
		bool tmp = (crc & 0x0001) != 0;
		crc >>= 1;
		if(tmp){
			crc ^= 0xA001;
		}
	}

	*crc_ptr = crc;
}

static uint16_t zrtos_vfs_module_modbus_rtu__crc_str(uint8_t *data,size_t len){
	uint16_t crc = 0xffff;
	while(len--){
		zrtos_vfs_module_modbus_rtu__crc(&crc,*data++);
	}
	return crc;
}

zrtos_error_t zrtos_vfs_module_modbus_rtu__cmp_crc(
	 uint16_t crc
	,uint16_t crc_msg
){
	return crc == crc_msg
	     ? ZRTOS_ERROR__SUCCESS
	     : ZRTOS_ERROR__IO
	;
}

void zrtos_vfs_module_modbus_rtu__on_recv_timeout(
	 void *thiz
){
	zrtos_vfs_module_modbus_rtu_inode_t *mod = ZRTOS_CAST(
		 zrtos_vfs_module_modbus_rtu_inode_t*
		,zrtos_vfs_file__get_inode_data(
			thiz
		)
	);
	zrtos_vfs_module_uart_inode_t *uart = mod->uart;
	zrtos_cbuffer_t *cbuffer = zrtos_vfs_module_uart_inode__get_cbuffer_in(uart);
	size_t cbuffer_length = zrtos_cbuffer__get_length(cbuffer);

	if(cbuffer_length > 0){
		if(cbuffer_length >= 4){
			uint16_t crc = 0xffff;
			uint16_t crc_msg;
			zrtos_error_t ret;
			zrtos_msg_queue_write_transaction_t txn;

			zrtos_msg_queue__start_write_transaction(&mod->msg_queue_in,&txn);

			zrtos_cbuffer__hash(
				cbuffer
				,cbuffer_length-2
				,zrtos_vfs_module_modbus_rtu__crc
				,&crc
			);

			if(zrtos_error__is_success((ret = zrtos_msg_queue__put_length(
				&mod->msg_queue_in
				,cbuffer_length-2
			)))
			&& zrtos_error__is_success((ret = zrtos_msg_queue__put_cbuffer_data(
				&mod->msg_queue_in
				,cbuffer
				,cbuffer_length-2
			)))
			&& zrtos_error__is_success((ret = zrtos_cbuffer__get_ex(
				cbuffer
				,crc_msg
				,2
				,&outlen
			)))
			&& zrtos_error__is_success((ret = zrtos_vfs_module_modbus_rtu__cmp_crc(
				crc
				,crc_msg
			)))
			){
				break;
			}else{
				zrtos_msg_queue__rollback_write_transaction(
					&mod->msg_queue_in
					,&txn
				);
			}
		}else{
			ret = ZRTOS_ERROR__IO;
		}

		zrtos_error_count__add(&mod->rx_error_count,ret);
	}
}

zrtos_error_t zrtos_vfs_module_modbus_rtu__on_send(
	void *callback_data
){
	zrtos_error_t ret = ZRTOS_ERROR__SUCCESS;
	zrtos_vfs_module_modbus_rtu_inode_t *thiz = ZRTOS_CAST(
		 zrtos_vfs_module_modbus_rtu_inode_t*
		,callback_data
	);
	size_t            outlen;

	if(zrtos_cbuffer__is_empty(thiz->uart->cbuffer_out)
	&& !zrtos_msg_queue__is_empty(&thiz->msg_queue_out)){
		zrtos_arch__delay_microseconds(thiz->timeout_frame_us);
		ret = zrtos_msg_queue__pipe_next_message_to_cbuffer(
			 &thiz->msg_queue_out
			,thiz->uart->cbuffer_out
			,ZRTOS_TYPES__SIZE_MAX
			,&outlen
		);
		zrtos_error_count__add(&mod->tx_error_count,ret);
	}

	return ret;
}

zrtos_error_t zrtos_vfs_module_modbus_rtu__on_recv(
	void *callback_data
){
	zrtos_error_t ret;
	zrtos_vfs_module_modbus_rtu_inode_t *thiz = ZRTOS_CAST(
		 zrtos_vfs_module_modbus_rtu_inode_t*
		,callback_data
	);

	ret = zrtos_vfs_fd__ioctl(
		 thiz->timeout_fd
		,(char*)""
		,ZRTOS_VFS_MODULE_TIMEOUT_IOCTL__RESET
	);

	return ret;
}

bool zrtos_vfs_module_modbus_rtu_inode__init(
	 zrtos_vfs_module_modbus_rtu_inode_t *thiz
	,zrtos_vfs_module_uart_inode_t *uart
	,char *timeout_path
){
	zrtos_error_t ret;
	zrtos_vfs_module_timeout_microseconds_t char_transmission_us = zrtos_vfs_module_uart__get_char_transmission_time(uart);

	thiz->uart = uart;
	thiz->uart->on_send = zrtos_vfs_module_modbus_rtu__on_send;
	thiz->uart->on_recv = zrtos_vfs_module_modbus_rtu__on_recv;
	thiz->uart->callback_data = thiz;
	thiz->timeout_response_us = ZRTOS_VFS_MODULE_MODBUS_RTU__CFG_RESPONSE_TIMEOUT_US;
	thiz->timeout_frame_us = ZRTOS_TYPES__MIN(
		 1750
		,char_transmission_us*3+char_transmission_us/2
	);

	ret = zrtos_vfs_fd__open(timeout_path,&thiz->timeout_fd,0);
	if(zrtos_error__is_success(ret)){
		ret = zrtos_vfs_fd__ioctl(
			 thiz->timeout_fd
			,(char*)""
			,ZRTOS_VFS_MODULE_TIMEOUT_IOCTL__SET_CALLBACK
			,zrtos_vfs_module_modbus_rtu__on_recv_timeout
			,thiz
		);
		if(zrtos_error__is_success(ret)){
			ret = zrtos_vfs_fd__ioctl(
				 thiz->timeout_fd
				,(char*)""
				,ZRTOS_VFS_MODULE_TIMEOUT_IOCTL__START
				,zrtos_vfs_module_modbus_rtu__on_recv_timeout
				,thiz
			);
			if(zrtos_error__is_success(ret)){
				if(zrtos_error_count__init(&thiz->rx_error_count)){
					if(zrtos_error_count__init(&thiz->tx_error_count)){
						if(zrtos_msg_queue__init(&thiz->msg_queue_in)){
							if(zrtos_msg_queue__init(&thiz->msg_queue_out)){
								return true;
							}
							zrtos_msg_queue__deinit(&thiz->msg_queue_in);
						}
						zrtos_error_count__deinit(&thiz->tx_error_count);
					}
					zrtos_error_count__deinit(&thiz->rx_error_count);
				}
				zrtos_vfs_fd__close(thiz->timeout_fd);
			}
		}
	}
	
	return false;
}

zrtos_msg_queue_t *zrtos_vfs_module_modbus_rtu_inode__get_msg_queue_in(
	zrtos_vfs_module_modbus_rtu_inode_t *thiz
){
	return &thiz->msg_queue_in;
}

zrtos_msg_queue_t *zrtos_vfs_module_modbus_rtu_inode__get_msg_queue_out(
	zrtos_vfs_module_modbus_rtu_inode_t *thiz
){
	return &thiz->msg_queue_out;
}

zrtos_error_t zrtos_vfs_module_modbus_rtu__on_read(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *out
){
	zrtos_error_t ret;
	zrtos_vfs_module_modbus_rtu_inode_t *mod = ZRTOS_CAST(
		 zrtos_vfs_module_modbus_rtu_inode_t*
		,zrtos_vfs_file__get_inode_data(
			thiz
		)
	);

	ret = zrtos_msg_queue__get(
		 &mod->msg_queue_in
		,buf
		,len
		,out
	);

	return ret;
}

zrtos_error_t zrtos_vfs_module_modbus_rtu__on_write(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *out
){
	zrtos_error_t ret;
	zrtos_vfs_module_modbus_rtu_inode_t *mod = ZRTOS_CAST(
		 zrtos_vfs_module_modbus_rtu_inode_t*
		,zrtos_vfs_file__get_inode_data(
			thiz
		)
	);
	uint16_t crc = zrtos_vfs_module_modbus_rtu__crc_str(buf,len);
	zrtos_msg_queue_write_transaction_t txn;

	zrtos_msg_queue__start_write_transaction(&mod->msg_queue_out,&txn);

	if(zrtos_error__is_success((ret = zrtos_msg_queue__put_length(
			&mod->msg_queue_out
		,buf
		,len+2
		,out
	)))
	&& zrtos_error__is_success((ret = zrtos_msg_queue__put_data(
			&mod->msg_queue_out
		,buf
		,len
		,out
	)))
	&& zrtos_error__is_success((ret = zrtos_msg_queue__put_data(
			&mod->msg_queue_out
		,&crc
		,2
		,out
	)))
	&& zrtos_error__is_success((ret = zrtos_msg_queue__put_end(
			&mod->msg_queue_out
	)))
	){
		ret = rtos_vfs_module_modbus_rtu__on_send(mod);
	}else{
		zrtos_msg_queue__rollback_write_transaction(
			&mod->msg_queue_out
			,&txn
		);
	}

	return ret;
}

zrtos_error_t zrtos_vfs_module_modbus_rtu__on_can_read(
	 zrtos_vfs_file_t *thiz
	,char *path
){
	zrtos_vfs_module_modbus_rtu_inode_t *mod = ZRTOS_CAST(
		 zrtos_vfs_module_modbus_rtu_inode_t*
		,zrtos_vfs_file__get_inode_data(
			thiz
		)
	);

	return zrtos_msg_queue__is_empty(&mod->msg_queue_in)
	     ? ZRTOS_ERROR__AGAIN
	     : ZRTOS_ERROR__SUCCESS
	;
}

zrtos_error_t zrtos_vfs_module_modbus_rtu__on_can_write(
	 zrtos_vfs_file_t *thiz
	,char *path
){
	return ZRTOS_ERROR__SUCCESS;
}

zrtos_error_t zrtos_vfs_module_modbus_rtu__on_ioctl(
	 zrtos_vfs_file_t *thiz
	,char *path
	,int request
	,va_list args
){
	zrtos_error_t ret = ZRTOS_ERROR__SUCCESS;
	zrtos_vfs_module_modbus_rtu_inode_t *mod = ZRTOS_CAST(
		 zrtos_vfs_module_modbus_rtu_inode_t *
		,zrtos_vfs_file__get_inode_data(
			thiz
		)
	);

	switch(ZRTOS_CAST__REINTERPRET(
		 zrtos_vfs_module_modbus_rtu_ioctl_t
		,request
	)){
		case ZRTOS_VFS_MODULE_MODBUS_RTU_IOCTL__GET_RX_ERROR_COUNT:
			zrtos_error_count_t **ret = zrtos_va__arg(
				 args
				,zrtos_error_count_t**
			);
			*ret = &mod->rx_error_count;
		break;
		case ZRTOS_VFS_MODULE_MODBUS_RTU_IOCTL__GET_TX_ERROR_COUNT:
			zrtos_error_count_t **ret = zrtos_va__arg(
				 args
				,zrtos_error_count_t**
			);
			*ret = &mod->tx_error_count;
		break;
		default:
			ret = ZRTOS_ERROR__INVAL;
		break;
	}

	return ret;
}

ZRTOS_VFS_PLUGIN__INIT(modbus_rtu,
	ZRTOS_VFS_PLUGIN__0_ON_OPEN_DEFAULT()
	ZRTOS_VFS_PLUGIN__1_ON_CLOSE_DEFAULT()
	ZRTOS_VFS_PLUGIN__2_ON_MOUNT_DEFAULT()
	ZRTOS_VFS_PLUGIN__3_ON_UMOUNT_DEFAULT()
	ZRTOS_VFS_PLUGIN__4_ON_READ(zrtos_vfs_module_modbus_rtu__on_read)
	ZRTOS_VFS_PLUGIN__5_ON_WRITE(zrtos_vfs_module_modbus_rtu__on_write)
	ZRTOS_VFS_PLUGIN__6_ON_CAN_READ(zrtos_vfs_module_modbus_rtu__on_can_read)
	ZRTOS_VFS_PLUGIN__7_ON_CAN_WRITE(zrtos_vfs_module_modbus_rtu__on_can_write)
	ZRTOS_VFS_PLUGIN__8_ON_SEEK_DEFAULT()
	ZRTOS_VFS_PLUGIN__9_ON_IOCTL(zrtos_vfs_module_modbus_rtu__on_ioctl)
);

#ifdef __cplusplus
}
#endif
#endif
