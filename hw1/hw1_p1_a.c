#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<stdarg.h>
#define IS_NULL(ptr) !(ptr)
// Error event
typedef enum{
    NULL_PTR,
    MEMORY_ALLOCATE_FAILURE,
} Event;

// Wrapper the random-size data for the node 
typedef struct Object{
    void* data;
    size_t data_size;
} Object;

// Generic Node for stack
typedef struct Node{
    Object* obj;
    struct Node* next;
} Node;

typedef struct Stack{
    Node* top;
    size_t stack_size;
    void (*print_data)(void*); // Function pointer for custom element printing
    void (*free_data)(void*);  // For custom data freeing
} Stack;



void printError(const char* format, ...);
bool isValid(void* ptr, const char* context, Event type);
bool isPTRValid(void* ptr, const char* functionName);
bool isMemoryAllocate(void* ptr, const char* functionName);
Object* Obj(void* data, size_t data_size); 
Node* getNewNode(Object* data);

Stack* initStack(void(*print_data)(void*), void(*free_data)(void*));
void* pop(Stack* s);
void push(Stack* s, Object* data);
void* peekStack(Stack* s);
bool isStackEmpty(Stack* s);
void freeStack(Stack* s);

char* readInputString(FILE* fp, size_t size);
bool isOperator(char c);
char* concat(const char* s1, const char* s2, const char* op);

const char operator[] = {'+', '-', '*', '/'};
// Testcase of prefix to infix
    //char inputBuffer[] = "-*AB/CD";      //A*B-C/D
    //char inputBuffer[] = "+A-*BC/DE";    //A+B*C-D/E
    //char inputBuffer[] = "+*AB-/CD+EF";  //A*B+C/D-E+F


int main(){
    Stack* s = initStack(NULL, NULL);

    // printf("input: ");
    char* inputBuffer = readInputString(stdin, 20);
    //string len is 7 but array is size 8 including clude NULL pointer
    int inputLen = strlen(inputBuffer);

    size_t len1, len2;
    for (int i = inputLen - 1; i >= 0; i--) {
        if (isOperator(inputBuffer[i])) {
            char* operand1 = (char*)pop(s);
            char* operand2 = (char*)pop(s);
            char operatorStr[2] = {inputBuffer[i], '\0'};

            char* res = concat(operand1, operand2, operatorStr);
            push(s, Obj(res, strlen((char*)res)));
            //since my data structure copy new one in the stack
            free(operand1);
            free(operand2);
            free(res);
        } 
        else {
            //operandStr is a local array, so calling free() directly on it 
            //would cause the error since the memory wasn't allocated on the heap.
            char operandStr[] = {inputBuffer[i], '\0'};
            push(s, Obj(operandStr, 2));
        }
    }


    char* output = (char*)pop(s);
    printf("%s\n", output);
    
    free(inputBuffer);
    free(output);
    freeStack(s);
    return 0;
}

bool isOperator(char c){
    for(int i=0; i<4; i++){
        if(c == operator[i]){
            return true;
        }
    }
    return false;
}

/**
 * @brief Concatenates two strings with an operator in between.
 * 
 * This function creates a new string s1 + op + s2
 * 
 * @param s1 operand_1
 * @param s2 operand_2
 * @param op operator
 * @return char*: A pointer to the newly allocated string with value of value = s1ops2\0,
 *          or NULL if memory allocation fails.
 */
char* concat(const char* s1, const char* s2, const char* op){
    size_t len = strlen(s1) + strlen(s2) + strlen(op) + 1;//+1 remember null terminator (\0)
    char* result = (char*) malloc(len);
    if(!isMemoryAllocate(result, "concat")) return NULL;
    
    //snprintf concat multiple string in formatting and avoiding buffer overflow
    snprintf(result, len, "%s%s%s", s1, op, s2);
    return result;
}


