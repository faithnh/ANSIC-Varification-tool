#include<stdio.h>
int fibonatti(int num){ num = -1;
	if(num < 0){ printf("line:3: Invalid value in variable num = %d", num); assert(0); return 1; } if(num == 0){
		return 0;
	}else if(num == 1){
		return 1;
	}else{
		return fibonatti(num - 1) + fibonatti(num - 2);
	}
}

int fibonatti_safe(int num){ num = -1; 
	if(num < 0){ return 0; }
	if(num == 0){
		return 0;
	}else if(num == 1){
		return 1;
	}else{
		return fibonatti(num - 1) + fibonatti(num - 2);
	}

}

int main(void){
	int i = fibonatti(-1);

	printf("%d", i);
	return 0;
}



