#include<stdio.h>
int vviterator_2 ; 

int main ( void ) { int *max_size_1_kuku ; int basis_location_1_kuku ; int *defined_1_kuku ; int *malloc_flag_1_kuku ; int **max_size_2_kuku ; int *basis_location_2_kuku ; int **defined_2_kuku ; int **malloc_flag_2_kuku ; 
int kuku [ 9 ] [ 9 ] ; max_size_1_kuku = malloc(sizeof(int)); *max_size_1_kuku =  9; basis_location_1_kuku = 0; defined_1_kuku = malloc(sizeof(int)); *defined_1_kuku = 1; malloc_flag_1_kuku = malloc(sizeof(int)); *malloc_flag_1_kuku = 0; max_size_2_kuku = malloc(( 9)*sizeof(int*)); basis_location_2_kuku = malloc(( 9)*sizeof(int)); defined_2_kuku = malloc(( 9)*sizeof(int*)); malloc_flag_2_kuku = malloc(( 9)*sizeof(int*)); for(vviterator_2 = 0; vviterator_2 <  9; vviterator_2++){ max_size_2_kuku[vviterator_2] = malloc(sizeof(int)); *max_size_2_kuku[vviterator_2] =  9; basis_location_2_kuku[vviterator_2] = 0; defined_2_kuku[vviterator_2] = malloc(sizeof(int)); *defined_2_kuku[vviterator_2] = 1; malloc_flag_2_kuku[vviterator_2] = malloc(sizeof(int)); *malloc_flag_2_kuku[vviterator_2] = 0; }  printf("<source file=\"kuku.c\" loc=\"4\">");
printf("<proc text=\"int kuku [ 9 ] [ 9 ] ;\"></proc>");
printf("</source>");
int i ; printf("<source file=\"kuku.c\" loc=\"5\">");
printf("<proc text=\"int i ;\"></proc>");
printf("</source>");int j ; printf("<source file=\"kuku.c\" loc=\"5\">");
printf("<proc text=\"int j ;\"></proc>");
printf("</source>");
i = 0 ; while( i < 9  ) {
j = 0 ; while( j < 9  ) {
kuku [ i ] [ j ] = ( i + 1 ) * ( j + 1 ) ; printf("<source file=\"kuku.c\" loc=\"8\">");
printf("<proc text=\"kuku [ i ] [ j ] = ( i + 1 ) * ( j + 1 ) ;\"></proc>");
printf("</source>");
j ++ ; } 
i ++ ; } 
printf ( "   " ) ; printf("<source file=\"kuku.c\" loc=\"9\">");
printf("<proc text=\"printf ( \"   \" ) ;\"></proc>");
printf("</source>");
i = 0 ; while( i < 9  ) {printf ( "%3d " , i + 1 ) ; printf("<source file=\"kuku.c\" loc=\"10\">");
printf("<proc text=\"printf ( \"%%3d \" , i + 1 ) ;\"></proc>");
printf("</source>");
i ++ ; } 
printf ( "\n" ) ; printf("<source file=\"kuku.c\" loc=\"11\">");
printf("<proc text=\"printf ( \"\\n\" ) ;\"></proc>");
printf("</source>");
i = 0 ; while( i < 9  ) {
printf ( "%2d:" , i ) ; printf("<source file=\"kuku.c\" loc=\"13\">");
printf("<proc text=\"printf ( \"%%2d:\" , i ) ;\"></proc>");
printf("</source>");
j = 0 ; while( j <= 9  ) {
printf ( "%3d " , kuku [ i ] [ j ] ) ; printf("<source file=\"kuku.c\" loc=\"15\">");
printf("<proc text=\"printf ( \"%%3d \" , kuku [ i ] [ j ] ) ;\"></proc>");
printf("</source>");
j ++ ; } 

printf ( "\n" ) ; printf("<source file=\"kuku.c\" loc=\"17\">");
printf("<proc text=\"printf ( \"\\n\" ) ;\"></proc>");
printf("</source>");
i ++ ; } 

return 0 ; 
} 