/*PROGRAM_START*///#xinclude<stdio.h>
//#xinclude<stdlib.h>

int main(void){
	int disorder_array[10];
	int i,j,tmp;

	for(i = 0; i < 10; i++){
		for(j = 0; j < 10-i; j++){
			if(disorder_array[j] > disorder_array[j+1]){
				tmp = disorder_array[j];
				disorder_array[j] = disorder_array[j+1];
				disorder_array[j+1] = tmp;
			}
		}
	}
}