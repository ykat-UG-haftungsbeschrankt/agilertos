/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_ERROR_COUNT_H
#define ZRTOS_ERROR_COUNT_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/error.h>

typedef struct _zrtos_error_count_t{
	size_t length;
}zrtos_error_count_t;

bool zrtos_error_count__init(zrtos_error_count_t *thiz){
	thiz->length = 0;
}

void zrtos_error_count__deinit(zrtos_error_count_t *thiz){
	thiz->length = 0;
}

bool zrtos_error_count__add(
	 zrtos_error_count_t *thiz
	,zrtos_error_t err
){
	if(zrtos_error__is_error(err)){
		thiz->length++;
	}
}

#ifdef __cplusplus
}
#endif
#endif