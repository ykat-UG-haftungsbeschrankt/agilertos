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
#include "zrtos_event.h"


typedef void (*zrtos_event_handler_callback_t)(
	 struct _zrtos_event_handler_t *thiz
	,struct _zrtos_event_handler_args_t *args
);

typedef struct _zrtos_event_handler_t{
	struct _zrtos_event_handler_t  *next;
	zrtos_event_handler_callback_t callback;
	zrtos_event_type_t             type;
	void                           *ctx;
}zrtos_event_handler_t;

typedef struct _zrtos_event_index_t{
	zrtos_event_handler_t *first;
}zrtos_event_index_t;

#define ZRTOS_EVENT_INDEX(name)\
    zrtos_event_index_t name = {};

#define ZRTOS_EVENT_INDEX__ADD_HANDLER(index,name,callback,type,ctx)\
    zrtos_event_handler_t name = {\
		 .next = ({\
			zrtos_event_handler_t *next = index.first ? index.first : &name;\
			index.first = &name;\
			next;\
		 })\
		,.callback = callback\
		,.type = type\
		,.ctx = ctx\
	};

bool zrtos_event_index__add_handler(
	 zrtos_event_index_t   *thiz
	,zrtos_event_handler_t *handler
){
	handler->next = thiz->first
	              ? thiz->first
	              : handler
	;
	thiz->first = handler;

	return true;
}

bool zrtos_event_index__remove_handler(
	 zrtos_event_index_t   *thiz
	,zrtos_event_handler_t *handler
){
	if(handler == handler->next){
		if(thiz->first == handler){
			thiz->first = 0;
		}
	}else{
		zrtos_event_handler_t *node = handler;
		while(node->next != handler){
			node = node->next;
		}
		node->next = handler->next;
	}
	handler->next = handler;

	return true;
}

bool zrtos_event_index__invoke_ex(
	 zrtos_event_index_t   *thiz
	,zrtos_event_type_t    type
	,zrtos_event_message_t *msg
){
	zrtos_event_t event;
	if(zrtos_event__init(
		 &event
		,thiz
		,type
		,msg
	)){
		zrtos_event_handler_t *node = thiz->first;

		for(zrtos_event_handler_t *next
			;node/* && !zrtos_event_handler_args__is_canceled(&args)*/
			;node = next
		){
			next = node->next;
			if(zrtos_event_type__is_any(&node->type)
			|| 0 == zrtos_event_type__cmp(&node->type,&type)){
				node->callback(node,&event);
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