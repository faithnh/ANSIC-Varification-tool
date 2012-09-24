#include<stdio.h>
#include<stdlib.h>
int malloc_number = 1 ; 



int array_access ( int x ) { int *max_size_1_arrays ; int basis_location_1_arrays ; int *defined_1_arrays ; int *malloc_flag_1_arrays ; 
int arrays [ 10 ] ; max_size_1_arrays = malloc(sizeof(int)); *max_size_1_arrays =  10; basis_location_1_arrays = 0; defined_1_arrays = malloc(sizeof(int)); *defined_1_arrays = 1; malloc_flag_1_arrays = malloc(sizeof(int)); *malloc_flag_1_arrays = 0;  
int i ; 
if ( x > 10 ) x = 10 ; 
i = 0 ; while( i < x  ) {
if(0 > i + basis_location_1_arrays || i + basis_location_1_arrays >= *max_size_1_arrays){printf("#../../POBUDIC/Debug/CBMC/experimental/array_access.c#:10:detected unbound access in variable arrays  basis_location = %d (i = %d)\n", basis_location_1_arrays, i); assert(0);return 1; } printf ( "%d" , arrays [ i ] ) ; 
i ++ ; } 


return arrays [ i - 1 ] ; 
} 

int main ( ) { int *max_size_1_d_arrays ; int basis_location_1_d_arrays ; int *defined_1_d_arrays ; int *malloc_flag_1_d_arrays ; int *max_size_1_arrays_2 ; int basis_location_1_arrays_2 ; int *defined_1_arrays_2 ; int *malloc_flag_1_arrays_2 ; int *max_size_2_arrays_2 ; int *basis_location_2_arrays_2 ; int *defined_2_arrays_2 ; int *malloc_flag_2_arrays_2 ; 
int * d_arrays = malloc(sizeof(int)*(1 * 10)) ; malloc_flag_1_d_arrays = malloc(sizeof(int)) ; *malloc_flag_1_d_arrays = malloc_number ; malloc_number++ ; max_size_1_d_arrays = malloc(sizeof(int)); *max_size_1_d_arrays = 0; basis_location_1_d_arrays = 0; defined_1_d_arrays = malloc(sizeof(int)); *defined_1_d_arrays = 0; malloc_flag_1_d_arrays = malloc(sizeof(int)); *malloc_flag_1_d_arrays = 0; *max_size_1_d_arrays = 1 * 10; basis_location_1_d_arrays = 0; *defined_1_d_arrays = 1; 

int * * arrays_2 = malloc(sizeof(int *)*(1 * 2)) ; malloc_flag_1_arrays_2 = malloc(sizeof(int)) ; *malloc_flag_1_arrays_2 = malloc_number ; malloc_number++ ; max_size_1_arrays_2 = malloc(sizeof(int)); *max_size_1_arrays_2 = 0; basis_location_1_arrays_2 = 0; defined_1_arrays_2 = malloc(sizeof(int)); *defined_1_arrays_2 = 0; malloc_flag_1_arrays_2 = malloc(sizeof(int)); *malloc_flag_1_arrays_2 = 0; *max_size_1_arrays_2 = 1 * 2; basis_location_1_arrays_2 = 0; *defined_1_arrays_2 = 1; max_size_2_arrays_2 = malloc((1 * 2)*sizeof(int)); basis_location_2_arrays_2 = malloc((1 * 2)*sizeof(int)); defined_2_arrays_2 = malloc((1 * 2)*sizeof(int)); malloc_flag_2_arrays_2 = malloc((1 * 2)*sizeof(int)); 

int i , j ; 

i = 0 ; while( i < 2  ) {
if(0 > i + basis_location_1_arrays_2 || i + basis_location_1_arrays_2 >= *max_size_1_arrays_2){printf("#../../POBUDIC/Debug/CBMC/experimental/array_access.c#:24:detected unbound access in variable arrays_2  basis_location = %d (i = %d)\n", basis_location_1_arrays_2, i); assert(0);return 1; } arrays_2 [ i ] = malloc(sizeof(int)*(1 * 2)) ; malloc_flag_2_arrays_2 [ i + basis_location_1_arrays_2 ] = malloc_number ; malloc_number++ ; max_size_2_arrays_2 [ i + basis_location_1_arrays_2 ] = 1 * 2; basis_location_2_arrays_2 [ i + basis_location_1_arrays_2 ] = 0; defined_2_arrays_2 [ i + basis_location_1_arrays_2 ] = 0; 
j = 0 ; while( j <= 2  ) {
if(0 > i + basis_location_1_arrays_2 || i + basis_location_1_arrays_2 >= *max_size_1_arrays_2){printf("#../../POBUDIC/Debug/CBMC/experimental/array_access.c#:26:detected unbound access in variable arrays_2  basis_location = %d (i = %d)\n", basis_location_1_arrays_2, i); assert(0);return 1; } if(0 > j + basis_location_2_arrays_2 [ i + basis_location_1_arrays_2 ] || j + basis_location_2_arrays_2 [ i + basis_location_1_arrays_2 ] >= max_size_2_arrays_2 [ i + basis_location_1_arrays_2 ]){printf("#../../POBUDIC/Debug/CBMC/experimental/array_access.c#:26:detected unbound access in variable arrays_2  basis_location = %d (j = %d)\n", basis_location_2_arrays_2 [ i + basis_location_1_arrays_2 ], j); assert(0);return 1; } arrays_2 [ i ] [ j ] = i * 2 + j * 4 ; 
j ++ ; } 
i ++ ; } 


} 