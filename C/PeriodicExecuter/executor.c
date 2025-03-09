#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Vectornew/vector.h"
#include "../heap/heap.h"
#include "executor.h"
#include "task.h"

#define TASK_INITIAL_CAPACITY 20
#define TASK_BLOCK_SIZE 10
#define MAGIC_NUMBER 0xDEADBEEF

struct PeriodicExecutor {
    Vector* m_tasks;
    clockid_t m_clockid;
    char* m_name;
    int m_pauseFlag;
    int m_magicNumber;
};

PeriodicExecutor* PeriodicExecutor_Create(const char* _name, clockid_t _clk_id) {

    if(_name == NULL) {
        return NULL;
    }

    PeriodicExecutor* pe = (PeriodicExecutor*)malloc(sizeof(PeriodicExecutor));

    if(pe == NULL) {
        return NULL;
    }
    
    pe->m_tasks = VectorCreate(TASK_INITIAL_CAPACITY, TASK_BLOCK_SIZE);

    if(pe->m_tasks == NULL) {
        free(pe);
        return NULL;
    }

    pe->m_name = (char*)malloc(strlen(_name) * sizeof(char));

    if(pe->m_name == NULL) {
        VectorDestroy(&pe->m_tasks, free);
        free(pe);
        return NULL;
    }

    pe->m_clockid = _clk_id;
    pe->m_magicNumber = MAGIC_NUMBER;

    return pe;
}


void PeriodicExecutor_Destroy(PeriodicExecutor* _executor) {
    
    if(_executor == NULL || _executor->m_magicNumber != MAGIC_NUMBER) {
        return;
    }
    _executor->m_magicNumber = 0;

    VectorDestroy(&_executor->m_tasks, (void*)TaskDestroy);
    free(_executor->m_name);
    free(_executor);

}

int PeriodicExecutor_Add(PeriodicExecutor* _executor, TaskFunction _taskFunction, void* _context, size_t _period_ms) {

    if(_executor == NULL) {
        return EXECUTOR_UNINITILIZED;
    }

    Task* task = TaskCreate((TaskFunction)_taskFunction, _context, _period_ms, _executor->m_clockid);

    if(task == NULL) {
        return EXECUTOR_TASK_UNINITILIZED;
    }

    VectorAppend(_executor->m_tasks, task);
    return EXECUTOR_SUCCESS;
}

size_t PeriodicExecutor_Run(PeriodicExecutor* _executor) {

    if(_executor == NULL) {
        return 0;
    }

    VectorForEach(_executor->m_tasks, (VectorElementAction)TaskUpdateExecTime, NULL);

    Heap* heap = HeapBuild(_executor->m_tasks, (LessThanComparator)TaskCompare);

    Task* task;
    size_t status;
    int taskCounter = 0;

    if(heap == NULL) {
        return 0;
    }

    _executor->m_pauseFlag = 0;

    while(HeapSize(heap) > 0 && _executor->m_pauseFlag == 0) {

        task = (Task*)HeapExtract(heap);
        TaskSleep(task);
        status = TaskRun(task);
        TaskUpdateExecTime(task);
        if(!status) {
            HeapInsert(heap, (void*)task);
        } else {
            TaskDestroy(task);
        }
        
        ++taskCounter;
    }

    return taskCounter;
}

size_t PeriodicExecutor_Pause(PeriodicExecutor* _executor) {

    if(_executor == NULL) {
        return 0;
    }

    _executor->m_pauseFlag = 1;

    return VectorSize(_executor->m_tasks);
}