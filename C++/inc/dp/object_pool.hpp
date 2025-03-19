#ifndef DP_OBJECT_POOL_H
#define DP_OBJECT_POOL_H

#include <stack>
#include <cstddef>
#include <memory>

namespace dp {

template <typename T>
class ObjectFactory {
public:
    ~ObjectFactory() = default;
    std::unique_ptr<T> create() const {
        return std::make_unique<T>();
    }
};

template <typename T, typename RampUpPolicy, typename Factory = ObjectFactory<T>>
class ObjectPool : public std::enable_shared_from_this<ObjectPool<T, RampUpPolicy, Factory>>
{
public:

    using PoolPtr = std::shared_ptr<ObjectPool<T, RampUpPolicy, Factory>>;

    static PoolPtr create(size_t size, RampUpPolicy policy = RampUpPolicy(), Factory factory = Factory()) {
        return std::shared_ptr<ObjectPool>(new ObjectPool(size, policy, factory));
    }


    std::unique_ptr<T, std::function<void(T*)>> take();
    void release(std::unique_ptr<T, std::function<void(T*)>> object);
    size_t size() const;

private:
    ObjectPool(size_t size, RampUpPolicy policy, Factory factory = Factory());
    // ~ObjectPool() = default;
    // ObjectPool(ObjectPool const& other) = delete;
    // ObjectPool& operator=(ObjectPool const& other) = delete;

private:
    std::stack<std::unique_ptr<T>> m_stack;
    RampUpPolicy m_policy;
    Factory m_factory;
    size_t m_initial_size;
};

template <typename T>
class NoRampPolicy
{
public:
    explicit NoRampPolicy() = default;
    ~NoRampPolicy() = default;

    void IfStackEmptyPolicy(std::stack<std::unique_ptr<T>>&, ObjectFactory<T>&);

private:
    size_t m_currentObjects = 0;
};

template <typename T>
class RampUpPolicy {
public:
    explicit RampUpPolicy(size_t max);
    ~RampUpPolicy() = default;

    void IfStackEmptyPolicy(std::stack<std::unique_ptr<T>>& pool, ObjectFactory<T> const& factory);
    void decreaseCurrentObjects();


private:
    size_t m_maxObjects;
    size_t m_currentObjects = 0;
};

template <typename T>
class ShrinkBackPolicy {
public:
    void HandleShrink(std::stack<std::unique_ptr<T>>& pool, size_t initial_size, RampUpPolicy<T>& policy) {
        while (pool.size() > initial_size) {
            pool.pop();
            policy.decreaseCurrentObjects();
        }
    }
};

}

#include "object_pool.txx"

#endif // DP_OBJECT_POOL_H