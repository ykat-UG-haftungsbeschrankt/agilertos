/*
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


#include "zrtos_debug.h"

typedef uint8_t* zrtos_malloc_buffer_t;

typedef struct _zrtos_malloc_heap_chunk_t{
	struct _zrtos_malloc_heap_chunk_t *next;
	size_t                            length;
}zrtos_malloc_heap_chunk_t;

typedef struct _zrtos_malloc_t{
	uint8_t *heap;
	uint8_t *ptr;
	size_t  length;
}zrtos_malloc_t;


#define ZRTOS_MALLOC__INIT(name,len)         \
	uint8_t name##_buffer[len];              \
											 \
	zrtos_malloc_t name##_index = {          \
		 .heap = name##_buffer               \
		,.ptr = name##_buffer                \
		,.length = len                       \
	};                                       \
											 \
	void *malloc(size_t length){             \
		return zrtos_malloc__malloc(         \
			 &name##_index                   \
			,length                          \
		);                                   \
	}                                        \
											 \
	void free(void *ptr){                    \
		zrtos_malloc__free(ptr);             \
	}

#define ZRTOS_MALLOC__INIT_DEBUG(name,length)           \
	ZRTOS__DEBUG_CODE({                                 \
		zrtos_debug__memset(name##_buffer,0xFF,length); \
	});

bool zrtos_malloc__init(zrtos_malloc_t *thiz,void *ptr,size_t length){
	thiz->heap = thiz->ptr = ptr;
	thiz->length = length;

	ZRTOS__DEBUG_CODE({
		zrtos_debug__memset(ptr,0xFF,length);
	});

	return true;
}

zrtos_malloc_heap_chunk_t *zrtos_malloc__get_free_chunk(
	 zrtos_malloc_t *thiz
	,size_t length
){
	zrtos_malloc_heap_chunk_t *first = (zrtos_malloc_heap_chunk_t *)thiz->heap;
	zrtos_malloc_heap_chunk_t *chunk = first;
	length <<= 1;

	do{
		if(chunk->length == length){
			return chunk;
		}
		chunk = chunk->next;
	}while(chunk != first);

	return 0;
}

/*
** either returns a recently freed memory block with the exact same
** length or allocates a new memory block
**/
void *zrtos_malloc__malloc(zrtos_malloc_t *thiz,size_t length){
	zrtos_malloc_heap_chunk_t *chunk = 0;
	size_t total_length = sizeof(zrtos_malloc_heap_chunk_t) + length;
	bool has_free_space = thiz->length >= total_length;
	if(length > (SIZE_MAX>>1)){
		//out of bounds
	}else if(thiz->heap == thiz->ptr){
		//first chunk
		if(has_free_space){
			chunk = (zrtos_malloc_heap_chunk_t*)thiz->ptr;
			chunk->next = chunk;

L_SET_LENGTH_AND_PTR:
			chunk->length = (length << 1) | 1;
			thiz->ptr += total_length;
		}
	}else{
		//search free chunk or append
		chunk = zrtos_malloc__get_free_chunk(thiz,length);
		if(chunk){
			chunk->length |= 1;
		}else if(has_free_space){
			zrtos_malloc_heap_chunk_t *first = (zrtos_malloc_heap_chunk_t*)thiz->heap;
			chunk = (zrtos_malloc_heap_chunk_t*)thiz->ptr;
			chunk->next = chunk;

			chunk->next = first->next;
			first->next = chunk;

			goto L_SET_LENGTH_AND_PTR;
/*
			chunk->length = (length << 1) | 1;
			thiz->ptr += total_length;
*/
		}
	}

	ZRTOS__DEBUG_CODE({
		static uint8_t pattern = 0x20;
		if(chunk){
			zrtos_debug__memset(chunk+1,pattern++,length);
		}
	});
	
	return chunk ? ++chunk : 0;
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