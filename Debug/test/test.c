#include<stdio.h>
#include<stdlib.h>

int main(void){
	int *ptr;
	int **ptr2;

	*ptr = 10;
	*(*(ptr2 + 1) + 1) = 10;



}