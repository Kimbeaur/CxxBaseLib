#ifndef _SPINMUTEX_H_
#define _SPINMUTEX_H_

#include <atomic>


class SpinMutex
{

public:
    SpinMutex() : flag_(false)
    {
    }

    void lock()
    {
        bool expect = false;
        while (!flag_.compare_exchange_weak(expect, true))
        {
            expect = false;
        }
    }

    void unlock()
    {
        flag_.store(false);
    }

private:
    std::atomic<bool> flag_;
};

#endif