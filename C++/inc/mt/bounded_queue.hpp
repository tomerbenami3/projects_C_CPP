#ifndef MT_BOUNDED_QUEUE_HPP
#define MT_BOUNDED_QUEUE_HPP

#include <cstddef>
#include <mutex>
#include <stdexcept>
#include <new>
#include <array>
#include <condition_variable>


namespace mt {

template <typename T, size_t N>
class PushHeadBQ;

template <typename T, size_t N>
class BoundedQueue {
public:
    explicit BoundedQueue();
    ~BoundedQueue();

    void enqueue(T const& value);
    T dequeue();

    size_t size() const;
    size_t capacity() const;
    bool is_empty() const;
    bool is_full() const;
    void clear();

private:
    void push_head(T const& value);
    T pop_tail();

    friend class PushHeadBQ<T, N>;

private:
    alignas(T) std::array<std::byte, sizeof(T) * N> m_data;
    size_t m_head;
    size_t m_tail;
    size_t m_size;
    mutable std::mutex m_mutex;
    std::condition_variable m_cond_not_full;
    std::condition_variable m_cond_not_empty;
};

template <typename T, size_t N>
class PushHeadBQ {
public:
    PushHeadBQ() = default;
    ~PushHeadBQ() = default;

    void push_head(BoundedQueue<T, N>& queue, T const& item) {
        queue.push_head(item);
    }

    void pop_tail(BoundedQueue<T, N>& queue) {
        queue.pop_tail();
    }
};

}

#include "bounded_queue.txx"

#endif // MT_BOUNDED_QUEUE_HPP