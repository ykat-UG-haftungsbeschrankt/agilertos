/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_AVR_UART_UART1_H
#define ZRTOS_VFS_MODULE_AVR_UART_UART1_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/vfs/module/uart.h>
#include <zrtos/vfs/module/avr/uart.h>

zrtos_vfs_module_uart_args_t *zrtos_vfs_module_avr_uart1;

bool zrtos_vfs_module_avr_uart1__init(uint16_t baudrate){
	/* Set baud rate */
	if (baudrate & 0x8000) {
		UART1_STATUS = (1<<U2X1);  //Enable 2x speed
		baudrate &= ~0x8000;
	}
	UBRR1H = (uint8_t) (baudrate>>8);
	UBRR1L = (uint8_t) baudrate;

	/* Enable USART receiver and transmitter and receive complete interrupt */
	UART1_CONTROL = _BV(RXCIE1)|(1<<RXEN1)|(1<<TXEN1);

	/* Set frame format: asynchronous, 8data, no parity, 1stop bit */
#ifdef URSEL1
	UCSR1C = (1<<URSEL1)|(3<<UCSZ10);
#else
	UCSR1C = (3<<UCSZ10);
#endif

	return zrtos_cbuffer__init(&zrtos_cbuffer1);
}

ISR(UART1_RECEIVE_INTERRUPT){
	zrtos_vfs_module_uart__set_error(
		 zrtos_vfs_module_avr_uart1
		,( 
			(UART1_STATUS & (_BV(FE1)|_BV(DOR1)|_BV(UPE1))) > 0
			? zrtos_cbuffer__put(
				zrtos_vfs_module_uart_args__get_cbuffer(zrtos_vfs_module_avr_uart1)
				,(UART1_DATA
			)
			: EIO
		)
	);
}

ISR(UART1_TRANSMIT_INTERRUPT){
	uint8_t tmp;
	if(!zrtos_cbuffer__is_empty(zrtos_cbuffer1)){
		zrtos_cbuffer__get(&zrtos_cbuffer1,&tmp);
		UART1_DATA = tmp;
	}else{
		UART1_CONTROL &= ~_BV(UART1_UDRIE);
	}
}

zrtos_error_t zrtos_vfs_module_avr_uart1__on_write(
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
	if(EXIT_SUCCESS == ret){
		UART1_CONTROL |= _BV(UART1_UDRIE);
	}
	return ret;
}

ZRTOS_VFS_PLUGIN__INIT(avr_uart1,ZRTOS_VFS_PLUGIN_TYPE__FILE,
	ZRTOS_VFS_PLUGIN__ON_MOUNT(zrtos_vfs_module_avr_uart1__on_mount)
	ZRTOS_VFS_PLUGIN__ON_UMOUNT(zrtos_vfs_module_avr_uart1__on_umount)
	ZRTOS_VFS_PLUGIN__ON_READ(zrtos_vfs_module_uart__on_read)
	ZRTOS_VFS_PLUGIN__ON_WRITE(zrtos_vfs_module_avr_uart1__on_write)
);


#ifdef __cplusplus
}
#endif
#endif