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
#include "zrtos_assert.h"

struct _zrtos_vm_t;

#include "zrtos_vm_io.h"
#include "zrtos_vm_function_index.h"


typedef enum{
	 ZRTOS_VM_OP__MIN          = 0x00

	,ZRTOS_VM_OP__CAST         = 0x00
	,ZRTOS_VM_OP__CAST_MIN     = 0x00
	,ZRTOS_VM_OP__CAST_UINT8   = 0x00
	,ZRTOS_VM_OP__CAST_UINT16  = 0x01
	,ZRTOS_VM_OP__CAST_UINT32  = 0x03
	,ZRTOS_VM_OP__CAST_UINT64  = 0x07
	,ZRTOS_VM_OP__CAST_INT8    = 0x08
	,ZRTOS_VM_OP__CAST_INT16   = 0x09
	,ZRTOS_VM_OP__CAST_INT32   = 0x0B
	,ZRTOS_VM_OP__CAST_FLOAT   = 0x0D
	,ZRTOS_VM_OP__CAST_DOUBLE  = 0x0E
	,ZRTOS_VM_OP__CAST_INT64   = 0x0F
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

	,ZRTOS_VM_OP__SET_SP       = 0x25

	,ZRTOS_VM_OP__NOP          = 0x26

	,ZRTOS_VM_OP__MAX          = 0xFF
}zrtos_vm_op_t;

ZRTOS_ASSERT__STATIC(sizeof(zrtos_vm_op_t) == sizeof(uint8_t));

typedef struct _zrtos_vm_t{
	zrtos_stack_t             stack;
	zrtos_stack_t             program;
	zrtos_vm_function_index_t functions;
	bool                      is_interrupted;
}zrtos_vm_t;

bool zrtos_vm__init(
	 zrtos_vm_t *thiz
	,zrtos_stack_t             stack
	,zrtos_stack_t             program
	,zrtos_vm_function_index_t functions
){
	thiz->stack = stack;
	thiz->program = program;
	thiz->functions = functions;
	thiz->is_interrupted = false;

	return true;
}

typedef struct _zrtos_vm_value_t{
	union{
		uint8_t  v_u8;
		uint16_t v_u16;
		uint32_t v_u32;
		uint64_t v_u64;

		int8_t   v_s8;
		int16_t  v_s16;
		int32_t  v_s32;
		int64_t  v_s64;

		float    v_f32;
		double   v_f64;
	}value;
	zrtos_vm_io_type_t             type;
	zrtos_vm_io_address_t          address;
}zrtos_vm_value_t;

void zrtos_vm_value__normalize(zrtos_vm_value_t *thiz){
	switch(thiz->type){
		case ZRTOS_VM_IO_TYPE__INT8:
			thiz->value.v_s64 = (int64_t)thiz->value.v_s8;
		break;
		case ZRTOS_VM_IO_TYPE__INT16:
			thiz->value.v_s64 = (int64_t)thiz->value.v_s16;
		break;
		case ZRTOS_VM_IO_TYPE__INT32:
			thiz->value.v_s64 = (int64_t)thiz->value.v_s32;
		break;
		case ZRTOS_VM_IO_TYPE__INT64:
		case ZRTOS_VM_IO_TYPE__UINT8:
		case ZRTOS_VM_IO_TYPE__UINT16:
		case ZRTOS_VM_IO_TYPE__UINT32:
		case ZRTOS_VM_IO_TYPE__UINT64:
		case ZRTOS_VM_IO_TYPE__FLOAT:
		case ZRTOS_VM_IO_TYPE__DOUBLE:
		break;
	}
}

typedef struct{
	uint8_t       io;
	zrtos_vm_op_t op;
}__attribute__((packed))zrtos_vm_ioop_t;

zrtos_error_t zrtos_vm__icall(zrtos_vm_t *thiz,zrtos_vm_function_id_t id){
	zrtos_error_t ret = EINVAL;
	zrtos_vm_function_t *fn = zrtos_vm_function_index__get_function(
		 &thiz->functions
		,id
	);
	if(fn){
		ret = zrtos_vm_function__get_callback(fn)(
			 thiz
			,fn
		);
	}
	return ret;
}


#define ZRTOS_VM_OP_WITHOUT_FLOAT(op)\
		case ZRTOS_VM_IO_TYPE__INT8:\
			a.value.v_s8 = a.value.v_s8 op b.value.v_s8;\
		break;\
		case ZRTOS_VM_IO_TYPE__INT16:\
			a.value.v_s16 = a.value.v_s16 op b.value.v_s16;\
		break;\
		case ZRTOS_VM_IO_TYPE__INT32:\
			a.value.v_s32 = a.value.v_s32 op b.value.v_s32;\
		break;\
		case ZRTOS_VM_IO_TYPE__INT64:\
			a.value.v_s64 = a.value.v_s64 op b.value.v_s64;\
		break;\
		case ZRTOS_VM_IO_TYPE__UINT8:\
			a.value.v_u8 = a.value.v_u8 op b.value.v_u8;\
		break;\
		case ZRTOS_VM_IO_TYPE__UINT16:\
			a.value.v_u16 = a.value.v_u16 op b.value.v_u16;\
		break;\
		case ZRTOS_VM_IO_TYPE__UINT32:\
			a.value.v_u32 = a.value.v_u32 op b.value.v_u32;\
		break;\
		case ZRTOS_VM_IO_TYPE__UINT64:\
			a.value.v_u64 = a.value.v_u64 op b.value.v_u64;\
		break;

