#include "intqueue.hpp"
#include <cassert>
#include <utility>


namespace ds {

IntQueue::IntQueue(size_t capacity)
: m_enque{capacity}
, m_deque{capacity}
, m_capacity{capacity}
, m_size{0}
{
}

IntQueue::IntQueue(IntQueue const& other)
: m_enque{other.m_enque}
, m_deque{other.m_deque}
, m_capacity{other.m_capacity}
, m_size{other.m_size}
{
}

void IntQueue::swap(IntQueue& other)
{
    std::swap(this->m_enque, other.m_enque);
    std::swap(this->m_deque, other.m_deque);
    std::swap(this->m_capacity, other.m_capacity);
    std::swap(this->m_size, other.m_size);
}

IntQueue& IntQueue::operator=(IntQueue const& other)
{
    if (this!= &other) {
        IntQueue temp(other);
        swap(temp);
        }

    return *this;
}

size_t IntQueue::capacity() const
{
    return m_capacity;
}

size_t IntQueue::size() const
{
    return m_size;
}

void IntQueue::enqueue(int number)
{
    assert(!full());

    if(m_enque.is_full()) {
        m_enque.StackDrain(m_deque);
    }
    m_enque.push(number);
    ++m_size;
}

int IntQueue::dequeue()
{
    assert(!empty());

    if(m_deque.is_empty()) {
        m_deque.StackSpill(m_enque);
    }
    int item = m_deque.pop();
    --m_size;

    return item;
}

bool IntQueue::full() const
{
    return m_enque.is_full() && m_deque.is_full();
}

bool IntQueue::empty() const
{
    return m_enque.is_empty() && m_deque.is_empty();
}

void IntQueue::clear()
{
    while(!empty()) {
        this->dequeue();
    }
}

}
