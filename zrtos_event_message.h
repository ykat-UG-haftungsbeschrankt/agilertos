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


#include "zrtos_string.h"


typedef struct _zrtos_event_message_t{
	zrtos_string_t data;
}zrtos_event_message_t;

bool zrtos_event_message__init(
	 zrtos_event_message_t *thiz
	,void *data
	,size_t length
){
	return zrtos_string__init(
		 &thiz->data
		,data
		,length
	);
}

void *zrtos_event_message__get_data(zrtos_event_message_t *thiz){
	return zrtos_string__get_data(&thiz->data);
}

size_t zrtos_event_message__get_length(zrtos_event_message_t *thiz){
	return zrtos_string__get_length(&thiz->data);
}


#ifdef __cplusplus
}
#endif
#endif