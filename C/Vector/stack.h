#ifndef __STACK_H__
#define __STACK_H__

#include <stddef.h>  /* size_t */

typedef struct Stack Stack;
typedef int	(*StackElementAction)(void* _element, size_t _index, void* _context);

typedef enum Stack_Result {
	STACK_SUCCESS,
	STACK_UNITIALIZED_ERROR,				
	STACK_ALLOCATION_ERROR,				
	STACK_IS_EMPTY,
    STACK_POINTER_ERROR,
    STACK_ERROR,
    STACK_OVERFLOW
	/* Add more as needed by your implementation */
} StackResult;

/**  
 * @brief Dynamically create a new stack object of given capacity and  
 * @param[in] _initialCapacity - initial capacity, number of elements that can be stored initially
 * @param[in] _blockSize - the stack will grow or shrink on demand by this size 
 * @return Stack * - on success / NULL on fail 
 *
 * @warning if _blockSize is 0 the stack will be of fixed size. 
 * @warning if both _initialCapacity and _blockSize are zero function will return NULL.
 */
Stack* StackCreate(size_t _initialCapacity, size_t _blockSize);

/**  
 * @brief Dynamically deallocate a previously allocated stack  
 * @param[in] _stack - Stack to be deallocated.
 * @params[in] _elementDestroy : A function pointer to be used to destroy all elements in the stack
 *             or a null if no such destroy is required
 * @return void
 */
void StackDestroy(Stack** _stack, void (*_elementDestroy)(void* _item));

/**  
 * @brief Add an Item to the top of the Stack.  
 * @param[in] _stack - Stack to push to.
 * @param[in] _item - Item to add.
 * @return success or error code 
 * @retval STACK_SUCCESS on success 
 * @retval STACK_.... 
 * (cover all possibilities) 
 */
StackResult StackPush(Stack* _stack, void* _item);

/**  
 * @brief Delete an Element from the top of the Stack.  
 * @param[in] _stack - Stack to delete item from.
 * @param[out] _pValue - pointer to variable that will receive deleted item value
 * @return success or error code 
 * @retval STACK_SUCCESS on success 
 * @retval STACK_.... 
 * (cover all possibilities) 
 * @warning _item can't be null. this will be assertion violation
 */
StackResult StackPop(Stack* _stack, void** _pValue);

/**  
 * @brief Return the Element from the top of the Stack.  
 * @param[in] _stack - Stack to return the top.
 * @param[out] _pValue - pointer to variable that will receive deleted item value
 * @return success or error code 
 * @retval STACK_SUCCESS on success 
 * @retval STACK_.... 
 * (cover all possibilities) 
 * @warning _item can't be null. this will be assertion violation
 */
StackResult StackTop(Stack* _stack, void** _pValue);


/**  
 * @brief Get the number of actual items currently in the stack.
 * @param[in] _stack - Stack to use.
 * @return  number of items on success 0 if stack is empty or invalid			
 */
size_t StackSize(const Stack* _stack);

/**  
 * @brief Get the current capacity of the  stack.
 * @param[in] _stack - Stack to use.
 * @return  capacity of stack			
 */
size_t StackCapacity(const Stack* _stack);

/**  
 * @brief Check if stack is empty.
 * @param[in] _stack - Stack to check.
 * @return  TRUE (1) - if empty or ERROR
	    FALSE(0) - if not empty			
 */
int StackIsEmpty(Stack* _stack);


/**  
 * @brief print all elements in the stack.
 * @details The user provided _action function will be called for each element
 *          if _action return a zero for an element the iteration will stop.  
 * @param[in] _stack - stack to iterate over.
 * @param[in] _action - User provided function pointer to be invoked for each element
 * @param[in] _context - User provided context, will be sent to _action
 * @returns number of times the user functions was invoked
 * 
 */
size_t StackPrint(const Stack* _stack, StackElementAction _action, void* _context);

#endif /* __STACK_H__ */
