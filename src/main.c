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
	printf("input file name ----->   ");
	scanf("%s",a), getchar();

	FILE *file;
	assembler_init();
	Error error;
	printf("Error Code %d\n",assembler_pretreatment(a,&file,&error));

	return	0;
}
