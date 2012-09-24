#include "malloc_number.h"
#include <stdio.h>
#include <stdlib.h>
int static_malloc_number = 1;
void malloc_number(int *set_malloc_number){
	*set_malloc_number = static_malloc_number;
	static_malloc_number++;
}
