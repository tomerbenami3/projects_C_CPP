#include "../../inc/ds/intstack.hpp"
#include <cstdlib>
#include <iostream>
#include <cassert>

namespace ds {

IntStack::IntStack(size_t capacity)
: m_capacity{capacity}
, m_elements{(int*)::calloc(m_capacity, sizeof(*m_elements))}
, m_nelements{0}
{
	assert(m_elements);
}

IntStack::~IntStack()
{
	::free(m_elements);
}

IntStack::IntStack(IntStack const& other)
: m_capacity{other.m_capacity}
, m_elements{(int*)::calloc(m_capacity, sizeof(*m_elements))}
, m_nelements{other.m_nelements}
{
	for (size_t i = 0; i < m_capacity; ++i) {
		m_elements[i] = other.m_elements[i];
	}
}

IntStack& IntStack::operator=(IntStack const& other)
{
	if (this != &other) {
		::free(m_elements);
		m_capacity = other.m_capacity;
        m_nelements = other.m_nelements;
		m_elements = (int*)::calloc(m_capacity, sizeof(*m_elements));
		for (size_t i = 0; i < m_capacity; ++i) {
			m_elements[i] = other.m_elements[i];
		}
	}

	return *this;
}

void IntStack::push(size_t number)
{

    assert(!(m_nelements == m_capacity));
    m_elements[m_nelements] = number;
    m_nelements += 1;
}

int IntStack::pop()
{

    assert(m_nelements != 0);
    --m_nelements;
    return m_elements[m_nelements];
}

int IntStack::top() const {

    assert(m_nelements != 0);
    return m_elements[m_nelements - 1];
}

size_t IntStack::capacity() const
{
	return m_capacity;
}

size_t IntStack::size() const
{
	return m_nelements;
}

bool IntStack::is_empty() const
{
	return m_nelements == 0;
}

bool IntStack::is_full() const
{
	return m_nelements == m_capacity;
}

void IntStack::StackDrain(IntStack& to_drain)
{

    IntStack temp;

    while(!to_drain.is_empty()) {
        temp.push(to_drain.pop());
    }

    while(!temp.is_empty()) {
        this->push(temp.pop());
    }
}

void IntStack::StackSpill(IntStack& to_drain)
{

    IntStack temp;

    while(!to_drain.is_empty()) {
        this->push(to_drain.pop());
    }

}

void IntStack::StackSwap(IntStack& to_swap)
    {
        IntStack temp1, temp2;
        while(!to_swap.is_empty()) {   
            temp1.push(to_swap.pop());  
        }

        while(!is_empty()) {       
            temp2.push(pop());
        }

        while(!temp1.is_empty()) {   
            push(temp1.pop());  
        }

        while(!temp2.is_empty()) {   
            to_swap.push(temp2.pop());  
        }
    }
}