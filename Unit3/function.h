#include <stdlib.h>
#include "var.h"

//简单数组实现表
int Arr_PrintList(Arrtable table)//打印表元素 OK
{
    for(int i=0; i<table.length; i++)
    {
        if(table.arr[i] == '\0'){ //pointer should be '\0',int should be NULL
            printf("Not Initialized");
            break;
        }
        else 
            printf("Array[%d]:%d \n",i,table.arr[i]);
    }

}

Arrtable Arr_MakeEmpty()//初始化空表  OK
{
    Arrtable t;
    t.arr=(int*)malloc(ARR_N * sizeof(int));//初始化表
    if(!t.arr)
    {
        printf("Initialized Fail");
        exit(0);
    }
    else    
        printf("Initialized Success\n");
    t.length = 0;//当前长度为0
    t.size = ARR_N;//顺序表的最大长度

    return t;
}

void Arr_Find(Arrtable table,int n)//返回关键字首次出现的位置  OK
{
    int found;
    for(int i=0; i<table.length; i++){
        if(n == table.arr[i] )
        {
            printf("%d第一次出现位置是Array[%d]\n",n,i);
            found = 1;
        }
    }
    if(found != 1)
        printf("NOT FOUND Number %d\n",n);
}

int Arr_Insert()//在某位置插入元素
{
    
}

int Arr_Dekete()//删除表中某元素
{

}