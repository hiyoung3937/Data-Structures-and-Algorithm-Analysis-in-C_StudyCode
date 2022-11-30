#include<stdlib.h>
#include<stdio.h>

#ifndef ARRAY_QUEUE_H
typedef struct _array_queue
{
    int size; //队列的大小
    int num; //当前队列存储数据大小
    int head; //队列头
    int tail; //队列尾
    int *array; //数据存储区
}array_queue;

#define array_queue_is_empty(array_queue) (array_queue->num == 0)
#define array_queue_is_full(array_queue) ((array_queue->num) ==(array_queue->size))

#endif

array_queue * array_queue_create(int size)
{
    array_queue *queue = NULL;

    queue = (array_queue *)malloc(sizeof(array_queue));
    if(queue == NULL)
    {
        return NULL;
    }

    queue->array = (int *)malloc(sizeof(int));
    if(queue->array == NULL)
    {
        free(queue);
        return NULL;
    }

    queue->size = size;
    queue->head = 0;
    queue->num = 0;
    queue->tail = 0;

    return queue;
}

void array_queue_destory(array_queue * queue)
{
    if(queue == NULL)
    {
        return ;
    }

    if(queue->array != NULL)
    {
        free(queue->array);
    }

    free(queue);

    return ;
}

//  入队
int array_queue_enqueue(array_queue *queue, int data) 
{
    /*队列为空，或者队列满时，返回-1*/
    if( (queue == NULL) || (array_queue_is_full(queue)))
    {
        return -1;
    }

    queue->array[queue->tail] = data;
    queue->tail = (queue->tail+1) % (queue->size); //循环队列
    queue->num++;

    return 0;
}

// 出队
int array_queue_dequeue(array_queue *queue, int *data)
{
    /*队列为空，数据存储区为空（为初始化），队列为空时返回-1*/
    if((queue == NULL) || (array_queue_is_empty(queue)) || (data == NULL))
    {
        return -1;
    }

    *data = queue->array[queue->head];
    queue->head = (queue->head +1) % (queue->size);
    queue->num--;

    return 0;
}

void array_queue_dump(array_queue *queue)
{
    int pos = 0;

    if((queue == NULL) || (array_queue_is_empty(queue)))
    {
        printf("\r\n queue is empty");
		return ;
    }

	printf("\r\n size:%d,num:%d,head:%d,tali:%d",
			queue->size,queue->num,queue->head,queue->tail); 

    for(int i = 0;i < queue->num; i++)
    {
        pos = (queue->head+i) % (queue->size);
        printf("\r\n array[%d] = %d",pos,queue->array[pos]);
    }
}