/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_FILE_DESCRIPTOR_H
#define ZRTOS_FILE_DESCRIPTOR_H
#ifdef __cplusplus
extern "C" {
#endif


#include "zrtos_bitfield.h"

zrtos_bitfield_t zrtos_file_descriptor_index[
	(ZRTOS_FILE_DESCRIPTOR__CFG_MAX/ZRTOS_BITFIELD__NFDBITS)+1
] = {};

zrtos_file_t *zrtos_file_descriptor[ZRTOS_FILE_DESCRIPTOR__CFG_MAX];

size_t zrtos_file_descriptor__open(){
	size_t fd = zrtos_bitfield__find_first_zero(
		 zrtos_file_descriptor_index
		,ZRTOS_TYPES__GET_STATIC_ARRAY_LENGTH(zrtos_file_descriptor_index)
		,0
	);
	if(fd != -1)
	zrtos_bitfield__set(zrtos_file_descriptor_index,fd,true);
	return fd;
}

size_t zrtos_file_descriptor__close(size_t fd){
	zrtos_bitfield__set(zrtos_file_descriptor_index,fd,false);
}

bool zrtos_file_descriptor__is_file(size_t fd){
	return zrtos_bitfield__get(zrtos_file_descriptor_index,fd);
}

zrtos_file_t *zrtos_file_descriptor__get_file(size_t fd){
	return zrtos_file_descriptor[fd];
}


#ifdef __cplusplus
}
#endif
#endif