//
// Created by Lucas Kujawski on 16/07/2021.
//
#include "Task.h"

#include <stdio.h>
#include <stdlib.h>
// miniOS
#include "Task.h"

char name[NAME_MAX_LENGTH];


char *taskGetName(Task *task) {
        snprintf(name, NAME_MAX_LENGTH, "Task %d", task->priority);
        return name;
}


void taskSetId(Task *task, pid_t _pid) {
    task->pid = _pid;
}

pid_t taskGetId(Task *task) {
    return task->pid;
}

void taskSuspend (Task* task){
//    printf("suspending %d \n", task->pid);
    SemDec(&task->sem);
//    printf("woken up %d \n", task->pid);
}

void taskWait(int t) {
    sleep(t + 1);
}

int taskPrio(Task *task) {
    return task->priority;
}

void initTask(Task *t, int _priority, pthread_t *_thread) {
    t->priority = _priority;
    t->thread = _thread;
    t->pid = -1000;
    MutexInitPos(&t->m);
}