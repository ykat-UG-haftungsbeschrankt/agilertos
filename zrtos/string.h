/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_STRING_H
#define ZRTOS_STRING_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/types.h>


typedef struct _zrtos_string_t{
	char   *data;
	size_t length;
}zrtos_string_t;

bool zrtos_string__init(
	 zrtos_string_t *thiz
	,char *data
	,size_t length
){
	thiz->data = data;
	thiz->length = length;
	return true;
}

char *zrtos_string__get_data(zrtos_string_t *thiz){
	return thiz->data;
}

size_t zrtos_string__get_length(zrtos_string_t *thiz){
	return thiz->length;
}


#ifdef __cplusplus
}

namespace zrtos{
	class string{
		zrtos_string_t thiz;
		string(
			 char *data
			,size_t length
		){
			zrtos_string__init(
				 &this->thiz
				,data
				,length
			);
		}
		char *getData(){
			return zrtos_string__get_data(&this->thiz);
		}
		size_t getLength(){
			return zrtos_string__get_length(&this->thiz);
		}
	};
}

#endif
#endif