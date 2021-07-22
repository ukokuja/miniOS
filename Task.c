//
// Created by Lucas Kujawski on 16/07/2021.
//
#include "Task.h"

#include <stdio.h>
#include <stdlib.h>
char* taskGetName (Task* task){
    switch (task->priority) {
        case 0:
            return "task 0";
            break;
        case 1:
            return "task 1";
            break;
        case 2:
            return "task 2";
            break;
        case 3:
            return "task 3";
            break;
        case 4:
            return "task 4";
            break;
        case 5:
            return "task 5";
            break;
        case 6:
            return "task 6";
            break;
        case 7:
            return "task 7";
            break;
        case 8:
            return "task 8";
            break;
        case 9:
            return "task 9";
            break;
    }
}


void taskSetId(Task* task, pid_t _pid) {
    task->pid = _pid;
}
pid_t taskGetId (Task* task){
    return task->pid;
}


void taskSuspend (Task* task){
//    printf("suspending %d \n", task->pid);
    SemDec(&task->sem);
//    printf("woken up %d \n", task->pid);
}

void taskWait (Task* task, int t){
    sleep(t+1);
}


int taskPrio (Task* task){
    return task->priority;
}


void init_task(Task *t, int _priority, pthread_t *_thread) {
    t->time = (int) time(NULL);
    t->priority = _priority;
    t->thread = _thread;
    t->pid = -1000;
//    SemInit(&t->sem, 0);
}