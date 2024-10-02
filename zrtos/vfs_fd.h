/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_FD_H
#define ZRTOS_VFS_FD_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/bitfield.h>
#include <zrtos/vfs_file.h>

typedef struct _zrtos_vfs_fd_t{
	size_t fd;
}zrtos_vfs_fd_t;

typedef struct _zrtos_vfs_fd_set_t{
	zrtos_bitfield_t fds_bits[
		ZRTOS_VFS_FILE_DESCRIPTOR__CFG_MAX / ZRTOS_BITFIELD__NFDBITS
	];
}zrtos_vfs_fd_set_t;

void zrtos_vfs_fd_set__clear(zrtos_vfs_fd_set_t *thiz,zrtos_vfs_fd_t fd){
	zrtos_bitfield__set(
		 thiz->fds_bits
		,fd.fd
		,false
	);
}

bool zrtos_vfs_fd_set__is_set(zrtos_vfs_fd_set_t *thiz,zrtos_vfs_fd_t fd){
	return zrtos_bitfield__get(
		 thiz->fds_bits
		,fd.fd
	);
}

void zrtos_vfs_fd_set__set(zrtos_vfs_fd_set_t *thiz,zrtos_vfs_fd_t fd){
	zrtos_bitfield__set(
		 thiz->fds_bits
		,fd.fd
		,true
	);
}

void zrtos_vfs_fd_set__zero(zrtos_vfs_fd_set_t *thiz){
	zrtos_bitfield__zero(
		 thiz->fds_bits
		,ZRTOS_VFS_FILE_DESCRIPTOR__CFG_MAX / ZRTOS_BITFIELD__NFDBITS
	);
}

void zrtos_vfs_fd_set__copy(zrtos_vfs_fd_set_t *thiz,zrtos_vfs_fd_set_t *src){
	zrtos_bitfield__copy(
		 thiz->fds_bits
		,src->fds_bits
		,ZRTOS_VFS_FILE_DESCRIPTOR__CFG_MAX / ZRTOS_BITFIELD__NFDBITS
	);
}

bool zrtos_vfs_fd_set__init(zrtos_vfs_fd_set_t *thiz){
	zrtos_vfs_fd_set__zero(thiz);
	return true;
}

zrtos_error_t zrtos_vfs_fd__open(char *path,zrtos_vfs_fd_t *thiz,void *file_ctx){
	zrtos_vfs_file_t *file;
	zrtos_error_t ret = zrtos_vfs_file__open(path,&file,file_ctx);
	thiz->fd = file - (&zrtos_vfs_file__index[0]);
	return ret;
}

zrtos_error_t zrtos_vfs_fd__close(zrtos_vfs_fd_t thiz){
	zrtos_error_t ret = ZRTOS_ERROR__INVAL;
	ZRTOS_TYPES__TYPEOF(thiz.fd) fd = thiz.fd;

	if(fd < ZRTOS_VFS_FILE_DESCRIPTOR__CFG_MAX){
		ret = zrtos_vfs_file__close(&zrtos_vfs_file__index[fd]);
	}

	return ret;
}

zrtos_error_t zrtos_vfs_fd__read(
	 zrtos_vfs_fd_t thiz
	,char *path
	,void *buffer
	,size_t len
	,size_t offset
	,size_t *outlen
){
	zrtos_error_t ret = ZRTOS_ERROR__INVAL;
	ZRTOS_TYPES__TYPEOF(thiz.fd) fd = thiz.fd;

	if(fd < ZRTOS_VFS_FILE_DESCRIPTOR__CFG_MAX){
		ret = zrtos_vfs_file__read(
			 &zrtos_vfs_file__index[fd]
			,path
			,buffer
			,len
			,offset
			,outlen
		);
	}

	return ret;
}

zrtos_error_t zrtos_vfs_fd__spi_transfer(
	 zrtos_vfs_fd_t fd
	,size_t len
	,...
){
	size_t l = 0;
	uint8_t ll;
	zrtos_error_t ret = ZRTOS_ERROR__SUCCESS;
	zrtos_va_t args1;
	zrtos_va_t args2;
	size_t outlen;

	zrtos_va__start(len,args1);
	zrtos_va__copy(args2,args1);

	while(len--){
		zrtos_va__arg_ptr(args2,void*);
		l += zrtos_va__arg(args2,size_t);
	}

	ll = l;

	ret = zrtos_vfs_fd__read(
		 fd
		,(char*)""
		,&ll
		,1
		,0
		,&outlen
	);

	while(zrtos_error__is_success(ret) && len--){
		void *buffer = zrtos_va__arg_ptr(args,void*);
		size_t length = zrtos_va__arg(args,size_t);
		ret = zrtos_vfs_fd__read(
			 fd
			,(char*)""
			,buffer
			,length
			,0
			,&outlen
		);
	}

	zrtos_va__end(args1);
	zrtos_va__end(args2);

	return ret;
}

bool zrtos_vfs_fd__is_sync_again_error(zrtos_error_t ret){
	return ret == ZRTOS_ERROR__AGAIN
	    || ret == ZRTOS_ERROR__WOULDBLOCK
	;
}

