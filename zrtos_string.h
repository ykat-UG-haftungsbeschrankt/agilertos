/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_EVENT_MESSAGE_H
#define ZRTOS_EVENT_MESSAGE_H
#ifdef __cplusplus
extern "C" {
#endif


#include "zrtos_types.h"


typedef struct _zrtos_string_t{
	char   *data;
	size_t length;
}zrtos_string_t;

bool zrtos_string__init(
	 zrtos_string_t *thiz
	,char *data
	,size_t length
){
	thiz->data = data;
	thiz->length = length;
	return true;
}

char *zrtos_string__get_data(zrtos_string_t *thiz){
	return thiz->data;
}

size_t zrtos_string__get_length(zrtos_string_t *thiz){
	return thiz->length;
}


#ifdef __cplusplus
}
#endif
#endif