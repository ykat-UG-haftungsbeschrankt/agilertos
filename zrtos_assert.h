/* vim: noai:ts=4
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_ASSERT_H
#define ZRTOS_ASSERT_H
#ifdef __cplusplus
extern "C" {
#endif


#define ZRTOS_ASSERT__STATIC(cond) typedef char static_assertion_###__LINE__[(cond)?1:-1]


#ifdef __cplusplus
}
#endif
#endif