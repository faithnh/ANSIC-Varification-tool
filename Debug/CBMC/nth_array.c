#include<stdio.h>
#include<stdlib.h>


#define SIZE 5


typedef struct pointer_test{
	int *a;
} POINTER_TEST;

int main(void){
	POINTER_TEST **pointer_test2;
	int array_2nd[SIZE][SIZE]; 
	int array_3rd[SIZE][SIZE][SIZE]; 
	int *pt_array_2nd[SIZE]; 
	int **pt_array_3rd[SIZE]; 
	int ***ptonly_array_3rd;
	int **test_pointer[SIZE][SIZE]; 
	int **a;
	int i,j,l,m;

	int **array4[5][5];



	pointer_test2 = malloc(SIZE*sizeof(POINTER_TEST*)); 

	for(i = 0; i < SIZE; i++){
		 pointer_test2[i] = calloc(SIZE, sizeof(POINTER_TEST));
		for(j = 0; j < SIZE; j++){
			pointer_test2[i][j].a = calloc(1, sizeof(int));
			*(pointer_test2[i][j].a) = 1;
		}
	}

	for(i = 0; i < 5; i++){
		for(j = 0; j < 5; j++){
			array4[i][j] = calloc(SIZE, sizeof(int*)); 
			for(l = 0; l < SIZE; l++){
				array4[i][j][l] = calloc(SIZE, sizeof(int)); 
				for(m = 0; m < SIZE; m++){
					array4[i][j][l][m] = i*1000 + j*100 + l*SIZE + m*1;
			 }
		 }
		}
	}

	for(i = 0; i < SIZE; i++){
		pt_array_2nd[i] = malloc(sizeof(int)*SIZE); 
		for(j = 0; j < SIZE; j++){
			*(pt_array_2nd[i]+j) = SIZE + i;
		}
	}

	for(i = 0; i < SIZE; i++){
		pt_array_3rd[i] = malloc(sizeof(int *)*SIZE); 
		for(j = 0; j < SIZE; j++){
			*(pt_array_3rd[i] + j) = malloc(sizeof(int)*(SIZE + j)); 
			for(l = 0; l < SIZE + j ; l++){
				*(*(pt_array_3rd[i] + j) + l) = SIZE + i + j;
		 }
		}
	}

	ptonly_array_3rd = malloc(sizeof(int **)*SIZE); 
	for(i = 0; i < SIZE; i++){
		*(ptonly_array_3rd + i) = malloc(sizeof(int *) * (SIZE +i)); 
		for(j = 0; j < SIZE + i; j++){
			*(*(ptonly_array_3rd + i) + j) = calloc(SIZE + j, sizeof(int)); 
		}
	}

	pt_array_2nd[0] = realloc(pt_array_2nd[0], sizeof(int)*(SIZE +1)); //max_size_2_pt_array_2nd[0] = 0; max_size_2_pt_array_2nd = SIZE + 1;
	pt_array_2nd[1] = realloc(pt_array_2nd[2], sizeof(int)*(SIZE +1)); 
	a = pt_array_2nd; //max_size_1_a = max_size_1_pt_array_2nd; max_size_2_a = max_size_2_pt_array_2nd;
	*(*(pt_array_3rd[0] + (a[9][1] + - 11)) + 3) = 1;
	(*(pt_array_3rd[0]+(a[9][1] + - 11)))[3] = 1;
	*(*(*pt_array_3rd + **a - 1) + 2) = 1;
	*(*(*pt_array_3rd + **a - 1) + 2) = 1;
	printf("%d\n", **a);


	*(*array4[1][2]+(**a - 1)) = 1;
	*(**(array4[1] + 2) - **a - 1) = 1;
	*((**a - 1)+*array4[1][2]) = 1;
	*( **a - 1 + **(array4[1] + 2)) = 1;


	for(i = 0; i < SIZE; i++){

		for(j = 0; j < SIZE + i; j++){
			free(ptonly_array_3rd[i][j]);// max_size_3_pt_only_array[i][j] = 0;
		}
		free(ptonly_array_3rd[i]);// max_size_2_pt_only_array[i] = 0; free(max_size_3_pt_only_array[i]);
	}
	free(ptonly_array_3rd);// max_size_1_pt_only_array = 0; free(max_size_2_pt_only_array); free(max_size_3_pt_only_array);

	return 0;
}