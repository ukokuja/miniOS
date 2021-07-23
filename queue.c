// Libraries
#include <stdio.h>
// miniOS
#include "queue.h"
#include "environment_variables.h"

int items[MAX_TASKS];
int front = -1, rear = -1;

int isFull() {
    if ((front == rear + 1) || (front == 0 && rear == MAX_TASKS - 1)) return 1;
    return 0;
}

// Check if the queue is empty
int isEmpty() {
    if (front == -1) return 1;
    return 0;
}

// Adding an element
void enQueue(int element) {
    if (!isFull()) {
        if (front == -1) front = 0;
        rear = (rear + 1) % MAX_TASKS;
        items[rear] = element;
    }
}

// Removing an element
int deQueue() {
    int element;
    if (!isEmpty()) {
        element = items[front];
        if (front == rear) {
            front = -1;
            rear = -1;
        }
            // Q has only one element, so we reset the
            // queue after dequeing it. ?
        else {
            front = (front + 1) % MAX_TASKS;
        }
        return (element);
    }
}

// Display the queue
void logQueue() {
    FILE *csv = fopen(LOG_FILENAME, "a");
    int i;
    if (!isEmpty()) {
        fprintf(csv, "[");
        for (i = front; i != rear; i = (i + 1) % MAX_TASKS) {
            fprintf(csv, "%d,", items[i]);
        }
        fprintf(csv, "%d]", items[i]);
    }
    fprintf(csv, "\n");
    fclose(csv);
}
