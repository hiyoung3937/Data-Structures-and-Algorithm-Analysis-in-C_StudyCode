#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct array_stack
{
    int size; //stack size
    int pos; //当前栈的元素个数，即栈顶元素下标
    int *array; //数据存储区（数组指针）
}stArrayStack;

#define arrayStack_size(arrayStack) (arrayStack->size)
#define arrayStack_is_empty(arrayStack) (arrayStack->pos == -1)
#define arrayStack_is_full(arrayStack)  (arrayStack->pos == (arrayStack->size-1))


//入栈
int arrayStack_push(stArrayStack *parrStack,int data)
{
    if(arrayStack_is_full(parrStack))
    {
        return -1;
    }

    parrStack->pos++;
    parrStack->array[parrStack->pos] = data;

    return 0;
}

// 创建并初始化数组栈
stArrayStack *arrayStack_create(int size)
{
    stArrayStack *parrStack = NULL;

    parrStack = (stArrayStack *)malloc(sizeof(stArrayStack)); //init arrayStack
    if (parrStack == NULL) //init error
    {
        return NULL;
    }
    
    parrStack->size = size;
    parrStack->pos = -1;
    parrStack->array = (int *)malloc(sizeof(int) * size); //生成数组
    if(parrStack->array == NULL) //init error
    {
        free(parrStack);
        return NULL;
    }

    return parrStack;
}

void arrayStack_destory(stArrayStack *parrStack)
{
    if(parrStack == NULL)
    {
        return ;
    }

    if(parrStack->array != NULL)
    {
        free(parrStack->array);
        return ;
    }

    free(parrStack);

    return ;
}

//出栈
int arrayStack_pop(stArrayStack * parrStack) //出栈
{
    int top_data = 0;

    if (arrayStack_is_empty(parrStack))
    {
        return -1;
    }

    //先出栈再减少下标
    top_data = parrStack->array[parrStack->pos];
    parrStack->pos--;

    return top_data;
}

int arrayStack_push_new(stArrayStack *parrStack, int data)
{
    int *ptmp = NULL;

    //如果栈未满，则直接插入
    if(!arrayStack_is_full(parrStack))
    {
        return(arrayStack_push(parrStack,data));
    }

    ptmp = (int *) malloc(2 * parrStack->size *sizeof(int));
    if(ptmp == NULL)
    {
        return -1;
    }

    //  void *memcpy(void *str1, const void *str2, size_t n) 从存储区 str2 复制 n 个字节到存储区 str1
    memcpy(ptmp,parrStack->array,parrStack->size *sizeof(int));

    free(parrStack->array);

    parrStack->array = ptmp;
    parrStack->size = 2*parrStack->size;
    parrStack->pos++;
    parrStack->array[parrStack->pos] = data;

    return 0;
}

void arrayStack_dump(stArrayStack *parrStack)
{
    int i =0;

    if(arrayStack_is_empty(parrStack))
    {
        printf("\n arrayStack is empty");
        return ;
    }

    printf("\narrayStack size =%d,pos=%d",parrStack->size,parrStack->pos);

    for ( i = 0; i <= parrStack->pos; i++)
    {
        printf("\n array[%d] = %d",i,parrStack->array[i]);
    }
}