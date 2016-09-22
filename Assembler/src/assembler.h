#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED

#include "common.h"


/* initialize the operator hash table */
error_t assembler_init(void);
/* the main assembler function */
error_t assembler(const char *src, const char *dst, Error *error);


/* get next token on buffer from *temp position */
/* buffer must end with \n\0 and *temp must be on the buffer */
error_t __get_nth_token(const char *buffer, char *buffer_sub, char n);

#endif // ASSEMBLER_H_INCLUDED
