#include <avr/io.h>

#include "zrtos_vheap.h"

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
