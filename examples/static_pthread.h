#include <avr/io.h>


#define ZRTOS_ARCH__ATMEGA328P
#define ZRTOS_BOARD__AVR_SOFTWARE_EMULATOR

//#define ZRTOS_DEBUG__CFG_ENABLED
//#define ZRTOS_DEBUG__CFG_MEMORY_CONSOLE 160

#include "zrtos_task_pthread.h"

pthread_attr_t attr;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *callback_aa(void *args){
	return (void*)0xA0A1;
}

void *callback_a(void *args){
	pthread_t thread_aa;
	void      *retval;

	pthread_create(
		 &thread_aa
		,0
		,callback_aa
		,(void*)0xAAAA
	);

	pthread_join(thread_aa,&retval);

	return (void*)0xA0A1;
}

void *callback_bb(void *args){
	pthread_mutex_unlock(&mutex);
	while(1){
	}
	return (void*)0xA0A1;
}

void *callback_b(void *args){
	pthread_t thread_bb;

	pthread_create(
		 &thread_bb
		,0
		,callback_bb
		,(void*)0xAAAA
	);

	pthread_mutex_lock(&mutex);
	pthread_mutex_lock(&mutex);

	return (void*)0xB0B1;
}

void *callback_c(void *args){
	return (void*)0xC0C1;
}

int main(void){
	pthread_t thread_a;
	pthread_t thread_b;
	pthread_t thread_c;
	void      *retval;

	ZRTOS_MALLOC__INIT(heap,ZRTOS_MALLOC__GET_REQUIRED_SIZE(zrtos_arch_stack_t,160*3));

	zrtos_task_scheduler__init();
	
	zrtos_task_pthread__set_heap(heap);

	if(pthread_attr_init(&attr)==0){
		pthread_attr_setstacksize(&attr,159);
		
		pthread_create(
			 &thread_a
			,&attr
			,callback_a
			,(void*)0xAAAA
		);

		pthread_create(
			 &thread_b
			,&attr
			,callback_b
			,(void*)0xAAAA
		);

		pthread_create(
			 &thread_c
			,&attr
			,callback_c
			,(void*)0xAAAA
		);

		pthread_join(thread_a,&retval);
		pthread_join(thread_b,&retval);
		pthread_join(thread_c,&retval);

		pthread_attr_destroy(&attr);
	}
}

