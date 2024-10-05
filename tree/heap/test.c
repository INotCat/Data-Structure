#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"queue_generic.c"
// #include"maxheap_array.c"
void swap(void* x, void* y, size_t size){
    void* temp = malloc(size);
    memcpy(temp, x, size);
    memcpy(x, y, size);
    memcpy(y, temp, size);
}

int main(){
    // MaxHeap* maxheap = initMaxHeap(20);
    // insertKey(maxheap, 10);
    // insertKey(maxheap,20);
    // insertKey(maxheap,5);
    // insertKey(maxheap,21);
    // insertKey(maxheap,19);
    // insertKey(maxheap,4);
    // insertKey(maxheap,2);
    // insertKey(maxheap,0);
    // printf("Initial Heap:");
    // printMaxHeap(maxheap);

    // printf("After Delete:");
    // deleteKey(maxheap, 5);
    // printMaxHeap(maxheap);

    // printf("Extract:");
    // int max_extract = extractMax(maxheap);
    // printf("%d\n", max_extract);
    // printMaxHeap(maxheap);

    // printf("Peek: ");
    // int max_peek = getmax(maxheap);
    // printf("%d\n", max_peek);
    // printMaxHeap(maxheap);
    int a = 3;
    int b =100;
    // void* b = NULL;
    memcpy(&b, (void*)&a, sizeof(int));
    // swap(&a, b, sizeof(int));

    Queue* q = initQueue(sizeof(int), NULL, NULL);
    enqueue(q,&a);
    enqueue(q,&b);
    printf("a = %d\n", *(int*)dequeue(q));
    printf("q size= %d\n", q->queue_size);
    printf("b = %d\n", *(int*)dequeue(q));
    printf("q size= %d\n", q->queue_size);
}

