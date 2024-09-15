/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_AVR_UART_UART3_H
#define ZRTOS_VFS_MODULE_AVR_UART_UART3_H
#ifdef __cplusplus
extern "C" {
#endif

#include <zrtos/vfs/module/uart/uart.h>
#include <zrtos/vfs/module/avr/uart/uart.h>

zrtos_vfs_module_uart_inode_t *zrtos_vfs_module_avr_uart3;

ISR(UART3_RECEIVE_INTERRUPT){
	zrtos_error_t err = zrtos_vfs_module_uart_args__get_error(
		zrtos_vfs_module_avr_uart3
	);
	zrtos_cbuffer_t *buffer = zrtos_vfs_module_uart_args__get_cbuffer_in(
		zrtos_vfs_module_avr_uart3
	);
	if(zrtos_error__is_success(err)){
		err = (
			(UART3_STATUS & (_BV(FE3)|_BV(DOR3)|_BV(UPE3))) == 0
			? zrtos_cbuffer__put(
				 buffer
				,UART3_DATA
			)
			: ZRTOS_ERROR__IO
		);

		if(zrtos_error__is_success(err)){
			err = zrtos_vfs_module_avr_uart3->on_recv(
				 zrtos_vfs_module_avr_uart3
			);
		}

		zrtos_vfs_module_uart_args__set_error(
			 zrtos_vfs_module_avr_uart3
			,err
		);
	}
}

ISR(UART3_TRANSMIT_INTERRUPT){
	uint8_t tmp;
	zrtos_error_t err = zrtos_vfs_module_uart_args__get_error(
		zrtos_vfs_module_avr_uart3
	);
	zrtos_cbuffer_t *buffer = zrtos_vfs_module_uart_args__get_cbuffer_out(
		zrtos_vfs_module_avr_uart3
	);

	if(zrtos_error__is_success(err)
	&& zrtos_error__is_success((err = zrtos_vfs_module_avr_uart3->on_send(
		zrtos_vfs_module_avr_uart3
	)))
	&& zrtos_error__is_success(zrtos_cbuffer__get(buffer,&tmp))
	){
		UART3_DATA = tmp;
	}else{
		UART3_CONTROL &= ~_BV(UART3_UDRIE);
	}

	zrtos_vfs_module_uart_args__set_error(
		 zrtos_vfs_module_avr_uart3
		,err
	);
}

zrtos_error_t zrtos_vfs_module_avr_uart3__on_mount(zrtos_vfs_dentry_t *thiz){
	uint16_t baudrate;
	zrtos_vfs_module_avr_uart3 = ZRTOS_CAST__REINTERPRET(
		 zrtos_vfs_module_uart_inode_t*
		,zrtos_vfs_dentry__get_inode_data(
			thiz
		)
	);

	baudrate = zrtos_vfs_module_avr_uart__baud_select(
		 zrtos_vfs_module_avr_uart3->baudrate
	);

	//Set baud rate
	if(baudrate & 0x8000){
		UART3_STATUS = _BV(U2X3);  //Enable 2x speed
		baudrate &= ~0x8000;
	}else{
		UART3_STATUS = 0;
		//UART3_STATUS &= ~_BV(U2X3);
	}
	UBRR3H = (uint8_t) (baudrate>>8);
	UBRR3L = (uint8_t) baudrate;

	/* Enable USART receiver and transmitter and receive complete interrupt */
	UART3_CONTROL = _BV(RXCIE3)|_BV(RXEN3)|_BV(TXEN3);
	//UART3_CONTROL = _BV(RXCIE3)|_BV(TXEN3);

	/* Set frame format: asynchronous, 8data, no parity, 1stop bit */
#ifdef URSEL3
	UCSR3C = _BV(URSEL3)|_BV(UCSZ31)|_BV(UCSZ30);
#else
	UCSR3C = _BV(UCSZ31)|_BV(UCSZ30);
#endif

	return ZRTOS_ERROR__SUCCESS;
}

zrtos_error_t zrtos_vfs_module_avr_uart3__on_umount(zrtos_vfs_dentry_t *thiz){
	UART3_CONTROL &= ~_BV(UART3_UDRIE);
	return ZRTOS_ERROR__SUCCESS;
}

zrtos_error_t zrtos_vfs_module_avr_uart3__on_write(
	 zrtos_vfs_file_t *thiz
	,char *path
	,void *buf
	,size_t len
	,zrtos_vfs_offset_t offset
	,size_t *out
){
	zrtos_error_t ret = zrtos_vfs_module_uart__on_write(
		 thiz
		,path
		,buf
		,len
		,offset
		,out
	);
	if(zrtos_error__is_success(ret)){
		UART3_CONTROL |= _BV(UART3_UDRIE);
	}
	return ret;
}

ZRTOS_VFS_PLUGIN__INIT(avr_uart3,
	ZRTOS_VFS_PLUGIN__0_ON_OPEN_DEFAULT()
	ZRTOS_VFS_PLUGIN__1_ON_CLOSE_DEFAULT()
	ZRTOS_VFS_PLUGIN__2_ON_MOUNT(zrtos_vfs_module_avr_uart3__on_mount)
	ZRTOS_VFS_PLUGIN__3_ON_UMOUNT(zrtos_vfs_module_avr_uart3__on_umount)
	ZRTOS_VFS_PLUGIN__4_ON_READ(zrtos_vfs_module_uart__on_read)
	ZRTOS_VFS_PLUGIN__5_ON_WRITE(zrtos_vfs_module_avr_uart3__on_write)
	ZRTOS_VFS_PLUGIN__6_ON_CAN_READ(zrtos_vfs_module_uart__on_can_read)
	ZRTOS_VFS_PLUGIN__7_ON_CAN_WRITE(zrtos_vfs_module_uart__on_can_write)
	ZRTOS_VFS_PLUGIN__8_ON_SEEK_DEFAULT()
	ZRTOS_VFS_PLUGIN__9_ON_IOCTL_DEFAULT()
);

#ifdef __cplusplus
}
#endif
#endif