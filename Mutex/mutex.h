#ifndef MINIOS_MUTEX_H
#define MINIOS_MUTEX_H

#include <unistd.h>
#include <stdbool.h>
enum {LOCKED, UNLOCKED};

/**
 * Struct for locking, create the situatuin that only 1 thread can be active
 * @param {char} state Mutex state of locking.
 */
typedef struct MutexStruct {
    bool state;
} Mutex;

/**
 * Constructor of Mutex, initilize to locked
 * @param {Mutex} *mutex Mutex.
 */
void MutexInitPos(Mutex *m);

/**
 * Constructor of Mutex, initilize to unlocked
 * @param {Mutex} *mutex Mutex.
 */
void MutexInit(Mutex *m);

/**
 * Acquire mutex
 * @param {Mutex} *mutex Mutex.
 */
void MutexAcquire(Mutex *m);


/**
 * Release mutex
 * @param {Mutex} *mutex Mutex.
 */
void MutexRelease(Mutex *m);

#endif //MINIOS_MUTEX_H


