/* vim: noai:ts=4
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_MALLOC_H
#define ZRTOS_MALLOC_H
#ifdef __cplusplus
extern "C" {
#endif

#include "zrtos_types.h"
#include "zrtos_debug.h"

typedef struct _zrtos_malloc_t{
	uint8_t value;
}__attribute__((packed))zrtos_malloc_t;

typedef struct _zrtos_malloc_heap_chunk_t{
	size_t  length;
}zrtos_malloc_heap_chunk_t;

typedef struct _zrtos_malloc_internal_t{
	uint8_t *ptr;
	size_t  length;
}zrtos_malloc_internal_t;

#define ZRTOS_MALLOC__GLOBAL_INIT(name)                   \
	zrtos_malloc__init(                                   \
		 name##_buffer                                    \
		,sizeof(name##_buffer) / sizeof(name##_buffer[0]) \
	)


#define ZRTOS_MALLOC__GLOBAL(name,len)                            \
	zrtos_malloc_t name##_buffer[len];                            \
                                                                  \
	ZRTOS_ASSERT__STATIC(len >= sizeof(zrtos_malloc_internal_t)); \
	                                                              \
	void *malloc(size_t length){                                  \
		return zrtos_malloc__malloc(                              \
			 name##_index                                         \
			,length                                               \
		);                                                        \
	}                                                             \
	                                                              \
	void free(void *ptr){                                         \
		zrtos_malloc__free(ptr);                                  \
	}

#define ZRTOS_MALLOC__INIT_DEBUG(name,length)           \
	ZRTOS__DEBUG_CODE({                                 \
		zrtos_debug__memset(name##_buffer,0xFF,length); \
	});

bool zrtos_malloc__init(zrtos_malloc_t *thiz,size_t length){
	zrtos_malloc_internal_t *thiz_ = thiz;

	if(length >= sizeof(zrtos_malloc_internal_t)){
		thiz_->ptr = zrtos_types__ptr_add(thiz,sizeof(zrtos_malloc_internal_t));
		thiz_->length = length - sizeof(zrtos_malloc_internal_t);

		ZRTOS__DEBUG_CODE({
			zrtos_debug__memset(ptr,0xFF,length);
		});
		return true;
	}
	return false;
}

zrtos_malloc_heap_chunk_t *zrtos_malloc__get_free_chunk(
	 zrtos_malloc_t *thiz
	,size_t         length
){
	zrtos_malloc_internal_t *thiz_ = thiz;
	zrtos_malloc_heap_chunk_t *chunk = (zrtos_malloc_heap_chunk_t *)(thiz_+1);
	zrtos_malloc_heap_chunk_t *last = (zrtos_malloc_heap_chunk_t *)thiz_->ptr;
	length <<= 1;

	while(chunk != last){
		if(chunk->length == length){
			return chunk;
		}
		chunk = zrtos_types__ptr_add(
			 chunk
			,sizeof(zrtos_malloc_heap_chunk_t) + (chunk->length>>1)
		);
	}

	return 0;
}

/*
** either returns a recently freed memory block with the exact same
** length or allocates a new memory block
**/
void *zrtos_malloc__malloc(zrtos_malloc_t *thiz,size_t length){
	zrtos_malloc_internal_t *thiz_ = thiz;
	zrtos_malloc_heap_chunk_t *chunk = 0;
	size_t total_length = sizeof(zrtos_malloc_heap_chunk_t) + length;
	bool has_free_space = (thiz_->length
	                    - zrtos_types__ptr_get_byte_distance(
	                		 thiz_->ptr
	                		,(thiz_ + 1)
	                    ))
	                    >= total_length
	;

	if(length > (SIZE_MAX>>1)){
		//out of bounds
		goto L_OUT;
	}else if((chunk = zrtos_malloc__get_free_chunk(thiz_,length))){
		chunk->length |= 1;
	}else if(has_free_space){
		chunk = (zrtos_malloc_heap_chunk_t*)thiz_->ptr;
		chunk->length = (length << 1) | 1;
		thiz_->ptr += total_length;
	}else{
		goto L_OUT;
	}

	chunk++;

	ZRTOS__DEBUG_CODE({
		static uint8_t pattern = 0x20;
		zrtos_debug__memset(chunk,pattern++,length);
	});

L_OUT:
	return chunk;
}

/*
** the memory adressed by the pointer will only be marked as unused
**/
void zrtos_malloc__free(void *ptr){
	zrtos_malloc_heap_chunk_t *chunk = ptr;
	--chunk;
	chunk->length &= ~((size_t)1);

	ZRTOS__DEBUG_CODE({
		zrtos_debug__memset(ptr,0xFF,(chunk->length >> 1));
	});
}


#ifdef __cplusplus
}
#endif
#endif