#ifndef ASSEMBLER_PRETREATMENT_H_INCLUDED
#define ASSEMBLER_PRETREATMENT_H_INCLUDED

#include "common.h"

/* the max length of the reading buffer*/
#define MAX_BUF_LEN		100

/* struct that stores the label/variable and its address */
typedef struct _Addr{
	char			symbol[MAX_BUF_LEN];
	uint32_t		addr;
	struct _Addr	*next;
}Addr;

#endif // ASSEMBLER_PRETREATMENT_H_INCLUDED
