

int main ( void ) { 
int kuku [ 9 ] [ 9 ] ; 
int i ; int j ; 
for ( i = 0 ; i < 9 ; i ++ ) 
for ( j = 0 ; j < 9 ; j ++ ) 
kuku [ i ] [ j ] = ( i + 1 ) * ( j + 1 ) ; 
printf ( "   " ) ; 
for ( i = 0 ; i < 9 ; i ++ ) printf ( "%3d " , i + 1 ) ; 
printf ( "\n" ) ; 
for ( i = 0 ; i < 9 ; i ++ ) { 
printf ( "%2d:" , i ) ; 
for ( j = 0 ; j <= 9 ; j ++ ) { 
printf ( "%3d " , kuku [ i ] [ j ] ) ; 
} 
printf ( "\n" ) ; 
} 
return 0 ; 
} 