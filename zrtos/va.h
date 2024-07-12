/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VA_H
#define ZRTOS_VA_H
#ifdef __cplusplus
extern "C" {
#endif


#include <stdarg.h>

#include <zrtos/assert.h>


#define zrtos_va_t va_list
#define zrtos_va__start va_start
#define zrtos_va__arg(ap,type)\
	({\
		ZRTOS_ASSERT__STATIC(sizeof(type) <= sizeof(int));\
		((type)va_arg(ap,int));\
	})
#define zrtos_va__arg_ptr(ap,type)\
	(type)va_arg(ap,type)
#define zrtos_va__end va_end
#define zrtos_va__copy va_copy


#ifdef __cplusplus
}
#endif
#endif