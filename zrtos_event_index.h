/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_EVENT_INDEX_H
#define ZRTOS_EVENT_INDEX_H
#ifdef __cplusplus
extern "C" {
#endif


#include "zrtos_types.h"
#include "zrtos_event_message.h"
#include "zrtos_event_type.h"
#include "zrtos_event_handler.h"
#include "zrtos_event.h"
#include "zrtos_clist.h"
#include "zrtos_assert.h"


#define ZRTOS_EVENT_INDEX(name,...) \
zrtos_event_handler_t name[] = { \
	 __VA_ARGS__ \
	,{} \
};

typedef zrtos_event_handler_t zrtos_event_index_t;

bool zrtos_event_index__invoke_ex(
	 zrtos_event_index_t   *thiz
	,zrtos_event_type_t    type
	,zrtos_event_message_t *msg
){
	zrtos_event_t event;
	if(zrtos_event__init(
		 &event
		,type
		,msg
	)){
		zrtos_event_handler_t *handler = (zrtos_event_handler_t *)thiz;
		for(;handler->callback;handler++){
			if(zrtos_event_type__is_any(&handler->type)
			|| 0 == zrtos_event_type__cmp(&handler->type,&event.type)){
				if(!handler->callback(handler,&event)){
					break;
				}
			}
		}
		return true;
	}
	return false;
}

bool zrtos_event_index__invoke(
	 zrtos_event_index_t *thiz
	,zrtos_event_type_t  type
	,void                *data
	,size_t              length
){
	zrtos_event_message_t msg;
	return zrtos_event_message__init(
		 &msg
		,data
		,length
	) && zrtos_event_index__invoke_ex(
		 thiz
		,type
		,&msg
	);
}


#ifdef __cplusplus
}
#endif
#endif