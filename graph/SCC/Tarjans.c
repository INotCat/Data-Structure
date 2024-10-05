#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define UNVISITED -1

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Function prototypes
Node* createNode(int v);
void addEdge(Node** graph, int from, int to);
void tarjanSCC(Node** graph, int n);
void dfs(int at, int* ids, int* low, bool* visited, int* stack, int* onStack, Node** graph, int* sccs, int* id, int* sccCount, int* stackIndex);

// Creates a new adjacency list node
Node* createNode(int v) {
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Adds an edge to the directed graph
void addEdge(Node** graph, int from, int to) {
    Node* newNode = createNode(to);
    newNode->next = graph[from];
    graph[from] = newNode;
}

// Main Tarjan's algorithm function
void tarjanSCC(Node** graph, int n) {
    int* ids = (int*)malloc(n * sizeof(int));
    int* low = (int*)malloc(n * sizeof(int));
    int* sccs = (int*)malloc(n * sizeof(int));
    bool* visited = (bool*)malloc(n * sizeof(bool));
    int* stack = (int*)malloc(n * sizeof(int));
    int* onStack = (int*)malloc(n * sizeof(int));

    int sccCount = 0, id = 0, stackIndex = 0;

    for (int i = 0; i < n; i++) {
        ids[i] = UNVISITED;
        low[i] = 0;
        sccs[i] = 0;
        visited[i] = false;
        onStack[i] = false;
    }

    for (int i = 0; i < n; i++) {
        if (ids[i] == UNVISITED) {
            dfs(i, ids, low, visited, stack, onStack, graph, sccs, &id, &sccCount, &stackIndex);
        }
    }

    printf("Number of Strongly Connected Components: %d\n", sccCount);
    // Display SCCs (optional: customize as needed)
    for (int i = 0; i < n; i++) {
        printf("Node %d is in SCC %d\n", i, sccs[i]);
    }

    // Free allocated memory
    free(ids);
    free(low);
    free(sccs);
    free(visited);
    free(stack);
    free(onStack);
}

// Recursive DFS function
void dfs(int at, int* ids, int* low, bool* visited, int* stack, int* onStack, Node** graph, int* sccs, int* id, int* sccCount, int* stackIndex) {
    ids[at] = low[at] = (*id)++;
    stack[(*stackIndex)++] = at;
    onStack[at] = true;

    Node* adjList = graph[at];
    while (adjList != NULL) {
        int to = adjList->vertex;
        if (ids[to] == UNVISITED) {
            dfs(to, ids, low, visited, stack, onStack, graph, sccs, id, sccCount, stackIndex);
        }
        if (onStack[to]) {
            low[at] = (low[at] < low[to]) ? low[at] : low[to];
        }
        adjList = adjList->next;
    }

    // Found a root node, start a new SCC
    if (ids[at] == low[at]) {
        int node;
        do {
            node = stack[--(*stackIndex)];
            onStack[node] = false;
            sccs[node] = *sccCount;
        } while (node != at);
        (*sccCount)++;
    }
}

// Main function
int main() {
    int n = 8;
    Node** graph = (Node**)malloc(n * sizeof(Node*));
    for (int i = 0; i < n; i++) {
        graph[i] = NULL;
    }

    addEdge(graph, 6, 0);
    addEdge(graph, 6, 2);
    addEdge(graph, 3, 4);
    addEdge(graph, 6, 4);
    addEdge(graph, 2, 0);
    addEdge(graph, 0, 1);
    addEdge(graph, 4, 5);
    addEdge(graph, 5, 6);
    addEdge(graph, 3, 7);
    addEdge(graph, 7, 5);
    addEdge(graph, 1, 2);
    addEdge(graph, 7, 3);
    addEdge(graph, 5, 0);

    tarjanSCC(graph, n);

    // Free the graph memory
    for (int i = 0; i < n; i++) {
        Node* current = graph[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph);

    return 0;
}
