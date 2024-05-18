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


#include "zrtos_task.h"


typedef struct _zrtos_task_scheduler_t{
	zrtos_task_t      *active_task;
	zrtos_arch_stack_t *tmp_stack_ptr;
}zrtos_task_scheduler_t;


volatile zrtos_task_scheduler_t zrtos_task_scheduler = {};

/*
 * Manual context switch.  The first thing we do is save the registers so we
 * can use a naked attribute.
 */
#pragma GCC push_options
#pragma GCC optimize ("O0")
void _zrtos_task_scheduler__restore_task(zrtos_task_t *task){
	zrtos_task_scheduler.tmp_stack_ptr = zrtos_task_scheduler.active_task->stack_ptr;
	_ZRTOS_TASK__RESTORE(zrtos_task_scheduler.tmp_stack_ptr);
	ZRTOS_TASK_SCHEDULER__ISR_RETURN();
/*
	if(!zrtos_task__is_running(zrtos_task_scheduler.active_task)){
		zrtos_task__set_running(zrtos_task_scheduler.active_task);
		
	}
*/
}
#pragma GCC pop_options

void zrtos_task_scheduler__init(void){
	_zrtos_task_scheduler__isr_start();
	_zrtos_task_scheduler__restore_task(zrtos_task_scheduler.active_task);
}

/*
 * Manual context switch.  The first thing we do is save the registers so we
 * can use a naked attribute.
 */
void zrtos_task_scheduler__start(void){
	_zrtos_task_scheduler__isr_start();
}

void zrtos_task_scheduler__stop(void){
	_zrtos_task_scheduler__isr_stop();
}

zrtos_task_t *_zrtos_task_scheduler__get_active_task(void){
	volatile zrtos_task_scheduler_t *thiz = &zrtos_task_scheduler;
	return thiz->active_task;
}

bool _zrtos_task_scheduler__set_active_task(zrtos_task_t *task){
	volatile zrtos_task_scheduler_t *thiz = &zrtos_task_scheduler;
	//if(thiz->active_task != task){
		zrtos_task__set_errno(thiz->active_task,errno);
		errno = zrtos_task__get_errno(task);

#ifdef ZRTOS_TASK__USE_MEM
		zrtos_mem__swap_task_out(thiz->active_task);
		thiz->active_task = zrtos_mem__swap_task_in(task);
#else
		thiz->active_task = task;
#endif
		//@todo move old 

	//}
/*
	if(thiz->active_task != task){
		if(zrtos_task__is_running(thiz->active_task)){
			_ZRTOS_TASK__SAVE(heap);
			zrtos_task__set_stack_ptr(thiz->active_task,heap);
		}

		heap = zrtos_task__get_stack_ptr(task);
		thiz->active_task = task;

		if(zrtos_task__is_running(task)){
			_ZRTOS_TASK__RESTORE(heap);
		}else{
			_ZRTOS_TASK__RESTORE(heap);
			asm volatile ( "ret" );
		}
	}else if(!zrtos_task__is_running(task)){
		zrtos_task__set_running(task);
		ZRTOS_ARCH__DISABLE_INTERRUPTS();
		_ZRTOS_TASK__RESTORE(heap);
		asm volatile ( "ret" );
	}
*/
	return true;
}

bool zrtos_task_scheduler__add_task(zrtos_task_t *task){
	volatile zrtos_task_scheduler_t *thiz = &zrtos_task_scheduler;
	zrtos_task_t *active_task = thiz->active_task;
	if(active_task){
		task->next = active_task->next;
		active_task->next = task;
	}else{
		thiz->active_task = task;
	}

	return true;
}

bool zrtos_task_scheduler__remove_task(zrtos_task_t *task){
	volatile zrtos_task_scheduler_t *thiz = &zrtos_task_scheduler;
	zrtos_task_t *active_task = thiz->active_task;
	zrtos_task_t *prev = zrtos_task__get_previous_task(task);
	bool ret = active_task != task;

	if(ret){
		prev->next = task->next;
		task->next = task;
	}

	return ret;
}

bool _zrtos_task_scheduler__switch_task(void){
	zrtos_task_t *active_task = _zrtos_task_scheduler__get_active_task();
	zrtos_task_t *task = active_task;
	if(task){
		do{
			zrtos_task__on_tick(task);
			task = zrtos_task__get_next_task(task);
		}while(task != active_task);

		task = active_task;
		do{
			task = zrtos_task__get_next_task(task);
			if(!zrtos_task__is_idle(task)){
				return _zrtos_task_scheduler__set_active_task(task);
			}
		}while(task != active_task);
	}
	return true;
}

#pragma GCC push_options
#pragma GCC optimize ("O0")
void _zrtos_task_scheduler__on_tick(void){
	_ZRTOS_TASK__SAVE(zrtos_task_scheduler.tmp_stack_ptr);
	zrtos_task_scheduler.active_task->stack_ptr = zrtos_task_scheduler.tmp_stack_ptr;
	_zrtos_task_scheduler__isr_reset_counter();
	if(!_zrtos_task_scheduler__switch_task()){
		ZRTOS__FATAL();
	}
	_zrtos_task_scheduler__restore_task(zrtos_task_scheduler.active_task);
}
#pragma GCC pop_options

inline void zrtos_task_scheduler__delay_ms(zrtos_task_delay_t ms){
	zrtos_task_t *active_task = _zrtos_task_scheduler__get_active_task();
	if(active_task){
		zrtos_task__set_delay_ms(
			 active_task
			,ms
		);
		_zrtos_task_scheduler__on_tick();
	}
}


#ifdef __cplusplus
}
#endif
#endif