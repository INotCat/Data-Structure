#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<string.h>
#include"error_custom.h"
#include"queue_generic.h"

queueNode* getNewQueueNode(void* data, size_t element_size){
    if(!isPTRValid(data, "getNewQueueNode") && element_size != 0) return NULL;

    queueNode* newNode = (queueNode*) malloc(sizeof(queueNode));
    if(!isMemoryAllocate(newNode, "getNewQueueNode")) return NULL;

    newNode->data = malloc(element_size);
    if(!isMemoryAllocate(newNode->data, "getNewQueueNode")){
        free(newNode);
        newNode = NULL;
        return NULL;
    }

    memcpy(newNode->data, data, element_size);
    return newNode;
}

Queue* initQueue(size_t element_size, void (*print_data)(void*), void(*free_data)(void*)){
    Queue* queue = (Queue*) malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    queue->queue_size = 0;
    queue->element_size = element_size;
    queue->print_data = print_data;

    void(*freeData)(void*) = queue->free_data ? queue->free_data : free;
    return queue;
}

void enqueue(Queue* q, void* data){
    if(!isPTRValid(q, "sizeOfQueue") || !isPTRValid(data, "sizeOfQueue")) return;
    
    if(isQueueEmpty(q)){
        q->front = getNewQueueNode(data, q->element_size);
        q->rear = q->front;
        q->queue_size++;
        return;
    }
    
    queueNode* newNode = getNewQueueNode(data, q->element_size);
    q->rear->next = newNode;
    q->rear = newNode;
    q->queue_size++;
}

void* dequeue(Queue* q){
    if(!isPTRValid(q, "sizeOfQueue") || isQueueEmpty(q)) return NULL;

    queueNode* temp = q->front;
    void* data = temp->data;

    q->front = q->front->next;
    if(q->front == NULL){
        q->rear = NULL;
    }

    q->queue_size--;
    free(temp);//free the temp but not the data, the data has been transfer the void* data
    return data;//even though the data pointer is wiped out, but the reference it pass is to a valid memory location
}

//case1: return copy of the data, much safer but use up space
//case2: return the direct data store in the Node
void* peekQueue(Queue* q){
    if(!isPTRValid(q, "sizeOfQueue") || isQueueEmpty(q)) return NULL;
    return q->front->data;
}

int sizeOfQueue(Queue* q){
    if(!isPTRValid(q, "sizeOfQueue")) return INT16_MIN;
    return q->queue_size;
}

bool isQueueEmpty(Queue* q){
    if(!isPTRValid(q, "sizeOfQueue")) return false;
    return q->queue_size == 0;
}

void freeQueue(Queue* q){
    if(!isPTRValid(q, "sizeOfQueue") || isQueueEmpty(q)) return;
}
