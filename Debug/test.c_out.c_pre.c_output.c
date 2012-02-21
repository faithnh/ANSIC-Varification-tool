#include<stdio.h>
#include<stdlib.h>





int main ( void ) { int *max_size_1_array ; int basis_location_1_array ; int *defined_1_array ; int *malloc_flag_1_array ; int *max_size_1_ptr ; int basis_location_1_ptr ; int *defined_1_ptr ; int *malloc_flag_1_ptr ; 
int array [ 6 ] = { 1 , 5 , 8 , 1 , 2 , - 1 } ; max_size_1_array = malloc(sizeof(int)); *max_size_1_array =  6; basis_location_1_array = 0; defined_1_array = malloc(sizeof(int)); *defined_1_array = 1; malloc_flag_1_array = malloc(sizeof(int)); *malloc_flag_1_array = 0;  printf("int array [ 6 ] = { 1 , 5 , 8 , 1 , 2 , - 1 } ;\n");

int * ptr ; max_size_1_ptr = malloc(sizeof(int)); *max_size_1_ptr = 0;basis_location_1_ptr = 0; defined_1_ptr = malloc(sizeof(int));  *defined_1_ptr = 0;malloc_flag_1_ptr = malloc(sizeof(int)); *malloc_flag_1_ptr = 0; printf("int * ptr ;\n");

int tmp ; printf("int tmp ;\n");
int num ; printf("int num ;\n");
int count = 1 ; printf("int count = 1 ;\n");
int flag = 0 ; printf("int flag = 0 ;\n");

printf ( "探索したい数字: " ) ; printf("printf ( \"探索したい数字: \" ) ;\n");
scanf ( "%d" , num ) ; printf("scanf ( \"%d\" , num ) ;\n");

ptr = array ; max_size_1_ptr = max_size_1_array; basis_location_1_ptr = basis_location_1_array; defined_1_ptr = defined_1_array; malloc_flag_1_ptr = malloc_flag_1_array;  while( * ptr != 0  ) {

if(*defined_1_ptr == 0 && *malloc_flag_1_ptr == 0){printf("#test.c#:13: detected undefine pointer access in variable ptr"); assert(0);return 1; } if(0 > 0 + basis_location_1_ptr || 0 + basis_location_1_ptr >= *max_size_1_ptr){printf("#test.c#:13:detected unbound access in variable ptr  basis_location = %d (0)\n", basis_location_1_ptr); assert(0);return 1; } tmp = * ptr ; printf("tmp = * ptr ;\n");


if ( tmp == num ) { 
flag = 1 ; printf("flag = 1 ;\n");
break ; 
} else { 
count ++ ; printf("count ++ ;\n");

} 
ptr ++ ; basis_location_1_ptr = basis_location_1_ptr + 1;  } 

if ( flag ) printf ( "%dはarrayの%d番目にあります。\n" , num , count ) ; printf("printf ( \"%dはarrayの%d番目にあります。\n\" , num , count ) ;\n");

else printf ( "%dは存在しません。\n" , num ) ; printf("printf ( \"%dは存在しません。\n\" , num ) ;\n");


return 0 ; 
} 