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


#include "zrtos_error.h"
#include "zrtos_types.h"
#include "zrtos_arch.h"

typedef zrtos_arch_gpio_pin_t zrtos_gpio_pin_t;

typedef enum{
	 ZRTOS_GPIO_MODE__INPUT  
	,ZRTOS_GPIO_MODE__OUTPUT 
	,ZRTOS_GPIO_MODE__PULLUP 
}zrtos_gpio_mode_t;

typedef bool zrtos_gpio_value_digital_t;
typedef zrtos_arch_gpio_value_analog_t zrtos_gpio_value_analog_t;

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
		,zrtos_gpio_value_digital_t val
	);

	//void *private_data;
}zrtos_gpio_t;

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
	zrtos_error_t     ret = EXIT_SUCCESS;
	zrtos_gpio_pin_t  pin;
	zrtos_gpio_mode_t val;
	size_t            len = va_arg(args,size_t);

	while(len-- && EXIT_SUCCESS == ret){
		pin = va_arg(args,zrtos_gpio_pin_t);
		val = va_arg(args,zrtos_gpio_mode_t);
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
	zrtos_error_t              ret = EXIT_SUCCESS;
	zrtos_gpio_pin_t           pin;
	zrtos_gpio_value_digital_t *val;
	size_t                     len = va_arg(args,size_t);

	while(len-- && EXIT_SUCCESS == ret){
		pin = va_arg(args,zrtos_gpio_pin_t);
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
	)
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
	zrtos_error_t              ret = EXIT_SUCCESS;
	zrtos_gpio_pin_t           pin;
	zrtos_gpio_value_digital_t val;
	size_t                     len = va_arg(args,size_t);

	while(len-- && EXIT_SUCCESS == ret){
		pin = va_arg(args,zrtos_gpio_pin_t);
		val = va_arg(args,zrtos_gpio_value_digital_t);
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
	zrtos_error_t    ret = EXIT_SUCCESS;
	zrtos_gpio_pin_t pin;
	size_t           len = va_arg(args,size_t);

	while(len-- && EXIT_SUCCESS == ret){
		pin = va_arg(args,zrtos_gpio_pin_t);
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
	)
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
	zrtos_error_t    ret = EXIT_SUCCESS;
	zrtos_gpio_pin_t pin;
	size_t           len = va_arg(args,size_t);

	while(len-- && EXIT_SUCCESS == ret){
		pin = va_arg(args,zrtos_gpio_pin_t);
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
	zrtos_error_t             ret = EXIT_SUCCESS;
	zrtos_gpio_pin_t          pin;
	zrtos_gpio_value_analog_t *val;
	size_t                    len = va_arg(args,size_t);

	while(len-- && EXIT_SUCCESS == ret){
		pin = va_arg(args,zrtos_gpio_pin_t);
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
	)
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
	zrtos_error_t             ret = EXIT_SUCCESS;
	zrtos_gpio_pin_t          pin;
	zrtos_gpio_value_analog_t val;
	size_t                    len = va_arg(args,size_t);

	while(len-- && EXIT_SUCCESS == ret){
		pin = va_arg(args,zrtos_gpio_pin_t);
		val = va_arg(args,zrtos_gpio_value_analog_t);
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
	)
	va_end(args);

	return ret;
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