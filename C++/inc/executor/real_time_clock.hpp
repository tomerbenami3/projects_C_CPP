#ifndef EXECUTOR_REAL_TIME_CLOCK_H
#define EXECUTOR_REAL_TIME_CLOCK_H

#include "clock.hpp"
#include "time_spec.hpp"
#include <ctime>
#include <chrono>

namespace executor {


class RealTimeClock : public AbstractClock {

public:
    Time RealTimeClock::getTime() override;
    void sleep(Time millis) override;
   

};

Time RealTimeClock::getTime()
{
    timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return Time(ts);
}

void RealTimeClock::sleep(Time nextTaskTime) {
    Time sleepDuration = nextTaskTime - getTime();

     if (sleepDuration.get_sec() < 0 || 
            (sleepDuration.get_sec() == 0 && sleepDuration.get_nsec() <= 0)) {
        return;
    }

    timespec ts;
    ts.tv_nsec = sleepDuration.get_nsec();
    ts.tv_sec = sleepDuration.get_sec();

    nanosleep(&ts, nullptr);
}

}

#endif // EXECUTOR_REAL_TIME_CLOCK_H