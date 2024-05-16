/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_CPU_H_
#define ZRTOS_CPU_H_
#ifdef __cplusplus
extern "C" {
#endif


typedef uint8_t zrtos_task_top_of_stack_t;
typedef int8_t zrtos_task_heap_signed_t;
typedef uint16_t zrtos_task_delay_t;
typedef void (*zrtos_task_callback_t)(void *arg);

void _zrtos_task_scheduler__on_tick(void)__attribute__((naked));

#include "cpu/atmega328p.h"
#include "cpu/atmega2560.h"


#ifdef __cplusplus
}
#endif
#endif