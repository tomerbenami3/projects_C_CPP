#include "thread_pool_executor.hpp"
#include <iostream>

namespace mt {

template <size_t Capacity>
ThreadPoolExecutor<Capacity>::ThreadPoolExecutor(size_t num_workers)
: m_workers{num_workers, [this]{worker_thread();}}
{}

template <size_t QueueCapacity>
ThreadPoolExecutor<QueueCapacity>::~ThreadPoolExecutor()
{}

template <size_t Capacity>
void ThreadPoolExecutor<Capacity>::submit(Task const& task)
{
    m_task_queue.enqueue(task);
}

template <size_t Capacity>
void ThreadPoolExecutor<Capacity>::submit_priority(Task const& task)
{
    m_priority_task.push_head(m_task_queue, task);
}


template <size_t Capacity>
size_t ThreadPoolExecutor<Capacity>::tasks_size() const
{
    return m_task_queue.size();
}

template <size_t Capacity>
size_t ThreadPoolExecutor<Capacity>::worker_size() const
{
    std::lock_guard lock(m_mutex);
    return m_workers.size();
}

template <size_t Capacity>
size_t ThreadPoolExecutor<Capacity>::add_workers(size_t n)
{
    std::lock_guard lock(m_mutex);
    return m_workers.add(n);
}

template <size_t Capacity>
void ThreadPoolExecutor<Capacity>::shutdown_graceful()
{
    {
        std::lock_guard lock(m_mutex);
        m_shutdown = true;
    }

    for (size_t i = 0; i < m_workers.size(); ++i) {
        m_priority_task.push_head(m_task_queue, []{});
    }

    m_workers.join_all();
}

template <size_t Capacity>
void ThreadPoolExecutor<Capacity>::shutdown_immediate()
{
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_shutdown = true;
        m_task_queue.clear();
    }

    submit([this]{shutdown_function();});

    // for (size_t i = 0; i < m_workers.size(); ++i) {
    //     m_priority_task.push_head(m_task_queue, []{});
    // }

    // m_mutex.lock();
    // if(m_workers.size() > 0) {
    //     m_mutex.unlock();
    //     m_priority_task.pop_tail(m_task_queue);
    //     m_priority_task.push_head(m_task_queue, [this]{shutdown_function();});
    // }
    // m_mutex.unlock();

    m_workers.join_all();
}

template <size_t QueueCapacity>
void ThreadPoolExecutor<QueueCapacity>::worker_thread()
{
    m_mutex.lock();
    while(!m_shutdown) {
        m_mutex.unlock();
        Task task =  m_task_queue.dequeue();

        try {
            task();
        } catch (...) {
            std::cerr << "Unknown exception in worker thread!" << std::endl;
        }
        m_mutex.lock();
    }
    m_mutex.unlock();
}

template <size_t QueueCapacity>
void ThreadPoolExecutor<QueueCapacity>::shutdown_function()
{
    if(m_shutdown) {
        submit([this]{this->shutdown_function();});
    }
}



}