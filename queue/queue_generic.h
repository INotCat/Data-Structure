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
    void(*print)(void*);
    void (*free_data)(void*);
    bool (*enqueue)(struct Queue*, void*);
    bool (*dequeue)(struct Queue*);
    bool (*peek)(struct Queue*);
    int (*size)(struct Queue*);
    bool (*isEmpty)(struct Queue*);
    bool (*clear)(struct Queue*);
    bool (*freeQueue)(struct Queue*);
} Queue;

// void printError(const char *format,...);
bool isValidQueue(Queue* q, const char* context); 
Queue* initQueue(size_t element_size, void (*print)(void*), void(*free_data)(void*));
bool enqueue(Queue* q, void* data);
bool dequeue(Queue* q);
bool peek(Queue* q);
int size(Queue* q);
bool isEmpty(Queue* q);
bool clear(Queue* q);
bool freeQueue(Queue* q);

