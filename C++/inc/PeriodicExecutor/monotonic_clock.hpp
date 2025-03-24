#ifndef EXECUTOR_MONOTONIC_TIME_CLOCK_H
#define EXECUTOR_MONOTONIC_TIME_CLOCK_H

#include "clock.hpp"
#include "time_spec.hpp"
#include <ctime>
#include <iostream>

namespace executor {


class MonotonicClock : public AbstractClock {

public:
    Time getTime() override;
    void sleep(Time nextTaskTime) override;
   
};

Time MonotonicClock::getTime()
{
    timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return Time(ts);
}

void MonotonicClock::sleep(Time nextTaskTime) {

    Time current_time = getTime();

    Time sleepDuration = nextTaskTime - current_time;

     if (sleepDuration.get_sec() < 0 || 
            (sleepDuration.get_sec() == 0 && sleepDuration.get_nsec() <= 0)) {
        return;
    }

    if (sleepDuration.get_sec() > 10) {
        std::cerr << "Sleep duration too large: " << sleepDuration.get_sec() << "s "
                  << sleepDuration.get_nsec() << "ns\n";
        return;
    }

    timespec ts;
    ts.tv_nsec = sleepDuration.get_nsec();
    ts.tv_sec = sleepDuration.get_sec();

    nanosleep(&ts, nullptr);
}

}

#endif // EXECUTOR_MONOTONIC_TIME_CLOCK_H