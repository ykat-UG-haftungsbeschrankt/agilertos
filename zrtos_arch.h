/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_ARCH_H
#define ZRTOS_ARCH_H
#ifdef __cplusplus
extern "C" {
#endif


#include "zrtos_types.h"

typedef uint8_t zrtos_task_top_of_stack_t;
typedef int8_t zrtos_task_heap_signed_t;
typedef uint16_t zrtos_task_delay_t;
typedef void *(*zrtos_task_callback_t)(void *arg);

void _zrtos_task_scheduler__on_tick(void)__attribute__((naked));

#include "arch/atmega328p.h"
#include "arch/atmega2560.h"


#ifdef __cplusplus
}
#endif
#endif