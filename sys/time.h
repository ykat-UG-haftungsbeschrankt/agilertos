/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_SYS_TIME_H
#define ZRTOS_SYS_TIME_H
#ifdef __cplusplus
extern "C" {
#endif


#include <sys/types.h>


struct timeval{
	time_t         tv_sec;
	suseconds_t    tv_usec;
};

struct itimerval{
	struct timeval it_interval timer interval;
	struct timeval it_value    current value;
};


#ifdef __cplusplus
}
#endif
#endif