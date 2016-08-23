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
	printf("input src file name ----->   ");
	scanf("%s",a), getchar();
	printf("input dst file name ----->   ");
	scanf("%s",b), getchar();

	assembler_init();

	Error error;

	printf("Error Code %d\n",assembler(a, b, &error));

	return	0;
}
