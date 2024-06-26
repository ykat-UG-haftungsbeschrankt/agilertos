/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VHEAP_TASK_SCHEDULER_H
#define ZRTOS_VHEAP_TASK_SCHEDULER_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/types.h>
#include <zrtos/vheap_task.h>
#include <zrtos/vheap.h>


typedef struct _zrtos_vheap_task_scheduler_t{
	zrtos_arch_stack_t *tmp_stack_ptr;
	zrtos_vheap_t               *heap;
	uint16_t                  ctx_switch_task_stack[100];
	size_t                    start_offset;
}zrtos_vheap_task_scheduler_t;


volatile zrtos_vheap_task_scheduler_t zrtos_vheap_task_scheduler = {};


zrtos_vheap_t *zrtos_vheap_task_scheduler__get_heap(void){
	return zrtos_vheap_task_scheduler.heap;
}

void zrtos_vheap_task_scheduler__set_heap(zrtos_vheap_t *heap){
	zrtos_vheap_task_scheduler.heap = heap;
}

zrtos_vheap_task_t *_zrtos_vheap_task_scheduler__get_active_task(void){
	return zrtos_types__ptr_subtract(
		 zrtos_vheap__get_last_address(zrtos_vheap_task_scheduler__get_heap())
		,sizeof(zrtos_vheap_task_t)
	);
}

#pragma GCC push_options
#pragma GCC optimize ("O0")
static void _zrtos_vheap_task_scheduler__restore_task(void){
	ZRTOS_ARCH__LOAD_CPU_STATE_EX(zrtos_vheap_task_scheduler.tmp_stack_ptr);
	ZRTOS_ARCH__RETURN_FROM_INTERRUPT();
}
#pragma GCC pop_options

static void zrtos_vheap_task_scheduler__page_task_out(void){
	zrtos_vheap_t *heap = zrtos_vheap_task_scheduler__get_heap();
	zrtos_vheap_task_t *task = _zrtos_vheap_task_scheduler__get_active_task();

	zrtos_vheap_task__set_stack_ptr(task,zrtos_vheap_task_scheduler.tmp_stack_ptr);
	zrtos_vheap_task__set_errno(task,errno);
	zrtos_vheap__page_out(
		 heap
		,zrtos_vheap__get_by_type_ex(heap,ZRTOS_VHEAP_TYPE__TASK_ACTIVE)
		,zrtos_types__ptr_get_byte_distance(
			 zrtos_vheap__get_last_address(heap)
			,zrtos_vheap_task_scheduler.tmp_stack_ptr
		)
	);
}

static void zrtos_vheap_task_scheduler__page_task_in(
	 /*zrtos_vheap_task_t      *task
	,*/zrtos_vheap_chunk_t *chunk
){
	zrtos_vheap_task_t *task;
	zrtos_vheap_t *heap = zrtos_vheap_task_scheduler__get_heap();
	zrtos_vheap__page_in(
		 heap
		,chunk
	);
	task = _zrtos_vheap_task_scheduler__get_active_task();
	zrtos_vheap_task_scheduler.tmp_stack_ptr = zrtos_vheap_task__get_stack_ptr(task);
	errno = zrtos_vheap_task__get_errno(_zrtos_vheap_task_scheduler__get_active_task());
}

static bool _zrtos_vheap_task_scheduler__set_active_task(
	 /*zrtos_vheap_task_t      *task
	,zrtos_vheap_chunk_t *chunk*/
	zrtos_vheap_chunk_uid_t uid
){
	zrtos_vheap_t *heap = zrtos_vheap_task_scheduler__get_heap();
	zrtos_vheap_chunk_t *chunk;
	zrtos_vheap_task_scheduler__page_task_out();
	chunk = zrtos_vheap__get_by_id(
		 heap
		,uid
	);
	zrtos_vheap_task_scheduler__page_task_in(/*task,*/chunk);

	return true;
}

bool zrtos_vheap_task_scheduler__has_enough_stack_space(
	 zrtos_vheap_task_t      *task
	,zrtos_vheap_chunk_t *chunk
){
	zrtos_vheap_t *mem = zrtos_vheap_task_scheduler__get_heap();
	//@todo stack_size_min
	//size_t stack_size_min = zrtos_vheap_task__get_stack_size_min(task);
	if(_zrtos_vheap__get_free_space_ex(
		 mem
		,zrtos_vheap_task_scheduler.tmp_stack_ptr
	)
	<=  ZRTOS_TYPES__MAX(
		 zrtos_vheap_task__get_stack_size_min(task)
		,zrtos_vheap_chunk__get_length(chunk)
	) - zrtos_vheap_chunk__get_length(chunk)){
		ZRTOS_ARCH__FATAL();
		return false;
	}
	return true;
}

bool zrtos_vheap_task_scheduler__start(void){ 
	zrtos_vheap_t *heap = zrtos_vheap_task_scheduler__get_heap();
	zrtos_vheap_chunk_t *chunk = zrtos_vheap__get_by_type_ex(
		 heap
		,ZRTOS_VHEAP_TYPE__TASK_IDLE
	);
	if(chunk){
		zrtos_vheap_task_scheduler__page_task_in(chunk);
		_zrtos_vheap_task_scheduler__restore_task();
		while(true){}
		return true;
	}
	return false;
}

