#include <stdlib.h>
#include <stdbool.h>
#include "bstree.h"

#define ROOT _tree->m_root.m_left
#define NOT_ROOT node->m_father != node->m_father->m_father

typedef struct Node Node;

struct Node {
    void* m_data;
    Node* m_left;
    Node* m_right;
    Node* m_father;
};

struct BSTree {
    Node m_root;
};

static Node* CreateNode(Node* _fatherNode, void* _item);
static Node* InsertNewNode(Node* _node, LessComparator _compare, void* _item);
static Node* GetBegin(Node* _node);
static void* ZeroSonsRemove(Node* _node);
static void* OneSonRemove(Node* _node, int _direction);
static void* TwoSonsRemove(Node* _node);
static int HowMannyChilds(Node* _node);
static void swap(Node* x, Node* y);
static bool CheckFull(Node* _node);
static bool IsSimilar(Node* _node1, Node* _node2);
void SwapNodes(Node* _node);


BSTree* BSTreeCreate(LessComparator _less) {

    if(_less == NULL) {
        return NULL;
    }

    BSTree* tree = (BSTree*)malloc(sizeof(BSTree));

    if(tree == NULL) {
        return NULL;
    }

    tree->m_root.m_data = _less;
    tree->m_root.m_father = &tree->m_root;
    tree->m_root.m_right = NULL;
    tree->m_root.m_left = NULL;

    return tree;
}

// void* DestroyPostOrder(Node* _node) {

//     if(_node == NULL) {
//         return;
//     }

//     DestroyPostOrder(&((Node*)_node)->m_left);
//     DestroyPostOrder(&((Node*)_node)->m_right);
//     free(_node);

//     return;
// }

void  BSTreeDestroy(BSTree** _tree, void (*_destroyer)(void*)) {

    if(_tree == NULL || *_tree == NULL) {
        return;
    }

    BSTree* tptr = *_tree;

    if(_destroyer != NULL) {
        _destroyer(&tptr->m_root);
    }

    free(tptr);
    *_tree = NULL;
}

BSTreeItr BSTreeInsert(BSTree* _tree, void* _item) {

    if(_tree == NULL || _item == NULL) {
        return _tree;
    }

    if(_tree->m_root.m_left == NULL) {
        ROOT = CreateNode(ROOT, _item);
        return ROOT;
    }

    return InsertNewNode(ROOT, _tree->m_root.m_data, _item);

}

BSTreeItr BSTreeItrBegin(const BSTree* _tree) {

    if(_tree == NULL || ROOT == NULL) {
        return NULL;
    }

    return GetBegin(ROOT);
}

BSTreeItr BSTreeItrEnd(const BSTree* _tree) {

    if(_tree == NULL) {
        return NULL;
    }

    return (BSTreeItr*)&_tree->m_root;
}

int BSTreeItrEquals(BSTreeItr _a, BSTreeItr _b) {

    return _a == _b;
}

BSTreeItr BSTreeItrNext(BSTreeItr _itr) {

    if(_itr == NULL) {
        return NULL;
    }

    Node* node = (Node*)_itr;

    if(node->m_right) {
        node = node->m_right;

        while(node->m_left) {
            node = node->m_left;
        }
    } else {
        node = node->m_father;
        while(node != node->m_father->m_right && NOT_ROOT) {
            node = node->m_father;
        }
    }

    return node;
}

BSTreeItr BSTreeItrPrev(BSTreeItr _itr) {

    if(_itr == NULL) {
        return NULL;
    }

    Node* node = (Node*)_itr;

    if(node->m_left) {
        node = node->m_left;

        while(node->m_right) {
            node = node->m_right;
        }
    } else {
        node = node->m_father;
        while(node != node->m_father->m_left && NOT_ROOT) {
            node = node->m_father;
        }
    }

    return node;
}

void* BSTreeItrRemove(BSTreeItr _itr) {

    if(_itr == NULL) {
        return NULL;
    }

    Node* node = (Node*)_itr;

    int numOfSons = HowMannyChilds(node);

    switch(numOfSons) {
        case 0:
            return ZeroSonsRemove(node);
        
        case 2:
            return TwoSonsRemove(node);
        

        default:
            return OneSonRemove(node, numOfSons);

    }

}

void* BSTreeItrGet(BSTreeItr _itr) {

    if(_itr == NULL) {
        return NULL;
    }

    return ((Node*)_itr)->m_data;
}

//--------------------------------------------------------------------------

bool CheckFull(Node* _node) {

    int status = HowMannyChilds(_node);

    if(status == 0) {
        return true;
    }

    if(status == 1 || status == -1) {
        return false;
    }

    if(status == 2) {
        return (CheckFull(_node->m_left) && CheckFull(_node->m_right));
    }
}

