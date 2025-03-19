#ifndef EXECUTOR_ABSTRACT_EXECUTOR_H
#define EXECUTOR_ABSTRACT_EXECUTOR_H

#include "abstract_task.hpp"
#include <unistd.h>


namespace executor {


class AbstractExecutor {

public:
    virtual ~AbstractExecutor() = default;

    virtual void addTask(AbstractTask& task, size_t periodTime, size_t execute_amount) = 0;

    virtual void remove_task(AbstractTask& task_to_remove) = 0;

    virtual void run() = 0;

};


}

#endif // EXECUTOR_ABSTRACT_EXECUTOR_H