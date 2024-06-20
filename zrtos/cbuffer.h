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
#include <stdarg.h>


#ifndef ZRTOS_CBUFFER__CFG_DATA_LENGTH
#define ZRTOS_CBUFFER__CFG_DATA_LENGTH 16
#endif

ZRTOS_ASSERT__STATIC_IS_POWER_OF_TWO(ZRTOS_CBUFFER__CFG_DATA_LENGTH);

typedef struct _zrtos_cbuffer_node_t{
	zrtos_clist_node_t  node;
	uint8_t             head;
	uint8_t             tail;
	uint8_t             data[ZRTOS_CBUFFER__CFG_DATA_LENGTH];
}zrtos_cbuffer_node_t;

typedef struct _zrtos_cbuffer_t{
	zrtos_clist_t      root;
}zrtos_cbuffer_t;

typedef struct _zrtos_cbuffer_state_t{
	zrtos_cbuffer_node_t *first;
	zrtos_cbuffer_node_t *last;
	uint8_t              head;
}zrtos_cbuffer_state_t;

zrtos_cbuffer_node_t *zrtos_cbuffer__get_first_node(zrtos_cbuffer_t *thiz){
	zrtos_cbuffer_node_t *node = zrtos_types__get_container_of(
		 zrtos_clist__get_first_node(&thiz->root)
		,zrtos_cbuffer_node_t
		,node
	);
	return node;
}

zrtos_cbuffer_node_t *zrtos_cbuffer_node__get_next_node(zrtos_cbuffer_node_t *thiz){
	zrtos_cbuffer_node_t *node = zrtos_types__get_container_of(
		 zrtos_clist_node__get_next_node(&thiz->node)
		,zrtos_cbuffer_node_t
		,node
	);
	return node;
}

void zrtos_cbuffer__start_write_transaction(
	 zrtos_cbuffer_t *thiz
	,zrtos_cbuffer_state_t *state
){
	zrtos_cbuffer_node_t *next;
	state->last->head = state->head;
	while((next = zrtos_clist_node__get_next_node(&state->last.node))
	   != state->first){
		zrtos_cbuffer_node__free(
			 next
			,thiz
		);
	}
}

void zrtos_cbuffer__rollback(
	 zrtos_cbuffer_t *thiz
	,zrtos_cbuffer_state_t *state
){
	zrtos_cbuffer_node_t *next;
	state->last->head = state->head;
	while((next = zrtos_clist_node__get_next_node(&state->last.node))
	   != state->first){
		zrtos_cbuffer_node__free(
			 next
			,thiz
		);
	}
}

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
		ret = EAGAIN;
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

zrtos_error_t zrtos_cbuffer__put_ex(
	 zrtos_cbuffer_t *thiz
	,size_t len
	,...
/*
	,void *data
	,size_t len
*/
){
	zrtos_error_t ret = EXIT_SUCCESS;
	uint8_t *data;
	size_t data_len;
	va_list args;
	va_start(args,outlen);
	while(len-- && ret == EXIT_SUCCESS){
		data = va_arg(args,void*);
		data_len = va_arg(args,size_t);
		while(data_len-- && ret == EXIT_SUCCESS){
			ret = zrtos_cbuffer__put(
				 thiz
				,*data++
			);
		}
	}
L_RETURN:
	va_end(args);
	return ret;

	zrtos_error_t ret = EXIT_SUCCESS;
	uint8_t *tmp = data;
	while(len--
	   && EXIT_SUCCESS == (ret = zrtos_cbuffer__put(thiz,*tmp++))){
		;
	}
	*outlen = zrtos_types__ptr_get_byte_distance(tmp,data);
	return ret;
}

zrtos_error_t zrtos_cbuffer__get(zrtos_cbuffer_t *thiz,uint8_t *out){
	zrtos_cbuffer_node_t *node = zrtos_types__get_container_of(
		 zrtos_clist__get_first_node(thiz)
		,zrtos_cbuffer_node_t
		,node
	);
	return zrtos_cbuffer_node__get(node,thiz,out);
}

zrtos_error_t zrtos_cbuffer__get_ex(
	 zrtos_cbuffer_t *thiz
	,void *data
	,size_t len
	,size_t *outlen
){
	zrtos_error_t ret = EXIT_SUCCESS;
	uint8_t *tmp = data;
	while(len--
	   && EXIT_SUCCESS == (ret = zrtos_cbuffer__get(thiz,tmp++))){
		;
	}
	*outlen = zrtos_types__ptr_get_byte_distance(tmp,data);
	return ret;
}

bool zrtos_cbuffer__is_empty(zrtos_cbuffer_t *thiz){
	zrtos_cbuffer_node_t *node = zrtos_cbuffer__get_first_node(thiz);
	return zrtos_cbuffer_node__is_empty(node);
}

void zrtos_cbuffer__clear(zrtos_cbuffer_t *thiz){
	zrtos_cbuffer_node_t *node = zrtos_cbuffer__get_first_node(thiz);

	while(zrtos_clist_node__has_next_node(&node->node)){
		zrtos_cbuffer_node__free(node,thiz);
		node = zrtos_cbuffer__get_first_node(thiz);
	}

	node->head = node->tail = 0;
}


#ifdef __cplusplus
}
#endif
#endif