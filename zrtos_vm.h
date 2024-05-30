/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_VM_H
#define ZRTOS_VM_H
#ifdef __cplusplus
extern "C" {
#endif


#include "zrtos_types.h"
#include "zrtos_error.h"
#include "zrtos_stack.h"
#include "zrtos_mem.h"


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
	 ZRTOS_VM_IO_TYPE__INT8    = 0x00
	,ZRTOS_VM_IO_TYPE__INT16   = 0x01
	,ZRTOS_VM_IO_TYPE__INT32   = 0x03
	,ZRTOS_VM_IO_TYPE__INT64   = 0x07

	,ZRTOS_VM_IO_TYPE__UINT8   = 0x08
	,ZRTOS_VM_IO_TYPE__UINT16  = 0x09
	,ZRTOS_VM_IO_TYPE__UINT32  = 0x0B

	,ZRTOS_VM_IO_TYPE__FLOAT   = 0x0D
	,ZRTOS_VM_IO_TYPE__DOUBLE  = 0x0E

	,ZRTOS_VM_IO_TYPE__UINT64  = 0x0F

	,ZRTOS_VM_IO_TYPE__MASK    = 0x0F
}zrtos_vm_io_type_t;

bool zrtos_vm_io_type__is_int(zrtos_vm_io_type_t type){
	return type >= ZRTOS_VM_IO_TYPE__INT8
	    && type <= ZRTOS_VM_IO_TYPE__INT32
	;
}

bool zrtos_vm_io_type__is_uint(zrtos_vm_io_type_t type){
	return (type >= ZRTOS_VM_IO_TYPE__UINT8
	    &&  type <= ZRTOS_VM_IO_TYPE__UINT32
		)|| type == ZRTOS_VM_IO_TYPE__UINT64
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
	 ZRTOS_VM_OP__MIN          = 0x00

	,ZRTOS_VM_OP__CAST         = 0x00
	,ZRTOS_VM_OP__CAST_MIN     = 0x00
	,ZRTOS_VM_OP__CAST_INT8    = 0x00
	,ZRTOS_VM_OP__CAST_INT16   = 0x01
	,ZRTOS_VM_OP__CAST_INT32   = 0x03
	,ZRTOS_VM_OP__CAST_INT64   = 0x07
	,ZRTOS_VM_OP__CAST_UINT8   = 0x08
	,ZRTOS_VM_OP__CAST_UINT16  = 0x09
	,ZRTOS_VM_OP__CAST_UINT32  = 0x0B
	,ZRTOS_VM_OP__CAST_FLOAT   = 0x0D
	,ZRTOS_VM_OP__CAST_DOUBLE  = 0x0E
	,ZRTOS_VM_OP__CAST_UINT64  = 0x0F
	,ZRTOS_VM_OP__CAST_MAX     = 0x0F

	,ZRTOS_VM_OP__PUSH         = 0x10
	,ZRTOS_VM_OP__POP          = 0x11

	,ZRTOS_VM_OP__AND          = 0x12
	,ZRTOS_VM_OP__OR           = 0x13
	,ZRTOS_VM_OP__XOR          = 0x14
	,ZRTOS_VM_OP__NEG          = 0x15

	,ZRTOS_VM_OP__ADD          = 0x16
	,ZRTOS_VM_OP__SUB          = 0x17
	,ZRTOS_VM_OP__MUL          = 0x18
	,ZRTOS_VM_OP__DIV          = 0x19
	,ZRTOS_VM_OP__MOD          = 0x1A

	,ZRTOS_VM_OP__NOT          = 0x1B
	,ZRTOS_VM_OP__EQ           = 0x1C
	,ZRTOS_VM_OP__LT           = 0x1D
	,ZRTOS_VM_OP__GT           = 0x1E
	,ZRTOS_VM_OP__LE           = 0x1F
	,ZRTOS_VM_OP__GE           = 0x20

	,ZRTOS_VM_OP__IF           = 0x21

	,ZRTOS_VM_OP__ICALL        = 0x22
	,ZRTOS_VM_OP__CALL         = 0x23
	,ZRTOS_VM_OP__RET          = 0x24

	,ZRTOS_VM_OP__NOP          = 0x25

	,ZRTOS_VM_OP__MAX          = 0xFF
}zrtos_vm_op_t;

