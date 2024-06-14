/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_CBUFFER_H
#define ZRTOS_CBUFFER_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/types.h>
#include <zrtos/mem.h>
#include <zrtos/error.h>
#include <zrtos/clist.h>
#include <zrtos/malloc.h>
#include <zrtos/assert.h>

#ifndef ZRTOS_CBUFFER__CFG_DATA_LENGTH
#define ZRTOS_CBUFFER__CFG_DATA_LENGTH 16
#endif

ZRTOS_ASSERT__STATIC_IS_POWER_OF_TWO(ZRTOS_CBUFFER__CFG_DATA_LENGTH);

typedef struct _zrtos_cbuffer_node_t{
	zrtos_clist_node_t node;
	uint8_t            head;
	uint8_t            tail;
	uint8_t            data[ZRTOS_CBUFFER__CFG_DATA_LENGTH];
}zrtos_cbuffer_node_t;

typedef struct _zrtos_cbuffer_t{
	zrtos_clist_t      root;
}zrtos_cbuffer_t;

bool zrtos_cbuffer_node__init(
	 zrtos_cbuffer_node_t *thiz
	,zrtos_cbuffer_t *ctx
){
	zrtos_clist_node__init(&thiz->node);
	zrtos_clist__push(&ctx->root,&thiz->node);
	thiz->head = 0;
	thiz->tail = 0;
	return true;
}

zrtos_cbuffer_node_t *zrtos_cbuffer_node__new(zrtos_cbuffer_t *ctx){
	zrtos_cbuffer_node_t *ret = malloc(sizeof(zrtos_cbuffer_node_t));
	if(ret){
		zrtos_cbuffer_node__init(ret,ctx);
	}
	return ret;
}

void zrtos_cbuffer_node__free(zrtos_cbuffer_node_t *thiz,zrtos_cbuffer_t *ctx){
	zrtos_clist__delete(&ctx->root,&thiz->node);
	free(thiz);
}

bool zrtos_cbuffer__init(
	 zrtos_cbuffer_t *thiz
){
	zrtos_clist__init(&thiz->root);
	return zrtos_cbuffer_node__new(thiz) != 0;
}

zrtos_error_t zrtos_cbuffer_node__put(
	 zrtos_cbuffer_node_t *thiz
	,zrtos_cbuffer_t *ctx
	,uint8_t val
){
	zrtos_error_t ret = EXIT_SUCCESS;
	uint8_t head = thiz->head;
	head = (head + 1) & (ZRTOS_CBUFFER__CFG_DATA_LENGTH - 1);
	if(head != thiz->tail){
		thiz->data[thiz->head] = val;
		thiz->head = head;
	}else{
		zrtos_cbuffer_node_t *node = zrtos_cbuffer_node__new(ctx);
		if(node){
			ret = zrtos_cbuffer_node__put(
				 node
				,ctx
				,val
			);
		}else{
			ret = ENOMEM;
		}
	}
	return ret;
}

bool zrtos_cbuffer_node__is_empty(zrtos_cbuffer_node_t *thiz){
	return thiz->head == thiz->tail;
}

zrtos_error_t zrtos_cbuffer_node__get(
	zrtos_cbuffer_node_t *thiz
	,zrtos_cbuffer_t *ctx
	,uint8_t *out
){
	zrtos_error_t ret = EXIT_SUCCESS;
	if(!zrtos_cbuffer_node__is_empty(thiz)){
		*out = thiz->data[thiz->tail++];
		thiz->tail &= (ZRTOS_CBUFFER__CFG_DATA_LENGTH - 1);
		if(zrtos_cbuffer_node__is_empty(thiz)
		&& zrtos_clist_node__has_next_node(&thiz->node)){
			zrtos_cbuffer_node__free(thiz,ctx);
		}
	}else{
		ret = ENODATA;
	}
	return ret;
}

zrtos_error_t zrtos_cbuffer__put(zrtos_cbuffer_t *thiz,uint8_t val){
	zrtos_cbuffer_node_t *node = zrtos_types__get_container_of(
		 zrtos_clist__get_first_node(thiz)
		,zrtos_cbuffer_node_t
		,node
	);
	return zrtos_cbuffer_node__put(node,thiz,val);
}

zrtos_error_t zrtos_cbuffer__get(zrtos_cbuffer_t *thiz,uint8_t *out){
	zrtos_cbuffer_node_t *node = zrtos_types__get_container_of(
		 zrtos_clist__get_first_node(thiz)
		,zrtos_cbuffer_node_t
		,node
	);
	return zrtos_cbuffer_node__get(node,thiz,out);
}

bool zrtos_cbuffer__is_empty(zrtos_cbuffer_t *thiz){
	zrtos_cbuffer_node_t *node = zrtos_types__get_container_of(
		 zrtos_clist__get_first_node(&thiz->root)
		,zrtos_cbuffer_node_t
		,node
	);
	return zrtos_cbuffer_node__is_empty(node);
}

void zrtos_cbuffer__clear(zrtos_cbuffer_t *thiz){
	zrtos_cbuffer_node_t *node = zrtos_types__get_container_of(
		 zrtos_clist__get_root(&thiz->root)
		,zrtos_cbuffer_node_t
		,node
	);

	while(zrtos_clist_node__has_next_node(&node->node)){
		zrtos_cbuffer_node__free(node,thiz);
		node = zrtos_types__get_container_of(
			 zrtos_clist__get_root(&thiz->root)
			,zrtos_cbuffer_node_t
			,node
		);
	}

	node->head = node->tail = 0;
}


#ifdef __cplusplus
}
#endif
#endif