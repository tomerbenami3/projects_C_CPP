#ifndef MT_THREAD_POOL_H
#define MT_THREAD_POOL_H

#include "bounded_queue.hpp"
#include "worker_threads_group.hpp"

#include <vector>
#include <thread>
#include <atomic>
#include <functional>


namespace mt {


template <size_t Capacity>
class ThreadPoolExecutor {
public:

    using Task = std::function<void()>;

    /// @brief Constructs a thread pool with a specified number of worker threads.
    /// @param num_workers The initial number of worker threads (default: 1).
    explicit ThreadPoolExecutor(size_t num_workers = 1);

    /// @brief Destructor. Cleans up worker threads and shuts down the pool.
    ~ThreadPoolExecutor();

    /// @brief Submits a task to the thread pool for execution.
    /// @param task The task function to be executed by a worker thread.
    void submit(Task const& task);

    void submit_priority(Task const& task);

    /// @brief Returns the number of tasks currently waiting in the queue.
    /// @return The number of pending tasks.
    size_t tasks_size() const;

    /// @brief Returns the number of active worker threads.
    /// @return The number of worker threads in the pool.
    size_t worker_size() const;

    /// @brief Adds more worker threads to the pool.
    /// @param n The number of additional worker threads to create (default: 1)
    size_t add_workers(size_t n = 1);

    // @brief Removes worker threads from the pool.
    // @param n The number of workers to remove.
    // @return The number of workers successfully removed.
    size_t remove_workers(size_t n);

    // @brief Gracefully shuts down the thread pool.
    // Executes all remaining tasks in the queue before shutting down.
    void shutdown_graceful();

    // @brief Immediately shuts down the thread pool.
    // Allows currently running tasks to finish, but discards remaining queued tasks.
    void shutdown_immediate();

private:

    /**
     * @brief The function executed by each worker thread.
     * Each worker thread continuously fetches tasks from the queue and executes them.
     * The thread exits when the pool is shutting down.
     */
    void worker_thread();
    void shutdown_function();

private:
    mutable std::mutex m_mutex;
    bool m_shutdown = false;
    BoundedQueue<Task, Capacity> m_task_queue;
    PushHeadBQ<Task, Capacity> m_priority_task;
	WorkerThreadGroup<ThreadFactory> m_workers;
};

} //namespace mt

#include "thread_pool_executor.txx"


#endif //MT_THREAD_POOL_H
