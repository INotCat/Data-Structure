#ifndef DEQUE_GENERIC_H
#define DEQUE_GENERIC_H
#define IS_NULL(ptr) !(ptr)
#include<stdio.h>
#include<stdbool.h>

typedef struct Node {
    void* data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct Deque {
    Node* front;
    Node* rear;
    size_t size; // queue size
    size_t element_size;
    void(*print)(void*);
    void(*free_data)(void*);
    //bool(*frontPush)(Deque* deque, void* value);why not put funciton ptr here and we can use .
} Deque;

static void printError(const char* format,...);
bool isValidDeque(Deque* deque, const char* context);
Deque* initDeque(size_t element_size, void(*print)(void*), void(*free_data)(void*));
bool isEmpty(Deque* deque);
size_t size(Deque* deque);
bool frontPush(Deque* deque, void* value);
bool rearPush(Deque* deque, void* value);
void* frontPop(Deque* deque);
void* rearPop(Deque* deque);
void* frontPeek(Deque* deque);
void* rearPeek(Deque* deque);
void printDeque(Deque* deque);
void freeDeque(Deque* deque);

#endif