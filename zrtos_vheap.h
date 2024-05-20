/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VHEAP_H
#define ZRTOS_VHEAP_H
#ifdef __cplusplus
extern "C" {
#endif


#include "zrtos_debug.h"
#include "zrtos_mem.h"
#include "zrtos_vheap_chunk.h"


#define ZRTOS_VHEAP__INIT(name,heap_size)                   \
    static struct{                                        \
        uint8_t heap[heap_size];                          \
    }__attribute__((aligned(ZRTOS_ARCH__BYTE_ALIGNMENT)))name;


#define ZRTOS_VHEAP__GET(name) \
    ((zrtos_vheap_t*)&(name.heap[0]))

typedef struct _zrtos_vheap_t{
	void                    *ptr;
	size_t                  length;//index length
	size_t                  heap_size;
	size_t                  total_size;
}zrtos_vheap_t;

bool zrtos_vheap__init(
	 zrtos_vheap_t *thiz
	,void        *heap
	,size_t      heap_size
){
	ZRTOS_DEBUG__CODE(
		zrtos_debug__memset(heap,0xEE,heap_size);
	);

	thiz->ptr = heap;
	thiz->length = 0;
	thiz->heap_size = 0;
	thiz->total_size = heap_size;

	return true;
}

void *zrtos_vheap__get_last_address(zrtos_vheap_t *thiz){
	return zrtos_types__ptr_add(thiz->ptr,thiz->total_size);
}

void *zrtos_vheap__get_stack_ptr(zrtos_vheap_t *thiz){
	return ZRTOS_ARCH__GET_STACK_PTR();
}

size_t _zrtos_vheap__get_free_space_ex(zrtos_vheap_t *thiz,void *stack_ptr){
	return
		  thiz->ptr < stack_ptr
		? zrtos_types__ptr_get_byte_distance(
			ZRTOS_TYPES__MIN(
				 stack_ptr
				,zrtos_vheap__get_last_address(thiz)
			)
			,thiz->ptr
		)
		: 0
	;
}

size_t _zrtos_vheap__get_free_space(zrtos_vheap_t *thiz){
	return _zrtos_vheap__get_free_space_ex(
		 thiz
		,zrtos_vheap__get_stack_ptr(thiz)
	);
}

zrtos_vheap_chunk_t *zrtos_vheap__get_by_id(
	 zrtos_vheap_t *thiz
	,zrtos_vheap_chunk_uid_t   uid
){
	zrtos_vheap_chunk_t *node = thiz->ptr;
	for(size_t l = thiz->length;l--;node++){
		if(node->uid.uid == uid.uid){
			return node;
		}
	}
	return 0;
}

zrtos_vheap_chunk_t *zrtos_vheap__get_by_type(
	 zrtos_vheap_t *thiz
	,zrtos_vheap_chunk_type_t   type
){
	zrtos_vheap_chunk_t *node = thiz->ptr;
	for(size_t l = thiz->length;l--;node++){
		if(node->type.type == type.type){
			return node;
		}
	}
	return 0;
}

zrtos_vheap_chunk_t *zrtos_vheap__get_by_type_ex(
	 zrtos_vheap_t *thiz
	,zrtos_vheap_type_t   type
){
	zrtos_vheap_chunk_type_t tmp;
	zrtos_vheap_chunk_type__init(&tmp,type);
	return zrtos_vheap__get_by_type(
		 thiz
		,tmp
	);
}

static zrtos_vheap_chunk_uid_t zrtos_vheap__get_next_uid(
	zrtos_vheap_t *thiz
){
	static zrtos_vheap_chunk_uid_t uid = {
		.uid = 1
	};
	zrtos_vheap_chunk_uid_t ret = {
		.uid = uid.uid++
	};

	while(ret.uid == 0 || zrtos_vheap__get_by_id(
		 thiz
		,ret
	)){
		ret.uid++;
	}

	return ret;
}

size_t zrtos_vheap__get_chunk_count(
	zrtos_vheap_t *thiz
){
	return thiz->length / sizeof(zrtos_vheap_chunk_t);
}

zrtos_vheap_chunk_t *_zrtos_vheap__malloc(
	 zrtos_vheap_t *thiz
	,zrtos_vheap_chunk_uid_t   parent
	,zrtos_vheap_type_t type
	,size_t length
){
	zrtos_vheap_chunk_t *chunk = 0;
	size_t free_space = _zrtos_vheap__get_free_space(thiz);
	size_t length_total = sizeof(zrtos_vheap_chunk_t) + length;
	if(free_space >= length_total){
		zrtos_vheap_chunk_t *node;
		size_t index_length = (sizeof(zrtos_vheap_chunk_t) * thiz->length);
		size_t heap_length = thiz->heap_size - index_length;

		uint8_t *src = thiz->ptr + thiz->heap_size;
		uint8_t *dest = src + sizeof(zrtos_vheap_chunk_t);

		thiz->heap_size += length_total;

		zrtos_mem__move_right_overlapping(
			 dest - heap_length
			,src - heap_length
			,heap_length
		);

		chunk = &((zrtos_vheap_chunk_t*)thiz->ptr)[thiz->length++];
	chunk->first[0] = 0x55;
	chunk->first[1] = 0x55;

		chunk->ptr = thiz->ptr + thiz->heap_size - length;
		chunk->length = length;
		chunk->uid = zrtos_vheap__get_next_uid(thiz);
		chunk->parent = parent;
		chunk->type.type = type;
	chunk->last[0] = 0x66;
	chunk->last[1] = 0x66;

		//update index
		node = &((zrtos_vheap_chunk_t*)thiz->ptr)[0];
		for(;node < chunk;node++){
			node->ptr += sizeof(zrtos_vheap_chunk_t);
		}

		ZRTOS_DEBUG__CODE(
			static uint8_t pattern = 0xE0;
			zrtos_debug__memset(chunk->ptr,(int)(pattern++),chunk->length);
		);
	}
	return chunk;
}

zrtos_vheap_chunk_uid_t zrtos_vheap__malloc(
	 zrtos_vheap_t *thiz
	,zrtos_vheap_chunk_uid_t   parent
	,zrtos_vheap_type_t type
	,size_t length
){
	zrtos_vheap_chunk_t *chunk = _zrtos_vheap__malloc(
		 thiz
		,parent
		,type
		,length
	);
	if(chunk){
		return chunk->uid;
	}
	return zrtos_vheap_chunk_uid__error();
}

static void _zrtos_vheap__update_index_ptr(
	 zrtos_vheap_t       *thiz
	,zrtos_vheap_chunk_t *chunk
	,size_t             sizeof_mem_chunk
){
	size_t length = chunk->length;
	zrtos_vheap_chunk_t *node = &((zrtos_vheap_chunk_t*)thiz->ptr)[0];
	zrtos_vheap_chunk_t *sentinel = &((zrtos_vheap_chunk_t*)thiz->ptr)[thiz->length];
	for(;node < sentinel;node++){
		node->ptr -= sizeof_mem_chunk/*sizeof(zrtos_vheap_chunk_t)*/ + (node > chunk ? length : 0);
	}
}

zrtos_vheap_chunk_t *zrtos_vheap__get_child(zrtos_vheap_t *thiz,zrtos_vheap_chunk_t *chunk){
	zrtos_vheap_chunk_t *node = &((zrtos_vheap_chunk_t*)thiz->ptr)[0];
	zrtos_vheap_chunk_t *sentinel = &((zrtos_vheap_chunk_t*)thiz->ptr)[thiz->length];
	zrtos_vheap_chunk_t *ret = 0;
	for(;node < sentinel;node++){
		if(zrtos_vheap_chunk_uid__cmp(&chunk->uid,&node->parent)){
			ret = node;
			break;
		}
	}
	return ret;
}

void zrtos_vheap__free_helper(zrtos_vheap_t *thiz,zrtos_vheap_chunk_t *chunk){
	/// @todo cancel running task...
	uint8_t *dest = (uint8_t*)chunk;
	uint8_t *src = dest + sizeof(zrtos_vheap_chunk_t);
	zrtos_vheap_chunk_t *sentinel;
	size_t length = chunk->length;
	size_t length_total = sizeof(zrtos_vheap_chunk_t) + length;
	int lp = 1;
	void *chunk_ptr = chunk->ptr;

	//update index
	_zrtos_vheap__update_index_ptr(thiz,chunk,sizeof(zrtos_vheap_chunk_t));

	//1st loop delete index, 2nd loop delete element
	sentinel = chunk_ptr;//zrtos_types__ptr_add(chunk->ptr,sizeof(zrtos_vheap_chunk_t));
	do{
		while(src < ((uint8_t*)sentinel)){
 			*dest++ = *src++;
		}
		src += length;
		sentinel = zrtos_types__ptr_add(thiz->ptr,thiz->heap_size);
	}while(lp--);

	thiz->length--;
	thiz->heap_size -= length_total;

	ZRTOS_DEBUG__CODE(
		zrtos_debug__memset(
			 zrtos_types__ptr_add(thiz->ptr,thiz->heap_size)
			,0xEE
			,length_total
		);
	);
}

void _zrtos_vheap__free(zrtos_vheap_t *thiz,zrtos_vheap_chunk_t *chunk){
	while(true){
		zrtos_vheap_chunk_t *node = zrtos_vheap__get_child(thiz,chunk);
		if(node){
			zrtos_vheap_chunk_t *last = node;
			while((node = zrtos_vheap__get_child(thiz,node))){
				last = node;
			}
			_zrtos_vheap__free_helper(thiz,last);
		}else{
			break;
		}
	}
	_zrtos_vheap__free_helper(thiz,chunk);
}

void zrtos_vheap__free(zrtos_vheap_t *thiz,zrtos_vheap_chunk_uid_t uid){
	zrtos_vheap_chunk_t *chunk = zrtos_vheap__get_by_id(
		 thiz
		,uid
	);
	_zrtos_vheap__free(thiz,chunk);
}

static void *_zrtos_vheap__swap_to_heap_end(
	 void   *heap
	,size_t heap_length
	,size_t used_length
	,size_t chunk_offset
	,size_t chunk_length
){
	uint8_t *buffer = heap;
	void *ret = buffer + heap_length - chunk_length;
	zrtos_mem__left_rotate(
		 buffer + chunk_offset
		,chunk_length
		,used_length - chunk_offset
	);
	zrtos_mem__move_right_overlapping(
		 ret//buffer + heap_length - chunk_length
		,buffer + used_length - chunk_length
		,chunk_length
	);
	return ret;
}

void *zrtos_vheap__page_in(
	 zrtos_vheap_t       *thiz
	,zrtos_vheap_chunk_t *chunk
){
	size_t index_length = (sizeof(zrtos_vheap_chunk_t) * thiz->length);
	void *ptr_index = zrtos_types__ptr_add(thiz->ptr,index_length);
	void *chunk_ptr = chunk->ptr;
	void *ret;

	//update index
	_zrtos_vheap__update_index_ptr(thiz,chunk,0);

	ret = _zrtos_vheap__swap_to_heap_end(
		 ptr_index
		,thiz->total_size - index_length
		,thiz->heap_size - index_length
		,zrtos_types__ptr_get_byte_distance(chunk_ptr,ptr_index)
		,chunk->length
	);

	thiz->heap_size -= chunk->length;
	//chunk->ptr = 0;
	chunk->length = 0;
	zrtos_vheap_chunk__set_type(chunk,ZRTOS_VHEAP_TYPE__TASK_ACTIVE);

	return ret;
}

void zrtos_vheap__page_out(
	 zrtos_vheap_t       *thiz
	,zrtos_vheap_chunk_t *chunk
	,size_t            length
){
	uint8_t *heap_end_ptr = zrtos_types__ptr_add(thiz->ptr,thiz->heap_size);
	zrtos_mem__move_left_overlapping(
		 heap_end_ptr
		,zrtos_types__ptr_add(thiz->ptr,thiz->total_size - length)
		,length
	);

	thiz->heap_size += length;

	chunk->ptr = heap_end_ptr;
	chunk->length = length;
	zrtos_vheap_chunk__set_type(
		 chunk
		,(
			  chunk->type.type == ZRTOS_VHEAP_TYPE__TASK_ACTIVE
			? ZRTOS_VHEAP_TYPE__TASK_IDLE
			: chunk->type.type
		)
	);

	//move chunk to end of index
	size_t index_length = (sizeof(zrtos_vheap_chunk_t) * thiz->length);
	zrtos_mem__left_rotate(
		 chunk
		,sizeof(zrtos_vheap_chunk_t)
		,zrtos_types__ptr_get_byte_distance(
			zrtos_types__ptr_add(
				 thiz->ptr
				,index_length
			)
			,chunk
		)
	);

	ZRTOS_DEBUG__CODE(
		zrtos_debug__memset(
			 zrtos_types__ptr_add(heap_end_ptr,length)
			,0xEE
			,thiz->total_size - thiz->heap_size
		);
	);
}

#define ZRTOS_VHEAP__EACH_EX_BEGIN(thiz,start_offset,l,type,value)               \
    for(size_t l = start_offset,len__=(thiz)->length;l < len__;l++){           \
        zrtos_vheap_chunk_t *value = &((zrtos_vheap_chunk_t*)((thiz)->ptr))[l];    \
        if(zrtos_vheap_chunk__is_type_eq(value,type)){

#define ZRTOS_VHEAP__EACH_EX_END \
        }                      \
    }

#define ZRTOS_VHEAP__EACH_BEGIN(thiz,type,value)                                 \
    for(size_t l__ = 0,len__=(thiz)->length;l__ < len__;l__++){                \
        zrtos_vheap_chunk_t *value = &((zrtos_vheap_chunk_t*)((thiz)->ptr))[l];    \
        if(zrtos_vheap_chunk__is_type_eq(value,type))

#define ZRTOS_VHEAP__EACH_END \
        }                   \
    }

#ifdef __cplusplus
}
#endif
#endif