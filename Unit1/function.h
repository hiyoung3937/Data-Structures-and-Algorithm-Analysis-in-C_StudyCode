//冒泡排序
void bubble_sort(int arr[], int len)//int len = (int)sizeof(arr)/sizeof(*arr);
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

//返回三者中最大
int Max(int a,int b,int c)
{
    int temp;
    if(a>b)
    {
        temp = a;
        if(c > temp)
            temp = c;
    }    
    else
    {
        temp = b;
        if(c > temp)
            temp = c;
    }

    return temp;
}

//二分查找
int BinarySearch(int A[], int X, int N)//查找X是否在数组中
{
    int Low, Mid, High;

    Low = 0;
    High =N-1;
    while (Low <= High) 
    {
        Mid=(Low+High)/2;
        if( A[Mid] < X )
            Low = Mid + 1;
        else
        if( A[Mid] > X )
            High = Mid - 1;
        else
            return Mid;
    }
    
    return -1;
}

//欧几里得算法求最大公因数
unsigned int God(unsigned int M, unsigned int N)//默认M >= N(if M < N第一轮循环会交换)
{
    unsigned int Rem;
    while (N>0)
    {
        Rem = M % N;
        M = N;
        N = Rem;
    }
    
    return M;
}

int IsEven(int N)
{
    if(N % 2 == 0)
        return 1;
    else
        return 0;
}

//求整数幂X^n
long int Pow(long int X, unsigned int N)
{
    if(X == 0)
    return 1;
    if(N == 1)
    return X;
    if(IsEven(N))
        return Pow(X*X, N/2);
    else
        return Pow(X*X, N/2) *X; 
        // return Pow(X, N-1) *X;
}