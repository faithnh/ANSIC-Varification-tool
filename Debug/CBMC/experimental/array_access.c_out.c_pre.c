//#xinclude<stdio.h>
//#xinclude<stdlib.h>


int array_access(int x){
 int arrays[10];
 int i;
 if(x > 10) x = 10;
 for(i = 0; i < x; i++){
  printf("%d", arrays[i]);
 }

 return arrays[i-1];
}

int main(){
 int *d_arrays = malloc(sizeof(int)*10);

 int **arrays_2 = malloc(sizeof(int*)*2);

 int i,j;

 for(i = 0; i < 2; i++){
  arrays_2[i] = malloc(sizeof(int)*2);
  for(j = 0; j <= 2 ; j++){
   arrays_2[i][j] = i*2+j*4;
  }
 }
}
