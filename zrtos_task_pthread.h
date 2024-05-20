/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_TASK_PTHREAD_H
#define ZRTOS_TASK_PTHREAD_H
#ifdef __cplusplus
extern "C" {
#endif


#include "zrtos_error.h"
#include "zrtos_vheap.h"
#include "zrtos_task_scheduler.h"
#include "zrtos_task_mutex.h"
#include "zrtos_types.h"


typedef struct{
	size_t stacksize;
}pthread_attr_t;

typedef struct{
	zrtos_vheap_chunk_uid_t id;
}pthread_t;

typedef struct{
}pthread_mutexattr_t;

typedef struct{
	zrtos_task_mutex_t mutex;
}pthread_mutex_t;

#define PTHREAD_MUTEX_INITIALIZER    \
    {                                \
        .mutex = ZRTOS_TASK_MUTEX__INIT() \
    }

int pthread_attr_init(pthread_attr_t *attr){
	attr->stacksize = ZRTOS_ARCH__GET_CPU_STATE_BUFFER_LENGTH()
	                + ZRTOS_ARCH__GET_FN_CALL_STACK_LENGTH()
	;
	return 0;
}

int pthread_attr_destroy(pthread_attr_t *attr){
	return 0;
}

int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize){
	attr->stacksize = stacksize;
	return 0;
}

int pthread_mutexattr_init(pthread_mutexattr_t *attr){
	return 0;
}

int pthread_mutexattr_destroy(pthread_mutexattr_t *attr){
	return 0;
}

int pthread_mutex_init(
	 pthread_mutex_t *restrict mutex
	,const pthread_mutexattr_t *restrict attr
){
	return !zrtos_task_mutex__init(&mutex->mutex);
}

int pthread_mutex_destroy(pthread_mutex_t *mutex){
	zrtos_task_mutex__deinit(&mutex->mutex);
	return 0;
}

int pthread_create(
	 pthread_t *restrict thread
	,const pthread_attr_t *restrict attr
	,void *(*start_routine)(void *)
	,void *restrict arg
){
	size_t stack_size_min = ZRTOS_ARCH__GET_CPU_STATE_BUFFER_LENGTH()
	                      + ZRTOS_ARCH__GET_FN_CALL_STACK_LENGTH()
	;
	zrtos_vheap_t *mem = zrtos_task_scheduler__get_heap();
	size_t stacksize_min = sizeof(zrtos_task_t) + (
		  attr
		? ZRTOS_TYPES__MAX(
			 stack_size_min
			,attr->stacksize
		)
		: stack_size_min
	);
	zrtos_vheap_chunk_t *chunk = _zrtos_vheap__malloc(
		 mem
		,ZRTOS_VHEAP_CHUNK_TYPE__TASK_IDLE
		,stacksize_min
	);
	int ret = ENOMEM;

	if(chunk){
		void *mem_chunk_last_address = zrtos_vheap_chunk__get_last_address(
			chunk
		);
		zrtos_task_t *task = zrtos_types__ptr_subtract(
			 mem_chunk_last_address
			,sizeof(zrtos_task_t)
		);
		zrtos_task__init(
			 task
			,(zrtos_arch_stack_t*)(task - 1)
			,stacksize_min
			,start_routine
			,arg
		);
		task->stack_ptr = zrtos_types__ptr_subtract(
			 zrtos_vheap__get_last_address(mem)
			,zrtos_types__ptr_get_byte_distance(
				 mem_chunk_last_address
				,task->stack_ptr
			)
		);
		ret = 0;
	}

	return ret;
}

int pthread_equal(pthread_t t1, pthread_t t2){
	return zrtos_vheap_chunk_uid__cmp(&t1.id,&t2.id);
}

zrtos_task_t *pthread__get_task(pthread_t thread){
	zrtos_vheap_chunk_t *chunk = zrtos_vheap__get_by_id(
		zrtos_task_scheduler__get_heap()
		,thread.id
	);
	if(chunk){
		return zrtos_types__ptr_subtract(
			 zrtos_vheap_chunk__get_last_address(
				chunk
			)
			,sizeof(zrtos_task_t)
		);
	}
	return 0;
}

int pthread_join(pthread_t thread, void **retval){
	int ret = ESRCH;

	do{
		zrtos_task_t *task = pthread__get_task(thread);
		if(task){
			if(!zrtos_task__is_done(task)){
				zrtos_task_scheduler__delay_ms(0);
				continue;
			}
			*retval = zrtos_task__get_return_value(task);
			zrtos_vheap__free(
				 zrtos_task_scheduler__get_heap()
				,thread.id
			);
			ret = 0;
		}
		break;
	}while(1);

	return ret;
}

pthread_t pthread_self(void){

}

int pthread_mutex_lock(pthread_mutex_t *mutex){
	return zrtos_task_mutex__lock(&mutex->mutex);
}

int pthread_mutex_trylock(pthread_mutex_t *mutex){
	return zrtos_task_mutex__try_lock(&mutex->mutex);
}

int pthread_mutex_unlock(pthread_mutex_t *mutex){
	return zrtos_task_mutex__unlock(&mutex->mutex);
}


#ifdef __cplusplus
}
#endif
#endif