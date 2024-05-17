/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_BOARDS_ARDUINO_H
#define ZRTOS_BOARDS_ARDUINO_H
#ifdef __cplusplus
extern "C" {
#endif

//https://android.googlesource.com/platform/external/arduino/+/d5790d78880d4bd60be277ee20e53a851aa8c116/hardware/arduino/cores/arduino/wiring.c

/*
// the prescaler is set so that timer0 ticks every 64 clock cycles, and the
// the overflow handler is called every 256 ticks.
#define MICROSECONDS_PER_TIMER0_OVERFLOW (clockCyclesToMicroseconds(64 * 256))
// the whole number of milliseconds per timer0 overflow
#define MILLIS_INC (MICROSECONDS_PER_TIMER0_OVERFLOW / 1000)
// the fractional number of milliseconds per timer0 overflow. we shift right
// by three to fit these numbers into a byte. (for the clock speeds we care
// about - 8 and 16 MHz - this doesn't lose precision.)
#define FRACT_INC ((MICROSECONDS_PER_TIMER0_OVERFLOW % 1000) >> 3)
#define FRACT_MAX (1000 >> 3)
volatile unsigned long timer0_overflow_count = 0;
volatile unsigned long timer0_millis = 0;
static unsigned char timer0_fract = 0;
*/

/*
Timer0: Timer0 is a 8bit timer. In the Arduino world Timer0 is been used for
 the timer functions, like delay(), millis() and micros(). If you change
 Timer0 registers, this may influence the Arduino timer function. So you 
 should know what you are doing. Timer1: Timer1 is a 16bit timer. In the
 Arduino world the Servo library uses Timer1 on Arduino Uno (Timer5 on
 Arduino Mega). Timer2: Timer2 is a 8bit timer like Timer0. In 
 the Arduino work the tone() function uses Timer2. Timer3, Timer4, Timer5:
 Timer 3,4,5 are only available on Arduino Mega boards. These timers are
 all 16bit timers. Timer Register You can change the Timer behaviour 
 through the timer register. The most important timer registers are:

 https://oscarliang.com/arduino-timer-and-interrupt-tutorial/
*/

SIGNAL(TIMER0_OVF_vect){
	// copy these to local variables so they can be stored in registers
	// (volatile variables must be read from memory on every access)
	unsigned long m = timer0_millis;
	unsigned char f = timer0_fract;
	m += MILLIS_INC;
	f += FRACT_INC;
	if (f >= FRACT_MAX) {
		f -= FRACT_MAX;
		m += 1;
	}
	timer0_fract = f;
	timer0_millis = m;
	timer0_overflow_count++;

    zrtos__on_interrupt(64);
}


#ifdef __cplusplus
}
#endif
#endif