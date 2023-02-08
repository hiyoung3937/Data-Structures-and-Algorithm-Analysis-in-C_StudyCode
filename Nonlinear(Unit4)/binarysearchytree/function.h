#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;
typedef int ElemType;

typedef struct Node
{
    ElemType data;
    struct Node *lchild, *rchild;
}BTree, *BTreePtr;

/**************** 插入 **********************/
Status BTree_Insert(BTreePtr *T,ElemType data)
{
    BTreePtr P;
    if(*T == NULL)
    {
        *T = (BTreePtr)malloc(sizeof(BTree));
        (*T)->data = data;
        //初始化左右子节点
        (*T)->lchild = NULL;
        (*T)->rchild = NULL;

        return TRUE;
    } else
    {
        P = *T;
        while ( P != NULL)
        {
            if(P->data < data)
            {
                if(P->rchild == NULL)
                {
                    P->rchild = (BTreePtr)malloc(sizeof(BTree));
                    P->rchild->data = data;
                    //初始化左右子节点
                    P->rchild->lchild = NULL;
                    P->rchild->rchild = NULL;
                    return TRUE;
                }
                
                P = P->rchild;
            } else
            {
                if(P->lchild == NULL)
                {
                    P->lchild = (BTreePtr)malloc(sizeof(BTree));
                    P->lchild->data = data;
                    //初始化左右子节点
                    P->lchild->lchild = NULL;
                    P->lchild->rchild = NULL;
                    return TRUE;
                }

                P = P->lchild;
            }
        }
    }

    return FALSE;
}

/**************** 删除 **********************/
// 详细注释参考：https://www.cnblogs.com/lanhaicode/p/11298338.html 
// & https://www.cnblogs.com/MrListening/p/5782752.html

Status BTree_Delete(BTreePtr T, ElemType data)
{
    //PNode :待删除结点     ParentPNode：待删除结点的父结点  
    //minPNode:待删除结点的右子树中的最左结点   minParentPNode:待删除结点的右子树中的最左结点的父结点
    BTreePtr PNode, ParentPNode, minPNode, minParentPNode, ChildNode;

    ChildNode = NULL;
    PNode = T;
    ParentPNode = NULL;

    //找到待删除的结点和他的的父结点
    while((PNode != NULL) && (PNode->data != data))
    {
        ParentPNode = PNode;

        if(data > PNode->data)
        {
            PNode = PNode->rchild;
        }else
        {
            PNode = PNode->lchild;
        }
    }

    if(PNode == NULL)   
        return FALSE;

    //待删除结点没有子结点时
    if(ParentPNode->lchild == PNode)
    {
        ParentPNode->lchild = ChildNode;
    }else
    {
        ParentPNode->rchild = ChildNode;
    }

    return TRUE;

    //待删除结点有一个子结点时
    if((PNode->lchild != NULL) || (PNode->rchild != NULL))
    {
        //判断待删除结点是具有左结点还是右结点
        if(PNode->lchild)
        {
            ChildNode = PNode->lchild;
        } else
        {
            ChildNode = PNode->rchild;
        }

        //判断待删除结点是其父结点的左结点还是右结点
        //这里的ParentPNode指向待删除的结点的父结点
        if(ParentPNode->data > PNode->data) //待删除结点是左结点
        {
            ParentPNode->lchild = ChildNode;
        } else //待删除结点是右结点
        {
            ParentPNode->rchild = ChildNode;
        }

        free(PNode);
        return TRUE;
    }

    //待删除结点有两个子结点时
    //找到待删除结点的右子树中的最左结点（也就是右子树中序遍历的第一个结点,不一定是叶子结点）
    if((PNode->lchild != NULL) && (PNode->rchild != NULL))
    {
        minParentPNode = PNode; //赋值为待删除结点
        minPNode = PNode->rchild; //赋值为待删除结点的右结点

        //minP迭代至找到待删除结点的右结点的最左结点,minPP为其父节点
        while (minPNode->lchild != NULL)
        {
            minParentPNode = minPNode;
            minPNode = minPNode->lchild;
        }

        PNode->data = minPNode->data; //把它（找到的最左结点，但不一定是叶子结点）的值赋值给要删除的节点
        minParentPNode->lchild = minPNode->rchild; //把最左结点的右结点赋值给其父结点的左结点
        free(minPNode);

        return TRUE;
    }

}

/**************** 查找 **********************/
Status BTree_Find(BTreePtr T, ElemType data)
{
    if(T == NULL)
        return FALSE;

    while ((T != NULL) && (T->data != data))
    {
        if(data > T->data)
        {
            T = T->rchild;
        } else
        {
            T = T->lchild;
        }
    }

    if(T)
    {
        return TRUE;
    } else
    {
        return FALSE;
    }
    
}

/**************** 最大值 **********************/
ElemType BTree_FindMax(BTreePtr T)
{
    ElemType max;

    while (T != NULL)
    {
        max = T->data;
        T = T->rchild;
    }

    return max;
}

/**************** 最小值 **********************/
ElemType BTree_FindMin(BTreePtr T)
{
    ElemType min;

    while (T != NULL)
    {
        min = T->data;
        T = T->lchild;
    }

    return min;
}

void BTree_Destroy(BTreePtr T)
{
    if(T)
    {
        if(T->lchild)
        {
            BTree_Destroy(T->lchild);
        }

        if(T->rchild)
        {
            BTree_Destroy(T->rchild);
        }

        free(T);
        T = NULL;
    }
}