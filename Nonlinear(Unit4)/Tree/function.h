#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100

typedef struct TreeNode
{
    int data;
    struct TreeNode * Lchild;
    struct TreeNode * Rchild;
}TNode,Tree;

//create tree
void binarytree_create(Tree **root)
{
    int data = 0;
    printf("Enter TNode data(Enter -1 to quit and finish create):");
    scanf("%d",&data);

    if(data == -1)
    {
        *root = NULL;
    }
    else
    {
        *root=(TNode *)malloc(sizeof(TNode));
        if(*root == NULL)
        {
            return ;
        }

        (*root)->data = data;
        printf("\r\n create %d 的左孩子:",data);
        binarytree_create(&((*root)->Lchild));
        printf("\r\n create %d 的右孩子:",data);
        binarytree_create(&((*root)->Rchild));
    }

    return ;
}

//destory Tree
void binarytree_destory(Tree *root)
{
    if(root == NULL)
    {
        return ;
    }

    binarytree_destory(root->Lchild);
    binarytree_destory(root->Rchild);
    free(root);
}

// 先序遍历：根结点--》左子树---》右子树
void binarytree_preorder(Tree *root)
{
    if(root == NULL)
    {
        return ;
    }

    printf(" %d ",root->data);
    binarytree_preorder(root->Lchild);
    binarytree_preorder(root->Rchild);

    return ;
}

/*中序遍历:左子树--》根节点---》右子树*/
void binarytree_inorder(Tree *root)
{
    if(root == NULL)
    {
        return ;
    }

    binarytree_inorder(root->Lchild);
    printf(" %d ",root->data);
    binarytree_inorder(root->Rchild);

    return ;
}

/*后序遍历:左子树---》右子树---》根节点*/
void binarytree_postorder(Tree *root)
{
	if (root == NULL)
	{
		return;
	}
	binarytree_postorder(root->Lchild);
	binarytree_postorder(root->Rchild);
	printf(" %d ",root->data);
    return;
}

//非递归实现遍历
// 非递归先序遍历
void preorder_NonRecursion(TNode *root)
{
    if(root != NULL)
    {
        TNode *Stack[MAXSIZE];  //自定义栈
        int top = -1;           //初始化
        TNode *p;
        Stack[++top] = root;    //根结点入栈

        while (top != -1)
        {
            p = Stack[top--];
            printf(" %d ",p->data);
            if(p->Rchild != NULL)
                Stack[++top] = p->Rchild; //入栈顺序要是先右后左
            if(p->Lchild != NULL)
                Stack[++top] = p->Lchild;
        }
        
    }
}

// 非递归中序遍历
void inorder_NonRecursion(TNode *root)
{
     if(root != NULL)
    {
        TNode *Stack[MAXSIZE];  //自定义栈
        int top = -1;           //初始化
        TNode *p;
        p = root;

        //遍历完左子树后会出现栈空状态，此时p非空，添加判断条件确保右子树完成遍历
        while (top != -1 || p != NULL)  
        {
            while (p != NULL)   //左子树存在，则左子树入栈
            {
                Stack[++top] = p;
                p = p->Lchild;              //左
            }

            if(top != -1)   //栈非空情况先出栈并输出出栈结点
            {
                p = Stack[top--];
                printf(" %d ",p->data);     //中
                p = p->Rchild;              //右
            }
        }
    }
}

// 非递归后序遍历(双栈法)
void postorder__NonRecursion(TNode *root)
{
    if(root != NULL)
    {
        int top1 = -1;
        int top2 = -1;
        TNode *Stack1[MAXSIZE]; //辅助完成逆后序遍历(将先序遍历的左、右子树遍历顺序交换)
        TNode *Stack2[MAXSIZE]; //将stack1中传来的结果在做一次逆序(逆 逆后序遍历)
        TNode *p = NULL;
        Stack1[++top1] = root;

        while (top1 != -1)
        {
            p = Stack1[top1--];
            Stack2[++top2] = p;

            if (p->Lchild != NULL)
                Stack1[++top1] = p->Lchild;
            if(p->Rchild != NULL)
                Stack1[++top1] = p->Rchild;
        }

        while (top2 != -1)
        {
            p = Stack2[top2--];
            printf(" %d ",p->data);
        }

    }

}

/*打印叶子节点*/
void binarytree_printfleaf(Tree *root)
{
    if(root == NULL)
    {
        return ;
    }

    if((root->Lchild == NULL) && (root->Rchild == NULL))
    {
        printf(" %d ",root->data);
    }
    else
    {
        binarytree_printfleaf(root->Lchild);
        binarytree_printfleaf(root->Rchild);
    }

    return ;
}

/*打印叶子的个数*/
int binarytree_getleafnum(Tree *root)
{
    if(root == NULL)
    {
        return 0;
    }

    if((root->Lchild == NULL) && (root->Rchild) == NULL)
    {
        return 1;
    }

    return (binarytree_getleafnum(root->Lchild)) + (binarytree_getleafnum(root->Rchild));
}

/*打印数的高度*/
int binarytree_gethigh(Tree *root)
{
    if(root == NULL)
    {
        return 0;
    }

    int lhigh = 0;
    int rhigh = 0;

    lhigh = binarytree_gethigh(root->Lchild);
    rhigh = binarytree_gethigh(root->Rchild);

    return ((lhigh>rhigh)?(lhigh+1):(rhigh+1));
}

//查找二叉树查找中特定数值
int binarytree_find(Tree *root, int findnum)
{
    if(root == NULL)
    {
        return 0;
    }
    
    if(findnum < root->data)
    {
        return binarytree_find(root->Lchild,findnum);
    } else if (findnum > root->data)
    {
        return binarytree_find(root->Rchild,findnum);
    } else
    {
        return root->data;
    }
    
}