#ifndef MINHEAP_GENERIC_H
    #define MINHEAP_GENERIC_H

    #include<stdio.h>
    #include<stdbool.h>
    #define IS_NULL(ptr) !(ptr)
    //generic minHeap

    typedef struct  HeapNode{
        void* data;
        struct HeapNode* left;
        struct HeapNode* right;
        struct HeapNode* parent;
    } HeapNode;

    typedef struct MinHeap {
        size_t heap_size;
        size_t element_size;
        HeapNode* root;
        int (*compare)(void* node1, void* node2);//compare priority value inside data
        void (*assign_priority)(void*, int);
        void (*print_data)(void*);
        void (*free_data)(void*);
    } MinHeap;

    //public
    MinHeap* initMinHeap(size_t element_size, 
                        int (*compare)(void*, void*), 
                        void (*assign_priority)(void*, int), 
                        void (*print_data)(void*), 
                        void (*free_data)(void*));


    void insertKey(MinHeap* heap, void* key);
    void deleteKey(MinHeap* heap, void* key);

    void* extractMin(MinHeap* heap);
    void* getMin(MinHeap* heap);

    void printMinHeap(MinHeap* heap);
    void freeHeap(MinHeap* heap);

    void heapifyUp(MinHeap* heap, HeapNode* node);
    void heapifyDown(MinHeap* heap, HeapNode* node);
    bool decreaseKey(MinHeap* heap, void* key);
#endif