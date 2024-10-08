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
#include <stdalign.h>

#include <zrtos/cast.h>

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

#define ZRTOS_TYPES__BYTE_ALIGNMENT (__alignof__(max_align_t))
#define ZRTOS_TYPES__BYTE_ALIGNMENT_MASK (__alignof__(max_align_t)-1)

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
        typeof( ((type *)0)->member ) *mptr__ = (typeof( ((type *)0)->member ) *)(ptr);         \
        (type *)((char *)mptr__ - zrtos_types__get_offset_of(type,member)); \
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
#define ZRTOS_TYPES__TYPEOF(a) auto
#else
#define ZRTOS_TYPES__TYPEOF(a) typeof(a)
#endif

#define ZRTOS_TYPES__SWAP(a,b)                    \
    do{                                           \
        ZRTOS_TYPES__TYPEOF(a) a____ = (a);       \
        (a) = (b);                                \
        (b) = a____;                              \
    }while(0);

#define ZRTOS_TYPES__SWAP_PTR_CONTENTS(a,b)   \
    do{                                       \
        ZRTOS_TYPES__TYPEOF(*a) a____ = *(a); \
        *(a) = *(b);                          \
        *(b) = a____;                         \
    }while(0);

#define ZRTOS_TYPES__IS_ADD_OVERFLOW(a,b) \
    (((a + b ) < a))

#define ZRTOS_TYPES__GET_STATIC_ARRAY_LENGTH(arr) \
    (sizeof(arr)/sizeof((arr)[0]))

#define ZRTOS_TYPES__SIZE_MIN (0)
#define ZRTOS_TYPES__SIZE_MAX SIZE_MAX

#define ZRTOS_TYPES__INT8_MIN INT8_MIN
#define ZRTOS_TYPES__INT8_MAX INT8_MAX
#define ZRTOS_TYPES__INT16_MIN INT16_MIN
#define ZRTOS_TYPES__INT16_MAX INT16_MAX
#define ZRTOS_TYPES__INT32_MIN INT32_MIN
#define ZRTOS_TYPES__INT32_MAX INT32_MAX
#define ZRTOS_TYPES__INT64_MIN INT64_MIN
#define ZRTOS_TYPES__INT64_MAX INT64_MAX

#define ZRTOS_TYPES__UINT8_MIN (0)
#define ZRTOS_TYPES__UINT8_MAX UINT8_MAX
#define ZRTOS_TYPES__UINT16_MIN (0)
#define ZRTOS_TYPES__UINT16_MAX UINT16_MAX
#define ZRTOS_TYPES__UINT32_MIN (0)
#define ZRTOS_TYPES__UINT32_MAX UINT32_MAX
#define ZRTOS_TYPES__UINT64_MIN (0)
#define ZRTOS_TYPES__UINT64_MAX UINT64_MAX

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

#define ZRTOS_TYPES__MAP(value,in_min,in_max,out_min,out_max)\
  (((value)-(in_min))*((out_max)-(out_min))/((in_max)-(in_min))+(out_min))

uint16_t zrtos_types__uint16_bswap(uint16_t x){
	return ((uint16_t) ((((x) >> 8) & 0xff) | (((x) & 0xff) << 8)));
}

uint32_t zrtos_types__uint32_bswap(uint32_t x){
	return ((((x) & 0xff000000u) >> 24) | (((x) & 0x00ff0000u) >> 8)
   | (((x) & 0x0000ff00u) << 8) | (((x) & 0x000000ffu) << 24));
}

uint64_t zrtos_types__uint64_bswap(uint64_t x){
	return 
  ((((x) & 0xff00000000000000ull) >> 56)
   | (((x) & 0x00ff000000000000ull) >> 40)
   | (((x) & 0x0000ff0000000000ull) >> 24)
   | (((x) & 0x000000ff00000000ull) >> 8)
   | (((x) & 0x00000000ff000000ull) << 8)
   | (((x) & 0x0000000000ff0000ull) << 24)
   | (((x) & 0x000000000000ff00ull) << 40)
   | (((x) & 0x00000000000000ffull) << 56))
   ;
}

#if ZRTOS_ARCH__BYTE_ORDER == ZRTOS_ARCH__BYTE_ORDER_LITTLE_ENDIAN
# define zrtos_types__htobe16(x) zrtos_types__uint16_bswap(x)
# define zrtos_types__htole16(x) (x)
# define zrtos_types__be16toh(x) zrtos_types__uint16_bswap(x)
# define zrtos_types__le16toh(x) (x)

# define zrtos_types__htobe32(x) zrtos_types__uint32_bswap(x)
# define zrtos_types__htole32(x) (x)
# define zrtos_types__be32toh(x) zrtos_types__uint32_bswap(x)
# define zrtos_types__le32toh(x) (x)

# define zrtos_types__htobe64(x) zrtos_types__uint64_bswap(x)
# define zrtos_types__htole64(x) (x)
# define zrtos_types__be64toh(x) zrtos_types__uint64_bswap(x)
# define zrtos_types__le64toh(x) (x)
#else
# define zrtos_types__htobe16(x) (x)
# define zrtos_types__htole16(x) zrtos_types__uint16_bswap(x)
# define zrtos_types__be16toh(x) (x)
# define zrtos_types__le16toh(x) zrtos_types__uint16_bswap(x)

# define zrtos_types__htobe32(x) (x)
# define zrtos_types__htole32(x) zrtos_types__uint32_bswap(x)
# define zrtos_types__be32toh(x) (x)
# define zrtos_types__le32toh(x) zrtos_types__uint32_bswap(x)

# define zrtos_types__htobe64(x) (x)
# define zrtos_types__htole64(x) zrtos_types__uint64_bswap(x)
# define zrtos_types__be64toh(x) (x)
# define zrtos_types__le64toh(x) zrtos_types__uint64_bswap(x)
#endif

bool zrtos_types__is_digit(char c){
	return c >= '0' && c <= '9';
}

bool zrtos_types__is_whitespace(char c){
	return c == ' ' || c == '\t';
}

bool zrtos_types__is_newline(char c){
	return c == '\r' || c == '\n';
}

#ifdef __cplusplus
}
#endif
#endif