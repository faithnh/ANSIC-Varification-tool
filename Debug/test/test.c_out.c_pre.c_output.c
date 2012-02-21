#include<stdio.h>
#include<stdlib.h>



int main ( void ) { 
int * ptr ; int * ptr ; 
int * * ptr2 ; int * * ptr2 ; 

* ptr = 10 ; * ptr = 10 ; 
* ( * ( ptr2 + 1 ) + 1 ) = 10 ; * ( * ( ptr2 + 1 ) + 1 ) = 10 ; 



} int main ( void ) { int * ptr ; int * ptr ; int * * ptr2 ; int * * ptr2 ; * ptr = 10 ; * ptr = 10 ; * ( * ( ptr2 + 1 ) + 1 ) = 10 ; * ( * ( ptr2 + 1 ) + 1 ) = 10 ; } 