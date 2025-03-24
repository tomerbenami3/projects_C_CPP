#include "containers.hpp"

namespace iq {


template<typename T>
MinStack<T>::MinStack(std::function<bool(T const&, T const&)> compare)
: m_compare(compare)
{}

template<typename T>
void MinStack<T>::push(std::shared_ptr<T> const& value)
{
    m_stack.push(value);

    if(m_minstack.empty() || m_compare(*value, *(m_minstack.top()))) {
        m_minstack.push(value);
    }
}

template<typename T>
void MinStack<T>::pop()
{
    if(m_stack.empty()) {
        throw std::out_of_range("stack is empty sorry bro\n");
    }

    if(m_stack.top() == m_minstack.top()) {
        m_minstack.pop();
    }
    m_stack.pop();
}

template<typename T>
std::shared_ptr<T> MinStack<T>::top() const
{
    if(m_stack.empty()) {
        throw std::out_of_range("stack is empty sorry bro\n");
    }

    return *(m_stack.top());
}

template<typename T>
std::shared_ptr<T> MinStack<T>::getMin() const
{
    if(m_minstack.empty()) {
        throw std::out_of_range("minimum stack is empty sorry bro\n");
    }

    return (m_minstack.top());
}


// Resettable slots ----------------------------------------------------------------------------------------

template <typename T>
ResettableSlots<T>::ResettableSlots(size_t size, std::shared_ptr<T> initial_value)
: m_size(size)
, m_default_value(initial_value)
{}

template <typename T>
void ResettableSlots<T>::set(size_t i, std::shared_ptr<T> value)
{
    if(i >= m_size) {
        throw std::out_of_range("index is out of range sorry bro\n");
    }
    m_changes[i] = value;
}

template <typename T>
std::shared_ptr<T> ResettableSlots<T>::get(size_t i) const
{
    if(i >= m_size) {
        throw std::out_of_range("index is out of range sorry bro\n");
    }

    return m_changes.count(i) ? m_changes.at(i) : m_default_value;
}

template <typename T>
void ResettableSlots<T>::reset(std::shared_ptr<T> reset_value)
{
    m_default_value = reset_value;
    m_changes.clear();
}

}
