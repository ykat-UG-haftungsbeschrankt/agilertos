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
#include "zrtos_clist.h"


struct _zrtos_event_handler_t;
 
typedef void (*zrtos_event_handler_callback_t)(
	 struct _zrtos_event_handler_t *thiz
	,struct _zrtos_event_t         *args
);

typedef struct _zrtos_event_handler_t{
	zrtos_clist_node_t             node;
	zrtos_event_handler_callback_t callback;
	zrtos_event_type_t             type;
	void                           *ctx;
}zrtos_event_handler_t;

typedef struct _zrtos_event_index_t{
	zrtos_clist_t root;
}zrtos_event_index_t;

#define ZRTOS_EVENT_INDEX(name)\
    zrtos_event_index_t name = {};

#define ZRTOS_EVENT_INDEX__ADD_HANDLER(index,name,callback,type,ctx)           \
    zrtos_event_handler_t name = {                                             \
         .next = ({                                                            \
            zrtos_event_handler_t *next = (index).root ? (index).root : &name; \
            (index).root = &name;                                              \
            next;                                                              \
         })                                                                    \
        ,.callback = (callback)                                                \
        ,.type = (type)                                                        \
        ,.ctx = (ctx)                                                          \
    };

bool zrtos_event_index__add_handler(
	 zrtos_event_index_t   *thiz
	,zrtos_event_handler_t *handler
){
	return zrtos_clist__push(
		 &thiz->root
		,&handler->node
	);
}

bool zrtos_event_index__remove_handler(
	 zrtos_event_index_t   *thiz
	,zrtos_event_handler_t *handler
){
	return zrtos_clist__delete(
		 &thiz->root
		,&handler->node
	);
}

static bool zrtos_event_index__invoke_ex_cb(
	 zrtos_clist_node_t *node
	,void               *arg
){
	zrtos_event_handler_t *handler = zrtos_types__get_container_of(
		 node
		,zrtos_event_handler_t
		,node
	);
	zrtos_event_t *event = (zrtos_event_t*)arg;

	if(zrtos_event_type__is_any(&handler->type)
	|| 0 == zrtos_event_type__cmp(&handler->type,&event->type)){
		handler->callback(handler,event);
	}

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
		zrtos_clist__each(
			 &thiz->root
			,zrtos_event_index__invoke_ex_cb
			,&event
		);
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