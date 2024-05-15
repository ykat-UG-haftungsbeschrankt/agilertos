#include <avr/io.h>


typedef uint16_t size_t;
typedef int16_t ssize_t;
typedef enum{
	false
	,true
}bool;

#define ZRTOS_DEBUG__ENABLED

#include "zrtos_malloc.h"

ZRTOS_MALLOC__INIT(name,160);

int main(void){
	size_t length = 10,l;
	void *ptr[10];

	zrtos_malloc_buffer_t heap_buffer[160];
	zrtos_malloc_t heap2;
	zrtos_malloc__init(&heap2,heap_buffer,160);

	ZRTOS_MALLOC__INIT_DEBUG(name,160);

	for(l=0;l<length;l++){
		ptr[l] = malloc(16-4);
	}
	for(l=0;l<length;l++){
		free(ptr[l]);
	}
	for(l=0;l<length;l++){
		ptr[l] = malloc(16-4);
	}
	for(l=0;l<length;l++){
		free(ptr[l]);
	}


	for(l=0;l<length;l++){
		ptr[l] = zrtos_malloc__malloc(&heap2,16-4);
	}
	for(l=0;l<length;l++){
		zrtos_malloc__free(ptr[l]);
	}
	for(l=0;l<length;l++){
		ptr[l] = zrtos_malloc__malloc(&heap2,16-4);
	}
	for(l=0;l<length;l++){
		zrtos_malloc__free(ptr[l]);
	}

	return 0;
}
