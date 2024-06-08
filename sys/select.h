/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_SYS_SELECT_H
#define ZRTOS_SYS_SELECT_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/bitfield.h>
#include <zrtos/vfs_file.h>

#include <sys/time.h>


#define FD_SETSIZE ZRTOS_FILE_DESCRIPTOR__CFG_MAX

typedef struct{
	zrtos_bitfield_t fds_bits[FD_SETSIZE / ZRTOS_BITFIELD__NFDBITS]
}fd_set;

int select(
	 int nfds
	,fd_set *readfds
	,fd_set *writefds
	,fd_set *exceptfds
	,struct timeval *timeout
){
	int ret = 0;
	typeof(zrtos_file__can_read) callback = zrtos_vfs_file__can_read;
	zrtos_bitfield_t *bitfield = readfds->fds_bits;
	size_t l = 1;

	while(l--){
		ZRTOS_BITFIELD__EACH(
			 bitfield
			,FD_SETSIZE / ZRTOS_BITFIELD__NFDBITS
			,fd
		){
			if(!callback(fd)){
				zrtos_bitfield__set(
					 bitfield
					,fd
					,false
				);
			}else{
				ret++;
			}
		}
		callback = zrtos_vfs_file__can_write;
		bitfield = writefds->fds_bits;
	}

	return ret;
}

void FD_CLR(int fd, fd_set *set){
	zrtos_bitfield__set(
		 set->fds_bits
		,(size_t)fd
		,false
	);
}

int FD_ISSET(int fd, fd_set *set){
	return (int)zrtos_bitfield__get(
		 set->fds_bits
		,(size_t)fd
	);
}

void FD_SET(int fd, fd_set *set){
	zrtos_bitfield__set(
		 set->fds_bits
		,(size_t)fd
		,true
	);
}

void FD_ZERO(fd_set *set){
	zrtos_bitfield__zero(
		 set->fds_bits
		,FD_SETSIZE/ZRTOS_BITFIELD__NFDBITS
	);
}


#ifdef __cplusplus
}
#endif
#endif