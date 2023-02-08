#include<stdio.h>
#include<stdlib.h>

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
    printf("Enter TNode data(Enter 100 to quit and finish create):");
    scanf("%d",&data);

    if(data == 100)
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

/*中序遍历:左子树--》跟节点---》右子树*/
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

/*后序遍历:左子树---》右子树-》根节点*/
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