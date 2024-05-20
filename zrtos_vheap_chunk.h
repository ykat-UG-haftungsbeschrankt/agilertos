/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VHEAP_CHUNK_H
#define ZRTOS_VHEAP_CHUNK_H
#ifdef __cplusplus
extern "C" {
#endif


#include "zrtos_vheap_chunk_uid.h"
#include "zrtos_vheap_chunk_type.h"


typedef struct _zrtos_vheap_chunk_t{
	char                    first[2];
	void                       *ptr;
	size_t                     length;
	zrtos_vheap_chunk_type_t     type;
	zrtos_vheap_chunk_uid_t      uid;
	char                    last[2];
}__attribute__((aligned(ZRTOS_ARCH__BYTE_ALIGNMENT)))zrtos_vheap_chunk_t;

void *zrtos_vheap_chunk__get_ptr(zrtos_vheap_chunk_t *thiz){
	return thiz->ptr;
}

size_t zrtos_vheap_chunk__get_length(zrtos_vheap_chunk_t *thiz){
	return thiz->length;
}

zrtos_vheap_chunk_uid_t zrtos_vheap_chunk__get_uid(zrtos_vheap_chunk_t *thiz){
	return thiz->uid;
}

zrtos_vheap_chunk_type_t *zrtos_vheap_chunk__get_type(zrtos_vheap_chunk_t *thiz){
	return &thiz->type;
}

void *zrtos_vheap_chunk__get_last_address(zrtos_vheap_chunk_t *thiz){
	return zrtos_types__ptr_add(
		 zrtos_vheap_chunk__get_ptr(thiz)
		,zrtos_vheap_chunk__get_length(thiz)
	);
}

#ifdef __cplusplus
}
#endif
#endif