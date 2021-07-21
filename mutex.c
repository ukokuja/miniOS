//
// Created by lucas on 20/07/2021.
//

#include "mutex.h"
void MutexInitPos(Mutex* m) {
    m->state=1;
};

void MutexInit(Mutex* m) {
    m->state=0;
};

void MutexAcquire(Mutex* m) {
    while (!__sync_bool_compare_and_swap(&m->state, 0, 1))
        usleep(1);
};

void MutexRelease(Mutex* m) {
    m->state = 0;
    __sync_synchronize();
}