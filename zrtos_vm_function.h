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

 
typedef zrtos_error_t (*zrtos_vm_function_callback_t)(
	 struct _zrtos_vm_function_t *thiz
	,struct _zrtos_vm_function_t         *args
);

typedef struct _zrtos_vm_function_t{
	zrtos_vm_function_id_t       id;
	zrtos_vm_function_callback_t callback;
	void                         *ctx;
}zrtos_vm_function_t;

#define ZRTOS_VM_FUNCTION(id_,callback_,ctx_)     \
    {                                             \
         .id=id_                                  \
        ,.callback=callback_                      \
        ,.ctx=ctx_                                \
    }

zrtos_vm_function_callback_t zrtos_vm_function__get_callback(
	zrtos_vm_function_t *thiz
){
	return thiz->callback;
}

void *zrtos_vm_function__get_context(
	zrtos_vm_function_t *thiz
){
	return thiz->ctx;
}


#ifdef __cplusplus
}
#endif
#endif