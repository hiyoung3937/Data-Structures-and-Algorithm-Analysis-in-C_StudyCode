#include<stdio.h>
#include<time.h>
#include"rand_array.h"//引用随机数组

#define LENGTH 1000    //生成多大的数组

//求最大子序列和
int MaxSubsequenceSum_1(const int A[],int N);//O(N^3)
int MaxSubsequenceSum_2(const int A[],int N);//O(N^2)

int main(void)
{
    clock_t start_t,end_t;
    double total_t;
    
    start_t = clock();
    printf("O(N^3): %d\n",MaxSubsequenceSum_1(rand_array(),LENGTH));
    end_t = clock();
    printf("CPU占用时间: %f\n",total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC);

    start_t = clock();
    printf("O(N^2): %d\n",MaxSubsequenceSum_2(rand_array(),LENGTH));
    end_t = clock();
    printf("CPU占用时间: %f\n",total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC);
}

int MaxSubsequenceSum_1(const int A[],int N)
{
    int ThisSum,MaxSum,i,j,k;

    MaxSum = 0;
    for ( i = 0; i < N; i++)
        for ( j = i; j < N; j++)
        {
            ThisSum = 0;
            for(k = i;  k <= j; k++)
                ThisSum += A[k];

            if(ThisSum > MaxSum)
                MaxSum = ThisSum;
        }
        
    return MaxSum;
}


int MaxSubsequenceSum_2(const int A[],int N)
{
    int ThisSum,MaxSum,i,j,k;

    MaxSum = 0;
    for ( i = 0; i < N; i++)
    {
        ThisSum = 0;
        for ( j = i; j < N; j++)
        {

            ThisSum += A[j];

            if(ThisSum > MaxSum)
                MaxSum = ThisSum;
        }
    }
    return MaxSum;
}