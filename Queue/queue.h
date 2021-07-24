#ifndef MINIOS_QUEUE_H
#define MINIOS_QUEUE_H
#include "../Config/environment_variables.h"

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
