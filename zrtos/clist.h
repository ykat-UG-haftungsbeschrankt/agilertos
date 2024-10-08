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


#include <zrtos/types.h>


typedef struct _zrtos_clist_node_t{
	struct _zrtos_clist_node_t *next;
}zrtos_clist_node_t;

typedef struct _zrtos_clist_t{
	zrtos_clist_node_t *root;
}zrtos_clist_t;

zrtos_clist_node_t *zrtos_clist__get_root(zrtos_clist_t *thiz){
	return thiz->root;
}

void zrtos_clist__set_root(zrtos_clist_t *thiz,zrtos_clist_node_t *node){
	thiz->root = node;
}

bool zrtos_clist_node__init(zrtos_clist_node_t *thiz){
	thiz->next = thiz;
	return true;
}

zrtos_clist_node_t *zrtos_clist_node__get_next_node(
	zrtos_clist_node_t *node
){
	return node->next;
}

bool zrtos_clist_node__has_next_node(
	zrtos_clist_node_t *node
){
	return node->next != node;
}

zrtos_clist_node_t *zrtos_clist_node__get_previous_node(
	zrtos_clist_node_t *node
){
	zrtos_clist_node_t *ret = node;
	zrtos_clist_node_t *next;
	while((next = ret->next) != node){
		ret = next;
	}
	return ret;
}

bool zrtos_clist__init(zrtos_clist_t *thiz){
	thiz->root = 0;
	return true;
}

zrtos_clist_node_t *zrtos_clist__get_first_node(zrtos_clist_t *thiz){
	return thiz->root;
}

zrtos_clist_node_t *zrtos_clist__get_last_node(zrtos_clist_t *thiz){
	zrtos_clist_node_t *root = zrtos_clist__get_root(thiz);
	return root
	     ? zrtos_clist_node__get_previous_node(root)
	     : root;
}

static void zrtos_clist_node__append(
	 zrtos_clist_node_t *thiz
	,zrtos_clist_node_t *node
){
	node->next = thiz->next;
	thiz->next = node;
}

bool zrtos_clist__push(zrtos_clist_t *thiz,zrtos_clist_node_t *node){
	zrtos_clist_node_t *last = zrtos_clist__get_last_node(thiz);
	if(last){
		zrtos_clist_node__append(last,node);
	}else{
		thiz->root = node;
	}
	return true;
}

bool zrtos_clist__delete(zrtos_clist_t *thiz,zrtos_clist_node_t *node){
	zrtos_clist_node_t *prev = zrtos_clist_node__get_previous_node(node);

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
	if(thiz->root){
		node->next = thiz->root;
	}
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

void zrtos_clist__shift_and_push(zrtos_clist_t *thiz){
	zrtos_clist_node_t *node = zrtos_clist__get_first_node(thiz);
	if(node){
		zrtos_clist__set_root(
			 thiz
			,zrtos_clist_node__get_next_node(node)
		);
	}
}

void zrtos_clist__each(
	 zrtos_clist_t *thiz
	,bool (*callback)(zrtos_clist_node_t *node,void *arg)
	,void *arg
){
	zrtos_clist_node_t *node = zrtos_clist__get_root(thiz);
	if(node){
		zrtos_clist_node_t *next;
		do{
			next = zrtos_clist_node__get_next_node(node);
		}while(callback(node,arg)
		   && (node = next) != zrtos_clist__get_root(thiz)
		);
	}
}

#define ZRTOS_CLIST__EACH_BEGIN(thiz,node,container,member)                    \
	do{\
		zrtos_clist_t *clist = thiz;\
		zrtos_clist_node_t *tmp = zrtos_clist__get_root(clist);\
		zrtos_clist_node_t *next;\
		container *node;\
		if(tmp){\
			do{\
				next = tmp->next;\
				node = zrtos_types__get_container_of(\
					tmp,container,member\
				);\
				do{

#define ZRTOS_CLIST__EACH_END\
				}while(0);\
				tmp = next;\
			}while(tmp != zrtos_clist__get_root(clist));\
		}\
	}while(0)


#ifdef __cplusplus
}
#endif
#endif