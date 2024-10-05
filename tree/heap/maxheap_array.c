#include<stdio.h>
#include<stdlib.h>
#include"maxheap_array.h"

MaxHeap* initMaxHeap(int capacity){
    MaxHeap* heap = (MaxHeap*) malloc(sizeof(MaxHeap));
    heap->harr = (int*)malloc( capacity *sizeof(int));

    if(IS_NULL(heap) || IS_NULL(heap->harr)){
        printf("Fail to allocate memory in initMaxHeap function");
        return NULL;
    }

    heap->heap_size = 0;
    heap->capacity = capacity;
    return heap;
}

void insertKey(MaxHeap* heap, int k){
    if(IS_NULL(heap)) return;
    if(heap->heap_size == heap->capacity){
        resizeHeap(heap);
    }

    heap->heap_size++;
    int i = heap->heap_size - 1;
    heap->harr[i] = k;

    // Handle the max heap property if it is violated
    //worst case :exchange the index until to the root 
    //average case :exchange until encounter a parent larger than it
    while(i!=0 && (heap->harr[(i-1)/2] < heap->harr[i])){
        swap(&(heap->harr[(i-1)/2]), &(heap->harr[i]));
        // Move up to the parent's position
        i = (i-1)/ 2;
    }
}


int extractMax(MaxHeap* heap){
    if(IS_NULL(heap) || heap->heap_size == 0){
        return INT16_MIN;
    }
    if(heap->heap_size == 1){
        heap->heap_size--;
        return heap->harr[0];
    }

    int root = heap->harr[0];
    //the last element to make up the absent of the root
    heap->harr[0] = heap->harr[heap->heap_size - 1];
    heap->heap_size--;

    maxHeapify(heap, 0);

    return root;
}

//delete according to "index" not value
void deleteKey(MaxHeap* heap, int i){
    increaseKey(heap, i, INT16_MAX);

    //the index we want to delete has become the largest, so just extract it.
    extractMax(heap);
}

static void maxHeapify(MaxHeap* heap, int i){
    int largest = i;
    int left = 2 * i + 1;//left is odd
    int right = 2 * i + 2;//right is even

    if(left < heap->heap_size && heap->harr[left] > heap->harr[largest]){
        largest = left;
    }
    if(right < heap->heap_size && heap->harr[right] > heap->harr[largest]){
        largest = right;
    }

    if(largest != i){
        swap(&(heap->harr[i]), &(heap->harr[largest]));
        maxHeapify(heap, largest);
    }
}

static void increaseKey(MaxHeap* heap, int i, int new_val){
    heap->harr[i] = new_val;

    //bubble up
    while(i!=0 && heap->harr[(i-1)/2] < heap->harr[i]){
        swap(&(heap->harr[(i-1)/2]), &(heap->harr[i]));
        i = (i-1)/2;
    }
}

int getmax(MaxHeap* heap){
    if(IS_NULL(heap) || heap->heap_size == 0) return INT16_MIN;
    return heap->harr[0];
}

static void resizeHeap(MaxHeap* heap){
    if(IS_NULL(heap)) return;
    heap->capacity *= 2;
    heap->harr = (int*)realloc(heap->harr, heap->capacity * sizeof(int));
    if(IS_NULL(heap->harr)){
        printf("Heap resize failed");
        exit(1);
    }
}

void printMaxHeap(MaxHeap* heap){
    if(IS_NULL(heap)) return;
    for(int i=0; i<heap->heap_size; i++){
        printf("%d,",heap->harr[i]);
    }
    printf("\n");
}

static void swap(int* x, int* y){
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}