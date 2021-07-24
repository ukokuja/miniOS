#ifndef MINIOS_OS_H
#define MINIOS_OS_H
#include "../Task/Task.h"

/**
 * Struct for OS, that schedueling tasks and threads.
 * @details creating mini os system.
 * @param {int} n, number of threads.
 * @param {int} cores,  number of cores.
 * @param {int} clock_interval,  number of secondes for chedualing.
 * @param {Task}* tasks, the tasks queue.
 * @param {pid_t}* active, the task that active at the current moment.
 * @param {Mutex} m, locking the current task.
 */
typedef struct OS_struct
{
    int n;
    int cores;
    int clock_interval;
    Task *tasks;
    pid_t active;
    Mutex m;
} OS;

/**
 * DTO For tranfer the os data into the task main function.
 * @param {OS}* os, .
 * @param {int} taskId,  .
 */
typedef struct ThreadData
{
    OS *os;
    int taskId;
} ThreadData;

/**
 * Constructor for mini OS
 * @param {OS}* os, the current os of the program .
 * @param {int} _threads, number of threads.
 * @param {int} _cores, number of cores.
 * @param {int} _clock_interval, number of secondes for schedualer.
 */
void initOs(OS *os, int _threads, int _cores, int _clock_interval);

/**
 * start the scheduler thar run ensless.
 * @param {OS}* os, the current os of the program .
 */
void runScheduler(OS *os);

/**
 * run spetcific test from the queue test, and return it to the queue by his sort.
 * @param {OS}* os, the current os of the program .
 */
void taskWake(OS *os, pid_t id);

/**
 * run spetcific test from the queue test, and return it to the queue by his sort.
 * @param {OS}* os, the current os of the program .
 */
char taskShouldSuspend(OS *os, Task *task);

/**
 * update the shared buffer with the last task.
 * @details in Critical Section.
 * @param {char *} pointer to string.
 */
void taskSetName(char *);



#endif //MINIOS_OS_H
