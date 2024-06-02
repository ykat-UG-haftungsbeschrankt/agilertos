/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_PTR_H
#define ZRTOS_PTR_H
#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>


#include "zrtos.h"
#include "zrtos_types.h"
#include "zrtos_mem.h"


typedef struct _zrtos_ptr_t{
	void    *ptr;
}zrtos_ptr_t;

typedef enum{
	 ZRTOS_PTR_TYPE__IS_FLASH = 0x0
	,ZRTOS_PTR_TYPE__IS_SRAM  = 0x1
	,ZRTOS_PTR_TYPE__MASK     = 0x1
}zrtos_ptr_type_t;

#define ZRTOS_PTR__FLASH(ptr)\
	({\
		zrtos_ptr_t ret;\
		zrtos_ptr__init(&ret,(ptr),ZRTOS_PTR_TYPE__IS_FLASH);\
		ret;\
	})

#define ZRTOS_PTR__SRAM(ptr)\
	({\
		zrtos_ptr_t ret;\
		zrtos_ptr__init(&ret,(ptr),ZRTOS_PTR_TYPE__IS_SRAM);\
		ret;\
	})

bool zrtos_ptr__init(zrtos_ptr_t *thiz,void *ptr,zrtos_ptr_type_t type){
	uintptr_t tmp = (uintptr_t)ptr;
	thiz->ptr = (void*)((tmp << 1) | type);
}

void *zrtos_ptr__get_ptr(zrtos_ptr_t *thiz,void *ptr,zrtos_ptr_type_t type){
	return (void*)(((uintptr_t)thiz->ptr) >> 1);
}

zrtos_ptr_type_t zrtos_ptr__get_type(zrtos_ptr_t *thiz){
	return (zrtos_ptr_type_t)(((uintptr_t)thiz->ptr) & ZRTOS_PTR_TYPE__MASK);
}


#ifdef __cplusplus
}
#endif
#endif