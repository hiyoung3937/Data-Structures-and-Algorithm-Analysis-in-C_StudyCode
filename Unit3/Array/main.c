#include <stdio.h>
#include "function.h" 

int main(void)
{
    //test OK
    // int arr[Arr_N]={1,2,3,4,5,6,7,8,9,10};
    // Arr_PrintList(arr,Arr_N);
    int n = 4; //传入元素
    Arrtable t = Arr_MakeEmpty();
    for(int i=0;i<t.size;i++)
    {
        t.arr[i]=i+1;
        t.length++;
    }
    printf("原数组\n");
    Arr_PrintList(t);

    printf("查找某元素第一次出现的位置\n");
    Arr_Find(t,n);

    printf("插入元素\n");
    Arr_Insert(t,n,10);
    Arr_PrintList(t);

    printf("删除元素\n");
    Arr_Delete(t,n);
    Arr_PrintList(t);

    return 0;
}