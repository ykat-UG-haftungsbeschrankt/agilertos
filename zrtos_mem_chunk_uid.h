/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_MEM_CHUNK_UID_H
#define ZRTOS_MEM_CHUNK_UID_H
#ifdef __cplusplus
extern "C" {
#endif


typedef struct _zrtos_mem_chunk_uid_t{
	uint8_t uid;
}zrtos_mem_chunk_uid_t;

void zrtos_mem_chunk_uid__set_error(zrtos_mem_chunk_uid_t *thiz){
	thiz->uid = 0;
}

bool zrtos_mem_chunk_uid__is_error(zrtos_mem_chunk_uid_t *thiz){
	return thiz->uid == 0;
}

zrtos_mem_chunk_uid_t zrtos_mem_chunk_uid__error(void){
	zrtos_mem_chunk_uid_t ret;
	zrtos_mem_chunk_uid__set_error(&ret);
	return ret;
}


#ifdef __cplusplus
}
#endif
#endif