#define ZRTOS_VHEAP_TASK_SCHEDULER__EACH_TASK_BEGIN(thiz,start_offset,pos,chunk,task)\
    ZRTOS_VHEAP__EACH_EX_BEGIN(                                                  \
         thiz                                                                  \
        ,start_offset                                                          \
        ,pos                                                                   \
        ,ZRTOS_VHEAP_TYPE__TASK_IDLE                                       \
        ,chunk                                                                 \
    ){                                                                         \
        zrtos_vheap_task_t *task = zrtos_types__ptr_subtract(                        \
            zrtos_types__ptr_add(                                              \
                 zrtos_vheap_chunk__get_ptr(chunk)                               \
                ,zrtos_vheap_chunk__get_length(chunk)                            \
            )                                                                  \
            ,sizeof(zrtos_vheap_task_t)                                              \
        );                                                                     \
        {

#define ZRTOS_VHEAP_TASK_SCHEDULER__EACH_TASK_END \
        }                                   \
     }ZRTOS_VHEAP__EACH_EX_END

void _zrtos_vheap_task_scheduler__switch_task(void){
	uint8_t tmp = 1;
	size_t offset = 0;
	do{
		ZRTOS_VHEAP_TASK_SCHEDULER__EACH_TASK_BEGIN(
			 zrtos_vheap_task_scheduler__get_heap()
			,offset
			,pos
			,chunk
			,task
		){
			if(tmp){
				zrtos_vheap_task__on_tick(task);
			}else{
				if(!zrtos_vheap_task__is_idle(task)
				&& zrtos_vheap_task_scheduler__has_enough_stack_space(
					 task
					,chunk
				)
				){
					/*size_t chunk_count = zrtos_vheap__get_chunk_count(
						zrtos_vheap_task_scheduler__get_heap()
					);

					zrtos_vheap_task_scheduler.start_offset = pos+1;
					zrtos_vheap_task_scheduler.start_offset = zrtos_vheap_task_scheduler.start_offset < chunk_count
								? zrtos_vheap_task_scheduler.start_offset
								: 0
					;*/

					_zrtos_vheap_task_scheduler__set_active_task(
						 /*task
						,*/zrtos_vheap_chunk__get_uid(chunk)
					);
					goto L_OUT;
				}
			}
		}ZRTOS_VHEAP_TASK_SCHEDULER__EACH_TASK_END;

		//offset = zrtos_vheap_task_scheduler.start_offset;
	}while(tmp--);

L_OUT:
	_zrtos_vheap_task_scheduler__restore_task();
}

#pragma GCC push_options
#pragma GCC optimize ("O0")
void _zrtos_vheap_task_scheduler__on_tick(void){
	ZRTOS_ARCH__SAVE_CPU_STATE_EX(zrtos_vheap_task_scheduler.tmp_stack_ptr);

	ZRTOS_DEBUG__CODE({
		zrtos_debug__memset(
			 (void*)zrtos_vheap_task_scheduler.ctx_switch_task_stack
			,0xbb
			,ZRTOS_TYPES__GET_STATIC_ARRAY_LENGTH(
				zrtos_vheap_task_scheduler.ctx_switch_task_stack
			)*sizeof(zrtos_vheap_task_scheduler.ctx_switch_task_stack[0])
		);
	});

	ZRTOS_ARCH__SET_STACK_PTR(
		  zrtos_vheap_task_scheduler.ctx_switch_task_stack
		+ ZRTOS_TYPES__GET_STATIC_ARRAY_LENGTH(
			zrtos_vheap_task_scheduler.ctx_switch_task_stack
		)
	);

	_zrtos_vheap_task_scheduler__switch_task();
}
#pragma GCC pop_options

void zrtos_vheap_task_scheduler__delay_ms(zrtos_vheap_task_delay_t ms){
	zrtos_vheap_task__set_delay_ms(
		 _zrtos_vheap_task_scheduler__get_active_task()
		,ms
	);
	_zrtos_vheap_task_scheduler__on_tick();
}

__attribute__((noreturn)) void zrtos_vheap_task_scheduler__trampoline_cb(
	 zrtos_vheap_task_t *thiz
	,void *(*callback)(void *args)
	,void *args
){
	void *ret = callback(args);
	zrtos_vheap_chunk_t *chunk = zrtos_vheap__get_by_type_ex(
		 zrtos_vheap_task_scheduler__get_heap()
		,ZRTOS_VHEAP_TYPE__TASK_ACTIVE
	);
	zrtos_vheap_task__set_return_value(thiz,ret);
	zrtos_vheap_chunk__set_type(chunk,ZRTOS_VHEAP_TYPE__TASK_DONE);

	_zrtos_vheap_task_scheduler__on_tick();

	__builtin_unreachable();
	while(1){
		//should not return
	}
}

#ifdef __cplusplus
}
#endif
#endif