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


#include <avr/pgmspace.h >

#include <zrtos/error.h>
#include <zrtos/types.h>
#include <zrtos/vfs_plugin.h>


ISR(UART0_RECEIVE_INTERRUPT)
/*************************************************************************
Function: UART Receive Complete interrupt
Purpose:  called when the UART has received a character
**************************************************************************/
{
    uint16_t tmphead;
    uint8_t data;
    uint8_t usr;
    uint8_t lastRxError;

    /* read UART status register and UART data register */
#if defined(AVR1_USART0)
    usr  = USART0_RXDATAH;
    data = USART0.RXDATAL;
#else
    usr  = UART0_STATUS;
    data = UART0_DATA;
#endif

    /* */
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

    /* calculate buffer index */
    tmphead = (UART_RxHead + 1) & UART_RX0_BUFFER_MASK;

    if (tmphead == UART_RxTail) {
        /* error: receive buffer overflow */
        lastRxError = UART_BUFFER_OVERFLOW >> 8;
    } else {
        /* store new index */
        UART_RxHead = tmphead;
        /* store received data in buffer */
        UART_RxBuf[tmphead] = data;
    }
    UART_LastRxError = lastRxError;
}


ISR(UART0_TRANSMIT_INTERRUPT)
/*************************************************************************
Function: UART Data Register Empty interrupt
Purpose:  called when the UART is ready to transmit the next byte
**************************************************************************/
{
    uint16_t tmptail;

    if (UART_TxHead != UART_TxTail) {
        /* calculate and store new buffer index */
        tmptail = (UART_TxTail + 1) & UART_TX0_BUFFER_MASK;
        UART_TxTail = tmptail;
        /* get one byte from buffer and write it to UART */
#if defined(AVR1_USART0)
        USART0_TXDATAL = UART_TxBuf[tmptail];  /* start transmission */
#else
        UART0_DATA = UART_TxBuf[tmptail];  /* start transmission */
#endif
    } else {
        /* tx buffer empty, disable UDRE interrupt */
#if defined(AVR1_USART0)
        USART0_CTRLA &= ~USART_DREIE_bm;
#else
        UART0_CONTROL &= ~_BV(UART0_UDRIE);
#endif
    }
}


#ifdef __cplusplus
}
#endif
#endif
