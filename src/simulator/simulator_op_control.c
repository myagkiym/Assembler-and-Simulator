#include "simulator.h"
#include "simulator_op_control.h"

/* the implementation of control command */
inline void HLT(void){
	return;
}
inline void JMP(void){
	PC	=	IR&0x00FFFFFF;
}
inline void CJMP(void){
	PC	=	GETC?(IR&0x00FFFFFF):PC;
}
inline void OJMP(void){
	PC	=	GETO?(IR&0x00FFFFFF):PC;
}
inline void CALL(void){
	for(int i=0; i<8;ES++, i++)
		mem[ES]	=	reg[i];
	mem[ES]	=	PSW,	ES++;
	mem[ES]	=	PC,		ES++;
	PC	=	IR&0x00FFFFFF;
}
inline void RET(void){
	PC	=	mem[ES],	ES--;
	PSW	=	mem[ES],	ES--;
	for(int i=0; i<8; ES--,i++)
		reg[7-i]	=	mem[ES];
}