#define ZRTOS_VM_OP(op)\
		ZRTOS_VM_OP_WITHOUT_FLOAT(op)\
		case ZRTOS_VM_IO_TYPE__FLOAT:\
			a.value.v_f32 = a.value.v_f32 op b.value.v_f32;\
		break;\
		case ZRTOS_VM_IO_TYPE__DOUBLE:\
			a.value.v_f64 = a.value.v_f64 op b.value.v_f64;\
		break;

#define ZRTOS_VM_OP_NOT(op)\
		case ZRTOS_VM_IO_TYPE__FLOAT:\
			a.value.v_f32 = op a.value.v_f32;\
		break;\
		case ZRTOS_VM_IO_TYPE__DOUBLE:\
			a.value.v_f64 = op a.value.v_f64;\
		break;\
		case ZRTOS_VM_IO_TYPE__INT8:\
		case ZRTOS_VM_IO_TYPE__INT16:\
		case ZRTOS_VM_IO_TYPE__INT32:\
		case ZRTOS_VM_IO_TYPE__INT64:\
		case ZRTOS_VM_IO_TYPE__UINT8:\
		case ZRTOS_VM_IO_TYPE__UINT16:\
		case ZRTOS_VM_IO_TYPE__UINT32:\
		case ZRTOS_VM_IO_TYPE__UINT64:\
			a.value.v_u64 = op a.value.v_u64;\
		break;

#define ZRTOS_VM_OP_BOOLEAN(op)\
		case ZRTOS_VM_IO_TYPE__INT8:\
		case ZRTOS_VM_IO_TYPE__INT16:\
		case ZRTOS_VM_IO_TYPE__INT32:\
		case ZRTOS_VM_IO_TYPE__INT64:\
			a.value.v_u8 = a.value.v_s64 op b.value.v_s64;\
		break;\
		case ZRTOS_VM_IO_TYPE__UINT8:\
		case ZRTOS_VM_IO_TYPE__UINT16:\
		case ZRTOS_VM_IO_TYPE__UINT32:\
		case ZRTOS_VM_IO_TYPE__UINT64:\
			a.value.v_u8 = a.value.v_u64 op b.value.v_u64;\
		break;\
		case ZRTOS_VM_IO_TYPE__FLOAT:\
			a.value.v_u8 = a.value.v_f32 op b.value.v_f32;\
		break;\
		case ZRTOS_VM_IO_TYPE__DOUBLE:\
			a.value.v_u8 = a.value.v_f64 op b.value.v_f64;\
		break;


