/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_DEBUG_CONSOLE_H
#define ZRTOS_DEBUG_CONSOLE_H
#ifdef __cplusplus
extern "C" {
#endif

#ifdef ZRTOS_DEBUG__CFG_ENABLED

#include "zrtos_types.h"
#include "zrtos_str.h"

#define ZRTOS_DEBUG_CONSOLE__INIT(name,length)\
	uint8_t name##_buffer[length];\
	zrtos_debug_console_t name = {\
		 .buffer = name##_buffer\
		,.ptr = name##_buffer\
		,.buffer_length = sizeof(name##_buffer)/sizeof(name##_buffer[0])\
	};

typedef struct _zrtos_debug_console_t{
	uint8_t *buffer;
	uint8_t *ptr;
	size_t buffer_length;
}zrtos_debug_console_t;

void zrtos_debug_console__put_char(zrtos_debug_console_t *thiz,char c){
	if(thiz->ptr > thiz->buffer + thiz->buffer_length){
		thiz->ptr = thiz->buffer;
	}
	*thiz->ptr++ = c;
}

void zrtos_debug_console__printf_callback(void *args,char c){
	zrtos_debug_console__put_char((zrtos_debug_console_t *)args,c);
}

void zrtos_debug_console__printf(
	 zrtos_debug_console_t *thiz
	,char const *fmt
	,...
){
	va_list arg;
	va_start(arg, fmt);
	zrtos_str__vsnprintf_internal(
		 zrtos_debug_console__printf_callback
		,(void*)thiz
		,fmt
		,arg
	);
	va_end(arg);
}

#endif

#ifdef __cplusplus
}
#endif
#endif