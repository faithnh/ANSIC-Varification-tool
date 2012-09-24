#include<stdio.h>
#include<stdlib.h>

#define SIZE 2
int array_access(int x){
	int arrays[10];
	int i;
	if(x > 10) x = 10;
	for(i = 0; i < x; i++){
		printf("%d", arrays[i]);
	}

	return arrays[i-1];
}

int main(){
	int *d_arrays = malloc(sizeof(int)*10);

	int **arrays_2 = malloc(sizeof(int*)*SIZE);

	int i,j;

	for(i = 0; i < SIZE; i++){
		arrays_2[i] = malloc(sizeof(int)*SIZE);
		for(j = 0; j <= SIZE ; j++){
			arrays_2[i][j] = i*2+j*4;
		}
	}
}