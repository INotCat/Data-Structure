#include<stdio.h>
#include"tool/error_custom.h"
#include"tool/queue_generic.h"
#include"tool/stack_generic.h"

int graph[7][7] = {
    {0,1,1,1,0,0,0},
    {1,0,1,0,0,0,0},
    {1,1,0,1,1,0,0},
    {1,0,1,0,1,0,0},
    {0,0,1,1,0,1,1},
    {0,0,0,0,1,0,0},
    {0,0,0,0,1,0,0},
};

int visited[7] = {0,0,0,0,0,0,0};

void DFS(int i){
    visited[i] = 1;
    printf("%d,", i);
    for(int j=0; j<7; j++){
        if(graph[i][j] == 1 && visited[j] == 0){
            DFS(j);
        }
    }
}

void DFS_iterate(){
    Stack* s = initStack(sizeof(int), NULL, NULL);
    int initial = 0;
    visited[initial] = 1;
    printf("%d,", initial);
    push(s, &initial);

    while(!isStackEmpty(s)){
        int node = *(int*)pop(s);
        for(int j=0; j<7; j++){
            if(graph[node][j] == 1 && visited[j] == 0){
                visited[node] = 1;
                printf("%d,", j);
                push(s, &j);
            }
        }
    }
}

void BFS(){
    Queue* q = initQueue(sizeof(int), NULL, NULL);
    int initial = 0;
    visited[initial] = 1;
    printf("%d,", initial);
    enqueue(q, &initial);

    while(!isQueueEmpty(q)){

        int node = *(int*)dequeue(q);

        for(int j=0; j<7; j++){
            if(graph[node][j] == 1 && visited[j] == 0){
                visited[j] = 1;
                printf("%d,", j);
                enqueue(q, &j);
            }
        }
    }
}

void zero(){
    int len = sizeof(visited) / sizeof(visited[0]);
    for(int i=0; i<len; i++){
        visited[i] = 0;
    }
}

int main(){
    printf("DFS_recursive:");
    DFS(0);
    printf("\n");
    zero();

    printf("DFS_iterate:");
    DFS(0);
    printf("\n");
    zero();

    printf("BFS:");
    BFS();
    printf("\n");
    zero();

    return 0;
}