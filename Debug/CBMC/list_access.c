#include<stdio.h>
#include<stdlib.h>

typedef struct list{
	int value;
	struct list *next;
} LIST;

LIST NULL_LIST = {-1, &NULL_LIST};

void main(void){ int malloc_flag_list,defined_list_next,defined_list, defined_iterator, defined_iterator_next;
	LIST *list = malloc(sizeof(LIST)); list->next = &NULL_LIST; malloc_flag_list = 1; defined_list_next = 0; defined_list = 1;
	 
	LIST *iterator;
	
	//defined_iterator = defined_list; defined_iterator_next = defined_list_next;
	for(iterator = list; iterator != &NULL_LIST; iterator = iterator->next){
		if(iterator == &NULL_LIST){printf("line:10:NULL pointer Access in variable list!"); assert(0); return;} printf("value = %d\n", iterator->value);
	}
}
LIST *newList(int value){int max_size_new_list, defined_new_list, malloc_flag_new_list;
	LIST *new_list = malloc(sizeof(LIST)); max_size_new_list = 1; defined_new_list = 1, malloc_flag_new_list = 1;

	new_list->value = value;

	return new_list;
}