#include <avr/io.h>

#define ZRTOS_ARCH__ATMEGA328P
#define ZRTOS_BOARD__AVR_SOFTWARE_EMULATOR

#include "zrtos_vm.h"

zrtos_error_t callback0(
	 struct _zrtos_vm_t          *vm
	,struct _zrtos_vm_function_t *fn
){
	static uint64_t a = 0;
	a++;
	return EXIT_SUCCESS;
}

zrtos_error_t callback1(
	 struct _zrtos_vm_t          *vm
	,struct _zrtos_vm_function_t *fn
){
	static uint64_t a = 0;
	a++;
	return EXIT_SUCCESS;
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

		,ZRTOS_VM_IO_TYPE__UINT8
		|ZRTOS_VM_IO_SOURCE__A_PROGRAM
		|ZRTOS_VM_IO_SOURCE__B_NONE
		,ZRTOS_VM_OP__ICALL
		,0x00


		,ZRTOS_VM_IO_TYPE__UINT8
		|ZRTOS_VM_IO_SOURCE__A_PROGRAM
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

