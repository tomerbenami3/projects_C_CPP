#include "bounded_queue.hpp"
#include <mutex>

namespace mt {

template <typename T, size_t N>
BoundedQueue<T, N>::BoundedQueue()
: m_head(0)
, m_tail(0)
, m_size(0)
{}

template <typename T, size_t N>
BoundedQueue<T, N>::~BoundedQueue()
{
    //clear() ?
}

template <typename T, size_t N>
void BoundedQueue<T, N>::enqueue(T const& value)
{
    std::unique_lock lock(m_mutex);

    while(is_full()) {
        m_cond_not_full.wait(lock);
    }

    new (reinterpret_cast<T*>(&m_data[m_tail * sizeof(T)])) T(value);

    m_tail = (m_tail + 1) % N;
    ++m_size;
    m_cond_not_empty.notify_all();
}

template <typename T, size_t N>
T BoundedQueue<T, N>::dequeue()
{
    std::unique_lock lock(m_mutex);

    while(is_empty()) {
        m_cond_not_empty.wait(lock);
    }

    T* obj = (reinterpret_cast<T*>(&m_data[m_head * sizeof(T)]));
    T value = *obj;
    obj->~T();

    m_head = (m_head + 1) % N;
    --m_size;

    m_cond_not_full.notify_all();

    return value;
}

template <typename T, size_t N>
void BoundedQueue<T, N>::push_head(T const& value)
{
    std::unique_lock lock(m_mutex);

    while (is_full()) {
        m_cond_not_full.wait(lock);
    }

    if (m_head == 0) {
        m_head = N - 1;
    } else {
        m_head = m_head - 1;
    }

    new (reinterpret_cast<T*>(&m_data[m_head * sizeof(T)])) T(value);

    ++m_size;
    m_cond_not_empty.notify_all();
}

template <typename T, size_t N>
T BoundedQueue<T, N>::pop_tail()
{
    std::unique_lock lock(m_mutex);

    while(is_empty()) {
        m_cond_not_empty.wait(lock);
    }

    if (m_tail == 0) {
        m_tail = N - 1;
    } else {
        m_tail = m_tail - 1;
    }

    T* obj = (reinterpret_cast<T*>(&m_data[m_tail * sizeof(T)]));
    T value = *obj;
    obj->~T();

    --m_size;

    m_cond_not_full.notify_all();

    return value;
}


template <typename T, size_t N>
size_t BoundedQueue<T, N>::size() const
{
    std::lock_guard lock(m_mutex);
    return m_size;
}

template <typename T, size_t N>
size_t BoundedQueue<T, N>::capacity() const
{
    return N;
}

template <typename T, size_t N>
bool BoundedQueue<T, N>::is_empty() const
{
    return m_size == 0;
}

template <typename T, size_t N>
bool BoundedQueue<T, N>::is_full() const
{
    return m_size == N;
}

template <typename T, size_t N>
void BoundedQueue<T, N>::clear()
{
    std::unique_lock lock(m_mutex);

    while (!is_empty()) {

        std::byte* ptr = &m_data[m_head * sizeof(T)];
        T* obj_ptr = reinterpret_cast<T*>(ptr);

        obj_ptr->~T();

        m_head = (m_head + 1) % N;
        --m_size;
    }
}

}