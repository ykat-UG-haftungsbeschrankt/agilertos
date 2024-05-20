/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_STR_H
#define ZRTOS_STR_H
#ifdef __cplusplus
extern "C" {
#endif


#include <stdarg.h>

#include "zrtos_types.h"


typedef struct _zrtos_str__vsnprintf_cb_args_t{
	char *dest;
	size_t len;
	size_t ret;
}zrtos_str__vsnprintf_cb_args_t;


char* zrtos_str__ultoa(uint64_t value, char *str, int radix){
	char tmp[65];
	char *tp = tmp;
	int64_t i;
	uint64_t v = value;
	char *sp;

	if(str == NULL){
		return 0;
	}

	if(radix > 36 || radix <= 1){
		return 0;
	}

	while(v || tp == tmp){
		i = v % radix;
		v = v / radix;
		if(i < 10){
			*tp++ = i+'0';
		}else{
			*tp++ = i + 'a' - 10;
		}
	}

	sp = str;
	while(tp > tmp){
		*sp++ = *--tp;
	}
	*sp = 0;

	return str;
}

static void zrtos_str__vsnprintf_internal(
	 void (*putc)(void *args,char c)
	,void *putc_args
	,char const *fmt
	,va_list arg
){
	char ch;
	while((ch = *fmt++)){
		if(ch == '%'){
			switch((ch = *fmt++)){
				case '%':
					putc(putc_args,'%');
				break;
				case 'c':{
					int tmp = va_arg(arg,int);
					putc(putc_args,(char)tmp);
				}
				break;
				case 's':{
					char *tmp = va_arg(arg,char*);
					while((ch = *tmp++)){
						putc(putc_args,ch);
					}
				}
				break;
				case 'S':{
					char *tmp = va_arg(arg,char*);
					size_t len = va_arg(arg,size_t);
					while(len--){
						putc(putc_args,*tmp++);
					}
				}
				break;
				case 'd':{
					char buffer[64];
					int64_t tmp = va_arg(arg, int64_t);
					if(tmp < 0){
						putc(putc_args,'-');
						tmp = -tmp;
					}
					zrtos_str__ultoa(tmp, buffer, 10);
					for(char *ptr = buffer;(ch = *ptr++);){
						putc(putc_args,ch);
					}
				}
				break;
				case 'u':{
					char buffer[64];
					uint64_t tmp = va_arg(arg, uint64_t);
					zrtos_str__ultoa(tmp, buffer, 10);
					for(char *ptr = buffer;(ch = *ptr++);){
						putc(putc_args,ch);
					}
				}
				break;
				case 'x':{
					char buffer[64];
					uint64_t tmp = va_arg(arg, uint64_t);
					zrtos_str__ultoa(tmp, buffer, 16);
					for(char *ptr = buffer;(ch = *ptr++);){
						putc(putc_args,ch);
					}
				}
				break;
				case 0:
				return;
			}
		}else{
			putc(putc_args,ch);
		}
	}
}

static void zrtos_str__vsnprintf_cb(void *args_,char ch){
	zrtos_str__vsnprintf_cb_args_t *args = (zrtos_str__vsnprintf_cb_args_t*)args_;
	if(args->len--){
		*args->dest++ = ch;
	}
	args->ret++;
}

int zrtos_str__vsnprintf(char *dest,size_t len,char const *fmt, ...){
	va_list arg;
	zrtos_str__vsnprintf_cb_args_t args = {
		 .dest = dest
		,.len = len
	};
	va_start(arg, fmt);
	zrtos_str__vsnprintf_internal(
		 zrtos_str__vsnprintf_cb
		,&args
		,fmt
		,arg
	);
	va_end(arg);
	return args.ret;
}


#ifdef __cplusplus
}
#endif
#endif