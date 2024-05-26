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
#include "zrtos_clist.h"


typedef unsigned int zrtos_task_tick_t;
typedef unsigned int zrtos_task_id_t;

typedef enum{
	 ZRTOS_TASK_STATE__READY   = 0x0000
	,ZRTOS_TASK_STATE__RUNNING = 1 << (sizeof(zrtos_task_tick_t) * 8 - 2)
	,ZRTOS_TASK_STATE__DONE    = 1 << (sizeof(zrtos_task_tick_t) * 8 - 1)
	,ZRTOS_TASK_STATE__MASK    = ZRTOS_TASK_STATE__RUNNING
	                           | ZRTOS_TASK_STATE__DONE
}zrtos_task_state_t;


typedef struct _zrtos_task_t{
	zrtos_clist_node_t           node;
	struct _zrtos_task_t         *parent;
	zrtos_arch_stack_t           *stack_ptr;
	zrtos_task_tick_t            ticks;
	errno_t                      error_code;
}zrtos_task_t;

bool zrtos_task__init(
	 zrtos_task_t          *thiz
	,zrtos_arch_stack_t    *stack_ptr
){
	if(zrtos_clist_node__init(&thiz->node)){
		thiz->parent = 0;
		thiz->stack_ptr = stack_ptr;
		thiz->ticks = 0;
		thiz->error_code = 0;
		return true;
	}
	return false;
}

bool zrtos_task__init_ex(
	 zrtos_task_t          *thiz
	,zrtos_arch_stack_t    *heap
	,zrtos_arch_callback_t callback
	,void                  *args
){
	return zrtos_task__init(
		 thiz
		,zrtos_arch__cpu_state_init(
			heap
			//,heap_size
			,callback
			,args
		)
	);
}

void zrtos_task__set_delay_ms(zrtos_task_t *thiz,zrtos_task_tick_t ms){
#if ZRTOS_BOARD__TICK_PERIOD_MS == 1
	thiz->ticks = ms;
#else
	thiz->ticks = ms ? (ms / ZRTOS_BOARD__TICK_PERIOD_MS) : 0;
#endif
}

void zrtos_task__on_tick(zrtos_task_t *thiz){
	zrtos_task_tick_t val  = thiz->ticks;
	if(0 == (val & ZRTOS_TASK_STATE__MASK)){
		thiz->ticks -= (val > 0);
	}
}

bool zrtos_task__is_ready(zrtos_task_t *thiz){
	return thiz->ticks == 0;
}

bool zrtos_task__is_running(zrtos_task_t *thiz){
	return (thiz->ticks & ZRTOS_TASK_STATE__RUNNING) > 0;
}

bool zrtos_task__is_done(zrtos_task_t *thiz){
	return (thiz->ticks & ZRTOS_TASK_STATE__DONE) > 0;
}

void zrtos_task__set_ready(zrtos_task_t *thiz){
	thiz->ticks ^= (thiz->ticks & ZRTOS_TASK_STATE__MASK);
}

void zrtos_task__set_running(zrtos_task_t *thiz){
	thiz->ticks |= ZRTOS_TASK_STATE__RUNNING;
}

void zrtos_task__set_done(zrtos_task_t *thiz){
	thiz->ticks |= ZRTOS_TASK_STATE__DONE;
}

zrtos_task_t *zrtos_task__get_next_task(zrtos_task_t *thiz){
	zrtos_clist_node_t *node = zrtos_clist_node__get_next_node(&thiz->node);
	return zrtos_types__get_container_of(node,zrtos_task_t,node);
}

zrtos_task_t *zrtos_task__get_previous_task(zrtos_task_t *thiz){
	zrtos_clist_node_t *node = zrtos_clist_node__get_previous_node(&thiz->node);
	return zrtos_types__get_container_of(node,zrtos_task_t,node);
}

void zrtos_task__set_stack_ptr(zrtos_task_t *thiz,zrtos_arch_stack_t *stack_ptr){
	thiz->stack_ptr = stack_ptr;
}

zrtos_arch_stack_t *zrtos_task__get_stack_ptr(zrtos_task_t *thiz){
	return thiz->stack_ptr;
}

void zrtos_task__set_errno(zrtos_task_t *thiz,errno_t error_code){
	thiz->error_code = error_code;
}

errno_t zrtos_task__get_errno(zrtos_task_t *thiz){
	return thiz->error_code;
}

void zrtos_task__set_parent(zrtos_task_t *thiz,zrtos_task_t *parent){
	thiz->parent = parent;
}

zrtos_task_t *zrtos_task__get_parent(zrtos_task_t *thiz){
	return thiz->parent;
}


#ifdef __cplusplus
}
#endif
#endif