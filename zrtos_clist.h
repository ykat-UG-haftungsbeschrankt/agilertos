/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_CLIST_H
#define ZRTOS_CLIST_H
#ifdef __cplusplus
extern "C" {
#endif


#include "zrtos_types.h"


typedef struct _zrtos_clist_node_t{
	struct _zrtos_clist_node_t *next;
}zrtos_clist_node_t;

typedef struct _zrtos_clist_t{
	zrtos_clist_node_t *root;
}zrtos_clist_t;

zrtos_clist_node_t *zrtos_clist__get_root(zrtos_clist_t *thiz){
	return thiz->root;
}

bool zrtos_clist_node__init(zrtos_clist_node_t *thiz){
	thiz->next = thiz;
	return true;
}

bool zrtos_clist__init(zrtos_clist_t *thiz){
	thiz->root = 0;
	return true;
}

zrtos_clist_node_t *zrtos_clist__get_previous_node(
	 zrtos_clist_t *thiz
	,zrtos_clist_node_t *node
){
	zrtos_clist_node_t *ret = node;
	zrtos_clist_node_t *next;
	while(ret && (next = ret->next) != node){
		ret = next;
	}
	return ret;
}

zrtos_clist_node_t *zrtos_clist__get_first_node(zrtos_clist_t *thiz){
	return thiz->root;
}

zrtos_clist_node_t *zrtos_clist__get_last_node(zrtos_clist_t *thiz){
	return zrtos_clist__get_previous_node(thiz,zrtos_clist__get_root(thiz));
}

bool zrtos_clist__push(zrtos_clist_t *thiz,zrtos_clist_node_t *node){
	zrtos_clist_node_t *root = zrtos_clist__get_root(thiz);
	if(root){
		zrtos_clist_node_t *last = zrtos_clist__get_last_node(thiz);
		node->next = last->next;
		last->next = node;
	}else{
		thiz->root = node;
	}
	return true;
}

bool zrtos_clist__delete(zrtos_clist_t *thiz,zrtos_clist_node_t *node){
	zrtos_clist_node_t *prev = zrtos_clist__get_previous_node(thiz,node);

	if(prev != node){
		prev->next = node->next;
	}else{
		thiz->root = 0;
	}
	node->next = node;

	return true;
}

zrtos_clist_node_t *zrtos_clist__pop(zrtos_clist_t *thiz){
	zrtos_clist_node_t *ret = zrtos_clist__get_last_node(thiz);
	if(ret){
		zrtos_clist__delete(thiz,ret);
	}
	return ret;
}

bool zrtos_clist__unshift(zrtos_clist_t *thiz,zrtos_clist_node_t *node){
	node->next = thiz->root
	           ? thiz->root
	           : node->next
	;
	thiz->root = node;

	return true;
}

zrtos_clist_node_t *zrtos_clist__shift(zrtos_clist_t *thiz){
	zrtos_clist_node_t *ret = zrtos_clist__get_first_node(thiz);
	if(ret){
		zrtos_clist__delete(thiz,ret);
	}
	return ret;
}



void zrtos_clist__each(
	 zrtos_clist_t *thiz
	,bool (*callback)(zrtos_clist_node_t *node,void *arg)
	,void *arg
){
	zrtos_clist_node_t *node = zrtos_clist__get_root(thiz);
	zrtos_clist_node_t *root = node;
	if(node){
		zrtos_clist_node_t *next;
		do{
			next = node->next;
		}while(callback(node,arg) && (node = next) != root);
	}
}


#ifdef __cplusplus
}
#endif
#endif