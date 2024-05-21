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


#ifndef ZRTOS_TASK_SCHEDULER__TICK_PERIOD_MS
#error "Please define ZRTOS_TASK_SCHEDULER__TICK_PERIOD_MS"
#endif


#include "zrtos_error.h"

typedef unsigned int zrtos_task_tick_type_t;
typedef unsigned int zrtos_task_id_t;


typedef struct _zrtos_task_t{
	struct _zrtos_task_t  *next;
	//zrtos_arch_stack_t    *heap;
	zrtos_arch_stack_t    *stack_ptr;
	//size_t               heap_size;
	uint16_t             ticks;
	//bool               is_running;
	errno_t              errno;
}zrtos_task_t;

bool zrtos_task__init(
	 zrtos_task_t          *thiz
	,zrtos_arch_stack_t     *heap
	,size_t                heap_size
	,zrtos_arch_callback_t callback
	,void                  *args
){
	thiz->next = thiz;
	thiz->ticks = 0;
	thiz->errno = 0;
	//thiz->is_running = false;
	//thiz->heap = heap;
	//thiz->heap_size = heap_size;
	thiz->stack_ptr = zrtos_task_heap__init(
		 heap
		,heap_size
		,callback
		,args
	);
	return true;
}

void zrtos_task__set_delay_ms(zrtos_task_t *thiz,zrtos_task_tick_type_t ms){
#if ZRTOS_TASK_SCHEDULER__TICK_PERIOD_MS == 1
	thiz->ticks = ms;
#else
	thiz->ticks = ms ? (ms / ZRTOS_TASK_SCHEDULER__TICK_PERIOD_MS) : 0;
#endif
}

void zrtos_task__on_tick(zrtos_task_t *thiz){
	thiz->ticks -= (thiz->ticks > 0);
}

bool zrtos_task__is_idle(zrtos_task_t *thiz){
	return thiz->ticks > 0;
}

#ifdef ZRTOS_TASK__USE_MEM

static volatile zrtos_malloc_t *zrtos_task__heap = 0;

zrtos_malloc_t *zrtos_task__get_heap(){
	return zrtos_task__heap;
}

void zrtos_task__set_heap(zrtos_malloc_t *heap){
	zrtos_task__heap = heap;
}

#endif

zrtos_task_t *zrtos_task__get_next_task(zrtos_task_t *thiz){
	return thiz->next;
}

zrtos_task_t *zrtos_task__get_previous_task(zrtos_task_t *thiz){
	zrtos_task_t *last;
	zrtos_task_t *sentinel = thiz;
	
	do{
		last = thiz;
		thiz = zrtos_task__get_next_task(thiz);
	}while(thiz != sentinel);

	return ret;
}

void zrtos_task__set_stack_ptr(zrtos_task_t *thiz,zrtos_arch_stack_t *stack_ptr){
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
/*
bool zrtos_task__is_running(zrtos_task_t *thiz){
	return thiz->is_running;
}

void zrtos_task__set_running(zrtos_task_t *thiz){
	thiz->is_running = true;
}
*/


#ifdef __cplusplus
}
#endif
#endif