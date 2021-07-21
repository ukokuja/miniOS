//
// Created by lucas on 20/07/2021.
//

#ifndef MINIOS_QUEUE_H
#define MINIOS_QUEUE_H
typedef struct QueueStruct {
    int front, rear, size;
    unsigned capacity;
    int* array;
} Queue;

// function to create a queue
// of given capacity.
// It initializes size of queue as 0
void initQueue(Queue* q, int* array, unsigned capacity);

// Queue is full when size becomes
// equal to the capacity
int isFull(Queue* queue);

// Queue is empty when size is 0
int isEmpty(Queue* queue);

// Function to add an item to the queue.
// It changes rear and size
void enqueue(Queue* queue, int item);

// Function to remove an item from queue.
// It changes front and size
int dequeue(Queue* queue);

// Function to add an item to stack.  It increases top by 1
void push(Queue* stack, int item);

// Function to remove an item from stack.  It decreases top by 1
int pop(Queue* stack);

void log_by_time(Queue* q);

void log_by_priority(Queue* q);
#endif //MINIOS_QUEUE_H
