//
// Created by lucas on 20/07/2021.
//

#ifndef MINIOS_OS_H
#define MINIOS_OS_H
#include <pthread.h>
#include <unistd.h>
#include <sys/signal.h>
#include "Task.h"
#include "queue.h"
#include <stdio.h>
#define MAX_TASKS 10
typedef struct OS_struct {
    int n;
    int cores;
    int clock_interval;
    Task *tasks;
    pid_t active;
    Queue q;
} OS;


typedef struct ThreadData {
    OS* os;
    int taskId;
} ThreadData;


void initOs(OS *os, int _threads, int _cores, int _clock_interval);

void runScheduler(OS *os);
void taskWake(OS *os, pid_t pid); // Wake a task by its pid.
char taskShouldSuspend(OS* os, Task* task); // Should the task suspend ?
void SetTaskName(OS *os, char *);  // Set New current task
void log_action(Task *tasks, pid_t current, int n, Queue *queue, char run_by_priority);

#endif //MINIOS_OS_H
