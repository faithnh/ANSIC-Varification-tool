#include<stdio.h>
#define KUKU 9
int main(void){
	int kuku[KUKU][KUKU];
	int i,j;
	for(i = 0; i < KUKU; i++)
		for(j = 0; j < KUKU; j++)
			kuku[i][j] = (i + 1) * (j + 1);
	printf("   ");
	for(i = 0; i < KUKU; i++) printf("%3d ", i+1);
	printf("\n");
	for(i = 0; i < KUKU; i++){
		printf("%2d:", i);
		for(j = 0; j <= KUKU; j++){
			printf("%3d ", kuku[i][j]);
		}
		printf("\n"); 
	}
	return 0;
}