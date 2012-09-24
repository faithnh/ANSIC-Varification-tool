#include<stdio.h>
#include<stdlib.h>

int foo(void){/*additional varidation variables*/ int defined_i = 0, basis_location_i = 0,malloc_flag_i = 0,max_size_i = 0,defined_l = 0, basis_location_l = 0, malloc_flag_l = 0,max_size_l = 0; 

	int *i,j,*l; /*additional varidation statement*/ defined_i = 0; defined_l = 0;
	i = malloc(sizeof(int)*10); /*additional varidation statement*/  malloc_flag_i = 1; max_size_i = 10; defined_i = 1;
	l = malloc(sizeof(int)*100); /*additional varidation statement*/  malloc_flag_l = 1; max_size_l = 100; defined_l = 1;
	for(j = 0;j < 100;j++){
		/*additional varidation statement*/ if(defined_l == 0){printf("line:10:pointer variable l is undefined!"); assert(0); } if(0 > j + basis_location_l || j + basis_location_l >= max_size_l){printf("line:10:detected unbound array in variable l!"); assert(0); return 0;} *(l + j) = j;
		/*additional varidation statement*/ if(defined_i == 0){printf("line:11:pointer variable i is undefined!"); assert(0); } if(0 > j + basis_location_i || j + basis_location_i >= max_size_i){printf("line:11:detected unbound array in variable i!"); assert(0); return 0;} i[j] = 1;
	}

	free(i); /*additional varidation statement*/ malloc_flag_i = 0; defined_i = 0;
	free(l); /*additional varidation statement*/ malloc_flag_l = 0; defined_l = 0;

	/*additional varidation statement*/ if(malloc_flag_i == 1){ printf("line:17:detected memory leake in variable i!" ); assert(0);} if(malloc_flag_l == 1){ printf("line:15:detected memory leake in variable l!" ); assert(0);} return 0;
	
}

int *getArray(int size){int malloc_flag_new_int_array, max_size_new_int_array, defined_new_int_array;
	if(size > 1000){
		printf("OVER AA %d",size);
		assert(0);
	}
	int new_int_array = malloc(sizeof(int)*size); malloc_flag_new_int_array = 1; max_size_new_int_array = size; defined_new_int_array = 1;

	return new_int_array;
}

int *getDoubleArray(int size){int malloc_flag_new_int_array, max_size_new_int_array, defined_new_int_array;
	int new_int_array = malloc(sizeof(int)*size*2); malloc_flag_new_int_array = 1; max_size_new_int_array = size*2; defined_new_int_array = 1;

	return new_int_array;
}

int main(void){ int malloc_flag_i, defined_i, max_size_i, malloc_flag_i2, defined_i2, max_size_i2;
	int *i,*i2; defined_i = 0; defined_i2 = 0;
	int iterator;
	i = getArray(100); malloc_flag_i = 1; defined_i = 1; max_size_i = 100;

	i2 = getDoubleArray(100); malloc_flag_i2 = 1; defined_i2 = 1; max_size_i2 = 200;
	for(iterator = 0; iterator <= 10; iterator++){
		printf("FOO %d",foo());
	}

	free(i); malloc_flag_i = 0; defined_i = 0; max_size_i = 0;
	free(i2); malloc_flag_i2 = 0; defined_i2 = 0; max_size_i2 = 0;

	/*additional varidation statement*/ if(malloc_flag_i == 1){ printf("line:46:detected memory leake in variable i!" ); assert(0); return 0;} if(malloc_flag_i2 == 1){ printf("line:46:detected memory leake in variable i2!" ); assert(0); return 0;} return 0;
}