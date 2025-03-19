#ifndef MT_SEMAPHORE_H
#define MT_SEMAPHORE_H

#include <mutex>
#include <condition_variable>

namespace mt {

class Semaphore {
public:
    Semaphore(int initial_count);

    void acquire();
    void release();

private:
    std::mutex m_mutex;
    std::condition_variable m_cond;
    int m_count;
};

#endif // MT_SEMAPHORE_H

}