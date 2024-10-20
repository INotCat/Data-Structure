#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<stdarg.h>
#define IS_NULL(ptr) !(ptr)
#define DEFAULT_ROW 100
#define DEFAULT_COLUMN 100
#define MAX_ROW 500
#define MAX_RCOLUMN 500

typedef enum{
    NULL_PTR,
    MEMORY_ALLOCATE_FAILURE,
} Event;

typedef struct Node{
    void* data;
    struct Node* next;
} Node;

typedef struct Queue{
    Node* front;
    Node* rear;
    size_t queue_size;
    size_t element_size;
    void(*print_data)(void*);
    void (*free_data)(void*);
} Queue;


typedef struct vertice {
    int data;
    int* neighbor; 
    int neighbor_count;
} V;

typedef struct Undirected_Graph {
    V* gArr; 
    size_t vertice_count; 
} Graph;




//Error handling and node creation
void printError(const char* format, ...);
bool isValid(void* ptr, const char* context, Event type);
bool isPTRValid(void* ptr, const char* functionName);
bool isMemoryAllocate(void* ptr, const char* functionName);

Node* getNewNode(void* data, size_t size);
Queue* initQueue(size_t element_size, void(*print_data)(void*), void(*free_data)(void*));
void enqueue(Queue* q, void* data);
void* dequeue(Queue* q);
void* peekQueue(Queue* q);
bool isQueueEmpty(Queue* q);
void freeQueue(Queue* q);

Graph* initGraph(size_t vertice_count);
bool isNeighbor(Graph* G,int v1, int v2);
void addUndirectedEdge(Graph* G,int vertice1, int vertice2);
int* BFS(Graph* G);

int main(){
    int gridLen = 4;
    Graph* G = initGraph(gridLen);


    //read grid first line = gridLen
    //use a loop to add edges
    addUndirectedEdge(G,1,2);
    addUndirectedEdge(G,1,4);
    addUndirectedEdge(G,2,1);
    addUndirectedEdge(G,2,3);
    addUndirectedEdge(G,2,4);
    addUndirectedEdge(G,3,2);
    addUndirectedEdge(G,3,4);
    addUndirectedEdge(G,4,1);
    addUndirectedEdge(G,4,2);
    addUndirectedEdge(G,4,3);
    
    int* output = BFS(G);
    for(int i =0; i<gridLen; i++){
        printf("%d ", output[i]);
    }

    return 0;
}


int* BFS(Graph* G) {
    int len = G->vertice_count; 
    int* visited = (int*)calloc(len, sizeof(int)); 
    int* queue = (int*)malloc(len * sizeof(int)); 
    int front = 0, rear = 0;

    queue[rear++] = 0; 
    visited[0] = 1; 

    int* result = (int*) malloc(len * sizeof(int));
    int order = 0;
    while (front < rear) {

        int current = queue[front++];

        result[order++] = current + 1;
        //printf("Visited: %d\n", current); 

        for (int i = 0; i < G->gArr[current].neighbor_count; i++) {
            int neighbor = G->gArr[current].neighbor[i];

            if (!visited[neighbor]) {
                visited[neighbor] = 1; 
                queue[rear++] = neighbor; 
            }
        }
    }

    free(queue); 
    free(visited);
    return result; 
}

Graph* initGraph(size_t vertice_count) {
    Graph* newGraph = (Graph*) malloc(sizeof(Graph));
    newGraph->vertice_count = vertice_count;
    newGraph->gArr = (V*)malloc(vertice_count * sizeof(V));

    for (size_t i = 0; i < vertice_count; i++) {
        newGraph->gArr[i].neighbor = (int*)calloc(vertice_count, sizeof(int)); 
        newGraph->gArr[i].neighbor_count = 0; 
    }

    return newGraph;
}

void addUndirectedEdge(Graph* G,int v1, int v2){
    v1 -= 1;
    v2 -= 1;
    if(isNeighbor(G, v1, v2)) return;
    G->gArr[v1].neighbor[G->gArr[v1].neighbor_count++] = v2;
    G->gArr[v2].neighbor[G->gArr[v2].neighbor_count++] = v1;
}

bool isNeighbor(Graph* G,int v1, int v2){
    for(int i=0; i<G->vertice_count; i++){
        if(G->gArr[v1].neighbor[i] == v2){
            return true;
        }
    }

    return false;
}



Queue* initQueue(size_t element_size, void(*print_data)(void*), void(*free_data)(void*)){
    Queue* queue = (Queue*) malloc(sizeof(Queue));
    if(!isPTRValid(queue, "initQueue")) return NULL;

    queue->element_size = element_size;
    queue->print_data = print_data;
    queue->free_data = free_data ? free_data : free;
    queue->front = queue->rear = NULL;
    queue->queue_size = 0;
    return queue;
}

void enqueue(Queue* q, void* data){
    if(!isPTRValid(q, "enqueue") || !isPTRValid(data, "enqueue")) return;

    Node* newNode = getNewNode(data, q->element_size);
    if(!isPTRValid(newNode, "enqueue")) return;

    if(isQueueEmpty(q)){
        q->front = q->rear = newNode;
    }
    else{
        q->rear->next = newNode;
        q->rear = newNode;
    }

    q->queue_size++;
}

void* dequeue(Queue* q){
    if(!isPTRValid(q, "dequeue")) return NULL;
    if(isQueueEmpty(q)){
        printError("Queue is empty");
        return NULL;
    }

    void* dequeueValue = malloc(q->element_size);
    // Even if malloc fails, you should still dequeue the node.
    Node* temp = q->front;
    q->front = q->front->next;

    if (isMemoryAllocate(dequeueValue, "dequeue")) {
        // Copy the data from the front node only if allocation was successful
        memcpy(dequeueValue, temp->data, q->element_size);
    }

    // Free the front node
    q->free_data(temp->data);
    free(temp);

    if (q->queue_size == 1) {
        q->rear = q->front = NULL;
    }

    q->queue_size--;

    return dequeueValue;
}

void* peekQueue(Queue* q){
    if(!isPTRValid(q, "peekQueue")) return NULL;
    if(isQueueEmpty(q)){
        printError("Queue is empty");
        return NULL;
    }

    void* peekValue = malloc(q->element_size);
    if(!isMemoryAllocate(peekValue, "peekQueue")) return NULL;
    memcpy(peekValue, q->front->data, q->element_size);

    return peekValue;
}

bool isQueueEmpty(Queue* q){
    return q->queue_size == 0;
}

void freeQueue(Queue* q){
    if(!isPTRValid(q, "freeQueue") || isQueueEmpty(q)) return;
    Node* curr = NULL;
    while(!isQueueEmpty(q)){
        curr = q->front;
        q->free_data(curr->data);
        q->front = curr->next;
        free(curr);
    }

    q->rear = q->front = NULL;
    free(q);
}

//copy the input data to Node, this way, make sure the data in stack is immutable  
Node* getNewNode(void* data, size_t size){
    if(size == 0 || !isPTRValid(data, "getNewNode")) return NULL;

    Node* newNode = (Node*) malloc(sizeof(Node));
    if(!isMemoryAllocate(newNode, "getNewNode")) return NULL;

    newNode->data = malloc(sizeof(size));
    if(!isMemoryAllocate(newNode->data, "getNewNode")) {
        free(newNode);
        return NULL;
    }

    newNode->data = memcpy(newNode->data, data, size);
    newNode->next= NULL;

    return newNode;
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