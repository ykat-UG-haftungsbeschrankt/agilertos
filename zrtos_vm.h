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


#include "zrtos_stack.h"
#include "zrtos_error.h"


typedef enum{
	 ZRTOS_VM_IO_SOURCE__A_NONE          = 0x00
	,ZRTOS_VM_IO_SOURCE__A_STACK         = 0x10
	,ZRTOS_VM_IO_SOURCE__A_PC            = 0x20
	,ZRTOS_VM_IO_SOURCE__A_ADDRESS       = 0x40
	,ZRTOS_VM_IO_SOURCE__B_NONE          = (0x00 << 2)
	,ZRTOS_VM_IO_SOURCE__B_STACK         = (0x10 << 2)
	,ZRTOS_VM_IO_SOURCE__B_PC            = (0x20 << 2)
	,ZRTOS_VM_IO_SOURCE__B_ADDRESS       = (0x40 << 2)
	,ZRTOS_VM_IO_SOURCE__MASK            = 0xF0
}zrtos_vm_io_source_t;

typedef enum{
	 ZRTOS_VM_IO_TYPE__INT8    = 0x01
	,ZRTOS_VM_IO_TYPE__INT16   = 0x02
	,ZRTOS_VM_IO_TYPE__INT32   = 0x03
	,ZRTOS_VM_IO_TYPE__INT64   = 0x04
	,ZRTOS_VM_IO_TYPE__UINT8   = 0x05
	,ZRTOS_VM_IO_TYPE__UINT16  = 0x06
	,ZRTOS_VM_IO_TYPE__UINT32  = 0x07
	,ZRTOS_VM_IO_TYPE__UINT64  = 0x08
	,ZRTOS_VM_IO_TYPE__FLOAT   = 0x09
	,ZRTOS_VM_IO_TYPE__DOUBLE  = 0x0A
	,ZRTOS_VM_IO_TYPE__MASK    = 0x0F
}zrtos_vm_io_type_t;

size_t zrtos_vm_io_type__get_length(zrtos_vm_io_type_t type){
	if(type >= ZRTOS_VM_IO_TYPE__FLOAT){
		type = (type - 8) * 4;
	}else if(type >= ZRTOS_VM_IO_TYPE__UINT8){
		type -= 4;
	}
	return type;
}

typedef enum{
	 ZRTOS_VM_OP__END        = 0x00
	,ZRTOS_VM_OP__CAST       = 0x00
	,ZRTOS_VM_OP__CAST_INT8    = 0x01
	,ZRTOS_VM_OP__CAST_INT16   = 0x02
	,ZRTOS_VM_OP__CAST_INT32   = 0x03
	,ZRTOS_VM_OP__CAST_INT64   = 0x04
	,ZRTOS_VM_OP__CAST_UINT8    = 0x05
	,ZRTOS_VM_OP__CAST_UINT16   = 0x06
	,ZRTOS_VM_OP__CAST_UINT32   = 0x07
	,ZRTOS_VM_OP__CAST_UINT64   = 0x08
	,ZRTOS_VM_OP__CAST_FLOAT   = 0x09
	,ZRTOS_VM_OP__CAST_DOUBLE   = 0x0A

	,ZRTOS_VM_OP__CALL    = 0x01
	,ZRTOS_VM_OP__RET     = 0x02
	,ZRTOS_VM_OP__JMP     = 0x03
	,ZRTOS_VM_OP__PUSH    = 0x04
	,ZRTOS_VM_OP__POP     = 0x05
	,ZRTOS_VM_OP__LOAD    = 0x06
	,ZRTOS_VM_OP__STORE   = 0x07

	,ZRTOS_VM_OP__ADD     = 0x40
	,ZRTOS_VM_OP__SUB     = 0x50
	,ZRTOS_VM_OP__MUL     = 0x60
	,ZRTOS_VM_OP__DIV     = 0x70
	,ZRTOS_VM_OP__1D      = 0x80
	,ZRTOS_VM_OP__2D      = 0x80
	,ZRTOS_VM_OP__3D      = 0x90

	,ZRTOS_VM_OP__EQ      = 0xA0
	,ZRTOS_VM_OP__LT      = 0xB0
	,ZRTOS_VM_OP__GT      = 0xC0
	,ZRTOS_VM_OP__LE      = 0xD0
	,ZRTOS_VM_OP__GE      = 0xE0

	,ZRTOS_VM_OP__MOD     = 0x01

	,ZRTOS_VM_OP__AND     = 0x02
	,ZRTOS_VM_OP__OR      = 0x03
	,ZRTOS_VM_OP__XOR     = 0x04
	,ZRTOS_VM_OP__NEG     = 0x05


}zrtos_vm_op_t;

