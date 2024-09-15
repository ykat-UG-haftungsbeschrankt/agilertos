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


#include <stdarg.h>

#include <zrtos/types.h>
#include <zrtos/error.h>
#include <zrtos/list.h>
#include <zrtos/malloc_limit.h>
#include <zrtos/assert.h>
#include <zrtos/cast.h>


#ifndef ZRTOS_CBUFFER__CFG_DATA_LENGTH
#define ZRTOS_CBUFFER__CFG_DATA_LENGTH 16
#endif

#ifndef ZRTOS_CBUFFER__CFG_MALLOC_LIMIT
#define ZRTOS_CBUFFER__CFG_MALLOC_LIMIT 200
#endif

#ifdef ZRTOS_MALLOC__CFG_DISABLE_FREE
#error "ZRTOS_MALLOC__CFG_DISABLE_FREE not supported with cbuffer"
#endif

ZRTOS_ASSERT__STATIC_IS_POWER_OF_TWO(ZRTOS_CBUFFER__CFG_DATA_LENGTH);

typedef struct _zrtos_cbuffer_node_t{
	zrtos_list_node_t   node;
	uint8_t             data[ZRTOS_CBUFFER__CFG_DATA_LENGTH];
	uint8_t             head;
	uint8_t             tail;
}zrtos_cbuffer_node_t;

typedef struct _zrtos_cbuffer_t{
	zrtos_list_t      root;
}zrtos_cbuffer_t;

typedef struct _zrtos_cbuffer_write_transaction_t{
	zrtos_cbuffer_t      thiz;
	uint8_t              head;
}zrtos_cbuffer_write_transaction_t;

/// @todo mutex lock zrtos_cbuffer__malloc_limit
zrtos_malloc_limit_t zrtos_cbuffer__malloc_limit = ZRTOS_MALLOC_LIMIT__INIT();

zrtos_cbuffer_node_t *zrtos_cbuffer__get_first_node(zrtos_cbuffer_t *thiz){
	zrtos_cbuffer_node_t *node = zrtos_types__get_container_of(
		 zrtos_list__get_first_node(&thiz->root)
		,zrtos_cbuffer_node_t
		,node
	);
	return node;
}

zrtos_cbuffer_node_t *zrtos_cbuffer__get_last_node(zrtos_cbuffer_t *thiz){
	zrtos_cbuffer_node_t *node = zrtos_types__get_container_of(
		 zrtos_list__get_last_node(&thiz->root)
		,zrtos_cbuffer_node_t
		,node
	);
	return node;
}

zrtos_cbuffer_node_t *zrtos_cbuffer_node__get_next_node(zrtos_cbuffer_node_t *thiz){
	zrtos_cbuffer_node_t *node = zrtos_types__get_container_of(
		 zrtos_list_node__get_next_node(&thiz->node)
		,zrtos_cbuffer_node_t
		,node
	);
	return node;
}

bool zrtos_cbuffer_node__init(
	 zrtos_cbuffer_node_t *thiz
	,zrtos_cbuffer_t *ctx
){
	zrtos_list_node__init(&thiz->node);
	zrtos_list__push(&ctx->root,&thiz->node);
	thiz->head = 0;
	thiz->tail = 0;
	return true;
}

zrtos_cbuffer_node_t *zrtos_cbuffer_node__new(zrtos_cbuffer_t *ctx){
	zrtos_cbuffer_node_t *ret = ZRTOS_CAST(
		 zrtos_cbuffer_node_t*
		,zrtos_malloc_limit__malloc(
			&zrtos_cbuffer__malloc_limit
			,sizeof(zrtos_cbuffer_node_t)
			,ZRTOS_CBUFFER__CFG_MALLOC_LIMIT
		)
	);
	if(ret){
		zrtos_cbuffer_node__init(ret,ctx);
	}
	return ret;
}

void zrtos_cbuffer_node__free(zrtos_cbuffer_node_t *thiz,zrtos_cbuffer_t *ctx){
	zrtos_list__delete(&ctx->root,&thiz->node);
	zrtos_malloc_limit__free(&zrtos_cbuffer__malloc_limit,thiz);
}

bool zrtos_cbuffer__init(
	 zrtos_cbuffer_t *thiz
){
	zrtos_list__init(&thiz->root);
	return zrtos_cbuffer_node__new(thiz) != 0;
}

void zrtos_cbuffer__deinit_callback(
	 zrtos_list_t *thiz
	,zrtos_list_node_t *node
){
	zrtos_cbuffer_node__free(
		zrtos_types__get_container_of(
			 node
			,zrtos_cbuffer_node_t
			,node
		)
		,zrtos_types__get_container_of(
			 thiz
			,zrtos_cbuffer_t
			,root
		)
	);
}

