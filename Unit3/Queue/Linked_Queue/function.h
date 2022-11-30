#include<stdlib.h>
#include<stdio.h>

#ifndef LINKED_QUEUE

typedef struct linked_queue_node
{
    int data;
    struct linked_queue_node *next;
}queue_node;

typedef struct linked_queue
{
    int num;
    queue_node *head;
    queue_node *tail;
}linked_queue;

#define linked_queue_is_empty(queue) ((queue->num) == 0)
#endif

/*创建队列头*/
linked_queue *linked_queue_create()
{
    linked_queue *queue = NULL;

    queue = (linked_queue *)malloc(sizeof(linked_queue));
    if(queue == NULL)
    {
        return NULL;
    }

    queue->num = 0;
    queue->head = NULL;
    queue->tail = NULL;

    return queue;
}

//出队
int linked_queue_dequeue(linked_queue *queue, int *data)
{
    queue_node *ptmp = NULL;

    if((queue == NULL) || (linked_queue_is_empty(queue)) || (data == NULL))
    {
        return -1;
    }

    *data = queue->head->data;
    ptmp = queue->head;
    queue->head = queue->head->next;
    queue->num--;

    if(queue->head == NULL) //如果头指针为NULL
    {
        queue->tail = NULL;
    }

    free(ptmp);
    return 0;
}

//入队
int linked_queue_enqueue(linked_queue *queue, int data)
{
    queue_node * ptmp =NULL;
    if(queue == NULL)
    {
        return -1;
    }

    ptmp = (queue_node *)malloc(sizeof(queue_node));
    if(ptmp == NULL)
    {
        return -1;
    }

    ptmp->data = data;
    ptmp->next = NULL;
    if(queue->head == NULL) //空队列
    {
        queue->head = ptmp;
    }
    else
    {
        queue->tail->next = ptmp;
    }
    queue->tail = ptmp;
    queue->num++;

    return 0;
}

void linked_queue_destroy(linked_queue *queue)
{
    
    int data = 0;
    if((queue == NULL) || (linked_queue_is_empty(queue)))
    {
        return ;
    }

    while (!linked_queue_is_empty(queue))
    {
        (void)linked_queue_dequeue(queue,&data);
    }

    free(queue);
    return ;
}

void linked_queue_dump(linked_queue * queue)
{
    queue_node *ptmp;

    if((queue == NULL) || (linked_queue_is_empty(queue)))
    {
        return ;
    }

    ptmp = queue->head;

    printf("\r\n----dump queue num = %d--------",queue->num);
    for(int i =0; ptmp != NULL; ptmp = ptmp->next, i++)
    {
        printf("\r\nnode[%d] = %d",i,ptmp->data);
    }

    printf("\r\n---------------------------------\r\n");
    
	return;
}