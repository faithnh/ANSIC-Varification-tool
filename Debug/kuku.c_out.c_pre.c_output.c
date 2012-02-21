#include<stdio.h>
int vviterator_2 ; 

int main ( void ) { int *max_size_1_kuku ; int basis_location_1_kuku ; int *defined_1_kuku ; int *malloc_flag_1_kuku ; int **max_size_2_kuku ; int *basis_location_2_kuku ; int **defined_2_kuku ; int **malloc_flag_2_kuku ; 
int kuku [ 9 ] [ 9 ] ; max_size_1_kuku = malloc(sizeof(int)); *max_size_1_kuku =  9; basis_location_1_kuku = 0; defined_1_kuku = malloc(sizeof(int)); *defined_1_kuku = 1; malloc_flag_1_kuku = malloc(sizeof(int)); *malloc_flag_1_kuku = 0; max_size_2_kuku = malloc(( 9)*sizeof(int*)); basis_location_2_kuku = malloc(( 9)*sizeof(int)); defined_2_kuku = malloc(( 9)*sizeof(int*)); malloc_flag_2_kuku = malloc(( 9)*sizeof(int*)); for(vviterator_2 = 0; vviterator_2 <  9; vviterator_2++){ max_size_2_kuku[vviterator_2] = malloc(sizeof(int)); *max_size_2_kuku[vviterator_2] =  9; basis_location_2_kuku[vviterator_2] = 0; defined_2_kuku[vviterator_2] = malloc(sizeof(int)); *defined_2_kuku[vviterator_2] = 1; malloc_flag_2_kuku[vviterator_2] = malloc(sizeof(int)); *malloc_flag_2_kuku[vviterator_2] = 0; }  printf("int kuku [ 9 ] [ 9 ] ;\n");

int i ; printf("int i ;\n");
int j ; printf("int j ;\n");

i = 0 ; while( i < 9  ) {
j = 0 ; while( j < 9  ) {
if(*defined_1_kuku == 0 && *malloc_flag_1_kuku == 0){printf("#kuku.c#:8: detected undefine pointer access in variable kuku"); assert(0);return 1; } if(0 > i + basis_location_1_kuku || i + basis_location_1_kuku >= *max_size_1_kuku){printf("#kuku.c#:8:detected unbound access in variable kuku  basis_location = %d (i = %d)\n", basis_location_1_kuku, i); assert(0);return 1; } if(*defined_2_kuku [ i + basis_location_1_kuku ] == 0 && *malloc_flag_2_kuku [ i + basis_location_1_kuku ] == 0){printf("#kuku.c#:8: detected undefine pointer access in variable kuku"); assert(0);return 1; } if(0 > j + basis_location_2_kuku [ i + basis_location_1_kuku ] || j + basis_location_2_kuku [ i + basis_location_1_kuku ] >= *max_size_2_kuku [ i + basis_location_1_kuku ]){printf("#kuku.c#:8:detected unbound access in variable kuku  basis_location = %d (j = %d)\n", basis_location_2_kuku [ i + basis_location_1_kuku ], j); assert(0);return 1; } kuku [ i ] [ j ] = ( i + 1 ) * ( j + 1 ) ; printf("kuku [ i ] [ j ] = ( i + 1 ) * ( j + 1 ) ;\n");

j ++ ; } 
i ++ ; } 
printf ( "   " ) ; printf("printf ( \"   \" ) ;\n");

i = 0 ; while( i < 9  ) {printf ( "%3d " , i + 1 ) ; printf("printf ( \"%3d \" , i + 1 ) ;\n");

i ++ ; } 
printf ( "\n" ) ; printf("printf ( \"\n\" ) ;\n");

i = 0 ; while( i < 9  ) {
printf ( "%2d:" , i ) ; printf("printf ( \"%2d:\" , i ) ;\n");

j = 0 ; while( j <= 9  ) {
if(*defined_1_kuku == 0 && *malloc_flag_1_kuku == 0){printf("#kuku.c#:15: detected undefine pointer access in variable kuku"); assert(0);return 1; } if(0 > i + basis_location_1_kuku || i + basis_location_1_kuku >= *max_size_1_kuku){printf("#kuku.c#:15:detected unbound access in variable kuku  basis_location = %d (i = %d)\n", basis_location_1_kuku, i); assert(0);return 1; } if(*defined_2_kuku [ i + basis_location_1_kuku ] == 0 && *malloc_flag_2_kuku [ i + basis_location_1_kuku ] == 0){printf("#kuku.c#:15: detected undefine pointer access in variable kuku"); assert(0);return 1; } if(0 > j + basis_location_2_kuku [ i + basis_location_1_kuku ] || j + basis_location_2_kuku [ i + basis_location_1_kuku ] >= *max_size_2_kuku [ i + basis_location_1_kuku ]){printf("#kuku.c#:15:detected unbound access in variable kuku  basis_location = %d (j = %d)\n", basis_location_2_kuku [ i + basis_location_1_kuku ], j); assert(0);return 1; } printf ( "%3d " , kuku [ i ] [ j ] ) ; printf("printf ( \"%3d \" , kuku [ i ] [ j ] ) ;\n");

j ++ ; } 

printf ( "\n" ) ; printf("printf ( \"\n\" ) ;\n");

i ++ ; } 

return 0 ; 
} 