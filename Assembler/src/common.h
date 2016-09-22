#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

typedef char error_t;
#define no_error						0x00
#define error_open_file					0x01
/* grammar error*/
#define error_gramma_label_not_first	0x02
#define error_gramma_declare_incomplete	0x02
#define error_gramma_duplicate_symbol	0x03
#define error_token_not_get				0x04
#define error_gramma_declare_is_keyword	0x05
#define error_gramma_lack_symbol		0x06
#define error_gramma_duplicate_command	0x07
#define error_gramma_unidentified		0x08
#define error_gramma_too_less_argument	0x09
#define error_gramma_too_much_argument	0x0A
#define error_gramma_declare_is_digit	0x0B
#define error_gramma_reg_illegal		0x0C

#define error_malloc					0x0D
#define error_stack_overflow			0xFE

#define error_how_could_it_be			0xFD
typedef unsigned char	uint8_t;
typedef unsigned short	uint16_t;
typedef unsigned int	uint32_t;
typedef short			int16_t;

#define MAX_ERROR_STRLEN	200
typedef struct _Error{
	/* the error line or error message */
	char error_line[MAX_ERROR_STRLEN];
	/* point to the position when grammar error occurs */
	char error_pos;
}Error;

/* the length of data stack*/
#define MAX_DATA_SPACE	(1<<23)

/*==========================================================*/
/* the mask of hash result */
/* enlarge it if hash result collied, when you're trying to change the operator set */
#define HASH_MASK	0x03FF
/* the max length of the reading buffer (also the max lenth of a line )*/
#define MAX_BUF_LEN		500

/*===========================================================================*/
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

/* the operator */
typedef	struct _Op{
	char		name[OP_MXLEN];		/* the name of the operator */
	uint32_t	value;				/* the value of the operator (use with '|') */
	format_t	format;				/* the format of the operator*/
}Op;
/* the hash table that stores the operator value(key is the name) */
extern Op op_hash[HASH_MASK];

/*============================================================================*/

#endif // COMMON_H_INCLUDED
