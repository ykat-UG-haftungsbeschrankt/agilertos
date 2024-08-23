/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_AVR_UART_UART0_H
#define ZRTOS_VFS_MODULE_AVR_UART_UART0_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/vfs/module/uart/uart.h>
#include <zrtos/vfs/module/avr/uart/uart.h>

zrtos_vfs_module_uart_args_t *zrtos_vfs_module_avr_uart0;

ISR(UART0_RECEIVE_INTERRUPT){
	uint8_t data;
	uint8_t usr;
	uint8_t lastRxError;
	zrtos_error_t err = zrtos_vfs_module_uart_args__get_error(
		zrtos_vfs_module_avr_uart0
	);
	zrtos_cbuffer_t *buffer = zrtos_vfs_module_uart_args__get_cbuffer_in(
		zrtos_vfs_module_avr_uart0
	);

	//read UART status register and UART data register
#if defined(AVR1_USART0)
	usr  = USART0_RXDATAH;
	data = USART0.RXDATAL;
#else
	usr  = UART0_STATUS;
	data = UART0_DATA;
#endif

#if defined(AT90_UART)
	lastRxError = (usr & (_BV(FE)|_BV(DOR)));
#elif defined(ATMEGA_USART)
	lastRxError = (usr & (_BV(FE)|_BV(DOR)));
#elif defined(ATMEGA_USART0)
	lastRxError = (usr & (_BV(FE0)|_BV(DOR0)));
#elif defined(ATMEGA_UART)
	lastRxError = (usr & (_BV(FE)|_BV(DOR)));
#elif defined(AVR1_USART0)
	lastRxError = (usr & (USART_BUFOVF_bm | USART_FERR_bm | USART_PERR_bm));
#endif

	if(zrtos_error__is_success(err)){
		err = ( 
			lastRxError > 0
			? zrtos_cbuffer__put(
				 buffer
				,data
			)
			: EIO
		);

		zrtos_vfs_module_uart_args__set_error(
			 zrtos_vfs_module_avr_uart0
			,err
		);
	}
}

ISR(UART0_TRANSMIT_INTERRUPT){
	uint8_t tmp;
	zrtos_error_t err = zrtos_vfs_module_uart_args__get_error(
		zrtos_vfs_module_avr_uart0
	);
	zrtos_cbuffer_t *buffer = zrtos_vfs_module_uart_args__get_cbuffer_out(
		zrtos_vfs_module_avr_uart0
	);
	if(zrtos_error__is_success(err)
	&& zrtos_error__is_success(zrtos_cbuffer__get(buffer,&tmp))){
#if defined(AVR1_USART0)
		USART0_TXDATAL = tmp;
#else
		UART0_DATA = tmp;
#endif
	}else{
#if defined(AVR1_USART0)
		USART0_CTRLA &= ~USART_DREIE_bm;
#else
		UART0_CONTROL &= ~_BV(UART0_UDRIE);
#endif
	}
}

