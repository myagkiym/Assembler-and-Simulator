#include "main.h"
#include "assembler.h"
#include "simulator.h"
#include "hash.h"
#include "common.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MASK 0x03FF
int main(void){
	char a[1000];
	char b[1000];
//	printf("input src file name ----->   ");
//	scanf("%s",a), getchar();
//	printf("input dst file name ----->   ");
//	scanf("%s",b), getchar();

//==============
strcpy(a,"queen.txt");
strcpy(b,"hello.s");
//============
	assembler_init();

	Error error;

	printf("Assembler done, Error Code %d\n",assembler(a, b, &error));

	simulator_init();

	simulator(b, &error);

	return	0;
}
