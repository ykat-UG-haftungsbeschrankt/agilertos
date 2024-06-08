/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_SYS_IOCTL_H
#define ZRTOS_SYS_IOCTL_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>

#include <zrtos/vfs_file.h>


int ioctl(int fd, int request,...){
	int ret;
	va_list args;
	va_start(args,request);
	ret = zrtos_vfs_file__ioctl(fd,request,args);
	va_end(args);
	return ret;
}


#ifdef __cplusplus
}
#endif
#endif