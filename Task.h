//
// Created by lucas on 20/07/2021.
//

#ifndef MINIOS_TASK_H
#define MINIOS_TASK_H

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "environment_variables.h"
#include "mutex.h"

typedef struct task_struct {
    int priority;
    Mutex m;
    pthread_t *thread;
    pid_t pid;
} Task;

// API
/**
 * Returns a unique ascii name of the thread. It is less than 19 bytes long.
 */
char *taskGetName(Task *task);

/**
 * Returns a unique id
 */
pid_t taskGetId(Task *task);
/**
 * Suspends a task until released
 */
void taskSuspend(Task *task);

/**
 * Suspends a task for n seconds.
 */
void taskWait(int t);

/**
 * Return the priority of the task
 */
int taskPrio(Task *task);

#endif //MINIOS_TASK_H
