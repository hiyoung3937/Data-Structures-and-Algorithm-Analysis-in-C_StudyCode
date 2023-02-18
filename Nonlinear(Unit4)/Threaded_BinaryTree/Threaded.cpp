//线索二叉树
/*当ltag和rtag为0时，leftChild和rightChild分别是指向左孩子和右孩子的指针；
*当ltag和rtag为1时，leftChild指向结点的直接前驱，rightChild指向结点的直接后继
*/
#include<stdio.h>

typedef struct TBTNode
{
    int data;
    int ltag, rtag; //线索标记
    struct TBTNode *lchild;
    struct TBTNode *rchild;
}TBTNode;

//通过中序遍历对二叉树线索化
void InThread(TBTNode *p, TBTNode *&pre)
{
    if(p != NULL)
    {
        InThread(p->lchild, pre);   //递归，左子树线索化
        if(p->lchild == NULL)   //建立当前结点的前驱线索
        {
            p->lchild = pre;
            p->ltag =1;
        }

        if(pre != NULL && pre->rchild == NULL)  //建立当前结点的后继线索
        {
            pre->rchild = p;
            pre->rtag = 1;
        }
        //pre指向当前的p，作为p将要指向的下一个结点的前驱结点的指示指针
        pre = p; 

        InThread(p->rchild,pre);    //递归，右子树线索化
    }
}

//通过中序遍历对二叉树线索化主程序
void createInThread(TBTNode *root)
{
    TBTNode *pre = NULL;
    if(root != NULL)
    {
        InThread(root,pre);
        pre->rchild = NULL;     //非空二叉树，线索化
        pre->rtag = 1;          //后处理中序的最后一个结点
    }
}

//求以root为根的线索二叉树中，中序序列下的第一个结点算法
TBTNode *FirstNode(TBTNode *root)
{
    while (root->ltag == 0)
    {
        root = root->lchild;    //最左下结点，不一定为叶子结点
    }

    return root;
}
//求以root为根的线索二叉树中，中序序列下的最后一个结点算法
TBTNode *LastNode(TBTNode *root)
{
    while (root->rtag == 0)
    {
        root = root->rchild;    //最右下结点，不一定为叶子结点
    }

    return root;
}

//求在中序线索二叉树中，结点p在中序下的后继结点
TBTNode *NextNode(TBTNode *p)
{
    if(p->rtag == 0)
        return FirstNode(p->rchild);
    else
        return p->rchild;   //rtag == 1 直接返回后继结点
}

//求在中序线索二叉树中，结点p在中序下的前驱结点
TBTNode *PriorNode(TBTNode *p)
{
    if(p->ltag == 0)
        return LastNode(p->lchild);
    else
        return p->lchild;   //ltag == 1 直接返回后继结点
}

void Inorder(TBTNode *root)
{
    TBTNode *p = FirstNode(root);
    while (p != NULL)
    {
        printf(" %d ",p->data);
        p = NextNode(p);
    }
}

//前序线索二叉树
void PreThread(TBTNode *p, TBTNode *&pre)
{
    if(p != NULL)
    {
        if(p->lchild == NULL)   //建立当前结点的前驱线索
        {
            p->lchild = pre;
            p->ltag =1;
        }

        if(pre != NULL && pre->rchild == NULL)  //建立当前结点的后继线索
        {
            pre->rchild = p;
            pre->rtag = 1;
        }
        //pre指向当前的p，作为p将要指向的下一个结点的前驱结点的指示指针
        pre = p; 
        
        //入口限制，左右指针都不是线索才能继续递归
        if(p->ltag == 0)    
        PreThread(p->lchild, pre);   //递归，左子树线索化
        if(p->rtag == 0)
        PreThread(p->rchild,pre);   //递归，右子树线索化
    }
}
//在前序线索二叉树上指向前序遍历
void preorder(TBTNode * root)
{
    if(root != NULL)
    {
        TBTNode *p = root;
        while (p != NULL)
        {
            while (p->ltag == 0)    //左指针不是线索，则边访问边左移
            {
                printf(" %d ",p->data);
                p = p->lchild;
            }
            printf(" %d ",p->data); // 此时p左指针必为线索，但没有访问，则访问
            p = p->rchild; //此时p左孩子不存在，若右指针非空，则不论是否为线索都指向其后继
        }
        
    }
}


//通过后序遍历对二叉树线索化
void PostThread(TBTNode *p, TBTNode *&pre)
{
    if(p != NULL)
    {
        PostThread(p->lchild, pre);   //递归，左子树线索化
        PostThread(p->rchild,pre);    //递归，右子树线索化
        if(p->lchild == NULL)   //建立当前结点的前驱线索
        {
            p->lchild = pre;
            p->ltag =1;
        }

        if(pre != NULL && pre->rchild == NULL)  //建立当前结点的后继线索
        {
            pre->rchild = p;
            pre->rtag = 1;
        }
        //pre指向当前的p，作为p将要指向的下一个结点的前驱结点的指示指针
        pre = p; 

    }
}