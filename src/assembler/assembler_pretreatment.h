#ifndef ASSEMBLER_PRETREATMENT_H_INCLUDED
#define ASSEMBLER_PRETREATMENT_H_INCLUDED

#include "common.h"
#include <stdio.h>

/* the max length of the reading buffer*/
#define MAX_BUF_LEN		500

/* struct that stores the label/variable and its address */
typedef struct _Addr{
	char			symbol[MAX_BUF_LEN];
	uint32_t		addr;
	struct _Addr	*next;
}Addr;

error_t assembler_pretreatment_stage0(const char *src, const char *dst);
error_t assembler_pretreatment_stage1(const char *src, const char *dst, Error *error);

#endif // ASSEMBLER_PRETREATMENT_H_INCLUDED
