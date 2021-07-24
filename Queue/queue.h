#ifndef MINIOS_QUEUE_H
#define MINIOS_QUEUE_H
#include "../Config/environment_variables.h"

/**
 * Struct for Queue, that describe data stract for tasks that can be sorted by 2 ways.
 * @details one way to sort (and default one) is task's priority and seconed is random.
 * @param {Array<int>} items, array of tasks PID, all are locks except the pop one.
 * @param {int} front,  Mutex for locking.
 * @param {int} rear, the currrent thread that running in the task.
 */
typedef struct Queue_Struct
{
    int items[MAX_TASKS];
    int front;
    int rear;
} Queue;

int items[MAX_TASKS];
int front = -1, rear = -1;

/**
 * Check if the queue is full
 */
int isFull();

/**
 * Check if the queue is empty
 */
int isEmpty();

/**
 * Adding an element
 * @param {int} element, the value
 */
void enQueue(int element);

/**
 * Removing an element
 */
int deQueue();

/**
 * Display the queue in CSV file
 */
void logQueue();

#endif //MINIOS_QUEUE_H
