/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_BOARD_H
#define ZRTOS_BOARD_H
#ifdef __cplusplus
extern "C" {
#endif

#define ZRTOS_BOARD__ON_TICK_CALLBACK(name,code) \
    void name(void){                             \
        code                                     \
        ZRTOS_ARCH__RETURN_FROM_INTERRUPT();     \
    }

#define ZRTOS_BOARD__ON_TICK_NAKED_CALLBACK(name,code) \
    __attribute__((naked)) void name(void){            \
        code                                           \
        ZRTOS_ARCH__RETURN_FROM_INTERRUPT();           \
    }

ZRTOS_BOARD__ON_TICK_CALLBACK(zrtos_board__empty_on_tick_callback,{
	//empty callback
});

ZRTOS_BOARD__ON_TICK_NAKED_CALLBACK(zrtos_board__empty_on_tick_naked_callback,{
	//empty callback
});

void (*zrtos_board__on_tick)(void) = zrtos_board__empty_on_tick_callback;
void (*zrtos_board__on_tick_naked)(void)__attribute__((naked)) = zrtos_board__empty_on_tick_naked_callback;

#define ZRTOS_BOARD__SET_ON_TICK_CALLBACK(callback) \
	zrtos_board__on_tick = callback;

#define ZRTOS_BOARD__SET_ON_TICK_NAKED_CALLBACK(callback) \
	zrtos_board__on_tick_naked = callback;

/*
#define ZRTOS_BOARD__FOUND
#define ZRTOS_BOARD__TICK_PERIOD_MS
#define ZRTOS_BOARD__ON_TICK()
#define ZRTOS_BOARD__ON_TICK_NAKED()
#define ZRTOS_BOARD__ON_WATCH_DOG()
#define ZRTOS_BOARD__WATCH_DOG_START()
#define ZRTOS_BOARD__WATCH_DOG_STOP()
#define ZRTOS_BOARD__WATCH_DOG_RESET()

uint64_t zrtos_board__get_ticks();
uint64_t zrtos_board__get_microseconds();
uint64_t zrtos_board__get_milliseconds();
uint64_t zrtos_board__get_seconds();
*/

#ifdef ZRTOS_BOARD__FOUND
#error "ZRTOS_BOARD__FOUND defined"
#endif

//#include <board/arduino.h>
#include <zrtos/board/ansi_c.h>
#include <zrtos/board/avr_software_emulator.h>
//#define ZRTOS_BOARD__FOUND

#ifndef ZRTOS_BOARD__FOUND
#error "board/*.h not found"
#endif

#ifdef __cplusplus
}
#endif
#endif