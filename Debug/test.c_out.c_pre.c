




int main ( void ) { 
int array [ 6 ] = { 1 , 5 , 8 , 1 , 2 , - 1 } ; 
int * ptr ; 
int tmp ; int num ; int count = 1 ; int flag = 0 ; 
printf ( "�T������������: " ) ; scanf ( "%d" , num ) ; 
for ( ptr = array ; * ptr != 0 ; ptr ++ ) { 

tmp = * ptr ; 

if ( tmp == num ) { 
flag = 1 ; break ; 
} else { 
count ++ ; 
} 
} 
if ( flag ) printf ( "%d��array��%d�Ԗڂɂ���܂��B\n" , num , count ) ; 
else printf ( "%d�͑��݂��܂���B\n" , num ) ; 

return 0 ; 
} 