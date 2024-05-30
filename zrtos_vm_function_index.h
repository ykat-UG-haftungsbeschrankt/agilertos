/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VM_FUNCTION_INDEX_H
#define ZRTOS_VM_FUNCTION_INDEX_H
#ifdef __cplusplus
extern "C" {
#endif


#include "zrtos_types.h"
#include "zrtos_progmem.h"
#include "zrtos_vm_function.h"

//#define ZRTOS_VM_FUNCTION_INDEX__CFG_ENABLE_PROGMEM
#define ZRTOS_VM_FUNCTION_INDEX(name,...) \
zrtos_vm_function_t name[] ZRTOS_PROGMEM = { \
	 __VA_ARGS__ \
	,{} \
};



bool zrtos_vm_function_index__get_function(
	 zrtos_vm_function_index_t *thiz
	,zrtos_vm_function_id_t    id
){
	zrtos_event_t event;
	if(zrtos_event__init(
		 &event
		,type
		,data
	)){
#ifndef ZRTOS_VM_FUNCTION_INDEX__CFG_ENABLE_PROGMEM
		zrtos_vm_function_t *handler = (zrtos_vm_function_t *)thiz;
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
		zrtos_vm_function_t *phandler = (zrtos_vm_function_t *)thiz;
		while(1){
			zrtos_vm_function_t handler;
			zrtos_progmem__cpy(&handler,phandler++,sizeof(zrtos_vm_function_t));
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

bool zrtos_vm_function__invoke(
	 zrtos_vm_function_index_t   *thiz
	,void                        *data
){
	zrtos_event_t event;
	if(zrtos_event__init(
		 &event
		,type
		,data
	)){
#ifndef ZRTOS_VM_FUNCTION_INDEX__CFG_ENABLE_PROGMEM
		zrtos_vm_function_t *handler = (zrtos_vm_function_t *)thiz;
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
		zrtos_vm_function_t *phandler = (zrtos_vm_function_t *)thiz;
		while(1){
			zrtos_vm_function_t handler;
			zrtos_progmem__cpy(&handler,phandler++,sizeof(zrtos_vm_function_t));
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