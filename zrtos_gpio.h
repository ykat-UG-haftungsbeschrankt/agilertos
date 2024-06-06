/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_GPIO_H
#define ZRTOS_GPIO_H
#ifdef __cplusplus
extern "C" {
#endif


#include "zrtos_arch.h"


typedef zrtos_arch_gpio_pin_t zrtos_gpio_pin_t;
typedef enum{
	 ZRTOS_GPIO_MODE__INPUT
	,ZRTOS_GPIO_MODE__OUTPUT
}zrtos_gpio_mode_t;
typedef zrtos_arch_gpio_value_t zrtos_gpio_value_t;

typedef struct _zrtos_gpio_t{
	zrtos_gpio_pin_t pin;
}zrtos_gpio_t;

void zrtos_gpio__set_mode(
	 zrtos_gpio_t *thiz
	,zrtos_gpio_mode_t mode
){
	zrtos_arch__pin_mode(thiz->pin,mode);
}

bool zrtos_gpio__digital_read(zrtos_gpio_t *thiz){
	return zrtos_arch__digital_read(thiz->pin);
}

void zrtos_gpio__digital_write(zrtos_gpio_t *thiz,bool val){
	zrtos_arch__digital_write(thiz->pin,val);
}

zrtos_gpio_value_t zrtos_gpio__analog_read(zrtos_gpio_t *thiz,zrtos_gpio_pin_t pin){
	return zrtos_arch__analog_read(thiz->pin);
}

void zrtos_gpio__analog_write(
	 zrtos_gpio_t *thiz
	,zrtos_gpio_value_t val
){
	zrtos_arch__analog_write(thiz->pin,val);
}

void zrtos_gpio__delay_microseconds(uint16_t us){
	zrtos_arch__delay_microseconds(us);
}

void zrtos_gpio__delay_milliseconds(uint16_t ms){
	zrtos_arch__delay_milliseconds(ms);
}


#ifdef __cplusplus
}
#endif
#endif