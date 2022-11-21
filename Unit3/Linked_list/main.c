#include "function.h"
#include<stdio.h>


int main(void)
{
    stDlistHead dlist = {0};
    stDlistNode *pNode = NULL;


    
    dlist_init(&dlist);

    printf("\r\n inset 1,2,3");
	dlist_insert_head(&dlist,NULL,1);
	dlist_insert_head(&dlist,NULL,2);
	dlist_insert_head(&dlist,NULL,3);
    dlist_dump(&dlist);

    dlist_insert_head(&dlist,pNode,6);
    dlist_dump(&dlist);
    // dlsit_destory(&dlist);
    printf("插入数据");
    dlist_insert(&dlist,7,4);
    dlist_dump(&dlist);

    printf("LRU算法");
    Lru_dlist(&dlist,5);
	dlist_dump(&dlist);
    Lru_dlist(&dlist,6);
	dlist_dump(&dlist);
    Lru_dlist(&dlist,7);
	dlist_dump(&dlist);
    Lru_dlist(&dlist,5);
	dlist_dump(&dlist);
    return 0; 
}