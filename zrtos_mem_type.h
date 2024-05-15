/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_MEM_TYPE_H
#define ZRTOS_MEM_TYPE_H
#ifdef __cplusplus
extern "C" {
#endif


typedef enum{
	 ZRTOS_MEM_CHUNK_TYPE__UNUSED      = 0x00
	,ZRTOS_MEM_CHUNK_TYPE__MALLOC      = 0x11
	,ZRTOS_MEM_CHUNK_TYPE__TASK_IDLE   = 0x22
	,ZRTOS_MEM_CHUNK_TYPE__TASK_ACTIVE = 0x33
}zrtos_mem_type_t;


#ifdef __cplusplus
}
#endif
#endif