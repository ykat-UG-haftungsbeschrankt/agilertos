/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_AVR_UART_UART2_H
#define ZRTOS_VFS_MODULE_AVR_UART_UART2_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/cbuffer.h>

#include "uart.h"

zrtos_cbuffer_t zrtos_cbuffer2;

zrtos_error_t uart2_init(uint16_t baudrate){
	/* Set baud rate */
	if (baudrate & 0x8000) {
		UART2_STATUS = (1<<U2X2);  //Enable 2x speed
		baudrate &= ~0x8000;
	}
	UBRR2H = (uint8_t) (baudrate>>8);
	UBRR2L = (uint8_t) baudrate;

	/* Enable USART receiver and transmitter and receive complete interrupt */
	UART2_CONTROL = _BV(RXCIE2)|(1<<RXEN2)|(1<<TXEN2);

	/* Set frame format: asynchronous, 8data, no parity, 1stop bit */
#ifdef URSEL2
	UCSR2C = (1<<URSEL2)|(3<<UCSZ20);
#else
	UCSR2C = (3<<UCSZ20);
#endif

	return zrtos_cbuffer__init(&zrtos_cbuffer2);
}

ISR(UART2_RECEIVE_INTERRUPT){
	uint16_t tmphead;
	uint8_t data;
	uint8_t usr;
	uint8_t lastRxError;

	usr  = UART2_STATUS;
	lastRxError = (usr & (_BV(FE2)|_BV(DOR2)));

	zrtos_cbuffer__put(&zrtos_cbuffer2,UART2_DATA);
}


ISR(UART2_TRANSMIT_INTERRUPT){
	uint8_t tmp;
	if(!zrtos_cbuffer__is_empty(zrtos_cbuffer2)){
		zrtos_cbuffer__get(&zrtos_cbuffer2,&tmp);
		UART2_DATA = tmp;
	}else{
		UART2_CONTROL &= ~_BV(UART2_UDRIE);
	}
}


#ifdef __cplusplus
}
#endif
#endif