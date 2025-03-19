#ifndef __DLIST_H__
#define __DLIST_H__

#include <stddef.h>  /* size_t */

typedef struct List List;
typedef void* ListItr;


/** 
 * @brief Action function to operate on an element
 *
 * @param _element : element to test
 * @param _context : context to be used
 * @return zero if action fails
 */
typedef int (*ListActionFunction)(void* _element, void* _context);

/** 
 * @brief Create a list
 * 
 * @returns a pointer to the created list.
 * @retval NULL on failure due to allocation failure
 */
List* ListCreate(void);

/** 
 * @brief Destroy list
 * @details Destroys the list completely 
 *          optionally destroys elements using user provided function
 *
 * @params[in] _pList : A pointer to previously created List returned via ListCreate
 *					   on completion *_pList will be null
 * @params[in] _elementDestroy : A function pointer to be used to destroy elements inserted into the list
 *             or a null if no such destroy is required
 */
void ListDestroy(List** _pList, void (*_elementDestroy)(void* _item));

/** 
 * @brief Add element to head of list
 * @details time complexity: O(1).
 *
 * @params _list A previously created List ADT returned via ListCreate
 * @params _item An item to add to the list
 * @return an iterator pointing at the element inserted or NULL on error
 */
ListItr ListPushHead(List* _list, void* _item);

/** 
 * @brief Add element to the list's tail
 * @details time complexity O(1).
 *
 * @params _list A previously created List ADT returned via ListCreate
 * @params _item An item to add to the list
 * @return an iterator pointing at the element inserted or NULL on error
 */
ListItr ListPushTail(List* _list, void* _item);

/** @brief Remove element from list's head
 *  @details if successfull, return a pointer to the removed item 
 *  time complexity O(1).
 *
 * @params _list : A previously created List ADT returned via ListCreate
 * @return an iterator pointing at the element that removed or NULL on error
 */
void* ListPopHead(List* _list);

/** @brief Remove element from list's tail
 *  @details if successfull, return a pointer to the removed item 
 *  time complexity O(1).
 *
 * @params _list : A previously created List ADT returned via ListCreate
 * @return an iterator pointing at the element that removed or NULL on error
 */
void* ListPopTail(List* _list);

/** 
 * @brief Get itertator to the list's beginning
 *
 * @params _list : list to return begin iterator, pointing at first element
 *                 or at the end if list is empty
 * @return iterator pointing at the list's beginning
 */
ListItr ListItrBegin(const List* _list);

/** 
 * @brief Get itertator to the list end
 *
 * @params _list : list to return end iterator
 * @return an iterator pointing at the list's end
 */
ListItr ListItrEnd(const List* _list);

/** 
 * @brief retruns none zero if _a and _b iterators refer to same node
 * @warning might be implemented as a macro
 */
int ListItrEquals(const ListItr _a, const ListItr _b);

/** 
 * @brief Get itertator to the next element from a given iterator
 * @warning if _itr is end iterator it will be returned
 */
ListItr ListItrNext(ListItr _itr);

/** 
 * @brief Get itertator to the previous element
 * @warning if _itr is begin iterator it will be returned
 */
ListItr ListItrPrev(ListItr _itr);

/** 
 * @brief Get data from the list node the iterator is pointing to
 *
 * @params _itr : A list iterator
 * @return the data the iterator is pointing at or NULL if pointing to the end
 */
void* ListItrGet(ListItr _itr);

/** 
 * @brief Set data at the node where the iterator is pointing at
 * @return the data from the node to be changed
 */
void* ListItrSet(ListItr _itr, void* _element);

/** 
 * @brief Inserts a new node before node the iterator is pointing at
 * @return an iterator pointing at the element inserted or NULL on error
 */
ListItr ListItrInsertBefore(ListItr _itr, void* _element);

/** 
 * @brief Removes the node the iterator is pointing at
 *
 * @params _itr : A list iterator
 * @return the removed data
 */
void* ListItrRemove(ListItr _itr);

/** @brief Get number of elements in the list
 * Average time complexity O(n).
 *
 * @params _list : A previously created List ADT returned via ListCreate
 */
size_t ListSize(const List* _list);

/**
 * @brief Check if a given list is empty
 * @param[in] _list - The list to check
 * @return size_t - return none zero if empty
 *
 */
size_t ListIsEmpty(List* _list);

/** 
 * @brief execute an action for all elements in a half open range
 * @details call -action for each element in the range [begin..end)
 * iteration will stop if Action function returns 0 for an element
 *
 * @param _begin: A list iterator to start operations from
 * @param _end : A list iterator to end operations on
 * @param _Action : user provided action function
 * @param _context : Parameters for the function
 * @return ListItr to the element where the iteration stoped. this might be end iterator
 */
ListItr ListItrForEach(ListItr _begin, ListItr _end, ListActionFunction _action, void* _context);


#endif /* __NEW_GEN_DLIST_H__ */