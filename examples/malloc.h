#include <avr/io.h>

#define ZRTOS_DEBUG__CFG_ENABLED

#include <zrtos/malloc.h>

ZRTOS_MALLOC__GLOBAL_HEAP(heap,160);

int main(void){
	ZRTOS_MALLOC__GLOBAL_HEAP_INIT(heap);
	ZRTOS_MALLOC__INIT(heap2,160);

	size_t length = 10,l;
	void *ptr[10];

	for(l=0;l<=length;l++){
		ptr[l] = malloc(16-4);
	}
	for(l=0;l<=length;l++){
		free(ptr[l]);
	}
	for(l=0;l<=length;l++){
		ptr[l] = malloc(16-4);
	}
	for(l=0;l<=length;l++){
		free(ptr[l]);
	}

	for(l=0;l<=length;l++){
		ptr[l] = zrtos_malloc__malloc(heap2,16-4);
	}
	for(l=0;l<=length;l++){
		zrtos_malloc__free(ptr[l]);
	}
	for(l=0;l<=length;l++){
		ptr[l] = zrtos_malloc__malloc(heap2,16-4);
	}
	for(l=0;l<=length;l++){
		zrtos_malloc__free(ptr[l]);
	}

	return 0;
}