zrtos_error_t zrtos_vfs_fd__read_sync(
	 zrtos_vfs_fd_t thiz
	,char *path
	,void *buffer
	,size_t len
	,size_t offset
){
	zrtos_error_t ret = ZRTOS_ERROR__AGAIN;
	size_t outlen;
	uint8_t *data = ZRTOS_CAST(uint8_t*,buffer);

	while(len && zrtos_vfs_fd__is_sync_again_error(ret)){
		ret = zrtos_vfs_fd__read(
			 thiz
			,path
			,data
			,len
			,offset
			,&outlen
		);
		if(zrtos_error__is_success(ret)){
			len -= outlen;
			offset += outlen;
			data += outlen;
		}
	}

	return ret;
}

zrtos_error_t zrtos_vfs_fd__write(
	 zrtos_vfs_fd_t thiz
	,char *path
	,void *buffer
	,size_t len
	,size_t offset
	,size_t *outlen
){
	zrtos_error_t ret = ZRTOS_ERROR__INVAL;
	ZRTOS_TYPES__TYPEOF(thiz.fd) fd = thiz.fd;

	if(fd < ZRTOS_VFS_FILE_DESCRIPTOR__CFG_MAX){
		ret = zrtos_vfs_file__write(
			 &zrtos_vfs_file__index[fd]
			,path
			,buffer
			,len
			,offset
			,outlen
		);
	}

	return ret;
}

zrtos_error_t zrtos_vfs_fd__write_sync(
	 zrtos_vfs_fd_t thiz
	,char *path
	,void *buffer
	,size_t len
	,size_t offset
){
	zrtos_error_t ret = ZRTOS_ERROR__AGAIN;
	size_t outlen;
	uint8_t *data = ZRTOS_CAST(uint8_t*,buffer);

	while(len && zrtos_vfs_fd__is_sync_again_error(ret)){
		ret = zrtos_vfs_fd__write(
			 thiz
			,path
			,data
			,len
			,offset
			,&outlen
		);
		if(zrtos_error__is_success(ret)){
			len -= outlen;
			offset += outlen;
			data += outlen;
		}
	}

	return ret;
}

zrtos_error_t zrtos_vfs_fd__ioctl(
	 zrtos_vfs_fd_t thiz
	,char *path
	,int request
	,...
){
	zrtos_error_t ret = ZRTOS_ERROR__INVAL;
	ZRTOS_TYPES__TYPEOF(thiz.fd) fd = thiz.fd;
	va_list       args;

	va_start(args,request);
	if(fd < ZRTOS_VFS_FILE_DESCRIPTOR__CFG_MAX){
		ret = zrtos_vfs_file__ioctl_va(
			 &zrtos_vfs_file__index[fd]
			,path
			,request
			,args
		);
	}
	va_end(args);

	return ret;
}

zrtos_error_t zrtos_vfs_fd__can_read(
	 zrtos_vfs_fd_t thiz
){
	zrtos_error_t ret = ZRTOS_ERROR__INVAL;
	ZRTOS_TYPES__TYPEOF(thiz.fd) fd = thiz.fd;

	if(fd < ZRTOS_VFS_FILE_DESCRIPTOR__CFG_MAX){
		ret = zrtos_vfs_file__can_read(
			 &zrtos_vfs_file__index[fd]
		);
	}

	return ret;
}

zrtos_error_t zrtos_vfs_fd__can_write(
	 zrtos_vfs_fd_t thiz
){
	zrtos_error_t ret = ZRTOS_ERROR__INVAL;
	ZRTOS_TYPES__TYPEOF(thiz.fd) fd = thiz.fd;

	if(fd < ZRTOS_VFS_FILE_DESCRIPTOR__CFG_MAX){
		ret = zrtos_vfs_file__can_write(
			 &zrtos_vfs_file__index[fd]
		);
	}

	return ret;
}

size_t zrtos_vfs_fd__select(
	 zrtos_vfs_fd_set_t *readfds
	,zrtos_vfs_fd_set_t *writefds
){
	size_t ret = 0;
	ZRTOS_TYPES__TYPEOF(zrtos_vfs_fd__can_read) callback = zrtos_vfs_fd__can_read;
	zrtos_bitfield_t *bitfield = readfds->fds_bits;
	size_t l = 1;

	while(l--){
		ZRTOS_BITFIELD__EACH(
			 bitfield
			,ZRTOS_VFS_FILE_DESCRIPTOR__CFG_MAX / ZRTOS_BITFIELD__NFDBITS
			,pos
		){
			zrtos_vfs_fd_t fd = {.fd = pos};
			if(ZRTOS_ERROR__AGAIN == callback(fd)){
				zrtos_bitfield__set(
					 bitfield
					,fd.fd
					,false
				);
			}else{
				ret++;
			}
		}
		callback = zrtos_vfs_fd__can_write;
		bitfield = writefds->fds_bits;
	}

	return ret;
}

#define ZRTOS_VFS_FD_SET__EACH_BEGIN(thiz,fd_)\
	ZRTOS_BITFIELD__EACH(\
		 (thiz)->fds_bits\
		,ZRTOS_VFS_FILE_DESCRIPTOR__CFG_MAX / ZRTOS_BITFIELD__NFDBITS\
		,pos\
	){\
		zrtos_vfs_fd_t fd_ = {.fd = pos};

#define ZRTOS_VFS_FD_SET__EACH_END\
	}

#ifdef __cplusplus
}
#endif
#endif