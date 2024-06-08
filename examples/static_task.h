#include <avr/io.h>


#define ZRTOS_ARCH__ATMEGA328P
#define ZRTOS_BOARD__AVR_SOFTWARE_EMULATOR

//#define ZRTOS_DEBUG__CFG_ENABLED
//#define ZRTOS_DEBUG__CFG_MEMORY_CONSOLE 160

#include <zrtos/task_scheduler.h>

__attribute__((noreturn)) void callback_a(void *args){
	static size_t a = 0;
	while(true){
		a++;
		zrtos_task_scheduler__delay_ms(0);
	}
	__builtin_unreachable();
}

__attribute__((noreturn)) void callback_b(void *args){
	static size_t b = 0;
	while(true){
		b++;
		zrtos_task_scheduler__delay_ms(0);
	}
	__builtin_unreachable();
}

__attribute__((noreturn)) void callback_c(void *args){
	static size_t c = 0;
	while(true){
		c++;
		zrtos_task_scheduler__delay_ms(0);
	}
	__builtin_unreachable();
}

int main(void){
	zrtos_arch_stack_t heap_a[160];
	zrtos_arch_stack_t heap_b[160];
	zrtos_arch_stack_t heap_c[160];
	zrtos_task_t task_a;
	zrtos_task_t task_b;
	zrtos_task_t task_c;

	zrtos_task_scheduler__init();

	zrtos_task__init_ex(
		 &task_a
		,heap_a+159
		,callback_a
		,(void*)0xAAAA
	);
	zrtos_task_scheduler__add_task(&task_a);

	zrtos_task__init_ex(
		 &task_b
		,heap_b+159
		,callback_b
		,(void*)0xAAAA
	);
	zrtos_task_scheduler__add_task(&task_b);

	zrtos_task__init_ex(
		 &task_c
		,heap_c+159
		,callback_c
		,(void*)0xAAAA
	);
	zrtos_task_scheduler__add_task(&task_c);

	zrtos_task_scheduler__start();
}

