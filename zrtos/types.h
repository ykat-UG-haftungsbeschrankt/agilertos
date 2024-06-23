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
#include <stdint.h>
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

#define ZRTOS_TYPES__BYTE_ALIGNMENT (sizeof(max_align_t))
#define ZRTOS_TYPES__BYTE_ALIGNMENT_MASK (sizeof(max_align_t)-1)

void *zrtos_types__ptr_to_alignment(void *ptr){
	uintptr_t ret = (uintptr_t)ptr;
	ret = ret
	    + ZRTOS_TYPES__BYTE_ALIGNMENT
	    - (ret & ZRTOS_TYPES__BYTE_ALIGNMENT_MASK)
	;
	return (void*)ret;
}

size_t zrtos_types__ceil_size_to_alignment(size_t len){
	return len
	     + ZRTOS_TYPES__BYTE_ALIGNMENT
	     - (len & ZRTOS_TYPES__BYTE_ALIGNMENT_MASK)
	;
}

#define zrtos_types__get_offset_of(type,member) \
    __builtin_offsetof(type,member)

#define zrtos_types__get_container_of(ptr, type, member)                    \
    ({                                                                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);                \
        (type *)((char *)__mptr - zrtos_types__get_offset_of(type,member)); \
    })

#define zrtos_types__get_container_of_ex(ptr, type, member)                 \
    ((ptr) ? zrtos_types__get_container_of(ptr, type, member) : 0)          \

#define ZRTOS_TYPES__MIN(a,b) ((a)<(b)?(a):(b))
#define ZRTOS_TYPES__MAX(a,b) ((a)>(b)?(a):(b))
#define  ZRTOS_TYPES__CMP(type,a_len,b_len)\
	((a_len) < (b_len) ? - 1 : ((a_len) > (b_len) ? 1 : 0))

bool zrtos_types__uint32_is_valid_address_range(
	 uint32_t first_address
	,uint32_t last_address
	,uint32_t offset
	,size_t *length
){
	if(offset >= first_address
	&& offset <= last_address){
		*length = ZRTOS_TYPES__MIN(
			 *length
			,last_address - offset
		);
		return true;
	}
	return false;
}

bool zrtos_types__ptr_is_valid_address_range(
	 void *first_address
	,void *last_address
	,size_t offset
	,size_t *length
){
	if(offset <= zrtos_types__ptr_get_byte_distance(
		 last_address
		,first_address
	)){
		*length = ZRTOS_TYPES__MIN(
			 *length
			,zrtos_types__ptr_get_byte_distance(
				 last_address
				,zrtos_types__ptr_subtract(
					 last_address
					,offset
				)
			)
		);
		return true;
	}
	return false;
}

bool zrtos_types__uint64_is_valid_address_range(
	 uint64_t first_address
	,uint64_t last_address
	,uint64_t offset
	,size_t *length
){
	if(offset >= first_address
	&& offset <= last_address){
		*length = ZRTOS_TYPES__MIN(
			 *length
			,last_address - offset
		);
		return true;
	}
	return false;
}

#ifdef __cplusplus
#define ZRTOS_TYPES__SWAP(a,b)              \
    do{                                     \
        auto a____ = (a);                   \
        (a) = (b);                          \
        (b) = a____;                        \
    }while(0);

#define ZRTOS_TYPES__SWAP_PTR_CONTENTS(a,b) \
    do{                                     \
        auto a____ = *(a);                  \
        *(a) = *(b);                        \
        *(b) = a____;                       \
    }while(0);
#else
#define ZRTOS_TYPES__SWAP(a,b)              \
    do{                                     \
        typeof(a) a____ = (a);              \
        (a) = (b);                          \
        (b) = a____;                        \
    }while(0);

#define ZRTOS_TYPES__SWAP_PTR_CONTENTS(a,b) \
    do{                                     \
        typeof(*a) a____ = *(a);            \
        *(a) = *(b);                        \
        *(b) = a____;                       \
    }while(0);
#endif

#define ZRTOS_TYPES__IS_ADD_OVERFLOW(a,b) \
    (((a + b ) < a))

#define ZRTOS_TYPES__GET_STATIC_ARRAY_LENGTH(arr) \
    (sizeof(arr)/sizeof((arr)[0]))

#define ZRTOS_TYPES__SIZE_MAX SIZE_MAX
#define ZRTOS_TYPES__UINT32_MAX UINT32_MAX

size_t zrtos_types__uint8_to_hex(uint8_t *dest,uint8_t src){
	uint8_t h = (src & 0xF) + '0';
	uint8_t l = (src >> 4) + '0';

	if(h > '9'){
		h += 'A' - '9';
	}
	if(l > '9'){
		l += 'A' - '9';
	}

	dest[0] = h;
	dest[1] = l;

	return 2;
}


#ifdef __cplusplus
}
#endif
#endif