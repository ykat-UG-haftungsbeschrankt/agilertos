#include <avr/io.h>


#define ZRTOS_ARCH__ATMEGA328P
#define ZRTOS_DEBUG__CFG_ENABLED
#define ZRTOS_DEBUG__CFG_MEMORY_CONSOLE 160

#include "zrtos.h"
#include "zrtos_task_pthread.h"
#include "zrtos_debug.h"

unsigned a = 0;
unsigned b = 0;

void *callback0(void *args){
	static uint64_t a = 0;
	while(1){
		a++;
		ZRTOS_DEBUG("callback0:%u;",a);
		zrtos_task_scheduler__delay_ms(1);
	}
}
void *callback1(void *args){
	static uint64_t b = 0;
	while(1){
		b++;
		ZRTOS_DEBUG("callback1:%u;",b);
		zrtos_task_scheduler__delay_ms(1);
	}
}

int main(void){
	pthread_t task0;
	pthread_t task1;
	zrtos_mem_t mem;   
	zrtos_mem__init(&mem,(void*)0x400,16*20);
	
	zrtos_task_scheduler__set_heap(&mem);

	if(pthread_create(
		 &task0
		,0
		,callback0
		,(void*)0xAFFE
	) == 0
	&& pthread_create(
		 &task1
		,0
		,callback1
		,(void*)0xCFFE
	) == 0){
		zrtos_task_scheduler__start();
	}
}

