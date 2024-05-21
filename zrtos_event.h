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
#include "zrtos_event_message.h"
#include "zrtos_event_type.h"

struct _zrtos_event_index_t;

typedef struct _zrtos_event_t{
	struct _zrtos_event_index_t *index;
	zrtos_event_type_t          type;
	zrtos_event_message_t       *msg;
	//bool                      is_canceled;
}zrtos_event_t;

bool zrtos_event__init(
	 zrtos_event_t               *thiz
	,struct _zrtos_event_index_t *index
	,zrtos_event_type_t          type
	,zrtos_event_message_t       *msg
){
	thiz->index = index;
	thiz->type = type;
	thiz->msg = msg;
	//thiz->is_canceled = false;

	return true;
}

struct _zrtos_event_index_t *zrtos_event__get_index(
	zrtos_event_t *thiz
){
	return thiz->index;
}

zrtos_event_type_t *zrtos_event__get_type(
	zrtos_event_t *thiz
){
	return &thiz->type;
}

zrtos_event_message_t *zrtos_event__get_msg(
	zrtos_event_t *thiz
){
	return thiz->msg;
}
/*
bool zrtos_event__is_canceled(zrtos_event_t *thiz){
	return thiz->is_canceled;
}

zrtos_event_t *zrtos_event__set_canceled(
	zrtos_event_t *thiz
){
	thiz->is_canceled = true;
}
*/

#ifdef __cplusplus
}
#endif
#endif