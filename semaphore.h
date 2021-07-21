//
// Created by lucas on 20/07/2021.
//

#ifndef MINIOS_SEMAPHORE_H
#define MINIOS_SEMAPHORE_H
#include "mutex.h"
typedef struct SemaphoreStruct{
    int val;
    Mutex mutex;
} Semaphore;

void SemInit(Semaphore* cs, int _val);
void SemDec(Semaphore* cs);
void SemInc(Semaphore* cs);

#endif //MINIOS_SEMAPHORE_H
