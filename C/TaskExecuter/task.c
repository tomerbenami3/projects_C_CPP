#include <stdlib.h>
#include <stdio.h>
#include "task.h"
#include "calctime.h"

#define MAGIC_NUMBER 0xDEADBEEF

struct Task {
    TaskFunction m_function;
    void* m_context;
    size_t m_periodTime;
    size_t m_execTime;
    clockid_t m_clockid;
    int m_magicNumber;
};

Task* TaskCreate(TaskFunction _taskFunction, void* _context, size_t _period_ms, clock_t _clockid) {
    
    if(_taskFunction == NULL || _period_ms == 0) {
        return NULL;
    }

    Task* task = (Task*)malloc(sizeof(Task));

    if(task == NULL) {
        return NULL;
    }

    task->m_function = _taskFunction;
    task->m_context = _context;
    task->m_periodTime = _period_ms;
    task->m_clockid = _clockid;
    task->m_magicNumber = MAGIC_NUMBER;
    
    return task;
}

void TaskDestroy(Task* _task) {
    
    if(_task == NULL || _task->m_magicNumber != MAGIC_NUMBER) {
        return;
    }

    _task->m_magicNumber = 0;

    free(_task);

}


size_t TaskRun(Task* _task) {

    if(_task == NULL) {
        return TASK_REMOVE;
    }

    return _task->m_function(_task->m_context);
}

int TaskCompare(void* _task1, void* _task2) {

    Task* task1 = (Task*)_task1;
    Task* task2 = (Task*)_task2;

    if(task1->m_execTime < task2->m_execTime) {
        return 1;
    }

    return 0;
}

int TaskUpdateExecTime(Task* _task) {

    return CalculateExecTime(_task->m_periodTime, &_task->m_execTime, _task->m_clockid);
}

void TaskSleep(Task* _task) {

    CalculateSleep(_task->m_periodTime, _task->m_execTime, _task->m_clockid);
}