typedef struct{
	uint8_t io;
	uint8_t op;
}zrtos_vm_ioop_t;

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

typedef struct _zrtos_vm_t{
	zrtos_stack_t             stack;
	zrtos_stack_t             program;
	zrtos_vm_function_index_t functions;
	bool                      is_interrupted;
}zrtos_vm_t;

typedef struct _zrtos_vm_value_t{
	union{
		uint8_t  u8;
		uint16_t u16;
		uint32_t u32;
		uint64_t u64;

		int8_t   s8;
		int16_t  s16;
		int32_t  s32;
		int64_t  s64;

		float    f4;
		double   f8;
	}value;
	zrtos_vm_io_type_t             type;
	zrtos_vm_io_address_t          address;
}zrtos_vm_value_t;

#define ZRTOS_VM_OP_CAST(target,op)\
		case ZRTOS_VM_IO_TYPE__INT8:\
			a.value.target = op b.value.s8;\
		break;\
		case ZRTOS_VM_IO_TYPE__INT16:\
			a.value.target = op b.value.s16;\
		break;\
		case ZRTOS_VM_IO_TYPE__INT32:\
			a.value.target = op b.value.s32;\
		break;\
		case ZRTOS_VM_IO_TYPE__INT64:\
			a.value.target = op b.value.s64;\
		break;\
		case ZRTOS_VM_IO_TYPE__UINT8:\
			a.value.target = op b.value.u8;\
		break;\
		case ZRTOS_VM_IO_TYPE__UINT16:\
			a.value.target = op b.value.u16;\
		break;\
		case ZRTOS_VM_IO_TYPE__UINT32:\
			a.value.target = op b.value.u32;\
		break;\
		case ZRTOS_VM_IO_TYPE__UINT64:\
			a.value.target = op b.value.u64;\
		break;

#define ZRTOS_VM_OP_WITHOUT_FLOAT(op)\
		case ZRTOS_VM_IO_TYPE__INT8:\
			a.value.s8 = a.value.s8 op b.value.s8;\
		break;\
		case ZRTOS_VM_IO_TYPE__INT16:\
			a.value.s16 = a.value.s16 op b.value.s16;\
		break;\
		case ZRTOS_VM_IO_TYPE__INT32:\
			a.value.s32 = a.value.s32 op b.value.s32;\
		break;\
		case ZRTOS_VM_IO_TYPE__INT64:\
			a.value.s64 = a.value.s64 op b.value.s64;\
		break;\
		case ZRTOS_VM_IO_TYPE__UINT8:\
			a.value.u8 = a.value.u8 op b.value.u8;\
		break;\
		case ZRTOS_VM_IO_TYPE__UINT16:\
			a.value.u16 = a.value.u16 op b.value.u16;\
		break;\
		case ZRTOS_VM_IO_TYPE__UINT32:\
			a.value.u32 = a.value.u32 op b.value.u32;\
		break;\
		case ZRTOS_VM_IO_TYPE__UINT64:\
			a.value.u64 = a.value.u64 op b.value.u64;\
		break;

#define ZRTOS_VM_OP(op)\
		ZRTOS_VM_OP_WITHOUT_FLOAT(op)\
		case ZRTOS_VM_IO_TYPE__FLOAT:\
			a.value.f4 = a.value.f4 op b.value.f4;\
		break;\
		case ZRTOS_VM_IO_TYPE__DOUBLE:\
			a.value.f8 = a.value.f8 op b.value.f8;\
		break;

#define ZRTOS_VM_OP_NOT(op)\
		case ZRTOS_VM_IO_TYPE__INT8:\
			a.value.s8 = op a.value.s8;\
		break;\
		case ZRTOS_VM_IO_TYPE__INT16:\
			a.value.s16 = op a.value.s16;\
		break;\
		case ZRTOS_VM_IO_TYPE__INT32:\
			a.value.s32 = op a.value.s32;\
		break;\
		case ZRTOS_VM_IO_TYPE__INT64:\
			a.value.s64 = op a.value.s64;\
		break;\
		case ZRTOS_VM_IO_TYPE__UINT8:\
			a.value.u8 = op a.value.u8;\
		break;\
		case ZRTOS_VM_IO_TYPE__UINT16:\
			a.value.u16 = op a.value.u16;\
		break;\
		case ZRTOS_VM_IO_TYPE__UINT32:\
			a.value.u32 = op a.value.u32;\
		break;\
		case ZRTOS_VM_IO_TYPE__UINT64:\
			a.value.u64 = op a.value.u64;\
		break;\
		case ZRTOS_VM_IO_TYPE__FLOAT:\
			a.value.f4 = op a.value.f4;\
		break;\
		case ZRTOS_VM_IO_TYPE__DOUBLE:\
			a.value.f8 = op a.value.f8;\
		break;

