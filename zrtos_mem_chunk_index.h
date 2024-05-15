/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_MEM_CHUNK_INDEX_H
#define ZRTOS_MEM_CHUNK_INDEX_H
#ifdef __cplusplus
extern "C" {
#endif


typedef struct _zrtos_mem_chunk_index_t{
	zrtos_mem_chunk_t          *heap;
	size_t                     heap_size;
	size_t                     length;
}zrtos_mem_chunk_index_t;

bool zrtos_mem_chunk_index__init(
	 zrtos_mem_chunk_index_t *thiz
	,zrtos_mem_chunk_t       *heap
	,size_t                  heap_size
){
	thiz->heap = heap;
	thiz->heap_size = heap_size;
	thiz->length = 0;
	return true;
}

void *zrtos_mem_chunk_index__get_first_address(zrtos_mem_chunk_index_t *thiz){
	return thiz->heap;
}

void *zrtos_mem_chunk_index__get_last_address(zrtos_mem_chunk_index_t *thiz){
	return zrtos__ptr_add(thiz->heap,thiz->heap_size);
}

size_t zrtos_mem_chunk_index__get_heap_size(zrtos_mem_chunk_index_t *thiz){
	return thiz->heap_size;
}

void zrtos_mem_chunk_index__set_heap_size(
	 zrtos_mem_chunk_index_t *thiz
	,size_t heap_size
){
	thiz->heap_size = heap_size;
}

size_t zrtos_mem_chunk_index__get_required_heap_size(
	size_t length
){
	return sizeof(zrtos_mem_chunk_t) * length;
}

zrtos_mem_chunk_t *zrtos_mem_chunk_index__get_by_id(
	 zrtos_mem_chunk_index_t *thiz
	,zrtos_mem_chunk_uid_t   uid
){
	zrtos_mem_chunk_t *ret = 0;
	for(size_t l = 0;l < thiz->length;l++){
		if(thiz->heap[l].uid.uid == uid.uid){
			ret = &thiz->heap[l];
			break;
		}
	}
	return ret;
}

size_t zrtos_mem_chunk_index__get_in_use(
	zrtos_mem_chunk_index_t *thiz
){
	size_t ret = 0;
	for(size_t l = 0;l < thiz->length;l++){
		ret += thiz->heap[l].length;
	}
	return ret;
}

size_t zrtos_mem_chunk_index__get_length(
	zrtos_mem_chunk_index_t *thiz
){
	return thiz->length;
}

zrtos_mem_chunk_uid_t zrtos_mem_chunk_index__get_next_uid(
   zrtos_mem_chunk_index_t *thiz
){
	static zrtos_mem_chunk_uid_t uid = {
		.uid = 1
	};
	zrtos_mem_chunk_uid_t ret = {
		.uid = uid.uid++
	};

	while(ret.uid == 0 || zrtos_mem_chunk_index__get_by_id(
		 thiz
		,ret
	)){
		ret.uid++;
	}

	return ret;
}

#define ZRTOS_MEM_CHUNK_INDEX__EACH_BEGIN(thiz,type,value)  \
	for(size_t l__ = 0,len__=(thiz)->length;l__ < len__;l__++){ \
		zrtos_mem_chunk_t *value = &((thiz)->heap[l__]);          \
		if(zrtos_mem_chunk_type__is_eq(zrtos_mem_chunk__get_type(value),type))

#define ZRTOS_MEM_CHUNK_INDEX__EACH_END\
	}


#ifdef __cplusplus
}
#endif
#endif