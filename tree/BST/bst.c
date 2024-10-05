#include<stdio.h>
#include"stack/stack_generic.h"
#include"queue/queue_generic.h"
typedef struct Node{
    int data;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct BST{
    struct Node* root;
} BST;

Node* getNode(int data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
}


void copy(){

}

void isSame(){

}

void isBST(){

}

void isIsomorphic(){

}


/// @iterative version
void preOrder(Node* root){
    if(root == NULL) return;

    Stack* stack = initStack(sizeof(Node*), NULL, NULL);
    push(stack, root);

    while (!isEmpty(stack)){
        Node* node = (Node*)pop(stack);
        printf("%d", node->data);

        if(node->right != NULL) push(stack, node->right);
        if(node->left != NULL) push(stack, node->left);
    }
}

void inOrder(Node* root){
    if(root == NULL) return;

    Stack* stack = initStack(sizeof(Node*), NULL, NULL);
    Node* curr = root;

    while(!isEmpty(stack) || curr != NULL){

        while(curr != NULL){
            push(stack, curr);
            curr = curr->left;
        }

        curr = pop(stack);
        printf("%d", curr->data);
        curr = curr->right;
    }
}

void postOrder(Node* root){
    if(root == NULL) return;
    
    Stack* stack = initStack(sizeof(Node*), NULL, NULL);
    Node* curr = root;
    Node* lastVisited = NULL;

    while(curr != NULL || !isEmpty(stack)){
        if(curr != NULL){
            push(stack, curr);
            curr = curr->left;
        }
        else{
            Node* peekNode = peek(stack);
            if(curr->right != NULL && curr->right != peekNode){
                curr = curr->right;
            }
            else{
                printf("%c", curr->data);
                lastVisited = pop(stack);
            }
        }
    }
}

// void levelOrder(Node* root){
//     if(root == NULL) return;
//     Queue queue = initQueue(sizeof(Node*), NULL, NULL);
//     push(queue, root);

//     while(!isEmpty(queue)){
//         Node* current = peek(queue);
//         printf("%c", current->data);

//         if(current->left != NULL){
//             push(queue, current->left);
//         }
//         if(current->right != NULL){
//             push(queue, current->right);
//         }
//         pop(queue);
//     }
// }

/// @given 2 array of Post/In or Pre/In
void reconstructBST(){

}