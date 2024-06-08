/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VM_IO_H
#define ZRTOS_VM_IO_H
#ifdef __cplusplus
extern "C" {
#endif


#include <zrtos/types.h>

 
typedef enum{
	 ZRTOS_VM_IO_SOURCE__A_NONE          = 0x00
	,ZRTOS_VM_IO_SOURCE__A_STACK         = 0x10
	,ZRTOS_VM_IO_SOURCE__A_PROGRAM       = 0x20
	,ZRTOS_VM_IO_SOURCE__A_ADDRESS       = 0x30
	,ZRTOS_VM_IO_SOURCE__B_NONE          = (0x00 << 2)
	,ZRTOS_VM_IO_SOURCE__B_STACK         = (0x10 << 2)
	,ZRTOS_VM_IO_SOURCE__B_PROGRAM       = (0x20 << 2)
	,ZRTOS_VM_IO_SOURCE__B_ADDRESS       = (0x30 << 2)
	,ZRTOS_VM_IO_SOURCE__MASK            = 0xF0
}zrtos_vm_io_source_t;

typedef enum{
	 ZRTOS_VM_IO_TYPE__UINT8    = 0x00
	,ZRTOS_VM_IO_TYPE__UINT16   = 0x01
	,ZRTOS_VM_IO_TYPE__UINT32   = 0x03
	,ZRTOS_VM_IO_TYPE__UINT64   = 0x07

	,ZRTOS_VM_IO_TYPE__INT8   = 0x08
	,ZRTOS_VM_IO_TYPE__INT16  = 0x09
	,ZRTOS_VM_IO_TYPE__INT32  = 0x0B

	,ZRTOS_VM_IO_TYPE__FLOAT   = 0x0D
	,ZRTOS_VM_IO_TYPE__DOUBLE  = 0x0E

	,ZRTOS_VM_IO_TYPE__INT64  = 0x0F

	,ZRTOS_VM_IO_TYPE__MASK    = 0x0F
}zrtos_vm_io_type_t;

bool zrtos_vm_io_type__is_uint(zrtos_vm_io_type_t type){
	return type >= ZRTOS_VM_IO_TYPE__UINT8
	    && type <= ZRTOS_VM_IO_TYPE__UINT64
	;
}

bool zrtos_vm_io_type__is_int(zrtos_vm_io_type_t type){
	return (type >= ZRTOS_VM_IO_TYPE__INT8
	    &&  type <= ZRTOS_VM_IO_TYPE__INT32
		)|| type == ZRTOS_VM_IO_TYPE__INT64
	;
}

bool zrtos_vm_io_type__is_float(zrtos_vm_io_type_t type){
	return type == ZRTOS_VM_IO_TYPE__FLOAT;
}

bool zrtos_vm_io_type__is_double(zrtos_vm_io_type_t type){
	return type == ZRTOS_VM_IO_TYPE__DOUBLE;
}

size_t zrtos_vm_io_type__get_length(zrtos_vm_io_type_t type){
	size_t length = type;
	length += 1;
	if(type == ZRTOS_VM_IO_TYPE__FLOAT){
		length = 4;
	}else if(type == ZRTOS_VM_IO_TYPE__DOUBLE){
		length = 8;
	}
	return length;
}

typedef enum{
	 ZRTOS_VM_IO_ADDRESS_TYPE__MIN                   = 0x00
	,ZRTOS_VM_IO_ADDRESS_TYPE__DISPLACEMENT_ABSOLUTE = 0x00
	,ZRTOS_VM_IO_ADDRESS_TYPE__DISPLACEMENT_RELATIVE = 0x10
	,ZRTOS_VM_IO_ADDRESS_TYPE__DISPLACEMENT_MASK     = 0x10

	,ZRTOS_VM_IO_ADDRESS_TYPE__IS_NEGATIVE           = 0x80

	,ZRTOS_VM_IO_ADDRESS_TYPE__SOURCE_PROGRAM        = 0x20
	,ZRTOS_VM_IO_ADDRESS_TYPE__SOURCE_STACK          = 0x40
	,ZRTOS_VM_IO_ADDRESS_TYPE__SOURCE_MASK           = 0x60

	,ZRTOS_VM_IO_ADDRESS_TYPE__LENGTH_1              = 0x01
	,ZRTOS_VM_IO_ADDRESS_TYPE__LENGTH_2              = 0x02
	,ZRTOS_VM_IO_ADDRESS_TYPE__LENGTH_4              = 0x04
	,ZRTOS_VM_IO_ADDRESS_TYPE__LENGTH_8              = 0x08
	,ZRTOS_VM_IO_ADDRESS_TYPE__LENGTH_MASK           = 0x0F
	,ZRTOS_VM_IO_ADDRESS_TYPE__MAX                   = 0xFF
}zrtos_vm_io_address_type_t;

typedef struct _zrtos_vm_io_source_address_t{
	size_t                      address;
	zrtos_vm_io_address_type_t  type;
}zrtos_vm_io_address_t;



size_t zrtos_vm_io_address__get_address(zrtos_vm_io_address_t *thiz){
	return thiz->address;
}

bool zrtos_vm_io_address__is_negative(zrtos_vm_io_address_t *thiz){
	return (thiz->type & ZRTOS_VM_IO_ADDRESS_TYPE__IS_NEGATIVE) > 0;
}

bool zrtos_vm_io_address__is_relative(zrtos_vm_io_address_t *thiz){
	return (thiz->type & ZRTOS_VM_IO_ADDRESS_TYPE__DISPLACEMENT_RELATIVE) > 0;
}

size_t zrtos_vm_io_address__get_length(zrtos_vm_io_address_t *thiz){
	return thiz->type & ZRTOS_VM_IO_ADDRESS_TYPE__LENGTH_MASK;
}

bool zrtos_vm_io_address__is_source_program(zrtos_vm_io_address_t *thiz){
	return (thiz->type & ZRTOS_VM_IO_ADDRESS_TYPE__SOURCE_PROGRAM) > 0;
}


#ifdef __cplusplus
}
#endif
#endif