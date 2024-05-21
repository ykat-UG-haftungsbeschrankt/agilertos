/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_H
#define ZRTOS_H
#ifdef __cplusplus
extern "C" {
#endif


#include "zrtos_debug.h"
#include "zrtos_arch.h"
#include "zrtos_board.h"


#ifdef ZRTOS_VHEAP_TASK_SCHEDULER__CFG_ENABLED

# define ZRTOS__DO_NOT_DISTURB(code) \
    ZRTOS_VHEAP_TASK_SCHEDULER__DO_NOT_DISTURB(code)

# define ZRTOS__DO_NOT_DISTURB_EX(is_locked,code) \
    ZRTOS_VHEAP_TASK_SCHEDULER__DO_NOT_DISTURB_EX(is_locked,code)

#else

# define ZRTOS__DO_NOT_DISTURB(code) \
    ZRTOS_ARCH__DO_NOT_DISTURB(code)

# define ZRTOS__DO_NOT_DISTURB_EX(is_locked,code) \
    ZRTOS_ARCH__DO_NOT_DISTURB_EX(is_locked,code)

#endif


#ifdef __cplusplus
}
#endif
#endif