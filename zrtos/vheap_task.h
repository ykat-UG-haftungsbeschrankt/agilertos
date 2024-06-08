/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VHEAP_TASK_H
#define ZRTOS_VHEAP_TASK_H
#ifdef __cplusplus
extern "C" {
#endif


#ifndef ZRTOS_BOARD__TICK_PERIOD_MS
#error "Please define ZRTOS_BOARD__TICK_PERIOD_MS"
#endif


#include <zrtos/error.h>
#include <zrtos/errno.h>
#include <zrtos/vheap_chunk_uid.h>


typedef uint16_t zrtos_vheap_task_delay_t;
typedef unsigned int zrtos_vheap_task_tick_type_t;
typedef unsigned int zrtos_vheap_task_id_t;


typedef struct _zrtos_vheap_task_t{
	zrtos_arch_stack_t           *stack_ptr;
	void                         *return_value;
	size_t                       stacksize_min;
	uint16_t                     ticks;
	zrtos_error_t                      errno;
}zrtos_vheap_task_t;

bool zrtos_vheap_task__init(
	 zrtos_vheap_task_t              *thiz
	,zrtos_arch_stack_t        *heap
	//,size_t                    heap_size
	,size_t                    stacksize_min
	,zrtos_arch_callback_t     callback
	,void                      *args
){
	thiz->stack_ptr = zrtos_arch__cpu_state_init(
		 heap
		//,heap_size
		,callback
		,args
	);
	thiz->return_value = 0;
	thiz->stacksize_min = stacksize_min;
	thiz->ticks = 0;
	thiz->errno = 0;

	return true;
}

void zrtos_vheap_task__set_delay_ms(zrtos_vheap_task_t *thiz,zrtos_vheap_task_tick_type_t ms){
#if ZRTOS_BOARD__TICK_PERIOD_MS == 1
	thiz->ticks = ms;
#else
	thiz->ticks = ms ? (ms / ZRTOS_BOARD__TICK_PERIOD_MS) : 0;
#endif
}

void zrtos_vheap_task__on_tick(zrtos_vheap_task_t *thiz){
	thiz->ticks -= (thiz->ticks > 0);
}

bool zrtos_vheap_task__is_idle(zrtos_vheap_task_t *thiz){
	return thiz->ticks > 0;
}

void zrtos_vheap_task__set_stack_ptr(
	 zrtos_vheap_task_t *thiz
	,zrtos_arch_stack_t *stack_ptr
){
	thiz->stack_ptr = stack_ptr;
}

zrtos_arch_stack_t *zrtos_vheap_task__get_stack_ptr(zrtos_vheap_task_t *thiz){
	return thiz->stack_ptr;
}

void zrtos_vheap_task__set_errno(zrtos_vheap_task_t *thiz,zrtos_error_t errno){
	thiz->errno = errno;
}

zrtos_error_t zrtos_vheap_task__get_errno(zrtos_vheap_task_t *thiz){
	return thiz->errno;
}

size_t zrtos_vheap_task__get_stack_size_min(zrtos_vheap_task_t *thiz){
	return thiz->stacksize_min;
}

void zrtos_vheap_task__set_return_value(zrtos_vheap_task_t *thiz,void *return_value){
	thiz->return_value = return_value;
}

void *zrtos_vheap_task__get_return_value(zrtos_vheap_task_t *thiz){
	return thiz->return_value;
}

#ifdef __cplusplus
}
#endif
#endif