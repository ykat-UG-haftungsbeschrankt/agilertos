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


#include <stdarg.h>


#include <zrtos/error.h>
#include <zrtos/types.h>
#include <zrtos/arch.h>
#include <zrtos/assert.h>

typedef zrtos_arch_gpio_pin_t zrtos_gpio_pin_t;

typedef enum{
	 ZRTOS_GPIO_MODE__INPUT  = 0x0
	,ZRTOS_GPIO_MODE__OUTPUT = 0x1
	,ZRTOS_GPIO_MODE__PULLUP = 0x2
}zrtos_gpio_mode_t;

typedef bool zrtos_gpio_value_digital_t;
typedef zrtos_arch_gpio_value_analog_t zrtos_gpio_value_analog_t;

ZRTOS_ASSERT__STATIC(sizeof(zrtos_gpio_value_digital_t) <= sizeof(unsigned int));
ZRTOS_ASSERT__STATIC(sizeof(zrtos_gpio_mode_t) <= sizeof(unsigned int));
ZRTOS_ASSERT__STATIC(sizeof(zrtos_gpio_pin_t) <= sizeof(unsigned int));

#define ZRTOS_GPIO__VA_ARG_MODE(args)\
	((zrtos_gpio_mode_t)va_arg(args,unsigned int))
#define ZRTOS_GPIO__VA_ARG_PIN(args)\
	((zrtos_gpio_pin_t)va_arg(args,unsigned int))
#define ZRTOS_GPIO__VA_ARG_VALUE_DIGITAL(args)\
	((zrtos_gpio_value_digital_t)va_arg(args,unsigned int))
#define ZRTOS_GPIO__VA_ARG_VALUE_ANALOG(args)\
	((zrtos_gpio_value_analog_t)va_arg(args,unsigned int))

typedef struct _zrtos_gpio_t{
	zrtos_error_t (*set_mode)(
		 struct _zrtos_gpio_t      *thiz
		,zrtos_gpio_pin_t           pin
		,zrtos_gpio_mode_t          mode
	);

	zrtos_error_t (*digital_read)(
		 struct _zrtos_gpio_t       *thiz
		,zrtos_gpio_pin_t           pin
		,zrtos_gpio_value_digital_t *val
	);
	zrtos_error_t (*digital_write)(
		struct _zrtos_gpio_t        *thiz
		,zrtos_gpio_pin_t           pin
		,zrtos_gpio_value_digital_t val
	);

	zrtos_error_t (*analog_read)(
		 struct _zrtos_gpio_t       *thiz
		,zrtos_gpio_pin_t           pin
		,zrtos_gpio_value_analog_t  *val
	);
	zrtos_error_t (*analog_write)(
		struct _zrtos_gpio_t        *thiz
		,zrtos_gpio_pin_t           pin
		,zrtos_gpio_value_analog_t  val
	);

	//void *private_data;
}zrtos_gpio_t;

#define ZRTOS_GPIO__INIT(\
	 set_mode_\
	,digital_read_\
	,digital_write_\
	,analog_read_\
	,analog_write_\
)\
	{\
		 .set_mode = set_mode_\
		,.digital_read = digital_read_\
		,.digital_write = digital_write_\
		,.analog_read = analog_read_\
		,.analog_write = analog_write_\
	}

bool zrtos_gpio__init(
	 zrtos_gpio_t *thiz
	,zrtos_error_t (*set_mode)(
		 struct _zrtos_gpio_t      *thiz
		,zrtos_gpio_pin_t           pin
		,zrtos_gpio_mode_t          mode
	)
	,zrtos_error_t (*digital_read)(
		 struct _zrtos_gpio_t       *thiz
		,zrtos_gpio_pin_t           pin
		,zrtos_gpio_value_digital_t *val
	)
	,zrtos_error_t (*digital_write)(
		struct _zrtos_gpio_t        *thiz
		,zrtos_gpio_pin_t           pin
		,zrtos_gpio_value_digital_t val
	)
	,zrtos_error_t (*analog_read)(
		 struct _zrtos_gpio_t       *thiz
		,zrtos_gpio_pin_t           pin
		,zrtos_gpio_value_analog_t  *val
	)
	,zrtos_error_t (*analog_write)(
		struct _zrtos_gpio_t        *thiz
		,zrtos_gpio_pin_t           pin
		,zrtos_gpio_value_analog_t  val
	)
){
	thiz->set_mode = set_mode;
	thiz->digital_read = digital_read;
	thiz->digital_write = digital_write;
	thiz->analog_read = analog_read;
	thiz->analog_write = analog_write;

	return true;
}

zrtos_error_t zrtos_gpio__set_mode(
	 zrtos_gpio_t      *thiz
	,zrtos_gpio_pin_t  pin
	,zrtos_gpio_mode_t mode
){
	return thiz->set_mode(thiz,pin,mode);
}

