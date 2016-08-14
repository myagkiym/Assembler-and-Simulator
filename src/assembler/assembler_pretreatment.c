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
/* the temporary data stack */
uint32_t data_stack[1<<24];

/* function that stores the label or declaration in hash table*/
static error_t __hash_store(const char *symbol, const uint32_t addr);

/* get next token on buffer from *temp position */
/* buffer must end with \n\0 and *temp must be on the buffer */
static error_t __get_nth_token(const char *buffer, char *buffer_sub, char n);

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
	/* initialize the temp data stack */
	memset(data_stack,0,sizeof(uint32)*(1<<24));
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
	char buffer_sub[MAX_BUF_LEN];

	/* store the current reading address (metric: 2Byte) (for :LABEL) */
	uint32_t pc_addr	=	0;
	/* store the current data distribution address (metric: 2Byte) (relative addr, start from DS) */
	uint32_t data_addr	=	0;
	/* mark if this line has a label */
	char flag_label		=	0;

	/*** stage one, find the labels and declarations ***/
	for(; fgets(buffer, MAX_BUF_LEN, file_src); pc_addr+=2){
		flag_label	=	0;
		/* if is the empty line */
		if(__get_nth_token(buffer, buffer_sub, 0)==error_token_not_get || buffer_sub[0]=='#'){
			pc_addr-=2;
			continue;	/* next line */
		}
		/* switch(the first token) */
		/* if this line *has* a label */
		if(buffer_sub[strlen(buffer_sub)-1]==':'){
			/* store the label into hash table */
			buffer_sub[strlen(buffer_sub)-1]	=	'\0';
			/* if find duplicate symbol */
			if(__hash_store(buffer_sub,pc_addr)==error_gramma_duplicate_symbol)
				__return_error(error_gramma_duplicate_symbol);
			/* get the next token */
			if(__get_nth_token(buffer, buffer_sub, 1)==error_token_not_get){
				pc_addr-=2;
				continue;
			}
			flag_label	=	1;
		}
		/* if this line is a byte or world declaration */
		if(strcmp(buffer_sub,"BYTE")==0 || strstr(buffer,"WORD")){
			/* if there noting next */
			if(__get_nth_token(buffer, buffer_sub, flag_label+1)==error_token_not_get)
				__return_error(error_gramma_lack_symbol);

			/** needs modify **/
			/* distribute data space */
			int space	=	0;
			char *temp	=	strstr(buffer, buffer_sub);
			/* make sure the symbol is legal */
			if(isdigit(*temp))
				__return_error(error_gramma_declare_is_digit);
			for(; isalnum(temp) || temp=='_'; temp++)
				buffer_sub	=	*temp;
			/* if the symbol is a keyword */
			if(strcmp(op_hash[hash_32(buffer_sub, HASH_SEED) & HASH_MASK].name,buffer_sub)==0)
				__return_error(error_gramma_declare_is_keyword);
			/* store the symbol and judge if find duplicate symbol */
			if(__hash_store(buffer_sub, data_addr)==error_gramma_duplicate_symbol)
				__return_error(error_gramma_duplicate_symbol);

			/* if it is a set */
			if(__get_nth_token(temp, buffer_sub, 0)==error_token_not_get || buffer_sub	=	'#'){
				space = 1;
				goto end;
			}
			temp	=	strstr(buffer, buffer_sub);
			if(*temp=='['){
				temp++;
				for(; isspace(*temp); temp++);
				for(temp++ ;isdigit(buffer_sub[i]);i--)
					space	=	space*10 + buffer_sub[i] - '0';
				for(; isspace(*temp); temp++);
				if(*temp != ']')
					__return_error(error_gramma_declare_incomplete);
			}
			else
				__return_error(error_gramma_too_much_argument);

			/* if already set the value */
			if(__get_nth_token(temp, buffer_sub, 0)==error_token_not_get || buffer_sub	=	'#')
				continue;
			temp	=	strstr(buffer, buffer_sub);
			if(*temp=='='){
				temp++;
				for(; isspace(*temp); temp++);
				/* if it is a set */
				if(temp=='{'){
					int counter=0;
					uint32_t data;
					char fmt[MAX_BUF_LEN]=="%d";
					for(;sscanf(temp,fmt,&data)==1;counter++){
						data_stack[data_addr+i]==data;
						fmt[0]	=	'\0';
						for(int i=0; i<counter; i++)
							strcat(fmt,"%*d");
						strcat(fmt,"%d");
					}
				}
				/* if it is a string */
				else if(temp=='"'){
				/************************ program here ********************************/
					temp++;
					for()
				}
				else
					__return_error(error_gramma_too_less_argument);
			}
			else
				__return_error(error_gramma_too_much_argument);

			end:
			/* distribute space */
			data_addr+=space;
			if(data_addr>=MAX_DATA_SPACE)
				return	error_stack_overflow;

			/* if there's still token after the declaration and it's not comment */
			if(	__get_nth_token(buffer, buffer_sub, flag_label+2)==no_error	&& buffer_sub[0]!='#'){
				__return_error(error_gramma_duplicate_command);
			}

			continue;	/* next line */
		}
		/* if is a keyword (test if the number of token is right ) */
		if(strcmp(op_hash[hash_32(buffer_sub, HASH_SEED) & HASH_MASK].name,buffer_sub)==0){
			int num=0, counter=0;
			switch(op_hash[hash_32(buffer_sub,HASH_SEED) & HASH_MASK].format){
				case o5_p27:
					num	=	1;
					break;
				case o5_p3_a24:
				case o5_r3_a24:
				case o5_r3_p24:
					num	=	2;
					break;
				case o5_r3_p16_t8:
				case o5_r3_p8_i16:
				case o5_r3_r4_p20:
					num	=	3;
					break;
				case o5_r3_r4_r4_p16:
					num	=	4;
					break;
			}
			/* make sure the number of argument is correct */
			for(counter=0; counter<num; counter++)
				if(__get_nth_token(buffer, buffer_sub, flag_label+counter+1)==error_token_not_get)
					__return_error(error_gramma_too_less_argument);
			if(__get_nth_token(buffer, buffer_sub,flag_label+counter+1)==no_error && buffer_sub[0]!='#')
				__return_error(error_gramma_too_much_argument);
			continue;
		}
		/* it is noting */
		else
			__return_error(error_gramma_unidentified);
	}
	/*** stage two, replace all the symbols with address, write into temp_dst ***/
	rewind(file_src);
	for(;fgets(buffer, MAX_BUF_LEN, file_src);){
		flag_label	=	0;
		/* ignore empty line */
		if(__get_nth_token(buffer, buffer_sub, 0)==error_token_not_get || buffer_sub[0]=='#')
			continue;
		/* has label */
		if(buffer_sub[strlen(buffer_sub)-1]==':'){
			flag_label	=	1;
			/* get next token */
			if(__get_nth_token(buffer, buffer_sub, 1)==error_token_not_get)
				continue;
		}
		/* ignore declaration */
		if(strcmp(buffer_sub,"BYTE")==0 || strcmp(buffer_sub,"WORD")==0)
			continue;
		/* replace label and declarations */
		if(strcmp(op_hash[hash_32(buffer_sub,HASH_SEED) & HASH_MASK].name, buffer_sub)==0){
			Addr	*temp;
			int i=0;
			/* print into temp_dst */
			for(i=0; i<flag_label+1; i++){
				__get_nth_token(buffer, buffer_sub, i);
				fprintf(*temp_dst," %s",buffer_sub);
			}
			for(i=0; __get_nth_token(buffer, buffer_sub, i+flag_label+1)==no_error && buffer[0]!= '#'; i++){
				temp=addr_table[hash_32(buffer_sub,HASH_SEED) & HASH_MASK];
				/* try to find the symbol in hash (whatever it is) */
				for(temp=temp->next; temp!=NULL && strcmp(temp->symbol,buffer_sub); temp=temp->next);
				if(temp==NULL)
					fprintf(*temp_dst, " %s", buffer_sub);
				else
					fprintf(*temp_dst, " %u", temp->addr);
				fprintf(*temp_dst, "\n");
			}
		}
		else
			return error_how_could_it_be;
	}
	//-----------------
	/* test: close the temp dst file */
	fclose(*temp_dst);
	//----------------
	/* free the hash table */
	Addr *temp, *temp_shadow;
	for(int i=0; i<HASH_MASK; i++){
		temp		=	addr_table[i];
		temp_shadow	=	temp;
		for(;temp!=NULL;){
			temp_shadow=temp,
			temp=temp->next;
			free(temp_shadow);
		}
	}

	return no_error;
}

static error_t __hash_store(const char *symbol, const uint32_t addr){
	Addr *addr_temp	=	addr_table[hash_32(symbol, HASH_SEED) & HASH_MASK];
	for(; addr_temp->next!=NULL; addr_temp=addr_temp->next)
		/* find the duplicate */
		if(!strcmp(addr_temp->next->symbol,symbol))
			return error_gramma_duplicate_symbol;
	/* store into the table */
	addr_temp->next	=	malloc(sizeof(Addr));
	addr_temp		=	addr_temp->next;
	strcpy(addr_temp->symbol,symbol);
	addr_temp->addr	=	addr;
	return no_error;
}

/* get the Nth(start from 0) token on buffer */
/* buffer must end with \n\0 */
static error_t __get_nth_token(const char *buffer, char *buffer_sub, char n){
	/* initialize the format string */
	char *fmt	=	(char *)malloc(sizeof(char)*4*n);
	fmt[0]		=	'\0';
	for(int i=0; i<n; i++)
		strcat(fmt, "%*s ");
	strcat(fmt,"%s");

	/* get the nth token */
	if(sscanf(buffer,fmt,buffer_sub)!=1)
		return	error_token_not_get;
	return no_error;
}
