[![GitHub release (latest by date)](https://img.shields.io/github/v/release/ykat-UG-haftungsbeschrankt/agilertos)](https://github.com/ykat-UG-haftungsbeschrankt/agilertos)

<!--
[![GitHub](https://img.shields.io/github/license/jothepro/doxygen-awesome-css)](https://github.com/jothepro/doxygen-awesome-css/blob/main/LICENSE)
![GitHub Repo stars](https://img.shields.io/github/stars/jothepro/doxygen-awesome-css)
-->



Documentation
============

AgileRTOS can probably be a RTOS but mostly it is just a RAM saving malloc and pthread implementation for microcontroller without memory management unit.

🔗 <img src=https://doxygen.nl/favicon.ico width=16 height=16> [Documentation](http://agilertos.com)

🔗 <img src=https://github.com/favicon.ico width=16 height=16> [Repository](https://github.com/ykat-UG-haftungsbeschrankt/agilertos)

Examples
------------

### malloc() / free() ###

[Implementation details](http://agilertos.com/zrtos__malloc_8h.html)

```C
#include <avr/io.h>

/**
 * If malloc and new is only used on boot without releasing the memory, code and
 * ram usage can be further reduced by '#define ZRTOS_MALLOC__CFG_DISABLE_FREE'.
 */
//#define ZRTOS_MALLOC__CFG_DISABLE_FREE
#include <zrtos/malloc.h>

// global heap for malloc()/free()
ZRTOS_MALLOC__GLOBAL_HEAP(heap,ZRTOS_MALLOC__GET_REQUIRED_SIZE(char,160));

int main(void){
	ZRTOS_MALLOC__GLOBAL_HEAP_INIT(heap);

	// separate heap usable with zrtos_malloc__malloc()/zrtos_malloc__free()
	ZRTOS_MALLOC__INIT(heap2,ZRTOS_MALLOC__GET_REQUIRED_SIZE(char,160));

	// separate heap usable with zrtos_malloc__malloc()/zrtos_malloc__free()
	ZRTOS_MALLOC__INIT(heap3,ZRTOS_MALLOC__GET_REQUIRED_SIZE(char,160));

	size_t length = 10,l;
	void *ptr[10];

	for(l=0;l<=length;l++){
		ptr[l] = malloc(16);
	}
	for(l=0;l<=length;l++){
		free(ptr[l]);
	}
	for(l=0;l<=length;l++){
		ptr[l] = malloc(16);
	}
	for(l=0;l<=length;l++){
		free(ptr[l]);
	}

	for(l=0;l<=length;l++){
		ptr[l] = zrtos_malloc__malloc(heap2,16);
	}
	for(l=0;l<=length;l++){
		zrtos_malloc__free(ptr[l]);
	}
	for(l=0;l<=length;l++){
		ptr[l] = zrtos_malloc__malloc(heap3,16);
	}
	for(l=0;l<=length;l++){
		zrtos_malloc__free(ptr[l]);
	}

	return 0;
}
```

### vheap ###

```C
#include <avr/io.h>

#include <zrtos/vheap.h>

ZRTOS_VHEAP__INIT(heap,160);

int main(void){
	zrtos_vheap_t mem;
	
	zrtos_vheap__init(
		 &mem
		,ZRTOS_VHEAP__GET(heap)
		,160
	);

	zrtos_vheap_chunk_uid_t chunka = zrtos_vheap__malloc(&mem,zrtos_vheap_chunk_uid__error(),ZRTOS_VHEAP_TYPE__MALLOC,16);
	zrtos_vheap_chunk_uid_t chunkb = zrtos_vheap__malloc(&mem,zrtos_vheap_chunk_uid__error(),ZRTOS_VHEAP_TYPE__MALLOC,16);
	zrtos_vheap_chunk_uid_t chunkc = zrtos_vheap__malloc(&mem,zrtos_vheap_chunk_uid__error(),ZRTOS_VHEAP_TYPE__MALLOC,16);
	zrtos_vheap_chunk_t *chunkaa = zrtos_vheap__get_by_id(
		 &mem
		,chunka
	);
	zrtos_vheap_chunk_t *chunkbb = zrtos_vheap__get_by_id(
		 &mem
		,chunkb
	);
	zrtos_vheap_chunk_t *chunkcc = zrtos_vheap__get_by_id(
		 &mem
		,chunkc
	);

	zrtos_vheap_chunk_uid_t chunkd = zrtos_vheap__malloc(&mem,zrtos_vheap_chunk_uid__error(),ZRTOS_VHEAP_TYPE__MALLOC,16);

	zrtos_vheap_chunk_t *chunkdd = zrtos_vheap__get_by_id(
		 &mem
		,chunkd
	);

	chunkaa = zrtos_vheap__get_by_id(
		 &mem
		,chunka
	);
	chunkbb = zrtos_vheap__get_by_id(
		 &mem
		,chunkb
	);
	chunkcc = zrtos_vheap__get_by_id(
		 &mem
		,chunkc
	);

	chunkdd = zrtos_vheap__get_by_id(
		 &mem
		,chunkd
	);

	zrtos_vheap__free(&mem,chunkb);

	chunkaa = zrtos_vheap__get_by_id(
		 &mem
		,chunka
	);
	chunkcc = zrtos_vheap__get_by_id(
		 &mem
		,chunkc
	);

	zrtos_vheap__free(&mem,chunka);

	chunkcc = zrtos_vheap__get_by_id(
		 &mem
		,chunkc
	);

	zrtos_vheap__free(&mem,chunkc);

	return 0;
}
```

### events ###

[Implementation details](http://agilertos.com/zrtos__event_8h.html)

```C
#include <avr/io.h>

#define ZRTOS_DEBUG__CFG_ENABLED
#define ZRTOS_DEBUG__CFG_MEMORY_CONSOLE 400

typedef enum{
	 ZRTOS_EVENT_TYPE__ANY = 0
	,EVENT_CODE_A
	,EVENT_CODE_B
}zrtos_event_type_t;

#include <zrtos/event_index.h>
#include <zrtos/debug.h>

bool handler_a(
	 zrtos_event_handler_t *thiz
	,zrtos_event_t         *args
){
	ZRTOS_DEBUG(
		 "{fn:%s,ctx:%p,data:%p,type:%d(EVENT_CODE_A)}  "
		,"handler_a"
		,zrtos_event_handler__get_context(thiz)
		,zrtos_event__get_data(args)
		,(int)zrtos_event__get_type(args)
	);
	return true;
}

bool handler_b(
	zrtos_event_handler_t *thiz
	,zrtos_event_t         *args
){
	char *data = zrtos_event__get_data(args);
	ZRTOS_DEBUG(
		 "{fn:%s,ctx:%p,data:'%c',type:%d(EVENT_CODE_B)}  "
		,"handler_b"
		,zrtos_event_handler__get_context(thiz)
		,*data
		,(int)zrtos_event__get_type(args)
	);
	return true;
}

bool handler_bb(
	zrtos_event_handler_t *thiz
	,zrtos_event_t         *args
){
	char *data = zrtos_event__get_data(args);
	ZRTOS_DEBUG(
		 "{fn:%s,ctx:%p,data:'%c',type:%d(EVENT_CODE_B)}  "
		,"handler_bb"
		,zrtos_event_handler__get_context(thiz)
		,*data
		,(int)zrtos_event__get_type(args)
	);
	return true;
}

bool handler_c(
	 zrtos_event_handler_t *thiz
	,zrtos_event_t         *args
){
	void *data = zrtos_event__get_data(args);
	ZRTOS_DEBUG(
		 "{fn:%s,ctx:%p,data:%p,type:%d("
		,"handler_c"
		,zrtos_event_handler__get_context(thiz)
		,data
		,(int)zrtos_event__get_type(args)
	);
	switch(zrtos_event__get_type(args)){
		case EVENT_CODE_A:
			ZRTOS_DEBUG("%s(%p)","EVENT_CODE_A",data);
		break;
		case EVENT_CODE_B:
			ZRTOS_DEBUG("%s(%c)","EVENT_CODE_B",((char*)data)[0]);
		break;
		default:
			ZRTOS_DEBUG("%s(%s)","EVENT_CODE_ANY",(char*)data);
		break;
	}
	ZRTOS_DEBUG(")}  ");
	return true;
}

ZRTOS_EVENT_INDEX(global_events,
	ZRTOS_EVENT_HANDLER(
		 handler_a
		,EVENT_CODE_A
		,0
	)
	,ZRTOS_EVENT_HANDLER(
		handler_b
		,EVENT_CODE_B
		,0
	)
	,ZRTOS_EVENT_HANDLER(
		handler_bb
		,EVENT_CODE_B
		,0
	)
	,ZRTOS_EVENT_HANDLER(
		 handler_c
		,ZRTOS_EVENT_TYPE__ANY
		,(void*)0xFFAA
	)
);

int main(void){
	void *ptr = (void*) 0xFAFA;
	char val = 'Z';

	zrtos_event_index__invoke(
		 global_events
		,ZRTOS_EVENT_TYPE__ANY
		,"test"
	);

	zrtos_event_index__invoke(
		 global_events
		,EVENT_CODE_A
		,ptr
	);

	zrtos_event_index__invoke(
		 global_events
		,EVENT_CODE_B
		,&val
	);


	return 0;
}

```

### static tasks ###
```C
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

	while(true){
		//
	}
}

```

### static pthread ###
```C
#include <avr/io.h>


#define ZRTOS_ARCH__ATMEGA328P
#define ZRTOS_BOARD__AVR_SOFTWARE_EMULATOR

//#define ZRTOS_DEBUG__CFG_ENABLED
//#define ZRTOS_DEBUG__CFG_MEMORY_CONSOLE 160

#include <zrtos/task_pthread.h>

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

```

### VM ###
```C
#include <avr/io.h>

#define ZRTOS_ARCH__ATMEGA328P
#define ZRTOS_BOARD__AVR_SOFTWARE_EMULATOR

#include <zrtos/vm.h>

zrtos_error_t callback0(
	 struct _zrtos_vm_t          *vm
	,struct _zrtos_vm_function_t *fn
){
	static uint64_t a = 0;
	a++;
	return ZRTOS_ERROR__SUCCESS;
}

zrtos_error_t callback1(
	 struct _zrtos_vm_t          *vm
	,struct _zrtos_vm_function_t *fn
){
	static uint64_t a = 0;
	a++;
	return ZRTOS_ERROR__SUCCESS;
}

ZRTOS_VM_FUNCTION_INDEX(vm_functions,
	 ZRTOS_VM_FUNCTION(0,callback0,0)
	,ZRTOS_VM_FUNCTION(1,callback1,0)	
);

int main(void){
	zrtos_stack_t             stack;
	zrtos_stack_t             program;
	zrtos_vm_function_index_t functions;
	zrtos_vm_t                vm;
	uint8_t program_data[] = {
		 ZRTOS_VM_IO_SOURCE__A_NONE
		|ZRTOS_VM_IO_SOURCE__B_NONE
		,ZRTOS_VM_OP__NOP

		,ZRTOS_VM_IO_SOURCE__A_NONE
		|ZRTOS_VM_IO_SOURCE__B_NONE
		,ZRTOS_VM_OP__NOP

		,ZRTOS_VM_IO_SOURCE__A_PROGRAM
		|ZRTOS_VM_IO_TYPE__UINT8
		|ZRTOS_VM_IO_SOURCE__B_NONE
		,ZRTOS_VM_OP__ICALL
		,0x00


		,ZRTOS_VM_IO_SOURCE__A_PROGRAM
		|ZRTOS_VM_IO_TYPE__UINT8
		|ZRTOS_VM_IO_SOURCE__B_NONE
		,ZRTOS_VM_OP__ICALL
		,0x01
	};

	zrtos_stack__init(
		 &stack
		,(void *)0x300
		,100
	);

	zrtos_stack__init(
		 &program
		,program_data
		,ZRTOS_TYPES__GET_STATIC_ARRAY_LENGTH(program_data)
	);

	zrtos_vm_function_index__init(
		 &functions
		,vm_functions
		,ZRTOS_TYPES__GET_STATIC_ARRAY_LENGTH(vm_functions)-1
	);

	zrtos_vm__init(
		 &vm
		,stack
		,program
		,functions
	);

	zrtos_error_t ret = zrtos_vm__run(&vm);
	return ret;
}

```


### VFS ###
```C
#include <avr/io.h>

#include <stdint.h>
#include <stddef.h>

#define ZRTOS_ARCH__ATMEGA328P
#define ZRTOS_BOARD__AVR_SOFTWARE_EMULATOR

//typedef uint8_t max_align_t;


#define ZRTOS_VFS_FILE_DESCRIPTOR__CFG_MAX 10

#include <zrtos/error.h>
#include <zrtos/types.h>

#include <zrtos/vfs_plugin.h>
#include <zrtos/vfs_inode.h>
#include <zrtos/vfs_dentry.h>
#include <zrtos/vfs_file.h>
#include <zrtos/vfs_fd.h>
#include <zrtos/vfs_notify.h>

#include <zrtos/vfs/module/zero/zero.h>
#include <zrtos/vfs/module/null/null.h>
#include <zrtos/vfs/module/random/random.h>
#include <zrtos/vfs/module/arduino/gpio.h>

#define ZRTOS_VFS_MODULE_AVR_ADC__CFG_PRESCALER (ZRTOS_BINARY__00000101)
#define ZRTOS_VFS_MODULE_AVR_ADC__CFG_VREF (ZRTOS_BINARY__01000000)
#define ZRTOS_VFS_MODULE_AVR_ADC__CFG_MAX_CHANNEL (6)
#define ZRTOS_VFS_MODULE_AVR_ADC__CFG_REFERENCE_VOLT (5.0)
#include <zrtos/vfs/module/avr/adc/adc.h>

void setup(void){
	Serial.begin(19200);
}

void on_can_read_zero(
	 zrtos_vfs_notify_t *thiz
	,zrtos_vfs_fd_t fd
){
	size_t outlen;
	uint8_t buffer[1];
	zrtos_vfs_fd__read(fd,0,buffer,1,0,&outlen);
	Serial.print("#ZERO:");
	Serial.print(buffer[0], HEX);
	Serial.print("\n");
}

void on_can_read_random(
	 zrtos_vfs_notify_t *thiz
	,zrtos_vfs_fd_t fd
){
	size_t outlen;
	uint8_t buffer[1];
	zrtos_vfs_fd__read(fd,0,buffer,1,0,&outlen);
	Serial.print("#RANDOM:");
	Serial.print(buffer[0], HEX);
	Serial.print("\n");
}

void on_can_read_adc(
	 zrtos_vfs_notify_t *thiz
	,zrtos_vfs_fd_t fd
){
	size_t outlen;
	float val;
	for(size_t l=0;l<ZRTOS_VFS_MODULE_AVR_ADC__CFG_MAX_CHANNEL;l++){
		Serial.print("#ADC:");
		Serial.print(l, DEC);
		Serial.print(": ");
		zrtos_error_t err = zrtos_vfs_fd__read(
			fd
			,0
			,&val
			,sizeof(val)
			,l*sizeof(val)
			,&outlen
		);
		Serial.print((int)err, DEC);
		Serial.print(":");
		Serial.print(val, DEC);
		Serial.print("\n");
		delay(1000);
	}
}

void loop(void){
	zrtos_vfs_dentry_t dev;
	zrtos_vfs_dentry_t dev_zero;
	zrtos_vfs_dentry_t dev_null;
	zrtos_vfs_dentry_t dev_random;
	zrtos_vfs_dentry_t dev_gpiochip0;
	zrtos_vfs_dentry_t dev_adc;

	zrtos_vfs_dentry__init(
		 &dev
		,(char*)"dev"
		,0
	);

	zrtos_vfs_dentry__init(
		 &dev_zero
		,(char*)"zero"
		,&dev
	);

	zrtos_vfs_dentry__init(
		 &dev_null
		,(char*)"null"
		,&dev
	);

	zrtos_vfs_dentry__init(
		 &dev_random
		,(char*)"random"
		,&dev
	);

	zrtos_vfs_dentry__init(
		 &dev_gpiochip0
		,(char*)"gpiochip0"
		,&dev
	);

	zrtos_vfs_dentry__init(
		 &dev_adc
		,(char*)"adc"
		,&dev
	);

	zrtos_vfs_dentry__mount(
		 &dev_zero
		,ZRTOS_VFS_PLUGIN(zero)
		,0
	);

	zrtos_vfs_dentry__mount(
		 &dev_random
		,ZRTOS_VFS_PLUGIN(random)
		,0
	);

	zrtos_vfs_dentry__mount(
		 &dev_gpiochip0
		,ZRTOS_VFS_PLUGIN(arduino_gpio)
		,0
	);

	zrtos_vfs_dentry__mount(
		 &dev_adc
		,ZRTOS_VFS_PLUGIN(avr_adc)
		,0
	);

	zrtos_vfs_fd_t fd_zero;
	zrtos_vfs_fd_t fd_random;
	zrtos_vfs_fd_t fd_adc;

	zrtos_vfs_notify_t notify;
	zrtos_vfs_notify__init(
		&notify
	);

	zrtos_vfs_fd__open((char*)"/dev/zero",&fd_zero);
	zrtos_vfs_fd__open((char*)"/dev/random",&fd_random);
	zrtos_vfs_fd__open((char*)"/dev/adc",&fd_adc);

	zrtos_vfs_notify__add(&notify,fd_zero,on_can_read_zero,0);
	zrtos_vfs_notify__add(&notify,fd_random,on_can_read_random,0);
	zrtos_vfs_notify__add(&notify,fd_adc,on_can_read_adc,0);
	zrtos_vfs_notify__start(
		&notify
	);
}

```


### Supported Chips and Boards ###

  * None