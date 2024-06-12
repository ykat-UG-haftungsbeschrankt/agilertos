/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_DEBUG_H
#define ZRTOS_DEBUG_H
#ifdef __cplusplus
extern "C" {
#endif

#ifdef ZRTOS_DEBUG__CFG_ENABLED

#include <zrtos/types.h>

#ifdef ZRTOS_DEBUG__CFG_MEMORY_CONSOLE
# if ZRTOS_DEBUG__CFG_MEMORY_CONSOLE > 0
#  include <zrtos/debug_console.h>
   ZRTOS_DEBUG_CONSOLE__INIT(zrtos_debug__memory_console,ZRTOS_DEBUG__CFG_MEMORY_CONSOLE);
#  define ZRTOS_DEBUG(fmt,...)\
       zrtos_debug_console__printf(&zrtos_debug__memory_console,fmt,##__VA_ARGS__)
# else
#  define ZRTOS_DEBUG(fmt,...)
# endif
#else
# define ZRTOS_DEBUG(fmt,...)
#endif

#ifdef ZRTOS__USE_MEMSET
#define zrtos_debug__memset memset
#else
void *zrtos_debug__memset(void *dest,int value, size_t n){
	register uint8_t *ptr = (uint8_t *) dest;
	register uint8_t val = value;
	while(n--){
		*ptr++ = val;
	}
	return dest;
}
#endif

#define ZRTOS_DEBUG__CODE(code) code

#else

#define ZRTOS_DEBUG__CODE(code)
#define ZRTOS_DEBUG(fmt,...)

#endif

#ifdef __cplusplus
}
#endif
#endif