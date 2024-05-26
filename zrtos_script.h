/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_RUNTIME_H
#define ZRTOS_RUNTIME_H
#ifdef __cplusplus
extern "C" {
#endif

typedef enum{
	 ZRTOS_RUNTIME_OP_TYPE__INT8    = 0x00
	,ZRTOS_RUNTIME_OP_TYPE__INT16   = 0x01
	,ZRTOS_RUNTIME_OP_TYPE__INT32   = 0x02
	,ZRTOS_RUNTIME_OP_TYPE__INT64   = 0x03
	,ZRTOS_RUNTIME_OP_TYPE__UINT8   = 0x04
	,ZRTOS_RUNTIME_OP_TYPE__UINT16  = 0x05
	,ZRTOS_RUNTIME_OP_TYPE__UINT32  = 0x06
	,ZRTOS_RUNTIME_OP_TYPE__UINT64  = 0x07
	,ZRTOS_RUNTIME_OP_TYPE__FLOAT   = 0x08
	,ZRTOS_RUNTIME_OP_TYPE__DOUBLE  = 0x09
	,ZRTOS_RUNTIME_OP_TYPE__PTR     = 0x0A
	,ZRTOS_RUNTIME_OP_TYPE__BYTES   = 0x0B
	,ZRTOS_RUNTIME_OP_TYPE__BOOLEAN = 0x0C
}zrtos_runtime_op_type_t;

typedef enum{
	
	 ZRTOS_RUNTIME_OP__CALL         = 0x0E
	,ZRTOS_RUNTIME_OP__RET          = 0x0F
	,ZRTOS_RUNTIME_OP__PUSH    = 0x00
	,ZRTOS_RUNTIME_OP__POP     = 0x10
	,ZRTOS_RUNTIME_OP__LOAD    = 0x20
	,ZRTOS_RUNTIME_OP__STORE   = 0x30

	,ZRTOS_RUNTIME_OP__ADD     = 0x40
	,ZRTOS_RUNTIME_OP__SUB     = 0x50
	,ZRTOS_RUNTIME_OP__MUL     = 0x60
	,ZRTOS_RUNTIME_OP__DIV     = 0x70
	,ZRTOS_RUNTIME_OP__2D      = 0x80
	,ZRTOS_RUNTIME_OP__3D      = 0x90

	,ZRTOS_RUNTIME_OP__EQ      = 0xA0
	,ZRTOS_RUNTIME_OP__LT      = 0xB0
	,ZRTOS_RUNTIME_OP__GT      = 0xC0
	,ZRTOS_RUNTIME_OP__LE      = 0xD0
	,ZRTOS_RUNTIME_OP__GE      = 0xE0

	,ZRTOS_RUNTIME_OP__MOD     = 0x01F0

	,ZRTOS_RUNTIME_OP__AND     = 0x02F0
	,ZRTOS_RUNTIME_OP__OR      = 0x03F0
	,ZRTOS_RUNTIME_OP__XOR     = 0x04F0
	,ZRTOS_RUNTIME_OP__NEG     = 0x05F0
}zrtos_runtime_op_type_t;

typedef struct _zrtos_script_runtime_t{
	zrtos_stack_t stack;
	zrtos_stack_t program;
}zrtos_script_runtime_t;

typedef struct _zrtos_script_value_t{
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

		void     *ptr;
		uint8_t  *bytes;

		bool     boolean;
	}data;
	zrtos_runtime_op_type_t type;
}zrtos_script_value_t;

bool zrtos_script_runtime__run(zrtos_script_runtime_t *thiz){
	zrtos_script_value_t a;
	zrtos_script_value_t b;
	zrtos_runtime_op_type_t type = (op & 0x0F);

	switch(op & 0xF0){
		case ZRTOS_RUNTIME_OP__PUSH:
			switch(op & 0x0F){
				case ZRTOS_RUNTIME_OP_TYPE__BYTES:
				break;
				default:
				break;
			}
		break;
		case ZRTOS_RUNTIME_OP__POP:
			switch(op & 0x0F){
				case ZRTOS_RUNTIME_OP_TYPE__BYTES:
				break;
				default:
				break;
			}
		break;
		case ZRTOS_RUNTIME_OP__LOAD:
			switch(op & 0x0F){
				case ZRTOS_RUNTIME_OP_TYPE__BYTES:
				break;
				default:
				break;
			}
		break;
		case ZRTOS_RUNTIME_OP__STORE:
		
			switch(op & 0x0F){
				case ZRTOS_RUNTIME_OP_TYPE__BYTES:
				break;
				default:
				break;
			}
		break;
		case ZRTOS_RUNTIME_OP__EQ:
			a.value.type = ZRTOS_RUNTIME_OP_TYPE__BOOLEAN;

			if(ZRTOS_RUNTIME_OP_TYPE__INT8 >= type
			&& ZRTOS_RUNTIME_OP_TYPE__UINT64 <= type){
				a.value.boolean = a.value.s64 == b.value.s64;
			}else

			if(ZRTOS_RUNTIME_OP_TYPE__UINT8 >= type
			&& ZRTOS_RUNTIME_OP_TYPE__UINT64 <= type){
				a.value.boolean = a.value.u64 == b.value.u64;
			}else
			switch(op & 0x0F){
				case ZRTOS_RUNTIME_OP_TYPE__BYTES:
				break;
				default:
				break;
			}
		break;



		case ZRTOS_RUNTIME_OP__AND:
			a.value.u64 &= b.value.u64;
		break;
		case ZRTOS_RUNTIME_OP__OR:
			a.value.u64 |= b.value.u64;
		break;
		case ZRTOS_RUNTIME_OP__XOR:
			a.value.u64 ^= b.value.u64;
		break;
		case ZRTOS_RUNTIME_OP__NEG:
			a.value.u64 = ~a.value.u64;
		break;
		case ZRTOS_RUNTIME_OP__SHL:
			a.value.u64 <<= b.value.u8;
		break;
		case ZRTOS_RUNTIME_OP__SHR:
			a.value.u64 >>= b.value.u8;
		break; 
		case ZRTOS_RUNTIME_OP__ROR:
			a.value.u64 = (a.value.u64 & b.value.u64);
		break;
		case ZRTOS_RUNTIME_OP__ROL:
			a.value.u64 = (a.value.u64 & b.value.u64);
		break;
		case ZRTOS_RUNTIME_OP__CLZ:
			a.value.u64 = __builtin_clzll(a.value.u64);
		break;
		case ZRTOS_RUNTIME_OP__CTZ:
			a.value.u64 = __builtin_ctzll(a.value.u64);
		break;
		case ZRTOS_RUNTIME_OP__POPCNT:
			a.value.u64 = __builtin_popcountll(a.value.u64);
		break;
		case ZRTOS_RUNTIME_OP__FFS:
			a.value.u64 = (a.value.u64 & b.value.u64);
		break;
		case 0xF0:
		break;
	}
}

