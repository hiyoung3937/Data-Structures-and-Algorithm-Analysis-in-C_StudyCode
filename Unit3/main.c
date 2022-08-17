#include <stdio.h>
#include "function.h" 

int main(void)
{
    //test OK
    // int arr[Arr_N]={1,2,3,4,5,6,7,8,9,10};
    // Arr_PrintList(arr,Arr_N);
    int n = 10;
    Arrtable t = Arr_MakeEmpty();
    for(int i=0;i<t.size;i++)
    {
        t.arr[i]=i+1;
        t.length++;
    }
    Arr_PrintList(t);
    Arr_Find(t,n);

    return 0;
}