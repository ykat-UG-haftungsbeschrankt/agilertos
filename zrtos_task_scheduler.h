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


#include "zrtos_types.h"
#include "zrtos_task.h"
#include "zrtos_mem.h"


typedef struct _zrtos_task_scheduler_t{
	zrtos_task_top_of_stack_t *tmp_stack_ptr;
	zrtos_mem_t               *heap;
}zrtos_task_scheduler_t;


volatile zrtos_task_scheduler_t zrtos_task_scheduler = {};


zrtos_mem_t *zrtos_task_scheduler__get_heap(void){
	return zrtos_task_scheduler.heap;
}

void zrtos_task_scheduler__set_heap(zrtos_mem_t *heap){
	zrtos_task_scheduler.heap = heap;
}

zrtos_task_t *_zrtos_task_scheduler__get_active_task(void){
	return zrtos_types__ptr_subtract(
		 zrtos_mem__get_last_address(zrtos_task_scheduler__get_heap())
		,sizeof(zrtos_task_t)
	);
}

#pragma GCC push_options
#pragma GCC optimize ("O0")
void _zrtos_task_scheduler__restore_task(void){
	_ZRTOS_TASK__RESTORE(zrtos_task_scheduler.tmp_stack_ptr);
	ZRTOS_TASK_SCHEDULER__ISR_RETURN();
}
#pragma GCC pop_options

void zrtos_task_scheduler__page_task_out(void){
	zrtos_mem_t *heap = zrtos_task_scheduler__get_heap();
	zrtos_task_t *task = _zrtos_task_scheduler__get_active_task();

	zrtos_task__set_errno(task,errno);
	zrtos_mem__page_out(
		 heap
		,zrtos_mem__get_by_type_ex(heap,ZRTOS_MEM_CHUNK_TYPE__TASK_ACTIVE)
		,zrtos_types__ptr_get_byte_distance(
			 zrtos_mem__get_last_address(heap)
			,zrtos_task_scheduler.tmp_stack_ptr
		)
	);
}

void zrtos_task_scheduler__page_task_in(
	 /*zrtos_task_t      *task
	,*/zrtos_mem_chunk_t *chunk
){
	zrtos_mem_t *heap = zrtos_task_scheduler__get_heap();
	zrtos_task_scheduler.tmp_stack_ptr = zrtos_mem__page_in(
		 heap
		,chunk
	);
	errno = zrtos_task__get_errno(_zrtos_task_scheduler__get_active_task());
}

bool _zrtos_task_scheduler__set_active_task(
	 /*zrtos_task_t      *task
	,*/zrtos_mem_chunk_t *chunk
){
	zrtos_task_scheduler__page_task_out();
	zrtos_task_scheduler__page_task_in(/*task,*/chunk);

	return true;
}

bool zrtos_task_scheduler__has_enough_stack_space(
	 zrtos_task_t      *task
	,zrtos_mem_chunk_t *chunk
){
	zrtos_mem_t *mem = zrtos_task_scheduler__get_heap();
	//@todo stack_size_min
	//size_t stack_size_min = zrtos_task__get_stack_size_min(task);
	if(_zrtos_mem__get_free_space(mem)
	<=  ZRTOS_TYPES__MAX(
		 zrtos_task__get_stack_size_min(task)
		,zrtos_mem_chunk__get_length(chunk)
	) - zrtos_mem_chunk__get_length(chunk)){
		ZRTOS__FATAL();
		return false;
	}
	return true;
}

bool zrtos_task_scheduler__start(void){
	zrtos_mem_t *heap = zrtos_task_scheduler__get_heap();
	zrtos_mem_chunk_t *chunk = zrtos_mem__get_by_type_ex(
		 heap
		,ZRTOS_MEM_CHUNK_TYPE__TASK_IDLE
	);
	if(chunk){
		zrtos_task_scheduler__page_task_in(chunk);
		//_zrtos_task_scheduler__isr_start();
		_zrtos_task_scheduler__restore_task();
		while(true){}
		return true;
	}
	return false;
}

#define ZRTOS_TASK_SCHEDULER__EACH_TASK_BEGIN(thiz,start_offset,pos,chunk,task)\
    ZRTOS_MEM__EACH_EX_BEGIN(                                                  \
         thiz                                                                  \
        ,start_offset                                                          \
        ,pos                                                                   \
        ,ZRTOS_MEM_CHUNK_TYPE__TASK_IDLE                                       \
        ,chunk                                                                 \
    ){                                                                         \
        zrtos_task_t *task = zrtos_types__ptr_subtract(                        \
            zrtos_types__ptr_add(                                              \
                 zrtos_mem_chunk__get_ptr(chunk)                               \
                ,zrtos_mem_chunk__get_length(chunk)                            \
            )                                                                  \
            ,sizeof(zrtos_task_t)                                              \
        );                                                                     \
        {

#define ZRTOS_TASK_SCHEDULER__EACH_TASK_END \
        }                                   \
     }ZRTOS_MEM__EACH_EX_END

void _zrtos_task_scheduler__switch_task(void){
	static size_t start_offset = 0;
	uint8_t tmp = 1;
	size_t offset = 0;
	size_t chunk_count = zrtos_mem__get_chunk_count(
		zrtos_task_scheduler__get_heap()
	);
	do{
		ZRTOS_TASK_SCHEDULER__EACH_TASK_BEGIN(
			 zrtos_task_scheduler__get_heap()
			,offset
			,pos
			,chunk
			,task
		){
			if(tmp){
				zrtos_task__on_tick(task);
			}else{
				if(!zrtos_task__is_idle(task)
				&& zrtos_task_scheduler__has_enough_stack_space(task,chunk)
				){
					start_offset = pos+1;
					start_offset = start_offset < chunk_count
								? start_offset
								: 0
					;
					_zrtos_task_scheduler__set_active_task(
						 /*task
						,*/chunk
					);
				}
			}
		}ZRTOS_TASK_SCHEDULER__EACH_TASK_END;

		offset = start_offset;
	}while(tmp--);

	_zrtos_task_scheduler__restore_task();
}

#pragma GCC push_options
#pragma GCC optimize ("O0")
void _zrtos_task_scheduler__on_tick(void){
	_ZRTOS_TASK__SAVE(zrtos_task_scheduler.tmp_stack_ptr);

	_zrtos_task_scheduler__switch_task();
}
#pragma GCC pop_options

void zrtos_task_scheduler__delay_ms(zrtos_task_delay_t ms){
	zrtos_task__set_delay_ms(
		 _zrtos_task_scheduler__get_active_task()
		,ms
	);
	_zrtos_task_scheduler__on_tick();
}


#ifdef __cplusplus
}
#endif
#endif