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

zrtos_vfs_module_uart_inode_t *zrtos_vfs_module_avr_uart0;

ISR(UART0_RECEIVE_INTERRUPT){
#if defined(AVR1_USART0)
# define ZRTOS_VFS_MODULE_AVR_UART_UART0__STATUS USART0_RXDATAH
# define ZRTOS_VFS_MODULE_AVR_UART_UART0__DATA   USART0.RXDATAL
#else
# define ZRTOS_VFS_MODULE_AVR_UART_UART0__STATUS UART0_STATUS
# define ZRTOS_VFS_MODULE_AVR_UART_UART0__DATA   UART0_DATA
#endif

#if defined(AT90_UART)
# define ZRTOS_VFS_MODULE_AVR_UART_UART0__ERROR\
	(ZRTOS_VFS_MODULE_AVR_UART_UART0__STATUS & (_BV(FE)|_BV(DOR)|_BV(UPE)))
#elif defined(ATMEGA_USART)
# define ZRTOS_VFS_MODULE_AVR_UART_UART0__ERROR\
	(ZRTOS_VFS_MODULE_AVR_UART_UART0__STATUS & (_BV(FE)|_BV(DOR)|_BV(UPE)))
#elif defined(ATMEGA_USART0)
# define ZRTOS_VFS_MODULE_AVR_UART_UART0__ERROR\
	(ZRTOS_VFS_MODULE_AVR_UART_UART0__STATUS & (_BV(FE0)|_BV(DOR0)|_BV(UPE0)))
#elif defined(ATMEGA_UART)
# define ZRTOS_VFS_MODULE_AVR_UART_UART0__ERROR\
	(ZRTOS_VFS_MODULE_AVR_UART_UART0__STATUS & (_BV(FE)|_BV(DOR)|_BV(UPE)))
#elif defined(AVR1_USART0)
# define ZRTOS_VFS_MODULE_AVR_UART_UART0__ERROR\
	(ZRTOS_VFS_MODULE_AVR_UART_UART0__STATUS & (USART_BUFOVF_bm | USART_FERR_bm | USART_PERR_bm))
#endif

	zrtos_vfs_module_avr_uart__on_receive_interrupt(
		 zrtos_vfs_module_avr_uart0
		,ZRTOS_VFS_MODULE_AVR_UART_UART0__DATA
		,(
			  ZRTOS_VFS_MODULE_AVR_UART_UART0__ERROR == 0
			? ZRTOS_ERROR__SUCCESS
			: ZRTOS_ERROR__IO
		)
	);

#undef ZRTOS_VFS_MODULE_AVR_UART_UART0__STATUS
#undef ZRTOS_VFS_MODULE_AVR_UART_UART0__DATA
#undef ZRTOS_VFS_MODULE_AVR_UART_UART0__ERROR
}

ISR(UART0_TRANSMIT_INTERRUPT,ISR_NOBLOCK){
	uint8_t tmp;
	if(zrtos_vfs_module_avr_uart__on_transmit_interrupt(
		 zrtos_vfs_module_avr_uart0
		,&tmp
	)){
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
		 zrtos_vfs_module_uart_inode_t*
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
	if(ZRTOS_VFS_MODULE_AVR_UART__IS_DOUBLE_SPEED(baudrate)){
		UART0_STATUS = _BV(U2X);  //Enable 2x speed
		baudrate &= ~0x8000;
	}else{
		UART0_STATUS &= ~_BV(U2X);
	}
	UBRRH = (uint8_t) (baudrate>>8);
	UBRRL = (uint8_t) baudrate;

	/* Enable USART receiver and transmitter and receive complete interrupt */
	UART0_CONTROL = _BV(RXCIE)|_BV(RXEN)|_BV(TXEN);

	/* Set frame format: asynchronous, 8data, no parity, 1stop bit */
#ifdef URSEL
	UCSRC = _BV(URSEL)|_BV(UCSZ1)|_BV(UCSZ0);
#else
	UCSRC = _BV(UCSZ1)|_BV(UCSZ0);
#endif

#elif defined(ATMEGA_USART0)
	/* Set baud rate */
	if(ZRTOS_VFS_MODULE_AVR_UART__IS_DOUBLE_SPEED(baudrate)){
		UART0_STATUS = _BV(U2X0);  //Enable 2x speed
		baudrate &= ~0x8000;
	}else{
		UART0_STATUS &= ~_BV(U2X0);
	}
	UBRR0H = (uint8_t)(baudrate>>8);
	UBRR0L = (uint8_t) baudrate;

	/* Enable USART receiver and transmitter and receive complete interrupt */
	UART0_CONTROL = _BV(RXCIE0)|_BV(RXEN0)|_BV(TXEN0);

	/* Set frame format: asynchronous, 8data, no parity, 1stop bit */
#ifdef URSEL0
	UCSR0C = _BV(URSEL0)|_BV(UCSZ01)|_BV(UCSZ00);
#else
	UCSR0C = _BV(UCSZ01)|_BV(UCSZ00);
#endif

#elif defined(ATMEGA_UART)
	/* set baud rate */
	if(ZRTOS_VFS_MODULE_AVR_UART__IS_DOUBLE_SPEED(baudrate)){
		UART0_STATUS = _BV(U2X);  //Enable 2x speed
		baudrate &= ~0x8000;
	}else{
		UART0_STATUS &= ~_BV(U2X);
	}
	UBRRHI = (uint8_t) (baudrate>>8);
	UBRR   = (uint8_t) baudrate;

	/* Enable UART receiver and transmitter and receive complete interrupt */
	UART0_CONTROL = _BV(RXCIE)|_BV(RXEN)|_BV(TXEN);

#elif defined(AVR1_USART0)
	// set the baud rate
	USART0.BAUD = USART0_BAUD_RATE(baudrate);

	USART0.CTRLA = USART_RXCIE_bm;
	USART0.CTRLB = USART_TXEN_bm | USART_RXEN_bm | USART_RXMODE_NORMAL_gc;
	// Default configuration of CTRLC is 8N1 in asynchronous mode
#endif

	return ZRTOS_ERROR__SUCCESS;
}

zrtos_error_t zrtos_vfs_module_avr_uart0__on_umount(zrtos_vfs_dentry_t *thiz){
#if defined(AVR1_USART0)
	USART0_CTRLA &= ~USART_DREIE_bm;
#else
	UART0_CONTROL &= ~_BV(UART0_UDRIE);
#endif
	return ZRTOS_ERROR__SUCCESS;
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
	ZRTOS_VFS_PLUGIN__9_ON_IOCTL(zrtos_vfs_module_uart__on_ioctl)
);

#ifdef __cplusplus
}
#endif
#endif
