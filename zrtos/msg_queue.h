/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_MSG_QUEUE_H
#define ZRTOS_MSG_QUEUE_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/types.h>
#include <zrtos/cbuffer.h>


typedef struct _zrtos_msg_queue_header_t{
	size_t length;
}__attribute__((packed))zrtos_msg_queue_header_t;

typedef struct _zrtos_msg_queue_t{
	zrtos_cbuffer_t          cbuffer;
	size_t                   msg_count;
	zrtos_msg_queue_header_t header;
}zrtos_msg_queue_t;


bool zrtos_msg_queue__is_empty(zrtos_msg_queue_t *thiz){
	return thiz->msg_count == 0 && thiz->header.length == 0;
}

zrtos_error_t zrtos_msg_queue__put_length(
	 zrtos_msg_queue_t *thiz
	,size_t            len
){
	zrtos_msg_queue_header_t header = {
		.length = len
	};
	size_t outlen;
	zrtos_error_t ret = zrtos_cbuffer__put_ex(
		 &thiz->cbuffer
		,1
		,&outlen
		,&header
		,sizeof(header)
	);
	return zrtos_error__is_success(ret);
}

zrtos_error_t zrtos_msg_queue__put_data(
	 zrtos_msg_queue_t *thiz
	,void              *data
	,size_t            len
){
	size_t outlen;
	zrtos_error_t ret = zrtos_cbuffer__put_ex(
		 &thiz->cbuffer
		,1
		,&outlen
		,data
		,len
	);
	if(zrtos_error__is_success(ret)){
		thiz->msg_count++;
	}
	return ret;
}

zrtos_error_t zrtos_msg_queue__put(
	 zrtos_msg_queue_t *thiz
	,void              *data
	,size_t            len
){
	zrtos_msg_queue_header_t header = {
		.length = len
	};
	size_t outlen;
	zrtos_error_t ret = zrtos_cbuffer__put_ex(
		 &thiz->cbuffer
		,2
		,&outlen
		,&header
		,sizeof(header)
		,data
		,len
	);
	if(zrtos_error__is_success(ret)){
		thiz->msg_count++;
	}
	return ret;
}

zrtos_error_t zrtos_msg_queue__get(
	 zrtos_msg_queue_t *thiz
	,void              *data
	,size_t            len
	,size_t            *outlen
){
	zrtos_error_t ret;
	if(thiz->header.length){
L_READ_MESSAGE_BODY:
		ret = zrtos_cbuffer__get_ex(
			 &thiz->cbuffer
			,data
			,ZRTOS_TYPES__MIN(len,thiz->header.length)
			,outlen
		);
		thiz->header.length -= *outlen;
		if(thiz->header.length == 0){
			thiz->msg_count--;
		}else{
			ret = ZRTOS_ERROR__AGAIN;
		}
	}else if(thiz->msg_count && zrtos_cbuffer__can_read_length(
 		 &thiz->cbuffer
		,sizeof(thiz->header)
	)){
		ret = zrtos_cbuffer__get_ex(
			 &thiz->cbuffer
			,&thiz->header
			,sizeof(thiz->header)
			,outlen
		);
		if(zrtos_error__is_success(ret)){
			goto L_READ_MESSAGE_BODY;
		}
	}else{
		ret = ZRTOS_ERROR__NODATA;
	}
	return ret;
}


#ifdef __cplusplus
}
#endif
#endif