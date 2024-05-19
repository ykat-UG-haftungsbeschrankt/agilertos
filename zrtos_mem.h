/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_MEM_H
#define ZRTOS_MEM_H
#ifdef __cplusplus
extern "C" {
#endif


#include "zrtos_types.h"


void zrtos_mem__swap(void *dest, void *src, size_t len){
	uint8_t *tmp_dest = dest;
	uint8_t *tmp_src = src;
	while(len--){
		ZRTOS_TYPES__SWAP_PTR_CONTENTS(tmp_src,tmp_dest);
		tmp_src++;
		tmp_dest++;
	}
}

void zrtos_mem__swap_ex(
	 void *ptr
	,size_t offest_dest
	,size_t offset_src
	,size_t len
){
	zrtos_mem__swap(
		 zrtos_types__ptr_add(ptr,offest_dest)
		,zrtos_types__ptr_add(ptr,offset_src)
		,len
	);
}

void zrtos_mem__left_rotate(
	 void *ptr
	,size_t length
	,size_t buffer_length
){
	size_t d = length;
	size_t n = buffer_length;
	size_t i = d;
	size_t j = n - d;
	while(i != j){
		if(i < j){
			//A is shorter
			zrtos_mem__swap_ex(ptr, d - i, d + j - i, i);
			j -= i;
		}else{
			//B is shorter
			zrtos_mem__swap_ex(ptr, d - i, d, j);
			i -= j;
		}
	}
	//Finally, block swap A and B
	zrtos_mem__swap_ex(ptr, d - i, d, i);
}

#ifdef ZRTOS__USE_MEMMOVE
# define zrtos_mem__move_right_overlapping memmove
# define zrtos_mem__move_left_overlapping memmove
#else
void zrtos_mem__move_right_overlapping(
	 void *dest
	,void *src
	,size_t length
){
	uint8_t *tmp_dest = dest;
	uint8_t *tmp_src = src;
	tmp_dest += --length;
	tmp_src += length++;
	while(length--){
		*tmp_dest-- = *tmp_src--;
	}
}

void zrtos_mem__move_left_overlapping(
	  void *dest
	 ,void *src
	 ,size_t length
){
	uint8_t *tmp_dest = dest;
	uint8_t *tmp_src = src;
	while(length--){
		*tmp_dest++ = *tmp_src++;
	}
}
#endif


#ifdef __cplusplus
}
#endif
#endif