zrtos_error_t zrtos_gpio__set_mode_va(
	 zrtos_gpio_t *thiz
	,va_list      args
){
	zrtos_error_t     ret = ZRTOS_ERROR__SUCCESS;
	zrtos_gpio_pin_t  pin;
	zrtos_gpio_mode_t val;
	size_t            len = va_arg(args,size_t);

	while(len-- && zrtos_error__is_success(ret)){
		pin = ZRTOS_GPIO__VA_ARG_PIN(args);
		val = ZRTOS_GPIO__VA_ARG_MODE(args);
		ret = zrtos_gpio__set_mode(
			 thiz
			,pin
			,val
		);
	}

	return ret;
}

zrtos_error_t zrtos_gpio__set_mode_ex(
	 zrtos_gpio_t *thiz
	,...
){
	zrtos_error_t ret;
	va_list       args;

	va_start(args,thiz);
	ret = zrtos_gpio__set_mode_va(
		 thiz
		,args
	);
	va_end(args);

	return ret;
}

zrtos_error_t zrtos_gpio__digital_read(
	 zrtos_gpio_t               *thiz
	,zrtos_gpio_pin_t           pin
	,zrtos_gpio_value_digital_t *val
){
	return thiz->digital_read(thiz,pin,val);
}

zrtos_error_t zrtos_gpio__digital_read_va(
	 zrtos_gpio_t *thiz
	,va_list      args
){
	zrtos_error_t              ret = ZRTOS_ERROR__SUCCESS;
	zrtos_gpio_pin_t           pin;
	zrtos_gpio_value_digital_t *val;
	size_t                     len = va_arg(args,size_t);

	while(len-- && zrtos_error__is_success(ret)){
		pin = ZRTOS_GPIO__VA_ARG_PIN(args);
		val = va_arg(args,zrtos_gpio_value_digital_t*);
		ret = zrtos_gpio__digital_read(
			 thiz
			,pin
			,val
		);
	}

	return ret;
}

zrtos_error_t zrtos_gpio__digital_read_ex(
	 zrtos_gpio_t *thiz
	,...
){
	zrtos_error_t ret;
	va_list       args;

	va_start(args,thiz);
	ret = zrtos_gpio__digital_read_va(
		 thiz
		,args
	);
	va_end(args);

	return ret;
}

zrtos_error_t zrtos_gpio__digital_write(
	 zrtos_gpio_t               *thiz
	,zrtos_gpio_pin_t           pin
	,zrtos_gpio_value_digital_t val
){
	return thiz->digital_write(thiz,pin,val);
}

zrtos_error_t zrtos_gpio__digital_write_va(
	 zrtos_gpio_t *thiz
	,va_list      args
){
	zrtos_error_t              ret = ZRTOS_ERROR__SUCCESS;
	zrtos_gpio_pin_t           pin;
	zrtos_gpio_value_digital_t val;
	size_t                     len = va_arg(args,size_t);

	while(len-- && zrtos_error__is_success(ret)){
		pin = ZRTOS_GPIO__VA_ARG_PIN(args);
		val = ZRTOS_GPIO__VA_ARG_VALUE_DIGITAL(args);
		ret = zrtos_gpio__digital_write(
			 thiz
			,pin
			,val
		);
	}

	return ret;
}

zrtos_error_t zrtos_gpio__digital_write_ex(
	 zrtos_gpio_t       *thiz
	,...
){
	zrtos_error_t ret;
	va_list       args;

	va_start(args,thiz);
	ret = zrtos_gpio__digital_write_va(
		 thiz
		,args
	);
	va_end(args);

	return ret;
}

zrtos_error_t zrtos_gpio__set_high(
	 zrtos_gpio_t     *thiz
	,zrtos_gpio_pin_t pin
){
	return zrtos_gpio__digital_write(
		 thiz
		,pin
		,true
	);
}

zrtos_error_t zrtos_gpio__set_high_va(
	 zrtos_gpio_t *thiz
	,va_list      args
){
	zrtos_error_t    ret = ZRTOS_ERROR__SUCCESS;
	zrtos_gpio_pin_t pin;
	size_t           len = va_arg(args,size_t);

	while(len-- && zrtos_error__is_success(ret)){
		pin = ZRTOS_GPIO__VA_ARG_PIN(args);
		ret = zrtos_gpio__set_high(
			 thiz
			,pin
		);
	}

	return ret;
}

zrtos_error_t zrtos_gpio__set_high_ex(
	zrtos_gpio_t *thiz
	,...
){
	zrtos_error_t ret;
	va_list       args;

	va_start(args,thiz);
	ret = zrtos_gpio__set_high_va(
		 thiz
		,args
	);
	va_end(args);

	return ret;
}

zrtos_error_t zrtos_gpio__set_low(
	 zrtos_gpio_t     *thiz
	,zrtos_gpio_pin_t pin
){
	return thiz->digital_write(
		 thiz
		,pin
		,false
	);
}

zrtos_error_t zrtos_gpio__set_low_va(
	zrtos_gpio_t *thiz
	,va_list     args
){
	zrtos_error_t    ret = ZRTOS_ERROR__SUCCESS;
	zrtos_gpio_pin_t pin;
	size_t           len = va_arg(args,size_t);

	while(len-- && zrtos_error__is_success(ret)){
		pin = ZRTOS_GPIO__VA_ARG_PIN(args);
		ret = zrtos_gpio__set_low(
			 thiz
			,pin
		);
	}

	return ret;
}

