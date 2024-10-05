#ifndef ERROR_HANDLE_H
#define ERROR_HANDLE_H
#include<stdbool.h>
#define IS_NULL(ptr) !(ptr)

static void printError(const char* format, ...);

typedef enum{
    NULL_PTR,
    MEMORY_ALLOCATE_FAILURE,
} Event;

bool isValid(void* ptr, const char* context, Event type);

//including null data ptr
bool isPTRValid(void* ptr, const char* functionName);
bool isMemoryAllocate(void* ptr, const char* functionName);

#endif