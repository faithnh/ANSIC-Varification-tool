/*PROGRAM_START*///#xinclude<stdio.h>
//#xinclude<stdlib.h>

#define SIZE 6

int main(void){
	int array[SIZE] = {1,5,8,1,2,-1};
	int *ptr;
	int tmp, num, count = 1,flag = 0;
	printf("探索したい数字: "); scanf("%d", num);
	for(ptr = array; *ptr != 0  ; ptr++){
		
		tmp = *ptr;
		
		if(tmp == num){
			flag = 1; break;
		}else{
			count++;
		}
	}
	if(flag) printf("%dはarrayの%d番目にあります。\n", num, count);
	else printf("%dは存在しません。\n", num);

	return 0;
}