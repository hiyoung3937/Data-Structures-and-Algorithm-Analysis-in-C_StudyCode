/**
 * C: 邻接表表示的"有向图(List Directed Graph)"
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

// 邻接表中表对应的链表的顶点
typedef struct ArcNode
{
    int adjvex;                 //该边所指向的顶点的位置
    struct ArcNode *next_edge;  //指向下一条边的位置
}ArcNode;

// 邻接表中表的顶点
typedef struct VNode
{
    char data;              // 顶点信息
    ArcNode *first_edge;    // 指向第一条依附该顶点的边
}VNode;

// 邻接表
typedef struct 
{
    int vexnum;     // 图的顶点的数目
    int edgenum;    // 图的边的数目
    VNode vertex[MAXSIZE];  //邻接表
}LGraph;

// 返回元素在邻接矩阵中的位置
int get_position(LGraph g, char ch)
{
    for(int i = 0; i < g.vexnum; i++)
        if(ch == g.vertex[i].data)
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
 * 将node链接到list的末尾
 */
void link_last(ArcNode *list, ArcNode *node)
{
    ArcNode *p = list;
    while (p->next_edge)
    {
        p = p->next_edge;
    }

    p->next_edge = node;
}

/*
 * 创建邻接表对应的图(自己输入)
 */
LGraph* create_lgraph()
{
    char c1, c2;
    int v, e;
    int i, p1, p2;
    ArcNode *node1, *node2;
    LGraph* pG;

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
 
    if ((pG=(LGraph*)malloc(sizeof(LGraph))) == NULL )
        return NULL;
    memset(pG, 0, sizeof(LGraph));

    // 初始化"顶点数"和"边数"
    pG->vexnum = v;
    pG->edgenum = e;
    // 初始化"邻接表"的顶点
    for(i=0; i<pG->vexnum; i++)
    {
        printf("vertex(%d): ", i);
        pG->vertex[i].data = read_char();
        pG->vertex[i].first_edge = NULL;
    }

    // 初始化"邻接表"的边
    for(i=0; i<pG->edgenum; i++)
    {
        // 读取边的起始顶点和结束顶点
        printf("edge(%d): ", i);
        c1 = read_char();
        c2 = read_char();

        p1 = get_position(*pG, c1);
        p2 = get_position(*pG, c2);
        // 初始化node1
        node1 = (ArcNode*)malloc(sizeof(ArcNode));
        node1->adjvex= p2;
        //原作者代码未将其指向NULL
        node1->next_edge = NULL;
        // 将node1链接到"p1所在链表的末尾"
        if(pG->vertex[p1].first_edge == NULL)
          pG->vertex[p1].first_edge = node1;
        else
            link_last(pG->vertex[p1].first_edge, node1);
    }

    return pG;
}

/*
 * 创建邻接表对应的图(用已提供的数据)
 */
LGraph* create_example_lgraph()
{
    char c1, c2;
    char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    char edges[][2] = {
        {'A', 'B'}, 
        {'B', 'C'}, 
        {'B', 'E'}, 
        {'B', 'F'}, 
        {'C', 'E'}, 
        {'D', 'C'}, 
        {'E', 'B'}, 
        {'E', 'D'}, 
        {'F', 'G'}}; 
    int vlen = LENGTH(vexs);
    int elen = LENGTH(edges);
    int i, p1, p2;
    ArcNode *node1, *node2;
    LGraph* pG;

    if ((pG=(LGraph*)malloc(sizeof(LGraph))) == NULL )
        return NULL;
    memset(pG, 0, sizeof(LGraph));

    // 初始化"顶点数"和"边数"
    pG->vexnum = vlen;
    pG->edgenum = elen;
    // 初始化"邻接表"的顶点
    for(i=0; i<pG->vexnum; i++)
    {
        pG->vertex[i].data = vexs[i];
        pG->vertex[i].first_edge = NULL;
    }

    // 初始化"邻接表"的边
    for(i=0; i<pG->edgenum; i++)
    {
        // 读取边的起始顶点和结束顶点
        c1 = edges[i][0];
        c2 = edges[i][1];

        p1 = get_position(*pG, c1);
        p2 = get_position(*pG, c2);
        // 初始化node1
        node1 = (ArcNode*)malloc(sizeof(ArcNode));
        node1->adjvex = p2;
        //原作者代码未将其指向NULL
        node1->next_edge = NULL;
        // 将node1链接到"p1所在链表的末尾"
        if(pG->vertex[p1].first_edge == NULL)
            pG->vertex[p1].first_edge = node1;
        else
            link_last(pG->vertex[p1].first_edge, node1);
    }

    return pG;
}

/*
 * 打印邻接表图
 */
void print_lgraph(LGraph G)
{
    int i,j;
    ArcNode *node;

    printf("List Graph:\n");
    for (i = 0; i < G.vexnum; i++)
    {
        printf("%d(%c): ", i, G.vertex[i].data);
        node = G.vertex[i].first_edge;
        while (node != NULL)
        {
            printf("%d(%c) ", node->adjvex, G.vertex[node->adjvex].data);
            node = node->next_edge;
        }
        printf("\n");
    }
}

void main()
{
    LGraph* pG;

    // 自定义"图"(自己输入数据)
    // pG = create_lgraph();
    // 采用已有的"图"
    pG = create_example_lgraph();

    // 打印图
    print_lgraph(*pG);
}