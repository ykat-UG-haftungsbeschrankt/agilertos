Documentation
============

AgileRTOS can probably be a RTOS but mostly it is just a RAM saving malloc and pthread implementation for microcontroller without memory management unit.

 🔗 [Documentation](http://agilertos.com)

 🔗 [Repository](https://github.com/ykat-UG-haftungsbeschrankt/agilertos)

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
#include "zrtos_malloc.h"

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

#include "zrtos_event_index.h"
#include "zrtos_debug.h"

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

### pthread ###
```C
```

### Supported Chips and Boards ###

  * None