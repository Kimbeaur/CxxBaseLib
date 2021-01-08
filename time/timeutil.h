#ifndef _TIME_UTIL_
#define _TIME_UTIL_
#include <sys/time.h>
#include <string.h>

#include <string>

static uint64_t get_time_ms()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

static uint64_t get_time_us()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

static std::string get_time_str_s(time_t time)
{
    struct tm tm_time;
    localtime_r(&time, &tm_time);
    char buf[64];
    snprintf(buf, sizeof(buf), "%4d-%02d-%02d %02d:%02d:%02d", 
             tm_time.tm_year + 1900,
             tm_time.tm_mon + 1,
             tm_time.tm_mday,
             tm_time.tm_hour,
             tm_time.tm_min,
             tm_time.tm_sec);

    return buf;
} 

static std::string get_time_day(time_t time)
{
    struct tm tm_time;
    localtime_r(&time, &tm_time);
    char buf[64];
    snprintf(buf, 64, "%4d-%02d",
             tm_time.tm_year + 1900,
             tm_time.tm_mon + 1);

    return buf;
}

static std::string get_time_str_s()
{
    return get_time_str_s(time(NULL));
}

static std::string get_time_str_ms(struct timeval& tv)
{
    struct tm tm_time;
    localtime_r(&tv.tv_sec, &tm_time);
    char buf[64];
    snprintf(buf, sizeof(buf), "%4d-%02d-%02d %02d:%02d:%02d.%03d", 
             tm_time.tm_year + 1900,
             tm_time.tm_mon + 1,
             tm_time.tm_mday,
             tm_time.tm_hour,
             tm_time.tm_min,
             tm_time.tm_sec,
             tv.tv_usec/1000);

    return buf;
}

static std::string get_time_str_ms()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    return get_time_str_ms(tv);
}


#endif 