void zrtos_cbuffer__deinit(
	 zrtos_cbuffer_t *thiz
){
	zrtos_list__deinit(&thiz->root,zrtos_cbuffer__deinit_callback);
}

void zrtos_cbuffer__start_write_transaction(
	 zrtos_cbuffer_t *thiz
	,zrtos_cbuffer_write_transaction_t *txn
){
	txn->thiz = *thiz;
	txn->head = zrtos_cbuffer__get_last_node(thiz)->head;
}

void zrtos_cbuffer__rollback_write_transaction(
	 zrtos_cbuffer_t *thiz
	,zrtos_cbuffer_write_transaction_t *txn
){
	zrtos_cbuffer_node_t *next;
	zrtos_cbuffer_node_t *node = zrtos_cbuffer__get_last_node(&txn->thiz);
	node->head = txn->head;
	while((next = zrtos_cbuffer_node__get_next_node(node))){
		zrtos_cbuffer_node__free(
			 next
			,thiz
		);
	}
}

static size_t zrtos_cbuffer_node__get_length(
	 zrtos_cbuffer_node_t *thiz
){
	return (thiz->head - thiz->tail) & (ZRTOS_CBUFFER__CFG_DATA_LENGTH - 1);
}

bool zrtos_cbuffer_node__is_empty(zrtos_cbuffer_node_t *thiz){
	//return zrtos_cbuffer_node__get_length(thiz) == 0;
	return thiz->head == thiz->tail;
}

static size_t zrtos_cbuffer_node__get_free_space(
	 zrtos_cbuffer_node_t *thiz
){
	return (ZRTOS_CBUFFER__CFG_DATA_LENGTH - 1)
	     - zrtos_cbuffer_node__get_length(thiz)
	;
}

zrtos_error_t zrtos_cbuffer_node__put(
	 zrtos_cbuffer_node_t *thiz
	,zrtos_cbuffer_t *ctx
	,uint8_t val
){
	zrtos_error_t ret = ZRTOS_ERROR__SUCCESS;

	if(zrtos_cbuffer_node__get_free_space(thiz) >= 1){
		thiz->data[thiz->head++] = val;
		thiz->head &= (ZRTOS_CBUFFER__CFG_DATA_LENGTH - 1);
	}else{
		zrtos_cbuffer_node_t *node = zrtos_cbuffer_node__new(ctx);
		if(node){
			ret = zrtos_cbuffer_node__put(
				 node
				,ctx
				,val
			);
		}else{
			ret = ZRTOS_ERROR__NOMEM;
		}
	}
	return ret;
}

zrtos_error_t zrtos_cbuffer_node__get(
	zrtos_cbuffer_node_t *thiz
	,zrtos_cbuffer_t *ctx
	,uint8_t *out
){
	zrtos_error_t ret = ZRTOS_ERROR__SUCCESS;
	if(!zrtos_cbuffer_node__is_empty(thiz)){
		*out = thiz->data[thiz->tail++];
		thiz->tail &= (ZRTOS_CBUFFER__CFG_DATA_LENGTH - 1);
		if(zrtos_cbuffer_node__is_empty(thiz)
		&& zrtos_list_node__has_next_node(&thiz->node)){
			zrtos_cbuffer_node__free(thiz,ctx);
		}
	}else{
		ret = ZRTOS_ERROR__AGAIN;
	}
	return ret;
}

zrtos_error_t zrtos_cbuffer__hash(
	zrtos_cbuffer_t *thiz
	,size_t length
	,void (*callback)(void *callback_args,uint8_t ch)
	,void *callback_args
){
	zrtos_cbuffer_node_t *node = zrtos_cbuffer__get_first_node(thiz);
	size_t tail;
	size_t head;

	while(node && length){
		head = node->head;
		tail = node->tail;

		while(tail != head && length--){
			callback(callback_args,node->data[tail++]);
		}

		node = zrtos_cbuffer_node__get_next_node(node);
	}

	return length == 0 ? ZRTOS_ERROR__SUCCESS : ZRTOS_ERROR__INVAL;
}

zrtos_error_t zrtos_cbuffer__put(zrtos_cbuffer_t *thiz,uint8_t val){
	zrtos_cbuffer_node_t *node = zrtos_types__get_container_of(
		 zrtos_list__get_last_node(&thiz->root)
		,zrtos_cbuffer_node_t
		,node
	);
	return zrtos_cbuffer_node__put(node,thiz,val);
}

