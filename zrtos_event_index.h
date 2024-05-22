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
#include "zrtos_progmem.h"
#include "zrtos_event_type.h"
#include "zrtos_event_handler.h"
#include "zrtos_event.h"

//#define ZRTOS_EVENT_INDEX__CFG_ENABLE_PROGMEM
#define ZRTOS_EVENT_INDEX(name,...) \
zrtos_event_handler_t name[] ZRTOS_PROGMEM = { \
	 __VA_ARGS__ \
	,{} \
};

typedef zrtos_event_handler_t zrtos_event_index_t;

bool zrtos_event_index__invoke(
	 zrtos_event_index_t   *thiz
	,zrtos_event_type_t    type
	,void                  *data
){
	zrtos_event_t event;
	if(zrtos_event__init(
		 &event
		,type
		,data
	)){
#ifndef ZRTOS_EVENT_INDEX__CFG_ENABLE_PROGMEM
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
#else
		zrtos_event_handler_t *phandler = (zrtos_event_handler_t *)thiz;
		while(1){
			zrtos_event_handler_t handler;
			zrtos_progmem__cpy(&handler,phandler++,sizeof(zrtos_event_handler_t));
			if(handler.callback){
				if(zrtos_event_type__is_any(&handler.type)
				|| 0 == zrtos_event_type__cmp(&handler.type,&event.type)){
					if(!handler.callback(&handler,&event)){
						break;
					}
				}
			}else{
				break;
			}
		}
		return true;
#endif
	}
	return false;
}


#ifdef __cplusplus
}
#endif
#endif