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


#include <zrtos/cbuffer.h>

#include "uart.h"

zrtos_cbuffer_t zrtos_cbuffer1;

zrtos_error_t uart1_init(uint16_t baudrate){
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
	uint16_t tmphead;
	uint8_t data;
	uint8_t usr;
	uint8_t lastRxError;

	usr  = UART1_STATUS;
	lastRxError = (usr & (_BV(FE1)|_BV(DOR1)));

	zrtos_cbuffer__put(&zrtos_cbuffer1,UART1_DATA);
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


#ifdef __cplusplus
}
#endif
#endif