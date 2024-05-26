/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VHEAP_TASK_PTHREAD_H
#define ZRTOS_VHEAP_TASK_PTHREAD_H
#ifdef __cplusplus
extern "C" {
#endif


#include "zrtos_error.h"
#include "zrtos_malloc.h"
#include "zrtos_task_scheduler.h"
#include "zrtos_task_mutex.h"
#include "zrtos_types.h"


typedef struct{
	size_t stacksize;
}pthread_attr_t;

typedef struct{
	zrtos_task_t *task;
}pthread_t;

typedef struct{
}pthread_mutexattr_t;

typedef struct{
	zrtos_task_mutex_t mutex;
}pthread_mutex_t;

typedef struct{
	void *(*callback)(void*args);
	void *args;
	void *return_value;
}zrtos_task_pthread__trampoline_cb_args_t;

#define PTHREAD_MUTEX_INITIALIZER              \
    {                                          \
        .mutex = ZRTOS_TASK_MUTEX__INITIALIZER \
    }

	
void *zrtos_task_pthread__heap;

void *zrtos_task_pthread__get_heap(void){
	return zrtos_task_pthread__heap;
}

void zrtos_task_pthread__set_heap(void *heap){
	zrtos_task_pthread__heap = heap;
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
	return zrtos_task_mutex__init(&mutex->mutex) ? 0 : EINVAL;
}

int pthread_mutex_destroy(pthread_mutex_t *mutex){
	zrtos_task_mutex__deinit(&mutex->mutex);
	return 0;
}

pthread_t pthread_self(void){
	pthread_t ret;
	ret.task = _zrtos_task_scheduler__get_active_task();
	return ret;
}

__attribute__((noreturn)) void zrtos_task_pthread__trampoline_cb(void *args){
	zrtos_task_pthread__trampoline_cb_args_t *tmp_args = args;
	zrtos_task_t *task = zrtos_types__ptr_subtract(
		 tmp_args
		,sizeof(zrtos_task_t)
	);;
	tmp_args->return_value = tmp_args->callback(tmp_args->args);
	zrtos_task__set_done(task);

	_zrtos_task_scheduler__on_tick_ex();

	__builtin_unreachable();
	while(1){
		//should not return
	}
}

int pthread_create(
	 pthread_t *restrict thread
	,const pthread_attr_t *restrict attr
	,void *(*start_routine)(void *)
	,void *restrict arg
){
	int ret = ENOMEM;

	ZRTOS_TASK_SCHEDULER__DO_NOT_DISTURB({
		size_t stack_size_min = ZRTOS_ARCH__GET_CPU_STATE_BUFFER_LENGTH()
		                      + ZRTOS_ARCH__GET_FN_CALL_STACK_LENGTH()
		;
		zrtos_malloc_t *mem = (zrtos_malloc_t*)zrtos_task_pthread__get_heap();
		size_t stacksize_min = sizeof(zrtos_task_t)
		                     + sizeof(zrtos_task_pthread__trampoline_cb_args_t)
		                     + (
			attr
			? ZRTOS_TYPES__MAX(
				stack_size_min
				,attr->stacksize
			)
			: stack_size_min
		);
		zrtos_task_t *task = zrtos_malloc__malloc(
			mem
			,stacksize_min
		);
		if(task){
			void *mem_chunk_last_address = zrtos_types__ptr_add(
				 task
				,stacksize_min-1
			);
			zrtos_task_pthread__trampoline_cb_args_t *args = zrtos_types__ptr_add(
				 task
				,sizeof(zrtos_task_t)
			);
			args->callback = start_routine;
			args->args = arg;
			zrtos_task__init_ex(
				 task
				,(zrtos_arch_stack_t*)mem_chunk_last_address
				,zrtos_task_pthread__trampoline_cb
				,args
			);
			zrtos_task_scheduler__add_task(task);

			thread->task = task;
			ret = 0;
		}
	});

	return ret;
}

int pthread_equal(pthread_t t1, pthread_t t2){
	return zrtos_types__ptr_cmp(t1.task,t1.task);
}

static void zrtos_task_pthread__free(zrtos_task_t *task){
	zrtos_task_t *child;

	while((child = zrtos_task_scheduler__get_any_child(task))){
		zrtos_task_t *last = child;
		while((child = zrtos_task_scheduler__get_any_child(child))){
			last = child;
		}
		zrtos_task_scheduler__remove_task(last);
		zrtos_malloc__free(last);
	}

	zrtos_task_scheduler__remove_task(task);
	zrtos_malloc__free(task);
}

int pthread_join(pthread_t thread, void **retval){
	int ret = EAGAIN;
	zrtos_task_t *task = thread.task;

	while(true){
		ZRTOS_TASK_SCHEDULER__DO_NOT_DISTURB({
			if(zrtos_task_scheduler__has_task(task)){
				if(zrtos_task__is_done(task)){
					zrtos_task_pthread__trampoline_cb_args_t *args = 
						(zrtos_task_pthread__trampoline_cb_args_t *)(task+1)
					;
					if(retval){
						*retval = args->return_value;
					}
					zrtos_task_pthread__free(task);
					ret = 0;
				}
			}else{
				ret = ESRCH;
			}
		});
		
		if(ret == EAGAIN){
			_zrtos_task_scheduler__on_tick_ex();
		}else{
			break;
		}
	}

	return ret;
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