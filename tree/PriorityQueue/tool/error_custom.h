#ifndef ERROR_CUSTOM_H
#define ERROR_CUSTOM_H

#define IS_NULL(ptr) !(ptr)
#include<stdbool.h>

typedef enum {
    NULL_PTR,
    MEMORY_ALLOCATE_FAILURE,
} Event;

void printError(const char* format, ...);
bool isValid(void* ptr, const char* functionName, Event type);
bool isPTRValid(void* ptr, const char* functionName);
bool isMemoryAllocate(void* ptr, const char* functionName);

#endif