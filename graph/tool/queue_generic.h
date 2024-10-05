#ifndef QUEUE_GENERIC_H
#define QUEUE_GENERIC_H

#include<stdio.h>
#include<stdbool.h>
#define IS_NULL(ptr) !(ptr)

typedef struct queueNode{
    void* data;
    struct queueNode* next;
} queueNode;

typedef struct Queue{
    queueNode* front;
    queueNode* rear;
    int queue_size;
    size_t element_size;
    void(*print_data)(void*);
    void (*free_data)(void*);
} Queue;

Queue* initQueue(size_t element_size, void (*print)(void*), void(*free_data)(void*));
void enqueue(Queue* q, void* data);
//return the direct data
void* dequeue(Queue* q);
void* peekQueue(Queue* q);

int sizeOfQueue(Queue* q);
bool isQueueEmpty(Queue* q);
void freeQueue(Queue* q);

#endif