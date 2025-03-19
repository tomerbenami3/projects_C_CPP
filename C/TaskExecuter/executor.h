#include <time.h>
#include "task.h"
#include "../Vectornew/vector.h"

typedef struct PeriodicExecutor PeriodicExecutor;

typedef enum Executor_Result{
    EXECUTOR_SUCCESS = 0,
    EXECUTOR_UNINITILIZED,
    EXECUTOR_TASK_UNINITILIZED,
}ExecutorResult;

PeriodicExecutor* PeriodicExecutor_Create(const char* _name, clockid_t _clk_id);

void PeriodicExecutor_Destroy(PeriodicExecutor* _executor);

int PeriodicExecutor_Add(PeriodicExecutor* _executor, TaskFunction _taskFunction, void* _context, size_t _period_ms);

size_t PeriodicExecutor_Run(PeriodicExecutor* _executor);