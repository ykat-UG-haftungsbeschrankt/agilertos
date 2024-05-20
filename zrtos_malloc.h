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

#include "zrtos_assert.h"
#include "zrtos_types.h"
#include "zrtos_debug.h"

typedef struct _zrtos_malloc_t{
	uint8_t value;
}__attribute__((packed))zrtos_malloc_t;

typedef struct _zrtos_malloc_heap_chunk_t{
#ifndef ZRTOS_MALLOC__CFG_DISABLE_FREE
	size_t  length;
#endif
}zrtos_malloc_heap_chunk_t;

typedef struct _zrtos_malloc_internal_t{
	uint8_t *ptr;
	size_t  length;
}zrtos_malloc_internal_t;

#define ZRTOS_MALLOC__GET_REQUIRED_SIZE(type,count)                     \
    ( sizeof(zrtos_malloc_internal_t)                                   \
    +   (                                                               \
            (                                                           \
                  sizeof(zrtos_malloc_heap_chunk_t)                     \
                + sizeof(type)                                          \
            )                                                           \
            * (count)                                                   \
        )                                                               \
    )

#define ZRTOS_MALLOC__GLOBAL_HEAP_INIT(name)                            \
    zrtos_malloc__init(                                                 \
         name                                                           \
        ,sizeof(name) / sizeof(name[0])                                 \
    );                                                                  \
                                                                        \
    ZRTOS_DEBUG__CODE({                                                 \
        zrtos_debug__memset(                                            \
             zrtos_types__ptr_add(name,sizeof(zrtos_malloc_internal_t)) \
            ,0xFF                                                       \
            ,(sizeof(name) / sizeof(name[0]))                           \
            -sizeof(zrtos_malloc_internal_t)                            \
        );                                                              \
    });

#define ZRTOS_MALLOC__GLOBAL_HEAP(name,len)                       \
    zrtos_malloc_t name[                                          \
        (len)                                                     \
    ];                                                            \
                                                                  \
    ZRTOS_ASSERT__STATIC(len >= sizeof(zrtos_malloc_internal_t)); \
                                                                  \
    void *malloc(size_t length){                                  \
        return zrtos_malloc__malloc(                              \
             name                                                 \
            ,length                                               \
        );                                                        \
    }                                                             \
                                                                  \
    void free(void *ptr){                                         \
        zrtos_malloc__free(ptr);                                  \
    }

#define ZRTOS_MALLOC__INIT(name,len)                              \
    zrtos_malloc_t name[                                          \
        (len)                                                     \
    ];                                                            \
                                                                  \
    ZRTOS_ASSERT__STATIC(len >= sizeof(zrtos_malloc_internal_t)); \
                                                                  \
    zrtos_malloc__init(                                           \
         name                                                     \
        ,sizeof(name) / sizeof(name[0])                           \
    )

bool zrtos_malloc__init(zrtos_malloc_t *thiz,size_t length){
	zrtos_malloc_internal_t *thiz_ = (zrtos_malloc_internal_t *)thiz;
	bool ret = false;
	if(length >= sizeof(zrtos_malloc_internal_t)){
		thiz_->ptr = zrtos_types__ptr_add(thiz,sizeof(zrtos_malloc_internal_t));
		thiz_->length = length - sizeof(zrtos_malloc_internal_t);

		ZRTOS_DEBUG__CODE({
			zrtos_debug__memset(thiz_->ptr,0xFF,length);
		});

		ret = true;
	}
	return ret;
}

#ifndef ZRTOS_MALLOC__CFG_DISABLE_FREE
static zrtos_malloc_heap_chunk_t *zrtos_malloc__get_free_chunk(
	 zrtos_malloc_t *thiz
	,size_t         length
){
	zrtos_malloc_internal_t *thiz_ = (zrtos_malloc_internal_t *)thiz;
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
#endif

/*
** defined(ZRTOS_MALLOC__CFG_DISABLE_FREE)
** ? allocates a new memory block
** : either returns a recently freed memory block with the exact same
**   length or allocates a new memory block
**/
void *zrtos_malloc__malloc(zrtos_malloc_t *thiz,size_t length){
#ifndef ZRTOS_MALLOC__CFG_DISABLE_FREE
	zrtos_malloc_internal_t *thiz_ = (zrtos_malloc_internal_t *)thiz;
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
	}else if((chunk = zrtos_malloc__get_free_chunk(thiz,length))){
		chunk->length |= 1;
	}else if(has_free_space){
		chunk = (zrtos_malloc_heap_chunk_t*)thiz_->ptr;
		chunk->length = (length << 1) | 1;
		thiz_->ptr += total_length;
	}else{
		goto L_OUT;
	}

	chunk++;

	ZRTOS_DEBUG__CODE({
		static uint8_t pattern = 0x20;
		zrtos_debug__memset(chunk,pattern++,length);
	});

L_OUT:
	return chunk;
#else
	zrtos_malloc_internal_t *thiz_ = (zrtos_malloc_internal_t *)thiz;
	void *ret = 0;
	bool has_free_space = (thiz_->length
	                    - zrtos_types__ptr_get_byte_distance(
	                		 thiz_->ptr
	                		,thiz_
	                    ))
	                    >= length
	;

	if(has_free_space){
		ret = thiz_->ptr;
		thiz_->ptr += length;
	}

	ZRTOS_DEBUG__CODE({
		static uint8_t pattern = 0x20;
		zrtos_debug__memset(ret,pattern++,length);
	});

	return ret;
#endif
}

/*
** defined(ZRTOS_MALLOC__CFG_DISABLE_FREE)
** ? noop
** : the memory adressed by the pointer will only be marked as unused
**/
void zrtos_malloc__free(void *ptr){
#ifndef ZRTOS_MALLOC__CFG_DISABLE_FREE
	zrtos_malloc_heap_chunk_t *chunk = ptr;
	--chunk;
	chunk->length &= ~((size_t)1);

	ZRTOS_DEBUG__CODE({
		zrtos_debug__memset(ptr,0xFF,(chunk->length >> 1));
	});
#endif
}


#ifdef __cplusplus
}
#endif
#endif