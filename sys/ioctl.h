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

#include "../zrtos_file_descriptor.h"


int ioctl(int d, int request,...){
	int ret;
	if(zrtos_file_descriptor__is_file((size_t)d)){
		va_list args;
		zrtos_file_t *file = zrtos_file_descriptor__get_file((size_t)d);
		va_start(args,request);
		file->inode->ioctl(
			file
			,request
			,args
		);
		va_end(args);
	}else{
		ret = -EBADF;
	}
	return ret;
}


#ifdef __cplusplus
}
#endif
#endif