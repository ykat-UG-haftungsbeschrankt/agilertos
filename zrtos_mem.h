/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_MEM_H
#define ZRTOS_MEM_H
#ifdef __cplusplus
extern "C" {
#endif


#include "zrtos_types.h"


/**
 * Swap \p len bytes of \p dest and \p src inplace.
 * 
 * @param[in] dest destination
 * @param[in] src source
 * @param[in] len byte length to swap
 * 
 * @return Nothing
 */
void zrtos_mem__swap(void *dest, void *src, size_t len){
	uint8_t *tmp_dest = dest;
	uint8_t *tmp_src = src;
	while(len--){
		ZRTOS_TYPES__SWAP_PTR_CONTENTS(tmp_src,tmp_dest);
		tmp_src++;
		tmp_dest++;
	}
}

void zrtos_mem__swap_ex(
	 void *ptr
	,size_t offest_dest
	,size_t offset_src
	,size_t len
){
	zrtos_mem__swap(
		 zrtos_types__ptr_add(ptr,offest_dest)
		,zrtos_types__ptr_add(ptr,offset_src)
		,len
	);
}

void zrtos_mem__left_rotate(
	 void *ptr
	,size_t length
	,size_t buffer_length
){
	size_t d = length;
	size_t n = buffer_length;
	size_t i = d;
	size_t j = n - d;
	while(i != j){
		if(i < j){
			//A is shorter
			zrtos_mem__swap_ex(ptr, d - i, d + j - i, i);
			j -= i;
		}else{
			//B is shorter
			zrtos_mem__swap_ex(ptr, d - i, d, j);
			i -= j;
		}
	}
	//Finally, block swap A and B
	zrtos_mem__swap_ex(ptr, d - i, d, i);
}

#ifdef ZRTOS__USE_MEMMOVE
# define zrtos_mem__move_right_overlapping memmove
# define zrtos_mem__move_left_overlapping memmove
#else
void zrtos_mem__move_right_overlapping(
	 void *dest
	,void *src
	,size_t length
){
	uint8_t *tmp_dest = dest;
	uint8_t *tmp_src = src;
	tmp_dest += --length;
	tmp_src += length++;
	while(length--){
		*tmp_dest-- = *tmp_src--;
	}
}

void zrtos_mem__move_left_overlapping(
	  void *dest
	 ,void *src
	 ,size_t length
){
	uint8_t *tmp_dest = dest;
	uint8_t *tmp_src = src;
	while(length--){
		*tmp_dest++ = *tmp_src++;
	}
}
#endif

void zrtos_mem__cpy(
	  void *dest
	 ,void *src
	 ,size_t length
){
	zrtos_mem__move_left_overlapping(dest,src,length);
}

void zrtos_mem__reverse(void *dest,size_t len){
	uint8_t *tmp_dest = dest;
	uint8_t *tmp_src = tmp_dest + len;
	len>>=1;
	while(len--){
		ZRTOS_TYPES__SWAP_PTR_CONTENTS(tmp_dest,tmp_src);
		tmp_dest++;
		tmp_src--;
	}
}

void *zrtos_mem__search(const void *key, const void *base, size_t /* nmemb */ high,
			  size_t size, int (*compar)(const void *, const void *))
{
	register char *p;
	size_t low;
	size_t mid;
	int r;

	if (size > 0) {				/* TODO: change this to an assert?? */
		low = 0;
		while (low < high) {
			mid = low + ((high - low) >> 1); /* Avoid possible overflow here. */
			p = ((char *)base) + mid * size; /* Could overflow here... */
			r = (*compar)(key, p); /* but that's an application problem! */
			if (r > 0) {
				low = mid + 1;
			} else if (r < 0) {
				high = mid;
			} else {
				return p;
			}
		}
	}
	return NULL;
}

void zrtos_mem__sort(void  *base,
           size_t nel,
           size_t width,
           int (*comp)(const void *, const void *))
{
	size_t wnel, gap, wgap, i, j, k;
	char *a, *b, tmp;

	wnel = width * nel;
	for (gap = 0; ++gap < nel;)
		gap *= 3;
	while ((gap /= 3) != 0) {
		wgap = width * gap;
		for (i = wgap; i < wnel; i += width) {
			for (j = i - wgap; ;j -= wgap) {
				a = j + (char *)base;
				b = a + wgap;
				if ((*comp)(a, b) <= 0)
					break;
				k = width;
				do {
					tmp = *a;
					*a++ = *b;
					*b++ = tmp;
				} while (--k);
				if (j < wgap)
					break;
			}
		}
	}
}


#ifdef __cplusplus
}
#endif
#endif