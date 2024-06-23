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

#ifdef __cplusplus
#define ZRTOS_ASSERT__STATIC_EX(cond,msg) static_assert(cond,msg)
#define ZRTOS_ASSERT__STATIC(cond) static_assert(cond)
#else
#define ZRTOS_ASSERT__STATIC_EX(cond,msg) \
    typedef char static_assertion_##msg[  \
        (cond)?1:-1                       \
    ]__attribute__((unused));

#define ZRTOS_ASSERT__STATIC_HELPER(cond,line)                   \
    ZRTOS_ASSERT__STATIC_EX(cond,line)

#define ZRTOS_ASSERT__STATIC(cond)                               \
    ZRTOS_ASSERT__STATIC_HELPER(cond,__COUNTER__)
#endif

#define ZRTOS_ASSERT__STATIC_IS_POWER_OF_TWO(x)                  \
    ZRTOS_ASSERT__STATIC(((x) != 0) && (((x) & ((x) - 1)) == 0))


#ifdef __cplusplus
}
#endif
#endif