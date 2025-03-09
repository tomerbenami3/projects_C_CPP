#include <time.h>


int CalculateExecTime(size_t _periodTime, size_t* _execTime, clock_t _clockid);

void CalculateSleep(size_t _periodTime, size_t _execTime, clock_t _clockid);