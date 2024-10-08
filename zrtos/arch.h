/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_ARCH_H
#define ZRTOS_ARCH_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/types.h>
#include <zrtos/assert.h>

typedef void (*zrtos_arch_callback_t)(void *arg);

/*
typedef uint8_t zrtos_arch_stack_t;
typedef int8_t zrtos_arch_stack_signed_t;
typedef int zrtos_arch_gpio_pin_t;
typedef int zrtos_arch_gpio_value_analog_t;
#define ZRTOS_ARCH__BYTE_ORDER
#define ZRTOS_ARCH__FOUND
#define ZRTOS_ARCH__CPU_CLOCK_HZ
#define ZRTOS_ARCH__BYTE_ALIGNMENT
#define ZRTOS_ARCH__FATAL()
#define ZRTOS_ARCH__SET_STACK_PTR(sp)
#define ZRTOS_ARCH__GET_STACK_PTR()
#define ZRTOS_ARCH__IS_INTERRUPTS_DISABLED()
#define ZRTOS_ARCH__IS_INTERRUPTS_ENABLED()
#define ZRTOS_ARCH__DISABLE_INTERRUPTS()
#define ZRTOS_ARCH__ENABLE_INTERRUPTS()
zrtos_arch_stack_t *zrtos_arch__cpu_state_init(
	 zrtos_arch_stack_t     *thiz
	//,size_t                length
	,zrtos_arch_callback_t callback
	,void                  *args
)
#define ZRTOS_ARCH__GET_CPU_STATE_BUFFER_LENGTH()
#define ZRTOS_ARCH__GET_FN_CALL_STACK_LENGTH()
#define ZRTOS_ARCH__SAVE_CPU_STATE(ptr)
#define ZRTOS_ARCH__LOAD_CPU_STATE(ptr)
#define ZRTOS_ARCH__RETURN_FROM_INTERRUPT()
void zrtos_arch__delay_microseconds(uint16_t us);
void zrtos_arch__delay_milliseconds(uint16_t ms);
*/

#ifdef ZRTOS_ARCH__FOUND
#error "ZRTOS_ARCH__FOUND defined"
#endif

#define ZRTOS_ARCH__BYTE_ORDER_LITTLE_ENDIAN        1234
#define ZRTOS_ARCH__BYTE_ORDER_BIG_ENDIAN           4321
#define ZRTOS_ARCH__BYTE_ORDER_PDP_ENDIAN           3412

#include <zrtos/arch/atmega328p.h>
#include <zrtos/arch/atmega2560.h>

#ifndef ZRTOS_ARCH__FOUND
#error "arch/*.h not found"
#endif

#if ZRTOS_ARCH__BYTE_ALIGNMENT == 32
    #define ZRTOS_ARCH__BYTE_ALIGNMENT_MASK    ( 0x001f )
#elif ZRTOS_ARCH__BYTE_ALIGNMENT == 16
    #define ZRTOS_ARCH__BYTE_ALIGNMENT_MASK    ( 0x000f )
#elif ZRTOS_ARCH__BYTE_ALIGNMENT == 8
    #define ZRTOS_ARCH__BYTE_ALIGNMENT_MASK    ( 0x0007 )
#elif ZRTOS_ARCH__BYTE_ALIGNMENT == 4
    #define ZRTOS_ARCH__BYTE_ALIGNMENT_MASK    ( 0x0003 )
#elif ZRTOS_ARCH__BYTE_ALIGNMENT == 2
    #define ZRTOS_ARCH__BYTE_ALIGNMENT_MASK    ( 0x0001 )
#elif ZRTOS_ARCH__BYTE_ALIGNMENT == 1
    #define ZRTOS_ARCH__BYTE_ALIGNMENT_MASK    ( 0x0000 )
#else
    #error "Invalid ZRTOS_ARCH__BYTE_ALIGNMENT definition"
#endif

///@todo verify alignment
/*
ZRTOS_ASSERT__STATIC(
	ZRTOS_ARCH__BYTE_ALIGNMENT == ZRTOS_TYPES__BYTE_ALIGNMENT
);
ZRTOS_ASSERT__STATIC(
	ZRTOS_ARCH__BYTE_ALIGNMENT_MASK != ZRTOS_TYPES__BYTE_ALIGNMENT_MASK
);
*/

size_t zrtos_arch__do_not_disturb = 0;
#define ZRTOS_ARCH__DO_NOT_DISTURB(code)       \
    do{                                        \
        ZRTOS_ARCH__DISABLE_INTERRUPTS();      \
        zrtos_arch__do_not_disturb++;          \
        do{                                    \
            code;                              \
        }while(0);                             \
        if(--zrtos_arch__do_not_disturb == 0){ \
            ZRTOS_ARCH__ENABLE_INTERRUPTS();   \
        }                                      \
    }while(0);


#define ZRTOS_ARCH__DO_NOT_DISTURB_EX(is_locked,code)     \
    do{                                                   \
        is_locked = ZRTOS_ARCH__IS_INTERRUPTS_DISABLED(); \
        ZRTOS_ARCH__DISABLE_INTERRUPTS();                 \
        zrtos_arch__do_not_disturb++;                     \
        do{                                               \
            code;                                         \
        }while(0);                                        \
        if(--zrtos_arch__do_not_disturb == 0){            \
            ZRTOS_ARCH__ENABLE_INTERRUPTS();              \
        }                                                 \
    }while(0);

#ifdef __cplusplus
}
#endif
#endif