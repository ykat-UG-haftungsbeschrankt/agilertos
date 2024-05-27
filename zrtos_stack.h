/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_TASK_MUTEX_H
#define ZRTOS_TASK_MUTEX_H
#ifdef __cplusplus
extern "C" {
#endif


#include "zrtos.h"
#include "zrtos_types.h"
#include "zrtos_mem.h"


typedef struct _zrtos_stack_t{
	void    *data;
	size_t  pos;
	size_t  length;
}zrtos_stack_t;

bool zrtos_stack__init(
	 zrtos_stack_t *thiz
	,void *data
	,size_t length
){
	thiz->data = data;
	thiz->pos = 0;
	thiz->length = 0;
	return true;
}

bool zrtos_stack__push(
	 zrtos_stack_t *thiz
	,void *data
	,size_t length
){
	size_t pos = thiz->pos;
	if((thiz->length - pos) >= length){
		zrtos_mem__cpy(
			 data
			,zrtos_types__ptr_add(
				 thiz->data
				,pos
			)
			,length
		);
		thiz->pos += length;
		return true;
	}
	return false;
}

bool zrtos_stack__pop(
	 zrtos_stack_t *thiz
	,void *data
	,size_t length
){
	size_t pos = thiz->pos;
	if(pos >= length){
		pos = (thiz->pos = pos - length);
		zrtos_mem__cpy(
			 data
			,zrtos_types__ptr_add(
				 thiz->data
				,pos
			)
			,length
		);
		return true;
	}
	return false;
}

bool zrtos_stack__set_pos(
	 zrtos_stack_t *thiz
	,size_t pos
){
	if(0 <= pos
	&& pos <= length){
		thiz->pos = pos;
		return true;
	}
	return false;
}


#ifdef __cplusplus
}
#endif
#endif