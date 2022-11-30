#include "function.h"

int main(void)
{
    int i = 0;
	int data = 0;
	int ret = 0;
	linked_queue * queue;

	queue = linked_queue_create();
	if (queue == NULL)
	{
		printf("\r\nlist queue create falied..");
		return 0;
	}

	for (i = 0; i < 5; i++)
	{
		(void)linked_queue_enqueue(queue,i);
	}
	linked_queue_dump(queue);

    ret = linked_queue_dequeue(queue,&data);
	if(ret != 0)
	{
		printf("\r\nlist queue dequeue %d falied.",data);
	}
	printf("\r\nlist queue dequeue %d",data);
	linked_queue_dump(queue);


    ret = linked_queue_dequeue(queue,&data);
	if(ret != 0)
	{
		printf("\r\nlist queue dequeue %d failed.",data);
	}
    printf("\r\nlist queue dequeue %d",data);
	linked_queue_dump(queue);

	printf("\r\nlist queue enqueue %d",data);
	(void)linked_queue_enqueue(queue,data);
	linked_queue_dump(queue);

    linked_queue_destroy(queue);
	return 0;
}