#ifndef EXECUTOR_TASK_H
#define EXECUTOR_TASK_H

namespace executor {


class AbstractTask {

public:
    virtual ~AbstractTask() = default;
    virtual void run() = 0;
};

}

#endif // EXECUTOR_TASK_H