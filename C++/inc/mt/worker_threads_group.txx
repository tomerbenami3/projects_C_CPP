#include "worker_threads_group.hpp"

namespace mt {

template <typename Factory>
WorkerThreadGroup<Factory>::WorkerThreadGroup(size_t num_workers, Task task)
: m_task{task}
{
    for(size_t i = 0; i < num_workers; ++i) {
        m_workers.push_back(m_thread_factory.create_thread(m_task));
    }
}

template <typename Factory>
WorkerThreadGroup<Factory>::~WorkerThreadGroup()
{}

template <typename Factory>
size_t WorkerThreadGroup<Factory>::size() const
{
	std::lock_guard lock(m_mutex);
    return m_workers.size();
}

template <typename Factory>
size_t WorkerThreadGroup<Factory>::add(size_t n)
{
    std::lock_guard lock(m_mutex);

    size_t count = 0;
    for (size_t i = 0; i < n; ++i) {
        try {
            m_workers.push_back(m_thread_factory.create_thread(m_task));
            ++count;
        } catch (...) {
            break;
        }
    }
    return count;
}

template <typename Factory>
void WorkerThreadGroup<Factory>::join_all() 
{   
    m_mutex.lock();
    auto w = std::move(m_workers);
    m_mutex.unlock();

    for (auto& worker : w) {
        worker.join();
    }
}

}
