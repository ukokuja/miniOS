//
// Created by lucas on 20/07/2021.
//

#include "queue.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
// function to create a queue
// of given capacity.
// It initializes size of queue as 0
void initQueue(Queue* q, int* array, unsigned capacity)
{
    q->capacity = capacity;
    q->front = q->size = 0;

    // This is important, see the enqueue
    q->rear = capacity - 1;
    q->array = array;
}

// Queue is full when size becomes
// equal to the capacity
int isFull(Queue* queue)
{
    return (queue->size == queue->capacity);
}

// Queue is empty when size is 0
int isEmpty(Queue* queue)
{
    return (queue->size == 0);
}

// Function to add an item to the queue.
// It changes rear and size
void enqueue(Queue* queue, int item)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1)
                  % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
//    printf("%d enqueued to queue\n", item);
//    for (int i = 0; i < 10; i++) {
//        printf("%d,", queue->array[i]);
//    }
//    printf("\n");
}

// Function to remove an item from queue.
// It changes front and size
int dequeue(Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1)
                   % queue->capacity;
    queue->size = queue->size - 1;
//    printf("%d dequeued to queue\n", item);
    return item;
}

// Function to add an item to stack.  It increases top by 1
void push(Queue* stack, int item)
{
    if (isFull(stack))
        return;
    stack->array[++stack->size] = item;
//    printf("%d pushed to stack\n", item);
}

// Function to remove an item from stack.  It decreases top by 1
int pop(Queue* stack)
{
    if (isEmpty(stack))
        return INT_MIN;
    int item = stack->array[stack->size--];
//    printf("%d poped from stack\n", item);
    return item;
}

void logByTime(Queue* q) {
    FILE* csv = fopen(LOG_FILENAME,"a");
    fprintf(csv, "[");
    int i;
    if (q->rear >= q->front) {
        for (i = q->front; i < q->rear; i++)
            fprintf(csv,"%d,",q->array[i]);
        fprintf(csv, "%d]", q->array[i]);
    } else {
        for (i = q->front; i <= q->size; i++)
            fprintf(csv,"%d,", q->array[i]);
        for (i = 0; i < q->rear; i++)
            fprintf(csv,"%d,", q->array[i]);
        fprintf(csv, "%d]", q->array[i]);
    }
    fprintf(csv, "\n");
    fclose(csv);
}

void logByPriority(Queue* q) {
    FILE* csv = fopen(LOG_FILENAME,"a");
    int h;
    fprintf(csv, "[");
    for (h = q->size; h > 1; h--)
        fprintf(csv, "%d,", q->array[h]);
    fprintf(csv, "%d]", q->array[h]);
    fprintf(csv, "\n");
    fclose(csv);
}