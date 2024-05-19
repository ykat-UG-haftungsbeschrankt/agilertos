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

void zrtos_str__swap(void *dest, void *src, size_t len){
	uint8_t *tmp_dest = dest;
	uint8_t *tmp_src = src;
	while(len--){
		ZRTOS_TYPES__SWAP_PTR_CONTENTS(tmp_src,tmp_dest);
		tmp_src++;
		tmp_dest++;
	}
}

void zrtos_str__swap_ex(void *str, size_t offest_dest, size_t offset_src, size_t len){
	zrtos_str__swap(str + offest_dest,str + offset_src,len);
}

void zrtos_str__left_rotate(void *str, size_t d, size_t n){ 
    size_t i = d; 
    size_t j = n - d; 
    while (i != j) { 
        if (i < j) /*A is shorter*/
        { 
            zrtos_str__swap_ex(str, d - i, d + j - i, i); 
            j -= i; 
        } 
        else /*B is shorter*/
        { 
            zrtos_str__swap_ex(str, d - i, d, j); 
            i -= j; 
        } 
        // printArray(arr, 7); 
    } 
    /*Finally, block swap A and B*/
    zrtos_str__swap_ex(str, d - i, d, i);
}

void zrtos_str__swap_to_end(
	 void *buffer
	,size_t length
	,size_t buffer_length
){
	size_t total_length = buffer_length - length;
	size_t rest_block_length = total_length % length;
	//size_t full_block_length = total_length - rest_block_length;
	size_t l = total_length - rest_block_length;//full_block_length;
	uint8_t *src = buffer;
	uint8_t *dest = src + length;

	while(l--){
		ZRTOS_TYPES__SWAP_PTR_CONTENTS(src,dest);
		src++;
		dest++;
		//_zrtos_mem__swap_uint8(src++,dest++);
	}

	zrtos_str__left_rotate(
		 src
		,length
		,rest_block_length + length
	);
}

#ifdef ZRTOS__USE_MEMMOVE
# define zrtos_str__move_right_overlapping memmove
# define zrtos_str__move_left_overlapping memmove
#else
void zrtos_str__move_right_overlapping(
	 uint8_t *dest
	,uint8_t *src
	,size_t length
){
	dest += --length;
	src += length++;
	while(length--){
		*dest-- = *src--;
	}
}

void zrtos_str__move_left_overlapping(
	  uint8_t *dest
	 ,uint8_t *src
	 ,size_t length
){
	while(length--){
		*dest++ = *src++;
	}
}
#endif

char* zrtos_str__ultoa( uint64_t value, char *string, int radix )
{
  char tmp[33];
  char *tp = tmp;
  int64_t i;
  uint64_t v = value;
  char *sp;

  if ( string == NULL )
  {
    return 0;
  }

  if (radix > 36 || radix <= 1)
  {
    return 0;
  }

  while (v || tp == tmp)
  {
    i = v % radix;
    v = v / radix;
    if (i < 10)
      *tp++ = i+'0';
    else
      *tp++ = i + 'a' - 10;
  }

  sp = string;


  while (tp > tmp)
    *sp++ = *--tp;
  *sp = 0;

  return string;
}

void zrtos_str__vsnprintf_internal(
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

typedef struct _zrtos_str__vsnprintf_cb_args_t{
    char *dest;
    size_t len;
    size_t ret;
}zrtos_str__vsnprintf_cb_args_t;

void zrtos_str__vsnprintf_cb(void *args_,char ch){
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