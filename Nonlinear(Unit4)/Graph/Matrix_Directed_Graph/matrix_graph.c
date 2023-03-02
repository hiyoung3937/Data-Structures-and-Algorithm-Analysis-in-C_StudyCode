/**
 * C: 邻接矩阵表示的"有向图(Matrix Directed Graph)"
 * @modified from skywang
 * @date 2023/3/2
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAXSIZE 100
#define isLetter(a)  ((((a)>='a')&&((a)<='z')) || (((a)>='A')&&((a)<='Z')))
#define LENGTH(a)  (sizeof(a)/sizeof(a[0]))

// 邻接矩阵结构
typedef struct 
{
    char vertex[MAXSIZE];           // 顶点集合
    int vexnum;                     // 顶点数
    int edgenum;                    // 边数
    int matrix[MAXSIZE][MAXSIZE];   // 邻接矩阵
}MGraph;                            

// 返回元素在邻接矩阵中的位置
int get_position(MGraph g, char ch)
{
    for(int i = 0; i < g.vexnum; i++)
        if(ch == g.vertex[i])
            return i;
    return -1;
}

// 读取一个输入字符(手动输入创建图时使用)
char read_char()
{
    char ch;
    
    do
    {
        ch = getchar();
    } while (!isLetter(ch));
    
    return ch;
}

/*
 * 创建图(自己输入)
 * 直接copy(hiyoung)
 */
MGraph* create_graph()
{
    char c1, c2;
    int v, e;
    int i, p1, p2;
    MGraph* pG;
    
    // 输入"顶点数"和"边数"
    printf("input vertex number: ");
    scanf("%d", &v);
    printf("input edge number: ");
    scanf("%d", &e);
    if ( v < 1 || e < 1 || (e > (v * (v-1))))
    {
        printf("input error: invalid parameters!\n");
        return NULL;
    }
    
    if ((pG=(MGraph*)malloc(sizeof(MGraph))) == NULL )
        return NULL;
    memset(pG, 0, sizeof(MGraph));

    // 初始化"顶点数"和"边数"
    pG->vexnum = v;
    pG->edgenum = e;
    // 初始化"顶点"
    for (i = 0; i < pG->vexnum; i++)
    {
        printf("vertex(%d): ", i);
        pG->vertex[i] = read_char();
    }

    // 初始化"边"
    for (i = 0; i < pG->edgenum; i++)
    {
        // 读取边的起始顶点和结束顶点
        printf("edge(%d):", i);
        c1 = read_char();
        c2 = read_char();

        p1 = get_position(*pG, c1);
        p2 = get_position(*pG, c2);
        if (p1==-1 || p2==-1)
        {
            printf("input error: invalid edge!\n");
            free(pG);
            return NULL;
        }

        pG->matrix[p1][p2] = 1;
    }

    return pG;
}

/*
 * 创建图(用已提供的矩阵)
 */
MGraph* create_example_graph()
{
    char vertex[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'}; //顶点数组
    // 边关系数组
    char edges[][2] = 
    {
        {'A', 'B'}, 
        {'B', 'C'}, 
        {'B', 'E'}, 
        {'B', 'F'}, 
        {'C', 'E'}, 
        {'D', 'C'}, 
        {'E', 'B'}, 
        {'E', 'D'}, 
        {'F', 'G'}
    }; 
    
    int vlen = LENGTH(vertex); //顶点数量
    int elen = LENGTH(edges);  //边数量
    int p1, p2;
    MGraph * pG;

    //输入“顶点数”和“边数”
    if((pG=(MGraph *)malloc(sizeof(MGraph))) == NULL)
        return NULL;
    memset(pG, 0, sizeof(MGraph)); //将pG初始化为0

    //初始化“顶点数”和“边数”
    pG->vexnum = vlen;
    pG->edgenum = elen;
    //初始化“顶点”
    for(int i = 0; i < pG->vexnum; i++)
    {
        pG->vertex[i] = vertex[i];
    }

    //初始化“边”
    for(int i = 0; i < pG->edgenum; i++)
    {
        // 读取边的起始顶点和结束顶点
        p1 = get_position(*pG, edges[i][0]);
        p2 = get_position(*pG, edges[i][1]);

        pG->matrix[p1][p2] = 1;
    }

    return pG;
}

/*
 * 打印矩阵队列图
 */
void print_graph(MGraph G)
{
    int i,j;

    printf("Martix Graph:\n");
    for (i = 0; i < G.vexnum; i++)
    {
        for (j = 0; j < G.vexnum; j++)
            printf("%d ", G.matrix[i][j]);
        printf("\n");
    }
}

void main(void)
{
    MGraph* pG;

    // 自定义"图"(输入矩阵队列)
    // pG = create_graph();
    // 采用已有的"图"
    pG = create_example_graph();

    print_graph(*pG);       // 打印图
}