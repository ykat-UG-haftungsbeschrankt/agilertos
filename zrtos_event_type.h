/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_EVENT_TYPE_H
#define ZRTOS_EVENT_TYPE_H
#ifdef __cplusplus
extern "C" {
#endif


#include "zrtos_types.h"


bool zrtos_event_type__cmp(zrtos_event_type_t *a,zrtos_event_type_t *b){
	return *a - *b;
}

bool zrtos_event_type__is_any(zrtos_event_type_t *thiz){
	return *thiz == ZRTOS_EVENT_TYPE__ANY;
}

#define ZRTOS_EVENT_TYPE__ENUM(...)\
    typedef enum{\
		 ZRTOS_EVENT_TYPE__ANY = 0\
		,__VA_ARGS__\
	}zrtos_event_type_t;


#ifdef __cplusplus
}
#endif
#endif