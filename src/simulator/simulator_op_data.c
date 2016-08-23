#include "simulator.h"
#include "simulator_op_data.h"

/* reg[7] is the 'G' register */
void LOADB(void){
    REG0	=	mem[ADDR+reg[7]];
}
void LOADW(void){
	REG0	=	mem[ADDR+reg[7]];
}
void STOREB(void){
	mem[ADDR+reg[7]]	=	REG0;
}
void STOREW(void){
	mem[ADDR+reg[7]]	=	REG0;
}
void LOADI(void){
	REG0	=	IMMD;
}
void NOP(void){
    return;
}
