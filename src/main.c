#include "main.h"
#include "assembler.h"
//---------
#include "assembler_pretreatment.h"
//--------
#include "hash.h"
#include "common.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MASK 0x03FF
int main(void){
	char a[1000];
	char b[1000];
	printf("input file name ----->   ");
	scanf("%s",a), getchar();
	strcpy(b,a);

	assembler_init();
	Error error;

	assembler_pretreatment_stage0(a,strcat(b,"$.txt"));
	strcpy(a,b);
	printf("Error Code %d\n",assembler_pretreatment_stage1(b,strcat(a,"$.txt"),&error));

	return	0;
}
