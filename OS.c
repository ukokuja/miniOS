#define _GNU_SOURCE
// Libraries
#include <sched.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/signal.h>
#include "environment_variables.h"
// miniOS
#include "OS.h"
#include "queue.h"


char interrupt = 0;
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
        taskSetName(taskGetName(&os->tasks[taskId])); // Set New current task
        taskReleaseMem(&os->m);
        taskWait(t);
    } while (1);
    return NULL;
}

void sig_handler() {
    interrupt = 1;
}

void initThreads(OS *os) {
    int i;
    for (i = 0; i < os->n; i++) {
        pthread_t t;
        initTask(&tasks[i], i, &t);
        os->tasks[i] = tasks[i];
        pthread_attr_t at;
        cpu_set_t cpu_set;
        CPU_ZERO(&cpu_set);
        CPU_SET(i % os->cores, &cpu_set);
        pthread_attr_init(&at);
        pthread_attr_setaffinity_np(&at, sizeof(cpu_set), &cpu_set);
        ThreadData thread_data = {os, i};
        if (pthread_create(&t, &at, MainTask, (void *) &thread_data)) {
            perror("pthread create 1 error\n");
        }
        sleep(1);
    }
    sleep(1);
    run = 1;

}


void initOs(OS *os, int _threads, int _cores, int _clock_interval) {

    os->n = _threads;
    os->cores = _cores;
    os->clock_interval = _clock_interval;
    os->tasks = tasks;
    MutexInit(&os->m);

    signal(SIGUSR1, sig_handler);
    initThreads(os);
}



void runScheduler(OS *os) {
    logHeaders(os);
    restartScheduler(os);
    os->active = deQueue();
    while (run) {
        taskWake(os, os->active);
        logAction(os->tasks, os->active, os->n);
        int prev = os->active;
        os->active = deQueue();
        __sync_synchronize();
        enQueue(prev);
        if (interrupt) {
            restartScheduler(os);
            os->active = deQueue();
        }
        sleep(os->clock_interval);
    }

    void *val;
    for (int i = 0; i < os->n; i++)
        pthread_join(*os->tasks[i].thread, &val);
}


void restartScheduler(OS *os) {
    for (int i = 0; i < os->n; i++) {
        MutexInitPos(&os->tasks[i].m);
        deQueue();
    }
    if (!interrupt) {
        for (int i = os->n - 1; i >=0; i--) {
            for (int j = 0; j < os->n; j++) {
                if (taskPrio(&os->tasks[j]) == i) {
                    enQueue(taskGetId(&os->tasks[j]));
                }
            }
        }
    } else {
        for (int i = 0; i < os->n; i++) {
            enQueue(taskGetId(&os->tasks[(i+1)%os->n]));
        }
    }
    interrupt = 0;
}



void taskWake(OS *os, pid_t pid) {
    for (int i = 0; i < os->n; i++) {
        if (os->tasks[i].pid == pid) {
            MutexRelease(&os->tasks[i].m);
        }
    }
}

void taskSetName(char *name) {
    strcpy(buff, name);
}


char taskShouldSuspend(OS *os, Task *task) {
    return os->active != task->pid;
}


char *taskGetMem(Mutex *m) {
    MutexAcquire(m);
    return buff;
}


void taskReleaseMem(Mutex *m) {
    MutexRelease(m);
}


void logHeaders(OS *os) {
    FILE *csv = fopen(LOG_FILENAME, "w");
    fprintf(csv, "interrupt, # sec,");
    for (int h = 0; h < os->n; h++)
        fprintf(csv, "task %d,", h);
    fprintf(csv, "Q\n");
    fclose(csv);
}

void logAction(Task *_tasks, int current, int n) {
    FILE *csv = fopen(LOG_FILENAME, "a");
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(csv, "%c,", interrupt == 0 ? '0' : '1');
    fprintf(csv, "%d-%02d-%02d %02d:%02d:%02d,", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min,
            tm.tm_sec);
    for (int h = 0; h < n; h++)
        fprintf(csv, taskGetId(&_tasks[h]) == current ? "run," : "suspend,");
    fclose(csv);
    logQueue();
}
