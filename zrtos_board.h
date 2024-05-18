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

void zrtos_board__on_tick(void){

}

#define ZRTOS_BOARD__ON_TICK_CALLBACK(name,code)\
void name(void){
	code
	ZRTOS_ARCH__RETURN_FROM_INTERRUPT();
}__attribute__((naked));

#ifdef ZRTOS_TASK_SCHEDULER__CFG_ENABLED
void _zrtos_task_scheduler__on_tick(void)__attribute__((naked));
#endif

__attribute__((naked)) void zrtos_board__on_tick_naked(void){
#ifdef ZRTOS_TASK_SCHEDULER__CFG_ENABLED
	_zrtos_task_scheduler__on_tick();
#endif
}

/*
#define ZRTOS_BOARD__TICK_PERIOD_MS
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

#include "board/arduino.h"

#ifndef ZRTOS_BOARD__FOUND
#error "board/*.h not found"
#endif

#ifdef __cplusplus
}
#endif
#endif