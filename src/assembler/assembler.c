#include "assembler.h"
#include "assembler_pretreatment.h"
#include "hash.h"
#include "common.h"
#include <string.h>

/* the operator set */
const Op op_set[OP_NUM][OP_MXLEN]={
	{"HLT",		(0<<27)},	{"JMP",		(1<<27)},
	{"CJMP",	(2<<27)},	{"OJMP",	(3<<27)},
	{"CALL",	(4<<27)},	{"RET",		(5<<27)},
	{"PUSH",	(6<<27)},	{"POP",		(7<<27)},
	{"LOADB",	(8<<27)},	{"LOADW",	(9<<27)},
	{"STOREB",	(10<<27)},	{"STOREW",	(11<<27)},
	{"LOADI",	(12<<27)},	{"NOP",		(13<<27)},
	{"IN",		(14<<27)},	{"OUT",		(15<<27)},
	{"ADD",		(16<<27)},	{"ADDI",	(17<<27)},
	{"SUB",		(18<<27)},	{"SUBI",	(19<<27)},
	{"MUL",		(20<<27)},	{"DIV",		(21<<27)},
	{"AND",		(22<<27)},	{"OR",		(23<<27)},
	{"NOR",		(24<<27)},	{"NOTB",	(25<<27)},
	{"SAL",		(26<<27)},	{"SAR",		(27<<27)},
	{"EQU",		(28<<27)},	{"LT",		(29<<27)},
	{"LTE",		(30<<27)},	{"NOTC",	(31<<27)}
};

/* the hash table that stores the operator value(key is the name) */
Op op_val[HASH_MASK];

error_t assembler_init(void){
	memset(op_val,0,sizeof(uint32_t)*HASH_MASK);
	/* initialize the op_val table */
	for(int i=0; i<OP_NUM; i++){
		strcpy(op_val[hash_32(op_set[i], strlen(op_set[i]), HASH_SEED) & HASH_MASK]->name, op_set[i]->name);
		op_val[hash_32(op_set[i], strlen(op_set[i]), HASH_SEED) & HASH_MASK]->value	=	op_set[i]->value;
	}
	return no_error;
}

error_t assembler(const char *src, const char *dst){
	/* open the necessary files */

	/* do the pre-treatment*/

	/* do the replacement */

	return no_error;
}


//static error_t assembler_replacement(FILE *src, FILE *dst){
//	return no_error;
//}


