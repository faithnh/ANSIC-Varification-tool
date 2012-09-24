#include<stdio.h>
int vviterator_2 ; 

int main ( void ) {
/*
int *max_size_1_a ;
int basis_location_1_a ;
int *defined_1_a ;
int *malloc_flag_1_a ;
int **max_size_2_a ;
int *basis_location_2_a ;
int **defined_2_a ;
int **malloc_flag_2_a ;
int *max_size_1_b ;
int basis_location_1_b ;
int *defined_1_b ;
int *malloc_flag_1_b ;
*/
int a [ 10 ] [ 10 ] ;
/*
max_size_1_a = malloc(sizeof(int)); *max_size_1_a =  10; basis_location_1_a = 0; defined_1_a = malloc(sizeof(int)); *defined_1_a = 1; malloc_flag_1_a = malloc(sizeof(int)); *malloc_flag_1_a = 0; max_size_2_a = malloc(( 10)*sizeof(int*)); basis_location_2_a = malloc(( 10)*sizeof(int)); defined_2_a = malloc(( 10)*sizeof(int*)); malloc_flag_2_a = malloc(( 10)*sizeof(int*)); for(vviterator_2 = 0; vviterator_2 <  10; vviterator_2++){ max_size_2_a[vviterator_2] = malloc(sizeof(int)); *max_size_2_a[vviterator_2] =  10; basis_location_2_a[vviterator_2] = 0; defined_2_a[vviterator_2] = malloc(sizeof(int)); *defined_2_a[vviterator_2] = 1; malloc_flag_2_a[vviterator_2] = malloc(sizeof(int)); *malloc_flag_2_a[vviterator_2] = 0; }  printf("<source file=\"test.c\" loc=\"4\">");
printf("<proc text=\"int a [ 10 ] [ 10 ] ;\"></proc>");
printf("</source>");
*/
int b [ 10 ] ;
/*max_size_1_b = malloc(sizeof(int)); *max_size_1_b =  10; basis_location_1_b = 0; defined_1_b = malloc(sizeof(int)); *defined_1_b = 1; malloc_flag_1_b = malloc(sizeof(int)); *malloc_flag_1_b = 0;  printf("<source file=\"test.c\" loc=\"5\">");
printf("<proc text=\"int b [ 10 ] ;\"></proc>");
printf("</source>");
*/
int i = 0 ;
/*
printf("<source file=\"test.c\" loc=\"6\">");
printf("<proc text=\"int i = 0 ;\"></proc>");
printf("</source>");
*/
int j = 0 ;
/*printf("<source file=\"test.c\" loc=\"6\">");
printf("<proc text=\"int j = 0 ;\"></proc>");
printf("</source>");
*/
if ( a [ i ] [ j ] == 0 || ( b [ a [ i ] [ j ] ] == 0 && b [ a [ i ] [ j ] ] == 0 ) ) {
 
/*if(*defined_1_b == 0 && *malloc_flag_1_b == 0){printf("#test.c#:9: detected undefine pointer access in variable b"); assert(0);return 1; } if(0 > i + basis_location_1_b || i + basis_location_1_b >= *max_size_1_b){printf("#test.c#:9:detected unbound access in variable b  basis_location = %d (i = %d)\n", basis_location_1_b, i); assert(0);return 1; } */
b [ i ] = 0 ;
/*
printf("<source file=\"test.c\" loc=\"9\">");
printf("<proc text=\"b [ i ] = 0 ;\"></proc>");
printf("</source>");
*/ 
} 

return 0 ; 
} 