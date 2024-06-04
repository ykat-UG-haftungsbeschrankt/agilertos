/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_FILE_INODE_H
#define ZRTOS_FILE_INODE_H
#ifdef __cplusplus
extern "C" {
#endif


#include "zrtos_file_operations.h"
#include "zrtos_str.h"


typedef struct _zrtos_file_inode_t{
	const char                 *name;
	struct _zrtos_file_inode_t *parent;
	zrtos_file_operations_t    *ops;
	void                       *private_data;
}zrtos_file_inode_t;


zrtos_file_inode_t *zrtos_file_inode__resolve_path(
	 zrtos_file_inode_t *thiz
	,const char *path
){
	char* token;
	char* rest = path;
	zrtos_file_inode_t *ret = 0;

	while((token = zrtos_str__tok_r(rest,"/", &rest))){
		ZRTOS_FILE_INODE__EACH(inode){
			if(parent == inode->parent
			&& 0 == zrtos_str__cmp(token,inode->name)){
				ret = inode;
			}
		}
	}

	return ret;
}


#ifdef __cplusplus
}
#endif
#endif