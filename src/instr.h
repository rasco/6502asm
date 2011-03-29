        case OP_BRK:
        	PUSH((pc >> 8));
			PUSH((pc & 0xFF));
			
			st_brk = 1;
			
			B = ((st_carry) | (st_zero << 1) | (st_int << 2) | (st_dec << 3)
				| (st_brk << 4) | (1 << 5) | (st_overflow << 6) | (st_neg << 7));
			PUSH(B);
			
			W = 0;
			W = readmem(0xFFFE);
			W = W | (readmem(0xFFFF) << 8);
			
			printf("\nINT (BRK)\npc:%x\nW:%x\n", pc, W);
			pc = W;
        	break;
        	
		case OP_ADC_IMM:
			read_imm(B);
			op_ADC(B);
			break;
		
		case OP_ADC_ZP:
			read_zp(B);
			op_ADC(B);
			break;
		
		case OP_ADC_ZPX:
			read_zpx(B);
			op_ADC(B);
			break;
		
		case OP_ADC_ABS:
			read_abs(B);
			op_ADC(B);
			break;
		
		case OP_ADC_ABX:
			read_abx(B);
			op_ADC(B);
			break;
		
		case OP_ADC_ABY:
			read_aby(B);
			op_ADC(B);
			break;
			
		case OP_ADC_INX:
			read_inx(B);
			op_ADC(B);
			break;
		
		case OP_ADC_INY:
			read_iny(B);
			op_ADC(B);
			break;
		
		case OP_AND_IMM:
			get1bytevalue(src);
			reg_a &= src;
			SET_SIGN(reg_a);
			SET_ZERO(reg_a);
			break;
		
		case OP_AND_ZP:
			get1bytevalue(src);
			src = readmem(src);
			reg_a &= src;
			SET_SIGN(reg_a);
			SET_ZERO(reg_a);
			break;
		
		case OP_AND_ZPX:
			getaddr_zpx(W);
			B = readmem(W);
			reg_a &= B;
			SET_SIGN(reg_a);
			SET_ZERO(reg_a);
			break;
		
		case OP_AND_ABS:
			getaddr_abs(W);
			B = readmem(W);
			reg_a &= B;
			SET_SIGN(reg_a);
			SET_ZERO(reg_a);
			break;
		
		case OP_AND_ABX:
			getaddr_abx(W);
			B = readmem(W);
			reg_a &= B;
			SET_SIGN(reg_a);
			SET_ZERO(reg_a);
			break;
		
		case OP_AND_ABY:
			getaddr_aby(W);
			B = readmem(W);
			reg_a &= B;
			SET_SIGN(reg_a);
			SET_ZERO(reg_a);
			break;
		
		case OP_AND_INX:
			getaddr_inx(W);
			B = readmem(W);
			reg_a &= B;
			SET_SIGN(reg_a);
			SET_ZERO(reg_a);
			break;
		
		case OP_AND_INY:
			getaddr_iny(W);
			B = readmem(W);
			reg_a &= B;
			SET_SIGN(reg_a);
			SET_ZERO(reg_a);
			break;
		
		case OP_ASL_A:
			op_ASL(reg_a);
			break;
		
		case OP_ASL_ZP:
			cmd_zp(op_ASL);
			break;
		
		case OP_ASL_ZPX:
			cmd_zpx(op_ASL);
			break;
		
		case OP_ASL_ABS:
			cmd_abs(op_ASL);
			break;
		
		case OP_ASL_ABX:
			cmd_abx(op_ASL);
			break;
		
		case OP_BCC:
			if ( st_carry == 0 )
				pc = pc + (signed char)(readmem(pc))+1;
			else
				pc++;
			break;
		
		case OP_BCS:
			if ( st_carry == 1 )
				pc = pc + (signed char)(readmem(pc))+1;
			else
				pc++;
			break;
		
		case OP_BEQ:
			if ( st_zero == 1 )
				pc = pc + (signed char)(readmem(pc))+1;
			else
				pc++;
			break;
		
		case OP_BIT_ZP:
			read_zp(B);
			op_BIT(B);
			break;
		
		case OP_BIT_ABS:
			read_abs(B);
			op_BIT(B);
			break;
		
		case OP_BMI:
			if ( st_neg == 1 )
				pc = pc + (signed char)(readmem(pc))+1;
			else
				pc++;
			break;
		
		case OP_BNE:
			if ( st_zero == 0 )
				pc = pc + (signed char)(readmem(pc))+1;
			else
				pc++;
			break;
		
		case OP_BPL:
			if ( st_neg == 0 )
				pc = pc + (signed char)(readmem(pc))+1;
			else
				pc++;
			break;
		
		case OP_BVS:
			if ( st_overflow == 1 )
				pc = pc + (signed char)(readmem(pc))+1;
			else
				pc++;
			break;
		
		case OP_CLC:
			SET_CARRY(0);
			break;
		
		case OP_CLD:
			st_dec = 1;
			break;
		
		case OP_CLI:
			st_int = 0;
			break;
		
		case OP_CLV:
			SET_OVERFLOW(0);
			break;
		
		case OP_CMP_IMM:
			read_imm(W);
			op_CMP(W);
			break;
		
		case OP_CMP_ZP:
			read_zp(W);
			op_CMP(W);
			break;
		
		case OP_CMP_ZPX:
			read_zpx(W);
			op_CMP(W);
			break;
		
		case OP_CMP_ABS:
			read_abs(W);
			op_CMP(W);
			break;
		
		case OP_CMP_ABX:
			read_abx(W);
			op_CMP(W);
			break;
		
		case OP_CMP_ABY:
			read_aby(W);
			op_CMP(W);
			break;
		
		case OP_CMP_INX:
			read_inx(W);
			op_CMP(W);
			break;
		
		case OP_CMP_INY:
			read_iny(W);
			op_CMP(W);
			break;
		
		case OP_CPX_IMM:
			read_imm(B);
			src = reg_x - B;
			SET_CARRY(src < 0x100);
			SET_SIGN(src);
			SET_ZERO(src & 0xff);
			break;
		
		case OP_CPX_ZP:
			read_imm(B);
			src = reg_x - B;
			SET_CARRY(src < 0x100);
			SET_SIGN(src);
			SET_ZERO(src & 0xff);
			break;
		
		case OP_CPX_ABS:
			read_imm(B);
			src = reg_x - B;
			SET_CARRY(src < 0x100);
			SET_SIGN(src);
			SET_ZERO(src & 0xff);
			break;
		
		case OP_CPY_IMM:
			read_imm(B);
			src = reg_y - B;
			SET_CARRY(src < 0x100);
			SET_SIGN(src);
			SET_ZERO(src & 0xff);
			break;
		
		case OP_CPY_ZP:
			read_imm(B);
			src = reg_y - B;
			SET_CARRY(src < 0x100);
			SET_SIGN(src);
			SET_ZERO(src & 0xff);
			break;
		
		case OP_CPY_ABS:
			read_imm(B);
			src = reg_y - B;
			SET_CARRY(src < 0x100);
			SET_SIGN(src);
			SET_ZERO(src & 0xff);
			break;
		
		case OP_DEC_ZP:
			cmd_zp(op_DEC);
			break;
		
		case OP_DEC_ZPX:
			cmd_zpx(op_DEC);
			break;
		
		case OP_DEC_ABS:
			cmd_abs(op_DEC);
			break;
		
		case OP_DEC_ABX:
			cmd_abx(op_DEC);
			break;
		
		case OP_DEX:
			reg_x--;
			SET_ZERO(reg_x);
			SET_SIGN(reg_x);
			break;
		
		case OP_DEY:
			reg_y--;
			SET_ZERO(reg_y);
			SET_SIGN(reg_y);
			break;
		
		case OP_EOR_IMM:
			read_imm(B);
			op_EOR(B);
			break;
		
		case OP_EOR_ZP:
			read_zp(B);
			op_EOR(B);
			break;
		
		case OP_EOR_ZPX:
			read_zpx(B);
			op_EOR(B);
			break;
		
		case OP_EOR_ABS:
			read_abs(B);
			op_EOR(B);
			break;
			
		case OP_EOR_ABX:
			read_abx(B);
			op_EOR(B);
			break;
			
		case OP_EOR_ABY:
			read_aby(B);
			op_EOR(B);
			break;
		
		case OP_EOR_INX:
			read_inx(B);
			op_EOR(B);
			break;
		
		case OP_EOR_INY:
			read_iny(B);
			op_EOR(B);
			break;
		
		case OP_INC_ZP:
			cmd_zp(op_INC);
			break;
		
		case OP_INC_ZPX:
			cmd_zpx(op_INC);
			break;
		
		case OP_INC_ABS:
			cmd_abs(op_INC);
			break;
		
		case OP_INC_ABX:
			cmd_abx(op_INC);
			break;
		
		case OP_INX:
			reg_x++;
			SET_SIGN(reg_x);
			SET_ZERO(reg_x);
			break;
		
		case OP_INY:
			reg_y++;
			SET_SIGN(reg_y);
			SET_ZERO(reg_y);
			break;
		
		case OP_JMP_ABS:
			getaddr_abs(W);
			pc = W;
			break;
		
		case OP_JMP_IND:
			getaddr_ind(W);
			pc = W;
			break;
		
		case OP_JSR:
			get2bytevalue(src);
			pc--;
			PUSH((pc >> 8));
			PUSH((pc & 0xFF));
			if ( cpu.verbose == 1 ) 
				printf("JSR: new pc: %x, old pc: %x\n", src, pc);
			pc = src;
			break;
		
		case OP_LDA_IMM:
			read_imm(B);
			op_LDA(B);
			break;
		
		case OP_LDA_ZP:
			read_zp(B);
			op_LDA(B);
			break;
		
		case OP_LDA_ZPX:
			read_zpx(B);
			op_LDA(B);
			break;
		
		case OP_LDA_ABS:
			read_abs(B);
			op_LDA(B);
			break;
		
		case OP_LDA_ABX:
			read_abx(B);
			op_LDA(B);
			break;
		
		case OP_LDA_ABY:
			read_aby(B);
			op_LDA(B);
			break;
		
		case OP_LDA_INX:
			read_inx(B);
			op_LDA(B);
			break;
		
		case OP_LDA_INY:
			read_iny(B);
			op_LDA(B);
			break;
		
		case OP_LDX_IMM:
			read_imm(B);
			op_LDX(B);
			break;
		
		case OP_LDX_ZP:
			read_zp(B);
			op_LDX(B);
			break;
		
		case OP_LDX_ZPY:
			read_zpy(B);
			op_LDX(B);
			break;
		
		case OP_LDX_ABS:
			read_abs(B);
			op_LDX(B);
			break;
		
		case OP_LDX_ABY:
			read_aby(B);
			op_LDX(B);
			break;
		
		case OP_LDY_IMM:
			read_imm(B);
			op_LDY(B);
			break;
		
		case OP_LDY_ZP:
			read_zp(B);
			op_LDY(B);
			break;
		
		case OP_LDY_ZPX:
			read_zpx(B);
			op_LDY(B);
			break;
		
		case OP_LDY_ABS:
			read_abs(B);
			op_LDY(B);
			break;
		
		case OP_LDY_ABX:
			read_abx(B);
			op_LDY(B);
			break;
		
		case OP_LSR_A:
			op_LSR(reg_a);
			break;
		
		case OP_LSR_ZP:
			cmd_zp(op_LSR);
			break;
		
		case OP_LSR_ZPX:
			cmd_zpx(op_LSR);
			break;
		
		case OP_LSR_ABS:
			cmd_abs(op_LSR);
			break;
		
		case OP_LSR_ABX:
			cmd_abx(op_LSR);
			break;
		
		case OP_NOP:
			break;
		
		case OP_ORA_IMM:
			read_imm(B);
			op_ORA(B);
			break;
		
		case OP_ORA_ZP:
			read_zp(B);
			op_ORA(B);
			break;
		
		case OP_ORA_ZPX:
			read_zpx(B);
			op_ORA(B);
			break;
		
		case OP_ORA_ABS:
			read_abs(B);
			op_ORA(B);
			break;
		
		case OP_ORA_ABX:
			read_abx(B);
			op_ORA(B);
			break;
		
		case OP_ORA_ABY:
			read_aby(B);
			op_ORA(B);
			break;
		
		case OP_ORA_INX:
			read_inx(B);
			op_ORA(B);
			break;
		
		case OP_ORA_INY:
			read_iny(B);
			op_ORA(B);
			break;
		
		case OP_PHA:
			PUSH(reg_a);
			break;
		
		case OP_PHP:
			B = ((st_carry) | (st_zero << 1) 
				| (st_int << 2) | (st_dec << 3)
				| (st_brk << 4) | (1 << 5) 
				| (st_overflow << 6) | (st_neg << 7));
			PUSH(B);
			break;
		
		case OP_PLA:
			PULL(B);
			reg_a = B;
			break;
		
		case OP_PLP:
			PULL(B);
			st_carry = B & 0x01;
			st_zero = B & 0x02;
			st_int = B & 0x04;
			st_dec = B & 0x08;
			st_overflow = B & 0x40;
			st_neg = B & 0x80;
			break;
		
		case OP_ROL_A:
			op_ROL(reg_a);
			break;
		
		case OP_ROL_ZP:
			cmd_zp(op_ROL);
			break;
		
		case OP_ROL_ZPX:
			cmd_zpx(op_ROL);
			break;
		
		case OP_ROL_ABS:
			cmd_abs(op_ROL);
			break;
		
		case OP_ROL_ABX:
			cmd_abx(op_ROL);
			break;
		
		case OP_ROR_A:
			op_ROR(reg_a);
			break;
		
		case OP_ROR_ZP:
			cmd_zp(op_ROR);
			break;
		
		case OP_ROR_ZPX:
			cmd_zpx(op_ROR);
			break;
		
		case OP_ROR_ABS:
			cmd_abs(op_ROR);
			break;
		
		case OP_ROR_ABX:
			cmd_abx(op_ROR);
			break;
		
		case OP_RTS:
			PULL(B);
			PULL(W);
			src = B | (W<<8);
			src += 1;
			if ( cpu.verbose == 1 ) 
				printf("RTS: old pc:%x, new pc:%x\n\n\n", pc, src);
			pc = src;
			break;
		
		case OP_RTI:
			PULL(B);
			st_carry = B & 0x01;
			st_zero = B & 0x02;
			st_int = B & 0x04;
			st_dec = B & 0x08;
			st_overflow = B & 0x40;
			st_neg = B & 0x80;
		
		
			PULL(B);
			PULL(W);
			src = B | (W<<8);
			if ( cpu.verbose == 1 ) 
				printf("RTI: old pc:%x, new pc:%x\n\n\n", pc, src);
			pc = src;
			break;
		
		
		case OP_SBC_IMM:
			read_imm(B);
			op_SBC(B);
			break;
		
		case OP_SBC_ZP:
			read_zp(B);
			op_SBC(B);
			break;
		
		case OP_SBC_ZPX:
			read_zpx(B);
			op_SBC(B);
			break;
		
		case OP_SBC_ABS:
			read_abs(B);
			op_SBC(B);
			break;
		
		case OP_SBC_ABX:
			read_abx(B);
			op_SBC(B);
			break;
		
		case OP_SBC_ABY:
			read_aby(B);
			op_SBC(B);
			break;
		
		case OP_SBC_INX:
			read_inx(B);
			op_SBC(B);
			break;
		
		case OP_SBC_INY:
			read_iny(B);
			op_SBC(B);
			break;
		
		case OP_SEC:
			st_carry = 1;
			break;
		
		case OP_SED:
			st_dec = 1;
			break;
		
		case OP_SEI:
			st_int = 1;
			break;
		
		case OP_STA_ZP:
			write_zp(reg_a);
			break;
		
		case OP_STA_ZPX:
			write_zpx(reg_a);
			break;
		
		case OP_STA_ABS:
			write_abs(reg_a);
			break;
		
		case OP_STA_ABX:
			write_abx(reg_a);
			break;
		
		case OP_STA_ABY:
			write_aby(reg_a);
			break;
		
		case OP_STA_INX:
			write_inx(reg_a);
			break;
		
		case OP_STA_INY:
			write_iny(reg_a);
			break;
		
		case OP_STX_ZP:
			write_zp(reg_x);
			break;
		
		case OP_STX_ZPY:
			write_zpy(reg_x);
			break;
		
		case OP_STX_ABS:
			write_abs(reg_x);
			break;
		
		case OP_STY_ZP:
			write_zp(reg_y);
			break;
		
		case OP_STY_ZPX:
			write_zpx(reg_y);
			break;
		
		case OP_STY_ABS:
			write_abs(reg_y);
			break;
		
		case OP_TAX:
			reg_x = reg_a;
			SET_SIGN(reg_a);
			SET_ZERO(reg_a);
			break;
		
		case OP_TAY:
			reg_y = reg_a;
			SET_SIGN(reg_a);
			SET_ZERO(reg_a);
			break;
		
		case OP_TSX:
			reg_x = sp;
			SET_SIGN(reg_x);
			SET_ZERO(reg_x);
			break;
		
		case OP_TXA:
			reg_a = reg_x;
			SET_SIGN(reg_a);
			SET_ZERO(reg_a);
			break;
		
		case OP_TXS:
			sp = reg_x;
			SET_SIGN(reg_a);
			SET_ZERO(reg_a);
			break;
		
		case OP_TYA:
			reg_a = reg_y;
			SET_SIGN(reg_a);
			SET_ZERO(reg_a);
			break;
		
		default:
			//exit(ERR_OPCODE);
			printf("ERR_OPCODE %x?\n", opcode);
			SDL_Flip(screen);
			//exit(ERR_OPCODE);
			cpu.running=0;
			break;
