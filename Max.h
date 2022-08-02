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