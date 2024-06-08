/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_TIME_H
#define ZRTOS_TIME_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/board.h>


typedef struct _zrtos_time_ticks_t{
	uint64_t ticks;
}zrtos_time_ticks_t;

typedef struct _zrtos_time_t{
	uint64_t ts;
}zrtos_time_t;

zrtos_time_ticks_t zrtos_time__get_ticks(){
	zrtos_time_ticks_t ret = {
		.ticks = zrtos_board__get_ticks();
	};
	return ret;
}
zrtos_time_t zrtos_time__get_microseconds(){
	zrtos_time_t ret = {
		.ts = zrtos_board__get_microseconds()
	};
	return ret;
}
zrtos_time_t zrtos_time__get_milliseconds(){
	zrtos_time_t ret = {
		.ts = zrtos_board__get_microseconds() / 1000
	};
	return ret;
}
zrtos_time_t zrtos_time__get_seconds(){
	zrtos_time_t ret = {
		.ts = zrtos_board__get_microseconds() / 1000000
	};
	return ret;
}


#ifdef __cplusplus
}
#endif
#endif