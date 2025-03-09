#include <stdlib.h>
#include <stdio.h>
#define _POSIX_C_SOURCE 200809L
#include <time.h>
#include "executor.h"

int PrintTask1(void* _context) {

    static int count = 0;

    printf("Task 1\n");
    ++count;

    return count == 3 ? 1 : 0;
}

int PrintTask2(void* _context) {

    static int count = 0;

    printf("Task 2\n");
    ++count;

    return count == 3 ? 1 : 0;
}

int PrintTask3(void* _context) {

    static int count = 0;

    printf("Task 3\n");
    ++count;

    return count == 3 ? 1 : 0;
}

int main() {

    clock_t clk = CLOCK_REALTIME;


    PeriodicExecutor* exec = PeriodicExecutor_Create("Tomer", clk);
    PeriodicExecutor_Add(exec, PrintTask1, NULL, 5000);
    PeriodicExecutor_Add(exec, PrintTask2, NULL, 1000);
    PeriodicExecutor_Add(exec, PrintTask3, NULL, 3000);
    PeriodicExecutor_Run(exec);
    PeriodicExecutor_Destroy(exec);


    return 0;
}
