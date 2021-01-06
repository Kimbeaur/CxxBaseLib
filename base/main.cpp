#include <iostream>
#include "thread/workqueue.h"
#include "timer/timer.h"
#include <unistd.h>
using namespace std;

int main()
{
    LTimer t;
    t.startTimer();
    ::usleep(1000000);

    uint64_t tes = t.setTimer(
        20, [] {
            static int a = 0;
            a++;
            cout << "1 ==" << a << endl;
        },10);
#if 0
    t.setTimer(1000, [] {
        static int a = 0;
        a++;
        cout << "222 ==" << a << endl;
    });

    t.setTimer(
        300, [] {
            static int a = 0;
            a++;
            cout << "33333 ==" << a << endl;
        },
        120);

    t.setTimer(700, [] {
        static int a = 0;
        a++;
        cout << "4444444 ==" << a << endl;
    });

    t.setTimer(1500, [] {
        static int a = 0;
        a++;
        cout << "6666666666666 ==" << a << endl;
    });

    t.setTimer(30000, [] {
        static int a = 0;
        a++;
        cout << "88888888888888888888888 ==" << a << endl;
    });
    std::cout << "yyyyyyyyy" << std::endl;
#endif
    int a = 0;
    ::usleep(30000000);
    t.removeTimer(tes);
    while (1)
    {
        ::usleep(3000000);
        a++;
        cout << "asd" << endl;
    }

    return 0;
}
