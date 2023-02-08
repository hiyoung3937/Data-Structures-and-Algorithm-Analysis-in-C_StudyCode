/*代码参考：https://www.cnblogs.com/skywang12345/p/3576969.html*/

#include<stdio.h>
#include<stdlib.h>

//此处定义为空的二叉树的高度是0
#define HEIGHT(PNode)   ( (PNode == NULL) ? 0 :(((Node*)(PNode))->height) )
//比较大小
#define MAX(a, b)    ( (a) > (b) ? (a) : (b) )

typedef int ElemType;

typedef struct AVLTreeNode
{
    ElemType data;     //值
    int height;     //树高度
    struct AVLTreeNode *LChild;     //左子结点
    struct AVLTreeNode *RChild;     //右子结点
}Node, *AVLTree;


/*
 * 前序遍历"AVL树"
 */
void preorder_avltree(AVLTree tree)
{
    if(tree != NULL)
    {
        printf("%d ", tree->data);
        preorder_avltree(tree->LChild);
        preorder_avltree(tree->RChild);
    }
}


/*
 * 中序遍历"AVL树"
 */
void inorder_avltree(AVLTree tree)
{
    if(tree != NULL)
    {
        inorder_avltree(tree->LChild);
        printf("%d ", tree->data);
        inorder_avltree(tree->RChild);
    }
}

/*
 * 后序遍历"AVL树"
 */
void postorder_avltree(AVLTree tree)
{
    if(tree != NULL)
    {
        postorder_avltree(tree->LChild);
        postorder_avltree(tree->RChild);
        printf("%d ", tree->data);
    }
}


//创建AVL树结点
Node *avltree_create_node(ElemType data,Node *LChild,Node *RChild)
{
    Node * PNode;

    if ((PNode = (Node *)malloc(sizeof(Node))) == NULL)
    {
        return NULL;
    }

    PNode->data = data;
    PNode->height = 0;
    PNode->LChild = LChild;
    PNode->RChild = RChild;
    
    return PNode;
}

//获取AVL树的高度
int avltree_height(AVLTree Tree)
{
    return HEIGHT(Tree);
}

/*
 * 查找最小结点：返回tree为根结点的AVL树的最小结点。
 */
Node *avltree_min(AVLTree tree)
{
    if(tree == NULL)
        return NULL;
    
    while (tree->LChild != NULL)
        tree = tree->LChild;
    return tree;
}

/*
 * 查找最大结点：返回tree为根结点的AVL树的最大结点。
 */
Node *avltree_max(AVLTree tree)
{
    if(tree == NULL)
        return NULL;
    
    while (tree->RChild != NULL)
        tree = tree->RChild;
    return tree;
}


 //(递归实现)查找"AVL树x"中值为data的节点
Node* avltree_search(AVLTree x, ElemType data)
{
    if(x == NULL || x->data == data)
        return x;
    
    if(data < x->data)
        return avltree_search(x->LChild, data);
    else
        return avltree_search(x->RChild, data);
}



/* 旋转：LL(左左)，LR(左右)，RR(右右)和RL(右左)
*导致树不平衡的插入可能有四种，在a结点的左儿子的左子树插入称为LL(左左)
*其中LL和RR、LR和RL为镜像问题，实际只有两种情况
*LL和RR可以通过一次单旋转完成调整，LR和RL则需要通过双旋转完成调整
*/

// LL情况,单旋转
static Node *left_left_rotation(AVLTree k2)
{
    AVLTree k1; //旋转后的根节点

    k1 = k2->LChild;
    k2->LChild = k1->RChild;
    k1->RChild = k2;

    k2->height = MAX(HEIGHT(k2->LChild), HEIGHT(k2->RChild)) + 1;
    k1->height = MAX(HEIGHT(k1->LChild), k2->height) + 1;

    return k1;
}

//RR情况,单旋转
static Node *right_right_rotation(AVLTree k1)
{
    AVLTree k2; //旋转后的根节点

    k2 = k1->RChild;
    k1->RChild = k2->LChild;
    k2->LChild = k1;

    k1->height = MAX(HEIGHT(k1->LChild), HEIGHT(k1->RChild)) + 1;
    k2->height = MAX(HEIGHT(k2->RChild), k1->height) + 1;

    return k2;
}

//LR情况，双旋转
//先RR单旋转再LL单旋转
static Node *left_right_rotation(AVLTree k3)
{
    k3->LChild = right_right_rotation(k3->LChild);

    return left_left_rotation(k3);
}

//RL情况，双旋转
//先LL单旋转，再RR单旋转
static Node *right_left_roration(AVLTree k3)
{
    k3->RChild = left_left_rotation(k3->RChild);

    return right_right_rotation(k3);
}

/* 
 * 将结点插入到AVL树中，并返回根节点
 *
 * 参数说明：
 *     tree AVL树的根结点
 *     data 插入的结点的键值
 * 返回值：
 *     根节点
 */

