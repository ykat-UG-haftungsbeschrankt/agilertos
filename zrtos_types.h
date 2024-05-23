/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_TYPES_H
#define ZRTOS_TYPES_H
#ifdef __cplusplus
extern "C" {
#endif


#include <stdbool.h>
#include <stddef.h>
#include <limits.h>

typedef uint16_t size_t;
typedef int16_t ssize_t;
/*
typedef enum{
	false
	,true
}bool;
*/

int zrtos_types__ptr_cmp(void *a,void *b){
	return ((ptrdiff_t)a)-((ptrdiff_t)b);
}

void *zrtos_types__ptr_add(void *ptr,size_t byte_len){
	return ((uint8_t*)ptr)+byte_len;
}

void *zrtos_types__ptr_subtract(void *ptr,size_t byte_len){
	return ((uint8_t*)ptr)-byte_len;
}

size_t zrtos_types__ptr_get_byte_distance(void *bigger,void *smaller){
	return ((uint8_t*)bigger)-((uint8_t*)smaller);
}

#define zrtos_types__get_offset_of(type,member) \
    __builtin_offsetof(type,member)

#define zrtos_types__get_container_of(ptr, type, member)                    \
    ({                                                                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);                \
        (type *)((char *)__mptr - zrtos_types__get_offset_of(type,member)); \
    })

#define ZRTOS_TYPES__MIN(a,b) ((a)<(b)?(a):(b))
#define ZRTOS_TYPES__MAX(a,b) ((a)>(b)?(a):(b))

#define ZRTOS_TYPES__SWAP_PTR_CONTENTS(a,b) \
    do{                                     \
        typeof(*a) a____ = *(a);            \
        *(a) = *(b);                        \
        *(b) = a____;                       \
    }while(0);

#define ZRTOS_TYPES__NO_ADD_OVERFLOW(a,b) \
    (((a + b ) >= a))

#define ZRTOS_TYPES__GET_STATIC_ARRAY_LENGTH(arr) \
    (sizeof(arr)/sizeof((arr)[0]))

#ifdef __cplusplus
}
#endif
#endif