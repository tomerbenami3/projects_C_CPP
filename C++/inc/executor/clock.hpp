#ifndef EXECUTOR_CLOCK_H
#define EXECUTOR_CLOCK_H

#include "time_spec.hpp"

namespace executor {


class AbstractClock {

public:
    virtual ~AbstractClock() = default;
    virtual Time getTime() = 0;

    virtual void sleep(Time millis) = 0;
};

}

#endif // EXECUTOR_CLOCK_H