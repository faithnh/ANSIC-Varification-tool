#include<stdio.h>
#define DATA 10
int main(void){

	int array[DATA];
	int i;
	i = 0;
	while(i < DATA+1){
		scanf("%d\n", array[i]);
		i++;
	}
	return 0;
}