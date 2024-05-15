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
	zrtos_task_heap_t *tmp_stack_ptr;
	zrtos_mem_t       *heap;
}zrtos_task_scheduler_t;


volatile zrtos_task_scheduler_t zrtos_task_scheduler = {};

zrtos_mem_t *zrtos_task_scheduler__get_heap(){
	return zrtos_task_scheduler.heap;
}

void zrtos_task_scheduler__set_heap(zrtos_mem_t *heap){
	zrtos_task_scheduler.heap = heap;
}

#pragma GCC push_options
#pragma GCC optimize ("O0")
void _zrtos_task_scheduler__restore_task(zrtos_task_t *task){
	zrtos_task_scheduler.tmp_stack_ptr = zrtos_task_scheduler.active_task->stack_ptr;
	_ZRTOS_TASK__RESTORE(zrtos_task_scheduler.tmp_stack_ptr);
	ZRTOS_TASK_SCHEDULER__ISR_RETURN();
}
#pragma GCC pop_options

void zrtos_task_scheduler__init(void){
	_zrtos_task_scheduler__isr_start();
	_zrtos_task_scheduler__restore_task(zrtos_task_scheduler.active_task);
}

void zrtos_task_scheduler__start(void){
	_zrtos_task_scheduler__isr_start();
}

void zrtos_task_scheduler__stop(void){
	_zrtos_task_scheduler__isr_stop();
}

zrtos_task_t *_zrtos_task_scheduler__get_active_task(void){
	return zrtos_task_scheduler.active_task;
}

bool _zrtos_task_scheduler__set_active_task(zrtos_task_t *task){
	volatile zrtos_task_scheduler_t *thiz = &zrtos_task_scheduler;

	zrtos_task__set_errno(thiz->active_task,errno);
	errno = zrtos_task__get_errno(task);

	zrtos_mem__swap_task_out(thiz->active_task);
	thiz->active_task = zrtos_mem__swap_task_in(task);

	return true;
}

#define ZRTOS_TASK_SCHEDULER__EACH_TASK_BEGIN(thiz,start_offset,pos,value)     \
    ZRTOS_MEM__EACH_BEGIN_EX(thiz,start_offset,pos,ZRTOS_MEM_CHUNK_TYPE__TASK_IDLE,value____){\
        zrtos_task_t *value = zrtos_types__ptr_subtract(                       \
            zrtos_types__ptr_add(                                              \
                 zrtos_mem_chunk__get_ptr(value____)                           \
                ,zrtos_mem_chunk__get_length(value____)                        \
            )                                                                  \
            ,sizeof(zrtos_task_t)                                              \
        );

#define ZRTOS_TASK_SCHEDULER__EACH_TASK_END \
     }ZRTOS_MEM__EACH_END_EX

bool _zrtos_task_scheduler__switch_task(void){
	static start_offset = 0;
	zrtos_task_t *active_task = _zrtos_task_scheduler__get_active_task();
	zrtos_task_t *task = active_task;
	if(task){
		uint8_t tmp = 1;
		size_t offset = 0;
		size_t pos;
		size_t chunk_count = zrtos_mem__get_chunk_count(
			zrtos_task_scheduler__get_heap()
		);
		do{
			ZRTOS_TASK_SCHEDULER__EACH_TASK_BEGIN(
				 zrtos_task_scheduler__get_heap()
				,offset
				,pos
				,task
			){
				if(tmp){
					zrtos_task__on_tick(task);
				}else{
					if(!zrtos_task__is_idle(task)){
						start_offset = pos+1;
						start_offset = start_offset < chunk_count
						             ? start_offset
						             : 0
						;
						return _zrtos_task_scheduler__set_active_task(task);
					}
				}
			}ZRTOS_TASK_SCHEDULER__EACH_TASK_END;

			offset = start_offset;
		}while(tmp--);
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