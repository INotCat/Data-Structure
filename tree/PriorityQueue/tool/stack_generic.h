#ifndef STACK_GENERIC_H
#define STACK_GENERIC_H

#define IS_NULL(ptr) !(ptr)
#include<stdio.h>
#include<stdbool.h>

typedef struct Node{
    void *data;
    struct Node* next;
} Node;

typedef struct Stack{
    Node* top;
    size_t size;
    size_t element_size;
    void (*print)(void*); //Function pointer for custom element printing
    void (*free_data)(void*);//for custom data freeing
} Stack;

Stack* initStack(size_t element_size, void (*print)(void*), void(*free_data)(void*));
bool isStackEmpty(Stack *stack);
size_t sizeOfStack(Stack *stack);
bool push(Stack* stack, void* value);
//return the copy
void* pop(Stack* stack);
//directly return org data
void* peekStack(Stack* stack);
void printStack(Stack *stack);
void freeStack(Stack *stack);

#endif