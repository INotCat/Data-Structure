#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdarg.h>
#include<string.h>
#include"tool/error_custom.h"
#include"tool/queue_generic.h"
#include"tool/stack_generic.h"
#include"minheap_generic.h"

bool isLeftChild(HeapNode* parent, HeapNode* child);
void swap(void* node1, void* node2, size_t size);
HeapNode* getNewHeapNode(MinHeap* heap,void* data);


MinHeap* initMinHeap(size_t element_size, 
                     int (*compare)(void*, void*), 
                     void (*assign_priority)(void*, int), 
                     void (*print_data)(void*), 
                     void (*free_data)(void*)){
    MinHeap* heap = (MinHeap*) malloc(sizeof(MinHeap));
    if(!isPTRValid(heap, "initMinHeap")) exit(EXIT_FAILURE);

    heap->element_size = element_size;
    heap->compare = compare;
    heap->assign_priority = assign_priority;
    heap->print_data = print_data;
    heap->free_data = free_data;
    heap->root = NULL;
    heap->heap_size = 0;

    return heap;
}

void insertKey(MinHeap* heap, void* key){
    if(!isPTRValid(heap, "inserKey") || !isPTRValid(key, "inserKey")) exit(EXIT_FAILURE);
    
    HeapNode* newNode = getNewHeapNode(heap, key);

    if(heap->heap_size == 0){
        heap->root = newNode;
        heap->heap_size++;
        return;
    }

    //BFS, level order to find the insert point
    Queue* queue = initQueue(sizeof(HeapNode*), NULL, heap->free_data);
    enqueue(queue, heap->root);

    while (sizeOfQueue(queue) > 0) {
        HeapNode* currentNode = (HeapNode*)dequeue(queue); 
        //
        if (IS_NULL(currentNode->left)) {//found the first NULL children and insert
            currentNode->left = newNode;
            newNode->parent = currentNode;
            break;//extremely important here
        } 
        else {
            enqueue(queue, currentNode->left);
        }
        
        if (IS_NULL(currentNode->right)) {
            currentNode->right = newNode;
            newNode->parent = currentNode;
            break;
        } 
        else {
            enqueue(queue, currentNode->right);
        }
    }

    heap->heap_size++;
    //after insert the newNode, we heapify the tree
    heapifyUp(heap, newNode);
    //freeQueue(queue);
    free(queue);
    queue = NULL;
}

//delete according to the key(data)
//what if exist duplicate node with same value->handle via delete recursively
void deleteKey(MinHeap* heap, void* key){
    if(!isPTRValid(heap, "deleteKey") || !isPTRValid(key, "deleteKey")) exit(EXIT_FAILURE);
    //decreaseKey would return true if decrease the target(if target exists)
    if(!decreaseKey(heap, key)) return;
    if(IS_NULL(heap->root)) exit(EXIT_FAILURE);

    extractMin(heap);
    
    //recursively delete if duplicate key is in the heap
    deleteKey(heap, key);
}

void* extractMin(MinHeap* heap){
    if(!isPTRValid(heap, "extractMin")) return NULL;

    if(heap->heap_size == 0){
        printError("Error: Heap is empty in extractMin");
        return NULL;
    }

    void* minData = malloc(heap->element_size);
    if(!isMemoryAllocate(minData, "extractMin")) return NULL;
    memcpy(minData, heap->root->data, heap->element_size);

    if(heap->heap_size == 1){
        heap->free_data(heap->root->data);
        heap->root->data = NULL;

        free(heap->root);
        heap->root = NULL;

        heap->heap_size--;
        return minData;
    }

    heap->free_data(heap->root->data);
    heap->root->data = NULL;

    //If the heap size > 1, Level order to find the last node
    Queue* queue = initQueue(sizeof(HeapNode*), NULL, NULL);//check queue malloc
    if(!isPTRValid(queue, "extractMin")) return NULL;
    enqueue(queue, heap->root);

    HeapNode* target = NULL;
    while(sizeOfQueue(queue) > 0){
        HeapNode* current = dequeue(queue);

        if(!IS_NULL(current->left)){
            enqueue(queue, current->left);
        }
        if(!IS_NULL(current->right)){
            enqueue(queue, current->right);
        }

        target = current;
    }

    //manually swap the data, since one is NULL
    heap->root->data = target->data;
    target->data = NULL;

    //Since the target->data is already NULL
    if(isLeftChild(target->parent, target)){
        target->parent->left = NULL;
    }
    else{
        target->parent->right = NULL;
    }

    free(target);
    //freeQueue(queue); //This will free the content and the queue entirly
    free(queue);// only free queue
    queue = NULL;

    heap->heap_size--;
    heapifyDown(heap, heap->root);
    return minData;
}

void* getMin(MinHeap* heap){
    if(!isPTRValid(heap, "getMin")) return NULL;

    if(heap->heap_size == 0){
        printError("Error: heap is empty in getMin");
        return NULL;
    }

    void* minData = malloc(heap->element_size);
    if(!isMemoryAllocate(minData, "extractMin")) return NULL;
    
    memcpy(minData, heap->root->data, heap->element_size);
    return minData;
}

