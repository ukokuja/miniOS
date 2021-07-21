//
// Created by Lucas Kujawski on 16/07/2021.
//
#include "Task.h"

char* taskGetName (Task* task){
    return "";
//    return "Task #"snprintf(buf, 12, "pre_%d_suff", i);
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

char* taskGetMem (Task* task) {
    char buff[20];
    return "buff";
}

void taskReleaseMem (Task* task){
//    printf("releasing buff\n");
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