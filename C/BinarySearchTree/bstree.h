#ifndef __BSTREE_H__
#define __BSTREE_H__

#include <stddef.h>  /* size_t */

/** 
 *  @file BSTree.h
 *  @brief Generic Binary Search Tree
 *	
 *  @details  Implement a binary search tree ADT.
 *  The tree is implemented using a sentinel. 
 *  The first node in the tree is the sentinel left subtree.
 *
 */

typedef struct BSTree  BSTree;
typedef void*  BSTreeItr;

typedef int (*LessComparator)(void* _left, void* _right);

/** 
 * @brief Action function to operate on an element
 *
 * @param _element : element to test
 * @param _context : context to be used
 * @return zero if action fails
 */
typedef int (*ActionFunction)(void* _element, void* _context);

typedef enum
{
    BSTREE_TRAVERSAL_PREORDER =0,
    BSTREE_TRAVERSAL_INORDER,
    BSTREE_TRAVERSAL_POSTORDER
} BSTreeTraversalMode;

/** 
 * @brief Create a binary search tree
 * Creates an empty binary search tree with sentinel
 * 
 * @param _less: A comparison function 
 *				that returns true (none zero value) if x < y 
 *				and false (zero) otherwise.
 * @return a pointer to the newly created tree.
 * @retval NULL on failure due to allocation failure or NULL function pointer given
 */
BSTree* BSTreeCreate(LessComparator _less);

/** 
 * @brief Destroy tree
 * Destroys the tree, freeing the memory.
 * If supplied with non-NULL destroyer function, frees items in tree.
 * Average time complexity: O(n) 
 *
 * @params _tree : A previously created Tree ADT returned via BSTreeCreate
 * @params _destroyer : A function to destroy the data in the tree (may be NULL if unnecessary)
 */
void  BSTreeDestroy(BSTree** _tree, void (*_destroyer)(void*));

/** 
 * @brief Add an element to tree if it'snot already there
 * Insert element to binary tree, using the tree's comparison function
 * Average time complexity O(log n).
 * Worst: O(n)
 *
 * @param _tree : A previously created Tree ADT returned via BSTreeCreate
 * @param _item: An item to add to the tree
 * @return iterator pointing to the item added or iterator to end on failure
 * @warning don't allow duplicates
 */
BSTreeItr BSTreeInsert(BSTree* _tree, void* _item);

/** 
 * @brief Get an in-order itertator to the tree's begin 
 *
 * @param _tree : tree to create iterator from
 * @return an iterator pointing at the tree's begin or end if tree is empty 
 */
BSTreeItr BSTreeItrBegin(const BSTree* _tree);

/** 
 * @brief Get itertator to the tree's end (in order)
 *
 * @param _tree : tree to create iterator from
 * @return an iterator pointing at the tree's end
 */
BSTreeItr BSTreeItrEnd(const BSTree* _tree);

/** 
 * @brief Compare two iterators
 *
 * @param _a, _b : Iterators to compare
 * @return : 0 if are not the same any noze zero value if iterators are the same
 */
int BSTreeItrEquals(BSTreeItr _a, BSTreeItr _b);

/** 
 * @brief Get itertator to the next element from current iterator
 *
 * @params _it : A tree iterator
 * @returns an iterator pointing at the next element after _it or end iterator.
 */
BSTreeItr BSTreeItrNext(BSTreeItr _itr);

/** 
 * @brief Get itertator to the previous element from current iterator
 *
 * @param _it : A tree iterator
 * @return an iterator pointing at the previous element
 * or to the beginning if _it points to the beginning
 */
BSTreeItr BSTreeItrPrev(BSTreeItr _itr);

/** 
 * @brief Removes element from tree
 * @details Remove element pointed to by _it and rearranges the tree so that it maintains binary search tree arrangement
 * Average/Worst time complexity O(1).
 *
 * @param _it : A tree iterator
 * @return removed item or null on failure
 */
void* BSTreeItrRemove(BSTreeItr _itr);

/** 
 * @brief Get element pointed to by iterator from tree
 * Average/Worst time complexity O(1).
 *
 * @param _it : A tree iterator
 * @return the item the iterator points at or null if _it as at end
 */
void* BSTreeItrGet(BSTreeItr _itr);

/** 
 * @brief Performs an action function on every element in tree, by given traversal mode
 * @details iteration will on the first element for which action returns a zero
 * or on reaching end of the conrainer
 *
 * @params _tree : tree to iterate over
 * @params _mode : Traversal mode - TREE_TRAVERSAL_PREORDER, TREE_TRAVERSAL_INORDER or TREE_TRAVERSAL_POSTORDER
 * @params _action : Action function to call for each element
 * @params _context : Parameters for the function
 * @return Iterator to end or an iterator to the specific element where action returned none zero value
 */
BSTreeItr BSTreeForEach(const BSTree* _tree, BSTreeTraversalMode _mode, ActionFunction _action, void* _context);


bool IsFullTree(BSTree* _tree);

bool AreSimilarTree(BSTree* _tree1, BSTree* _tree2);

int CalcTreeLevel(BSTree* _tree);

void MirrorTree(BSTree* _tree);

int IsPerfectTree(BSTree* _tree);


#endif /* __BSTREE_H__ */