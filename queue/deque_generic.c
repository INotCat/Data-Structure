#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include"deque_generic.h"

void printError(const char *format, ...){
    va_list args;
    va_start(args, format);

    fprintf(stderr, "Error: ");
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");

    va_end(args);
}

bool isValidDeque(Deque* stack, const char* context){
    if(IS_NULL(stack)){
        printError("Deque pointer is null in %s", context);
        return false;
    }
    
    return true;
}

Deque* initDeque(size_t element_size, void(*print)(void*), void(*free_data)(void*)){
    Deque* deque = (Deque*)malloc(sizeof(Deque));
    deque->front = NULL;
    deque->rear = NULL;
    deque->size = 0;
    deque->element_size = element_size;
    deque->print = print;
    deque->free_data = free_data;
    return deque;
}

bool isEmpty(Deque* deque){
    if(!isValidDeque(deque, "isEmpty")) return false;
    return deque->size == 0;
}

size_t size(Deque* deque){
    if(!isValidDeque(deque, "size")) return 0;////how to check if is invalid
    return deque->size;
}

bool frontPush(Deque* deque, void* value){
    if(!isValidDeque(deque, "frontPush")) return false;
    if (IS_NULL(value)){
        printError("Invalid value passed to frontPush function");
        return false;
    }
    Node* newNode = (Node*) malloc(sizeof(Node));
    if(IS_NULL(newNode)){
        printError("Fail to allocate memory for newNode in frontPush function");
        return NULL;
    }
    newNode->next = deque->front;//next rightforward 211113 2->1->1->...->3
    newNode->prev = NULL;

    newNode->data = malloc(deque->element_size);
    if(IS_NULL(newNode->data)){
        free(newNode);
        printError("Fail to allocate memory for newNode->data in frontPush function");
        return false;
    }

    memcpy(newNode->data, value, deque->element_size);//how to check if it failed

    if (isEmpty(deque)) {
        deque->rear = newNode;
    } 
    else {
        deque->front->prev = newNode;
    }
    deque->front = newNode;
    deque->size++;
    return true;
}

bool rearPush(Deque* deque, void* value){
    if(!isValidDeque(deque, "rearPush")) return false;
    if(IS_NULL(value)){
        printError("Invalid value passed to frontPush function");
        return false;
    }

    Node* newNode = (Node*) malloc(sizeof(Node));
    if(IS_NULL(newNode)){
        printError("Fail to allocate memory for newNode in rearPush function");
        return false;
    }
    
    newNode->next = NULL;
    newNode->prev = deque->rear;

    newNode->data = malloc(deque->element_size);
    if(IS_NULL(newNode->data)){
        free(newNode);
        printError("Fail to allocate memory for newNode->data in rearPush function");
        return false;
    }

    if (isEmpty(deque)) {
        deque->front = newNode;
    } else {
        deque->rear->next = newNode;
    }
    deque->rear = newNode;
    deque->size++;
    return true;
}

void* frontPop(Deque* deque){
    if(!isValidDeque(deque, "frontPop")) return NULL;
    if(isEmpty(deque)) return NULL;

    Node* temp = deque->front;

    void* poppedValue = malloc(deque->element_size);
    if(IS_NULL(poppedValue)){
        printError("Fail to allocate memory for popped value in frontPop function");
        return NULL;
    }
    memcpy(poppedValue, temp->data, deque->element_size);
    deque->front = temp->next;

    // If the deque is not empty, update the new front's prev pointer
    if (!IS_NULL(deque->front)) {
        deque->front->prev = NULL;
    } else {
        // If the deque becomes empty, set rear to NULL as well
        deque->rear = NULL;
    }

    if(!IS_NULL(deque->free_data)){
        deque->free_data(temp->data);
    }
    else{
        free(temp->data);
        temp->data = NULL;
    }

    free(temp);
    temp = NULL;
    deque->size--;
    return poppedValue;
}

void* rearPop(Deque* deque){
    if(!isValidDeque(deque, "rearPop")) return NULL;
    if(isEmpty(deque)) return NULL;

    Node* temp = deque->rear;

    void*  poppedValue = malloc(deque->element_size);
    if (IS_NULL(poppedValue)) {
        printError("Fail to allocate memory for popped value in rearPop function");
        return NULL;
    }
    memcpy(poppedValue, temp->data, deque->element_size);
    deque->rear = temp->prev;

    //If the deque is not empty, update the new rear's next pointer
    if(!IS_NULL(deque->rear)){
        deque->rear->next = NULL;
    }
    else{
        //If the deque becomes empty, front = rear = NULL
        deque->front = NULL;
    }

    if(!IS_NULL(deque->free_data)){
        deque->free_data(temp->data);
    }
    else{
        free(temp->data);
        temp->data = NULL;
    }

    free(temp);
    temp = NULL;
    deque->size--;
    return poppedValue;
}

void* frontPeek(Deque* deque){
    if(!isValidDeque(deque, "frontPeek")) return NULL;
    if(isEmpty(deque)) return NULL;

    return deque->front->data;
}

void* rearPeek(Deque* deque){
    if(!isValidDeque(deque, "rearPeek")) return NULL;
    if(isEmpty(deque)) return NULL;

    return deque->rear->data;
}

void printDeque(Deque* deque){
    if(!isValidDeque(deque, "printDeque")) return;
    if(IS_NULL(deque->print)) {
        printError("prrint function pointer is null");
        return;
    }
    if(isEmpty(deque)){
        printf("Deque is empty \n");
        return;
    } 

    Node* current = deque->front;
    while(!IS_NULL(current)){
        deque->print(current->data);
        current = current->next;
    }
}

void freeDeque(Deque* deque){
    if(!isValidDeque(deque, "freeDeque")) return;
    if(isEmpty(deque)){
        free(deque);
        deque = NULL;
        return;
    }

    Node* current = deque->front;
    Node* nextNode = current;

    // Determine the function to free data based on free_data presence
    void (*freeData)(void*) = deque->free_data ? deque->free_data : free;

    while (current != NULL) {
        nextNode = current->next;

        freeData(current->data);
        free(current);

        current = nextNode;
    }

    free(deque);
    deque = NULL;
}