typedef struct{
	uint8_t io;
	uint8_t op;
}zrtos_vm_ioop_t;

typedef enum{
	 ZRTOS_VM_IO_ADDRESS_TYPE__MIN                   = 0x00
	,ZRTOS_VM_IO_ADDRESS_TYPE__DISPLACEMENT_ABSOLUTE = 0x00
	,ZRTOS_VM_IO_ADDRESS_TYPE__DISPLACEMENT_RELATIVE = 0x01
	,ZRTOS_VM_IO_ADDRESS_TYPE__DISPLACEMENT_MASK     = 0x01

	,ZRTOS_VM_IO_ADDRESS_TYPE__SOURCE_PROGRAM        = 0x02
	,ZRTOS_VM_IO_ADDRESS_TYPE__SOURCE_STACK          = 0x04
	,ZRTOS_VM_IO_ADDRESS_TYPE__SOURCE_MASK           = 0x06

	,ZRTOS_VM_IO_ADDRESS_TYPE__LENGTH_1              = 0x10
	,ZRTOS_VM_IO_ADDRESS_TYPE__LENGTH_2              = 0x20
	,ZRTOS_VM_IO_ADDRESS_TYPE__LENGTH_4              = 0x30
	,ZRTOS_VM_IO_ADDRESS_TYPE__LENGTH_8              = 0x40
	,ZRTOS_VM_IO_ADDRESS_TYPE__LENGTH_MASK           = 0x70
	,ZRTOS_VM_IO_ADDRESS_TYPE__MAX                   = 0xFF
}zrtos_vm_io_address_type_t;

typedef struct _zrtos_vm_io_source_address_t{
	size_t                      address;
	zrtos_vm_io_address_type_t  type;
}zrtos_vm_io_address_t;

typedef struct _zrtos_vm_t{
	zrtos_stack_t stack;
	zrtos_stack_t program;
}zrtos_vm_t;

