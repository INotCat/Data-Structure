#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#define MAX_STACK 1000

typedef struct {
    int top;
    int arr[MAX_STACK];
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
    if(stack == NULL){
        printError("Stack pointer is null in %s", context);
        return 0;
    }
    return 1;
}

int initStack(Stack* stack){
    if(!isValidStack(stack, "initStack")){
        return  -1;
    } 
    else{
        stack->top = -1;
        return 0;
    }
}

int isFull(Stack* stack){
    return stack->top == MAX_STACK - 1;
}

int isEmpty(Stack* stack){
    return stack->top == -1;
}

int size(Stack* stack){
    return stack->top+1 ;
}

int push(Stack* stack, int value){
    if(!isValidStack(stack, "push")) return -1;
    if(isFull(stack)) {
        printError("Stack overflow in push function");
        return -1;
    }

    stack->arr[++stack->top] = value;
    return 0;
}

int pop(Stack* stack, int* poppedValue){
    if(!isValidStack(stack, "pop")) return -1;
    if(isEmpty(stack)) {
        printError("Stack underflow in pop function");
        return -1;
    }

    *poppedValue = stack->arr[stack->top--]; 
    //not strickly necessarily to set the 0 when the value is popped out
    return 0;
}

int peek(Stack* stack, int *topValue){
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
        printf("In stack: %d\n", stack->arr[i]);
    }
}

Stack* merge(Stack* s1, Stack* s2){
    if(!isValidStack) return -1;
    
}

int main(){

}
