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

size_t _zrtos__do_not_disturb = 0;
#define ZRTOS__DO_NOT_DISTURB(code)    \
do{                                    \
    ZRTOS_ARCH__DISABLE_INTERRUPTS();       \
    _zrtos__do_not_disturb++;          \
    do{                                \
        code;                          \
    }while(0);                         \
    if(--_zrtos__do_not_disturb == 0){ \
        ZRTOS_ARCH__ENABLE_INTERRUPTS();    \
    }                                  \
}while(0);

#define ZRTOS__DO_NOT_DISTURB_EX(is_locked,code) \
do{                                              \
    is_locked = ZRTOS_ARCH__IS_INTERRUPTS_DISABLED(); \
    ZRTOS_ARCH__DISABLE_INTERRUPTS();                 \
    _zrtos__do_not_disturb++;                    \
    do{                                          \
        code;                                    \
    }while(0);                                   \
    if(--_zrtos__do_not_disturb == 0){           \
        ZRTOS_ARCH__ENABLE_INTERRUPTS();              \
    }                                            \
}while(0);


#ifdef __cplusplus
}
#endif
#endif