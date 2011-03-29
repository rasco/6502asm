#include <stdlib.h>
#include <stdio.h>

#include "errors.h"
#include "cpu.h"
#include "opcodes.h"

double cyccount;

#define printstatus() \
			printf("pc: %x, opcode: 0x%x (arg1: 0x%x, arg2: 0x%x)\n",   \
			pc, readmem(pc), readmem(pc+1), readmem(pc+2));\
			printf("reg_a: %d, reg_x: %d, reg_y: %d, 1000: %d\n", \
			reg_a, reg_x, reg_y, readmem(0x1000));\
			printf("interrupt vectors: %x, %x, %x\n", \
			readmem(0xFFFA)\
			|(readmem(0xFFFB)<<8), \
			readmem(0xFFFC)\
			|(readmem(0xFFFD)<<8), \
			readmem(0xFFFE)\
			|(readmem(0xFFFF)<<8));\
			printf("status: %x %x %x %x %x %x %x %x\n", \
			(st_carry) , \
			(st_zero ) , \
			(st_int ) , \
			(st_dec ) , \
			(st_brk ) , \
			(1 ) , \
			(st_overflow ) , \
			(st_neg ));\
			printf("0x2000: %x\n", readmem(0x2000));

#define pc              (cpu.pc)
#define sp              (cpu.sp)
#define reg_a         (cpu.reg_a)
#define reg_x         (cpu.reg_x)
#define reg_y         (cpu.reg_y)
#define st_zero       (cpu.st_zero)
#define st_neg        (cpu.st_neg)
#define st_carry      (cpu.st_carry)
#define st_overflow (cpu.st_overflow)
#define st_int          (cpu.st_int)
#define st_dec         (cpu.st_dec)
#define st_brk         (cpu.st_brk)

// NES stuff..
#define nmi() \
			st_int = 1; \
			PUSH((pc >> 8)); \
			PUSH((pc & 0xFF));  \
			st_brk = 0; \
			B = ((st_carry) | (st_zero << 1) \
					| (st_int << 2) | (st_dec << 3) \
					| (st_brk << 4) | (1 << 5)  \
					| (st_overflow << 6) | (st_neg << 7)); \
			PUSH(B); \
			W = 0; \
			W = readmem(0xFFFA); \
			W = W | (readmem(0xFFFB) << 8); \
			if ( cpu.verbose == 1 ) \
				printf("\nINT (NMI)\npc:%x\nW:%x\n", pc, W); \
			pc = W; \
			cyccount = 50000; 


#define get2bytevalue(var) \
			var = 0; \
			var = readmem(pc++); \
			var = var | (readmem(pc++) << 8)

#define get1bytevalue(var) \
			var = 0; \
			var = readmem(pc++)


/* Flag manipulation
 */
#define SET_ZERO(var) \
			st_zero = ((var) == 0 ? 1 : 0)

#define SET_SIGN(var) \
			st_neg = ( (((var) & 0x80) == 0x80) ? 1 : 0)

#define SET_CARRY(var) \
			st_carry = ((var) ? 1 :0)

#define SET_OVERFLOW(var) \
			st_overflow = ((var) == 0 ? 0 : 1)



/* Stack operation
 */
#define PUSH(var) \
	writemem(STACK_BEGIN + sp--, var)
#define PULL(var) \
	var = readmem(STACK_BEGIN + ++sp)


/* Addressing mode macros 
 */

// -------- Get address macros ---------

// Zero page
#define getaddr_zp(var) \
			get1bytevalue(var)

// Zero page indexed
#define getaddr_zpx(var) \
			get1bytevalue(var); \
			var = (0xff)&(var + reg_x); \

// Zero page indexed (Y)
#define getaddr_zpy(var) \
			get1bytevalue(var); \
			var = (0xff)&(var + reg_x)

// Absolute
#define getaddr_abs(var) \
			get2bytevalue(var)

// Absolute indexed, x
#define getaddr_abx(var) \
			get2bytevalue(var); \
			var += reg_x

// Absolute indexed, y
#define getaddr_aby(var) \
			get2bytevalue(var); \
			var += reg_y
			
// Pre-indexed indirect (x)
#define getaddr_inx(var) \
			get1bytevalue(src); \
			temp3 = (byte)(src+reg_x); \
			temp = readmem(temp3); \
			var = temp | (readmem(temp3+1) << 8 )

// Post-indexed indirect (y)
#define getaddr_iny(var) \
			get1bytevalue(src); \
			temp = readmem(src); \
			var = temp | (readmem(src+1) << 8 ); \
			var += reg_y

// Indirect
#define getaddr_ind(var) \
			get1bytevalue(src); \
			temp = readmem(src); \
			var = temp | (readmem(src+1) << 8 )

// -------- Read macros ---------

// Immediate
#define read_imm(var) \
			get1bytevalue(var)

// Zero page
#define read_zp(var) \
			getaddr_zp(W); \
			var = readmem(W)

// Zero page indexed
#define read_zpx(var) \
			getaddr_zpx(W); \
			var = readmem(W)

// Zero page indexed (Y)
#define read_zpy(var) \
			getaddr_zpy(W); \
			var = readmem(W)

// Absolute
#define read_abs(var) \
			getaddr_abs(W); \
			var = readmem(W)

// Absolute indexed, x
#define read_abx(var) \
			getaddr_abx(W); \
			var = readmem(W)

// Absolute indexed, y
#define read_aby(var) \
			getaddr_aby(W); \
			var = readmem(W)

// Pre-indexed indirect (x)
#define read_inx(var) \
			getaddr_inx(W); \
			var = readmem(W)
			
