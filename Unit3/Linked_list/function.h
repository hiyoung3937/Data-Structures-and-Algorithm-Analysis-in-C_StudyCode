#include<stdio.h>
#include<malloc.h> //malloc()，free()
#include<stdlib.h> 
#include<string.h> //memset()

typedef struct DlistNode //定义双链表的结点
{
    struct DlistNode *prev; //前继结点
    struct DlistNode *next; //后继结点
    int data; //结点数据
}stDlistNode;

typedef struct Dlisthead //定义链表
{
    stDlistNode *head; //头指针
    stDlistNode *tail; //尾指针
    int size; //链表长度
}stDlistHead;

void dlist_init(stDlistHead *dlist) //初始化双链表
{
    dlist->size = 0;
    dlist->head = NULL;
    dlist->tail = NULL;

    return;
}

void dlsit_destory(stDlistHead *dlist) //删除链表
{
    stDlistNode *pNode = NULL;

    while(dlist->size>0)
    {
        pNode = dlist->head; //将头指针（地址）传给pNode
        dlist->head = dlist->head->next; //将链表head指向下一个结点地址
        free(pNode); //释放之前的head结点，当前head结点为之前head->next
        dlist->size--; //链表长度减一
    }

    memset(dlist,0,sizeof(stDlistHead)); //将双链表中数据全置为0

    return;

}

int dlist_insert_head(stDlistHead *dlist,stDlistNode *pNode,int data) //插入头结点(操作的链表，操作的节点，数据)
{
    if(pNode == NULL) //当只传递一个数据时
    {
        pNode = (stDlistNode *)malloc(sizeof(stDlistNode)); //新建结点，为结点动态分配空间
        if(pNode == NULL) //分配空间出错
        {
            return -1;
        }
    }

    pNode->data = data;
    pNode->next = NULL;
    pNode->prev = NULL;

    if(dlist->size == 0) //如果链表长度为0，即链表当前无节点
    {
        dlist->head = pNode;
        dlist->tail = pNode;
    }
    else                //如果链表已有节点，则令新插入节点为头节点
    {
        pNode->next = dlist->head;
        dlist->head->prev = pNode;
        dlist->head = pNode;
    }

    dlist->size++;  //每成功调用一次链表长度+1
    return 0;
}

// 在第add位置的前面插入data节点 ！
int dlist_insert(stDlistHead *dlist,int data,int add) //在任意两结点之间插入(操作的链表，数据，插入位置)
{
    stDlistNode *temp = (stDlistNode *)malloc(sizeof(stDlistNode)); //新建存储data的临时结点
    if(dlist->size == 0) //空链表
    {
        return -1;
    }
    else
    {
        temp->data=data;
        temp->next=NULL;
        temp->prev=NULL;
    }

    if(add == 1)//插入到表头
    {
        temp->next = dlist->head;
        dlist->head->prev = temp;
        dlist->head = temp;
    }
    else
    {
        stDlistNode *body = dlist->head;
        for (int i = 1; i < add-1; i++)
        {   
            body = body->next;
        }

        /*判断条件为真，说明插入位置为链表尾*/
        if (body->next==NULL)
        {
            body->next=temp;
            temp->prev=body;
        }
        else
        {
            body->next->prev=temp;
            temp->next=body->next;
            body->next=temp;
            temp->prev=body;
        }
        
    }

    return 0;

}


void dlist_dump(stDlistHead *dlist)		//显示链表中的数据
{
	int no = 0;
	stDlistNode *pNode = dlist->head;
	while(pNode != NULL)
	{
		printf("\r\n [%d] = %d",no++,pNode->data);
		pNode = pNode->next;		//将pNode的下一个节点赋值给pNode，推进循环
	}

    printf("\n");
	return;
}

stDlistNode *dlist_remove_tail(stDlistHead *dlist)  //删除尾部节点,并返回删除节点
{
    stDlistNode *pNode = NULL;
    
    if(dlist->size == 0)
    {
        return NULL;
    }
    
    pNode = dlist->tail;
    if(dlist->size > 1)  //删除的链表不止一个结点
    {
        dlist->tail = dlist->tail->prev;
        dlist->tail->next = NULL;
    }
    else                //dlist->size == 1
    {
        dlist->head = NULL;
        dlist->tail = NULL;
    }

    dlist->size--;
    return pNode;
}


void dlist_remove_node(stDlistHead *dlist,stDlistNode *pNode) //删除指定结点
{
    if((dlist->size == 0) || (pNode == NULL))
    {
        return;
    }

    if(dlist->head == pNode)
    {
        dlist->head = dlist->head->next;
    }
    else if(dlist->tail == pNode)
    {
        dlist->tail = dlist->tail->prev;
        dlist->tail->next = NULL;
    }
    else 
    {
        pNode->prev->next = pNode->next;
        pNode->next->prev = pNode->prev;
    }

    dlist->size--;
    pNode->next = NULL;
    pNode->prev = NULL;

    if(dlist->size == 0)
    {
        memset(dlist,0,sizeof(stDlistHead)); 
        //将dlist占用内存块的所有值置为0，也就是清空head,tail指针内容
    }

    return;
}

stDlistNode * dlist_search(stDlistHead * dlist,int data) //根据值搜索节点，并返回
{
    stDlistNode * pNode = dlist->head;
    while (pNode != NULL)
    {
        if(pNode->data == data)
        {
            return pNode;
        }

        pNode = pNode->next; //继续查找下一个
    }

    return NULL;
    
}


//应用以上函数实现LRU(最近最少使用)缓存淘汰算法

void Lru_dlist(stDlistHead *dlist,int data)
{
    stDlistNode *pNode = NULL;

    pNode = dlist_search(dlist,data);
    if(pNode != NULL)  //如果在链表中找到这个值，则删除储存这个值的节点，之后吧这个节点放在头部
    {
        dlist_remove_node(dlist,pNode);
    }
    else if(dlist->size >= 4) //没在链表中找到，且链表长度大于4，则从链表中删除尾部节点，将新数据放在头部
	{
		pNode = dlist_remove_tail(dlist);
	}

    dlist_insert_head(dlist,pNode,data);

	return;
}
