int vviterator_2 ;
#include<stdio.h>
#include<stdlib.h>

void main ( void ) { int max_size_1_array_v ; int basis_location_1_array_v ; int defined_1_array_v ; int malloc_flag_1_array_v ; int max_size_1_array_2 ; int basis_location_1_array_2 ; int defined_1_array_2 ; int malloc_flag_1_array_2 ; int *max_size_2_array_2 ; int *basis_location_2_array_2 ; int *defined_2_array_2 ; int *malloc_flag_2_array_2 ; int max_size_1_p ; int basis_location_1_p ; int defined_1_p ; int malloc_flag_1_p ; int max_size_1_q ; int basis_location_1_q ; int defined_1_q ; int malloc_flag_1_q ;
int array_v [ 10 ] ; max_size_1_array_v =  10; basis_location_1_array_v = 0; defined_1_array_v = 1; malloc_flag_1_array_v = 0;
int array_2 [ 10 ] [ 10 ] ; max_size_1_array_2 =  10; basis_location_1_array_2 = 0; defined_1_array_2 = 1; malloc_flag_1_array_2 = 0; max_size_2_array_2 = malloc(( 10)*sizeof(int)); basis_location_2_array_2 = malloc(( 10)*sizeof(int)); defined_2_array_2 = malloc(( 10)*sizeof(int)); malloc_flag_2_array_2 = malloc(( 10)*sizeof(int)); for(vviterator_2 = 0; vviterator_2 <  10; vviterator_2++){ max_size_2_array_2[vviterator_2] =  10; basis_location_2_array_2[vviterator_2] = 0; defined_2_array_2[vviterator_2] = 1; malloc_flag_2_array_2[vviterator_2] = 0; }
int sum = 0 ;

int i , j ;

int * p , * q ;

q = malloc ( 5 * sizeof ( int ) ) ; max_size_1_q = 5 * 1; basis_location_1_q = 0; defined_1_q = 1; malloc_flag_1_q = 1;

for ( i = 0 ; i < 5 ; i ++ ) {
if(0 > i + basis_location_1_q || i + basis_location_1_q >= max_size_1_q){printf("line:18:detected unbound access in variable q  basis_location = %d (i = %d)\n", basis_location_1_q, i); assert(0); return; } q [ i ] = i + 1 ;
}

//for ( p = q ; * p != 4 ; p ++ ) {
//if(0 > 0 + basis_location_1_p || 0 + basis_location_1_p >= max_size_1_p){printf("line:22:detected unbound access in variable p  basis_location = %d (0)\n", basis_location_1_p); assert(0); return; } sum += * p ;
//}



for ( i = 0 ; i < 10 ; i ++ ) {
for ( j = 0 ; j < 10 ; j ++ ) {
if(0 > i + basis_location_1_array_2 || i + basis_location_1_array_2 >= max_size_1_array_2){printf("line:29:detected unbound access in variable array_2  basis_location = %d (i = %d)\n", basis_location_1_array_2, i); assert(0); return; } if(0 > j + basis_location_2_array_2 [ i + basis_location_1_array_2 ] || j + basis_location_2_array_2 [ i + basis_location_1_array_2 ] >= max_size_2_array_2 [ i + basis_location_1_array_2 ]){printf("line:29:detected unbound access in variable array_2  basis_location = %d (j = %d)\n", basis_location_2_array_2 [ i + basis_location_1_array_2 ], j); assert(0); return; } array_2 [ i ] [ j ] = 1 ;
}
}

for ( j = 0 ; j < 10 ; j ++ ) {
if(0 > j + basis_location_1_array_v || j + basis_location_1_array_v >= max_size_1_array_v){printf("line:34:detected unbound access in variable array_v  basis_location = %d (j = %d)\n", basis_location_1_array_v, j); assert(0); return; } array_v [ j ] = 1 ;
}

for ( j = 0 ; j < 10 ; j ++ ) {
if(0 > j + basis_location_1_array_v || j + basis_location_1_array_v >= max_size_1_array_v){printf("line:38:detected unbound access in variable array_v  basis_location = %d (j = %d)\n", basis_location_1_array_v, j); assert(0); return; } sum += array_v [ j ] ;
}

for ( j = 0 ; j <= 10 ; j ++ ) {
if(0 > i + basis_location_1_array_v || i + basis_location_1_array_v >= max_size_1_array_v){printf("line:42:detected unbound access in variable array_v  basis_location = %d (i = %d)\n", basis_location_1_array_v, i); assert(0); return; } printf ( "%d" , array_v [ i ] ) ;
}
}