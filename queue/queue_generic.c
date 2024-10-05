#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include"queue_generic.h"

// void printError(const char* format, ...){

// }

bool isValidQueue(Queue* q, const char* context){
    if(IS_NULL(q)){
        //printError("queue pointer is null in %c", context);
        return false;
    }
    return true;
}

Queue* initQueue(size_t element_size, void (*print)(void*), void(*free_data)(void*)){
    Queue* queue = (Queue*) malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    queue->queue_size = 0;
    queue->enqueue = enqueue;
    queue->dequeue = dequeue;
    queue->peek = peek;
    queue->size = size;
    queue->isEmpty = isEmpty;
    queue->clear = clear;
    queue->freeQueue = freeQueue;
    
    return queue;
}

bool enqueue(Queue* q, void* data){
    printf("%d", *(int*)data );
}

bool dequeue(Queue* q){

}

bool peek(Queue* q){

}

int size(Queue* q){

}

bool isEmpty(Queue* q){

}

bool clear(Queue* q){

}

bool freeQueue(Queue* q){

}
