#include "function.h"

int main(void)
{
	Tree *root = NULL;
    int findnum = 3;

	printf("\r\n创建二叉树:");
	binarytree_create(&root);

	printf("\r\n先序遍历二叉树:");
	binarytree_preorder(root);	//递归
	printf("\r\n非递归先序遍历二叉树:");
	preorder_NonRecursion(root);	//非递归
	
	printf("\r\n中序遍历二叉树:");
	binarytree_inorder(root);
	printf("\r\n非递归中序遍历二叉树:");
	inorder_NonRecursion(root);

	printf("\r\n后序遍历二叉树:");
	binarytree_postorder(root);
	printf("\r\n非递归后序遍历二叉树:");
	postorder__NonRecursion(root);

    //未实现
	// printf("\r\n层次遍历二叉树:");
	// binarytree_levelorder(root);

    //查找二叉树才可行
    // printf("\r\n二叉树查找中数值: %d",binarytree_find(root,findnum));

	printf("\r\n打印二叉树叶子节点:");
	binarytree_printfleaf(root);

	printf("\r\n打印二叉树叶子节点个数:%d",binarytree_getleafnum(root));
	printf("\r\n打印二叉树高度:%d",binarytree_gethigh(root));

	binarytree_destory(root);

	return 0;
}
