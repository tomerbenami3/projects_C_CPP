#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include "calctime.h"
#define REAL_TIME_MS currentTime.tv_nsec
#define REAL_TIME_S currentTime.tv_sec * 1000000000

int CalculateExecTime(size_t _periodTime, size_t* _execTime, clock_t _clockid) {

    struct timespec currentTime;
    clock_gettime(_clockid, &currentTime);
    
    *_execTime = (((REAL_TIME_MS + REAL_TIME_S) / 1000000) + _periodTime);
    // 
    // printf("Execution: %lu, \n", *_execTime);
    printf("CurrentTime: %lu, \n", ((REAL_TIME_MS + REAL_TIME_S) / 1000000));

    return 1;

}

void CalculateSleep(size_t _periodTime, size_t _execTime, clock_t _clockid) {

    struct timespec currentTime;
    clock_gettime(_clockid, &currentTime);
    size_t timetoWait = ((REAL_TIME_MS + REAL_TIME_S) / 1000000);

    if( _execTime < timetoWait) {
        return;
    }
    usleep((_execTime - timetoWait) * 1000);
}