bool IsFullTree(BSTree* _tree) {

    if(_tree == NULL) {
        return 0;
    }

    return CheckFull(ROOT);

}

bool IsSimilar(Node* _node1, Node* _node2) {

    if(_node1 == NULL && _node2 == NULL) {
        return true;
    } else if(_node1 != NULL && _node2 != NULL) {
        return (IsSimilar(_node1->m_left, _node2->m_left) && IsSimilar(_node1->m_right, _node2->m_right));
    }

    return false;
}

bool AreSimilarTree(BSTree* _tree1, BSTree* _tree2) {

    if(_tree1 == NULL || _tree2 == NULL) {
        return 0;
    }

    return IsSimilar(_tree1->m_root.m_left, _tree2->m_root.m_left);
}

static void* ZeroSonsRemove(Node* _node) {

    void* item = _node->m_data;

    if(_node == _node->m_father->m_left) {
        _node->m_father->m_left = NULL;
    }

    if(_node == _node->m_father->m_right) {
        _node->m_father->m_right = NULL;
    }

    free(_node);
    return item;
}

static int FindMax(int a, int b) {

    if(a > b) {
        return a;
    }
    return b;
}

static int CalcHeight(Node* _node) {

    if(_node == NULL) {
        return -1;
    }

    return 1 + FindMax(CalcHeight(_node->m_left), CalcHeight(_node->m_right));
}

static int CalcTreeLevel(BSTree* _tree) {

    if(_tree == NULL) {
        return -1;
    }

    return CalcHeight(ROOT);

}

void SwapNodes(Node* _node) {

    if(_node == NULL) {
        return;
    }

    swap(_node->m_left, _node->m_right);

    SwapNodes(_node->m_left);
    SwapNodes(_node->m_right);
}

void MirrorTree(BSTree* _tree) {

    if(_tree == NULL) {
        return;
    }

    SwapNodes(ROOT);

}

int IsPerfectTree(BSTree* _tree) {

    if(_tree == NULL) {
        return 0;
    }

    CheckPerfection(ROOT);
}

static void* OneSonRemove(Node* _node, int _direction) {

    switch (_direction)
    {
    case 1:
        _node->m_father->m_left = _node->m_left;
        break;
    
    case -1:
        _node->m_father->m_right = _node->m_right;
    default:
        break;
    }

    return ZeroSonsRemove(_node);
}

static void* TwoSonsRemove(Node* _node) {

    Node* next = BSTreeItrNext((BSTreeItr*)_node);
    swap(next, _node);

    int numOfSons = HowMannyChilds(_node);

    if (numOfSons == 0) {
        return ZeroSonsRemove(_node);
    }
    if (numOfSons == -1) {
        return OneSonRemove(_node, -1);
    }

    return NULL;
}

void swap(Node* x, Node* y) {
    Node temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

int HowMannyChilds(Node* _node) {

    if(_node->m_left == NULL && _node->m_right == NULL) {
        return 0;
    }

    if(_node->m_left != NULL && _node->m_right != NULL) {
        return 2;
    }

    if(_node->m_left != NULL && _node->m_right == NULL) {
        return 1; // left son only
    } else return -1; // right son only

}

static Node* GetBegin(Node* _node) {

    if(_node->m_left == NULL) {
        return _node;
    }

    return GetBegin(_node->m_left);
}

Node* CreateNode(Node* _fatherNode, void* _item) {

    Node* new_node = (Node*)malloc(sizeof(Node));

    if(new_node == NULL) {
        return NULL;
    }

    new_node->m_father = _fatherNode;
    new_node->m_data = _item;
    new_node->m_left = NULL;
    new_node->m_right = NULL;
    
    return new_node;
}

static Node* InsertNewNode(Node* _node, LessComparator _compare, void* _item) {

    int status = _compare(_node->m_data, _item);

    switch(status) {
        case 0: 
            return NULL;
        case 1:
            if(_node->m_left == NULL) {
                _node->m_left = CreateNode(_node, _item);
                return _node->m_left;
            } else if (_node->m_left != NULL) {
                return InsertNewNode(_node->m_left, _compare, _item);
            }
        case -1:
            if(_node->m_right == NULL) {
                _node->m_right = CreateNode(_node, _item);
                return _node->m_right;
            } else if (_node->m_right != NULL) {
                return InsertNewNode(_node->m_right, _compare, _item);
            }
    }

    return NULL;
}

/* 
check if I have sons
// if not - stop.
if yes -
    1 son - 
    2 sons - check if i am bigger from my 2 sons, if not swap. if yes, swap.
    if swap - go to the index that we swapped with. and over again.
*/