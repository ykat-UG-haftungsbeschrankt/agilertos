/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_MEM_CHUNK_TYPE_H
#define ZRTOS_MEM_CHUNK_TYPE_H
#ifdef __cplusplus
extern "C" {
#endif


#include "zrtos_mem_type.h"

typedef struct _zrtos_mem_chunk_type_t{
	zrtos_mem_type_t type;
}zrtos_mem_chunk_type_t;

bool zrtos_mem_chunk_type__init(
	 zrtos_mem_chunk_type_t *thiz
	,zrtos_mem_type_t       type
){
	thiz->type = type;
	return true;
}

bool zrtos_mem_chunk_type__is_eq(
	 zrtos_mem_chunk_type_t *thiz
	,zrtos_mem_type_t       type
){
	return thiz->type == type;
}


#ifdef __cplusplus
}
#endif
#endif