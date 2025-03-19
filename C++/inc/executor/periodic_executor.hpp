#ifndef EXECUTOR_PERIODIC_EXECUTOR_H
#define EXECUTOR_PERIODIC_EXECUTOR_H

#include "abstract_executor.hpp"
#include "abstract_task.hpp"
#include "time_calculations.hpp"
#include "time_spec.hpp"
#include <queue>
#include <vector>
#include <cstddef>


namespace executor {

struct Task {
    AbstractTask* task;
    size_t period_time;
    Time execution_time;
    size_t execute_amount;

    bool operator>(Task const& other) const {
        return execution_time > other.execution_time;
    }
};

class PeriodicExecutor : AbstractExecutor {

public:
    PeriodicExecutor(AbstractClock& clock);
    ~PeriodicExecutor() = default;

    void addTask(AbstractTask& task, size_t periodTime, size_t execute_amount) override;

    void remove_task(AbstractTask& task_to_remove) override;

    void run() override;

private:
    std::vector<Task> m_tasks;
    TimeCalculation m_time;
    AbstractClock& m_clock;
};


}

#endif // EXECUTOR_PERIODIC_EXECUTOR_H