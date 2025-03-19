#ifndef MT_WORKER_THREAD_GROUP_H
#define MT_WORKER_THREAD_GROUP_H

#include <vector>
#include <thread>
#include <functional>
#include <mutex>


namespace mt {

using Task = std::function<void()>;

class ThreadFactory {

public:
    ThreadFactory() = default;
    ~ThreadFactory() = default;

    std::thread create_thread(Task task) {
        return std::thread{task};
    }

};

template <typename Factory>
class WorkerThreadGroup {
public:

    explicit WorkerThreadGroup(size_t num_workers, Task task);
    ~WorkerThreadGroup();

    /// @brief Returns the number of active worker threads.
    /// @return The number of worker threads in the pool.
    size_t size() const;

    /// @brief Adds more worker threads to the pool.
    /// @param n The number of additional worker threads to create (default: 1)
    size_t add(size_t n);

    // @brief Removes worker threads from the pool.
    // @param n The number of workers to remove.
    // @return The number of workers successfully removed.
    size_t remove_workers(size_t n);

	void join_all();

private:
	mutable std::mutex m_mutex;
    std::vector<std::thread> m_workers;
    Task m_task;
    Factory m_thread_factory;
};

}

#include "worker_threads_group.txx"

#endif //MT_WORKER_THREAD_GROUP_H