Node * avltree_insert(AVLTree tree, ElemType data)
{
    if(tree == NULL)
    {
        //新建节点
        tree=avltree_create_node(data,NULL,NULL);
        if(tree == NULL)
            return NULL;
    }
    else if(data < tree->data)  // 应该将data插入到"tree的左子树"的情况
    {
        tree->LChild = avltree_insert(tree->LChild,data);
        // 插入节点后，若AVL树失去平衡，则进行相应的调节
        if(HEIGHT(tree->LChild) - HEIGHT(tree->RChild) == 2)
        {
            if(data < tree->LChild->data)
                left_left_rotation(tree);   //LL
            else
                left_right_rotation(tree);  //LR
        }
    }
    else if(data > tree->data)  // 应该将data插入到"tree的右子树"的情况
    {
        tree->RChild = avltree_insert(tree->RChild,data);
        // 插入节点后，若AVL树失去平衡，则进行相应的调节
        if(HEIGHT(tree->RChild) - HEIGHT(tree->LChild) == 2)
        {
            if(data < tree->RChild->data)
                right_left_roration(tree); //RL
            else
                right_right_rotation(tree); //RR
        }
    }
    else    //data == tree->data
    {
        return NULL; //添加失败：不允许添加相同的节点
    }

    tree->height = MAX( HEIGHT(tree->LChild), HEIGHT(tree->RChild)) + 1;

    return tree;
}

/* 
 * 删除结点(z)，返回根节点
 *
 * 参数说明：
 *     tree AVL树的根结点
 *     z 待删除的结点
 * 返回值：
 *     根节点
 */
Node * delete_node(AVLTree tree, Node *z)
{
    if(tree == NULL || z == NULL)
        return NULL;

    if(z->data < tree->data)
    {
        tree->LChild = delete_node(tree->LChild, z);
        // 删除节点后，若AVL树失去平衡，则进行相应的调节
        if(HEIGHT(tree->RChild) - HEIGHT(tree->LChild) == 2)
        {
            Node *r = tree->RChild;
            if(HEIGHT(r->LChild) > HEIGHT(r->RChild))
                tree = right_left_roration(tree);
            else
                tree = right_right_rotation(tree);
        }
    }
    else if(z->data > tree->data)
        tree->RChild = delete_node(tree->RChild, z);
        // 删除节点后，若AVL树失去平衡，则进行相应的调节
        if(HEIGHT(tree->LChild) - HEIGHT(tree->RChild) == 2)
        {
            Node *l = tree->LChild;
            if(HEIGHT(l->LChild) > HEIGHT(l->RChild))
                tree = left_left_rotation(tree);
            else
                tree = left_right_rotation(tree);
        }
    else     // tree是对应要删除的节点
    {
        // tree的左右孩子都非空
        if((tree->LChild) && (tree->RChild))
        {
            if(HEIGHT(tree->LChild) > HEIGHT(tree->RChild))
            {   
                // 如果tree的左子树比右子树高；
                // 则(01)找出tree的左子树中的最大节点
                //   (02)将该最大节点的值赋值给tree。
                //   (03)删除该最大节点。
                // 这类似于用"tree的左子树中最大节点"做"tree"的替身；
                // 采用这种方式的好处是：删除"tree的左子树中最大节点"之后，AVL树仍然是平衡的。
                Node * max = avltree_max(tree->LChild);
                tree->data = max->data;
                tree->LChild = delete_node(tree->LChild, max);
            }
            else
            {
                Node * min = avltree_min(tree->RChild);
                tree->data = min->data;
                tree->RChild = delete_node(tree->RChild, min);
            }
        }
        else
        {
            Node * tmp = tree;
            tree = tree->LChild ? tree->LChild : tree->RChild;
            free(tmp);
        }
    }

    return tree;
}

/*
 * 删除结点(data是节点值)，返回根节点
 *
 * 参数说明：
 *     tree AVL树的根结点
 *     data 待删除的结点的值
 * 返回值：
 *     根节点
 */
Node * avltree_delete(AVLTree tree, ElemType data)
{
    Node *z;

    if((z = avltree_search(tree,data)) != NULL)
        tree = delete_node(tree, z);
    return tree;
}

//销毁AVL树
void avltree_destroy(AVLTree tree)
{
    if(tree == NULL)
        return ;
    
    if(tree->LChild != NULL)
        avltree_destroy(tree->LChild);
    if(tree->RChild != NULL)
        avltree_destroy(tree->RChild);

    free(tree);
}

/*
 * 打印"AVL树"
 *
 * tree       -- AVL树的节点
 * data        -- 节点的值
 * direction  --  0，表示该节点是根节点;
 *               -1，表示该节点是它的父结点的左孩子;
 *                1，表示该节点是它的父结点的右孩子。
 */
void print_avltree(AVLTree tree, ElemType data, int direction)
{
    if(tree != NULL)
    {
        if(direction==0)    // tree是根节点
            printf("%2d is root\n", tree->data, data);
        else                // tree是分支节点
            printf("%2d is %2d's %6s child\n", tree->data, data, direction==1?"right" : "left");

        print_avltree(tree->LChild, tree->data, -1);
        print_avltree(tree->RChild,tree->data,  1);
    }
}

