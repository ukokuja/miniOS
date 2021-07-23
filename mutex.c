//Libraries
#include <stdio.h>
#include <unistd.h>

// miniOS
#include "mutex.h"

void MutexInitPos(Mutex *m) {
    m->state = 1;
};

void MutexInit(Mutex *m) {
    m->state = 0;
};

void MutexAcquire(Mutex *m) {
    while (!__sync_bool_compare_and_swap(&m->state, 0, 1))
        usleep(1000);
};

void MutexRelease(Mutex *m) {
    m->state = 0;
    __sync_synchronize();
}