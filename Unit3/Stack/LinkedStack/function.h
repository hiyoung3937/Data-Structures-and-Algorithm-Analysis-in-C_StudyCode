// linked list stack struct
#include<stdio.h>
#include<stdlib.h>

#define stack_is_empty(stLinkedlist_Stack) (stLinkedlist_Stack->next == NULL)

typedef struct linkedlist_stack //定义结点
{
    int data;
    struct linkedlist_stack *next;
}stLinkedlist_Stack;


stLinkedlist_Stack * linkedliststack_create() //init stack
{
    stLinkedlist_Stack *linkstack = NULL;

    linkstack = (stLinkedlist_Stack *)malloc(sizeof(stLinkedlist_Stack));
    if(linkstack == NULL)
    {
        return NULL;
    }

    linkstack->next = NULL;

    return linkstack;
}

void linkedliststack_destory(stLinkedlist_Stack *linkstack) // destory stack
{
    stLinkedlist_Stack *ptmp = NULL;

    while(!stack_is_empty(linkstack))
    {
        ptmp = linkstack->next; //将结点（address）赋给ptmp
        linkstack->next = linkstack->next->next; //栈指针下移

        free(ptmp); //释放结点
    }

    free(linkstack); //释放结构

    return ;
}

int linkedliststack_push(stLinkedlist_Stack *linkstack , int data) //入栈
{
    stLinkedlist_Stack * ptmp = NULL;

    ptmp = (stLinkedlist_Stack *)malloc(sizeof(stLinkedlist_Stack));
    if(ptmp == NULL)
    {
        return -1;
    }

    ptmp->data = data;
    ptmp->next = linkstack->next; //将结点插入栈头（头插法）
    linkstack->next = ptmp;

    return 0;
}

int linkedliststack_pop(stLinkedlist_Stack *linkstack, int *data)
{
    stLinkedlist_Stack *ptmp = NULL;
    if (data == NULL)
    {
        return -1;
    }

    if (stack_is_empty(linkstack))
    {
        return -1;
    }
    
    *data = linkstack->next->data; //通过指针传递数据，返回栈数据
    ptmp = linkstack->next;  //栈顶赋值给ptmp
    linkstack->next = ptmp->next; //将下一个栈元素，传给栈顶
    
    free(ptmp);

    return 0;
}

void linkedliststack_dump(stLinkedlist_Stack *linkstack)
{
    stLinkedlist_Stack *ptmp = linkstack->next;

    while (ptmp != NULL)
    {
        printf("\n data = %d",ptmp->data);
        ptmp = ptmp->next;
    }

    return ;
}