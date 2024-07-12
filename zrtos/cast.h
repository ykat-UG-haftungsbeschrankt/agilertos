/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_CAST_H
#define ZRTOS_CAST_H
#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
#define ZRTOS_CAST(type,value) static_cast<type>(value)
#define ZRTOS_CAST__REINTERPRET(type,value) reinterpret_cast<type>(value)
#else
#define ZRTOS_CAST(type,value) (type)(value)
#define ZRTOS_CAST__REINTERPRET(type,value) (type)(value)
#endif


#ifdef __cplusplus
}
#endif
#endif
