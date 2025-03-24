#ifndef DS_INT_QUEUE_H
#define DS_INT_QUEUE_H

#include <cstddef>
#include "intstack.hpp"

namespace ds {

class IntQueue {
public:

	/// @brief constructor
	/// @param capacity queue size
	IntQueue(size_t capacity = 128);

	/// @brief destructor
	~IntQueue() = default;

    /// @brief copy constructor
    /// @param other copy from other
    IntQueue(IntQueue const& other);
	/// @brief assignment constructor
	/// @param other copy from other
	/// @return IntQueue by reference
	IntQueue& operator=(IntQueue const& other);

    /// @brief push to the queue
    /// @param number item to push
    void enqueue(int number);
    /// @brief pop from queue
    /// @return removed item
    int dequeue();
    /// @brief clear all queue
    void clear();
    /// @brief swap between two queues
    /// @param other swap other with this
    void swap(IntQueue& other);
    /// @brief get total capacity
    /// @return total capacity of queue 
    size_t capacity() const;
    /// @brief number of elements
    /// @return number of elements
    size_t size() const;
    /// @brief check if queue is empty
    /// @return 1 if empty, 0 if not
    bool empty() const;
    /// @brief check if queue is full
    /// @return 1 if full, 0 if not
    bool full() const;

private:
	IntStack m_enque;
    IntStack m_deque;
    size_t m_capacity;
    size_t m_size;
};


} // namespace ds


#endif // DS_INT_QUEUE_H
