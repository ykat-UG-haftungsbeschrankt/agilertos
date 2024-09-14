#include <avr/io.h>

#include <stdint.h>
#include <stddef.h>

#define ZRTOS_ARCH__ATMEGA328P
#define ZRTOS_BOARD__AVR_SOFTWARE_EMULATOR

#include <zrtos/error.h>
#include <zrtos/types.h>
#include <zrtos/malloc.h>
#include <zrtos/str.h>

ZRTOS_MALLOC__GLOBAL_HEAP(heap,500);

#include <zrtos/cbuffer.h>

typedef enum{
	ZRTOS_VFS_MODULE_MAX7219_OPCODE__NOOP         = 0
	,ZRTOS_VFS_MODULE_MAX7219_OPCODE__DIGIT_0      = 1
	,ZRTOS_VFS_MODULE_MAX7219_OPCODE__DIGIT_1      = 2
	,ZRTOS_VFS_MODULE_MAX7219_OPCODE__DIGIT_2      = 3
	,ZRTOS_VFS_MODULE_MAX7219_OPCODE__DIGIT_3      = 4
	,ZRTOS_VFS_MODULE_MAX7219_OPCODE__DIGIT_4      = 5
	,ZRTOS_VFS_MODULE_MAX7219_OPCODE__DIGIT_5      = 6
	,ZRTOS_VFS_MODULE_MAX7219_OPCODE__DIGIT_6      = 7
	,ZRTOS_VFS_MODULE_MAX7219_OPCODE__DIGIT_7      = 8
	,ZRTOS_VFS_MODULE_MAX7219_OPCODE__DECODE_MODE  = 9
	,ZRTOS_VFS_MODULE_MAX7219_OPCODE__INTENSITY    = 10
	,ZRTOS_VFS_MODULE_MAX7219_OPCODE__SCAN_LIMIT   = 11
	,ZRTOS_VFS_MODULE_MAX7219_OPCODE__SHUTDOWN     = 12
	,ZRTOS_VFS_MODULE_MAX7219_OPCODE__DISPLAY_TEST = 15
}zrtos_vfs_module_max7219_opcode_t;

int main(void){
	ZRTOS_MALLOC__GLOBAL_HEAP_INIT(heap);

	char data_in[20] = "1234\n";
	char data_out[20] = "1234\n";
	zrtos_error_t err;
	zrtos_cbuffer_t buffer;
	size_t outlen;
	zrtos_cbuffer__init(&buffer);
	size_t len;
	size_t free_space;

	while(1){
	size_t l = 16;
	while(l--){
		err = zrtos_cbuffer__put_ex(
			 &buffer
			,1
			,&outlen
			,data_in
			,1//zrtos_str__len(data_in)
		);
		zrtos_cbuffer_node_t *node = zrtos_cbuffer__get_last_node(&buffer);
		len = zrtos_cbuffer_node__get_length(node);
		free_space = zrtos_cbuffer_node__get_free_space(node);
		continue;
	}
	l = 16;
	while(l--){
		err = zrtos_cbuffer__get_ex(
			 &buffer
			,data_out
			,1//zrtos_str__len(data_out)
			,&outlen
		);
		zrtos_cbuffer_node_t *node = zrtos_cbuffer__get_first_node(&buffer);
		len = zrtos_cbuffer_node__get_length(node);
		free_space = zrtos_cbuffer_node__get_free_space(node);
		continue;
	}
err = err;
len = len;
free_space = free_space;
	}
/*
		
		if(zrtos_str__cmp(data_in,data_out) != 0){
			break;
		}
*/

	return 0;

}

