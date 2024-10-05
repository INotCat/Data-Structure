#include<stdlib.h>
#include<string.h>
#include<stdarg.h>
#include"stack_generic.h"

void printError(const char *format, ...){
    va_list args;
    va_start(args, format);

    fprintf(stderr, "Error: ");
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");

    va_end(args);
}

bool isValidStack(Stack* stack, const char* context){
    if(IS_NULL(stack)){
        printError("Stack pointer is null in %s", context);
        return false;
    }
    
    return true;
}

Stack* initStack(size_t element_size, void (*print)(void*), void(*free_data)(void*)){
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    stack->top = NULL;
    stack->size = 0;
    stack->element_size = element_size;
    stack->print = print;
    stack->free_data = free_data;
    return stack;
}

bool isEmpty(Stack* stack){
    if(!isValidStack(stack, "isEmpty")) return false;
    return stack->size == 0;
}

size_t size(Stack* stack){
    if(!isValidStack(stack, "isEmpty")) return 0;
    return stack->size;
}

bool push(Stack* stack, void* value){
    if(!isValidStack(stack, "push")) return false;
    
    Node* newNode = (Node*) malloc(sizeof(Node));
    if(IS_NULL(newNode)) {
        printError("Fail to allocate memory for newNode in push function");
        return false;
    }
    
    newNode->data = malloc(stack->element_size);
     if(IS_NULL(newNode->data)) {
        printError("Fail to allocate memory for newNode->data in push function");
        return false;
    }

    memcpy(newNode->data, value, stack->element_size);
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
    return true;
}

void* pop(Stack* stack){
    if(!isValidStack(stack, "pop")) return NULL;
    if(isEmpty(stack)) return NULL;

    Node* temp = stack->top;
    void* poppedvalue = malloc(stack->element_size);
    if(IS_NULL(poppedvalue)) return NULL;

    memcpy(poppedvalue, temp->data, stack->element_size);
    stack->top = stack->top->next;
    
    if(!IS_NULL(stack->free_data)){
        stack->free_data(temp->data);
    }
    else{
        free(temp->data);
        temp->data = NULL;
    }
    
    free(temp);
    temp = NULL;
    stack->size--;
    return poppedvalue;
}

void* peek(Stack* stack){
    if(!isValidStack(stack, "peek")) return NULL;
    if(isEmpty(stack)) return NULL;
    
    void* topValue = malloc(stack->element_size);
    if(IS_NULL(topValue)) reuturn NULL;

    memcpy(topValue, stack->top->data, stack->element_size);
    return topValue;
}

void printStack(Stack *stack){
    if(!isValidStack(stack, "printStack")) return;
    if(IS_NULL(stack->print)) {
        printError("prrint function pointer is null");
        return;
    }
    if(isEmpty(stack)) return;

    Node* current = stack->top;

    while(!IS_NULL(current)){
        stack->print(current->data);
        current = current->next;
    }

    printf("NULL\n");
}

void freeStack(Stack *stack){
    if(!isValidStack(stack, "freeStack")) return;
    if(isEmpty(stack)){
        free(stack);
        stack = NULL;
        return;
    }

    Node* current = stack->top;
    Node* nextNode;

    void(*freeData)(void*) = stack->free_data ? stack->free_data : free;


    //if stack->free_data is not null, then use this customed free_function to free the data
    while (current != NULL) {
        nextNode = current->next;

        freeData(current->data);
        free(current);
        
        current = nextNode;
    }

    stack->top = NULL;
    free(stack);
    stack = NULL;
}
