// Libraries
#include <stdio.h>
#include <stdlib.h>
// miniOS
#include "Task.h"

#define YEL "\x1B[33m"
#define RESET "\x1B[0m"

char name[NAME_MAX_LENGTH];


void initTask(Task *t, int _priority, pthread_t *_thread) {
    t->priority = _priority;
    t->thread = _thread;
    t->pid = -1000;
    MutexInitPos(&t->m);   
}

char *taskGetName(Task *task) {
        snprintf(name, NAME_MAX_LENGTH, YEL "Task %d" RESET, task->pid);
        return name;
}


void taskSetId(Task *task, pid_t _pid) {
    task->pid = _pid;
}

pid_t taskGetId(Task *task) {
    return task->pid;
}

void taskSuspend(Task *task) {
    MutexAcquire(&task->m);
}

void taskWait(int t) {
    sleep(t + 1);
}

int taskPrio(Task *task) {
    return task->priority;
}

