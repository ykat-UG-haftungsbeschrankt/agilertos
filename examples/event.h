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
