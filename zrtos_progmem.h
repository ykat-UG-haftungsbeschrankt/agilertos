/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_PROGMEM_H
#define ZRTOS_PROGMEM_H
#ifdef __cplusplus
extern "C" {
#endif

#if !defined(ZRTOS_PROGMEM__CFG_ENABLED) || !defined(ZRTOS_ARCH__HAS_PROGMEM)

# include "zrtos_mem.h"
# define ZRTOS_PROGMEM
bool zrtos_progmem__cpy(void *dest,void *src,size_t len){
	memcpy(dest,src,len);
}

#else

# define ZRTOS_PROGMEM ZRTOS_ARCH__PROGMEM
bool zrtos_progmem__cpy(void *dest,void *src,size_t len){
	ZRTOS_ARCH__PROGMEM_CPY(dest,src,len);
}

#endif

#ifdef __cplusplus
}
#endif
#endif