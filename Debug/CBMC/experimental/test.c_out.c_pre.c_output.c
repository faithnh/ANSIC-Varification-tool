#include<stdio.h>
int vviterator_2 ; 

int main ( void ) { int *max_size_1_a ; int basis_location_1_a ; int *defined_1_a ; int *malloc_flag_1_a ; int **max_size_2_a ; int *basis_location_2_a ; int **defined_2_a ; int **malloc_flag_2_a ; int *max_size_1_b ; int basis_location_1_b ; int *defined_1_b ; int *malloc_flag_1_b ; 
int a [ 10 ] [ 10 ] ; max_size_1_a = malloc(sizeof(int)); *max_size_1_a =  10; basis_location_1_a = 0; defined_1_a = malloc(sizeof(int)); *defined_1_a = 1; malloc_flag_1_a = malloc(sizeof(int)); *malloc_flag_1_a = 0; max_size_2_a = malloc(( 10)*sizeof(int*)); basis_location_2_a = malloc(( 10)*sizeof(int)); defined_2_a = malloc(( 10)*sizeof(int*)); malloc_flag_2_a = malloc(( 10)*sizeof(int*)); for(vviterator_2 = 0; vviterator_2 <  10; vviterator_2++){ max_size_2_a[vviterator_2] = malloc(sizeof(int)); *max_size_2_a[vviterator_2] =  10; basis_location_2_a[vviterator_2] = 0; defined_2_a[vviterator_2] = malloc(sizeof(int)); *defined_2_a[vviterator_2] = 1; malloc_flag_2_a[vviterator_2] = malloc(sizeof(int)); *malloc_flag_2_a[vviterator_2] = 0; }  printf("<source file=\"test.c\" loc=\"4\">");
printf("<proc text=\"int a [ 10 ] [ 10 ] ;\"></proc>");
printf("</source>");
int b [ 10 ] ; max_size_1_b = malloc(sizeof(int)); *max_size_1_b =  10; basis_location_1_b = 0; defined_1_b = malloc(sizeof(int)); *defined_1_b = 1; malloc_flag_1_b = malloc(sizeof(int)); *malloc_flag_1_b = 0;  printf("<source file=\"test.c\" loc=\"5\">");
printf("<proc text=\"int b [ 10 ] ;\"></proc>");
printf("</source>");
int i = 0 ; printf("<source file=\"test.c\" loc=\"6\">");
printf("<proc text=\"int i = 0 ;\"></proc>");
printf("</source>");int j = 0 ; printf("<source file=\"test.c\" loc=\"6\">");
printf("<proc text=\"int j = 0 ;\"></proc>");
printf("</source>");if( (2) == 0 ){ printf("#test.c#:8:detected zero division oparation in expression 2 (  )"); assert(0);return 1; }
if ( i / 2 == 0 ) {
}
 

if ( i / 2 == 0 ) { 
   if( (( j + 1 )) == 0 ){ printf("#test.c#:9:detected zero mod oparation in expression ( j + 1 ) ( j = %d )", j); assert(0);return 1; } if( (i) == 0 ){ printf("#test.c#:9:detected zero division oparation in expression i ( i = %d )", i); assert(0);return 1; } i = ( 1 % ( j + 1 ) ) / i ; printf("<source file=\"test.c\" loc=\"9\">");
printf("<proc text=\"i = ( 1 %% ( j + 1 ) ) / i ;\"></proc>");
printf("</source>");
   if( (2) == 0 ){ printf("#test.c#:10:detected zero division oparation in expression 2 (  )"); assert(0);return 1; } if( (( j / 2 )) == 0 ){ printf("#test.c#:10:detected zero division oparation in expression ( j / 2 ) ( j = %d )", j); assert(0);return 1; } if( (i) == 0 ){ printf("#test.c#:10:detected zero mod oparation in expression i ( i = %d )", i); assert(0);return 1; } i = ( 1 / ( j / 2 ) ) % i ; printf("<source file=\"test.c\" loc=\"10\">");
printf("<proc text=\"i = ( 1 / ( j / 2 ) ) %% i ;\"></proc>");
printf("</source>");
} 










return 0 ; 
} 