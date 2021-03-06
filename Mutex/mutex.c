//Libraries
#include <stdio.h>

// miniOS
#include "mutex.h"

void MutexInitPos(Mutex *m) {
    m->state = LOCKED;
};

void MutexInit(Mutex *m) {
    m->state = UNLOCKED;
};

void MutexAcquire(Mutex *m) {
    while (!__sync_bool_compare_and_swap(&m->state, UNLOCKED, LOCKED))
        usleep(1000);
};

void MutexRelease(Mutex *m) {
    m->state = UNLOCKED;
    __sync_synchronize();
}
