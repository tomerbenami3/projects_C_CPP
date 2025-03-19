#include "time_spec.hpp"
#include <ctime>

namespace executor {

Time::Time()
: m_time{0, 0}
{
}

Time::Time(time_t sec, long n_sec)
: m_time{sec, n_sec}
{
    normalize();
}

Time::Time(timespec const& other)
: m_time(other)
{
    normalize();
}

Time::~Time()
{
}

void Time::normalize()
{
        while(m_time.tv_nsec >= 1000000000) {
            ++m_time.tv_sec;
            m_time.tv_nsec -= 1000000000;
        }
        while(m_time.tv_nsec < 0) {
            --m_time.tv_sec;
            m_time.tv_nsec += 1000000000;
        }
}

Time& Time::operator=(Time const& other)
{
    m_time.tv_sec = other.m_time.tv_sec;
    m_time.tv_nsec = other.m_time.tv_nsec;

    return *this;
}

bool Time::operator==(Time const& other)
{
    return m_time.tv_nsec == other.m_time.tv_nsec && m_time.tv_sec == other.m_time.tv_sec;
}

bool Time::operator!=(Time const& other)
{
    return !(*this == other);
}

bool Time::operator<(Time const& other)
{
    if(m_time.tv_sec < other.m_time.tv_sec) {
        return true;
    }
    if((m_time.tv_sec == other.m_time.tv_sec) && m_time.tv_nsec < other.m_time.tv_nsec) {
        return true;
    }
    return false;
}

bool Time::operator>(Time const& other) const
{
    if(m_time.tv_sec > other.m_time.tv_sec) {
        return true;
    }
    if((m_time.tv_sec == other.m_time.tv_sec) && m_time.tv_nsec > other.m_time.tv_nsec) {
        return true;
    }
    return false;
}

bool Time::operator<=(Time const& other)
{
 return !(*this > other);
}

bool Time::operator>=(Time const& other)
{
 return !(*this < other);
}

Time& Time::operator+=(Time const& other)
{
    m_time.tv_sec += other.m_time.tv_sec;
    m_time.tv_nsec += other.m_time.tv_nsec;
    normalize();

    return *this;
}

Time& Time::operator-=(Time const& other)
{
    m_time.tv_sec -= other.m_time.tv_sec;
    m_time.tv_nsec -= other.m_time.tv_nsec;
    normalize();

    return *this;
}

Time Time::operator+(Time const& other)
{
    return Time(m_time.tv_sec + other.m_time.tv_sec, m_time.tv_nsec + other.m_time.tv_nsec);
}

Time Time::operator-(Time const& other)
{
    return Time(m_time.tv_sec - other.m_time.tv_sec, m_time.tv_nsec - other.m_time.tv_nsec);
}

time_t Time::get_sec() 
{
        return m_time.tv_sec;
}

time_t Time::get_nsec()
{
        return m_time.tv_nsec;
}

}