/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_TASK_MUTEX_H_
#define ZRTOS_TASK_MUTEX_H_
#ifdef __cplusplus
extern "C" {
#endif


#include "zrtos_error.h"


typedef struct _zrtos_task_mutex_t{
	bool is_locked;
}zrtos_task_mutex_t;

#define ZRTOS_MUTEX__INIT() {.is_locked = 0};

bool zrtos_task_mutex__init(zrtos_task_mutex_t *thiz){
	thiz->is_locked = false;
	return true;
}

void zrtos_task_mutex__deinit(zrtos_task_mutex_t *thiz){
	
}

int zrtos_task_mutex__try_lock(zrtos_task_mutex_t *thiz){
	int ret = EBUSY;
	ZRTOS__DO_NOT_DISTURB_EX({
		if(thiz->is_locked == false){
			thiz->is_locked = true;
			ret = 0;
		}
	});
	return ret;
}

int zrtos_task_mutex__lock(zrtos_task_mutex_t *thiz){
	bool ret = true;
	bool is_locked;
	uint8_t limit = 0xFF;
	do{
		ZRTOS__DO_NOT_DISTURB_EX(is_locked,{
			if(thiz->is_locked == false){
				thiz->is_locked = true;
				ret = false;
			}
		});
		if(ret){
			zrtos_task_scheduler__delay_ms(0);
		}
	}while(ret && !is_locked && limit--);
	return ret;
}

int zrtos_task_mutex__unlock(zrtos_task_mutex_t *thiz){
	ZRTOS__DO_NOT_DISTURB({
		thiz->is_locked = false;
	});
	return 0;
}


#ifdef __cplusplus
}
#endif
#endif