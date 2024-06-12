/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_BOARD_AVR_SOFTWARE_EMULATOR_H
#define ZRTOS_BOARD_AVR_SOFTWARE_EMULATOR_H
#ifdef __cplusplus
extern "C" {
#endif


#if defined(ZRTOS_BOARD__AVR_SOFTWARE_EMULATOR) || defined(__DOXYGEN__)
#define ZRTOS_BOARD__FOUND


#include <avr/interrupt.h>
#include <avr/wdt.h>


#define ZRTOS_BOARD__TICK_PERIOD_MS 1

void zrtos_board__start_tick_timer(void){
	ZRTOS_ARCH__DISABLE_INTERRUPTS();
	// Clear registers
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;

	// 1000 Hz (16000000/((249+1)*64))
	OCR1A = 249;
	// CTC
	TCCR1B |= (1 << WGM12);
	// Prescaler 64
	TCCR1B |= (1 << CS11) | (1 << CS10);
	// Output Compare Match A Interrupt Enable
	TIMSK1 |= (1 << OCIE1A);
	ZRTOS_ARCH__ENABLE_INTERRUPTS();
}

void zrtos_board__stop_tick_timer(void){
	ZRTOS_ARCH__DISABLE_INTERRUPTS();
	TIMSK1 &= ~(1 << OCIE1A);
	ZRTOS_ARCH__ENABLE_INTERRUPTS();
}

ISR(TIMER1_COMPA_vect,ISR_NAKED){
	ZRTOS_ARCH__SAVE_CPU_STATE();
	zrtos_board__on_tick();
	//avr/time.h system_tick();
	ZRTOS_ARCH__LOAD_CPU_STATE();
	zrtos_board__on_tick_naked();
	ZRTOS_ARCH__RETURN_FROM_INTERRUPT();
}

#define ZRTOS_BOARD__WATCH_DOG_START() \
    wdt_enable(WDTO_8S);

#define ZRTOS_BOARD__WATCH_DOG_STOP() \
    wdt_disable();

#define ZRTOS_BOARD__WATCH_DOG_RESET() \
    wdt_reset();

ISR(WDT_vect,ISR_NAKED){
	ZRTOS_ARCH__FATAL();
}

#endif


#ifdef __cplusplus
}
#endif
#endif