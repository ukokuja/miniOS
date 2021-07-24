//
// Created by lucas on 20/07/2021.
//

#ifndef MINIOS_TASK_H
#define MINIOS_TASK_H

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "../Config/environment_variables.h"
#include "../Mutex/mutex.h"

/**
 * Struct for task, that describe single process with priority/
 * @param {int} priority, Any new thread created has a unique priority.
 * @param {Mutex} m,  Mutex for locking.
 * @param {pthread_t}* thread, the currrent thread that running in the task.
 * @param {pid_t} pid, process id number.
 */
typedef struct task_struct
{
    int priority;
    Mutex m;
    pthread_t *thread;
    pid_t pid;
} Task;

/**
 * Constructor for Task
 * @param {Task}* t, the current task.
 * @param {int}* _priority, unique.
 * @param {pthread_t}* _thread, the task's thread.
 */
void initTask(Task *t, int _priority, pthread_t *_thread);

/**
 * Setter for the id of the task
 * @param {Task}* t, the current task.
 * @param {pid_t} _pid, new process id.
 */
void taskSetId(Task *task, pid_t _pid);


/**
 * Returns a unique ascii name of the thread.
 * @details It is less than 19 bytes long.
 * @param {Task}* task, the current task.
 */
char *taskGetName(Task *task);

/**
 * Returns a unique id
 * @param {Task}* task, the current task.
 */
pid_t taskGetId(Task *task);

/**
 * Suspends a task until released
 * @param {Task}* task, the current task.
 */
void taskSuspend(Task *task);

/**
 * Suspends a task for n seconds.
 * @param {int} t, the n scondes for delay the schedular.
 */
void taskWait(int t);

/**
 *  Return the priority of the task
 * @param {Task}* task, the current task.
 */
int taskPrio(Task *task);

#endif //MINIOS_TASK_H
