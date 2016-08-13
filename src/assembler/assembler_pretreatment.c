#include "assembler.h"
#include "assembler_pretreatment.h"
#include "hash.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/* the hash table of label address */
Addr *addr_table[HASH_MASK];

/* function that stores the label or declaration in hash table*/
static error_t __hash_store(const char *symbol, const uint32_t pc_addr);

/* get next token on buffer from *temp position */
/* buffer must end with \n\0 and *temp must be on the buffer */
static error_t __get_next_token(const char *buffer, char *buffer_sub, char **temp);

#define	__return_error(error_code)	\
{strcpy(error->error_line,buffer);\
error->error_pos	=	(char)(strstr(buffer,buffer_sub)-buffer);\
return	error_code;}

/* substitute the BYTE, WORD declaration and :LABEL */
/* returning temp_dst(the temp file of pre-treatment */
error_t assembler_pretreatment(const char *src, FILE **temp_dst, Error *error){
	/* initialize the address table */
	for(int i=0; i<HASH_MASK; i++){
		addr_table[i]		=	malloc(sizeof(Addr));
		addr_table[i]->next	=	NULL;
	}
	/* open necessary files */
	char src_cpy[strlen(src)+2];
	strcpy(src_cpy,src);
	FILE *file_src	=	fopen(src,"r");
	if(!file_src)
		return error_open_file;
	*temp_dst		=	fopen(strcat(src_cpy,"$"),"w");

	/* store the reading line */
	char buffer[MAX_BUF_LEN];
	/* analyze the reading line */
	char *temp;
	char buffer_sub[MAX_BUF_LEN];

	/* store the current reading address (metric: 2Byte) (for :LABEL) */
	uint32_t pc_addr	=	0;
	/* store the current data distribution address (metric: 2Byte) (relative addr, start from DS) */
	uint32_t data_addr	=	0;

	/*** stage one, find the labels and declarations ***/
	for(; fgets(buffer, MAX_BUF_LEN, file_src); pc_addr+=2){
		temp	=	buffer;
		/* if is the empty line */
		if(__get_next_token(buffer, buffer_sub, &temp)==error_token_not_get){
			pc_addr-=2;
			continue;	/* next line */
		}
		/* switch(the first token) */
		/* if this line has a label */
		if(buffer_sub[counter]==':'){
			/* store the label into hash table */
			buffer_sub[counter]	=	'\0';
			/* if find duplicate symbol */
			if(__hash_store(buffer_sub,pc_addr)==error_gramma_duplicate_symbol
				__return_error(error_gramma_duplicate_symbol);
			/* get the next token */
			if(__get_next_token(buffer, buffer_sub, &temp)==error_token_not_get){
				pc_addr-=2;
				continue;
			}
		}
		/* if this line has a byte declaration */
		if(strcmp(buffer_sub,"BYTE")==0 || strstr(buffer,"WORD")){
			/* if there noting next */
			if(__get_next_token(buffer, buffer_sub, &temp)==error_token_not_get)
				__return_error(error_gramma_lack_symbol);
			/* if next is a keyword */
			if(strcmp(op_val[hash_32(buffer_sub,strlen(buffer_sub),HASH_SEED)]->name,buffer_sub)==0)
				__return_error(error_gramma_declare_is_keyword);
			/* if find duplicate symbol */
			if(__hash_store(buffer_sub, pc_addr)==error_gramma_duplicate_symbol)
				__return_error(error_gramma_duplicate_symbol);
			/* distribute data space */
			int space	=	0;
			int i		=	strlen(buffer_sub)-1;
			if(buffer_sub[i]==']')
				for(i--;isdigit(buffer_sub[i]-'0');i--)
					space	=	space*10 + buffer_sub[i] - '0';
			else
				space	=	1;
			data_addr+=space;
			/* if space exceeded */
			if(data_addr>=MAX_DATA_SPACE)
				return	error_stack_overflow;
			/* if there's still token after the declaration*/
			if(__get_next_token()==no_error){
				__return_error(error_gramma_duplicate_command);
			}
			continue;	/* next line */
		}
		/* if is a keyword (note that it doesn't do error treatment for Op here) */
		if(op_val[hash_32(buffer_sub,strlen(buffer_sub),HASH_SEED)]->name,buffer_sub)==0)
			continue;
		/* it is noting */
		else
			__return_error(error_gramma_unidentified);
	}
	/*** stage two, replace all the symbols with address, write into temp_dst ***/
	for(;fgets(buffer, MAX_BUF_LEN, file_src);){
		if(strstr(buffer,""))
	}
	/* free the hash table */
	return no_error;
}

static error_t __hash_store(const char *symbol, const uint32_t pc_addr){
	Addr *addr_temp	=	addr_table[hash_32(symbol,strlen(symbol),HASH_SEED) & HASH_MASK];
	for(; addr_temp->next!=NULL; addr_temp=addr_temp->next)
		/* find the duplicate */
		if(!strcmp(addr_temp->next->symbol,symbol))
			return error_gramma_duplicate_symbol;
	/* store into the table */
	addr_temp->next	=	malloc(sizeof(Addr));
	addr_temp		=	addr_temp->next;
	strcpy(addr_temp->symbol,symbol);
	addr_temp->addr	=	pc_addr;
	return no_error;
}

/* get next token on buffer from *temp position */
/* buffer must end with \n\0 and *temp must be on the buffer */
static error_t __get_next_token(const char *buffer, char *buffer_sub, char **temp){
	int counter	=	0;
	/* get a line and find the first token of it */
	for(; isspace(**temp) && **temp!='\n'; (*temp)++);
	/* if empty line */
	if(**temp=='\n')
		return	error_token_not_get;
	/* get the first token */
	for(counter=0; !isspace(**temp); (*temp)++, counter++)
		buffer_sub[counter]	=	**temp;
	buffer_sub[counter+1]	=	'\0';
	return no_error;
}
