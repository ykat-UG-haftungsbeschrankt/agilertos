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

#include <zrtos/vfs/module/uart/uart.h>
#include <zrtos/vfs/module/avr/uart/uart.h>

zrtos_vfs_module_uart_inode_t *zrtos_vfs_module_avr_uart1;

ISR(UART3_RECEIVE_INTERRUPT){
	zrtos_vfs_module_avr_uart__on_receive_interrupt(
		 zrtos_vfs_module_avr_uart1
		,UART1_DATA
		,(
			  (UART1_STATUS & (_BV(FE1)|_BV(DOR1)|_BV(UPE1))) == 0
			? ZRTOS_ERROR__SUCCESS
			: ZRTOS_ERROR__IO
		)
	);
}

ISR(UART3_TRANSMIT_INTERRUPT,ISR_NOBLOCK){
	uint8_t tmp;
	if(zrtos_vfs_module_avr_uart__on_transmit_interrupt(
		 zrtos_vfs_module_avr_uart1
		,&tmp
	)){
		UART1_DATA = tmp;
	}else{
		UART1_CONTROL &= ~_BV(UART1_UDRIE);
	}
}

zrtos_error_t zrtos_vfs_module_avr_uart1__on_mount(zrtos_vfs_dentry_t *thiz){
	uint16_t baudrate;
	zrtos_vfs_module_avr_uart1 = ZRTOS_CAST(
		 zrtos_vfs_module_uart_inode_t*
		,zrtos_vfs_dentry__get_inode_data(
			thiz
		)
	);

	baudrate = zrtos_vfs_module_avr_uart__baud_select(
		 zrtos_vfs_module_avr_uart1->baudrate
	);

	//Set baud rate
	if(ZRTOS_VFS_MODULE_AVR_UART__IS_DOUBLE_SPEED(baudrate)){
		UART1_STATUS = _BV(U2X1);  //Enable 2x speed
		baudrate &= ~0x8000;
	}else{
		UART1_STATUS = 0;
		//UART1_STATUS &= ~_BV(U2X1);
	}
	UBRR1H = (uint8_t) (baudrate>>8);
	UBRR1L = (uint8_t) baudrate;

	/* Enable USART receiver and transmitter and receive complete interrupt */
	UART1_CONTROL = _BV(RXCIE1)|_BV(RXEN1)|_BV(TXEN1);
	//UART1_CONTROL = _BV(RXCIE1)|_BV(TXEN1);

	/* Set frame format: asynchronous, 8data, no parity, 1stop bit */
#ifdef URSEL1
	UCSR1C = _BV(URSEL1)|_BV(UCSZ11)|_BV(UCSZ10);
#else
	UCSR1C = _BV(UCSZ11)|_BV(UCSZ10);
#endif

	return ZRTOS_ERROR__SUCCESS;
}

zrtos_error_t zrtos_vfs_module_avr_uart1__on_umount(zrtos_vfs_dentry_t *thiz){
	UART1_CONTROL &= ~_BV(UART1_UDRIE);
	return ZRTOS_ERROR__SUCCESS;
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
	if(zrtos_error__is_success(ret)){
		UART1_CONTROL |= _BV(UART1_UDRIE);
	}
	return ret;
}

ZRTOS_VFS_PLUGIN__INIT(avr_uart1,
	ZRTOS_VFS_PLUGIN__0_ON_OPEN_DEFAULT()
	ZRTOS_VFS_PLUGIN__1_ON_CLOSE_DEFAULT()
	ZRTOS_VFS_PLUGIN__2_ON_MOUNT(zrtos_vfs_module_avr_uart1__on_mount)
	ZRTOS_VFS_PLUGIN__3_ON_UMOUNT(zrtos_vfs_module_avr_uart1__on_umount)
	ZRTOS_VFS_PLUGIN__4_ON_READ(zrtos_vfs_module_uart__on_read)
	ZRTOS_VFS_PLUGIN__5_ON_WRITE(zrtos_vfs_module_avr_uart1__on_write)
	ZRTOS_VFS_PLUGIN__6_ON_CAN_READ(zrtos_vfs_module_uart__on_can_read)
	ZRTOS_VFS_PLUGIN__7_ON_CAN_WRITE(zrtos_vfs_module_uart__on_can_write)
	ZRTOS_VFS_PLUGIN__8_ON_SEEK_DEFAULT()
	ZRTOS_VFS_PLUGIN__9_ON_IOCTL(zrtos_vfs_module_uart__on_ioctl)
);

#ifdef __cplusplus
}
#endif
#endif