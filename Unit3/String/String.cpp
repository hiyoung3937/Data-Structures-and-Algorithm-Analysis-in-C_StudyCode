#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100

typedef struct 
{
    char *ch;   
    int length; //String 长度
}Str;

//字符串赋值
int Strassign(Str &str, char *ch)
{
    if(str.ch)
        free(str.ch);   //释放原串空间
    
    int len =0;
    char *c = ch;
    while (*c)  //求串的长度
    {
        ++len;
        ++c;
    }
    if(len == 0)    //如果ch为空串，直接返回空串
    {
        str.ch = NULL;
        str.length = 0;
        return 1;
    }
    else
    {
        str.ch = (char*)malloc((len+1) *sizeof(char));  //len+1是多留一位给“\0”
        if(str.ch == NULL)  //分配失败
            return 0;   
        else
        {
            c = ch;
            for(int i = 0; i <= len; ++i, ++c)  //使用“<=”可以将原字符串的“\0”复制到新串中
                str.ch[i] = *c; 
            str.length = len;
            return 1;
        }
    }
    
}

//取串长
int Strlength(Str str)
{
    printf("%d\n",str.length);
    return str.length;
}

//串比较
int StrCompare(Str s1, Str s2)
{
    for(int i=0; i<s1.length && i<s2.length; ++i)
    {
        if(s1.ch[i] != s2.ch[i])
            return s1.ch[i] - s2.ch[i];
    }

    return s1.length - s2.length;
}

//将两串首尾相连
int StrConcat(Str &str, Str str1, Str str2)
{
    if(str.ch)
    {
        free(str.ch);   //释放原串空间
        str.ch = NULL;
    }

    str.ch = (char*)malloc((str1.length + str2.length + 1)* sizeof(char));
    if(str.ch == NULL)  //分配失败
        return 0;

    //将str1复制到新串
    for (int i =0; i< str1.length; ++i)  
    {
        str.ch[i] = str1.ch[i];
    }
    
    //将str2复制到新串
    for (int j =0; j<= str2.length; ++j)  
    {
        str.ch[str1.length+j] = str2.ch[j];
    }

    str.length = str1.length + str2.length;
    return 1;
}

//求子串,求str串中从pos位置开始长为len的子串
int StrSub(Str &substr , Str str, int pos, int len)
{
    if(pos < 0 || pos > str.length || len < 0 || len > str.length - pos)
        return 0;
    if(substr.ch)
    {
        free(substr.ch);
        substr.ch = NULL;
    }

    if(len == 0)
    {
        substr.ch = NULL;
        substr.length = 0;
        return 1;
    }
    else
    {
        substr.ch = (char *)malloc((len + 1) * sizeof(char));
        int i = pos;
        int j =0;
        while (i < pos+len)
        {
            substr.ch[j] = str.ch[i];
            ++i;
            ++j;
        }
        substr.ch[j] = '\0';
        substr.length = len;
        return 1;
    }
}


//清空串
int StrClear(Str &str)
{
    if(str.ch)
    {
        free(str.ch);
        str.ch = NULL;
    }

    str.length = 0;
    return 1;
}


//打印字符串内容
int StrPrint(Str str)
{
    //字符串为空
    if(str.length == 0)
        return 0;
    
    printf("%s\n",str.ch);

    return 1;
}


int main(void)
{
    Str str, str1, str2, substr; 
    int pos = 0;
    int len = 5;
    str.ch = NULL;
    str1.ch = NULL;
    str2.ch = NULL;
    substr.ch = NULL;

    char s1[MAXSIZE] = "hello world,";
    char s2[MAXSIZE] = "hello world!";
    
    Strassign(str1, s1);
    Strassign(str2, s2);

    StrConcat(str,str1,str2);

    StrSub(substr, str, pos, len);

    StrPrint(substr);
    StrPrint(str);
    Strlength(str);

    return 0;
}