#define ZRTOS_VM_OP_BOOLEAN(op)\
		case ZRTOS_VM_IO_TYPE__INT8:\
			a.value.u8 = a.value.s8 op b.value.s8;\
		break;\
		case ZRTOS_VM_IO_TYPE__INT16:\
			a.value.u8 = a.value.s16 op b.value.s16;\
		break;\
		case ZRTOS_VM_IO_TYPE__INT32:\
			a.value.u8 = a.value.s32 op b.value.s32;\
		break;\
		case ZRTOS_VM_IO_TYPE__INT64:\
			a.value.u8 = a.value.s64 op b.value.s64;\
		break;\
		case ZRTOS_VM_IO_TYPE__UINT8:\
			a.value.u8 = a.value.u8 op b.value.u8;\
		break;\
		case ZRTOS_VM_IO_TYPE__UINT16:\
			a.value.u8 = a.value.u16 op b.value.u16;\
		break;\
		case ZRTOS_VM_IO_TYPE__UINT32:\
			a.value.u8 = a.value.u32 op b.value.u32;\
		break;\
		case ZRTOS_VM_IO_TYPE__UINT64:\
			a.value.u8 = a.value.u64 op b.value.u64;\
		break;\
		case ZRTOS_VM_IO_TYPE__FLOAT:\
			a.value.u8 = a.value.f4 op b.value.f4;\
		break;\
		case ZRTOS_VM_IO_TYPE__DOUBLE:\
			a.value.u8 = a.value.f8 op b.value.f8;\
		break;

zrtos_error_t zrtos_vm__icall(zrtos_vm_t *thiz,zrtos_vm_function_id_t id){
	zrtos_error_t ret = EINVAL;
	zrtos_vm_function_t fn = zrtos_vm_function_index__get_function(
		 &thiz->functions
		,id
	);
	if(fn){
		ret = zrtos_vm_function__get_callback(fn)(
			 thiz
			,zrtos_vm_function__get_ctx(fn)
		);
	}
	return ret;
}

