/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_CDLIST_H
#define ZRTOS_CDLIST_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/types.h>
#include <zrtos/clist.h>


typedef struct _zrtos_cdlist_node_t{
	zrtos_clist_node_t next;//first
	zrtos_clist_node_t prev;//last
}zrtos_cdlist_node_t;

typedef struct _zrtos_cdlist_t{
	zrtos_clist_t first;
	zrtos_clist_t last;
}zrtos_cdlist_t;

bool zrtos_cdlist_node__init(zrtos_cdlist_node_t *thiz){
	zrtos_clist_node__init(&thiz->next);
	zrtos_clist_node__init(&thiz->prev);
	return true;
}

zrtos_cdlist_node_t *zrtos_cdlist_node__get_next_node(
	zrtos_cdlist_node_t *node
){
	return zrtos_types__get_container_of(
		 zrtos_clist_node__get_next_node(&thiz->next)
		,zrtos_cdlist_node_t
		,next
	);
}

bool zrtos_cdlist_node__has_next_node(
	zrtos_cdlist_node_t *thiz
){
	return zrtos_cdlist_node__get_next_node(thiz) != thiz;
}

zrtos_cdlist_node_t *zrtos_cdlist_node__get_previous_node(
	zrtos_cdlist_node_t *thiz
){
	return zrtos_types__get_container_of(
		 zrtos_clist_node__get_next_node(&thiz->prev)
		,zrtos_cdlist_node_t
		,prev
	);
}

bool zrtos_cdlist__init(zrtos_cdlist_t *thiz){
	zrtos_clist__init(&thiz->first);
	zrtos_clist__init(&thiz->last);
	return true;
}

zrtos_cdlist_node_t *zrtos_cdlist__get_first_node(zrtos_cdlist_t *thiz){
	return zrtos_types__get_container_of_ex(
		 zrtos_clist__get_root(&thiz->first)
		,zrtos_cdlist_node_t
		,next
	);
}

zrtos_cdlist_node_t *zrtos_cdlist__get_last_node(zrtos_cdlist_t *thiz){
	return zrtos_types__get_container_of_ex(
		 zrtos_clist__get_root(&thiz->last)
		,zrtos_cdlist_node_t
		,prev
	);
}

bool zrtos_cdlist__push(zrtos_cdlist_t *thiz,zrtos_cdlist_node_t *node){
	zrtos_clist__unshift(
		 &thiz->first
		,&node->next
	);
	zrtos_clist__push(
		 &thiz->last
		,&node->prev
	);

	return true;
}

bool zrtos_cdlist__delete(zrtos_cdlist_t *thiz,zrtos_cdlist_node_t *node){
	zrtos_cdlist_node_t *next = zrtos_cdlist_node__get_next_node(node);
	zrtos_cdlist_node_t *prev = zrtos_cdlist_node__get_previous_node(node);

	if(prev != node){
		prev->next.next = node->next.next;
		next->prev.next = node->prev.next;
	}else{
		thiz->first.root = 0;
		thiz->last.root = 0;
	}
	node->next.next = &node->next;
	node->prev.next = &node->next;

	return true;
}

zrtos_cdlist_node_t *zrtos_cdlist__pop(zrtos_cdlist_t *thiz){
	zrtos_cdlist_node_t *ret = zrtos_cdlist__get_last_node(thiz);
	if(ret){
		zrtos_cdlist__delete(thiz,ret);
	}
	return ret;
}

bool zrtos_cdlist__unshift(zrtos_cdlist_t *thiz,zrtos_cdlist_node_t *node){
	zrtos_cdlist__push(thiz,node);
	thiz->first.root = &node->next;

	return true;
}

zrtos_cdlist_node_t *zrtos_cdlist__shift(zrtos_cdlist_t *thiz){
	zrtos_cdlist_node_t *ret = zrtos_cdlist__get_first_node(thiz);
	if(ret){
		zrtos_cdlist__delete(thiz,ret);
	}
	return ret;
}

void zrtos_cdlist__each(
	 zrtos_cdlist_t *thiz
	,bool (*callback)(zrtos_cdlist_node_t *node,void *arg)
	,void *arg
){
	zrtos_cdlist_node_t *node = zrtos_cdlist__get_root(thiz);
	zrtos_cdlist_node_t *root = node;
	if(node){
		zrtos_cdlist_node_t *next;
		do{
			next = zrtos_cdlist_node__get_next_node(node);
		}while(callback(node,arg) && (node = next) != root);
	}
}


#ifdef __cplusplus
}
#endif
#endif