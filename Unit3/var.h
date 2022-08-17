#define ARR_N 10 //数组大小
 
typedef struct Arrtable //顺序表的数据结构
{
    int * arr;//创建一个名为Arr的数组
    int length;//记录当前顺序表的长度
    int size;//记录顺序表定义的最大容量
}Arrtable;
