#include<stdio.h>

int main(void){
	int ans;
	int a = 1, b = 2, c = 3;

	ans = a + b;
	ans = ans + ans;
	ans = ans + c;
	printf("ans = %d", ans);
	assert(0);
}