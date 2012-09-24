#include<stdio.h>
#include<stdlib.h>

#define NUM 102

int foo(void){int max_size_i = 0, basis_location_i = 0, defined_i = 0, malloc_flag_i = 0;
	int *i;
	
	i = malloc(sizeof(i)); max_size_i = 1; basis_location_i = 0; defined_i = 1; malloc_flag_i = 1;
	
	if(defined_i == 0){ printf("line:11: pointer variable i is undefined!"); assert(0); return 0; } *i = NUM;
	
	if(malloc_flag_i == 0){ printf("line:13:free instraction to variable i is invalid! variable i isn't used by malloc or undefined."); assert(0); return 0;} free(i); malloc_flag_i = 0; defined_i = 0;

	if(malloc_flag_i == 1){ printf("line:15: detected memory leake in variable i"); assert(0); return 0;} return 0;
}