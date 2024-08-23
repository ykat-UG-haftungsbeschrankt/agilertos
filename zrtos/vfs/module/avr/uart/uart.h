/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_AVR_UART_H
#define ZRTOS_VFS_MODULE_AVR_UART_H
#ifdef __cplusplus
extern "C" {
#endif


#include <avr/io.h>
#include <avr/interrupt.h>


#if defined(__AVR_AT90S2313__) \
 || defined(__AVR_AT90S4414__) \
 || defined(__AVR_AT90S4434__) \
 || defined(__AVR_AT90S8515__) \
 || defined(__AVR_AT90S8535__) \
 || defined(__AVR_ATmega103__)
	/* old AVR classic or ATmega103 with one UART */
	#define AT90_UART
	#define UART0_RECEIVE_INTERRUPT   UART_RX_vect
	#define UART0_TRANSMIT_INTERRUPT  UART_UDRE_vect
	#define UART0_STATUS   USR
	#define UART0_CONTROL  UCR
	#define UART0_DATA     UDR
	#define UART0_UDRIE    UDRIE
#elif defined(__AVR_AT90S2333__) \
   || defined(__AVR_AT90S4433__)
	/* old AVR classic with one UART */
	#define AT90_UART
	#define UART0_RECEIVE_INTERRUPT   UART_RX_vect
	#define UART0_TRANSMIT_INTERRUPT  UART_UDRE_vect
	#define UART0_STATUS   UCSRA
	#define UART0_CONTROL  UCSRB
	#define UART0_DATA     UDR
	#define UART0_UDRIE    UDRIE
#elif defined(__AVR_ATmega8__) \
   || defined(__AVR_ATmega16__) \
   || defined(__AVR_ATmega32__) \
   || defined(__AVR_ATmega323__)
	/* ATmega with one USART */
	#define ATMEGA_USART
	#define UART0_RECEIVE_INTERRUPT   USART_RXC_vect
	#define UART0_TRANSMIT_INTERRUPT  USART_UDRE_vect
	#define UART0_STATUS   UCSRA
	#define UART0_CONTROL  UCSRB
	#define UART0_DATA     UDR
	#define UART0_UDRIE    UDRIE
#elif defined(__AVR_ATmega8U2__) \
   || defined(__AVR_ATmega16U2__) \
   || defined(__AVR_ATmega16U4__) \
   || defined(__AVR_ATmega32U2__) \
   || defined(__AVR_ATmega32U4__) \
   || defined(__AVR_ATmega32U6__)
	/* ATmega with one USART, but is called USART1 (untested) */
	#define ATMEGA_USART1
	#define UART1_RECEIVE_INTERRUPT   USART1_RX_vect
	#define UART1_TRANSMIT_INTERRUPT  USART1_UDRE_vect
	#define UART1_STATUS   UCSR1A
	#define UART1_CONTROL  UCSR1B
	#define UART1_DATA     UDR1
	#define UART1_UDRIE    UDRIE1
#elif defined(__AVR_ATmega8515__) \
   || defined(__AVR_ATmega8535__)
	/* ATmega with one USART */
	#define ATMEGA_USART
	#define UART0_RECEIVE_INTERRUPT   USART_RX_vect
	#define UART0_TRANSMIT_INTERRUPT  USART_UDRE_vect
	#define UART0_STATUS   UCSRA
	#define UART0_CONTROL  UCSRB
	#define UART0_DATA     UDR
	#define UART0_UDRIE    UDRIE
#elif defined(__AVR_ATmega163__)
	/* ATmega163 with one UART */
	#define ATMEGA_UART
	#define UART0_RECEIVE_INTERRUPT   UART_RX_vect
	#define UART0_TRANSMIT_INTERRUPT  UART_UDRE_vect
	#define UART0_STATUS   UCSRA
	#define UART0_CONTROL  UCSRB
	#define UART0_DATA     UDR
	#define UART0_UDRIE    UDRIE
#elif defined(__AVR_ATmega162__)
	/* ATmega with two USART */
	#define ATMEGA_USART0
	#define ATMEGA_USART1
	#define UART0_RECEIVE_INTERRUPT   USART0_RXC_vect
	#define UART1_RECEIVE_INTERRUPT   USART1_RXC_vect
	#define UART0_TRANSMIT_INTERRUPT  USART0_UDRE_vect
	#define UART1_TRANSMIT_INTERRUPT  USART1_UDRE_vect
	#define UART0_STATUS   UCSR0A
	#define UART0_CONTROL  UCSR0B
	#define UART0_DATA     UDR0
	#define UART0_UDRIE    UDRIE0
	#define UART1_STATUS   UCSR1A
	#define UART1_CONTROL  UCSR1B
	#define UART1_DATA     UDR1
	#define UART1_UDRIE    UDRIE1
#elif defined(__AVR_ATmega64__) \
   || defined(__AVR_ATmega128__)
	/* ATmega with two USART */
	#define ATMEGA_USART0
	#define ATMEGA_USART1
	#define UART0_RECEIVE_INTERRUPT   USART0_RX_vect
	#define UART1_RECEIVE_INTERRUPT   USART1_RX_vect
	#define UART0_TRANSMIT_INTERRUPT  USART0_UDRE_vect
	#define UART1_TRANSMIT_INTERRUPT  USART1_UDRE_vect
	#define UART0_STATUS   UCSR0A
	#define UART0_CONTROL  UCSR0B
	#define UART0_DATA     UDR0
	#define UART0_UDRIE    UDRIE0
	#define UART1_STATUS   UCSR1A
	#define UART1_CONTROL  UCSR1B
	#define UART1_DATA     UDR1
	#define UART1_UDRIE    UDRIE1
#elif defined(__AVR_ATmega161__)
	/* ATmega with UART */
	#error "AVR ATmega161 currently not supported by this libaray !"
#elif defined(__AVR_ATmega169__)
	/* ATmega with one USART */
	#define ATMEGA_USART
	#define UART0_RECEIVE_INTERRUPT   USART0_RX_vect
	#define UART0_TRANSMIT_INTERRUPT  USART0_UDRE_vect
	#define UART0_STATUS   UCSRA
	#define UART0_CONTROL  UCSRB
	#define UART0_DATA     UDR
	#define UART0_UDRIE    UDRIE
#elif defined(__AVR_ATmega48__) \
   || defined(__AVR_ATmega88__) \
   || defined(__AVR_ATmega168__) \
   || defined(__AVR_ATmega48P__) \
   || defined(__AVR_ATmega88P__) \
   || defined(__AVR_ATmega168P__) \
   || defined(__AVR_ATmega328P__)
	/* TLS-Added 48P/88P/168P/328P */
	/* ATmega with one USART */
	#define ATMEGA_USART0
	#define UART0_RECEIVE_INTERRUPT   USART_RX_vect
	#define UART0_TRANSMIT_INTERRUPT  USART_UDRE_vect
	#define UART0_STATUS   UCSR0A
	#define UART0_CONTROL  UCSR0B
	#define UART0_DATA     UDR0
	#define UART0_UDRIE    UDRIE0
#elif defined(__AVR_ATtiny2313__) \
   || defined(__AVR_ATtiny2313A__) \
   || defined(__AVR_ATtiny4313__)
	#define ATMEGA_USART
	#define UART0_RECEIVE_INTERRUPT   USART_RX_vect
	#define UART0_TRANSMIT_INTERRUPT  USART_UDRE_vect
	#define UART0_STATUS   UCSRA
	#define UART0_CONTROL  UCSRB
	#define UART0_DATA     UDR
	#define UART0_UDRIE    UDRIE
#elif defined(__AVR_ATmega329__) \
   || defined(__AVR_ATmega649__) \
   || defined(__AVR_ATmega325__) \
   || defined(__AVR_ATmega3250__) \
   || defined(__AVR_ATmega645__) \
   || defined(__AVR_ATmega6450__)
	/* ATmega with one USART */
	#define ATMEGA_USART0
	#define UART0_RECEIVE_INTERRUPT   USART0_RX_vect
	#define UART0_TRANSMIT_INTERRUPT  USART0_UDRE_vect
	#define UART0_STATUS   UCSR0A
	#define UART0_CONTROL  UCSR0B
	#define UART0_DATA     UDR0
	#define UART0_UDRIE    UDRIE0
#elif defined(__AVR_ATmega3290__) \
   || defined(__AVR_ATmega6490__)
	/* TLS-Separated these two from the previous group because of inconsistency in the USART_RX */
	/* ATmega with one USART */
	#define ATMEGA_USART0
	#define UART0_RECEIVE_INTERRUPT   USART_RX_vect
	#define UART0_TRANSMIT_INTERRUPT  USART0_UDRE_vect
	#define UART0_STATUS   UCSR0A
	#define UART0_CONTROL  UCSR0B
	#define UART0_DATA     UDR0
	#define UART0_UDRIE    UDRIE0
#elif defined(__AVR_ATmega2560__) \
   || defined(__AVR_ATmega1280__) \
	 || defined(__AVR_ATmega640__)
	/* ATmega with four USART */
	#define ATMEGA_USART0
	#define ATMEGA_USART1
	#define ATMEGA_USART2
	#define ATMEGA_USART3
	#define UART0_RECEIVE_INTERRUPT   USART0_RX_vect
	#define UART1_RECEIVE_INTERRUPT   USART1_RX_vect
	#define UART2_RECEIVE_INTERRUPT   USART2_RX_vect
	#define UART3_RECEIVE_INTERRUPT   USART3_RX_vect
	#define UART0_TRANSMIT_INTERRUPT  USART0_UDRE_vect
	#define UART1_TRANSMIT_INTERRUPT  USART1_UDRE_vect
	#define UART2_TRANSMIT_INTERRUPT  USART2_UDRE_vect
	#define UART3_TRANSMIT_INTERRUPT  USART3_UDRE_vect
	#define UART0_STATUS   UCSR0A
	#define UART0_CONTROL  UCSR0B
	#define UART0_DATA     UDR0
	#define UART0_UDRIE    UDRIE0
	#define UART1_STATUS   UCSR1A
	#define UART1_CONTROL  UCSR1B
	#define UART1_DATA     UDR1
	#define UART1_UDRIE    UDRIE1
	#define UART2_STATUS   UCSR2A
	#define UART2_CONTROL  UCSR2B
	#define UART2_DATA     UDR2
	#define UART2_UDRIE    UDRIE2
	#define UART3_STATUS   UCSR3A
	#define UART3_CONTROL  UCSR3B
	#define UART3_DATA     UDR3
	#define UART3_UDRIE    UDRIE3
#elif defined(__AVR_ATmega644__)
	/* ATmega with one USART */
	#define ATMEGA_USART0
	#define UART0_RECEIVE_INTERRUPT   USART0_RX_vect
	#define UART0_TRANSMIT_INTERRUPT  USART0_UDRE_vect
	#define UART0_STATUS   UCSR0A
	#define UART0_CONTROL  UCSR0B
	#define UART0_DATA     UDR0
	#define UART0_UDRIE    UDRIE0
#elif defined(__AVR_ATmega164P__) \
   || defined(__AVR_ATmega324P__) \
   || defined(__AVR_ATmega644P__) \
   || defined(__AVR_ATmega644PA__) \
   || defined(__AVR_ATmega1284P__)
	/* ATmega with two USART */
	#define ATMEGA_USART0
	#define ATMEGA_USART1
	#define UART0_RECEIVE_INTERRUPT   USART0_RX_vect
	#define UART1_RECEIVE_INTERRUPT   USART1_RX_vect
	#define UART0_TRANSMIT_INTERRUPT  USART0_UDRE_vect
	#define UART1_TRANSMIT_INTERRUPT  USART1_UDRE_vect
	#define UART0_STATUS   UCSR0A
	#define UART0_CONTROL  UCSR0B
	#define UART0_DATA     UDR0
	#define UART0_UDRIE    UDRIE0
	#define UART1_STATUS   UCSR1A
	#define UART1_CONTROL  UCSR1B
	#define UART1_DATA     UDR1
	#define UART1_UDRIE    UDRIE1
#elif defined(__AVR_ATtiny814__)
  /* AVR-1 with USART */
	#define AVR1_USART0
	#define UART0_RECEIVE_INTERRUPT   USART0_RXC_vect
	#define UART0_TRANSMIT_INTERRUPT  USART0_DRE_vect
  #define USART0_BAUD_RATE(_br_)    (uint16_t)((float)(F_CPU * 64 / (16 * (float)(_br_)) + 0.5))
  //	#error "AVR ATtiny814 currently not supported by this libaray !"
#else
	#error "no UART definition for MCU available"
#endif


/** @brief  UART Baudrate Expression
 *  @param  xtalCpu  system clock in Mhz, e.g. 4000000L for 4Mhz
 *  @param  baudRate baudrate in bps, e.g. 1200, 2400, 9600
 */
#define UART_BAUD_SELECT(baudRate,xtalCpu) (((xtalCpu)+8UL*(baudRate))/(16UL*(baudRate))-1UL)

/** @brief  UART Baudrate Expression for ATmega double speed mode
 *  @param  xtalCpu  system clock in Mhz, e.g. 4000000L for 4Mhz
 *  @param  baudRate baudrate in bps, e.g. 1200, 2400, 9600
 */
#define UART_BAUD_SELECT_DOUBLE_SPEED(baudRate,xtalCpu) ((((xtalCpu)+4UL*(baudRate))/(8UL*(baudRate))-1)|0x8000)

uint16_t zrtos_vfs_module_avr_uart__baud_select(
	zrtos_vfs_module_uart_baudrate_t baudrate
){
	uint16_t ret;
	if(baudrate & ZRTOS_VFS_MODULE_UART_BAUDRATE__DOUBLE_SPEED){
		baudrate = (zrtos_vfs_module_uart_baudrate_t)
			(baudrate & ZRTOS_VFS_MODULE_UART_BAUDRATE__MASK
		);
		ret = UART_BAUD_SELECT_DOUBLE_SPEED(baudrate,F_CPU);
	}else{
		ret = UART_BAUD_SELECT(baudrate,F_CPU);
	}
	return ret;
}

#ifdef __cplusplus
}
#endif
#endif
