/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_MAX7219_H
#define ZRTOS_VFS_MODULE_MAX7219_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/vfs_module.h>
#include <zrtos/mem.h>

typedef enum{
	 ZRTOS_VFS_MODULE_MAX7219_OPCODE__NOOP         = 0
	,ZRTOS_VFS_MODULE_MAX7219_OPCODE__DIGIT_0      = 1
	,ZRTOS_VFS_MODULE_MAX7219_OPCODE__DIGIT_1      = 2
	,ZRTOS_VFS_MODULE_MAX7219_OPCODE__DIGIT_2      = 3
	,ZRTOS_VFS_MODULE_MAX7219_OPCODE__DIGIT_3      = 4
	,ZRTOS_VFS_MODULE_MAX7219_OPCODE__DIGIT_4      = 5
	,ZRTOS_VFS_MODULE_MAX7219_OPCODE__DIGIT_5      = 6
	,ZRTOS_VFS_MODULE_MAX7219_OPCODE__DIGIT_6      = 7
	,ZRTOS_VFS_MODULE_MAX7219_OPCODE__DIGIT_7      = 8
	,ZRTOS_VFS_MODULE_MAX7219_OPCODE__DECODE_MODE  = 9
	,ZRTOS_VFS_MODULE_MAX7219_OPCODE__INTENSITY    = 10
	,ZRTOS_VFS_MODULE_MAX7219_OPCODE__SCAN_LIMIT   = 11
	,ZRTOS_VFS_MODULE_MAX7219_OPCODE__SHUTDOWN     = 12
	,ZRTOS_VFS_MODULE_MAX7219_OPCODE__DISPLAY_TEST = 15
}zrtos_vfs_module_max7219_opcode_t;


#ifdef __cplusplus
}
#endif
#endif
