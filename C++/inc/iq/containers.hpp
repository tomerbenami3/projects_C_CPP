#ifndef IQ_MIN_STACK_RESETTABLE_SLOTS_HPP
#define IQ_MIN_STACK_RESETTABLE_SLOTS_HPP

#include <stack>
#include <memory>
#include <functional>
#include <stdexcept>
#include <vector>
#include <unordered_map>

namespace iq
{

template <typename T>
class MinStack {

public:
    MinStack(std::function<bool(T const&, T const&)> compare);
    void push(std::shared_ptr<T> const& value);
    void pop();
    std::shared_ptr<T> top() const;
    std::shared_ptr<T> getMin() const;

private:
    std::stack<std::shared_ptr<T>> m_stack;
    std::stack<std::shared_ptr<T>> m_minstack;
    std::function<bool(T const&, T const&)> m_compare;
};

template <typename T>
class ResettableSlots {

public:
    ResettableSlots(size_t size, std::shared_ptr<T> initial_value);

    void set(size_t i, std::shared_ptr<T> value);
    std::shared_ptr<T> get(size_t i) const;
    void reset(std::shared_ptr<T> reset_value);

private:
    size_t m_size;
    std::unordered_map<size_t, std::shared_ptr<T>> m_changes;
    std::shared_ptr<T> m_default_value;
};


}

#include "containers.txx"

#endif //IQ_MIN_STACK_RESETTABLE_SLOTS_HPP
