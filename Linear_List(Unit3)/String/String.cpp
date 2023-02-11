#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

//简单模式匹配子串
int StrBF(Str str, Str substr)
{
    int i = 0, j = 0, k = i;//串从数组下标0开始

    while (i < str.length && j < substr.length)
    {
        if(str.ch[i] == substr.ch[j])
        {
            ++i; 
            ++j;
        }
        else
        {
            j = 0; //匹配失败，子串重置到开头
            i = ++k; //匹配失败，i从子串的下一个位置开始，k记录了上一次的起始位置
        }

    }
    //跳出循环有两种可能，i == str.length说明已经遍历完主串，匹配失败；
    //j == substr.length,说明子串遍历完成，在主串中成功匹配
    if(j == substr.length)
        return k;
    else 
        return 0;
}

//KMP算法匹配子串(假设串从数组下标1位置开始存储,有BUG)

//获取NEXT数组(假设串从数组下标1位置开始存储)
void Strnext(Str substr, int *next)
{
    int i=1, j=0;   //串从数组下标1位置开始存储，i初值设为1
    next[1] = 0;    //特殊情况，模式串的第一个字符与主串不匹配，赋值为0来表示

    while (i < substr.length)
    {
        if(j == 0 || substr.ch[i] == substr.ch[j])
        {
            ++i;
            ++j;
            next[i] = j;
        }
        else
            j = next[j];
    }
}

//KMP算法
int StrKMP(Str str, Str substr)
{
    int next[20];
    Strnext(substr, next);

    int i = 1, j = 1; //串从数组下标1位置开始存储
    while (i <= str.length && j <= substr.length)
    {
        if( j == 0 || str.ch[i] == substr.ch[j])    
        {
            ++i;
            ++j;
        }
        else
            j = next[j];
    }
    
    if( j > substr.length)
        return i - substr.length;
    else
        return 0;
}

//KMP算法匹配子串(假设串从数组下标1位置开始存储,无BUG)
void Next(char *str,int *next)
{
    int i=1;
    next[1]=0;
    int j=0;
    while (i<strlen(str)) 
    {
        if (j==0||str[i-1]==str[j-1]) 
        {
            i++;
            j++;
            next[i]=j;
        }else
        {
            j=next[j];
        }
    }
}
int KMP(char *str,char *substr)
{
    int next[10];
    Next(substr,next);//根据模式串T,初始化next数组
    int i=1;
    int j=1;

    while (i<=strlen(str)&&j<=strlen(substr)) 
    {
        //j==0:代表模式串的第一个字符就和当前测试的字符不相等；str[i-1]==substr[j-1],
        //如果对应位置字符相等，两种情况下，指向当前测试的两个指针下标i和j都向后移
        if (j==0 || str[i-1]==substr[j-1]) 
        {
            i++;
            j++;
        }
        else
        {
            j=next[j];//如果测试的两个字符不相等，i不动，j变为当前测试字符串的next值
        }
    }
    if (j>strlen(substr)) //如果条件为真，说明匹配成功
    {
        return i-(int)strlen(substr);
    }
    return -1;
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

    char s1[MAXSIZE] = "ababcabcacbab";
    char s2[MAXSIZE] = "abcac";

    Strassign(str1, s1);
    Strassign(str2, s2);

   
    printf("%d\n", StrBF(str1, str2));
    printf("%d\n", KMP(s1,s2));

    StrConcat(str,str1,str2);

    StrSub(substr, str, pos, len);

    StrPrint(substr);
    StrPrint(str);
    Strlength(str);

    return 0;
}