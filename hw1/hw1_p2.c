#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<stdarg.h>
#define IS_NULL(ptr) !(ptr)
#define HEAP_CAPACITY 200
#define MAX_INPUT_LENGTH 1000
#define MAX_COMMAND_LENGTH 100

typedef enum{
    NULL_PTR,
    MEMORY_ALLOCATE_FAILURE,
} Event;


typedef struct MinHeap{
    int* harr;
    int capacity;
    int heap_size;
} MinHeap;

//Error handling and node creation
void printError(const char* format, ...);
bool isValid(void* ptr, const char* context, Event type);
bool isPTRValid(void* ptr, const char* functionName);
bool isMemoryAllocate(void* ptr, const char* functionName);

//Heap creation
MinHeap* initMinHeap(int capacity);
void insertKey(MinHeap* heap, int k);
void deleteKey(MinHeap* heap, int i);
int extractMin(MinHeap* heap);
int getMin(MinHeap* heap);
void decreaseKey(MinHeap* heap, int i, int new_val);
void bubbleUp(MinHeap* heap, int i);
void bubbleDown(MinHeap* heap, int i);
void resizeHeap(MinHeap* heap);
void freeHeap(MinHeap* heap);
void swap(int* x,int* y);
void printMinHeap(MinHeap* heap);
int searchIndex(MinHeap* heap, int value);

char* readInputString(FILE* fp, size_t size);

bool isEqual(const char* s1, const char* s2){
    return strcmp(s1, s2) == 0;
}

// int main(){
//     MinHeap* minheap = initMinHeap(200);
//     char* command = malloc(7);
//     const char* INSERT = "insert";
//     const char* DELETE = "delete";
//     const char* EXIT = "exit";


//     int number = 0;
//     while(1){
//         if( scanf("%s %d", command, &number)!=2){
//             printError("Invalid format");
//             break;
//         }
//         if(isEqual(command, INSERT)){
//             insertKey(minheap, number);
//         }
//         else if (isEqual(command, DELETE))
//         {
//             deleteKey(minheap, number);
//         }
//         else if (isEqual(command, EXIT)){
//             break;
//         }
//         else{
//             printError("Invaild Input");
//             break;
//         } 

//         printMinHeap(minheap);
//     }

//     printMinHeap(minheap);
//     return 0;
// }

int main() {
    MinHeap* minheap = initMinHeap(200);
    char command[MAX_COMMAND_LENGTH]; // Buffer to hold each command
    int number = 0;

    // Read the entire input at once
    char input[MAX_INPUT_LENGTH];
    // printf("Enter commands (end with a blank line):\n");
    
    while (fgets(input, sizeof(input), stdin)) {
        // Break the loop if an empty line is encountered
        if (strcmp(input, "\n") == 0) {
            break; // Exit the loop if the user presses Enter on an empty line
        }

        // Tokenize the input based on spaces
        char* token = strtok(input, " ");
        while (token != NULL) {
            // Check for "insert" or "delete" command
            if (strcmp(token, "insert") == 0) {
                token = strtok(NULL, " "); // Get the next token for the number
                if (token != NULL) {
                    number = atoi(token); // Convert the number from string to int
                    insertKey(minheap, number);
                } else {
                    printError("Invalid input format for insert.");
                }
            } else if (strcmp(token, "delete") == 0) {
                token = strtok(NULL, " "); // Get the next token for the number
                if (token != NULL) {
                    number = atoi(token); // Convert the number from string to int
                    deleteKey(minheap, number);
                } else {
                    printError("Invalid input format for delete.");
                }
            } else {
                printError("Invalid command.");
            }
            token = strtok(NULL, " "); // Get the next command or number
        }
    }
    
    printMinHeap(minheap); 
    return 0;
}


//minHeap for int
MinHeap* initMinHeap(int capacity){
    if(capacity == 0) return NULL;
    MinHeap* newHeap = (MinHeap*) malloc(sizeof(MinHeap));
    if(!isMemoryAllocate(newHeap, "initMinHeap")) return NULL;

    newHeap->capacity = capacity;
    newHeap->harr = (int *)malloc(newHeap->capacity * sizeof(int));
    if(!isMemoryAllocate( newHeap->harr, "initMinHeap")) return NULL;

    
    newHeap->heap_size = 0;
    
    return newHeap;
}

void insertKey(MinHeap* heap, int k){
    if(!isPTRValid(heap, "increasKey")) return;
    
    if(heap->heap_size == heap->capacity) {
        resizeHeap(heap);
        if(!isMemoryAllocate(heap->harr, "resizeHeap")) return;
    }

    //last element = insert element
    heap->heap_size++;
    int i = heap->heap_size - 1;
    heap->harr[i] = k;

    bubbleUp(heap, i);
}

//change to decrease by value
void deleteKey(MinHeap* heap, int value){
    if(!isPTRValid(heap, "deleteKey")) return;

    int index = searchIndex(heap, value);
    if(index < 0) return ;//if not found

    decreaseKey(heap, index, INT16_MIN);
    extractMin(heap);
}

int searchIndex(MinHeap* heap, int value){
    for(int i=0; i<heap->heap_size; i++){
        if(heap->harr[i] == value){
            return i;
        }
    }
    return INT16_MIN;
}

int extractMin(MinHeap* heap){
    if(!isPTRValid(heap, "extractMin") || heap->heap_size == 0) return INT16_MAX;
    
    if(heap->heap_size == 1){
        heap->heap_size--;
        return heap->harr[0];
    }
    
    int root = heap->harr[0];
    heap->harr[0] = heap->harr[heap->heap_size - 1];
    heap->heap_size--;

    bubbleDown(heap, 0);

    return root;
}

int getMin(MinHeap* heap){
    if(!isPTRValid(heap, "getMin") || heap->heap_size == 0) return INT16_MAX;
    return heap->harr[0];
}

void decreaseKey(MinHeap* heap, int i, int new_val){
    if(!isPTRValid(heap, "decreaseKey")) return;
    heap->harr[i] = new_val;

    bubbleUp(heap, i);
}

void bubbleUp(MinHeap* heap, int i){
    while(i!=0 && (heap->harr[i] < heap->harr[((i-1)/2)])){
        swap(&(heap->harr[i]), &(heap->harr[(i-1)/2]));
        i = (i-1) / 2;
    }
}

void bubbleDown(MinHeap* heap, int i){
    int smallest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if(left < heap->heap_size && heap->harr[left] < heap->harr[smallest]){
        smallest = left;
    }
    if(right < heap->heap_size && heap->harr[right] < heap->harr[smallest]){
        smallest = right;
    }

    if(smallest != i){
        swap(&(heap->harr[i]), &(heap->harr[smallest]));
        bubbleDown(heap, smallest);
    }
}

void resizeHeap(MinHeap* heap){
    heap->capacity *= 2;
    heap->harr = (int*) realloc(heap->harr, heap->capacity);
    if(!isMemoryAllocate(heap->harr, "resizeHeap")) return; 
}

void printMinHeap(MinHeap* heap){
    if(!isPTRValid(heap, "printMinHeap") || heap->heap_size == 0) return;
    
    int i=0;
    for(i=0; i<heap->heap_size; i++){
        printf("%d ", heap->harr[i]);
    }
    printf("\n");
}

void freeHeap(MinHeap* heap){
    if(!isPTRValid(heap, "freeHeap") || heap->heap_size == 0) return;
    free(heap->harr);
    free(heap);
}

void swap(int* x,int* y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

//error handler
void printError(const char* format, ...){
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