void heapifyUp(MinHeap* heap, HeapNode* node){
    //heap and node has been checked valid inside the calling function
    HeapNode* current = node;
    //until root (root->parent = NULL)
    //if priority of data: current < parent swap(current,parent)
    while(current->parent != NULL && (heap->compare(current->data, current->parent->data) < 0)){
        swap(current->data, current->parent->data, heap->element_size);
        current = current->parent;
    }

    if(current != node){
        heapifyUp(heap, current);
    }
}

void heapifyDown(MinHeap* heap, HeapNode* node){
    HeapNode* current = node;
    HeapNode* left = node->left;
    HeapNode* right = node->right;
    // if left < cur
    if(left != NULL && (heap->compare(left, current) < 0)){
        current = left;
    }
    if(right != NULL && (heap->compare(right, current) < 0)){
        current = right;
    }
    //if address not the same
    if(current != node){
        swap(current->data, node->data, heap->element_size);
        heapifyDown(heap, current);
    }
}

bool decreaseKey(MinHeap* heap, void* key){
    Queue* queue = (Queue*)initQueue(sizeof(HeapNode*), NULL, NULL);
    if(!isMemoryAllocate(queue, "decreaseKey")) return false;

    enqueue(queue, heap->root);
    HeapNode* target = NULL;
    bool found = false;

    while(sizeOfQueue(queue) != 0){
        HeapNode* current = dequeue(queue);
        
        if(current->left != NULL){
            //if found then stop level order traverse
            if(heap->compare(current->left->data, key) == 0){
                target = current->left;
                found = true;
                break;
            }
            else{
                enqueue(queue, current->left);
            }
        }
    
        if(current->right != NULL){
            if(heap->compare(current->right->data, key) == 0){
                target = current->right;
                found = true;
                break;
            }
            else{
                enqueue(queue, current->right);
            }
        }
    }

    // user must define assigned value function in initheap, then the data's member(maybe prority) can be decrese to the lowest
    //heap->assign(key);
    if(target != NULL){
        heap->assign_priority(target->data, INT16_MIN);
        heapifyUp(heap, target);
    }
    
    return found;
}

HeapNode* getNewHeapNode(MinHeap* heap,void* data){
    
    if(!isPTRValid(heap, "getNewHeapNode") || !isPTRValid(data, "getNewHeapNode")) return NULL;

    HeapNode* newNode = (HeapNode*) malloc(sizeof(HeapNode));
    if(!isMemoryAllocate(newNode, "getNewHeapNode")) return NULL;

    newNode->data = malloc(heap->element_size);
    if(!isMemoryAllocate(newNode->data, "getNewHeapNode")){
        free(newNode);
        newNode = NULL;
        return NULL;
    }
        

    memcpy(newNode->data, data, heap->element_size);

    newNode->left = newNode->right = newNode->parent =  NULL;
    return newNode;
}

void swap(void* node1, void* node2, size_t size){
    if(!isPTRValid(node1, "swap") && !isPTRValid(node2, "swap") && size != 0) return;

    void* temp = malloc(size);
    if(!isMemoryAllocate(temp, "swap")) return;

    memcpy(temp, node1, size);
    memcpy(node1, node2, size);
    memcpy(node2, temp, size);
    free(temp);
    temp = NULL;
}

/**
 * Checks if the given child node is the left child of the parent node.
 *
 * @param parent Pointer to the parent node.
 * @param child Pointer to the child node to check.
 * @return true if child is the left child of parent; false otherwise.
 */
bool isLeftChild(HeapNode* parent, HeapNode* child) {
    // Ensure parent is not NULL and check if child is the left child
    return parent != NULL && parent->left == child;
}

void printMinHeap(MinHeap* heap){
    if(!isPTRValid(heap->print_data, "printMinHeap")) exit(EXIT_FAILURE);

    Queue* queue = initQueue(sizeof(HeapNode*), NULL, NULL);
    enqueue(queue, heap->root);
    
    while(sizeOfQueue(queue) > 0){
        HeapNode* current = dequeue(queue);
        heap->print_data(current);

        if(!IS_NULL(current->left)){
            enqueue(queue, current->left);
        }
        if(!IS_NULL(current->right)){
            enqueue(queue, current->right);
        }

        current = current->left;
    }
}

void freeHeap(MinHeap* heap) {
    if(!isPTRValid(heap, "freeHeap") || !isPTRValid(heap->root, "freeHeap")) exit(EXIT_FAILURE);

    Stack* stack = initStack(sizeof(HeapNode*), NULL, NULL);
    HeapNode* current = heap->root;
    HeapNode* lastVisited = NULL;

    while(current != NULL || !isStackEmpty(stack)){
        if(!IS_NULL(current)){
            push(stack, current);
            current = current->left;
        }
        else{
            HeapNode* peekNode = peekStack(stack);
            if(!IS_NULL(peekNode->right) || peekNode->right != lastVisited){
                current = peekNode->right;
            }
            else{
                heap->free_data(peekNode->data);
                lastVisited = pop(stack);
            }
        }

    }

    free(stack);
    stack = NULL;
    
    free(heap);
    heap = NULL;
}