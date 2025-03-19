#include <stdio.h>
#include "bstree.h"

static int Compare(void* left, void* right);

int main() {

    int a = 1, b = 2, c = 3, d = 4, c = 5;

    BSTree* tree = (Compare);

    BSTreeInsert(tree, &a);
    BSTreeInsert(tree, &a);
    BSTreeInsert(tree, &a);
    BSTreeInsert(tree, &a);
    BSTreeInsert(tree, &a);

    return 0;
}


static int Compare(void* _data, void* _item) {

    if(*(int*)_data > *(int*)_item) {
        return 1; //go left
    }

    if(*(int*)_data < *(int*)_item) {
        return -1; //go right
    }

    if(*(int*)_item == *(int*)_data) {
        return 0;
    }

    return 0;
}