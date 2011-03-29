/* 
	Opcodes for the robot
	Taken originally MOS 6502 opcodes
*/

/* Add accumulator with carry -> ADC */
#define OP_ADC_IMM		0x69
#define OP_ADC_ZP		0x65
#define	OP_ADC_ZPX		0x75
#define OP_ADC_ABS		0x6D
#define OP_ADC_ABX		0x7d
#define OP_ADC_ABY		0x79
#define OP_ADC_INX		0x61
#define OP_ADC_INY		0x71

/* "AND" memory with accumulator -> AND */
#define OP_AND_IMM		0x29
#define OP_AND_ZP		0x25
#define OP_AND_ZPX		0x35
#define OP_AND_ABS		0x2D
#define OP_AND_ABX		0x3D
#define OP_AND_ABY		0x39
#define OP_AND_INX		0x21
#define OP_AND_INY		0x31


/* Shift left one bit (memory or accumulator -> ASL */
#define OP_ASL_A		0x0A
#define OP_ASL_ZP		0x06
#define OP_ASL_ZPX		0x16
#define OP_ASL_ABS		0x0E
#define OP_ASL_ABX		0x1E


/* Branch on carry clear -> BCC */
#define OP_BCC			0x90


/* Branch on carry set -> BCS */
#define OP_BCS			0xB0


/* Branch on result zero -> BEQ */
#define OP_BEQ			0xF0


/* Test bits in memory with accumulator -> BIT */
#define OP_BIT_ZP		0x24
#define OP_BIT_ABS		0x2C


/* Branch on result minus -> BMI */
#define OP_BMI			0x30


/* Branch on result not zero -> BNE */
#define OP_BNE			0xD0


/* Branch on result plus -> BPL */
#define OP_BPL			0x10


/* Force break -> BRK */
#define OP_BRK			0x00


/* Branch on overflow clear -> BVC */
#define OP_BVC			0x50


/* Branch on overflow set -> BVS */
#define OP_BVS			0x70


/* Flag instructions */
#define OP_CLC          0x18
#define OP_CLD			0xD8 //Clear decimal flag
#define OP_CLI			0x58 //Clear interrupt disable flag
#define OP_CLV			0xB8 //Clear overflow flag


/* Compare memory with accumulator -> CMP */
#define OP_CMP_IMM		0xC9
#define OP_CMP_ZP		0xC5
#define OP_CMP_ZPX		0xD5
#define OP_CMP_ABS		0xCD
#define OP_CMP_ABX		0xDD
#define OP_CMP_ABY		0xD9
#define OP_CMP_INX		0xC1
#define OP_CMP_INY		0xD1


/* Compare memory with index X -> CPX */
#define OP_CPX_IMM		0xE0
#define OP_CPX_ZP		0xE4
#define OP_CPX_ABS		0xEC


/* Compare memory with index Y -> CPY */
#define OP_CPY_IMM		0xC0
#define OP_CPY_ZP		0xC4
#define OP_CPY_ABS		0xCC


/* Decrement memory by one -> DEC */
#define OP_DEC_ZP		0xC6
#define OP_DEC_ZPX		0xD6
#define OP_DEC_ABS		0xCE
#define OP_DEC_ABX		0xDE


/* Decrement index X by one -> DEX */
#define OP_DEX			0xCA


/* Decrement index X by one -> DEY */
#define OP_DEY			0x88


/* "Exclusive-Or" memory with accumulator -> EOR */
#define OP_EOR_IMM		0x49
#define OP_EOR_ZP		0x45
#define OP_EOR_ZPX		0x55
#define OP_EOR_ABS		0x4D
#define OP_EOR_ABX		0x50
#define OP_EOR_ABY		0x59
#define OP_EOR_INX		0x41
#define OP_EOR_INY		0x51


/* Increment memory by one -> INC */
#define OP_INC_ZP		0xE6
#define OP_INC_ZPX		0xF6
#define OP_INC_ABS		0xEE
#define OP_INC_ABX		0xFE


/* Increment index X by one -> INX */
#define OP_INX			0xE8


/* Increment index Y by one -> INY */
#define OP_INY			0xC8


/* Jump to location -> JMP */
#define OP_JMP_ABS		0x4C
#define OP_JMP_IND		0x6C


/* Jump to new location saving return address -> JSR */
#define OP_JSR			0x20


