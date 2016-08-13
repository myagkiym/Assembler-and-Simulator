#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

typedef char error_t;
#define no_error						0x00
#define error_open_file					0x01

#define error_gramma_label_not_first	0x02
#define error_gramma_declare_not_first	0x02
#define error_gramma_duplicate_symbol	0x03
#define error_token_not_get				0x04
#define error_gramma_declare_is_keyword	0x05
#define error_gramma_lack_symbol		0x06
#define error_gramma_duplicate_command	0x07
#define error_gramma_unidentified		0x08

#define error_stack_overflow			0xFE
typedef unsigned char	uint8_t;
typedef unsigned int	uint32_t;

#define MAX_ERROR_STRLEN	200
typedef struct _Error{
	/* the error line or error message */
	char error_line[MAX_ERROR_STRLEN];
	/* point to the position when grammar error occurs */
	char error_pos;
}Error;

#endif // COMMON_H_INCLUDED
