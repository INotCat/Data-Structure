#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct TreeNode{
    int id;
    struct TreeNode* parent;
    struct TreeNode** children;
    int childCount;
} TreeNode;

TreeNode* getTreeNode(int id, TreeNode* parent);
TreeNode* rootTree(int** graph, int* graphSizes, int rootId);
TreeNode* buildTree(int** graph, int* graphSizes, TreeNode* node, TreeNode* parent);




TreeNode* getTreeNode(int id, TreeNode* parent){
    TreeNode* newNode = (TreeNode*) malloc(sizeof(TreeNode));
    if(newNode == NULL) return NULL;
    newNode->id = id;
    newNode->parent = parent;
    newNode->children = NULL;
    newNode->childCount = 0;
    return newNode;
}

TreeNode* rootTree(int** graph, int* graphSizes, int rootId){
    TreeNode* root = getTreeNode(rootId, NULL);
    return buildTree(graph, graphSizes, root, NULL);
}

TreeNode* buildTree(int** graph, int* graphSizes, TreeNode* node, TreeNode* parent){
    for(int i=0; i<graphSizes[node->id]; i++){
        int childId = graph[node->id][i];

        if(parent && childId == parent->id ){
            continue;
        }

        TreeNode* child = getTreeNode(childId, node);

        node->childCount++;
        node->children = (TreeNode**) realloc(node->children, node->childCount* sizeof(TreeNode*));
        node->children[node->childCount - 1] = child;
    
        buildTree(graph, graphSizes, child, node);
    }

    return node;
}



// Utility function to print the tree (for testing)
void printTree(TreeNode* node, int level) {
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    printf("Node %d\n", node->id);

    for (int i = 0; i < node->childCount; i++) {
        printTree(node->children[i], level + 1);
    }
}

// Free the memory allocated for the tree
void freeTree(TreeNode* node) {
    for (int i = 0; i < node->childCount; i++) {
        freeTree(node->children[i]);
    }
    free(node->children);
    free(node);
}

int main() {
    // Example graph represented as an adjacency list
    int graphSize = 5;

    int graph0[] = {1, 2};
    int graph1[] = {0, 3, 4};
    int graph2[] = {0};
    int graph3[] = {1};
    int graph4[] = {1};

    int* graph[] = {graph0, graph1, graph2, graph3, graph4};
    int graphSizes[] = {2, 3, 1, 1, 1};  // Sizes of each adjacency list

    // Build the tree rooted at node 0
    TreeNode* root = rootTree(graph, graphSizes, 5);

    // Print the tree
    printTree(root, 0);

    // Free the allocated memory
    freeTree(root);

    return 0;
}