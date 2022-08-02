#include <stdlib.h>
#include <time.h>
#include "variable.h"//全局变量


int * rand_array() //C可以通过指定不带索引的数组名来返回一个指向数组的指针
{

    static int arr[ARRAY]={};
    srand((unsigned) time(NULL)); //用时间做种，每次产生随机数不一样


    for (int i = 0; i < ARRAY; i++)
    {
        int number = rand() % RANGE + 1;  //产生1-100的随机数
        arr[i] = number;
    }

/*
    for (int j = 0; j < ARRAY; j++)
    {
        printf("%d ",arr[j]);
    }

*/    
    return arr;
}
