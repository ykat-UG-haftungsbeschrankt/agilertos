/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_MODULE_NETWORK_H
#define ZRTOS_VFS_MODULE_NETWORK_H
#ifdef __cplusplus
extern "C" {
#endif

#include <zrtos/types.h>


typedef struct{
	uint8_t data[6];
}zrtos_vfs_module_network_mac_t;

typedef struct{
	uint8_t data[4];
}zrtos_vfs_module_network_ip_t;

typedef struct{
	uint8_t data[4];
}zrtos_vfs_module_network_subnet_mask_t;

bool zrtos_vfs_module_network_ip__init(
	 zrtos_vfs_module_network_ip_t *thiz
	,const char *src
){
	char ch;
	uint16_t val = 0;
	size_t pos = 0;
	size_t octets = 0;

	while(true){
		ch = *src++;
		if(zrtos_types__is_digit(ch)){
			val += (ch - '0') * 10;
		}else if(ch == '.'){
			if(++octets < 4){
				if(val < 2560){
					thiz->data[pos++] = val/10;
					val = 0;
				}else{
					goto L_ERROR;
				}
			}else{
				goto L_ERROR;
			}
		}else if(ch == '\0'){
			thiz->data[pos++] = val/10;
			val = 0;
		}else{
			goto L_ERROR;
		}
	}

	if (octets < 4)
		return (0);
	memcpy(dst, tmp, NS_INADDRSZ);
	return (1);
}

#ifdef __cplusplus
}
#endif
#endif