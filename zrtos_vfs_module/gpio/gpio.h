/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_GPIO_H
#define ZRTOS_VFS_MODULE_GPIO_H
#ifdef __cplusplus
extern "C" {
#endif


#include <stdarg.h>

#include <zrtos/zrtos_gpio.h>
#include <zrtos/zrtos_vfs_file.h>
#include <zrtos/zrtos_vfs_plugin.h>
#include <zrtos/zrtos_error.h>


zrtos_error_t zrtos_vfs_module_gpio__ioctl(zrtos_file_t *thiz,int request,va_list args){
	zrtos_gpio_t **val = va_arg(args,zrtos_gpio_t**);
	*val = zrtos_vfs_file__get_inode_data(thiz);
	return EXIT_SUCCESS;
}

zrtos_vfs_plugin_t zrtos_vfs_module_gpio = {
	,.ioctl = zrtos_vfs_module_gpio__ioctl
};


#ifdef __cplusplus
}
#endif
#endif
