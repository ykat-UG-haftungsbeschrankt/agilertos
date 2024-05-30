/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VM_FUNCTION_INDEX_H
#define ZRTOS_VM_FUNCTION_INDEX_H
#ifdef __cplusplus
extern "C" {
#endif


#include "zrtos_types.h"
#include "zrtos_mem.h"
#include "zrtos_vm_function.h"

//#define ZRTOS_VM_FUNCTION_INDEX__CFG_ENABLE_PROGMEM
#define ZRTOS_VM_FUNCTION_INDEX(name,...) \
zrtos_vm_function_t name[] = { \
	 __VA_ARGS__ \
	,{} \
};

typedef struct _zrtos_vm_function_index_t{
	zrtos_vm_function_t *arr;
	size_t              length;
}zrtos_vm_function_index_t;

bool zrtos_vm_function_index__init(
	 zrtos_vm_function_index_t *thiz
	,zrtos_vm_function_t *arr
	,size_t length
){
	thiz->arr = arr;
	thiz->length = length;
	return true;
}

zrtos_vm_function_t *zrtos_vm_function_index__get_function(
	 zrtos_vm_function_index_t *thiz
	,zrtos_vm_function_id_t    id
){
	zrtos_vm_function_t key = {
		.id = id
	};
	return zrtos_mem__search(
		 &key
		,thiz->arr
		,thiz->length
		,sizeof(zrtos_vm_function_t)
		,zrtos_vm_function__cmp
	);
}


#ifdef __cplusplus
}
#endif
#endif