#if 0
bool interpret(Module *m) {
    uint8_t     *bytes = m->bytes;
    StackValue  *stack = m->stack;

    uint32_t     cur_pc;
    Block       *block;
    uint32_t     arg, val, fidx, tidx, cond, depth, count;
    uint32_t     flags, offset, addr;
    uint8_t     *maddr, *mem_end;
    //uint32_t    *depths;
    uint8_t      opcode;
    uint32_t     a, b, c; // I32 math
    uint64_t     d, e, f; // I64 math
    float        g, h, i; // F32 math
    double       j, k, l; // F64 math
    bool         overflow = false;

    while (m->pc < m->byte_count) {
        opcode = bytes[m->pc];
        cur_pc = m->pc;
        m->pc += 1;

        if (TRACE) {
            if (DEBUG) { dump_stacks(m); }
            info("    0x%x <0x%x/%s>\n", cur_pc, opcode, OPERATOR_INFO[opcode]);
        }

        switch (opcode) {

        //
        // Control flow operators
        //
        case 0x00:  // unreachable
            sprintf(exception, "%s", "unreachable");
            return false;
        case 0x01:  // nop
            continue;
        case 0x02:  // block
            read_LEB(bytes, &m->pc, 32);  // ignore block type
            if (m->csp >= CALLSTACK_SIZE) {
                sprintf(exception, "call stack exhausted");
                return false;
            }
            push_block(m, m->block_lookup[cur_pc], m->sp);
            continue;
        case 0x03:  // loop
            read_LEB(bytes, &m->pc, 32);  // ignore block type
            if (m->csp >= CALLSTACK_SIZE) {
                sprintf(exception, "call stack exhausted");
                return false;
            }
            push_block(m, m->block_lookup[cur_pc], m->sp);
            continue;
        case 0x04:  // if
            read_LEB(bytes, &m->pc, 32);  // ignore block type
            block = m->block_lookup[cur_pc];
            if (m->csp >= CALLSTACK_SIZE) {
                sprintf(exception, "call stack exhausted");
                return false;
            }
            push_block(m, block, m->sp);

            cond = stack[m->sp--].value.uint32;
            if (cond == 0) { // if false (I32)
                // branch to else block or after end of if
                if (block->else_addr == 0) {
                    // no else block, pop if block and skip end
                    m->csp -= 1;
                    m->pc = block->br_addr+1;
                } else {
                    m->pc = block->else_addr;
                }
            }
            // if true, keep going
            if (TRACE) {
                debug("      - cond: 0x%x jump to 0x%x, block: %s\n",
                       cond, m->pc, block_repr(block));
            }
            continue;
        case 0x05:  // else
            block = m->callstack[m->csp].block;
            m->pc = block->br_addr;
            if (TRACE) {
                debug("      - of %s jump to 0x%x\n", block_repr(block), m->pc);
            }
            continue;
        case 0x0b:  // end
            block = pop_block(m);
            if (block == NULL) {
                return false; // an exception (set by pop_block)
            }
            if (TRACE) { debug("      - of %s\n", block_repr(block)); }
            if (block->block_type == 0x00) { // Function
                if (TRACE) {
                 warn("  << fn0x%x(%d) %s = %s\n",
                      block->fidx, block->fidx,
                      block->export_name ? block->export_name : "",
                      block->type->result_count > 0 ?
                        value_repr(&m->stack[m->sp]) :
                        "_");
                }
                if (m->csp == -1) {
                    // Return to top-level
                    return true;
                } else {
                    // Keep going at return address
                }
            } else if (block->block_type == 0x01) { // init_expr
                return true;
            } else {  // Block
                // End of block/loop/if, keep going
            }
            continue;
        case 0x0c:  // br
            depth = read_LEB(bytes, &m->pc, 32);
            m->csp -= depth;
            // set to end for pop_block
            m->pc = m->callstack[m->csp].block->br_addr;
         //   if (TRACE) { debug("      - to: 0x%x\n", &m->pc); }
            if (TRACE) { debug("      - to: 0x%x\n", m->pc); }
            continue;
        case 0x0d:  // br_if
            depth = read_LEB(bytes, &m->pc, 32);

            cond = stack[m->sp--].value.uint32;
            if (cond) { // if true
                m->csp -= depth;
                // set to end for pop_block
                m->pc = m->callstack[m->csp].block->br_addr;
            }
            if (TRACE) { debug("      - depth: 0x%x, cond: 0x%x, to: 0x%x\n", depth, cond, m->pc); }
            continue;
        case 0x0e:  // br_table
            count = read_LEB(bytes, &m->pc, 32);
            if (count > BR_TABLE_SIZE) {
                // TODO: check this prior to runtime
                sprintf(exception, "br_table size %d exceeds max %d\n",
                        count, BR_TABLE_SIZE);
                return false;
            }
            for(uint32_t i=0; i<count; i++) {
                m->br_table[i] = read_LEB(bytes, &m->pc, 32);
            }
            depth = read_LEB(bytes, &m->pc, 32);

            int32_t didx = stack[m->sp--].value.int32;
            if (didx >= 0 && didx < (int32_t)count) {
                depth = m->br_table[didx];
            }

            m->csp -= depth;
            // set to end for pop_block
            m->pc = m->callstack[m->csp].block->br_addr;
            if (TRACE) {
                debug("      - count: %d, didx: %d, to: 0x%x\n", count, didx, m->pc);
            }
            continue;
        case 0x0f:  // return
            while (m->csp >= 0 &&
                   m->callstack[m->csp].block->block_type != 0x00) {
                m->csp--;
            }
            // Set the program count to the end of the function
            // The actual pop_block and return is handled by the end opcode.
            m->pc = m->callstack[0].block->end_addr;
            if (TRACE) {
                debug("      - to: 0x%x\n", m->pc);
            }
            continue;


        //
        // Call operators
        //
        case 0x10:  // call
            fidx = read_LEB(bytes, &m->pc, 32);

            if (fidx < m->import_count) {
                thunk_out(m, fidx);   // import/thunk call
            } else {
                if (m->csp >= CALLSTACK_SIZE) {
                    sprintf(exception, "call stack exhausted");
                    return false;
                }
                setup_call(m, fidx);  // regular function call
                if (TRACE) {
                    debug("      - calling function fidx: %d at: 0x%x\n", fidx, m->pc);
                }
            }
            continue;
        case 0x11:  // call_indirect
            tidx = read_LEB(bytes, &m->pc, 32); // TODO: use tidx?
            (void)tidx;
            read_LEB(bytes, &m->pc, 1); // reserved immediate
            val = stack[m->sp--].value.uint32;
            if (m->options.mangle_table_index) {
                // val is the table address + the index (not sized for the
                // pointer size) so get the actual (sized) index
                if (TRACE) {
                    debug("      - entries: %p, original val: 0x%x, new val: 0x%x\n",
                        m->table.entries, val, (uint32_t)m->table.entries - val);
                }
                //val = val - (uint32_t)((uint64_t)m->table.entries & 0xFFFFFFFF);
                val = val - (uint32_t)m->table.entries;
            }
            if (val >= m->table.maximum) {
                sprintf(exception, "undefined element 0x%x (max: 0x%x) in table",
                        val, m->table.maximum);
                return false;
            }

            fidx = m->table.entries[val];
            if (TRACE) {
                debug("       - call_indirect tidx: %d, val: 0x%x, fidx: 0x%x\n",
                      tidx, val, fidx);
            }

            if (fidx < m->import_count) {
                thunk_out(m, fidx);    // import/thunk call
            } else {
                Block *func = &m->functions[fidx];
                Type *ftype = func->type;

                if (m->csp >= CALLSTACK_SIZE) {
                    sprintf(exception, "call stack exhausted");
                    return false;
                }
                if (ftype->mask != m->types[tidx].mask) {
                    sprintf(exception, "indirect call type mismatch (call type and function type differ)");
                    return false;
                }

                setup_call(m, fidx);   // regular function call

                // Validate signatures match
                if (ftype->param_count + func->local_count != m->sp - m->fp + 1) {
                    sprintf(exception, "indirect call type mismatch (param counts differ)");
                    return false;
                }
                for (uint32_t f=0; f<ftype->param_count; f++) {
                    if (ftype->params[f] != m->stack[m->fp+f].value_type) {
                        sprintf(exception, "indirect call type mismatch (param types differ)");
                        return false;
                    }
                }

                if (TRACE) {
                    debug("      - tidx: %d, table idx: %d, "
                          "calling function fidx: %d at: 0x%x\n",
                        tidx, val, fidx, m->pc);
                }
            }
            continue;

        //
        // Parametric operators
        //
        case 0x1a:  // drop
            m->sp--;
            continue;
        case 0x1b:  // select
            cond = stack[m->sp--].value.uint32;
            m->sp--;
            if (!cond) {  // use a instead of b
                stack[m->sp] = stack[m->sp+1];
            }
            continue;


        //
        // Variable access
        //
        case 0x20:  // get_local
            arg = read_LEB(bytes, &m->pc, 32);
            if (TRACE) {
                debug("      - arg: 0x%x, got %s\n",
                       arg, value_repr(&stack[m->fp+arg]));
            }
            stack[++m->sp] = stack[m->fp+arg];
            continue;
        case 0x21:  // set_local
            arg = read_LEB(bytes, &m->pc, 32);
            stack[m->fp+arg] = stack[m->sp--];
            if (TRACE) {
                debug("      - arg: 0x%x, to %s\n",
                       arg, value_repr(&stack[m->sp]));
            }
            continue;
        case 0x22:  // tee_local
            arg = read_LEB(bytes, &m->pc, 32);
            stack[m->fp+arg] = stack[m->sp];
            if (TRACE) {
                debug("      - arg: 0x%x, to %s\n",
                       arg, value_repr(&stack[m->sp]));
            }
            continue;
        case 0x23:  // get_global
            arg = read_LEB(bytes, &m->pc, 32);
            if (TRACE) {
                debug("      - arg: 0x%x, got %s\n",
                       arg, value_repr(&m->globals[arg]));
            }
            stack[++m->sp] = m->globals[arg];
            continue;
        case 0x24:  // set_global
            arg = read_LEB(bytes, &m->pc, 32);
            m->globals[arg] = stack[m->sp--];
            if (TRACE) {
                debug("      - arg: 0x%x, to %s\n",
                       arg, value_repr(&m->globals[arg]));
            }
            continue;

        //
        // Memory-related operators
        //
        case 0x3f:  // current_memory
            read_LEB(bytes, &m->pc, 32); // ignore reserved
            stack[++m->sp].value_type = I32;
            stack[m->sp].value.uint32 = m->memory.pages;
            continue;
        case 0x40:  // grow_memory
            read_LEB(bytes, &m->pc, 32); // ignore reserved
            uint32_t prev_pages = m->memory.pages;
            uint32_t delta = stack[m->sp].value.uint32;
            stack[m->sp].value.uint32 = prev_pages;
            if (delta == 0) {
                continue; // No change
            } else if (delta+prev_pages > m->memory.maximum) {
                stack[m->sp].value.uint32 = -1;
                continue;
            }
            m->memory.pages += delta;
            m->memory.bytes = arecalloc(m->memory.bytes,
                                        prev_pages*PAGE_SIZE,
                                        m->memory.pages*PAGE_SIZE,
                                        sizeof(uint32_t),
                                        "grow_memory: Module->memory.bytes");
            continue;

        // Memory load operators
        case 0x28 ... 0x35:
            flags = read_LEB(bytes, &m->pc, 32);
            offset = read_LEB(bytes, &m->pc, 32);
            addr = stack[m->sp--].value.uint32;
            if (flags != 2 && TRACE) {
                info("      - unaligned load - flags: 0x%x,"
                      " offset: 0x%x, addr: 0x%x\n",
                      flags, offset, addr);
            }
            if (offset+addr < addr) { overflow = true; }
            maddr = m->memory.bytes+offset+addr;
            if (maddr < m->memory.bytes) { overflow = true; }
            mem_end = m->memory.bytes+m->memory.pages*(uint32_t)PAGE_SIZE;
            if (maddr+LOAD_SIZE[opcode-0x28] > mem_end) {
                overflow = true;
            }
            info("      - addr: 0x%x, offset: 0x%x, maddr: %p, mem_end: %p\n",
                 addr, offset, maddr, mem_end);
            if (!m->options.disable_memory_bounds) {
                if (overflow) {
                    warn("memory start: %p, memory end: %p, maddr: %p\n",
                        m->memory.bytes, mem_end, maddr);
                    sprintf(exception, "out of bounds memory access");
                    return false;
                }
            }
            stack[++m->sp].value.uint64 = 0; // initialize to 0
            switch (opcode) {
            case 0x28: memcpy(&stack[m->sp].value, maddr, 4);
                       stack[m->sp].value_type = I32; break; // i32.load
            case 0x29: memcpy(&stack[m->sp].value, maddr, 8);
                       stack[m->sp].value_type = I64; break; // i64.load
            case 0x2a: memcpy(&stack[m->sp].value, maddr, 4);
                       stack[m->sp].value_type = F32; break; // f32.load
            case 0x2b: memcpy(&stack[m->sp].value, maddr, 8);
                       stack[m->sp].value_type = F64; break; // f64.load
            case 0x2c: memcpy(&stack[m->sp].value, maddr, 1);
                       sext_8_32(&stack[m->sp].value.uint32);
                       stack[m->sp].value_type = I32;
                       break; // i32.load8_s
            case 0x2d: memcpy(&stack[m->sp].value, maddr, 1);
                       stack[m->sp].value_type = I32; break; // i32.load8_u
            case 0x2e: memcpy(&stack[m->sp].value, maddr, 2);
                       sext_16_32(&stack[m->sp].value.uint32);
                       stack[m->sp].value_type = I32; break; // i32.load16_s
            case 0x2f: memcpy(&stack[m->sp].value, maddr, 2);
                       stack[m->sp].value_type = I32; break; // i32.load16_u
            case 0x30: memcpy(&stack[m->sp].value, maddr, 1);
                       sext_8_64(&stack[m->sp].value.uint64);
                       stack[m->sp].value_type = I64; break; // i64.load8_s
            case 0x31: memcpy(&stack[m->sp].value, maddr, 1);
                       stack[m->sp].value_type = I64; break; // i64.load8_u
            case 0x32: memcpy(&stack[m->sp].value, maddr, 2);
                       sext_16_64(&stack[m->sp].value.uint64);
                       stack[m->sp].value_type = I64; break; // i64.load16_s
            case 0x33: memcpy(&stack[m->sp].value, maddr, 2);
                       stack[m->sp].value_type = I64; break; // i64.load16_u
            case 0x34: memcpy(&stack[m->sp].value, maddr, 4);
                       sext_32_64(&stack[m->sp].value.uint64);
                       stack[m->sp].value_type = I64; break; // i64.load32_s
            case 0x35: memcpy(&stack[m->sp].value, maddr, 4);
                       stack[m->sp].value_type = I64; break; // i64.load32_u
            }
            continue;

        // Memory store operators
        case 0x36 ... 0x3e:
            flags = read_LEB(bytes, &m->pc, 32);
            offset = read_LEB(bytes, &m->pc, 32);
            StackValue *sval = &stack[m->sp--];
            addr = stack[m->sp--].value.uint32;
            if (flags != 2 && TRACE) {
                info("      - unaligned store - flags: 0x%x,"
                      " offset: 0x%x, addr: 0x%x, val: %s\n",
                      flags, offset, addr, value_repr(sval));
            }
            if (offset+addr < addr) { overflow = true; }
            maddr = m->memory.bytes+offset+addr;
            if (maddr < m->memory.bytes) { overflow = true; }
            mem_end = m->memory.bytes+m->memory.pages*(uint32_t)PAGE_SIZE;
            if (maddr+LOAD_SIZE[opcode-0x28] > mem_end) {
                overflow = true;
            }
            info("      - addr: 0x%x, offset: 0x%x, maddr: %p, mem_end: %p, value: %s\n",
                 addr, offset, maddr, mem_end, value_repr(sval));
            if (!m->options.disable_memory_bounds) {
                if (overflow) {
                    warn("memory start: %p, memory end: %p, maddr: %p\n",
                        m->memory.bytes, mem_end, maddr);
                    sprintf(exception, "out of bounds memory access");
                    return false;
                }
            }
            switch (opcode) {
            case 0x36: memcpy(maddr, &sval->value.uint32, 4); break; // i32.store
            case 0x37: memcpy(maddr, &sval->value.uint64, 8); break; // i64.store
            case 0x38: memcpy(maddr, &sval->value.f32, 4); break;    // f32.store
            case 0x39: memcpy(maddr, &sval->value.f64, 8); break;    // f64.store
            case 0x3a: memcpy(maddr, &sval->value.uint32, 1); break; // i32.store8
            case 0x3b: memcpy(maddr, &sval->value.uint32, 2); break; // i32.store16
            case 0x3c: memcpy(maddr, &sval->value.uint64, 1); break; // i64.store8
            case 0x3d: memcpy(maddr, &sval->value.uint64, 2); break; // i64.store16
            case 0x3e: memcpy(maddr, &sval->value.uint64, 4); break; // i64.store32
            }
            continue;

        //
        // Constants
        //
        case 0x41:  // i32.const
            stack[++m->sp].value_type = I32;
            stack[m->sp].value.uint32 = read_LEB_signed(bytes, &m->pc, 32);
            continue;
        case 0x42:  // i64.const
            stack[++m->sp].value_type = I64;
            stack[m->sp].value.int64 = read_LEB_signed(bytes, &m->pc, 64);
            continue;
        case 0x43:  // f32.const
            stack[++m->sp].value_type = F32;
            memcpy(&stack[m->sp].value.uint32, bytes+m->pc, 4);
            m->pc += 4;
            //stack[m->sp].value.uint32 = read_LEB_signed(bytes, pm->c, 32);
            continue;
        case 0x44:  // f64.const
            stack[++m->sp].value_type = F64;
            memcpy(&stack[m->sp].value.uint64, bytes+m->pc, 8);
            m->pc += 8;
            //stack[m->sp].value.uint64 = read_LEB_signed(bytes, m->pc, 64);
            continue;

        //
        // Comparison operators
        //

        // unary
        case 0x45:  // i32.eqz
            stack[m->sp].value.uint32 = stack[m->sp].value.uint32 == 0;
            continue;
        case 0x50:  // i64.eqz
            stack[m->sp].value_type = I32;
            stack[m->sp].value.uint32 = stack[m->sp].value.uint64 == 0;
            continue;

        // i32 binary
        case 0x46 ... 0x4f:
            a = stack[m->sp-1].value.uint32;
            b = stack[m->sp].value.uint32;
            m->sp -= 1;
            switch (opcode) {
            case 0x46: c = a == b; break;  // i32.eq
            case 0x47: c = a != b; break;  // i32.ne
            case 0x48: c = (int32_t)a <  (int32_t)b; break;  // i32.lt_s
            case 0x49: c = a <  b; break;  // i32.lt_u
            case 0x4a: c = (int32_t)a >  (int32_t)b; break;  // i32.gt_s
            case 0x4b: c = a >  b; break;  // i32.gt_u
            case 0x4c: c = (int32_t)a <= (int32_t)b; break;  // i32.le_s
            case 0x4d: c = a <= b; break;  // i32.le_u
            case 0x4e: c = (int32_t)a >= (int32_t)b; break;  // i32.ge_s
            case 0x4f: c = a >= b; break;  // i32.ge_u
            }
            stack[m->sp].value_type = I32;
            stack[m->sp].value.uint32 = c;
            continue;
        case 0x51 ... 0x5a:
            d = stack[m->sp-1].value.uint64;
            e = stack[m->sp].value.uint64;
            m->sp -= 1;
            switch (opcode) {
            case 0x51: c = d == e; break;  // i64.eq
            case 0x52: c = d != e; break;  // i64.ne
            case 0x53: c = (int64_t)d <  (int64_t)e; break;  // i64.lt_s
            case 0x54: c = d <  e; break;  // i64.lt_u
            case 0x55: c = (int64_t)d >  (int64_t)e; break;  // i64.gt_s
            case 0x56: c = d >  e; break;  // i64.gt_u
            case 0x57: c = (int64_t)d <= (int64_t)e; break;  // i64.le_s
            case 0x58: c = d <= e; break;  // i64.le_u
            case 0x59: c = (int64_t)d >= (int64_t)e; break;  // i64.ge_s
            case 0x5a: c = d >= e; break;  // i64.ge_u
            }
            stack[m->sp].value_type = I32;
            stack[m->sp].value.uint32 = c;
            continue;
        case 0x5b ... 0x60:
            g = stack[m->sp-1].value.f32;
            h = stack[m->sp].value.f32;
            m->sp -= 1;
            switch (opcode) {
            case 0x5b: c = g == h; break;  // f32.eq
            case 0x5c: c = g != h; break;  // f32.ne
            case 0x5d: c = g <  h; break;  // f32.lt
            case 0x5e: c = g >  h; break;  // f32.gt
            case 0x5f: c = g <= h; break;  // f32.le
            case 0x60: c = g >= h; break;  // f32.ge
            }
            stack[m->sp].value_type = I32;
            stack[m->sp].value.uint32 = c;
            continue;
        case 0x61 ... 0x66:
            j = stack[m->sp-1].value.f64;
            k = stack[m->sp].value.f64;
            m->sp -= 1;
            switch (opcode) {
            case 0x61: c = j == k; break;  // f64.eq
            case 0x62: c = j != k; break;  // f64.ne
            case 0x63: c = j <  k; break;  // f64.lt
            case 0x64: c = j >  k; break;  // f64.gt
            case 0x65: c = j <= k; break;  // f64.le
            case 0x66: c = j >= k; break;  // f64.ge
            }
            stack[m->sp].value_type = I32;
            stack[m->sp].value.uint32 = c;
            continue;

        //
        // Numeric operators
        //

        // unary i32
        case 0x67 ... 0x69:
            a = stack[m->sp].value.uint32;
            switch (opcode) {
            case 0x67: c = a==0 ? 32 : __builtin_clz(a); break; // i32.clz
            case 0x68: c = a==0 ? 32 : __builtin_ctz(a); break; // i32.ctz
            case 0x69: c = __builtin_popcount(a); break;        // i32.popcnt
            }
            stack[m->sp].value.uint32 = c;
            continue;

        // unary i64
        case 0x79 ... 0x7b:
            d = stack[m->sp].value.uint64;
            switch (opcode) {
            case 0x79: f = d==0 ? 64 : __builtin_clzll(d); break; // i64.clz
            case 0x7a: f = d==0 ? 64 : __builtin_ctzll(d); break; // i64.ctz
            case 0x7b: f = __builtin_popcountll(d); break;        // i64.popcnt
            }
            stack[m->sp].value.uint64 = f;
            continue;

        // unary f32
        case 0x8b: stack[m->sp].value.f32
                   = fabs(stack[m->sp].value.f32); break;  // f32.abs
        case 0x8c: stack[m->sp].value.f32
                   = -stack[m->sp].value.f32; break;       // f32.neg
        case 0x8d: stack[m->sp].value.f32
                   = ceil(stack[m->sp].value.f32); break;  // f32.ceil
        case 0x8e: stack[m->sp].value.f32
                   = floor(stack[m->sp].value.f32); break; // f32.floor
        case 0x8f: stack[m->sp].value.f32
                   = trunc(stack[m->sp].value.f32); break; // f32.trunc
        case 0x90: stack[m->sp].value.f32
                   = rint(stack[m->sp].value.f32); break; // f32.nearest
        case 0x91: stack[m->sp].value.f32
                   = sqrt(stack[m->sp].value.f32); break;  // f32.sqrt

        // unary f64
        case 0x99: stack[m->sp].value.f64
                   = fabs(stack[m->sp].value.f64); break;  // f64.abs
        case 0x9a: stack[m->sp].value.f64
                   = -stack[m->sp].value.f64; break;       // f64.neg
        case 0x9b: stack[m->sp].value.f64
                   = ceil(stack[m->sp].value.f64); break;  // f64.ceil
        case 0x9c: stack[m->sp].value.f64
                   = floor(stack[m->sp].value.f64); break; // f64.floor
        case 0x9d: stack[m->sp].value.f64
                   = trunc(stack[m->sp].value.f64); break; // f64.trunc
        case 0x9e: stack[m->sp].value.f64
                   = rint(stack[m->sp].value.f64); break; // f64.nearest
        case 0x9f: stack[m->sp].value.f64
                   = sqrt(stack[m->sp].value.f64); break;  // f64.sqrt

        // i32 binary
        case 0x6a ... 0x78:
            a = stack[m->sp-1].value.uint32;
            b = stack[m->sp].value.uint32;
            m->sp -= 1;
            if (opcode >= 0x6d && opcode <= 0x70 && b == 0) {
                sprintf(exception, "integer divide by zero");
                return false;
            }
            switch (opcode) {
            //case 0x6a: o = __builtin_add_overflow(a, b, &c); break;  // i32.add
            //case 0x6b: o = __builtin_sub_overflow(a, b, &c); break;  // i32.sub
            case 0x6a: c = a + b; break;  // i32.add
            case 0x6b: c = a - b; break;  // i32.sub
            case 0x6c: c = a * b; break;  // i32.mul
            case 0x6d: if (a == 0x80000000 && b == -1) {
                           sprintf(exception, "integer overflow");
                           return false;
                       }
                       c = (int32_t)a / (int32_t)b; break;  // i32.div_s
            case 0x6e: c = a / b; break;  // i32.div_u
            case 0x6f: if (a == 0x80000000 && b == -1) {
                           c = 0;
                       } else {
                           c = (int32_t)a % (int32_t)b;
                       }; break;  // i32.rem_s
            case 0x70: c = a % b; break;  // i32.rem_u
            case 0x71: c = a & b; break;  // i32.and
            case 0x72: c = a | b; break;  // i32.or
            case 0x73: c = a ^ b; break;  // i32.xor
            case 0x74: c = a << b; break; // i32.shl
            case 0x75: c = (int32_t)a >> b; break; // i32.shr_s
            case 0x76: c = a >> b; break; // i32.shr_u
            case 0x77: c = rotl32(a, b); break; // i32.rotl
            case 0x78: c = rotr32(a, b); break; // i32.rotr
            }
            //if (o == 1) {
            //    sprintf(exception, "integer overflow");
            //    return false;
            //}
            stack[m->sp].value.uint32 = c;
            continue;

        // i64 binary
        case 0x7c ... 0x8a:
            d = stack[m->sp-1].value.uint64;
            e = stack[m->sp].value.uint64;
            m->sp -= 1;
            if (opcode >= 0x7f && opcode <= 0x82 && e == 0) {
                sprintf(exception, "integer divide by zero");
                return false;
            }
            switch (opcode) {
            case 0x7c: f = d + e; break;  // i64.add
            case 0x7d: f = d - e; break;  // i64.sub
            case 0x7e: f = d * e; break;  // i64.mul
            case 0x7f: if (d == 0x8000000000000000 && e == -1) {
                           sprintf(exception, "integer overflow");
                           return false;
                       }
                       f = (int64_t)d / (int64_t)e; break;  // i64.div_s
            case 0x80: f = d / e; break;  // i64.div_u
            case 0x81: if (d == 0x8000000000000000 && e == -1) {
                           f = 0;
                       } else {
                           f = (int64_t)d % (int64_t)e;
                       }
                       break;  // i64.rem_s
            case 0x82: f = d % e; break;  // i64.rem_u
            case 0x83: f = d & e; break;  // i64.and
            case 0x84: f = d | e; break;  // i64.or
            case 0x85: f = d ^ e; break;  // i64.xor
            case 0x86: f = d << e; break; // i64.shl
            case 0x87: f = ((int64_t)d) >> e; break; // i64.shr_s
            case 0x88: f = d >> e; break; // i64.shr_u
            case 0x89: f = rotl64(d, e); break; // i64.rotl
            case 0x8a: f = rotr64(d, e); break; // i64.rotr
            }
            stack[m->sp].value.uint64 = f;
            continue;

        // f32 binary
        case 0x92 ... 0x98:
            g = stack[m->sp-1].value.f32;
            h = stack[m->sp].value.f32;
            m->sp -= 1;
            switch (opcode) {
            case 0x92: i = g + h; break;  // f32.add
            case 0x93: i = g - h; break;  // f32.sub
            case 0x94: i = g * h; break;  // f32.mul
            case 0x95: i = g / h; break;  // f32.div
            case 0x96: i = wa_fmin(g, h); break;  // f32.min
            case 0x97: i = wa_fmax(g, h); break;  // f32.max
            case 0x98: i = signbit(h) ? -fabs(g) : fabs(g); break;  // f32.copysign
            }
            stack[m->sp].value.f32 = i;
            continue;

        // f64 binary
        case 0xa0 ... 0xa6:
            j = stack[m->sp-1].value.f64;
            k = stack[m->sp].value.f64;
            m->sp -= 1;
            switch (opcode) {
            case 0xa0: l = j + k; break;  // f64.add
            case 0xa1: l = j - k; break;  // f64.sub
            case 0xa2: l = j * k; break;  // f64.mul
            case 0xa3: l = j / k; break;  // f64.div
            case 0xa4: l = wa_fmin(j, k); break;  // f64.min
            case 0xa5: l = wa_fmax(j, k); break;  // f64.max
            case 0xa6: l = signbit(k) ? -fabs(j) : fabs(j); break;  // f64.copysign
            }
            stack[m->sp].value.f64 = l;
            continue;

        // conversion operations
        //case 0xa7 ... 0xbb:
        case 0xa7: stack[m->sp].value.uint64 &= 0x00000000ffffffff;
                   stack[m->sp].value_type = I32; break;  // i32.wrap/i64
        case 0xa8: if (isnan(stack[m->sp].value.f32)) {
                       sprintf(exception, "invalid conversion to integer");
                       return false;
                   } else if (stack[m->sp].value.f32 >= INT32_MAX ||
                              stack[m->sp].value.f32 < INT32_MIN) {
                       sprintf(exception, "integer overflow");
                       return false;
                   }
                   stack[m->sp].value.int32 = stack[m->sp].value.f32;
                   stack[m->sp].value_type = I32; break;  // i32.trunc_s/f32
        case 0xa9: if (isnan(stack[m->sp].value.f32)) {
                       sprintf(exception, "invalid conversion to integer");
                       return false;
                   } else if (stack[m->sp].value.f32 >= UINT32_MAX ||
                              stack[m->sp].value.f32 <= -1) {
                       sprintf(exception, "integer overflow");
                       return false;
                   }
                   stack[m->sp].value.uint32 = stack[m->sp].value.f32;
                   stack[m->sp].value_type = I32; break;  // i32.trunc_u/f32
        case 0xaa: if (isnan(stack[m->sp].value.f64)) {
                       sprintf(exception, "invalid conversion to integer");
                       return false;
                   } else if (stack[m->sp].value.f64 > INT32_MAX ||
                              stack[m->sp].value.f64 < INT32_MIN) {
                       sprintf(exception, "integer overflow");
                       return false;
                   }
                   stack[m->sp].value.int32 = stack[m->sp].value.f64;
                   stack[m->sp].value_type = I32; break;  // i32.trunc_s/f64
        case 0xab: if (isnan(stack[m->sp].value.f64)) {
                       sprintf(exception, "invalid conversion to integer");
                       return false;
                   } else if (stack[m->sp].value.f64 > UINT32_MAX ||
                              stack[m->sp].value.f64 <= -1) {
                       sprintf(exception, "integer overflow");
                       return false;
                   }
                   stack[m->sp].value.uint32 = stack[m->sp].value.f64;
                   stack[m->sp].value_type = I32; break;  // i32.trunc_u/f64
        case 0xac: stack[m->sp].value.uint64 = stack[m->sp].value.uint32;
                   sext_32_64(&stack[m->sp].value.uint64);
                   stack[m->sp].value_type = I64; break;  // i64.extend_s/i32
        case 0xad: stack[m->sp].value.uint64 = stack[m->sp].value.uint32;
                   stack[m->sp].value_type = I64; break;  // i64.extend_u/i32
        case 0xae: if (isnan(stack[m->sp].value.f32)) {
                       sprintf(exception, "invalid conversion to integer");
                       return false;
                   } else if (stack[m->sp].value.f32 >= INT64_MAX ||
                              stack[m->sp].value.f32 < INT64_MIN) {
                       sprintf(exception, "integer overflow");
                       return false;
                   }
                   stack[m->sp].value.int64 = stack[m->sp].value.f32;
                   stack[m->sp].value_type = I64; break;  // i64.trunc_s/f32
        case 0xaf: if (isnan(stack[m->sp].value.f32)) {
                       sprintf(exception, "invalid conversion to integer");
                       return false;
                   } else if (stack[m->sp].value.f32 >= UINT64_MAX ||
                              stack[m->sp].value.f32 <= -1) {
                       sprintf(exception, "integer overflow");
                       return false;
                   }
                   stack[m->sp].value.uint64 = stack[m->sp].value.f32;
                   stack[m->sp].value_type = I64; break;  // i64.trunc_u/f32
        case 0xb0: if (isnan(stack[m->sp].value.f64)) {
                       sprintf(exception, "invalid conversion to integer");
                       return false;
                   } else if (stack[m->sp].value.f64 >= INT64_MAX ||
                              stack[m->sp].value.f64 < INT64_MIN) {
                       sprintf(exception, "integer overflow");
                       return false;
                   }
                   stack[m->sp].value.int64 = stack[m->sp].value.f64;
                   stack[m->sp].value_type = I64; break;  // i64.trunc_s/f64
        case 0xb1: if (isnan(stack[m->sp].value.f64)) {
                       sprintf(exception, "invalid conversion to integer");
                       return false;
                   } else if (stack[m->sp].value.f64 >= UINT64_MAX ||
                              stack[m->sp].value.f64 <= -1) {
                       sprintf(exception, "integer overflow");
                       return false;
                   }
                   stack[m->sp].value.uint64 = stack[m->sp].value.f64;
                   stack[m->sp].value_type = I64; break;  // i64.trunc_u/f64
        case 0xb2: stack[m->sp].value.f32 = stack[m->sp].value.int32;
                   stack[m->sp].value_type = F32; break;  // f32.convert_s/i32
        case 0xb3: stack[m->sp].value.f32 = stack[m->sp].value.uint32;
                   stack[m->sp].value_type = F32; break;  // f32.convert_u/i32
        case 0xb4: stack[m->sp].value.f32 = stack[m->sp].value.int64;
                   stack[m->sp].value_type = F32; break;  // f32.convert_s/i64
        case 0xb5: stack[m->sp].value.f32 = stack[m->sp].value.uint64;
                   stack[m->sp].value_type = F32; break;  // f32.convert_u/i64
        case 0xb6: stack[m->sp].value.f32 = stack[m->sp].value.f64;
                   stack[m->sp].value_type = F32; break;  // f32.demote/f64
        case 0xb7: stack[m->sp].value.f64 = stack[m->sp].value.int32;
                   stack[m->sp].value_type = F64; break;  // f64.convert_s/i32
        case 0xb8: stack[m->sp].value.f64 = stack[m->sp].value.uint32;
                   stack[m->sp].value_type = F64; break;  // f64.convert_u/i32
        case 0xb9: stack[m->sp].value.f64 = stack[m->sp].value.int64;
                   stack[m->sp].value_type = F64; break;  // f64.convert_s/i64
        case 0xba: stack[m->sp].value.f64 = stack[m->sp].value.uint64;
                   stack[m->sp].value_type = F64; break;  // f64.convert_u/i64
        case 0xbb: stack[m->sp].value.f64 = stack[m->sp].value.f32;
                   stack[m->sp].value_type = F64; break;  // f64.promote/f32

        // reinterpretations
        case 0xbc: stack[m->sp].value_type = I32; break;  // i32.reinterpret/f32
        case 0xbd: stack[m->sp].value_type = I64; break;  // i64.reinterpret/f64
        case 0xbe: //memmove(&stack[m->sp].value.f32, &stack[m->sp].value.uint32, 4);
                   stack[m->sp].value_type = F32; break;  // f32.reinterpret/i32
        case 0xbf: stack[m->sp].value_type = F64; break;  // f64.reinterpret/i64

        default:
            sprintf(exception, "unrecognized opcode 0x%x", opcode);
            return false;
        }
    }
    return false; // We shouldn't reach here
}

#endif

#ifdef __cplusplus
}
#endif
#endif