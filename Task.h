//
// Created by lucas on 20/07/2021.
//

#ifndef MINIOS_TASK_H
#define MINIOS_TASK_H

#include <time.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "semaphore.h"

typedef struct task_struct {
    int time;
    int priority;
    Semaphore sem;
    pthread_t *thread;
    pid_t pid;
} Task;

void init_task(Task *t, int _priority, pthread_t *_thread);

char* taskGetName(Task *task); //Returns a unique ascii name of the thread. It is less than 19 bytes long.
pid_t taskGetId(Task *task); // Returns a unique id
void taskSuspend(Task *task); // Suspends a task until released
void taskWait(Task *task, int t); // Suspends a task for n seconds.
int taskPrio(Task *task); // Return the priority of the task
void taskSetId(Task* task, pid_t _pid);
#endif //MINIOS_TASK_H
