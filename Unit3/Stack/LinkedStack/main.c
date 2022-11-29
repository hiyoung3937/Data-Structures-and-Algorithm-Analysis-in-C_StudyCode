#include "function.h"
#include<stdio.h>

int main(void)
{
int i = 0;
	int ret = 0;
	int data = 0;
	stLinkedlist_Stack * linkstack = NULL;

    linkstack = linkedliststack_create();
	if (linkstack == NULL)
	{
		printf("\r\n linkstack create falied.");
        return 0;			
	}
    
	for (i = 0; i < 4; i++)
	{
		ret = linkedliststack_push(linkstack,i);
		if(ret != 0)
		{
		    printf("\r\n stack push %d falied.",i);
		}
	}

    linkedliststack_dump(linkstack);

	for (i = 0; i < 5; i++)
	{
		ret = linkedliststack_pop(linkstack,&data);
		if(ret != 0)
		{
		    printf("\r\n linkstack pop %d falied.", i);
		}
		else
		{
		    printf("\r\n data = %d",data);
		}
	}

	linkedliststack_destory(linkstack);

	return 0;
}