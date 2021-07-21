//
// Created by lucas on 20/07/2021.
//

#ifndef MINIOS_MUTEX_H
#define MINIOS_MUTEX_H


#include <stdio.h>

typedef struct MutexStruct {
    char state;
} Mutex;


void MutexInitPos(Mutex* m);
void MutexInit(Mutex* m);
void MutexAcquire(Mutex* m);
void MutexRelease(Mutex* m);

#endif //MINIOS_MUTEX_H
