#include<stdio.h>
#include "function.h"

int main(void)
{
	int i = 0;
	int ret = 0;
	stArrayStack * parrStack = NULL;

	printf("\r\n create size = 4 arrayStack.");

	parrStack = arrayStack_create(4);
	if (parrStack == NULL)
	{
	    printf("\r\n create size = 4 arrayStack faided.");
		return 0;
	}

	arrayStack_push(parrStack,1);
	arrayStack_push(parrStack,2);
	arrayStack_push(parrStack,3);
	arrayStack_push(parrStack,4);


	arrayStack_dump(parrStack);
		
	arrayStack_push_new(parrStack,4);

	arrayStack_pop(parrStack);

	arrayStack_dump(parrStack);

	arrayStack_destory(parrStack);
    
	return 0;
}