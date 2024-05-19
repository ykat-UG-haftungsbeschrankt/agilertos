/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_TASK_H
#define ZRTOS_TASK_H
#ifdef __cplusplus
extern "C" {
#endif


#ifndef ZRTOS_BOARD__TICK_PERIOD_MS
#error "Please define ZRTOS_BOARD__TICK_PERIOD_MS"
#endif


#include "zrtos_error.h"


typedef uint16_t zrtos_task_delay_t;
typedef unsigned int zrtos_task_tick_type_t;
typedef unsigned int zrtos_task_id_t;


typedef struct _zrtos_task_t{
	zrtos_arch_stack_t           *stack_ptr;
	size_t                       stacksize_min;
	uint16_t                     ticks;
	errno_t                      errno;
}zrtos_task_t;

bool zrtos_task__init(
	 zrtos_task_t              *thiz
	,zrtos_arch_stack_t        *heap
	//,size_t                    heap_size
	,size_t                    stacksize_min
	,zrtos_arch_callback_t     callback
	,void                      *args
){
	thiz->stacksize_min = stacksize_min;
	thiz->ticks = 0;
	thiz->errno = 0;
	thiz->stack_ptr = zrtos_arch__cpu_state_init(
		 heap
		//,heap_size
		,callback
		,args
	);
	return true;
}

void zrtos_task__set_delay_ms(zrtos_task_t *thiz,zrtos_task_tick_type_t ms){
#if ZRTOS_BOARD__TICK_PERIOD_MS == 1
	thiz->ticks = ms;
#else
	thiz->ticks = ms ? (ms / ZRTOS_BOARD__TICK_PERIOD_MS) : 0;
#endif
}

void zrtos_task__on_tick(zrtos_task_t *thiz){
	thiz->ticks -= (thiz->ticks > 0);
}

bool zrtos_task__is_idle(zrtos_task_t *thiz){
	return thiz->ticks > 0;
}

void zrtos_task__set_stack_ptr(
	 zrtos_task_t *thiz
	,zrtos_arch_stack_t *stack_ptr
){
	thiz->stack_ptr = stack_ptr;
}

zrtos_arch_stack_t *zrtos_task__get_stack_ptr(zrtos_task_t *thiz){
	return thiz->stack_ptr;
}

void zrtos_task__set_errno(zrtos_task_t *thiz,errno_t errno){
	thiz->errno = errno;
}

errno_t zrtos_task__get_errno(zrtos_task_t *thiz){
	return thiz->errno;
}

size_t zrtos_task__get_stack_size_min(zrtos_task_t *thiz){
	return thiz->stacksize_min;
}

#ifdef __cplusplus
}
#endif
#endif