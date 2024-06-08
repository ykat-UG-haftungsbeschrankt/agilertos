/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VHEAP_TYPE_H
#define ZRTOS_VHEAP_TYPE_H
#ifdef __cplusplus
extern "C" {
#endif


typedef enum{
	 ZRTOS_VHEAP_TYPE__UNUSED      = 0x00
	,ZRTOS_VHEAP_TYPE__MALLOC      = 0x11
	,ZRTOS_VHEAP_TYPE__TASK_IDLE   = 0x22
	,ZRTOS_VHEAP_TYPE__TASK_ACTIVE = 0x33
	,ZRTOS_VHEAP_TYPE__TASK_DONE   = 0x44
}zrtos_vheap_type_t;


#ifdef __cplusplus
}
#endif
#endif