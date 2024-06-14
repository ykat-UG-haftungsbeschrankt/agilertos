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


#include <zrtos/cbuffer.h>

#include "uart.h"

zrtos_cbuffer_t zrtos_cbuffer3;

zrtos_error_t uart3_init(uint16_t baudrate){
	/* Set baud rate */
	if (baudrate & 0x8000) {
		UART3_STATUS = (1<<U2X3);  //Enable 2x speed
		baudrate &= ~0x8000;
	}
	UBRR3H = (uint8_t) (baudrate>>8);
	UBRR3L = (uint8_t) baudrate;

	/* Enable USART receiver and transmitter and receive complete interrupt */
	UART3_CONTROL = _BV(RXCIE3)|(1<<RXEN3)|(1<<TXEN3);

	/* Set frame format: asynchronous, 8data, no parity, 1stop bit */
#ifdef URSEL3
	UCSR3C = (1<<URSEL3)|(3<<UCSZ30);
#else
	UCSR3C = (3<<UCSZ30);
#endif

	return zrtos_cbuffer__init(&zrtos_cbuffer3);
}

ISR(UART3_RECEIVE_INTERRUPT){
	uint16_t tmphead;
	uint8_t data;
	uint8_t usr;
	uint8_t lastRxError;

	usr  = UART3_STATUS;
	lastRxError = (usr & (_BV(FE3)|_BV(DOR3)));

	zrtos_cbuffer__put(&zrtos_cbuffer3,UART3_DATA);
}


ISR(UART3_TRANSMIT_INTERRUPT){
	uint8_t tmp;
	if(!zrtos_cbuffer__is_empty(zrtos_cbuffer3)){
		zrtos_cbuffer__get(&zrtos_cbuffer3,&tmp);
		UART3_DATA = tmp;
	}else{
		UART3_CONTROL &= ~_BV(UART3_UDRIE);
	}
}


#ifdef __cplusplus
}
#endif
#endif