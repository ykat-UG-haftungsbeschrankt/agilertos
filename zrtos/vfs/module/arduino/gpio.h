/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_ARDUINO_GPIO_H
#define ZRTOS_VFS_MODULE_ARDUINO_GPIO_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <zrtos/error.h>
#include <zrtos/vfs/module/gpio/gpio.h>

zrtos_error_t zrtos_vfs_module_arduino_gpio__set_mode(
	 zrtos_gpio_t               *thiz
	,zrtos_gpio_pin_t           pin
	,zrtos_gpio_mode_t          mode
){
	int tmp;
	switch(mode){
		case ZRTOS_GPIO_MODE__INPUT:
			tmp = INPUT;
		break;
		case ZRTOS_GPIO_MODE__OUTPUT:
			tmp = OUTPUT;
		break;
		case ZRTOS_GPIO_MODE__PULLUP:
			tmp = INPUT_PULLUP;
		break;
	}
	pinMode(pin,tmp);
	return ZRTOS_ERROR__SUCCESS;
}

zrtos_error_t zrtos_vfs_module_arduino_gpio__digital_read(
	 zrtos_gpio_t               *thiz
	,zrtos_gpio_pin_t           pin
	,zrtos_gpio_value_digital_t *val
){
	*val = digitalRead(pin);
	return ZRTOS_ERROR__SUCCESS;
}

zrtos_error_t zrtos_vfs_module_arduino_gpio__digital_write(
	 zrtos_gpio_t               *thiz
	,zrtos_gpio_pin_t           pin
	,zrtos_gpio_value_digital_t val
){
	digitalWrite(pin, val);
	return ZRTOS_ERROR__SUCCESS;
}

zrtos_error_t zrtos_vfs_module_arduino_gpio__analog_read(
	 zrtos_gpio_t               *thiz
	,zrtos_gpio_pin_t           pin
	,zrtos_gpio_value_analog_t  *val
){
	//*val = analogRead(pin);
	return ZRTOS_ERROR__NOSYS;
}

zrtos_error_t zrtos_vfs_module_arduino_gpio__analog_write(
	 zrtos_gpio_t               *thiz
	,zrtos_gpio_pin_t           pin
	,zrtos_gpio_value_analog_t  val
){
	//analogWrite(pin, val);
	return ZRTOS_ERROR__NOSYS;
}

zrtos_gpio_t zrtos_vfs_module_arduino_gpio = ZRTOS_GPIO__INIT(
	 zrtos_vfs_module_arduino_gpio__set_mode
	,zrtos_vfs_module_arduino_gpio__digital_read
	,zrtos_vfs_module_arduino_gpio__digital_write
	,zrtos_vfs_module_arduino_gpio__analog_read
	,zrtos_vfs_module_arduino_gpio__analog_write
);

zrtos_error_t zrtos_vfs_module_arduino_gpio__on_mount(
	 zrtos_vfs_dentry_t *thiz
){
	zrtos_vfs_dentry__set_inode_data(thiz,&zrtos_vfs_module_arduino_gpio);
	return ZRTOS_ERROR__SUCCESS;
}

ZRTOS_VFS_PLUGIN__INIT(arduino_gpio,
	ZRTOS_VFS_PLUGIN__0_ON_OPEN_DEFAULT()
	ZRTOS_VFS_PLUGIN__1_ON_CLOSE_DEFAULT()
	ZRTOS_VFS_PLUGIN__2_ON_MOUNT(zrtos_vfs_module_arduino_gpio__on_mount)
	ZRTOS_VFS_PLUGIN__3_ON_UMOUNT_DEFAULT()
	ZRTOS_VFS_PLUGIN__4_ON_READ_DEFAULT()
	ZRTOS_VFS_PLUGIN__5_ON_WRITE_DEFAULT()
	ZRTOS_VFS_PLUGIN__6_ON_CAN_READ_DEFAULT()
	ZRTOS_VFS_PLUGIN__7_ON_CAN_WRITE_DEFAULT()
	ZRTOS_VFS_PLUGIN__8_ON_SEEK_DEFAULT()
	ZRTOS_VFS_PLUGIN__9_ON_IOCTL_DEFAULT()
);


#ifdef __cplusplus
}
#endif
#endif
