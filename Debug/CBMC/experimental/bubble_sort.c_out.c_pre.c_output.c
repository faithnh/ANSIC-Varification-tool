#include<stdio.h>
#include<stdlib.h>
int malloc_number = 1 ; 


int main ( void ) { int *max_size_1_disorder_array ; int basis_location_1_disorder_array ; int *defined_1_disorder_array ; int *malloc_flag_1_disorder_array ; 
int disorder_array [ 10 ] ; max_size_1_disorder_array = malloc(sizeof(int)); *max_size_1_disorder_array =  10; basis_location_1_disorder_array = 0; defined_1_disorder_array = malloc(sizeof(int)); *defined_1_disorder_array = 1; malloc_flag_1_disorder_array = malloc(sizeof(int)); *malloc_flag_1_disorder_array = 0;  
int i , j , tmp ; 

i = 0 ; while( i < 10  ) {
j = 0 ; while( j < 10 - i  ) {
if ( disorder_array [ j ] > disorder_array [ j + 1 ] ) { 
if(0 > j + basis_location_1_disorder_array || j + basis_location_1_disorder_array >= *max_size_1_disorder_array){printf("#../../POBUDIC/Debug/CBMC/experimental/bubble_sort.c#:11:detected unbound access in variable disorder_array  basis_location = %d (j = %d)\n", basis_location_1_disorder_array, j); assert(0);return 1; } tmp = disorder_array [ j ] ; 
if(0 > j + basis_location_1_disorder_array || j + basis_location_1_disorder_array >= *max_size_1_disorder_array){printf("#../../POBUDIC/Debug/CBMC/experimental/bubble_sort.c#:12:detected unbound access in variable disorder_array  basis_location = %d (j = %d)\n", basis_location_1_disorder_array, j); assert(0);return 1; } if(0 > j + 1 + basis_location_1_disorder_array || j + 1 + basis_location_1_disorder_array >= *max_size_1_disorder_array){printf("#../../POBUDIC/Debug/CBMC/experimental/bubble_sort.c#:12:detected unbound access in variable disorder_array  basis_location = %d (j + 1 = %d)\n", basis_location_1_disorder_array, j + 1); assert(0);return 1; } disorder_array [ j ] = disorder_array [ j + 1 ] ; 
if(0 > j + 1 + basis_location_1_disorder_array || j + 1 + basis_location_1_disorder_array >= *max_size_1_disorder_array){printf("#../../POBUDIC/Debug/CBMC/experimental/bubble_sort.c#:13:detected unbound access in variable disorder_array  basis_location = %d (j + 1 = %d)\n", basis_location_1_disorder_array, j + 1); assert(0);return 1; } disorder_array [ j + 1 ] = tmp ; 
} 
j ++ ; } 
i ++ ; } 


} 