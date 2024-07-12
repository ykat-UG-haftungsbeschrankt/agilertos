/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_LIST_H
#define ZRTOS_LIST_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/types.h>


typedef struct _zrtos_list_node_t{
	struct _zrtos_list_node_t *next;
}zrtos_list_node_t;

typedef struct _zrtos_list_t{
	zrtos_list_node_t *first;
	zrtos_list_node_t *last;
}zrtos_list_t;

zrtos_list_node_t *zrtos_list__get_first_node(zrtos_list_t *thiz){
	return thiz->first;
}

zrtos_list_node_t *zrtos_list__get_last_node(zrtos_list_t *thiz){
	return thiz->last;
}

bool zrtos_list_node__init(zrtos_list_node_t *thiz){
	thiz->next = 0;
	return true;
}

zrtos_list_node_t *zrtos_list_node__get_next_node(
	zrtos_list_node_t *node
){
	return node->next;
}

bool zrtos_list_node__has_next_node(
	zrtos_list_node_t *node
){
	return node->next != 0;
}

bool zrtos_list__init(zrtos_list_t *thiz){
	thiz->first = 0;
	thiz->last = 0;
	return true;
}

bool zrtos_list__push(zrtos_list_t *thiz,zrtos_list_node_t *node){
	zrtos_list_node_t *last = zrtos_list__get_last_node(thiz);
	if(last){
		thiz->last = last->next = node;
	}else{
		thiz->first = thiz->last = node;
	}
	return true;
}

bool zrtos_list__unshift(zrtos_list_t *thiz,zrtos_list_node_t *node){
	zrtos_list_node_t *first = zrtos_list__get_first_node(thiz);
	if(first){
		thiz->first = node;
		node->next = first;
	}else{
		thiz->first = thiz->last = node;
	}
	return true;
}

zrtos_list_node_t *zrtos_list__shift(zrtos_list_t *thiz){
	zrtos_list_node_t *ret = zrtos_list__get_first_node(thiz);
	if(ret){
		thiz->first = ret->next;
		if(thiz->first == 0){
			thiz->last = 0;
		}
	}
	return ret;
}

void zrtos_list__shift_and_push(zrtos_list_t *thiz){
	zrtos_list_node_t *node = zrtos_list__shift(thiz);
	if(node){
		zrtos_list__push(thiz,node);
	}
}

void zrtos_list__delete(zrtos_list_t *thiz,zrtos_list_node_t *node){
	zrtos_list_node_t *next;
	zrtos_list_node_t *prev = zrtos_list__get_first_node(thiz);
	if(node == prev){
		zrtos_list__shift(thiz);
	}else{
		while((next = prev->next) != node){
			prev = next;
		}
		if((prev->next = node->next) == 0){
			thiz->last = prev;
		}
	}
}

bool zrtos_list__is_empty(zrtos_list_t *thiz){
	return zrtos_list__get_first_node(thiz) == 0;
}

void zrtos_list__deinit(
	zrtos_list_t *thiz
	,void (*callback)(zrtos_list_t *thiz,zrtos_list_node_t *node)
){
	while(!zrtos_list__is_empty(thiz)){
		zrtos_list_node_t *node = zrtos_list__shift(thiz);
		callback(thiz,node);
	}
}

void zrtos_list__each(
	 zrtos_list_t *thiz
	,bool (*callback)(zrtos_list_node_t *node,void *arg)
	,void *arg
){
	zrtos_list_node_t *node = zrtos_list__get_first_node(thiz);
	zrtos_list_node_t *root = node;
	if(node){
		zrtos_list_node_t *next;
		do{
			next = node->next;
		}while(callback(node,arg) && (node = next) != root);
	}
}


#ifdef __cplusplus
}
#endif
#endif