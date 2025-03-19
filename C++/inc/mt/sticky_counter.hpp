#ifndef MT_STICKY_COUNTER_H
#define MT_STICKY_COUNTER_H

#include <atomic>

namespace mt {

class StickyCounter {

public:
    StickyCounter(int initial_value)
    : value(initial_value)
    {}

    int read() const
    {
        return value.load();
    }

    void decrement()
    {
        int current = value.load();

        if (current != 0) {
            value.compare_exchange_strong(current, current - 1);
        }
    }

    void increment()
    {
        int current = value.load();

        if (current != 0) {
            value.compare_exchange_strong(current, current + 1);
        }
    }


private:
    std::atomic<int> value;
};

}

#endif //MT_STICKY_COUNTER_H