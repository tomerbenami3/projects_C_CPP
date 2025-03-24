#ifndef EXECUTOR_TIME_H
#define EXECUTOR_TIME_H

#include <ctime>

namespace executor {

class Time
{
public:
    Time();
    Time(time_t sec, long n_sec);
    Time(timespec const& other);
    ~Time();
    Time& operator=(Time const& other);

    time_t get_sec();
    long get_nsec();

    bool operator==(Time const& other);
    bool operator!=(Time const& other);
    bool operator<(Time const& other);
    bool operator>(Time const& other) const;
    bool operator>=(Time const& other);
    bool operator<=(Time const& other);
    Time& operator+=(Time const& other);
    Time& operator-=(Time const& other);
    Time operator+(Time const& other);
    Time operator-(Time const& other);

    void normalize();
    
private:
    struct timespec m_time;
    
};

}


#endif // EXECUTOR_TIME_SPEC_H