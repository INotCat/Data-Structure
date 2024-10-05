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

void printError(const char* format,...);
bool isValidStack(Stack* stack, const char* context);
Stack* initStack(size_t element_size, void (*print)(void*), void(*free_data)(void*));
bool isEmpty(Stack *stack);
size_t size(Stack *stack);
bool push(Stack* stack, void* value);
void* pop(Stack* stack);
void* peek(Stack* stack);//wrong
void printStack(Stack *stack);
void freeStack(Stack *stack);

#endif