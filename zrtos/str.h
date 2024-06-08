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

#include <zrtos/types.h>
#include <zrtos/mem.h>


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

int zrtos_str__cmp(char *a,char *b){
	size_t a_len = zrtos_str__len(a);
	size_t b_len = zrtos_str__len(b);
	int ret = ZRTOS_TYPES__CMP(size_t,a_len,b_len);
	return ret ? ret : zrtos_mem__cmp(a,b,a_len);
}

void zrtos_str__reverse(char *str){
	zrtos_mem__reverse(str,zrtos_str__len(str));
}

/**
 * @param value 
 * @param str must be str != NULL
 * @param radix must be radix < 36 && radix >= 1
 * @return char* 
 */
char *zrtos_str__ultoa(uint64_t value, char *str, int radix){
	char *tp = str;
	uint64_t i;
	uint64_t v = value;

	while(v){
		i = v % radix;
		v = v / radix;
		if(i < 10){
			*tp++ = i + '0';
		}else{
			*tp++ = i + 'a' - 10;
		}
	}

	zrtos_mem__reverse(
		 str
		,zrtos_types__ptr_get_byte_distance(tp,str)
	);

	*tp = 0;

	return tp;
}

char *zrtos_str__ltoa(int64_t value, char *str, int radix){
	if(value < 0){
		value = -value;
		*str++ = '-';
	}
	return zrtos_str__ultoa(value,str,radix);
}

#define ZRTOS_STR__CFG_DTOA_PRECISION 1000000

char *zrtos_str__dtoa(double val,char *str){
	int64_t c = (val * ZRTOS_STR__CFG_DTOA_PRECISION) + .5;
	int64_t d = c / ZRTOS_STR__CFG_DTOA_PRECISION;
	uint64_t f = c - (d * ZRTOS_STR__CFG_DTOA_PRECISION);

	str = zrtos_str__ltoa(d,str,10);
	*str++ = '.';
	return zrtos_str__ultoa(f,str,10);
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
					double out_double = va_arg(arg, double);
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

size_t zrtos_str__spn(const char *s1, const char *s2){
	register const char *p = s1, *spanp;
	register char c, sc;

	/*
	 * Skip any characters in s2, excluding the terminating \0.
	 */
cont:
	c = *p++;
	for (spanp = s2; (sc = *spanp++) != 0;){
		if (sc == c){
			goto cont;
		}
	}
	return (p - 1 - s1);
}

size_t zrtos_str__cspn(const char *s1,const char *s2){
	register const char *p, *spanp;
	register char c, sc;

	/*
	 * Stop as soon as we find any character from s2.  Note that there
	 * must be a NUL in s2; it suffices to stop when we find that, too.
	 */
	for (p = s1;;) {
		c = *p++;
		spanp = s2;
		do {
			if ((sc = *spanp++) == c){
				return (p - 1 - s1);
			}
		} while (sc != 0);
	}
	/* NOTREACHED */
}

/* Parse S into tokens separated by characters in DELIM.
   If S is NULL, the saved pointer in SAVE_PTR is used as
   the next starting point.  For example:
	char s[] = "-abc-=-def";
	char *sp;
	x = strtok_r(s, "-", &sp);	// x = "abc", sp = "=-def"
	x = strtok_r(NULL, "-=", &sp);	// x = "def", sp = NULL
	x = strtok_r(NULL, "=", &sp);	// x = NULL
		// s = "abc\0-def\0"
*/
char *zrtos_str__tok_r(char *s, const char *delim, char **save_ptr){
  char *end;
  if (s == NULL)
    s = *save_ptr;
  if (*s == '\0')
    {
      *save_ptr = s;
      return NULL;
    }
  /* Scan leading delimiters.  */
  s += zrtos_str__spn(s, delim);
  if (*s == '\0')
    {
      *save_ptr = s;
      return NULL;
    }
  /* Find the end of the token.  */
  end = s + zrtos_str__cspn(s, delim);
  if (*end == '\0')
    {
      *save_ptr = end;
      return s;
    }
  /* Terminate the token and make *SAVE_PTR point past it.  */
  *end = '\0';
  *save_ptr = end + 1;
  return s;
}


#ifdef __cplusplus
}
#endif
#endif