/* Load accumulator with memory -> LDA */
#define OP_LDA_IMM		0xA9
#define OP_LDA_ZP		0xA5
#define OP_LDA_ZPX		0xB5
#define OP_LDA_ABS		0xAD
#define OP_LDA_ABX		0xBD
#define OP_LDA_ABY		0xB9
#define OP_LDA_INX		0xA1
#define OP_LDA_INY		0xB1


/* Load index X with memory -> LDX */
#define OP_LDX_IMM		0xA2
#define OP_LDX_ZP		0xA6
#define OP_LDX_ZPY		0xB6
#define OP_LDX_ABS		0xAE
#define OP_LDX_ABY		0xBE


/* Load index Y with memory -> LDY */
#define OP_LDY_IMM		0xA0
#define OP_LDY_ZP		0xA4
#define OP_LDY_ZPX		0xB4
#define OP_LDY_ABS		0xAC
#define OP_LDY_ABX		0xBC


/* Shift right one bit (memory or accumulator) -> LSR */
#define OP_LSR_A		0x4A
#define	OP_LSR_ZP		0x46
#define OP_LSR_ZPX		0x56
#define OP_LSR_ABS		0x4E
#define OP_LSR_ABX		0x5E


/* No operation -> NOP */
#define OP_NOP			0xEA


/* "OR" memory with accumulator -> ORA */
#define OP_ORA_IMM		0x09
#define OP_ORA_ZP		0x05
#define OP_ORA_ZPX		0x15
#define OP_ORA_ABS		0x0D
#define OP_ORA_ABX		0x1D
#define OP_ORA_ABY		0x19
#define OP_ORA_INX		0x01
#define OP_ORA_INY		0x11


/* Push accumulator on stack -> PHA */
#define OP_PHA			0x48


/* Push processor on stack -> PHP */
#define OP_PHP			0x08


/* Pull accumulator from stack -> PLA */
#define OP_PLA			0x68


/* Pull processor status from stack -> PLP */
#define OP_PLP			0x28


/* Rotate one bit left (memory or accumulator) -> ROL */
#define OP_ROL_A		0x2A
#define OP_ROL_ZP		0x26
#define OP_ROL_ZPX		0x36
#define OP_ROL_ABS		0x2E
#define OP_ROL_ABX		0x3E


/* Rotate one bit right (memory or accumulator) -> ROR */
#define OP_ROR_A		0x6A
#define OP_ROR_ZP		0x66
#define OP_ROR_ZPX		0x76
#define OP_ROR_ABS		0x6E
#define OP_ROR_ABX		0x7E


/* Return from interrupt -> RTI */
#define OP_RTI			0x40


/* Return from subroutine -> RTS */
#define OP_RTS			0x60


/* Subtract memory from accumulator with borrow */
#define OP_SBC_IMM		0xE9
#define OP_SBC_ZP		0xE5
#define OP_SBC_ZPX		0xF5
#define OP_SBC_ABS		0xED
#define OP_SBC_ABX		0xFD
#define OP_SBC_ABY		0xF9
#define OP_SBC_INX		0xE1
#define OP_SBC_INY		0xF1


/* Set carry flag -> SEC */
#define OP_SEC			0x38


/* Set decimal mode -> SED */
#define OP_SED			0xF8


/* Set interrupt flag -> SEI */
#define OP_SEI			0x78


/* Store accumulator in memory -> STA */
#define OP_STA_ZP		0x85
#define OP_STA_ZPX		0x95
#define OP_STA_ABS		0x8D
#define OP_STA_ABX		0x9D
#define OP_STA_ABY		0x99
#define OP_STA_INX		0x81
#define OP_STA_INY		0x91


/* Store index X in memory -> STX */
#define OP_STX_ZP		0x86
#define OP_STX_ZPY		0x96
#define OP_STX_ABS		0x8E


/* Store index Y in memory -> STY */
#define OP_STY_ZP		0x84
#define OP_STY_ZPX		0x94
#define OP_STY_ABS		0x8C


/* Transfer accumulator to index X -> TAX */
#define OP_TAX			0xAA


/* Transfer accumulator to index Y -> TAY */
#define OP_TAY			0xA8


/* Transfer stack pointer to index X -> TSX */
#define OP_TSX			0xBA


/* Transfer index X to accumulator -> TXA */
#define OP_TXA			0x8A


/* Transfer index X to stack pointer -> TXS */
#define OP_TXS			0x9A


/* Transfer index Y to accumulator -> TYA */
#define OP_TYA			0x98
