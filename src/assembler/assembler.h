#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED

#include "common.h"
/* the mask of hash result */
/* enlarge it if hash result collied, when you're trying to change the operator set */
#define HASH_MASK	0x03FF

/* the number of operator */
#define OP_NUM	32
/* the max length of operator*/
#define OP_MXLEN 8

/* stores the command format 												*/
/* 'o' for operator, 'r' for register, 'a' for address, 'i' for immediate	*/
/* 'p' for padding, 't'for port, the number follows stands for bits 		*/
typedef char format_t;
#define o5_p27			0x01
#define o5_p3_a24		0x02
#define o5_r3_p24		0x03
#define o5_r3_a24		0x04
#define o5_r3_p8_i16	0x05
#define o5_r3_p16_t8	0x06
#define o5_r3_r4_r4_p16	0x07
#define o5_r3_r4_p20	0x08

typedef	struct _Op{
	char		name[OP_MXLEN];		/* the name of the operator */
	uint32_t	value;				/* the value of the operator (use with '|') */
	format_t	format;				/* the format of the operator*/
}Op;

/* the hash table that stores the operator value(key is the name) */
extern Op op_hash[HASH_MASK];

error_t assembler_init(void);

#endif // ASSEMBLER_H_INCLUDED
