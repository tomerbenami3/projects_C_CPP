#include "periodic_executor.hpp"
#include "time_spec.hpp"
#include <iostream>

namespace executor {

PeriodicExecutor::PeriodicExecutor(AbstractClock& clock)
: m_time (clock)
, m_clock(clock)
{}

void PeriodicExecutor::addTask(AbstractTask& task, size_t periodTime, size_t execute_amount) {

    if(execute_amount > 0) {
    Task t1 = {&task, periodTime, Time(0, 0), execute_amount};
    m_tasks.push_back(t1);
    }

    return;
}

void PeriodicExecutor::remove_task(AbstractTask& task_to_remove)
{
    std::vector<Task>::iterator itr;

    for(itr = m_tasks.begin(); itr != m_tasks.end(); ++itr) {
        if(itr->task == &task_to_remove) {
            m_tasks.erase(itr);
            std::cout << "task removed successfully.\n";
            return;
        }
    }
}

void PeriodicExecutor::run() 
{
    std::vector<Task>::iterator itr;

    for(itr = m_tasks.begin(); itr != m_tasks.end(); ++itr) {
        itr->execution_time = m_time.calculate_exec_time(itr->period_time);
    }
    
    std::priority_queue<Task, std::vector<Task>, std::greater<Task>> pq(m_tasks.begin(), m_tasks.end());

    while(!pq.empty()) {
        Task next_task = pq.top();
        pq.pop();

        m_clock.sleep(next_task.execution_time);

        next_task.task->run();
        --next_task.execute_amount;

        if(next_task.execute_amount != 0) {
            next_task.execution_time = m_time.calculate_exec_time(next_task.period_time);
            pq.push(next_task);
        }
    }

}


}