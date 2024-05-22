/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_EVENT_H
#define ZRTOS_EVENT_H
#ifdef __cplusplus
extern "C" {
#endif


#include "zrtos_types.h"
#include "zrtos_event_type.h"

struct _zrtos_event_index_t;

typedef struct _zrtos_event_t{
	zrtos_event_type_t          type;
	void                        *data;
}zrtos_event_t;

bool zrtos_event__init(
	 zrtos_event_t               *thiz
	,zrtos_event_type_t          type
	,void                        *data
){
	thiz->type = type;
	thiz->data = data;

	return true;
}

zrtos_event_type_t zrtos_event__get_type(
	zrtos_event_t *thiz
){
	return thiz->type;
}

void *zrtos_event__get_data(
	zrtos_event_t *thiz
){
	return thiz->data;
}

#ifdef __cplusplus
}
#endif
#endif