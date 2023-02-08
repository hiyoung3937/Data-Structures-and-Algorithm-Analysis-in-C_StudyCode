#include <stdlib.h>

#define ARR_N 10 //数组大小
 
typedef struct Arrtable //顺序表的数据结构
{
    int * arr;//创建一个名为Arr的数组
    int length;//记录当前顺序表的长度
    int size;//记录顺序表定义的最大容量
}Arrtable;


//简单数组实现表
void Arr_PrintList(Arrtable table)//打印表元素 OK
{
    for(int i=0; i < table.length; i++)
    {
        if(table.arr[i] == '\0') //pointer should be '\0',int should be NULL
            exit(0);
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

void Arr_Find(Arrtable table,int n)//返回元素首次出现的位置  OK
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

void Arr_Insert(Arrtable table,int InsertPos,int Element)//在某位置插入元素 OK
{
    if (InsertPos < 0 || InsertPos > table.length) //插入位置是否合理
    {
        printf("Array Insertion Position Error");
        exit(0);
    }    

    if(table.length == table.size)
    {
        table.arr = (int*)realloc(table.arr,(table.size + 1)*sizeof(int));
        if (!table.arr)
        {
            printf("Error");
            exit(0);
        }
        table.arr += 1;
    }

    for(int i = table.length-1; i >= InsertPos-1; i--)
    {
        table.arr[i+1] = table.arr[i];
    }
    table.arr[InsertPos-1] = Element;

    table.length++;
}

void Arr_Delete(Arrtable table,int DelDataPos)//删除表中某位置元素 OK
{
    if(DelDataPos < 0 || DelDataPos > table.length)//删除位置是否合理
    {
        printf("Array Delete Position Error");
        exit(0);
    }

    for (int i = DelDataPos; i < table.length; i++)
    {   
        table.arr[i-1]=table.arr[i];
    }
    table.arr[table.length-1] = 0;
    table.length--;
}