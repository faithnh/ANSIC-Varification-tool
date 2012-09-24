#include<stdio.h>



int main ( void ) { int max_size_1_iterator ; int basis_location_1_iterator ; int defined_1_iterator ; int malloc_flag_1_iterator ; int max_size_1_test_array ; int basis_location_1_test_array ; int defined_1_test_array ; int malloc_flag_1_test_array ;
int * iterator ; basis_location_1_iterator = 0; defined_1_iterator = 0; malloc_flag_1_iterator = 0;

int test_array [ 7 ] = { 2 , 3 , 5 , 7 , 11 , 13 , 19 } ; max_size_1_test_array =  7; basis_location_1_test_array = 0; defined_1_test_array = 1; malloc_flag_1_test_array = 0;

iterator = test_array ; max_size_1_iterator = max_size_1_test_array; basis_location_1_iterator = basis_location_1_test_array; defined_1_iterator = defined_1_test_array; malloc_flag_1_iterator = malloc_flag_1_test_array;

while ( * iterator != 12 ) {
if(0 > 0 + basis_location_1_iterator || 0 + basis_location_1_iterator >= max_size_1_iterator){printf("line:13:detected unbound access in variable iterator  basis_location = %d (0)\n", basis_location_1_iterator); assert(0); return 1; } printf ( "%d\n" , * iterator ) ;

iterator = iterator + 1 ; max_size_1_iterator = max_size_1_iterator; basis_location_1_iterator = basis_location_1_iterator + 1; defined_1_iterator = defined_1_iterator; malloc_flag_1_iterator = malloc_flag_1_iterator;
}

return 0 ;
}