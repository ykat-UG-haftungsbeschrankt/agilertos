/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VM_FUNCTION_H
#define ZRTOS_VM_FUNCTION_H
#ifdef __cplusplus
extern "C" {
#endif


#include "zrtos_types.h"
#include "zrtos_error.h"

typedef size_t zrtos_vm_function_id_t;
struct _zrtos_vm_function_t;

typedef zrtos_error_t (*zrtos_vm_function_callback_t)(
	 struct _zrtos_vm_t          *vm
	,struct _zrtos_vm_function_t *fn
);

typedef struct _zrtos_vm_function_t{
	zrtos_vm_function_id_t       id;
	zrtos_vm_function_callback_t callback;
	void                         *context;
}zrtos_vm_function_t;

#define ZRTOS_VM_FUNCTION(id_,callback_,context_) \
    {                                             \
         .id=id_                                  \
        ,.callback=callback_                      \
        ,.context=context_                        \
    }

int zrtos_vm_function__cmp(const void *aa,const void *bb){
	const zrtos_vm_function_t *a = (const zrtos_vm_function_t *)aa;
	const zrtos_vm_function_t *b = (const zrtos_vm_function_t *)bb;
	return a->id - b->id;
}

zrtos_vm_function_callback_t zrtos_vm_function__get_callback(
	zrtos_vm_function_t *thiz
){
	return thiz->callback;
}

void *zrtos_vm_function__get_context(
	zrtos_vm_function_t *thiz
){
	return thiz->context;
}


#ifdef __cplusplus
}
#endif
#endif