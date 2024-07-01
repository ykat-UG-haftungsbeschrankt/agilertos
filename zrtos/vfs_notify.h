/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VFS_NOTIFY_H
#define ZRTOS_VFS_NOTIFY_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/bitfield.h>
#include <zrtos/vfs_fd.h>

struct _zrtos_vfs_notify_t;

typedef void (*zrtos_vfs_notify_callback_t)(
	 struct _zrtos_vfs_notify_t *thiz
	,zrtos_vfs_fd_t fd
);

typedef struct _zrtos_vfs_notify_entry_t{
	zrtos_vfs_notify_callback_t on_can_read;
	zrtos_vfs_notify_callback_t on_can_write;
}zrtos_vfs_notify_entry_t;

typedef struct _zrtos_vfs_notify_t{
	zrtos_vfs_fd_set_t fdset;
	zrtos_vfs_notify_entry_t data[ZRTOS_VFS_FILE_DESCRIPTOR__CFG_MAX];
	zrtos_error_t error;
}zrtos_vfs_notify_t;

bool zrtos_vfs_notify__init(zrtos_vfs_notify_t *thiz){
	zrtos_vfs_fd_set__init(&thiz->fdset);
	zrtos_mem__zero(
		 &thiz->data
		,sizeof(zrtos_vfs_notify_entry_t)*ZRTOS_VFS_FILE_DESCRIPTOR__CFG_MAX
	);
	thiz->error = ESUCCESS;

	return true;
}

void zrtos_vfs_notify__add(
	 zrtos_vfs_notify_t *thiz
	,zrtos_vfs_fd_t fd
	,zrtos_vfs_notify_callback_t on_can_read
	,zrtos_vfs_notify_callback_t on_can_write
){
	zrtos_vfs_fd_set__set(&thiz->fdset,fd);
	zrtos_vfs_notify_entry_t *entry = &thiz->data[fd.fd];
	entry->on_can_read = on_can_read;
	entry->on_can_write = on_can_write;
}

void zrtos_vfs_notify__remove(
	 zrtos_vfs_notify_t *thiz
	,zrtos_vfs_fd_t fd
){
	zrtos_vfs_fd_set__clear(&thiz->fdset,fd);
	zrtos_vfs_notify_entry_t *entry = &thiz->data[fd.fd];
	entry->on_can_read = 0;
	entry->on_can_write = 0;
}

void zrtos_vfs_notify__start(
	zrtos_vfs_notify_t *thiz
){
	zrtos_vfs_fd_set_t fdset_can_read;
	zrtos_vfs_fd_set_t fdset_can_write;

	while(zrtos_error__is_success(thiz->error)){
		zrtos_vfs_fd_set__copy(&fdset_can_read,&thiz->fdset);
		zrtos_vfs_fd_set__copy(&fdset_can_write,&thiz->fdset);
		if(zrtos_vfs_fd__select(&fdset_can_read,&fdset_can_write)>0){
			ZRTOS_VFS_FD_SET__EACH_BEGIN(&fdset_can_read,fd){
				if(thiz->data[fd.fd].on_can_read){
					thiz->data[fd.fd].on_can_read(
						 thiz
						,fd
					);
				}
			}ZRTOS_VFS_FD_SET__EACH_END;

			ZRTOS_VFS_FD_SET__EACH_BEGIN(&fdset_can_write,fd){
				if(thiz->data[fd.fd].on_can_write){
					thiz->data[fd.fd].on_can_write(
						 thiz
						,fd
					);
				}
			}ZRTOS_VFS_FD_SET__EACH_END;
		}
	}
}

void zrtos_vfs_notify__stop(
	zrtos_vfs_notify_t *thiz
){
	thiz->error = EINTR;
}

#ifdef __cplusplus
}
#endif
#endif