//
// Created by lucas on 20/07/2021.
//

#include "semaphore.h"

void SemInit(Semaphore* cs, int _val){
    cs->val = _val;
    MutexInit(&cs->mutex);
}

void SemDec(Semaphore* cs){
    MutexAcquire(&cs->mutex);
    __sync_synchronize();
    cs->val--;
    __sync_synchronize();
    while (cs->val < 0) {
        usleep(1000);
    }
    MutexRelease(&cs->mutex);
}

void SemInc(Semaphore* cs){
    cs->val++;
    __sync_synchronize();
}