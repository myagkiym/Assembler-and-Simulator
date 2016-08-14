#ifndef ASSEMBLER_PRETREATMENT_H_INCLUDED
#define ASSEMBLER_PRETREATMENT_H_INCLUDED

#include "common.h"
#include <stdio.h>

/* the max length of the reading buffer*/
#define MAX_BUF_LEN		100

/* struct that stores the label/variable and its address */
typedef struct _Addr{
	char			symbol[MAX_BUF_LEN];
	uint32_t		addr;
	struct _Addr	*next;
}Addr;

error_t assembler_pretreatment(const char *src, FILE **temp_dst, Error *error);

#endif // ASSEMBLER_PRETREATMENT_H_INCLUDED