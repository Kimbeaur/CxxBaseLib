
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IPC_IMPLEMENTATION
#include "ipc.h"

#if defined(_WIN32)
int myprocessid()
{
    return GetCurrentProcessId();
}
#else
#include <unistd.h>
int myprocessid()
{
    return getpid();
}
#endif

#define WORKUNITS 1024
#define WORKUNITSIZE (64*64)
#define TOTALSIZE WORKUNITS+WORKUNITS*WORKUNITSIZE+1

ipc_sharedsemaphore coop;
ipc_sharedmemory mem;
int pid;

int busywork(int seed)
{
    double xx, yy, x0, y0, s;
    int n;
    xx = (seed % WORKUNITSIZE) / (double)WORKUNITSIZE;
    yy = (seed / WORKUNITSIZE) / (double)WORKUNITSIZE;
    x0 = xx;
    y0 = yy;
    n = 1;
    do
    {
        double x1, y1;
        n++;
        x1 = x0 * x0;
        y1 = y0 * y0;
        y0 = (x0 * y0) * 2 + yy;
        x0 = x1 - y1 + xx;
        s = x1 + y1;
    } while ((s < 4) && (n < 1000));
    return n;
}

int main(int parc, char **pars)
{
    int done = 0;
    int first = 0;

    pid = myprocessid();

    printf("%08x: Starting\n", pid);

    ipc_sem_init(&coop, "ipc_test_semaphore");
    ipc_mem_init(&mem, "ipc_test_memory", TOTALSIZE);

    if (ipc_sem_create(&coop, 1))
    {
        printf("%08x: ipc_sem_create failed\n", pid);
        return -1;
    }

    // Grab semaphore
    ipc_sem_decrement(&coop);

    if (ipc_mem_open_existing(&mem))
    {
        printf("%08x: Opening existing memory failed, maybe we're first?\n", pid);
        if (ipc_mem_create(&mem))
        {
            printf("%08x: Creating memory failed.\n", pid);
            return -1;
        }
        printf("%08x: Seems we're the first. Initializing work memory.\n", pid);
        memset(mem.data, 0, mem.size);
        first = 1;
    }
    else
    {
        printf("%08x: We're not the first.\n", pid);
    }

    // let's clock in
    mem.data[0]++;

    // release semaphore before the main loop
    ipc_sem_increment(&coop);

    while (!done)
    {
        int i, work = -1;

        // Grab semaphore
        ipc_sem_decrement(&coop);
        printf("%08x: Looking for work.\n", pid);
        for (i = 0; work == -1 && i < WORKUNITS; i++)
        {
            if (mem.data[i + 1] == 0)
            {
                printf("%08x: Taking work unit %d.\n", pid, i);
                mem.data[i + 1] += 1;
                work = i;
            }
        }
        // Let someone else work
        ipc_sem_increment(&coop);
        if (work != -1)
        {
            // do "work"
            for (i = 0; i < WORKUNITSIZE; i++)
                mem.data[WORKUNITS + work * WORKUNITSIZE + i + 1] += busywork(work * WORKUNITSIZE + i);
        }
        else
        {
            printf("%08x: No work found, I guess we're done.\n", pid);
            done = 1;
        }
    }

    // Grab semaphore
    ipc_sem_decrement(&coop);

    // clock out
    mem.data[0]--;

    // Let someone else work
    ipc_sem_increment(&coop);

    if (first)
    {
        FILE *f;
        printf("%08x: Since we're the first, let's dump the work memory for diagnostics purposes\n", pid);
        if (mem.data[0] > 0)
        {
            printf("%08x: oops, someone else is still working..\n", pid);
            while (mem.data[0] > 0)
            {
                busywork(0xc0cac01a);
            }
            printf("%08x: they're done now I guess.\n", pid);
        }
        f = fopen("dump.dat", "wb");
        fwrite(mem.data, 1, mem.size, f);
        fclose(f);
        printf("%08x: dump.dat written.\n", pid);
    }

    ipc_mem_close(&mem);
    ipc_sem_close(&coop);

    printf("%08x: Done.\n", pid);
    return 0;
}