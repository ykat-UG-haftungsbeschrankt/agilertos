/*
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


#define ZRTOS_ASSERT__STATIC_EX(cond,msg) \
    typedef char static_assertion_##msg[  \
        (cond)?1:-1                       \
    ]__attribute__((unused));

#define _ZRTOS_ASSERT__STATIC_HELPER(cond,line) \
    ZRTOS_ASSERT__STATIC_EX(cond,line)

#define ZRTOS_ASSERT__STATIC(cond)                 \
    _ZRTOS_ASSERT__STATIC_HELPER(cond,__COUNTER__)


#ifdef __cplusplus
}
#endif
#endif