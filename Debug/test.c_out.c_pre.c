




int main ( void ) { 
int array [ 6 ] = { 1 , 5 , 8 , 1 , 2 , - 1 } ; 
int * ptr ; 
int tmp ; int num ; int count = 1 ; int flag = 0 ; 
printf ( "’Tõ‚µ‚½‚¢”š: " ) ; scanf ( "%d" , num ) ; 
for ( ptr = array ; * ptr != 0 ; ptr ++ ) { 

tmp = * ptr ; 

if ( tmp == num ) { 
flag = 1 ; break ; 
} else { 
count ++ ; 
} 
} 
if ( flag ) printf ( "%d‚Íarray‚Ì%d”Ô–Ú‚É‚ ‚è‚Ü‚·B\n" , num , count ) ; 
else printf ( "%d‚Í‘¶İ‚µ‚Ü‚¹‚ñB\n" , num ) ; 

return 0 ; 
} 