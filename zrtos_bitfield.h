/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_BITFIELD_H
#define ZRTOS_BITFIELD_H
#ifdef __cplusplus
extern "C" {
#endif


#include "zrtos_types.h"
#include "zrtos_mem.h"


typedef uint8_t zrtos_bitfield_mask_t;

typedef struct{
	uint8_t val;
}__attribute__((packed))zrtos_bitfield_t;

#define	ZRTOS_BITFIELD__NFDBITS	(8 * sizeof(zrtos_bitfield_mask_t))
#define	ZRTOS_BITFIELD__ELT(d)	(((size_t)d) / ZRTOS_BITFIELD__NFDBITS)
#define	ZRTOS_BITFIELD__MASK(d)	((zrtos_bitfield_mask_t) (1 << (((size_t)d) % ZRTOS_BITFIELD__NFDBITS)))

void zrtos_bitfield__set(zrtos_bitfield_t *thiz,size_t pos,bool val){
	zrtos_bitfield_mask_t *tmp = &(&thiz->val)[ZRTOS_BITFIELD__ELT(pos)];
	if(val){
		*tmp |= ZRTOS_BITFIELD__MASK(pos);
	}else{
		*tmp &= ~ZRTOS_BITFIELD__MASK(pos);
	}
}

bool zrtos_bitfield__get(zrtos_bitfield_t *thiz,size_t pos){
	return 0 != (
		(&thiz->val)[ZRTOS_BITFIELD__ELT(pos)] & ZRTOS_BITFIELD__MASK(pos)
	);
}

void zrtos_bitfield__zero(zrtos_bitfield_t *thiz,size_t len){
	zrtos_mem__zero(thiz,len);
}

static size_t zrtos_bitfield__find_first(
	 zrtos_bitfield_t *thiz
	,size_t len
	,size_t start
	,bool zero
){
	len *= ZRTOS_BITFIELD__NFDBITS;
	for(size_t i=start;i<len;i++){
		bool val = zrtos_bitfield__get(thiz,i);

		if(zero){
			val = !val;
		}

		if(val){
			return i;
		}
	}
	return ZRTOS_TYPES__SIZE_MAX;
}

size_t zrtos_bitfield__find_first_zero(
	 zrtos_bitfield_t *thiz
	,size_t len
	,size_t start
){
	return zrtos_bitfield__find_first(
		 thiz
		,len
		,start
		,true
	);
}

size_t zrtos_bitfield__find_first_set(
	 zrtos_bitfield_t *thiz
	,size_t len
	,size_t start
){
	return zrtos_bitfield__find_first(
		 thiz
		,len
		,start
		,false
	);
}

#ifdef __cplusplus
}
#endif
#endif