/**
 * @brief Reads a string from fp, expanding the buffer as needed.
 * 
 * This function reads characters from the provided file pointer until
 * a newline or EOF is encountered. The buffer size is dynamically
 * increased if necessary to accommodate the input.
 * 
 * @param fp stdin/stdout/stderr/or a file ptr
 * @param size The initial size of the buffer.
 * @return char* A pointer to the newly allocated string containing the 
 *         input, or NULL if memory allocation fails.
 */
char* readInputString(FILE* fp, size_t size){
    char *str = malloc(sizeof(*str) * size);
    if(!isMemoryAllocate(str, "readInputString")) return NULL;

    int ch;
    size_t len = 0; // calculate the real length of the string
    int max_capacity = 2000;

    while(EOF != (ch = fgetc(fp)) && ch != '\n'){
        if(size >= max_capacity){
            printError("Input string exceeded max capacity!");
            break;
        }

        str[len++] = ch;

        if(len == size){
            str = realloc(str, sizeof(*str) * (size *= 2) );
            if(!isMemoryAllocate(str, "readInputString")) return NULL;
        }
    }
    str[len++] = '\0';

    return realloc(str, sizeof(*str) * len);
}    

Stack* initStack(void(*print_data)(void*), void(*free_data)(void*)){
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    if(!isPTRValid(stack, "initStack")) return NULL;

    stack->print_data = print_data;
    stack->free_data = free_data ? free_data : free;
    stack->top = NULL;
    stack->stack_size = 0;
    return stack;
}

//Return "copy" of the data of stack's top and pop out the original one
void* pop(Stack* s){
    if(!isPTRValid(s, "pop")) return NULL;
    if(isStackEmpty(s)) {
        printError("Stack is Empty");
        return NULL;
    }

    void* poppedData = malloc(s->top->obj->data_size); 
    if (isMemoryAllocate(poppedData, "pop")) {
        memcpy(poppedData, s->top->obj->data, s->top->obj->data_size);
    }

    // Regardless of malloc success, remove the top node from the stack, 
    // since we already copy a same one to poppedData;
    s->free_data(s->top->obj->data);
    free(s->top->obj);
    // Adjust the stack
    Node* temp = s->top;
    s->top = s->top->next;
    free(temp);

    s->stack_size--;
    return poppedData;  // If malloc failed, poppedData will be NULL
}

void push(Stack* s, Object* data){
    if(!isPTRValid(s, "push") || !isPTRValid(data, "push")) return;

    Node* newNode = getNewNode(data);
    if(!isPTRValid(newNode, "push")) return;

    // Set the new node's next to the current top
    newNode->next = s->top;

    // Update the top pointer to the new node
    s->top = newNode;

    s->stack_size++;
}

//Return "copy" of the data of stack's top
void* peekStack(Stack* s){
    if(!isPTRValid(s, "peekStack")) return NULL;
    if(isStackEmpty(s)) {
        printError("Stack is Empty");
        return NULL;
    }

    void* poppedData = malloc(s->top->obj->data_size); 
    if(!isMemoryAllocate(poppedData, "pop")) return NULL;

    memcpy(poppedData, s->top->obj->data, s->top->obj->data_size); 

    return poppedData;
}

bool isStackEmpty(Stack* s){
    return s->stack_size == 0;
}

void freeStack(Stack* s){
    if(!isPTRValid(s, "freeStack") || isStackEmpty(s)) return;
    
    Node* curr = NULL;
    while(s->top != NULL){
        curr = s->top;
        s->top = curr->next;
        s->free_data(curr->obj->data);
        free(curr->obj);
        free(curr);
    }

    s->top = NULL;
    free(s);
}

 
/*
 * Problem: The data is of type char*, so we can use strlen to determine its size.
 * However, if the data is not a string, we need to handle different data types 
 * and sizes. The following functions facilitate creating new nodes and 
 * objects while managing memory safely.
 */

/**
 * @brief Creates a new node for stack usage.
 *
 * This function allocates memory for a new node, initializes it with the given
 * data, and links it to the next node.
 *
 * @note Store the Object data directly, not copy anything
 * @param Object* A pointer to the object data.
 * @return Node*: A pointer to the newly created Node, or NULL if memory allocation fails 
 *         or if the input pointer is invalid.
 */
