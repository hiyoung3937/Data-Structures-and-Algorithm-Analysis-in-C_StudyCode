#include "./function.h"

int main(void)
{
    BTreePtr T;
    T = NULL;
    int a[] = {33, 16, 50, 13, 18, 34, 58, 15, 17, 25, 51, 66, 19, 27, 55};
    int i;
    for (i = 0; i < 15; i++) {
        BTree_Insert(&T, a[i]);
    }

    printf("Max is %d\n", BTree_FindMax(T));
    printf("Min is %d\n", BTree_FindMin(T));
    BTree_Delete(T, 18);
    BTree_Delete(T, 13);
    printf("%d:NOT FOUND\n",BTree_Find(T,13));
    BTree_Destroy(T);

    return 0;
}