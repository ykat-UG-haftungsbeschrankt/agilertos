/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_EVENT_HANDLER_H
#define ZRTOS_EVENT_HANDLER_H
#ifdef __cplusplus
extern "C" {
#endif


#include "zrtos_types.h"

struct _zrtos_event_t;
struct _zrtos_event_handler_t;
 
typedef bool (*zrtos_event_handler_callback_t)(
	 struct _zrtos_event_handler_t *thiz
	,struct _zrtos_event_t         *args
);

typedef struct _zrtos_event_handler_t{
	zrtos_event_handler_callback_t callback;
	zrtos_event_type_t             type;
	void                           *ctx;
}zrtos_event_handler_t;

#define ZRTOS_EVENT_HANDLER(callback_,type_,ctx_) \
    {                                             \
         .callback=callback_                      \
        ,.type=type_                              \
        ,.ctx=ctx_                                \
    }


#ifdef __cplusplus
}
#endif
#endif