/* vim: noai:ts=4
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_DEBUG_H
#define ZRTOS_DEBUG_H
#ifdef __cplusplus
extern "C" {
#endif

#ifdef ZRTOS_DEBUG__ENABLED

#ifdef ZRTOS__USE_MEMSET
#define zrtos_debug__memset memset
#else
void *zrtos_debug__memset(void *dest,int value, size_t n){
	register uint8_t *ptr = (uint8_t *) dest;
	register uint8_t val = value;
	while(n--){
		*ptr++ = val;
	}
	return dest;
}
#endif

#define ZRTOS__DEBUG_CODE(code) code

#else

#define ZRTOS__DEBUG_CODE(code)

#endif

#ifdef __cplusplus
}
#endif
#endif