zrtos_error_t zrtos_vm__run(zrtos_vm_t *thiz){
	zrtos_stack_t *stack = &thiz->stack;
	zrtos_stack_t *program = &thiz->program;
	zrtos_stack_t *set_offset_stack;
	zrtos_error_t ret = EXIT_SUCCESS;
	zrtos_vm_value_t a;
	zrtos_vm_value_t b;
	zrtos_vm_io_type_t io_type;
	zrtos_vm_io_source_t io_src;
	size_t length; 
	zrtos_vm_ioop_t ioop;
	zrtos_vm_value_t *dest;

	while(!thiz->is_interrupted
	   && zrtos_stack__shift(program,&ioop,2)
	){
		io_type = (ioop.io & ZRTOS_VM_IO_TYPE__MASK);
		io_src = (ioop.io & ZRTOS_VM_IO_SOURCE__MASK);
		length = zrtos_vm_io_type__get_length(io_type);

		zrtos_mem__zero(&a.value,sizeof(a.value));
		zrtos_mem__zero(&b.value,sizeof(b.value));

		a.type = b.type = io_type;

		//input
		dest = &a;
		while((io_src & ZRTOS_VM_IO_SOURCE__MASK)){
			if((io_src & ZRTOS_VM_IO_SOURCE__A_PROGRAM) > 0){
				if(!zrtos_stack__shift(program,&dest->value,length)){
					goto L_RETURN__EFAULT;
				}
			}else if((io_src & ZRTOS_VM_IO_SOURCE__A_STACK) > 0){
				if(!zrtos_stack__pop(stack,&dest->value,length)){
					goto L_RETURN__EFAULT;
				}
			}else if((io_src & ZRTOS_VM_IO_SOURCE__A_ADDRESS) > 0){
				zrtos_mem__zero(
					 &dest->address.address
					,sizeof(dest->address.address)
				);
				if(zrtos_stack__shift(program,&dest->address.type,1)
				&& zrtos_stack__shift(
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
					goto L_INPUT_NORMALIZE;
				}
				goto L_RETURN__EFAULT;
			}else{
				goto L_INPUT__NEXT;
			}

			

L_INPUT_NORMALIZE:
			zrtos_vm_value__normalize(dest);
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
				if(zrtos_vm_io_type__is_uint(a.type)){
					a.value.v_s64 = (int64_t)a.value.v_u64;
				}else if(zrtos_vm_io_type__is_float(a.type)){
					a.value.v_s64 = (int64_t)a.value.v_f32;
				}else if(zrtos_vm_io_type__is_double(a.type)){
					a.value.v_s64 = (int64_t)a.value.v_f64;
				}else{//} if(zrtos_vm_io_type__is_int(a.type)){

				}
			goto L_OUTPUT__CAST;
			case ZRTOS_VM_OP__CAST_UINT8:
			case ZRTOS_VM_OP__CAST_UINT16:
			case ZRTOS_VM_OP__CAST_UINT32:
			case ZRTOS_VM_OP__CAST_UINT64:
				if(zrtos_vm_io_type__is_uint(a.type)){

				}else if(zrtos_vm_io_type__is_float(a.type)){
					a.value.v_u64 = (uint64_t)a.value.v_f32;
				}else if(zrtos_vm_io_type__is_double(a.type)){
					a.value.v_u64 = (uint64_t)a.value.v_f64;
				}else{//} if(zrtos_vm_io_type__is_int(a.type)){
					a.value.v_u64 = (uint64_t)a.value.v_s64;
				}
			goto L_OUTPUT__CAST;
			case ZRTOS_VM_OP__CAST_FLOAT:
				if(zrtos_vm_io_type__is_uint(a.type)){
					a.value.v_f32 = (float)a.value.v_u64;
				}else if(zrtos_vm_io_type__is_float(a.type)){

				}else if(zrtos_vm_io_type__is_double(a.type)){
					a.value.v_f32 = (float)a.value.v_f64;
				}else{//} if(zrtos_vm_io_type__is_int(a.type)){
					a.value.v_f32 = (float)a.value.v_s64;
				}
			goto L_OUTPUT__CAST;
			case ZRTOS_VM_OP__CAST_DOUBLE:
				if(zrtos_vm_io_type__is_uint(a.type)){
					a.value.v_f64 = (double)a.value.v_u64;
				}else if(zrtos_vm_io_type__is_float(a.type)){
					a.value.v_f64 = (double)a.value.v_f32;
				}else if(zrtos_vm_io_type__is_double(a.type)){

				}else{//} if(zrtos_vm_io_type__is_int(a.type)){
					a.value.v_f64 = (double)a.value.v_s64;
				}
			goto L_OUTPUT__CAST;

			case ZRTOS_VM_OP__PUSH:
			goto L_OUTPUT__PUSH_TYPE;
			case ZRTOS_VM_OP__POP:
			goto L_OUTPUT__END;



			case ZRTOS_VM_OP__AND:
				a.value.v_u64 &= b.value.v_u64;
			goto L_OUTPUT__PUSH_TYPE;
			case ZRTOS_VM_OP__OR:
				a.value.v_u64 |= b.value.v_u64;
			goto L_OUTPUT__PUSH_TYPE;
			case ZRTOS_VM_OP__XOR:
				a.value.v_u64 ^= b.value.v_u64;
			goto L_OUTPUT__PUSH_TYPE;
			case ZRTOS_VM_OP__NEG:
				a.value.v_u64 = ~a.value.v_u64;
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
					case ZRTOS_VM_IO_TYPE__FLOAT:
					case ZRTOS_VM_IO_TYPE__DOUBLE:
					goto L_RETURN__EINVAL;
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
				if(b.value.v_u8 == 0){
					goto L_OUTPUT__SET_PROGRAM_OFFSET;
				}
			goto L_OUTPUT__END;

			case ZRTOS_VM_OP__ICALL:
				ret = zrtos_vm__icall(thiz,a.value.v_u64);
				if(ret != 0){
					goto L_RETURN__END;
				}
			goto L_OUTPUT__END;

			case ZRTOS_VM_OP__CALL:
			case ZRTOS_VM_OP__RET:
			goto L_OUTPUT__SET_PROGRAM_OFFSET;

			case ZRTOS_VM_OP__SET_SP:
			goto L_OUTPUT__SET_STACK_OFFSET;

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
			,a.value.v_u64 >> 2
			,(a.value.v_u64 & 0x1) > 0
			,(a.value.v_u64 & 0x2) > 0
		)){
			goto L_RETURN__EFAULT;
		}
		goto L_OUTPUT__END;
L_OUTPUT__END:
		continue;
	}

L_RETURN__EINVAL:
	ret = EINVAL;
	goto L_RETURN__END;
L_RETURN__EFAULT:
	ret = EFAULT;
	goto L_RETURN__END;
L_RETURN__END:
	return ret;
}

#undef ZRTOS_VM_OP_WITHOUT_FLOAT
#undef ZRTOS_VM_OP
#undef ZRTOS_VM_OP_NOT
#undef ZRTOS_VM_OP_BOOLEAN


#ifdef __cplusplus
}
#endif
#endif