/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_FILE_H
#define ZRTOS_VFS_FILE_H
#ifdef __cplusplus
extern "C" {
#endif


#include "zrtos_error.h"
#include "zrtos_bitfield.h"
#include "zrtos_vfs_dentry.h"


typedef struct{
	zrtos_vfs_dentry_t *dentry;
	off_t              offset;
}zrtos_vfs_file_t;

zrtos_vfs_file_t zrtos_vfs_file_index[ZRTOS_VFS_FILE_DESCRIPTOR__CFG_MAX];

int zrtos_vfs_file__open(const char *path){
	int ret;
	zrtos_vfs_dentry_t *dentry = zrtos_vfs_dentry__lookup(
		 0
		,path
	);
	if(dentry){
		for(size_t i=0;i<ZRTOS_VFS_FILE_DESCRIPTOR__CFG_MAX;i++){
			if(0 == zrtos_vfs_file_index[i].dentry){
				dentry->count++;
				zrtos_vfs_file_index[i].dentry = dentry;
				ret = i;
				goto L_OUT;
			}
		}
		ret = -EMFILE;
	}else{
		ret = -ENOENT;
	}

L_OUT:
	return ret;
}

void zrtos_vfs_file__close(size_t fd){
	zrtos_vfs_file_t file = zrtos_vfs_file_index[fd];
	file.dentry->count--;
	file.dentry->inode.close(&file);
	zrtos_vfs_file_index[fd].dentry = 0;
}

ssize_t zrtos_vfs_file__read(size_t fd,void *buffer,size_t len,size_t offset){
	zrtos_vfs_file_t file = zrtos_vfs_file_index[fd];
	return file.dentry->inode.read(&file,buffer,len,offset);
}

ssize_t zrtos_vfs_file__write(size_t fd,void *buffer,size_t len,size_t offset){
	zrtos_vfs_file_t file = zrtos_vfs_file_index[fd];
	return file.dentry->inode.write(&file,buffer,len,offset);
}

int zrtos_vfs_file__ioctl(size_t fd,int request,va_list args){
	int ret;
	zrtos_vfs_file_t file = zrtos_vfs_file_index[fd];
	if(file.dentry){
		ret = file.dentry->inode.plugin->ioctl(
			 &file
			,request
			,args
		);
	}else{
		ret = -EBADF;
	}
	return ret;
}

void *zrtos_vfs_file__get_inode_data(zrtos_vfs_file_t *thiz){
	return thiz->dentry->inode.private_data;
}

#ifdef __cplusplus
}
#endif
#endif