zrtos_error_t zrtos_vm__run(zrtos_vm_t *thiz){
	zrtos_stack_t *stack = &thiz->stack;
	zrtos_stack_t *program = &thiz->program;
	zrtos_stack_t *set_offset_stack;
	zrtos_error_t ret = EXIT_SUCCESS;
	zrtos_vm_value_t a;
	zrtos_vm_value_t b;
	zrtos_vm_value_t tmp;
	zrtos_vm_io_type_t io_type;
	zrtos_vm_io_source_t io_src;
	size_t length; 
	zrtos_vm_ioop_t ioop;
	zrtos_stack_t *src;
	zrtos_vm_value_t *dest;
	zrtos_vm_io_address_t address;

	while(!thiz->is_interrupted
	   && zrtos_stack__pop(program,&ioop,2)
	){
		io_type = (ioop.io & ZRTOS_VM_IO_TYPE__MASK);
		io_src = ioop.io & ZRTOS_VM_IO_SOURCE__MASK;
		length = zrtos_vm_io_type__get_length(io_type);

		zrtos_mem__zero(&a.value,sizeof(a.value));

		//input
		dest = &a;
		while(io_src){
			if((io_src & ZRTOS_VM_IO_SOURCE__A_PROGRAM) > 0){
				src = program;
			}else if((io_src & ZRTOS_VM_IO_SOURCE__A_STACK) > 0){
				src = stack;
			}else if((io_src & ZRTOS_VM_IO_SOURCE__A_ADDRESS) > 0){
				zrtos_mem__zero(
					 &dest->address.address
					,sizeof(dest->address.address)
				);
				if(zrtos_stack__pop(program,&dest->address.type,1)
				&& zrtos_stack__pop(
					 program
					,&dest->address.address
					,zrtos_vm_io_address__get_length(&dest->address)
				)
				&& zrtos_stack__read_ex(
					( zrtos_vm_io_address__is_source_program(&dest->address)
					? program
					: stack)
					,&dest->value
					,length
					,zrtos_vm_io_address__get_address(&dest->address)
					,zrtos_vm_io_address__is_relative(&dest->address)
					,zrtos_vm_io_address__is_negative(&dest->address)
				)){
					goto L_INPUT__NEXT;
				}
				goto L_RETURN__EFAULT;
			}else{
				goto L_INPUT__NEXT;
			}

			if(!zrtos_stack__pop(src,&dest->value,length)){
				goto L_RETURN__EFAULT;
			}

L_INPUT__NEXT:
			dest = &b;
			io_src >>= 2;
		}

		//process
		switch(ioop.op){
			case ZRTOS_VM_OP__CAST_INT8:
			case ZRTOS_VM_OP__CAST_INT16:
			case ZRTOS_VM_OP__CAST_INT32:
			case ZRTOS_VM_OP__CAST_INT64:
				if(zrtos_vm_io_type__is_int(a.type)){
				}else if(zrtos_vm_io_type__is_uint(a.type)){
					a.value.s64 = (int64_t)a.value.u64;
				}else if(zrtos_vm_io_type__is_float(a.type)){
					a.value.s64 = (int64_t)a.value.f32;
				}else if(zrtos_vm_io_type__is_double(a.type)){
					a.value.s64 = (int64_t)a.value.f64;
				}
			goto L_OUTPUT__CAST;
			case ZRTOS_VM_OP__CAST_UINT8:
			case ZRTOS_VM_OP__CAST_UINT16:
			case ZRTOS_VM_OP__CAST_UINT32:
			case ZRTOS_VM_OP__CAST_UINT64:
				if(zrtos_vm_io_type__is_uint(a.type)){
				}else if(zrtos_vm_io_type__is_int(a.type)){
					a.value.u64 = (uint64_t)a.value.s64;
				}else if(zrtos_vm_io_type__is_float(a.type)){
					a.value.u64 = (uint64_t)a.value.f32;
				}else if(zrtos_vm_io_type__is_double(a.type)){
					a.value.u64 = (uint64_t)a.value.f64;
				}
			goto L_OUTPUT__CAST;
			case ZRTOS_VM_OP__CAST_FLOAT:
				if(zrtos_vm_io_type__is_uint(a.type)){
					a.value.f32 = (float)a.value.s64;
				}else if(zrtos_vm_io_type__is_int(a.type)){
					a.value.u64 = (uint64_t)a.value.s64;
				}else if(zrtos_vm_io_type__is_float(a.type)){
					a.value.u64 = (uint64_t)a.value.f32;
				}else if(zrtos_vm_io_type__is_double(a.type)){
					a.value.u64 = (uint64_t)a.value.f64;
				}
			goto L_OUTPUT__CAST;
			case ZRTOS_VM_OP__CAST_DOUBLE:
			goto L_OUTPUT__CAST;

			case ZRTOS_VM_OP__PUSH:
			goto L_OUTPUT__PUSH_TYPE;
			case ZRTOS_VM_OP__POP:
			goto L_OUTPUT__END;



			case ZRTOS_VM_OP__AND:
				a.value.u64 &= b.value.u64;
			goto L_OUTPUT__PUSH_TYPE;
			case ZRTOS_VM_OP__OR:
				a.value.u64 |= b.value.u64;
			goto L_OUTPUT__PUSH_TYPE;
			case ZRTOS_VM_OP__XOR:
				a.value.u64 ^= b.value.u64;
			goto L_OUTPUT__PUSH_TYPE;
			case ZRTOS_VM_OP__NEG:
				a.value.u64 = ~a.value.u64;
			goto L_OUTPUT__PUSH_TYPE;

			case ZRTOS_VM_OP__ADD:
				switch(io_type){
					ZRTOS_VM_OP(+)
				}
			goto L_OUTPUT__PUSH_TYPE;
			case ZRTOS_VM_OP__SUB:
				switch(io_type){
					ZRTOS_VM_OP(-)
				}
			goto L_OUTPUT__PUSH_TYPE;
			case ZRTOS_VM_OP__MUL:
				switch(io_type){
					ZRTOS_VM_OP(*)
				}
			goto L_OUTPUT__PUSH_TYPE;
			case ZRTOS_VM_OP__DIV:
				switch(io_type){
					ZRTOS_VM_OP(/)
				}
			goto L_OUTPUT__PUSH_TYPE;
			case ZRTOS_VM_OP__MOD:
				switch(io_type){
					ZRTOS_VM_OP_WITHOUT_FLOAT(%)
				}
			goto L_OUTPUT__PUSH_TYPE;

			case ZRTOS_VM_OP__NOT:
				switch(io_type){
					ZRTOS_VM_OP_NOT(!)
				}
			goto L_OUTPUT__PUSH_BOOL;
			case ZRTOS_VM_OP__EQ:
				switch(io_type){
					ZRTOS_VM_OP_BOOLEAN(==)
				}
			goto L_OUTPUT__PUSH_BOOL;
			case ZRTOS_VM_OP__LT:
				switch(io_type){
					ZRTOS_VM_OP_BOOLEAN(<)
				}
			goto L_OUTPUT__PUSH_BOOL;
			case ZRTOS_VM_OP__GT:
				switch(io_type){
					ZRTOS_VM_OP_BOOLEAN(>)
				}
			goto L_OUTPUT__PUSH_BOOL;
			case ZRTOS_VM_OP__LE:
				switch(io_type){
					ZRTOS_VM_OP_BOOLEAN(<=)
				}
			goto L_OUTPUT__PUSH_BOOL;
			case ZRTOS_VM_OP__GE:
				switch(io_type){
					ZRTOS_VM_OP_BOOLEAN(>=)
				}
			goto L_OUTPUT__PUSH_BOOL;


			case ZRTOS_VM_OP__IF:
				if(b.value.u8 == 0){
					goto L_OUTPUT__SET_PROGRAM_OFFSET;
				}
			goto L_OUTPUT__END;

			case ZRTOS_VM_OP__ICALL:
				ret = zrtos_vm__icall(thiz,a.value.uint64);
				if(ret != 0){
					goto L_RETURN__END;
				}
			goto L_OUTPUT__END;

			case ZRTOS_VM_OP__CALL:
			goto L_OUTPUT__SET_PROGRAM_OFFSET;

			case ZRTOS_VM_OP__RET:

			case ZRTOS_VM_OP__NOP:
			goto L_OUTPUT__END;
		}

		goto L_OUTPUT__END;

		//output
L_OUTPUT__CAST:
		a.type = ioop.op - ZRTOS_VM_OP__CAST;
		goto L_OUTPUT__PUSH_TYPE;
L_OUTPUT__PUSH_BOOL:
		a.type = ZRTOS_VM_IO_TYPE__UINT8;
L_OUTPUT__PUSH_TYPE:
		if((io_src & ZRTOS_VM_IO_SOURCE__A_ADDRESS) > 0){
			if(zrtos_stack__write_ex(
				 stack
				,&a.value
				,zrtos_vm_io_type__get_length(a.type)	
				,zrtos_vm_io_address__get_address(&a.address)
				,zrtos_vm_io_address__is_relative(&a.address)
				,zrtos_vm_io_address__is_negative(&a.address)
			)){
				goto L_OUTPUT__END;
			}
		}else if(zrtos_stack__push(
			 stack
			,&a.value
			,zrtos_vm_io_type__get_length(a.type)
		)){
			goto L_OUTPUT__END;
		}
		goto L_RETURN__EFAULT;
L_OUTPUT__SET_PROGRAM_OFFSET:
		set_offset_stack = program;
		goto L_OUTPUT__SET_OFFSET;
L_OUTPUT__SET_STACK_OFFSET:
		set_offset_stack = stack;
L_OUTPUT__SET_OFFSET:
		if(!zrtos_stack__set_offset_ex(
			 set_offset_stack
			,a.value.u64 >> 2
			,(a.value.u64 & 0x1) > 0
			,(a.value.u64 & 0x2) > 0
		)){
			goto L_RETURN__EFAULT;
		}
		goto L_OUTPUT__END;
L_OUTPUT__END:
		continue;
	}

L_RETURN__EFAULT:
	ret = EFAULT;
L_RETURN__END:
	return ret;
}


#ifdef __cplusplus
}
#endif
#endif