#include <avr/io.h>

#define ZRTOS_DEBUG__ENABLED

#include "zrtos_malloc.h"

ZRTOS_MALLOC__GLOBAL_HEAP(heap,160);

int main(void){
	ZRTOS_MALLOC__GLOBAL_HEAP_INIT(heap);

	size_t length = 10,l;
	void *ptr[10];

	ZRTOS_MALLOC__HEAP(heap2,160);

	ZRTOS_MALLOC__INIT_DEBUG(heap,160);

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
		ptr[l] = zrtos_malloc__malloc(heap2,16-4);
	}
	for(l=0;l<length;l++){
		zrtos_malloc__free(ptr[l]);
	}
	for(l=0;l<length;l++){
		ptr[l] = zrtos_malloc__malloc(heap2,16-4);
	}
	for(l=0;l<length;l++){
		zrtos_malloc__free(ptr[l]);
	}

	return 0;
}
