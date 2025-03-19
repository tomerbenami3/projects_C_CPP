#include "object_pool.hpp"
#include <memory>
#include <stack>
#include <type_traits>

namespace dp {

template <typename T, typename RampUpPolicy, typename Factory>
ObjectPool<T, RampUpPolicy, Factory>::ObjectPool(size_t size, RampUpPolicy policy, Factory factory)
: m_policy(policy)
, m_factory(factory)
, m_initial_size(size)
{
    for(size_t i = 0; i < size; ++i) {
        m_stack.push(m_factory.create());
    }
}

template <typename T, typename RampUpPolicy, typename Factory>
std::unique_ptr<T, std::function<void(T*)>> ObjectPool<T, RampUpPolicy, Factory>::take()
{
    if (m_stack.empty()) {
        m_policy.IfStackEmptyPolicy(m_stack, m_factory);
        if (m_stack.empty()) { 
            throw std::out_of_range("Object pool is empty and cannot expand further.");
        }
    }

    auto uptr = std::move(m_stack.top());
    m_stack.pop();

    std::shared_ptr<ObjectPool> poolSharedPtr = this->shared_from_this();

    return std::unique_ptr<T, std::function<void(T*)>>(
        uptr.release(),
        [poolSharedPtr](T* obj) {
            if (poolSharedPtr) {  
                poolSharedPtr->release(std::unique_ptr<T>(obj));
            } else {
                delete obj;
            }
        });
}

template <typename T, typename RampUpPolicy, typename Factory>
void ObjectPool<T, RampUpPolicy, Factory>::release(std::unique_ptr<T, std::function<void(T*)>> object)
{
    std::unique_ptr<T> fixed_object(object.release());
    m_stack.push(std::move(fixed_object));

    if constexpr (std::is_same_v<RampUpPolicy, dp::RampUpPolicy<T>>) {
        if (m_stack.size() > m_initial_size) {
            ShrinkBackPolicy<T>().HandleShrink(m_stack, m_initial_size, m_policy);
        }
    }
}

template <typename T, typename RampUpPolicy, typename Factory>
size_t ObjectPool<T, RampUpPolicy, Factory>::size() const
{
    return m_stack.size();
}


template <typename T>
void NoRampPolicy<T>::IfStackEmptyPolicy(std::stack<std::unique_ptr<T>>&, ObjectFactory<T>&) {
    throw std::out_of_range("Alo en makom ah sheli go to petah tikva.\n");
}

template <typename T>
RampUpPolicy<T>::RampUpPolicy(size_t max)
: m_maxObjects(max)
{}

template <typename T>
void RampUpPolicy<T>::IfStackEmptyPolicy(std::stack<std::unique_ptr<T>>& stack, ObjectFactory<T> const& factory)
{
    if (m_currentObjects < m_maxObjects) {
            stack.push(factory.create());
            ++m_currentObjects;
    } else {
        throw std::runtime_error("Object pool stack limit reached! No more objects can be created.");
    }
}

template <typename T>
void RampUpPolicy<T>::decreaseCurrentObjects()
{
    if (m_currentObjects > 0) {
        --m_currentObjects;
    }
}


}