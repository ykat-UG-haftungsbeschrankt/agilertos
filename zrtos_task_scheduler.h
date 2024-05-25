/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_TASK_SCHEDULER_H
#define ZRTOS_TASK_SCHEDULER_H
#ifdef __cplusplus
extern "C" {
#endif


#include "zrtos.h"
#include "zrtos_types.h"
#include "zrtos_clist.h"
#include "zrtos_error.h"
#include "zrtos_task.h"


typedef struct _zrtos_task_scheduler_t{
	zrtos_clist_t      root;
	zrtos_task_t       sleep_task;
	zrtos_arch_stack_t *tmp_stack_ptr;
	size_t             do_not_disturb;
}zrtos_task_scheduler_t;


zrtos_task_scheduler_t zrtos_task_scheduler = {};


#define ZRTOS_TASK_SCHEDULER__DO_NOT_DISTURB(code)       \
    do{                                        \
        ZRTOS_ARCH__DISABLE_INTERRUPTS();      \
        zrtos_task_scheduler.do_not_disturb++; \
        ZRTOS_ARCH__ENABLE_INTERRUPTS();       \
        do{                                    \
            code;                              \
        }while(0);                             \
        ZRTOS_ARCH__DISABLE_INTERRUPTS();      \
        zrtos_task_scheduler.do_not_disturb--; \
        ZRTOS_ARCH__ENABLE_INTERRUPTS();       \
    }while(0);


#define ZRTOS_TASK_SCHEDULER__DO_NOT_DISTURB_EX(is_locked,code) \
    do{                                                         \
        ZRTOS_ARCH__DISABLE_INTERRUPTS();                       \
        is_locked = (zrtos_task_scheduler.do_not_disturb == 0); \
        zrtos_task_scheduler.do_not_disturb++;                  \
        ZRTOS_ARCH__ENABLE_INTERRUPTS();                        \
        do{                                                     \
            code;                                               \
        }while(0);                                              \
        ZRTOS_ARCH__DISABLE_INTERRUPTS();                       \
        zrtos_task_scheduler.do_not_disturb--;                  \
        ZRTOS_ARCH__ENABLE_INTERRUPTS();                        \
    }while(0);


zrtos_task_t *_zrtos_task_scheduler__get_active_task(void){
	zrtos_clist_node_t *node = zrtos_clist__get_root(
		&zrtos_task_scheduler.root
	);
	return zrtos_types__get_container_of(node,zrtos_task_t,node);
}

bool zrtos_task_scheduler__add_task(zrtos_task_t *task){
	ZRTOS_TASK_SCHEDULER__DO_NOT_DISTURB({
		zrtos_task_t *active_task = _zrtos_task_scheduler__get_active_task();

		zrtos_task__set_parent(task,active_task);
		zrtos_clist__push(&active_task->children,&task->child_node);
		zrtos_clist__push(&zrtos_task_scheduler.root,&task->node);
	});

	return true;
}

bool zrtos_task_scheduler__remove_task(zrtos_task_t *task){
	ZRTOS_TASK_SCHEDULER__DO_NOT_DISTURB({
		zrtos_task_t *parent = zrtos_task__get_parent(task);
		zrtos_clist__delete(&parent->children,&task->child_node);
		zrtos_clist__delete(&zrtos_task_scheduler.root,&task->node);
		zrtos_task__set_parent(task,0);
	});

	return true;
}

bool zrtos_task_scheduler__has_task(zrtos_task_t *task){
	bool ret = false;

	ZRTOS_TASK_SCHEDULER__DO_NOT_DISTURB({
		zrtos_task_t *node = _zrtos_task_scheduler__get_active_task();
		zrtos_task_t *sentinel = node;

		do{
			if(node == task){
				ret = true;
				break;
			}
			node = zrtos_task__get_next_task(node);
		}while(node != sentinel);
	});

	return ret;
}

static zrtos_task_t *_zrtos_task_scheduler__get_sleep_task(void){
	return &zrtos_task_scheduler.sleep_task;
}

static void zrtos_task_scheduler__page_task_out(void){
	zrtos_task_t *active_task = _zrtos_task_scheduler__get_active_task();
	zrtos_task__set_stack_ptr(
		 active_task
		,zrtos_task_scheduler.tmp_stack_ptr
	);
	zrtos_task__set_errno(active_task,errno);
}

static void zrtos_task_scheduler__page_task_in(
	 zrtos_task_t      *task
){
	zrtos_clist__set_root(&zrtos_task_scheduler.root,&task->node);
	zrtos_task_scheduler.tmp_stack_ptr = zrtos_task__get_stack_ptr(task);
	errno = zrtos_task__get_errno(task);
}

static bool _zrtos_task_scheduler__set_active_task(zrtos_task_t *task){
	zrtos_task_scheduler__page_task_out();
	zrtos_task_scheduler__page_task_in(task);
	return true;
}

static bool _zrtos_task_scheduler__switch_task(void){
	zrtos_task_t *active_task = _zrtos_task_scheduler__get_active_task();
	zrtos_task_t *task = active_task;

	do{
		zrtos_task__on_tick(task);
		task = zrtos_task__get_next_task(task);
	}while(task != active_task);

	task = active_task;
	do{
		task = zrtos_task__get_next_task(task);
		if(zrtos_task__is_ready(task)){
			return _zrtos_task_scheduler__set_active_task(task);
		}
	}while(task != active_task);

	_zrtos_task_scheduler__set_active_task(
		_zrtos_task_scheduler__get_sleep_task()
	);

	return true;
}

#pragma GCC push_options
#pragma GCC optimize ("O0")
__attribute__((naked)) void _zrtos_task_scheduler__on_tick(void){
	ZRTOS_ARCH__SAVE_CPU_STATE_EX(zrtos_task_scheduler.tmp_stack_ptr);
	if(zrtos_task_scheduler.do_not_disturb == 0){
		_zrtos_task_scheduler__switch_task();
	}
	ZRTOS_ARCH__LOAD_CPU_STATE_EX(zrtos_task_scheduler.tmp_stack_ptr);
	ZRTOS_ARCH__RETURN_FROM_INTERRUPT();
}
#pragma GCC pop_options

static void _zrtos_task_scheduler__on_tick_ex(void){
	_zrtos_task_scheduler__on_tick();
}

void zrtos_task_scheduler__delay_ms(zrtos_task_tick_t ms){
	zrtos_task__set_delay_ms(
		 _zrtos_task_scheduler__get_active_task()
		,ms
	);
	_zrtos_task_scheduler__on_tick_ex();
}

void zrtos_task_scheduler__start(void){
/*
	while(true){
		_zrtos_task_scheduler__on_tick_ex();
	}
	__builtin_unreachable();
*/
}

void zrtos_task_scheduler__stop(void){
	//_zrtos_task_scheduler__isr_stop();
}

void zrtos_task_scheduler__init(){
	zrtos_clist__init(&zrtos_task_scheduler.root);
	zrtos_task__init(
		 &zrtos_task_scheduler.sleep_task
		,(zrtos_arch_stack_t*)0
	);
	zrtos_clist__push(
		 &zrtos_task_scheduler.root
		,&zrtos_task_scheduler.sleep_task.node
	);
	//zrtos_task_scheduler__add_task(&zrtos_task_scheduler.sleep_task);
	//zrtos_task_scheduler.tmp_stack_ptr = 0;
	zrtos_task_scheduler.do_not_disturb = 0;
	_zrtos_task_scheduler__on_tick_ex();
}




#ifdef __cplusplus
}
#endif
#endif