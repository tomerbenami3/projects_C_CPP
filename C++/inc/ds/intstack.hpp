#ifndef DS_INT_STACK_H
#define DS_INT_STACK_H

#include <cstddef>

namespace ds {

class IntStack {
public:
	IntStack(size_t capacity = 64);
	~IntStack();

    IntStack(IntStack const& other);
	IntStack& operator=(IntStack const& other);

    void push(size_t number);
    int pop();
    int top() const;
    size_t capacity() const;
    size_t size() const;
    bool is_empty() const;
    bool is_full() const;

    void StackDrain(IntStack& to_drain);
    void StackSpill(IntStack& to_drain);
    void StackSwap(IntStack& to_swap);

private:
	size_t m_capacity;
	int* m_elements;
    size_t m_nelements;
};


} // namespace ds


#endif // DS_INT_STACK_H