// Post-indexed indirect (y)
#define read_iny(var) \
			getaddr_iny(W); \
			var = readmem(W)

// -------- Write macros ---------

// Zero page
#define write_zp(var) \
			getaddr_zp(W); \
			writemem(W, var)

// Zero page indexed, x
#define write_zpx(var) \
			getaddr_zpx(W); \
			writemem(W, var)

// Zero page indexed, y
#define write_zpy(var) \
			getaddr_zpy(W); \
			writemem(W, var)
			
// Absolute
#define write_abs(var) \
			getaddr_abs(W); \
			writemem(W, var)

// Absolute indexed, x
#define write_abx(var) \
			getaddr_abx(W); \
			writemem(W, var)

// Absolute indexed, y
#define write_aby(var) \
			getaddr_aby(W); \
			writemem(W, var)

// Pre-indexed indirect (x)
#define write_inx(var) \
			getaddr_inx(W); \
			writemem(W, var)
			
// Post-indexed indirect (y)
#define write_iny(var) \
			getaddr_iny(W); \
			writemem(W, var)

// -------- Modify memory macros ---------

#define cmd_zp(cmd) \
	read_zp(B); \
	cmd(B); \
	writemem(W, B);

#define cmd_zpx(cmd) \
	read_zpx(B); \
	cmd(B); \
	writemem(W, B);

#define cmd_abs(cmd) \
	read_abs(B); \
	cmd(B); \
	writemem(W, B);

#define cmd_abx(cmd) \
	read_abx(B); \
	cmd(B); \
	writemem(W, B);

#define cmd_aby(cmd) \
	read_aby(B); \
	cmd(B); \
	writemem(W, B);

#define cmd_inx(cmd) \
	read_inx(B); \
	cmd(B); \
	writemem(W, B);

#define cmd_iny(cmd) \
	read_iny(B); \
	cmd(B); \
	writemem(W, B);


/* Operation macros
 */

#define op_ADC(var) \
	temp = reg_a + var + st_carry; \
	SET_ZERO(temp & 0xff); \
	SET_SIGN(temp); \
	SET_OVERFLOW(!((reg_a ^ var) & 0x80) && ((reg_a ^ temp) & 0x80)); \
	SET_CARRY(temp > 0xff); \
	reg_a = temp & 0xff

#define op_SBC(var) \
	temp = reg_a - var - (st_carry == 1 ? 0 : 1); \
	SET_SIGN(temp); \
	SET_ZERO(temp & 0xFF); \
	SET_OVERFLOW(((reg_a ^ var) & 0x80) && ((reg_a ^ temp) & 0x80)); \
	SET_CARRY(temp < 0x100); \
	reg_a = temp & 0xff

#define op_ASL(var) \
	SET_CARRY(var & 0x80); \
	var <<= 1; \
	SET_SIGN(var); \
	SET_ZERO(var)

#define op_BIT(var) \
	SET_SIGN(var); \
	SET_OVERFLOW(0x40 & var); \
	SET_ZERO(var & reg_a)

#define op_CMP(var) \
	var = reg_a - var; \
	SET_CARRY(var < 0x100); \
	SET_SIGN(var); \
	SET_ZERO(var & 0xff)

#define op_DEC(var) \
	var = var - 1; \
	SET_SIGN(var); \
	SET_ZERO(var)

#define op_EOR(var) \
	var ^= reg_a; \
	SET_SIGN(var); \
	SET_ZERO(var); \
	reg_a = var

#define op_INC(var) \
	var = var + 1; \
	SET_SIGN(var); \
	SET_ZERO(var)

#define op_LDA(var) \
	SET_SIGN(var); \
	SET_ZERO(var); \
	reg_a = var

#define op_LDX(var) \
	SET_SIGN(var); \
	SET_ZERO(var); \
	reg_x = var

#define op_LDY(var) \
	SET_SIGN(var); \
	SET_ZERO(var); \
	reg_y = var

#define op_LSR(var) \
	SET_CARRY(var & 0x01); \
	var >>= 1; \
	SET_SIGN(var); \
	SET_ZERO(var)

#define op_ORA(var) \
	var |= reg_a; \
	SET_SIGN(var); \
	SET_ZERO(var); \
	reg_a = var

#define op_ROL(var) \
	temp = var << 1; \
	if ( st_carry == 1 ) temp |= 1; \
	SET_CARRY(temp > 0xff); \
	temp &= 0xff; \
	var = temp; \
	SET_SIGN(var); \
	SET_ZERO(var)

#define op_ROR(var) \
	if ( st_carry == 1 ) var |= 0x100; \
	SET_CARRY(var > 0x01); \
	var >>= 1; \
	SET_SIGN(var); \
	SET_ZERO(var)


/* initialize
 */
void cpu_init()
{
	pc = MEM_SIZE - ROM_SIZE;
	sp = 0xFF;
	cyccount = 50000;
}

/* executes one instruction on the cpu
 */
inline void cpu_step() 
{
	unsigned char opcode = 0;
	unsigned int src = 0;
	register byte B = 0;
	register word W = 0;
	int temp;
	unsigned char temp3;
	
	if ( cpu.running != 1 )
		return;
		
	if ( cpu.verbose == 1 ) {
		printstatus();
	}
	
	opcode = readmem(pc);
	
	pc++;
	
	switch(opcode)
	{
		#include "instr.h"
	}
	
	// NMI 
	/*
	if ( cyccount-- <= 0 && (readmem(0x2000) & 0x80) == 0x80 )
	{
		nmi();
	}
	*/
}
