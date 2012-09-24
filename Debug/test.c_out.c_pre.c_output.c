#include<stdio.h>


int main ( void ) { int *max_size_1_a ; int basis_location_1_a ; int *defined_1_a ; int *malloc_flag_1_a ; int *max_size_1_b ; int basis_location_1_b ; int *defined_1_b ; int *malloc_flag_1_b ; 
printf("<source file=#dquot#test.c#dquot# loc=#dquot#4#dquot#>");
printf("<prog text=#dquot#int a [ 10 ] ;#dquot#></prog>");
printf("<before_variable_info>");printf("</before_variable_info>");int a [ 10 ] ; max_size_1_a = malloc(sizeof(int)); *max_size_1_a =  10; basis_location_1_a = 0; defined_1_a = malloc(sizeof(int)); *defined_1_a = 1; malloc_flag_1_a = malloc(sizeof(int)); *malloc_flag_1_a = 0;  printf("<after_variable_info>");printf("</after_variable_info>");printf("</source>");
printf("<source file=#dquot#test.c#dquot# loc=#dquot#5#dquot#>");
printf("<prog text=#dquot#int b [ 10 ] ;#dquot#></prog>");
printf("<before_variable_info>");printf("</before_variable_info>");int b [ 10 ] ; max_size_1_b = malloc(sizeof(int)); *max_size_1_b =  10; basis_location_1_b = 0; defined_1_b = malloc(sizeof(int)); *defined_1_b = 1; malloc_flag_1_b = malloc(sizeof(int)); *malloc_flag_1_b = 0;  printf("<after_variable_info>");printf("</after_variable_info>");printf("</source>");
printf("<source file=#dquot#test.c#dquot# loc=#dquot#6#dquot#>");
printf("<prog text=#dquot#int i = 0 ;#dquot#></prog>");
printf("<before_variable_info>");printf("</before_variable_info>");int i = 0 ; printf("<after_variable_info>");printf("</after_variable_info>");printf("</source>");printf("<source file=#dquot#test.c#dquot# loc=#dquot#6#dquot#>");
printf("<prog text=#dquot#int j = 0 ;#dquot#></prog>");
printf("<before_variable_info>");printf("</before_variable_info>");int j = 0 ; printf("<after_variable_info>");printf("</after_variable_info>");printf("</source>");

printf("<source file=#dquot#test.c#dquot# loc=#dquot#8#dquot#>");
printf("<prog text=#dquot#i = 9 ;#dquot#></prog>");
printf("<before_variable_info>");printf("<variable type=#dquot#int#dquot# name=#dquot#i#dquot# value=#dquot#%d#dquot#></variable>", i);
printf("</before_variable_info>"); i = 9 ; printf("<after_variable_info>");printf("<variable type=#dquot#int#dquot# name=#dquot#i#dquot# value=#dquot#%d#dquot#></variable>", i);
printf("</after_variable_info>");printf("</source>");
do { 
printf("<source file=#dquot#test.c#dquot# loc=#dquot#10#dquot#>");
printf("<prog text=#dquot#i -- ;#dquot#></prog>");
printf("<before_variable_info>");printf("<variable type=#dquot#int#dquot# name=#dquot#i#dquot# value=#dquot#%d#dquot#></variable>", i);
printf("</before_variable_info>"); i -- ; printf("<after_variable_info>");printf("<variable type=#dquot#int#dquot# name=#dquot#i#dquot# value=#dquot#%d#dquot#></variable>", i);
printf("</after_variable_info>");printf("</source>");printf("<source file=#dquot#test.c#dquot# loc=#dquot#11#dquot#>");
printf("<prog text=#dquot#i &gt 0 || b [ i ] == 0#dquot#></prog>");
printf("<before_variable_info>");printf("<variable type=#dquot#int#dquot# name=#dquot#i#dquot# value=#dquot#%d#dquot#></variable>", i);
printf("<variable type=#dquot#int [ 10 ]#dquot# name=#dquot#b#dquot# value=#dquot##dquot#></variable>");
printf("<variable type=#dquot#int#dquot# name=#dquot#i#dquot# value=#dquot#%d#dquot#></variable>", i);
printf("</before_variable_info>");
if ( i > 0 ) {
}else{
if(0 > i + basis_location_1_b || i + basis_location_1_b >= *max_size_1_b){
printf("#test.c#:11:detected unbound access in variable b  basis_location = %d (i = %d)\n", basis_location_1_b, i);
printf("<error type = #dquot#Unbound Access#dquot# variable=#dquot#b#dquot#>");
printf("<expression text=#dquot#i#dquot# value=#dquot#%d#dquot#></expression>",i);
printf("<basic_location value=#dquot#%d#dquot#></basic_location>", basis_location_1_b);
printf("</error>");
printf("</source>");
assert(0);
return 1;
}

if ( b [ i ] == 0 ) {
}
}
 printf("</source>");} 
while ( i > 0 || b [ i ] == 0 ) ; 
printf("<source file=#dquot#test.c#dquot# loc=#dquot#12#dquot#>");
printf("<prog text=#dquot#i = 9 ;#dquot#></prog>");
printf("<before_variable_info>");printf("<variable type=#dquot#int#dquot# name=#dquot#i#dquot# value=#dquot#%d#dquot#></variable>", i);
printf("</before_variable_info>"); i = 9 ; printf("<after_variable_info>");printf("<variable type=#dquot#int#dquot# name=#dquot#i#dquot# value=#dquot#%d#dquot#></variable>", i);
printf("</after_variable_info>");printf("</source>");printf("<source file=#dquot#test.c#dquot# loc=#dquot#13#dquot#>");
printf("<prog text=#dquot#1 / i == 0 || i / i == 1#dquot#></prog>");
printf("<before_variable_info>");printf("<variable type=#dquot#int#dquot# name=#dquot#i#dquot# value=#dquot#%d#dquot#></variable>", i);
printf("<variable type=#dquot#int#dquot# name=#dquot#i#dquot# value=#dquot#%d#dquot#></variable>", i);
printf("<variable type=#dquot#int#dquot# name=#dquot#i#dquot# value=#dquot#%d#dquot#></variable>", i);
printf("</before_variable_info>");
if ( 1 / i == 0 ) {
}else{

if ( i / i == 1 ) {
}
}
 printf("</source>");
while ( 1 / i == 0 || i / i == 1 ) { printf("<source file=#dquot#test.c#dquot# loc=#dquot#14#dquot#>");
printf("<prog text=#dquot#b [ i ] == 0#dquot#></prog>");
if(0 > i + basis_location_1_b || i + basis_location_1_b >= *max_size_1_b){
printf("#test.c#:14:detected unbound access in variable b  basis_location = %d (i = %d)\n", basis_location_1_b, i);
printf("<error type = #dquot#Unbound Access#dquot# variable=#dquot#b#dquot#>");
printf("<expression text=#dquot#i#dquot# value=#dquot#%d#dquot#></expression>",i);
printf("<basic_location value=#dquot#%d#dquot#></basic_location>", basis_location_1_b);
printf("</error>");
printf("</source>");
assert(0);
return 1;
}

if ( b [ i ] == 0 ) {
}
 printf("</source>");
if ( b [ i ] == 0 ) { 
printf("<source file=#dquot#test.c#dquot# loc=#dquot#15#dquot#>");
printf("<prog text=#dquot#b [ i ] = i ;#dquot#></prog>");
printf("<before_variable_info>");printf("<variable type=#dquot#int [ 10 ]#dquot# name=#dquot#b#dquot# value=#dquot##dquot#></variable>");
printf("<variable type=#dquot#int#dquot# name=#dquot#i#dquot# value=#dquot#%d#dquot#></variable>", i);
printf("<variable type=#dquot#int#dquot# name=#dquot#i#dquot# value=#dquot#%d#dquot#></variable>", i);
printf("</before_variable_info>");if(0 > i + basis_location_1_b || i + basis_location_1_b >= *max_size_1_b){
printf("#test.c#:15:detected unbound access in variable b  basis_location = %d (i = %d)\n", basis_location_1_b, i);
printf("<error type = #dquot#Unbound Access#dquot# variable=#dquot#b#dquot#>");
printf("<expression text=#dquot#i#dquot# value=#dquot#%d#dquot#></expression>",i);
printf("<basic_location value=#dquot#%d#dquot#></basic_location>", basis_location_1_b);
printf("</error>");
printf("</source>");
assert(0);
return 1;
}
   b [ i ] = i ; printf("<after_variable_info>");printf("<variable type=#dquot#int [ 10 ]#dquot# name=#dquot#b#dquot# value=#dquot##dquot#></variable>");
printf("<variable type=#dquot#int#dquot# name=#dquot#i#dquot# value=#dquot#%d#dquot#></variable>", i);
printf("</after_variable_info>");printf("</source>");
} else { 
printf("<source file=#dquot#test.c#dquot# loc=#dquot#17#dquot#>");
printf("<prog text=#dquot#b [ i ] = 0 ;#dquot#></prog>");
printf("<before_variable_info>");printf("<variable type=#dquot#int [ 10 ]#dquot# name=#dquot#b#dquot# value=#dquot##dquot#></variable>");
printf("<variable type=#dquot#int#dquot# name=#dquot#i#dquot# value=#dquot#%d#dquot#></variable>", i);
printf("</before_variable_info>");if(0 > i + basis_location_1_b || i + basis_location_1_b >= *max_size_1_b){
printf("#test.c#:17:detected unbound access in variable b  basis_location = %d (i = %d)\n", basis_location_1_b, i);
printf("<error type = #dquot#Unbound Access#dquot# variable=#dquot#b#dquot#>");
printf("<expression text=#dquot#i#dquot# value=#dquot#%d#dquot#></expression>",i);
printf("<basic_location value=#dquot#%d#dquot#></basic_location>", basis_location_1_b);
printf("</error>");
printf("</source>");
assert(0);
return 1;
}
  b [ i ] = 0 ; printf("<after_variable_info>");printf("<variable type=#dquot#int [ 10 ]#dquot# name=#dquot#b#dquot# value=#dquot##dquot#></variable>");
printf("<variable type=#dquot#int#dquot# name=#dquot#i#dquot# value=#dquot#%d#dquot#></variable>", i);
printf("</after_variable_info>");printf("</source>");
} 
printf("<source file=#dquot#test.c#dquot# loc=#dquot#19#dquot#>");
printf("<prog text=#dquot#i -- ;#dquot#></prog>");
printf("<before_variable_info>");printf("<variable type=#dquot#int#dquot# name=#dquot#i#dquot# value=#dquot#%d#dquot#></variable>", i);
printf("</before_variable_info>"); i -- ; printf("<after_variable_info>");printf("<variable type=#dquot#int#dquot# name=#dquot#i#dquot# value=#dquot#%d#dquot#></variable>", i);
printf("</after_variable_info>");printf("</source>");printf("<source file=#dquot#test.c#dquot# loc=#dquot#13#dquot#>");
printf("<prog text=#dquot#1 / i == 0 || i / i == 1#dquot#></prog>");
printf("<before_variable_info>");printf("<variable type=#dquot#int#dquot# name=#dquot#i#dquot# value=#dquot#%d#dquot#></variable>", i);
printf("<variable type=#dquot#int#dquot# name=#dquot#i#dquot# value=#dquot#%d#dquot#></variable>", i);
printf("<variable type=#dquot#int#dquot# name=#dquot#i#dquot# value=#dquot#%d#dquot#></variable>", i);
printf("</before_variable_info>");printf("</source>");} 











return 0 ; 
} 