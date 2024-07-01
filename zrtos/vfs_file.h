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


#include <zrtos/error.h>
#include <zrtos/bitfield.h>
#include <zrtos/vfs_dentry.h>

typedef struct _zrtos_vfs_file_t{
	zrtos_vfs_dentry_t *dentry;
	zrtos_vfs_offset_t offset;
	void               *ctx;
}zrtos_vfs_file_t;

#ifndef ZRTOS_VFS_FILE_DESCRIPTOR__CFG_MAX
#error "define ZRTOS_VFS_FILE_DESCRIPTOR__CFG_MAX"
#endif

zrtos_vfs_file_t zrtos_vfs_file__index[ZRTOS_VFS_FILE_DESCRIPTOR__CFG_MAX];

zrtos_error_t zrtos_vfs_file__open(char *path,zrtos_vfs_file_t **file){
	zrtos_error_t ret;
	zrtos_vfs_dentry_t *dentry = zrtos_vfs_dentry__lookup(
		 0
		,path
	);
	if(dentry){ 
		for(size_t fd=0;fd<ZRTOS_VFS_FILE_DESCRIPTOR__CFG_MAX;fd++){
			if(0 == zrtos_vfs_file__index[fd].dentry){
				zrtos_vfs_file_t *tmp = *file = &zrtos_vfs_file__index[fd];

				dentry->count++;
				tmp->dentry = dentry;

				zrtos_vfs_plugin_t *plugin = dentry->inode.plugin;
				ret = ZRTOS_VFS_PLUGIN__INVOKE(
					 plugin
					,ZRTOS_VFS_PLUGIN_OPERATION__OPEN
					,tmp
				);
				if(!zrtos_error__is_success(ret)){
					dentry->count--;
					tmp->dentry = 0;
				}
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

zrtos_error_t zrtos_vfs_file__close(zrtos_vfs_file_t *file){
	zrtos_error_t ret;

	file->dentry->count--;
	ret = ZRTOS_VFS_PLUGIN__INVOKE(
		 file->dentry->inode.plugin
		,ZRTOS_VFS_PLUGIN_OPERATION__CLOSE
		,file
	);
	file->dentry = 0;
	file->offset = 0;

	return ret;
}

zrtos_error_t zrtos_vfs_file__read(
	 zrtos_vfs_file_t *file
	,char *path
	,void *buffer
	,size_t len
	,size_t offset
	,size_t *ret
){
	return file->dentry ? ZRTOS_VFS_PLUGIN__INVOKE(
		 file->dentry->inode.plugin
		,ZRTOS_VFS_PLUGIN_OPERATION__READ
		,file
		,path
		,buffer
		,len
		,offset
		,ret
	) : EBADF;
}

zrtos_error_t zrtos_vfs_file__write(
	 zrtos_vfs_file_t *file
	,char *path
	,void *buffer
	,size_t len
	,size_t offset
	,size_t *ret
){
	return file->dentry ? ZRTOS_VFS_PLUGIN__INVOKE(
		 file->dentry->inode.plugin
		,ZRTOS_VFS_PLUGIN_OPERATION__WRITE
		,file
		,path
		,buffer
		,len
		,offset
		,ret
	) : EBADF;
}

zrtos_error_t zrtos_vfs_file__can_read(
	 zrtos_vfs_file_t *file
){
	return file->dentry ? ZRTOS_VFS_PLUGIN__INVOKE(
		 file->dentry->inode.plugin
		,ZRTOS_VFS_PLUGIN_OPERATION__CAN_READ
		,file
	) : EBADF;
}

zrtos_error_t zrtos_vfs_file__can_write(
	 zrtos_vfs_file_t *file
){
	return file->dentry ? ZRTOS_VFS_PLUGIN__INVOKE(
		 file->dentry->inode.plugin
		,ZRTOS_VFS_PLUGIN_OPERATION__CAN_WRITE
		,file
	) : EBADF;
}

zrtos_error_t zrtos_vfs_file__ioctl_va(
	 zrtos_vfs_file_t *file
	,char *path
	,int request
	,va_list args
){
	zrtos_error_t ret;

	ret = file->dentry ? ZRTOS_VFS_PLUGIN__INVOKE(
		 file->dentry->inode.plugin
		,ZRTOS_VFS_PLUGIN_OPERATION__IOCTL
		,file
		,path
		,request
		,args
	) : EBADF;

	return ret;
}

zrtos_error_t zrtos_vfs_file__ioctl(
	 zrtos_vfs_file_t *file
	,char *path
	,int request
	,...
){
	zrtos_error_t ret;
	va_list       args;

	va_start(args,request);
	ret = zrtos_vfs_file__ioctl_va(
		 file
		,path
		,request
		,args
	);
	va_end(args);

	return ret;
}

void zrtos_vfs_file__set_inode_data(zrtos_vfs_file_t *thiz,void *ctx){
	thiz->dentry->inode.ctx = ctx;
}

void *zrtos_vfs_file__get_inode_data(zrtos_vfs_file_t *thiz){
	return thiz->dentry->inode.ctx;
}

void zrtos_vfs_file__set_data(zrtos_vfs_file_t *thiz,void *ctx){
	thiz->ctx = ctx;
}

void *zrtos_vfs_file__get_data(zrtos_vfs_file_t *thiz){
	return thiz->ctx;
}

void zrtos_vfs_file__set_offset(zrtos_vfs_file_t *thiz,zrtos_vfs_offset_t offset){
	thiz->offset = offset;
}

zrtos_vfs_offset_t zrtos_vfs_file__get_offset(zrtos_vfs_file_t *thiz){
	return thiz->offset;
}

#define ZRTOS_VFS_FILE__EACH_BEGIN(fd,file)\
	for(size_t fd = 0;fd < ZRTOS_VFS_FILE_DESCRIPTOR__CFG_MAX;fd++){\
		zrtos_vfs_file_t *file = &zrtos_vfs_file__index[fd];\
		if(0 != file->dentry){

#define ZRTOS_VFS_FILE__EACH_END\
        }\
    }

#ifdef __cplusplus
}
#endif
#endif