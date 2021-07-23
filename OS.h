#ifndef MINIOS_OS_H
#define MINIOS_OS_H

#include "Task.h"

typedef struct OS_struct {
    int n;
    int cores;
    int clock_interval;
    Task *tasks;
    pid_t active;
    Mutex m;
} OS;


typedef struct ThreadData {
    OS *os;
    int taskId;
} ThreadData;


void initOs(OS *os, int _threads, int _cores, int _clock_interval);
void runScheduler(OS *os);
//API
void taskWake(OS *os, pid_t id);
char taskShouldSuspend(OS *os, Task *task);
void taskSetName(char *);

#endif //MINIOS_OS_H
