#ifndef MINIOS_QUEUE_H
#define MINIOS_QUEUE_H
#include "queue.h"
// Check if the queue is full
int isFull();

// Check if the queue is empty
int isEmpty();
// Adding an element
void enQueue(int element);
// Removing an element
int deQueue();
// Display the queue
void logQueue();
#endif //MINIOS_QUEUE_H
