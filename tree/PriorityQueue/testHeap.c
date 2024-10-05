#include<string.h>
#include<stdlib.h>
#include"minheap_generic.h"

typedef struct{
    int priority;
    char* name;
} Album;

Album* createNewAlbum(const char* name, int priority){
    Album* newAlbum = (Album*) malloc(sizeof(Album));
    newAlbum->priority = priority;
    newAlbum->name = (char*) malloc(strlen(name) + 1);
    strcpy(newAlbum->name, name);
    return newAlbum;
}

int compareAlbum(void* x, void* y){
    int X = ((Album*)x)->priority;
    int Y = ((Album*)y)->priority;
    if(X > Y) return 1;
    else if (X < Y) return -1;
    else return 0;
}

void assign_priority(void* x, int value){
    ((Album*)x)->priority = value;
}

void printAlbum(void* x){
    Album* X = ((Album*)x);
    printf("Album: %s, Priority: %d", X->name, X->priority);
}

void freeAlbum(void* x){
    free(((Album*)x)->name);
}

int main(){
    Album* fearless = createNewAlbum("fearless", 10);
    Album* lover = createNewAlbum("lover", 10);
    MinHeap* minheap = initMinHeap(sizeof(Album), compareAlbum, assign_priority, printAlbum, freeAlbum);
    //printf("%zu", minheap->heap_size);
    insertKey(minheap, fearless);
    insertKey(minheap, lover);
    printMinHeap(minheap);
}