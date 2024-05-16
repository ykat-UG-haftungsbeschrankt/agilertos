#include <avr/io.h>


typedef uint16_t size_t;
typedef int16_t ssize_t;
typedef enum{
	false
	,true
}bool;

#define ZRTOS_CPU__ATMEGA328P
#define ZRTOS_DEBUG__ENABLED

#include "zrtos.h"
#include "zrtos_task_scheduler.h"

unsigned a = 0;
unsigned b = 0;

void callback0(void *args){
	while(1){
		a++;
	}
}
void callback1(void *args){
	while(1){
		b++;
	}
}

int main(void){
	zrtos_task_t task0;
	zrtos_task_t task1;

	if(zrtos_task__init(
	   &task0
	  ,(void*)0x600
	  ,16*7
	  ,callback0
	  ,(void*)0xAFFE
	)){
		zrtos_task_scheduler__add_task(&task0);
	}

	if(zrtos_task__init(
	   &task1
	  ,(void*)0x700
	  ,16*7
	  ,callback1
	  ,(void*)0xCFFE
	)){
		zrtos_task_scheduler__add_task(&task1);
	}

	zrtos_task_scheduler__init();
}

