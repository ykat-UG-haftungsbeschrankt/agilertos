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


typedef size_t zrtos_event_type_t;

bool zrtos_event_type__cmp(zrtos_event_type_t *a,zrtos_event_type_t *b){
	return *a - *b;
}

bool zrtos_event_type__is_any(zrtos_event_type_t *thiz){
	return *thiz == 0;
}


#ifdef __cplusplus
}
#endif
#endif