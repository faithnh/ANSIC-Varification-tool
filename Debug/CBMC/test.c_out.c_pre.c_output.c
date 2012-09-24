#include<stdio.h>


int main ( void ) { int *max_size_1_a ; int basis_location_1_a ; int *defined_1_a ; int *malloc_flag_1_a ; int *max_size_1_b ; int basis_location_1_b ; int *defined_1_b ; int *malloc_flag_1_b ; 
int a [ 10 ] ; max_size_1_a = malloc(sizeof(int)); *max_size_1_a =  10; basis_location_1_a = 0; defined_1_a = malloc(sizeof(int)); *defined_1_a = 1; malloc_flag_1_a = malloc(sizeof(int)); *malloc_flag_1_a = 0;  printf("<source file=\"test.c\" loc=\"4\">");
printf("<proc text=\"int a [ 10 ] ;\"></proc>");
printf("</source>");
int b [ 10 ] ; max_size_1_b = malloc(sizeof(int)); *max_size_1_b =  10; basis_location_1_b = 0; defined_1_b = malloc(sizeof(int)); *defined_1_b = 1; malloc_flag_1_b = malloc(sizeof(int)); *malloc_flag_1_b = 0;  printf("<source file=\"test.c\" loc=\"5\">");
printf("<proc text=\"int b [ 10 ] ;\"></proc>");
printf("</source>");
int i = 0 ; printf("<source file=\"test.c\" loc=\"6\">");
printf("<proc text=\"int i = 0 ;\"></proc>");
printf("</source>");int j = 0 ; printf("<source file=\"test.c\" loc=\"6\">");
printf("<proc text=\"int j = 0 ;\"></proc>");
printf("</source>");

 i = 9 ; printf("<source file=\"test.c\" loc=\"8\">");
printf("<proc text=\"i = 9 ;\"></proc>");
printf("</source>");
do { 
 i -- ; printf("<source file=\"test.c\" loc=\"10\">");
printf("<proc text=\"i -- ;\"></proc>");
printf("</source>");
if ( i > 0 ) {
}else{
if(*defined_1_b == 0 && *malloc_flag_1_b == 0){
printf("#test.c#:11: detected undefine pointer access in variable b");
 assert(0);
return 1;
}
if(0 > i + basis_location_1_b || i + basis_location_1_b >= *max_size_1_b){
printf("#test.c#:11:detected unbound access in variable b  basis_location = %d (i = %d)\n", basis_location_1_b, i);
assert(0);
return 1;
}

if ( b [ i ] == 0 ) {
}
}
 } 
while ( i > 0 || b [ i ] == 0 ) ; 
 i = 9 ; printf("<source file=\"test.c\" loc=\"12\">");
printf("<proc text=\"i = 9 ;\"></proc>");
printf("</source>");if( (i) == 0 ){ printf("#test.c#:13:detected zero division oparation in expression i ( i = %d )", i); assert(0);return 1; }
if ( 1 / i == 0 ) {
}else{
if( (i) == 0 ){ printf("#test.c#:13:detected zero division oparation in expression i ( i = %d )", i); assert(0);return 1; }
if ( i / i == 1 ) {
}
}
 
while ( 1 / i == 0 || i / i == 1 ) { if(*defined_1_b == 0 && *malloc_flag_1_b == 0){
printf("#test.c#:14: detected undefine pointer access in variable b");
 assert(0);
return 1;
}
if(0 > i + basis_location_1_b || i + basis_location_1_b >= *max_size_1_b){
printf("#test.c#:14:detected unbound access in variable b  basis_location = %d (i = %d)\n", basis_location_1_b, i);
assert(0);
return 1;
}

if ( b [ i ] == 0 ) {
}
 
if ( b [ i ] == 0 ) { 
if(*defined_1_b == 0 && *malloc_flag_1_b == 0){
printf("#test.c#:15: detected undefine pointer access in variable b");
 assert(0);
return 1;
}
if(0 > i + basis_location_1_b || i + basis_location_1_b >= *max_size_1_b){
printf("#test.c#:15:detected unbound access in variable b  basis_location = %d (i = %d)\n", basis_location_1_b, i);
assert(0);
return 1;
}
   b [ i ] = i ; printf("<source file=\"test.c\" loc=\"15\">");
printf("<proc text=\"b [ i ] = i ;\"></proc>");
printf("</source>");
} else { 
if(*defined_1_b == 0 && *malloc_flag_1_b == 0){
printf("#test.c#:17: detected undefine pointer access in variable b");
 assert(0);
return 1;
}
if(0 > i + basis_location_1_b || i + basis_location_1_b >= *max_size_1_b){
printf("#test.c#:17:detected unbound access in variable b  basis_location = %d (i = %d)\n", basis_location_1_b, i);
assert(0);
return 1;
}
  b [ i ] = 0 ; printf("<source file=\"test.c\" loc=\"17\">");
printf("<proc text=\"b [ i ] = 0 ;\"></proc>");
printf("</source>");
} 
 i -- ; printf("<source file=\"test.c\" loc=\"19\">");
printf("<proc text=\"i -- ;\"></proc>");
printf("</source>");if( (i) == 0 ){ printf("#test.c#:13:detected zero division oparation in expression i ( i = %d )", i); assert(0);return 1; }
if ( 1 / i == 0 ) {
}else{
if( (i) == 0 ){ printf("#test.c#:13:detected zero division oparation in expression i ( i = %d )", i); assert(0);return 1; }
if ( i / i == 1 ) {
}
}
 } 











return 0 ; 
} 