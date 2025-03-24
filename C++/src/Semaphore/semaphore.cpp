#include "semaphore.hpp"
#include <mutex>
#include <condition_variable>

namespace mt {

Semaphore::Semaphore(int initial_count)
: m_count(initial_count)
{}

void Semaphore::acquire()
{
    std::unique_lock lock(m_mutex);

    while(m_count <= 0) {
        m_cond.wait(lock);
    }
    --m_count;
}

void Semaphore::release()
{
    std::unique_lock lock(m_mutex);
    ++m_count;
    m_cond.notify_all();
}

}
