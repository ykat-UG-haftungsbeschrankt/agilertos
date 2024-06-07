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


typedef struct _zrtos_vfs_file_t{
	zrtos_vfs_dentry_t *dentry;
	zrtos_vfs_offset_t offset;
}zrtos_vfs_file_t;

#ifndef ZRTOS_VFS_FILE_DESCRIPTOR__CFG_MAX
#error "define ZRTOS_VFS_FILE_DESCRIPTOR__CFG_MAX"
#endif

zrtos_vfs_file_t zrtos_vfs_file_index[ZRTOS_VFS_FILE_DESCRIPTOR__CFG_MAX];

zrtos_error_t zrtos_vfs_file__open(char *path,size_t *fd){
	zrtos_error_t ret;
	zrtos_vfs_dentry_t *dentry = zrtos_vfs_dentry__lookup(
		 0
		,path
	);
	if(dentry){ 
		for(size_t i=0;i<ZRTOS_VFS_FILE_DESCRIPTOR__CFG_MAX;i++){
			if(0 == zrtos_vfs_file_index[i].dentry){
				dentry->count++;
				zrtos_vfs_file_index[i].dentry = dentry;
				*fd = i;
				ret = EXIT_SUCCESS;
				goto L_OUT;
			}
		}
		ret = EMFILE;
	}else{
		ret = ENOENT;
	}

L_OUT:
	return ret;
}

zrtos_error_t zrtos_vfs_file__close(size_t fd){
	zrtos_error_t ret;
	zrtos_vfs_file_t file = zrtos_vfs_file_index[fd];
	file.dentry->count--;
	ret = ZRTOS_VFS_PLUGIN__INVOKE(
		 file.dentry->inode.plugin
		,ZRTOS_VFS_PLUGIN_OPERATION__CLOSE
		,&file
	);
	zrtos_vfs_file_index[fd].dentry = 0;
	return ret;
}

zrtos_error_t zrtos_vfs_file__read(size_t fd,char *path,void *buffer,size_t len,size_t offset,size_t *ret){
	zrtos_vfs_file_t file = zrtos_vfs_file_index[fd];
	return ZRTOS_VFS_PLUGIN__INVOKE(
		 file.dentry->inode.plugin
		,ZRTOS_VFS_PLUGIN_OPERATION__READ
		,&file
		,path
		,buffer
		,len
		,offset
		,ret
	);
}

zrtos_error_t zrtos_vfs_file__write(size_t fd,char *path,void *buffer,size_t len,size_t offset,size_t *ret){
	zrtos_vfs_file_t file = zrtos_vfs_file_index[fd];
	return ZRTOS_VFS_PLUGIN__INVOKE(
		 file.dentry->inode.plugin
		,ZRTOS_VFS_PLUGIN_OPERATION__WRITE
		,&file
		,path
		,buffer
		,len
		,offset
		,ret
	);
}

zrtos_error_t zrtos_vfs_file__ioctl(size_t fd,char *path,int request,...){
	zrtos_error_t ret;
	zrtos_vfs_file_t file = zrtos_vfs_file_index[fd];
	va_list       args;

	va_start(args,request);
	if(file.dentry){
		return ZRTOS_VFS_PLUGIN__INVOKE(
			 file.dentry->inode.plugin
			,ZRTOS_VFS_PLUGIN_OPERATION__IOCTL
			,&file
			,path
			,request
			,args
		);
	}else{
		ret = EBADF;
	}
	va_end(args);

	return ret;
}

void *zrtos_vfs_file__get_inode_data(zrtos_vfs_file_t *thiz){
	return thiz->dentry->inode.ctx;
}

#ifdef __cplusplus
}
#endif
#endif