#include <stdio.h>
#include <time.h>
#include "variable.h"//全局变量
#include "rand_array.h"//引用随机数组
#include "Max.h"//三者中最大值

//#define LENGTH 1000    //生成多大的数组

//求最大子序列和
int MaxSubsequenceSum_1(const int A[],int N);//O(N^3)
int MaxSubsequenceSum_2(const int A[],int N);//O(N^2)
int MaxSubsequenceSum_3(const int A[],int N);//O(NlogN)
static int MaxSubSum(const int A[],int Left,int Right);//O(NlogN)

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

    start_t = clock();
    printf("O(NlogN): %d\n",MaxSubsequenceSum_3(rand_array(),LENGTH));
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


int MaxSubsequenceSum_3(const int A[],int N)
{
    return MaxSubSum(A, 0, N - 1);
}

static int MaxSubSum(const int A[],int Left,int Right)
{
    int MaxLeftSum, MaxRightSum;
    int MaxLeftBorderSum, MaxRightBorderSum;
    int LeftBorderSum, RightBorderSum;
    int Center, i;

    if (Left == Right) // base case
        if (A[Left] > 0)
            return A[Left];
    else
        return 0;
    
    Center = (Left+Right)/2;
    MaxLeftSum = MaxSubSum(A, Left, Center);
    MaxRightSum = MaxSubSum(A, Center+1, Right);
    
    MaxLeftBorderSum = 0;
    LeftBorderSum = 0;
    for(i=Center; i>=Left; i--)
    {
        LeftBorderSum +=A[i];
        if(LeftBorderSum > MaxLeftBorderSum)
            MaxLeftBorderSum = LeftBorderSum;
    }

    MaxRightBorderSum = 0;
    RightBorderSum = 0;
    for(i=Center+1; i<=Right; i++)
    {
        RightBorderSum +=A[i];
        if(RightBorderSum > MaxRightBorderSum)
            MaxRightBorderSum = RightBorderSum;
    }

    return Max(MaxLeftSum, MaxRightSum, MaxLeftBorderSum+MaxRightBorderSum);


}

