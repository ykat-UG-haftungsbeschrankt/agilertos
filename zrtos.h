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

size_t _zrtos__do_not_disturb = 0;
#define ZRTOS__DO_NOT_DISTURB(code)    \
do{                                    \
    ZRTOS__INTERRUPTS_DISABLE();       \
    _zrtos__do_not_disturb++;          \
    do{                                \
        code;                          \
    }while(0);                         \
    if(--_zrtos__do_not_disturb == 0){ \
        ZRTOS__INTERRUPTS_ENABLE();    \
    }                                  \
}while(0);

#define ZRTOS__DO_NOT_DISTURB_EX(is_locked,code) \
do{                                              \
    is_locked = ZRTOS__INTERRUPTS_IS_DISABLED(); \
    ZRTOS__INTERRUPTS_DISABLE();                 \
    _zrtos__do_not_disturb++;                    \
    do{                                          \
        code;                                    \
    }while(0);                                   \
    if(--_zrtos__do_not_disturb == 0){           \
        ZRTOS__INTERRUPTS_ENABLE();              \
    }                                            \
}while(0);



#if ZRTOS__BYTE_ALIGNMENT == 32
    #define ZRTOS__BYTE_ALIGNMENT_MASK    ( 0x001f )
#elif ZRTOS__BYTE_ALIGNMENT == 16
    #define ZRTOS__BYTE_ALIGNMENT_MASK    ( 0x000f )
#elif ZRTOS__BYTE_ALIGNMENT == 8
    #define ZRTOS__BYTE_ALIGNMENT_MASK    ( 0x0007 )
#elif ZRTOS__BYTE_ALIGNMENT == 4
    #define ZRTOS__BYTE_ALIGNMENT_MASK    ( 0x0003 )
#elif ZRTOS__BYTE_ALIGNMENT == 2
    #define ZRTOS__BYTE_ALIGNMENT_MASK    ( 0x0001 )
#elif ZRTOS__BYTE_ALIGNMENT == 1
    #define ZRTOS__BYTE_ALIGNMENT_MASK    ( 0x0000 )
#else /* if ZRTOS__BYTE_ALIGNMENT == 32 */
    #error "Invalid ZRTOS__BYTE_ALIGNMENT definition"
#endif /* if ZRTOS__BYTE_ALIGNMENT == 32 */


#ifdef __cplusplus
}
#endif
#endif