zrtos_error_t zrtos_vfs_module_avr_uart0__on_mount(zrtos_vfs_dentry_t *thiz){
	uint16_t baudrate;

	zrtos_vfs_module_avr_uart0 = ZRTOS_CAST(
		 zrtos_vfs_module_uart_args_t*
		,zrtos_vfs_dentry__get_inode_data(
			thiz
		)
	);

	baudrate = zrtos_vfs_module_avr_uart__baud_select(
		 zrtos_vfs_module_avr_uart0->baudrate
	);

#if defined(AT90_UART)
	/* set baud rate */
	UBRR = (uint8_t) baudrate;

	/* enable UART receiver and transmitter and receive complete interrupt */
	UART0_CONTROL = _BV(RXCIE)|_BV(RXEN)|_BV(TXEN);

#elif defined(ATMEGA_USART)
	/* Set baud rate */
	if (baudrate & 0x8000) {
		UART0_STATUS = (1<<U2X);  //Enable 2x speed
		baudrate &= ~0x8000;
	}else{
		UART0_STATUS &= ~(1<<U2X);
	}
	UBRRH = (uint8_t) (baudrate>>8);
	UBRRL = (uint8_t) baudrate;

	/* Enable USART receiver and transmitter and receive complete interrupt */
	UART0_CONTROL = _BV(RXCIE)|(1<<RXEN)|(1<<TXEN);

	/* Set frame format: asynchronous, 8data, no parity, 1stop bit */
#ifdef URSEL
	UCSRC = (1<<URSEL)|(3<<UCSZ0);
#else
	UCSRC = (3<<UCSZ0);
#endif

#elif defined(ATMEGA_USART0)
	/* Set baud rate */
	if (baudrate & 0x8000) {
		UART0_STATUS = (1<<U2X0);  //Enable 2x speed
		baudrate &= ~0x8000;
	}else{
		UART0_STATUS &= ~(1<<U2X0);
	}
	UBRR0H = (uint8_t)(baudrate>>8);
	UBRR0L = (uint8_t) baudrate;

	/* Enable USART receiver and transmitter and receive complete interrupt */
	UART0_CONTROL = _BV(RXCIE0)|(1<<RXEN0)|(1<<TXEN0);

	/* Set frame format: asynchronous, 8data, no parity, 1stop bit */
#ifdef URSEL0
	UCSR0C = (1<<URSEL0)|(3<<UCSZ00);
#else
	UCSR0C = (3<<UCSZ00);
#endif

#elif defined(ATMEGA_UART)
	/* set baud rate */
	if (baudrate & 0x8000) {
		UART0_STATUS = (1<<U2X);  //Enable 2x speed
		baudrate &= ~0x8000;
	}else{
		UART0_STATUS &= ~(1<<U2X);
	}
	UBRRHI = (uint8_t) (baudrate>>8);
	UBRR   = (uint8_t) baudrate;

	/* Enable UART receiver and transmitter and receive complete interrupt */
	UART0_CONTROL = _BV(RXCIE)|(1<<RXEN)|(1<<TXEN);

#elif defined(AVR1_USART0)
	// set the baud rate
	USART0.BAUD = USART0_BAUD_RATE(baudrate);

	USART0.CTRLA = USART_RXCIE_bm;
	USART0.CTRLB = USART_TXEN_bm | USART_RXEN_bm | USART_RXMODE_NORMAL_gc;
	// Default configuration of CTRLC is 8N1 in asynchronous mode
#endif

	return ESUCCESS;
}

zrtos_error_t zrtos_vfs_module_avr_uart0__on_umount(zrtos_vfs_dentry_t *thiz){
#if defined(AVR1_USART0)
	USART0_CTRLA &= ~USART_DREIE_bm;
#else
	UART0_CONTROL &= ~_BV(UART0_UDRIE);
#endif
	return ESUCCESS;
}

zrtos_error_t zrtos_vfs_module_avr_uart0__on_write(
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
#if defined(AVR1_USART0)
		USART0_CTRLA |= USART_DREIE_bm;
#else
		UART0_CONTROL |= _BV(UART0_UDRIE);
#endif
	}
	return ret;
}

ZRTOS_VFS_PLUGIN__INIT(avr_uart0,
	ZRTOS_VFS_PLUGIN__0_ON_OPEN_DEFAULT()
	ZRTOS_VFS_PLUGIN__1_ON_CLOSE_DEFAULT()
	ZRTOS_VFS_PLUGIN__2_ON_MOUNT(zrtos_vfs_module_avr_uart0__on_mount)
	ZRTOS_VFS_PLUGIN__3_ON_UMOUNT(zrtos_vfs_module_avr_uart0__on_umount)
	ZRTOS_VFS_PLUGIN__4_ON_READ(zrtos_vfs_module_uart__on_read)
	ZRTOS_VFS_PLUGIN__5_ON_WRITE(zrtos_vfs_module_avr_uart0__on_write)
	ZRTOS_VFS_PLUGIN__6_ON_CAN_READ(zrtos_vfs_module_uart__on_can_read)
	ZRTOS_VFS_PLUGIN__7_ON_CAN_WRITE(zrtos_vfs_module_uart__on_can_write)
	ZRTOS_VFS_PLUGIN__8_ON_SEEK_DEFAULT()
	ZRTOS_VFS_PLUGIN__9_ON_IOCTL_DEFAULT()
);

#ifdef __cplusplus
}
#endif
#endif