zrtos_error_t zrtos_cbuffer__put_ex(
	 zrtos_cbuffer_t *thiz
	,size_t len
	,size_t *outlen
	,...
/*
	,void *data
	,size_t len
*/
){
	zrtos_error_t ret = ZRTOS_ERROR__SUCCESS;
	uint8_t *data;
	size_t data_len;
	va_list args;
	zrtos_cbuffer_write_transaction_t txn;

	va_start(args,outlen);

	zrtos_cbuffer__start_write_transaction(thiz,&txn);

	while(len-- && zrtos_error__is_success(ret)){
		data = ZRTOS_CAST(uint8_t*,va_arg(args,void*));
		data_len = va_arg(args,size_t);
		while(data_len-- && zrtos_error__is_success(ret)){
			ret = zrtos_cbuffer__put(
				 thiz
				,*data++
			);
		}
	}

	if(zrtos_error__is_error(ret)){
		zrtos_cbuffer__rollback_write_transaction(thiz,&txn);
	}

	va_end(args);

	return ret;
}

zrtos_error_t zrtos_cbuffer__get(zrtos_cbuffer_t *thiz,uint8_t *out){
	zrtos_cbuffer_node_t *node = zrtos_types__get_container_of(
		 zrtos_list__get_first_node(&thiz->root)
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
	zrtos_error_t ret = ZRTOS_ERROR__SUCCESS;
	uint8_t *tmp = ZRTOS_CAST(uint8_t*,data);
	while(len--
	   && ZRTOS_ERROR__SUCCESS == (ret = zrtos_cbuffer__get(thiz,tmp++))){
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

	while(zrtos_list_node__has_next_node(&node->node)){
		zrtos_cbuffer_node__free(node,thiz);
		node = zrtos_cbuffer__get_first_node(thiz);
	}

	node->head = node->tail = 0;
}

zrtos_error_t zrtos_cbuffer__can_read(
	 zrtos_cbuffer_t *thiz
){
	return zrtos_cbuffer__is_empty(thiz)
	     ? ZRTOS_ERROR__AGAIN
	     : ZRTOS_ERROR__SUCCESS
	;
}

bool zrtos_cbuffer__can_read_length(
	 zrtos_cbuffer_t *thiz
	,size_t length
){
	zrtos_cbuffer_node_t *node = zrtos_cbuffer__get_first_node(thiz);

	while(node
	&& length
	&& !zrtos_cbuffer_node__is_empty(node)){
		length -= ZRTOS_TYPES__MIN(
			 ((size_t)(node->head - node->tail))
			,length
		);
		node = zrtos_cbuffer_node__get_next_node(node);
	}

	return length == 0;
}

size_t zrtos_cbuffer__get_length(
	 zrtos_cbuffer_t *thiz
){
	zrtos_cbuffer_node_t *node = zrtos_cbuffer__get_first_node(thiz);
	size_t length = 0;

	while(node){
		length += zrtos_cbuffer_node__get_length(node);
		node = zrtos_cbuffer_node__get_next_node(node);
	}

	return length == 0;
}

zrtos_error_t zrtos_cbuffer__can_write(
	 zrtos_cbuffer_t *thiz
){
	return ZRTOS_ERROR__SUCCESS;
}

zrtos_error_t zrtos_cbuffer__pipe(
	 zrtos_cbuffer_t *thiz
	,zrtos_cbuffer_t *src
	,size_t length
){
	zrtos_error_t ret = ZRTOS_ERROR__SUCCESS;
	uint8_t tmp;
	zrtos_cbuffer_write_transaction_t txn;

	zrtos_cbuffer__start_write_transaction(thiz,&txn);

	while(zrtos_error__is_success(ret) && length--){
		ret = zrtos_cbuffer__get(src,&tmp);
		if(zrtos_error__is_success(ret)){
			ret = zrtos_cbuffer__put(thiz,tmp);
		}
	}

	if(zrtos_error__is_error(ret)){
		zrtos_cbuffer__rollback_write_transaction(thiz,&txn);
	}

	return ret;
}
#if 0
void zrtos_cbuffer_node__debug(
	 zrtos_cbuffer_node_t *thiz
){
	Serial.println("zrtos_cbuffer_node{");
	Serial.println("head:");
	Serial.print(thiz->head);
	Serial.println("tail:");
	Serial.print(thiz->tail);
	Serial.println("data:[");

	size_t length = 0;

	for(;length < ZRTOS_CBUFFER__CFG_DATA_LENGTH-1;length++){
		Serial.print(length);
		Serial.print(":[");
		Serial.print(thiz->data[length],HEX);
		Serial.println("],");
	}

	Serial.println("]}");
}

void zrtos_cbuffer__debug(
	 zrtos_cbuffer_t *thiz
){
	zrtos_cbuffer_node_t *node = zrtos_cbuffer__get_first_node(thiz);
	Serial.print("zrtos_cbuffer{");
	while(node){
		zrtos_cbuffer_node__debug(node);
		node = zrtos_cbuffer_node__get_next_node(node);
	}
	Serial.print("}");
}
#endif

#ifdef __cplusplus
}
#endif
#endif