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
char run_by_priority = 1; //PRIORITY = stack / TIME = queue
int run = 0;
Task tasks[MAX_TASKS];
Queue q;
int array[MAX_TASKS];

void *MainTask(void *_thread_data) {
    ThreadData *thread_data = (ThreadData *) _thread_data;
    int taskId = thread_data->taskId;
    OS* os = thread_data->os;
    taskSetId(&os->tasks[taskId], gettid());
    int t = taskPrio(&os->tasks[taskId]);
    do {
        if (taskShouldSuspend(os, &os->tasks[taskId]))
            taskSuspend(&os->tasks[taskId]);
        printf("executing: task %d with priority %d=%d\n", os->tasks[taskId].pid, os->tasks[taskId].priority, t);
        char *ptr = taskGetMem(&os->tasks[taskId]);
//        printf("Cur Task is %s Last Task is %s\n", taskGetName(task), ptr);
//        SetTaskName(&os, taskGetName(&thread)); // Set New current task
        taskReleaseMem(&os->tasks[taskId]);
        taskWait(&os->tasks[taskId], t); // sleep for t seconds
    } while (1);
}

void sig_handler(int sig) {
    run_by_priority = !run_by_priority;
}


void init_os(OS *os, int _n, int _cores, int _clock_interval) {
    os->n = _n;
    os->cores = _cores;
    os->clock_interval = _clock_interval;
    os->tasks = tasks;
    os->q = q;
    initQueue(&os->q, array, os->n);
    signal(SIGUSR1, sig_handler);
    for (int i = 0; i < os->n; i++) {
        pthread_t t;
        init_task(&tasks[i], i, &t);
        os->tasks[i] = tasks[i];
        pthread_attr_t at;
        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);
        CPU_SET(i % os->cores, &cpuset);
        pthread_attr_init(&at);
        pthread_attr_setaffinity_np(&at, sizeof(cpuset), &cpuset);
        ThreadData thread_data;
        thread_data.os = os;
        thread_data.taskId = i;
        if (pthread_create(&t, &at, MainTask, (void *) &thread_data)) {
            perror("pthread create 1 error\n");
        }
    }
    sleep(1);
    run = 1;
}

void run_scheduler(OS *os) {
    FILE* csv = fopen("log_action.csv","w");
    fprintf(csv, "# sec,");
    for (int h = 0; h < os->n; h++)
        fprintf(csv, "task %d,", h);
    fprintf(csv, "Q\n");
    fclose(csv);
    while (run) {
        while (!isEmpty(&os->q))
            dequeue(&os->q);
        if (run_by_priority) {
            for (int h = 0; h < os->n; h++)
                push(&os->q, taskGetId(&os->tasks[h])); // TBD: order by priority
            os->active = pop(&os->q);
            __sync_synchronize();
        } else {
            for (int h = 0; h < os->n; h++)
                enqueue(&os->q, taskGetId(&os->tasks[h]));
            os->active = dequeue(&os->q);
            __sync_synchronize();
        }
        while (run_by_priority) {
            taskWake(os, os->active);
            log_action(os->tasks, os->active, os->n, &os->q, run_by_priority);
            pid_t prev = os->active;
            os->active = pop(&os->q);
            __sync_synchronize();
            push(&os->q, prev);
            sleep(os->clock_interval);
        }
        while (!run_by_priority) {
            taskWake(os, os->active);
            log_action(os->tasks, os->active, os->n, &os->q, run_by_priority);
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

void log_action(Task *tasks, pid_t current, int n, Queue* queue, char run_by_priority) {
    FILE* csv = fopen("log_action.csv","a");
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(csv, "%d-%02d-%02d %02d:%02d:%02d,", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    for (int h = 0; h < n; h++)
        fprintf(csv, taskGetId(&tasks[h]) == current ? "run," : "suspend,");
    if (run_by_priority)
        log_by_priority(queue);
    else
        log_by_time(queue);
    fclose(csv);
}


void taskWake(OS *os, pid_t pid) {
    for (int i = 0; i < os->n; i++) {
        if (os->tasks[i].pid == pid)
            printf("waking up %d\n", os->tasks[i].pid);
            SemInc(&os->tasks[i].sem);
    }
}

void SetTaskName(OS *os, char *name) {

}


char taskShouldSuspend (OS* os, Task* task){
    return os->active == task->pid ? 0 : 1;
}
