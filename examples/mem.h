#include <avr/io.h>


typedef uint16_t size_t;
typedef int16_t ssize_t;
typedef enum{
	false
	,true
}bool;

#define ZRTOS__BYTE_ALIGNMENT 1
#define ZRTOS_DEBUG__CFG_ENABLED
#define ZRTOS_CPU__ATMEGA328P

#include "zrtos.h"
#include "zrtos_mem.h"

void _zrtos_task_scheduler__on_tick(void){
}


ZRTOS_MEM__INIT(heap,160);

int main(void){
	zrtos_mem_t mem;
	
	zrtos_mem__init(
		 &mem
		,ZRTOS_MEM__GET(heap)
		,160
	);

	zrtos_mem_chunk_uid_t chunka = zrtos_mem__malloc(&mem,ZRTOS_MEM_CHUNK_TYPE__MALLOC,16);
	zrtos_mem_chunk_uid_t chunkb = zrtos_mem__malloc(&mem,ZRTOS_MEM_CHUNK_TYPE__MALLOC,16);
	zrtos_mem_chunk_uid_t chunkc = zrtos_mem__malloc(&mem,ZRTOS_MEM_CHUNK_TYPE__MALLOC,16);
	zrtos_mem_chunk_t *chunkaa = zrtos_mem__get_by_id(
	&mem
	,chunka
	);
	zrtos_mem_chunk_t *chunkbb = zrtos_mem__get_by_id(
	&mem
	,chunkb
	);
	zrtos_mem_chunk_t *chunkcc = zrtos_mem__get_by_id(
	&mem
	,chunkc
	);

	zrtos_mem__page_in(
		 &mem
		,chunkbb
	);

	zrtos_mem_chunk_uid_t chunke = zrtos_mem__malloc(&mem,ZRTOS_MEM_CHUNK_TYPE__MALLOC,16);

	zrtos_mem_chunk_t *chunkee = zrtos_mem__get_by_id(
		 &mem
		,chunke
	);

	zrtos_mem__page_out(
		 &mem
		,chunkbb
		,16
	);

	chunkaa = zrtos_mem__get_by_id(
		 &mem
		,chunka
	);
	chunkbb = zrtos_mem__get_by_id(
		 &mem
		,chunkb
	);
	chunkcc = zrtos_mem__get_by_id(
		 &mem
		,chunkc
	);

	chunkee = zrtos_mem__get_by_id(
		 &mem
		,chunke
	);

	zrtos_mem__page_in(
		 &mem
		,chunkee
	);

	chunkaa = zrtos_mem__get_by_id(
		 &mem
		,chunka
	);
	chunkbb = zrtos_mem__get_by_id(
		 &mem
		,chunkb
	);
	chunkcc = zrtos_mem__get_by_id(
		 &mem
		,chunkc
	);

	chunkee = zrtos_mem__get_by_id(
		 &mem
		,chunke
	);

	zrtos_mem__free(&mem,chunkb);
	chunkaa = zrtos_mem__get_by_id(
		 &mem
		,chunka
	);
	chunkcc = zrtos_mem__get_by_id(
		 &mem
		,chunkc
	);
	zrtos_mem__free(&mem,chunka);
	chunkcc = zrtos_mem__get_by_id(
		 &mem
		,chunkc
	);
	zrtos_mem__free(&mem,chunkc);
	//zrtos_mem__free(&mem,chunke);

	return 0;
}
