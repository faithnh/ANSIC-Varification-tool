#include<stdio.h>


int main ( void ) { int *max_size_1_array ; int basis_location_1_array ; int *defined_1_array ; int *malloc_flag_1_array ; 

printf("<source file=#dquot#test_s.c#dquot# loc=#dquot#5#dquot#>");
printf("<prog text=#dquot#int array [ 10 ] ;#dquot#></prog>");
printf("<before_variable_info>");printf("</before_variable_info>");int array [ 10 ] ; max_size_1_array = malloc(sizeof(int)); *max_size_1_array =  10; basis_location_1_array = 0; defined_1_array = malloc(sizeof(int)); *defined_1_array = 1; malloc_flag_1_array = malloc(sizeof(int)); *malloc_flag_1_array = 0;  printf("<after_variable_info>");printf("</after_variable_info>");printf("</source>");
printf("<source file=#dquot#test_s.c#dquot# loc=#dquot#6#dquot#>");
printf("<prog text=#dquot#int i ;#dquot#></prog>");
printf("<before_variable_info>");printf("</before_variable_info>");int i ; printf("<after_variable_info>");printf("</after_variable_info>");printf("</source>");
printf("<source file=#dquot#test_s.c#dquot# loc=#dquot#7#dquot#>");
printf("<prog text=#dquot#i = 0 ;#dquot#></prog>");
printf("<before_variable_info>");printf("<variable type=#dquot#int#dquot# name=#dquot#i#dquot# value=#dquot#%d#dquot#></variable>", i);
printf("</before_variable_info>"); i = 0 ; printf("<after_variable_info>");printf("<variable type=#dquot#int#dquot# name=#dquot#i#dquot# value=#dquot#%d#dquot#></variable>", i);
printf("</after_variable_info>");printf("</source>");printf("<source file=#dquot#test_s.c#dquot# loc=#dquot#8#dquot#>");
printf("<prog text=#dquot#i &lt; 10 + 1#dquot#></prog>");
printf("<before_variable_info>");printf("<variable type=#dquot#int#dquot# name=#dquot#i#dquot# value=#dquot#%d#dquot#></variable>", i);
printf("</before_variable_info>");
if ( i < 10 + 1 ) {
}
 printf("</source>");
while ( i < 10 + 1 ) { 
printf("<source file=#dquot#test_s.c#dquot# loc=#dquot#9#dquot#>");
printf("<prog text=#dquot#scanf ( &quot;%%d\\n&quot; , array [ i ] ) ;#dquot#></prog>");
printf("<before_variable_info>");printf("<variable type=#dquot#int [ 10 ]#dquot# name=#dquot#array#dquot# value=#dquot##dquot#></variable>");
printf("<variable type=#dquot#int#dquot# name=#dquot#i#dquot# value=#dquot#%d#dquot#></variable>", i);
printf("</before_variable_info>"); if(0 > i + basis_location_1_array || i + basis_location_1_array >= *max_size_1_array){
printf("#test_s.c#:9:detected unbound access in variable array  basis_location = %d (i = %d)\n", basis_location_1_array, i);
printf("<error type = #dquot#Unbound Access#dquot# variable=#dquot#array#dquot#>");
printf("<expression text=#dquot#i#dquot# value=#dquot#%d#dquot#></expression>",i);
printf("<basic_location value=#dquot#%d#dquot#></basic_location>", basis_location_1_array);
printf("</error>");
printf("</source>");
assert(0);
return 1;
}
 scanf ( "%d\n" , array [ i ] ) ; printf("<after_variable_info>");printf("<variable type=#dquot#int [ 10 ]#dquot# name=#dquot#array#dquot# value=#dquot##dquot#></variable>");
printf("<variable type=#dquot#int#dquot# name=#dquot#i#dquot# value=#dquot#%d#dquot#></variable>", i);
printf("</after_variable_info>");printf("</source>");
printf("<source file=#dquot#test_s.c#dquot# loc=#dquot#10#dquot#>");
printf("<prog text=#dquot#i ++ ;#dquot#></prog>");
printf("<before_variable_info>");printf("<variable type=#dquot#int#dquot# name=#dquot#i#dquot# value=#dquot#%d#dquot#></variable>", i);
printf("</before_variable_info>"); i ++ ; printf("<after_variable_info>");printf("<variable type=#dquot#int#dquot# name=#dquot#i#dquot# value=#dquot#%d#dquot#></variable>", i);
printf("</after_variable_info>");printf("</source>");printf("<source file=#dquot#test_s.c#dquot# loc=#dquot#8#dquot#>");
printf("<prog text=#dquot#i &lt; 10 + 1#dquot#></prog>");

if ( i < 10 + 1 ) {
}
 printf("</source>");} 

return 0 ; 
} 