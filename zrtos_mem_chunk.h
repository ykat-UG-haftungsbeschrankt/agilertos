/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_MEM_CHUNK_H
#define ZRTOS_MEM_CHUNK_H
#ifdef __cplusplus
extern "C" {
#endif


#include "zrtos_mem_chunk_uid.h"
#include "zrtos_mem_chunk_type.h"


typedef struct _zrtos_mem_chunk_t{
	char                    first[2];
	void                       *ptr;
	size_t                     length;
	zrtos_mem_chunk_type_t     type;
	zrtos_mem_chunk_uid_t      uid;
	char                    last[2];
}__attribute__((aligned(ZRTOS__BYTE_ALIGNMENT)))zrtos_mem_chunk_t;

void *zrtos_mem_chunk__get_ptr(zrtos_mem_chunk_t *thiz){
	return thiz->ptr;
}

size_t zrtos_mem_chunk__get_length(zrtos_mem_chunk_t *thiz){
	return thiz->length;
}

zrtos_mem_chunk_uid_t zrtos_mem_chunk__get_uid(zrtos_mem_chunk_t *thiz){
	return thiz->uid;
}

zrtos_mem_chunk_type_t *zrtos_mem_chunk__get_type(zrtos_mem_chunk_t *thiz){
	return &thiz->type;
}


#ifdef __cplusplus
}
#endif
#endif