Node* getNewNode(Object* data){
    if (!isPTRValid(data, "getNewNode")) return NULL;

    Node* newNode = (Node*) malloc(sizeof(Node));
    if (!isMemoryAllocate(newNode, "getNewNode")) return NULL;
    newNode->obj = data;
    newNode->next = NULL;
    return newNode;
}  

/**
 * @brief A wrapper: creates a new Object and copies input data into it.
 *
 * This function allocates memory for a new Object, copies the input data into it,
 * and records the size of the data.
 * 
 * @note After the copy, if the original data is of no used, then free(data) yourselves
 *
 * @param data A pointer to the data to be copied into the new Object.
 * @param data_size The size of the data to be copied.
 * @return Object*: A pointer to the newly created Object, or NULL if memory allocation fails 
 *         or if the input pointer is invalid.
 */
Object* Obj(void* data, size_t data_size){
    if (!isPTRValid(data, "Obj") || data_size <= 0) return NULL;

    Object* newObj = (Object*) malloc(sizeof(Object));
    if (!isMemoryAllocate(newObj, "Obj")) return NULL;

    newObj->data_size = data_size;
    newObj->data = malloc(newObj->data_size);
    if (!isMemoryAllocate(newObj->data, "getNewNode")){
        free(newObj);
        return NULL;
    }

    memcpy(newObj->data, data, newObj->data_size);
    return newObj;
}

/*
 * Error Handling Documentation
 *
 * This module provides functions for error handling in C, specifically
 * for validating pointers and handling memory allocation errors.
 *
 * Functions Overview:
 *
 * 1. void printError(const char* format, ...);
 * 2. bool isValid(void* ptr, const char* context, Event type);
 * 3. bool isPTRValid(void* ptr, const char* functionName);
 * 4. bool isMemoryAllocate(void* ptr, const char* functionName);
 */

/**
 * @brief Prints error messages to the standard error stream.
 *
 * This function accepts a format string and a variable number of arguments,
 * similar to printf.
 *
 * @param format A format string that specifies how subsequent arguments are 
 *               converted for output.
 */
void printError(const char* format, ...){
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
}

/**
 * @brief Checks the condition of a pointer and logs an error message.
 *
 * This function validates a pointer and logs an error message based on the
 * specified context and error type.
 *
 * @param ptr The pointer to be validated.
 * @param context A string represents function name where the pointer is used
 * @param type An enumeration indicating the type of error to be reported.
 *
 * @return true if the pointer is valid (not NULL), false if it is NULL and an
 *         error message is printed.
 */
bool isValid(void* ptr, const char* context, Event type){
    if(IS_NULL(ptr)){
        switch(type){
            case NULL_PTR:
                printError("Error: NULL pointer in %s", context);
                break;
            case MEMORY_ALLOCATE_FAILURE:
                printError("Error: Fail to allocate memory in %s", context);
                break;
        }
        return false;
    }
    return true;
}

/**
 * @brief Checks if a pointer is NULL, specifically for pointer validation.
 *
 * This function wraps the isValid function to check for NULL pointers.
 *
 * @param ptr The pointer to be checked.
 * @param functionName The name of the function where the check is performed.
 *
 * @return Result of isValid function with NULL_PTR as the error type.
 */
bool isPTRValid(void* ptr, const char* functionName){
    return isValid(ptr, functionName, NULL_PTR);
}

/**
 * @brief Checks for memory allocation failures.
 *
 * This function wraps the isValid function to specifically check for memory
 * allocation failures.
 * 
 * @param ptr The pointer to be checked.
 * @param functionName The name of the function where the check is performed.
 *
 * @return Result of isValid function with MEMORY_ALLOCATE_FAILURE as the
 *         error type.
 */
bool isMemoryAllocate(void* ptr, const char* functionName){
    return isValid(ptr, functionName, MEMORY_ALLOCATE_FAILURE);
}