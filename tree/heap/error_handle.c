#include<stdio.h>
#include<stdarg.h>
#include"error_handle.h"

static void printError(const char* format, ...){
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
}

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

//including null data ptr
bool isPTRValid(void* ptr, const char* functionName){
    return isValid(ptr, functionName, NULL_PTR);
}

bool isMemoryAllocate(void* ptr, const char* functionName){
    return isValid(ptr, functionName, MEMORY_ALLOCATE_FAILURE);
}
