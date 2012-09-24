#include<stdio.h>

int foo(void){
	int i;
	int j;
	int a[10];
	for(i = 0; i <= 1000; i++){

		a[i] = 1;		if(!(i < 10)){
			printf("line:7 counter example! i = %d",i);
			assert(0);
		}		
		a[i-1] = 1;		if(!(0 < (i - 1) && (i - 1) < 10) ){
			printf("line:8 counter example! i = %d",i);
			assert(0);
		}
	}
	return 1;
}