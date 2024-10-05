#include"stack_generic.c"

void printIntArr(int* arr, int len) {
    for(int i = 0; i < len; i++) {
        printf("%d, ", arr[i]);
    }
    printf("\n");
}

/** NGL Nearest Greater to Left
*   array  = {4, 10, 5, 8, 20, 15, 3, 12}
*   answer = {-1, -1, 5, 10, -1, 20, 15, 15}
**/
void NGL(){
    
}

/** NGR Nearest Greater to Right
*   array  = {4, 10, 5, 8, 20, 15, 3, 12}
*   answer = {10, 20, 8, 20, -1, -1, 12, -1}
**/
void NGR(){

}

/** NSL Nearest Smaller to Left
*   array  = {4, 10, 5, 8, 20, 15, 3, 12}
*   answer = {-1, 4, 4, 5, 8, 8, -1, 3}
**/
void NSL(int input[], int len){
    Stack stack;
    initStack(&stack, sizeof(int), NULL, NULL);
    int output[len];
    int topValue;
    int poppedValue;
    
    for(int i=0; i<len; i++){
        while(!isEmpty(&stack) && (peek(&stack, &topValue), topValue >= input[i])){
            pop(&stack, &poppedValue);
        }

        if(isEmpty(&stack)){
            output[i] = -1;
        }
        else{
            output[i] = topValue;
        }

        push(&stack, &input[i]);
    }

    printIntArr(output, len);
}



/** NSR Nearest Smaller to Right
*   array  = {4, 10, 5, 8, 20, 15, 3, 12}
*   answer = {3, 5, 3, 3, 15, 3, -1, -1}
**/
void NSR(){
    
}




int main(){
    int input[] = {4, 10, 5, 8, 20, 15, 3, 12};
    int len = sizeof(input)/sizeof(int);
    NSL(input, len);


    return 0;
}