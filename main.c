#include <avr/io.h>


#define ZRTOS_CPU__ATMEGA328P
#define ZRTOS_DEBUG__ENABLED

#include "zrtos.h"
#include "zrtos_task_pthread.h"

unsigned a = 0;
unsigned b = 0;

void *callback0(void *args){
	while(1){
		a++;
	}
}
void *callback1(void *args){
	while(1){
		b++;
	}
}

ZRTOS_MEM__INIT(task_heap,300);

int main(void){
	pthread_t task0;
	pthread_t task1;
	
	zrtos_task_scheduler__set_heap(ZRTOS_MEM__GET(task_heap));

	if(pthread_create(
		 &task0
		,0
		,callback0
		,(void*)0xAFFE
	)){
		;
	}

	if(pthread_create(
	   &task1
	  ,0
	  ,callback1
	  ,(void*)0xCFFE
	)){
		;
	}

	zrtos_task_scheduler__start();
}

