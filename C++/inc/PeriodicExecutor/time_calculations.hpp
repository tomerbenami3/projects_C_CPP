#ifndef EXECUTOR_TIME_CALCULATIONS_H
#define EXECUTOR_TIME_CALCULATIONS_H
#include "clock.hpp"
#include "time_spec.hpp"
#include <thread>

namespace executor {


class TimeCalculation {

public:
    TimeCalculation(AbstractClock& m_other_clock)
    : m_clock(m_other_clock)
    {

    }

    Time inline calculate_exec_time(size_t period_time);
   

private:
    AbstractClock& m_clock;

};

Time TimeCalculation::calculate_exec_time(size_t period_time) {
    
    Time period(0, period_time * 1000000);
    Time currentTime = m_clock.getTime();
    
    return currentTime + period;
}

}

#endif // EXECUTOR_TIME_CALCULATIONS_H