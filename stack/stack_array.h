#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#define MAX_STACK_SIZE 1000
#define IS_NULL(ptr) (!ptr)

typedef struct {
    int top;
    int capacity;
    char* arr;
} Stack;

void printError(const char *format, ...){
    va_list args;
    va_start(args, format); //Start retrieving additional arguments

    fprintf(stderr,"Error: ");
    vfprintf(stderr, format, args);//Print the formatted error message
    fprintf(stderr, "\n");

    va_end(args); //Clean up the va_list
}

int isValidStack(Stack* stack, const char* context){
    if(IS_NULL(stack)){
        printError("Stack pointer is null in %s", context);
        return 0;
    }
    return 1;
}

int initStack(Stack* stack, int capacity){
    if(!isValidStack(stack, "initStack")){
        return  -1;
    } 
    else if(capacity > MAX_STACK_SIZE){
        printError("The capacity for memory allocating exceeded the limit in initStack");
        return -1;
    }
    else{
        stack->capacity = capacity;
        stack->top = -1;
        stack->arr = (char*)malloc(sizeof(char));
        if(IS_NULL(stack->arr)) {
            printError("fail to to malloc in initStack funciton");
            return -1;
        }
        return 0;
    }
}

int isFull(Stack* stack){
    return stack->top == stack->capacity - 1;
}

int isEmpty(Stack* stack){
    return stack->top == -1;
}

int size(Stack* stack){
    return stack->top + 1 ;
}

int push(Stack* stack, char value){
    if(!isValidStack(stack, "push")) return -1;
    if(isFull(stack)) {
        printError("Stack overflow in push function");
        return -1;
    }

    stack->arr[++stack->top] = value;
    return 0;
}

int pop(Stack* stack, char* poppedValue){
    if(!isValidStack(stack, "pop")) return -1;
    if(isEmpty(stack)) {
        printError("Stack underflow in pop function");
        return -1;
    }

    *poppedValue = stack->arr[stack->top--]; 
    //not strickly necessarily to set the 0 when the value is popped out
    return 0;
}

int peek(Stack* stack, char *topValue){
    if(!isValidStack(stack, "peek")) return -1;
    if(isEmpty(stack)) {
        printError("Stack is empty in peeok function");
        return -1;
    }

    *topValue = stack->arr[stack->top];
    return 0;
}

void displayStack(Stack* stack){
    for(int i=0; i<stack->top+1; i++){
        printf("In stack: %c\n", stack->arr[i]);
    }
}

int resize(Stack* stack, int newCapacity){
    char* newArr = (char*)realloc(stack->arr, newCapacity*sizeof(char));
    if(IS_NULL(newArr)){
        printError("Fail to realloc in resize funciton");
        return -1;
    }
    stack->arr = newArr;
    stack->capacity = newCapacity;
    return 0;
}

//merge s2 into si
void merge(Stack* s1, Stack* s2){
    while(s1->top + s2->top + 2 >= s1->capacity){
        resize(s1, s1->capacity * 2);//resize * 2^n  
    }

    for(int i=0; i<s2->top+1; i++){
        s1->arr[++s1->top] = s2->arr[i];
    }

    s2->top = -1;
}