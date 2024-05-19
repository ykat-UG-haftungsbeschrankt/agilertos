#include <avr/io.h>


typedef uint16_t size_t;
typedef int16_t ssize_t;
typedef enum{
	false
	,true
}bool;

#define ZRTOS_ARCH__BYTE_ALIGNMENT 1
#define ZRTOS_DEBUG__CFG_ENABLED
#define ZRTOS_ARCH__ATMEGA328P

#include "zrtos.h"
#include "zrtos_vheap.h"

void _zrtos_task_scheduler__on_tick(void){
}


ZRTOS_VHEAP__INIT(heap,160);

int main(void){
	zrtos_vheap_t mem;
	
	zrtos_vheap__init(
		 &mem
		,ZRTOS_VHEAP__GET(heap)
		,160
	);

	zrtos_vheap_chunk_uid_t chunka = zrtos_vheap__malloc(&mem,ZRTOS_VHEAP_CHUNK_TYPE__MALLOC,16);
	zrtos_vheap_chunk_uid_t chunkb = zrtos_vheap__malloc(&mem,ZRTOS_VHEAP_CHUNK_TYPE__MALLOC,16);
	zrtos_vheap_chunk_uid_t chunkc = zrtos_vheap__malloc(&mem,ZRTOS_VHEAP_CHUNK_TYPE__MALLOC,16);
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

	zrtos_vheap__page_in(
		 &mem
		,chunkbb
	);

	zrtos_vheap_chunk_uid_t chunke = zrtos_vheap__malloc(&mem,ZRTOS_VHEAP_CHUNK_TYPE__MALLOC,16);

	zrtos_vheap_chunk_t *chunkee = zrtos_vheap__get_by_id(
		 &mem
		,chunke
	);

	zrtos_vheap__page_out(
		 &mem
		,chunkbb
		,16
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

	chunkee = zrtos_vheap__get_by_id(
		 &mem
		,chunke
	);

	zrtos_vheap__page_in(
		 &mem
		,chunkee
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

	chunkee = zrtos_vheap__get_by_id(
		 &mem
		,chunke
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
	//zrtos_vheap__free(&mem,chunke);

	return 0;
}
