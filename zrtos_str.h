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
#include "zrtos_mem.h"


typedef struct _zrtos_str__vsnprintf_cb_args_t{
	char *dest;
	size_t len;
	size_t ret;
}zrtos_str__vsnprintf_cb_args_t;

size_t zrtos_str__len(char *str){
	char *tmp = str+1;
	while(*str++){}
	return zrtos_types__ptr_get_byte_distance(str,tmp);
}

void zrtos_str__reverse(char *str){
	zrtos_mem__reverse(str,zrtos_str__len(str));
}

/**
 * @brief 
 * 
 * 	if(str == NULL){
 * 		return 0;
 * 	}
 * 
 * 	if(radix > 36 || radix <= 1){
 * 		return 0;
 * 	}
 * 
 * @param value 
 * @param str 
 * @param radix 
 * @return char* 
 */
char* zrtos_str__ultoa(uint64_t value, char *str, int radix){
	char *tp = str;
	uint64_t i;
	uint64_t v = value;

	while(v){
		i = v % radix;
		v = v / radix;
		if(i < 10){
			*tp++ = i+'0';
		}else{
			*tp++ = i + 'a' - 10;
		}
	}

	zrtos_mem__reverse(
		 str
		,zrtos_types__ptr_get_byte_distance(tp,str)
	);

	*tp++ = 0;

	return tp;
}

#define ZRTOS_STR__DTOA_PRECISION 1000000

char* zrtos_str__dtoa(double val,char *str){
	char buffer[65];
	char *tmp = buffer;

	if(val < 0){
		val = -val;
		*tmp++ = '-';
	}

	uint64_t c = (val * ZRTOS_STR__DTOA_PRECISION) + .5;
	uint64_t d = c / ZRTOS_STR__DTOA_PRECISION;
	uint64_t f = c - (d * ZRTOS_STR__DTOA_PRECISION);

	tmp = zrtos_str__ultoa(d,tmp,10);
	*tmp++ = '.';
	return zrtos_str__ultoa(f,tmp,10);
}

static void zrtos_str__vsnprintf_internal(
	 void (*putc)(void *args,char c)
	,void *putc_args
	,char const *fmt
	,va_list arg
){
	char ch;
	uint8_t out_mod;
	char *out_str;
	size_t out_len;
	uint64_t out_num;
	uint8_t out_radix;
	double out_double;
	char buffer[64];

	while((ch = *fmt++)){
		out_mod = 0x1;
		if(ch == '%'){
			switch((ch = *fmt++)){
				case 'c':
					out_mod = 0x1;
					ch = va_arg(arg,int);
				break;
				case 's':
					out_mod = 0x4 | 0x2;
					out_str = va_arg(arg,char*);
				break;
				case 'S':
					out_mod = 0x4;
					out_len = va_arg(arg,size_t);
					out_str = va_arg(arg,char*);
				break;
				case 'd':{
					int tmp = va_arg(arg, int);
					out_num = (uint64_t)tmp;
					out_mod = 0x8 | 0x4 | 0x2;
					out_radix = 10;
					if(tmp < 0){
						ch = '-';
						out_mod |= 0x1;
					}
				}
				break;
				case 'u':{
					out_num = (uint64_t)va_arg(arg, int);
					out_mod = 0x8 | 0x4 | 0x2;
					out_radix = 10;
				}
				break;
				case 'f':{
					out_double = (double)va_arg(arg, float);
					goto L_PRINT_DOUBLE;
				}
				break;
				case 'F':{
					out_double = (uint64_t)va_arg(arg, double);
L_PRINT_DOUBLE:
					zrtos_str__dtoa(out_double,buffer);
					out_mod = 0x4 | 0x2;
					out_str = buffer;
				}
				break;
				case 'p':
					out_num = (uint64_t)va_arg(arg,uintptr_t);
					goto L_PRINT_HEX;
				case 'x':
					out_num = va_arg(arg,uint64_t);
L_PRINT_HEX:
					out_mod = 0x8 | 0x4 | 0x2;
					out_radix = 16;
				break;
				case 0:
				return;
			}
		}

		if(out_mod & 0x1){
			putc(putc_args,ch);
		}
		if(out_mod & 0x8){
			zrtos_str__ultoa(out_num, buffer, out_radix);
			out_str = buffer;
		}
		if(out_mod & 0x2){
			out_len = zrtos_str__len(out_str);
		}
		if(out_mod & 0x4){
			while(out_len--){
				putc(putc_args,*out_str++);
			}
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