zrtos_error_t zrtos_gpio__set_low_ex(
	zrtos_gpio_t *thiz
	,...
){
	zrtos_error_t ret;
	va_list args;

	va_start(args,thiz);
	ret = zrtos_gpio__set_low_va(
		 thiz
		,args
	);
	va_end(args);

	return ret;
}

zrtos_error_t zrtos_gpio__analog_read(
	 zrtos_gpio_t              *thiz
	,zrtos_gpio_pin_t          pin
	,zrtos_gpio_value_analog_t *val
){
	return thiz->analog_read(thiz,pin,val);
}

zrtos_error_t zrtos_gpio__analog_read_va(
	 zrtos_gpio_t *thiz
	,va_list      args
){
	zrtos_error_t             ret = ZRTOS_ERROR__SUCCESS;
	zrtos_gpio_pin_t          pin;
	zrtos_gpio_value_analog_t *val;
	size_t                    len = va_arg(args,size_t);

	while(len-- && zrtos_error__is_success(ret)){
		pin = ZRTOS_GPIO__VA_ARG_PIN(args);
		val = va_arg(args,zrtos_gpio_value_analog_t*);
		ret = zrtos_gpio__analog_read(
			 thiz
			,pin
			,val
		);
	}

	return ret;
}

zrtos_error_t zrtos_gpio__analog_read_ex(
	 zrtos_gpio_t *thiz
	,...
){
	zrtos_error_t ret;
	va_list       args;

	va_start(args,thiz);
	ret = zrtos_gpio__analog_read_ex(
		 thiz
		,args
	);
	va_end(args);

	return ret;
}

zrtos_error_t zrtos_gpio__analog_write(
	 zrtos_gpio_t              *thiz
	,zrtos_gpio_pin_t          pin
	,zrtos_gpio_value_analog_t val
){
	return thiz->analog_write(thiz,pin,val);
}

zrtos_error_t zrtos_gpio__analog_write_va(
	 zrtos_gpio_t *thiz
	,va_list      args
){
	zrtos_error_t             ret = ZRTOS_ERROR__SUCCESS;
	zrtos_gpio_pin_t          pin;
	zrtos_gpio_value_analog_t val;
	size_t                    len = va_arg(args,size_t);

	while(len-- && zrtos_error__is_success(ret)){
		pin = ZRTOS_GPIO__VA_ARG_PIN(args);
		val = ZRTOS_GPIO__VA_ARG_VALUE_ANALOG(args);
		ret = zrtos_gpio__analog_write(
			 thiz
			,pin
			,val
		);
	}

	return ret;
}

zrtos_error_t zrtos_gpio__analog_write_ex(
	 zrtos_gpio_t       *thiz
	,...
){
	zrtos_error_t ret;
	va_list       args;

	va_start(args,thiz);
	ret = zrtos_gpio__analog_write_va(
		 thiz
		,args
	);
	va_end(args);

	return ret;
}

uint8_t zrtos_gpio__shift_in(
	 zrtos_gpio_t     *thiz
	,zrtos_gpio_pin_t dataPin
	,zrtos_gpio_pin_t clockPin
	,bool is_lsb
){
	uint8_t value = 0;
	size_t i;
	zrtos_gpio_value_digital_t val;

	for (i = 0; i < 8; ++i) {
		zrtos_gpio__set_high(thiz,clockPin);
		zrtos_gpio__digital_read(thiz,dataPin,&val);
		if(is_lsb){
			value |= val << i;
		}else{
			value |= val << (7 - i);
		}
		zrtos_gpio__set_low(thiz,clockPin);
	}
	return value;
}

zrtos_error_t zrtos_gpio__shift_out(
	 zrtos_gpio_t     *thiz
	,zrtos_gpio_pin_t dataPin
	,zrtos_gpio_pin_t clockPin
	,bool             is_lsb
	,uint8_t          value
){
	size_t i;
	zrtos_gpio_value_digital_t val;

	for(i = 0; i < 8; i++){
		if(is_lsb){
			val = (value & 1);
			value >>= 1;
		} else {
			val = ((value & 128) != 0);
			value <<= 1;
		}
		zrtos_gpio__digital_write(thiz,dataPin,val);
		zrtos_gpio__set_high(thiz,clockPin);
		zrtos_gpio__set_low(thiz,clockPin);
	}

	return ZRTOS_ERROR__SUCCESS;
}

void zrtos_gpio__delay_microseconds(uint16_t us){
	zrtos_arch__delay_microseconds(us);
}

void zrtos_gpio__delay_milliseconds(uint16_t ms){
	zrtos_arch__delay_milliseconds(ms);
}

#undef ZRTOS_GPIO__VA_ARG_MODE
#undef ZRTOS_GPIO__VA_ARG_PIN
#undef ZRTOS_GPIO__VA_ARG_VALUE_DIGITAL
#undef ZRTOS_GPIO__VA_ARG_VALUE_ANALOG


#ifdef __cplusplus
}
#endif
#endif