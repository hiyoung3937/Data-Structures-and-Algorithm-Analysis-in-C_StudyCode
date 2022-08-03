//selection problem
#include<stdio.h>
void bubble_sort(int arr[], int len);//冒泡

int main(void)
{
    int array_ori[10]={1,2,3,4,6,5,8,9,1,10};
    int len = (int)sizeof(array_ori)/sizeof(*array_ori);
    bubble_sort(array_ori, len);

    for (int i = 0; i < len; i++)
    {
        printf("%d ",array_ori[i]);
    }
    
    return 0;
}


void bubble_sort(int arr[], int len)
{
    int i,j,temp;
    for ( i = 0; i < len; i++) {
        for ( j= 0; j < len-1-i; j++){   
            if(arr[j] > arr[j+1]){
            temp=arr[j];
            arr[j]=arr[j+1];
            arr[j+1]=temp;

            }

        }
        
    }
    
}