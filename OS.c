//
// Created by lucas on 20/07/2021.
//

#define _GNU_SOURCE

#include <sched.h>
#include "OS.h"
#include "Task.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

char run_by_priority = 0; //PRIORITY = stack / TIME = queue
int run = 0;
Task tasks[MAX_TASKS];
char buff[BUFF_LENGTH];

void logAction(Task *tasks, int current, int n);
char *taskGetMem(Mutex *);
void taskReleaseMem(Mutex *);
void logHeaders(OS *os);
void restartScheduler(OS *os);
void taskSetId(Task *task, pid_t _pid);
void initTask(Task *t, int _priority, pthread_t *_thread);

void *MainTask(void *_thread_data) {
    ThreadData *thread_data = (ThreadData *) _thread_data;
    int taskId = thread_data->taskId;
    OS *os = thread_data->os;
    taskSetId(&os->tasks[taskId], gettid());
    int t = taskPrio(&os->tasks[taskId]);
    do {
        if (taskShouldSuspend(os, &os->tasks[taskId]))
            taskSuspend(&os->tasks[taskId]);
        char *ptr = taskGetMem(&os->m);
        printf("Cur Task is %s Last Task is %s\n", taskGetName(&os->tasks[taskId]), ptr);
        SetTaskName(taskGetName(&os->tasks[taskId])); // Set New current task
        taskReleaseMem(&os->m);
        taskWait(&os->tasks[taskId], t); // sleep for t seconds
    } while (run);
}

void sig_handler(int sig) {
    run_by_priority = !run_by_priority;
}


void initOs(OS *os, int _threads, int _cores, int _clock_interval) {
    os->n = _threads;
    os->cores = _cores;
    os->clock_interval = _clock_interval;
    os->tasks = tasks;
    os->q = q;
    MutexInit(&os->m);

    signal(SIGUSR1, sig_handler);
    initThreads(os);
}

void runScheduler(OS *os) {
    logHeaders(os);
    while (run) {
        resetQueue(&os->q);
        restartTasks(os);
        if (run_by_priority) {
            sortByPriority(os);
            pushTasks(os);
            os->active = pop(&os->q);
            __sync_synchronize();
        } else {
            sortByTime(os);
            enqueueTasks(os);
            os->active = dequeue(&os->q);
            __sync_synchronize();
        }
        char is_have_run_by_priority = 0;
        while (run_by_priority) {
            is_have_run_by_priority = 1;
            taskWake(os, os->active);
            logAction(os->tasks, os->active, os->n, &os->q, run_by_priority);
            pid_t prev = os->active;
            os->active = pop(&os->q);
            __sync_synchronize();
            push(&os->q, prev);
            sleep(os->clock_interval);
        }
        while (!is_have_run_by_priority && !run_by_priority) {
            taskWake(os, os->active);
            logAction(os->tasks, os->active, os->n, &os->q, run_by_priority);
            pid_t prev = os->active;
            os->active = dequeue(&os->q);
            __sync_synchronize();
            enqueue(&os->q, prev);
            sleep(os->clock_interval);
        }
    }

    void *val;
    for (int i = 0; i < os->n; i++)
        pthread_join(os->tasks->thread[i], &val);
}


void restartTasks(OS *os) {
    for (int i = 0; i < os->n; i++)
        SemInit(&os->tasks[i].sem, 0);
}

void logHeaders(OS *os) {
    FILE *csv = fopen(LOG_FILENAME, "w");
    fprintf(csv, "# sec,");
    for (int h = 0; h < os->n; h++)
        fprintf(csv, "task %d,", h);
    fprintf(csv, "Q\n");
    fclose(csv);
}

void logAction(Task *tasks, pid_t current, int n, Queue *queue, char run_by_priority) {
    FILE *csv = fopen(LOG_FILENAME, "a");
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(csv, "%d-%02d-%02d %02d:%02d:%02d,", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min,
            tm.tm_sec);
    for (int h = 0; h < n; h++)
        fprintf(csv, taskGetId(&tasks[h]) == current ? "run," : "suspend,");
    if (run_by_priority)
        logByPriority(queue);
    else
        logByTime(queue);
    fclose(csv);
}


void taskWake(OS *os, pid_t pid) {
    for (int i = 0; i < os->n; i++) {
        if (os->tasks[i].pid == pid) {
//            printf("waking up %d\n", os->tasks[i].pid);
            SemInc(&os->tasks[i].sem);
        }
    }
}

void SetTaskName(char *name) {
    strcpy(buff, name);
}


char taskShouldSuspend(OS *os, Task *task) {
    return os->active == task->pid ? 0 : 1;
}


char *taskGetMem(Mutex *m) {
    MutexAcquire(m);
    return buff;
}


void taskReleaseMem(Mutex *m) {
    MutexRelease(m);
}
