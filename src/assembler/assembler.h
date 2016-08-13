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

typedef	struct _Op{
	char		name[OP_MXLEN];
	uint32_t	value;
}Op;

/* the hash table that stores the operator value(key is the name) */
extern Op op_val[HASH_MASK];

#endif // ASSEMBLER_H_INCLUDED