typedef struct _zrtos_vm_value_t{
	union{
		bool     boolean;

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
	
		size_t   pc;
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
			a.value.boolean = a.value.s8 op b.value.s8;\
		break;\
		case ZRTOS_VM_IO_TYPE__INT16:\
			a.value.boolean = a.value.s16 op b.value.s16;\
		break;\
		case ZRTOS_VM_IO_TYPE__INT32:\
			a.value.boolean = a.value.s32 op b.value.s32;\
		break;\
		case ZRTOS_VM_IO_TYPE__INT64:\
			a.value.boolean = a.value.s64 op b.value.s64;\
		break;\
		case ZRTOS_VM_IO_TYPE__UINT8:\
			a.value.boolean = a.value.u8 op b.value.u8;\
		break;\
		case ZRTOS_VM_IO_TYPE__UINT16:\
			a.value.boolean = a.value.u16 op b.value.u16;\
		break;\
		case ZRTOS_VM_IO_TYPE__UINT32:\
			a.value.boolean = a.value.u32 op b.value.u32;\
		break;\
		case ZRTOS_VM_IO_TYPE__UINT64:\
			a.value.boolean = a.value.u64 op b.value.u64;\
		break;\
		case ZRTOS_VM_IO_TYPE__FLOAT:\
			a.value.boolean = a.value.f4 op b.value.f4;\
		break;\
		case ZRTOS_VM_IO_TYPE__DOUBLE:\
			a.value.boolean = a.value.f8 op b.value.f8;\
		break;



zrtos_error_t zrtos_vm_runtime__run(zrtos_vm_t *thiz){
	zrtos_stack_t *stack = &thiz->stack;
	zrtos_stack_t *program = &thiz->program;
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
	size_t pc;

	while(true){
		if(!zrtos_stack__pop(program,&ioop,2)){
			goto L_EFAULT;
		}

		io_type = (ioop.io & ZRTOS_VM_IO_TYPE__MASK);
		io_src = ioop.io & ZRTOS_VM_IO_SOURCE__MASK;
		length = zrtos_vm_io_type__get_length(io_type);
		//load values
		dest = &a;
		while(io_src){
			if((io & ZRTOS_VM_IO_SOURCE__A_PC) > 0){
				src = program;
			}else if((io & ZRTOS_VM_IO_SOURCE__A_STACK) > 0){
				src = stack;
			}else if((io & ZRTOS_VM_IO_SOURCE__A_ADDRESS) > 0){
				if(!zrtos_stack__pop(program,&dest->address.type,1)){
					goto L_EFAULT;
				}
				if(!zrtos_stack__pop(
					program
					,&dest->address.address
					,zrtos_vm_io_address__get_length(&dest->address)
				)){
					goto L_EFAULT;
				}
				if(!zrtos_stack__read(
					( zrtos_vm_io_address__is_source_program(&dest->address)
					? program
					: stack)
					,dest
					,length
				)){
					goto L_EFAULT;
				}
				goto L_NEXT;
			}else{
				goto L_NEXT;
			}

			if(!zrtos_stack__pop(src,dest,length)){
				goto L_EFAULT;
			}
L_NEXT:
			dest = &b;
			io_src >>= 2;
		}

		
		//compute values
		switch(ioop.op){
			case ZRTOS_VM_OP__CAST_INT8:
			case ZRTOS_VM_OP__CAST_INT16:
			case ZRTOS_VM_OP__CAST_INT32:
			case ZRTOS_VM_OP__CAST_INT64:
				if(zrtos_vm_io_type__is_int(a.value.type)){
				}else if(zrtos_vm_io_type__is_uint(a.value.type)){
					a.value.s64 = (int64_t)a.value.u64;
				}else if(zrtos_vm_io_type__is_float(a.value.type)){
					a.value.s64 = (int64_t)a.value.f32;
				}else if(zrtos_vm_io_type__is_double(a.value.type)){
					a.value.s64 = (int64_t)a.value.f64;
				}
			goto L_CAST;
			case ZRTOS_VM_OP__CAST_UINT8:
			case ZRTOS_VM_OP__CAST_UINT16:
			case ZRTOS_VM_OP__CAST_UINT32:
			case ZRTOS_VM_OP__CAST_UINT64:
				if(zrtos_vm_io_type__is_uint(a.value.type)){
				}else if(zrtos_vm_io_type__is_int(a.value.type)){
					a.value.u64 = (uint64_t)a.value.s64;
				}else if(zrtos_vm_io_type__is_float(a.value.type)){
					a.value.u64 = (uint64_t)a.value.f32;
				}else if(zrtos_vm_io_type__is_double(a.value.type)){
					a.value.u64 = (uint64_t)a.value.f64;
				}
			goto L_CAST;
			case ZRTOS_VM_OP__CAST_FLOAT:
				if(zrtos_vm_io_type__is_uint(a.value.type)){
					a.value.f32 = (float)a.value.s64;
				}else if(zrtos_vm_io_type__is_int(a.value.type)){
					a.value.u64 = (uint64_t)a.value.s64;
				}else if(zrtos_vm_io_type__is_float(a.value.type)){
					a.value.u64 = (uint64_t)a.value.f32;
				}else if(zrtos_vm_io_type__is_double(a.value.type)){
					a.value.u64 = (uint64_t)a.value.f64;
				}
			goto L_CAST;
			case ZRTOS_VM_OP__CAST_DOUBLE:
			goto L_CAST;

			case ZRTOS_VM_OP__PUSH:
			goto L_PUSH_TPYE;
			case ZRTOS_VM_OP__POP:
			goto L_PUSH_NOTHING;

			case ZRTOS_VM_OP__ADD:
				switch(io_type){
					ZRTOS_VM_OP(+)
				}
			goto L_PUSH_TYPE;
			case ZRTOS_VM_OP__SUB:
				switch(io_type){
					ZRTOS_VM_OP(-)
				}
			goto L_PUSH_TYPE;
			case ZRTOS_VM_OP__MUL:
				switch(io_type){
					ZRTOS_VM_OP(*)
				}
			goto L_PUSH_TYPE;
			case ZRTOS_VM_OP__DIV:
				switch(io_type){
					ZRTOS_VM_OP(/)
				}
			goto L_PUSH_TYPE;
			case ZRTOS_VM_OP__MOD:
				switch(io_type){
					ZRTOS_VM_OP_WITHOUT_FLOAT(%)
				}
			goto L_PUSH_TYPE;

			case ZRTOS_VM_OP__NOT:
				switch(io_type){
					ZRTOS_VM_OP_NOT(!)
				}
			goto L_PUSH_BOOL;
			case ZRTOS_VM_OP__EQ:
				switch(io_type){
					ZRTOS_VM_OP_BOOLEAN(==)
				}
			goto L_PUSH_BOOL;
			case ZRTOS_VM_OP__LT:
				switch(io_type){
					ZRTOS_VM_OP_BOOLEAN(<)
				}
			goto L_PUSH_BOOL;
			case ZRTOS_VM_OP__GT:
				switch(io_type){
					ZRTOS_VM_OP_BOOLEAN(>)
				}
			goto L_PUSH_BOOL;
			case ZRTOS_VM_OP__LE:
				switch(io_type){
					ZRTOS_VM_OP_BOOLEAN(<=)
				}
			goto L_PUSH_BOOL;
			case ZRTOS_VM_OP__GE:
				switch(io_type){
					ZRTOS_VM_OP_BOOLEAN(>=)
				}
			goto L_PUSH_BOOL;

			case ZRTOS_VM_OP__AND:
				a.value.u64 &= b.value.u64;
			goto L_PUSH_TPYE;
			case ZRTOS_VM_OP__OR:
				a.value.u64 |= b.value.u64;
			goto L_PUSH_TPYE;
			case ZRTOS_VM_OP__XOR:
				a.value.u64 ^= b.value.u64;
			goto L_PUSH_TPYE;
			case ZRTOS_VM_OP__NEG:
				a.value.u64 = ~a.value.u64;
			goto L_PUSH_TPYE;

			case ZRTOS_VM_OP__IF:
				if(!zrtos_stack__pop(stack,&tmp,sizeof(tmp.value.boolean))){
					goto L_EFAULT;
				}
				if(tmp.value.boolean){
					pc = a.value.pc;
					goto L_SET_PROGRAM_POS;
				}
			goto L_PUSH_NOTHING;
			case ZRTOS_VM_OP__IFELSE:
				if(!zrtos_stack__pop(stack,&tmp,sizeof(tmp.value.boolean))){
					goto L_EFAULT;
				}

				pc = tmp.value.boolean ? a.value.pc : b.value.pc;
			goto L_SET_PROGRAM_POS;

			case ZRTOS_VM_OP__ICALL:
				ret = zrtos_vm__icall(thiz,a.value.pc);
				if(ret != 0){
					goto L_END;
				}
			goto L_NOP;
			case ZRTOS_VM_OP__CALL:
				pc = a.value.pc;
			goto L_SET_PROGRAM_POS;
			case ZRTOS_VM_OP__RET:
				pc = a.value.pc;
			goto L_SET_PROGRAM_POS;
			case ZRTOS_VM_OP__SET_SP:
				zrtos_stack__set_pos(stack,a.value.pc);
			goto L_NEXT;
			case ZRTOS_VM_OP__NOP:
			goto L_NOP;
			case ZRTOS_VM_OP__END:
			goto L_END;
		}

		goto L_NOP;
		//store values
L_CAST:
		a.type = op - ZRTOS_VM_OP__CAST;
		goto L_PUSH_TPYE;
L_PUSH_BOOL:
		a.type = ZRTOS_VM_IO_TYPE__BOOLEAN;
L_PUSH_TPYE:
		if(!zrtos_stack__push(stack,&a,zrtos_vm_io_type__get_length(a.type))){
			goto L_EFAULT;
		}
		goto L_PUSH_NOTHING;
L_SET_PROGRAM_POS:
		zrtos_stack__set_pos(program,pc);
L_PUSH_NOTHING:
L_NEXT:
L_NOP:
		continue;
	}

L_EFAULT:
	ret = EFAULT;
L_END:
	return ret;
}


#ifdef __cplusplus
}
#endif
#endif