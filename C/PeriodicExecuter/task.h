#include <stddef.h>
#include <time.h>
#define TASK_REMOVE 3


typedef struct Task Task;
typedef int (*TaskFunction)(void *_context);

Task* TaskCreate(TaskFunction _taskFunction, void* _context, size_t _period_ms, clock_t _clockid);

void TaskDestroy(Task* _task);

size_t TaskRun(Task* _task);

int TaskUpdateExecTime(Task* _task);

int TaskCompare(void* _task1, void* _task2);

void TaskSleep(Task* _task);