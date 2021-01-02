#include <stdio.h>
#include <string.h>
#include <string>
#include <unistd.h> //usleep
#include <pthread.h>
#include "SkipList.h"
#include "crc.h"
#include "SkipListTimer.h"
#include "debug.h"
#include "Log.h"
// test timer
void print_hello(zskiplistNode *zn) {
    printf("hello world time = %lu\n", zn->score);
}

void print_hello1(zskiplistNode *zn) {
    printf("hello world1 time = %lu\n", zn->score);
}

void print_hello2(zskiplistNode *zn) {
    printf("hello world2 time = %lu\n", zn->score);
}

void testTimer(void)
{

     printf("----------- test timer %s() ------------\n",__func__);
    zskiplist *zsl = init_timer();
    add_timer(zsl, 3010, print_hello);
    add_timer(zsl, 6000, print_hello1);
    add_timer(zsl, 9000, print_hello2);
    //zskiplistNode *zn = add_timer(zsl, 3005, print_hello);
    //del_timer(zsl, zn);
    //add_timer(zsl, 3008, print_hello);
    //add_timer(zsl, 3003, print_hello);
    zslPrint(zsl);

      for (;;) {
        expire_timer(zsl);
        usleep(10000);
    }
}

void testCrc(void)
{
    printf("----------- test crc %s() ------------\n",__func__);
    int crc = 0;
    const char* buf = "voice from hell....";
    crc = crc32((unsigned char *)buf, strlen(buf));
    printf("crc: 0x%x\n", crc);
    dump(buf, strlen(buf));
    
}


pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

struct tlog_log *logs = NULL;

void *test(void *arg)
{
    int id = (intptr_t)arg;
    int i = 0;

    for (i = 0; i < 100000; i++) {
        tlog(TLOG_ERROR, "%d i = %d\n", id, i);
    }
    return NULL;
}

void *test1(void *arg)
{
    int *id = (int*)(arg);
    int i = 0;

    for (i = 0; i < 100000; i++) {
        tlog_printf(logs, " %d i = %d\n", id, i);
    }
    return NULL;
}

void testLog(void)
{
    tlog_init("log/test.log", 1024 * 1024 * 32, 10, 1, 0, 1);
    logs = tlog_open("log/test1.log", 1024 * 1024 * 32, 10, 1, 0, 1);
    pthread_attr_t attr;
    pthread_t threads[10];
    pthread_t threads1[10];
    int i;
    int ret;

    pthread_attr_init(&attr);
    for (i = 0; i < 10; i++) {
        ret = pthread_create(&threads[i], &attr, test, (void *)(intptr_t)i);
        if (ret != 0) {
            return ;
        }
    }

    for (i = 0; i < 10; i++) {
        ret = pthread_create(&threads1[i], &attr, test1, (void *)(intptr_t)i);
        if (ret != 0) {
            return ;
        }
    }

    for (i = 0; i < 10; i++) {
        void *retval = NULL;
        pthread_join(threads1[i], &retval);
    }

    for (i = 0; i < 10; i++) {
        void *retval = NULL;
        pthread_join(threads[i], &retval);
    }

    tlog_close(logs);
    tlog_exit();
}



int main(void)
{
    //测试crc模块
    testCrc();

    //测试定时器模块
    //testTimer();

    //测试日记
    testLog();
 
    return 0;
}