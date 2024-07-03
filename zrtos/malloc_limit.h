/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_MALLOC_LIMIT_H
#define ZRTOS_MALLOC_LIMIT_H
#ifdef __cplusplus
extern "C" {
#endif

#include <zrtos/malloc.h>

#ifdef ZRTOS_MALLOC__CFG_DISABLE_FREE
#error "ZRTOS_MALLOC__CFG_DISABLE_FREE not supported"
#endif

typedef struct _zrtos_malloc_limit_t{
	size_t length;
}zrtos_malloc_limit_t;

#define ZRTOS_MALLOC_LIMIT__INIT() {.length = 0}

void *zrtos_malloc_limit__malloc(
	 zrtos_malloc_limit_t *thiz
	,size_t length
	,size_t limit
){
	void *ret = 0;
	size_t len = thiz->length + length;
	if(len <= limit){
		ret = malloc(length);
		if(ret){
			thiz->length = len;
		}
	}
	return ret;
}

void zrtos_malloc_limit__free(zrtos_malloc_limit_t *thiz,void *ptr){
	thiz->length -= zrtos_malloc__get_length(ptr);
}


#ifdef __cplusplus
}
#endif
#endif