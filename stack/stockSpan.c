#include"stack_generic.c"
// Stock Span problem is to calculate the span of the stock’s price for all N days.

// Input: N = 7, price[] = [100 80 60 70 60 75 85]
// Output: 1 1 1 2 1 4 6
// Explination: take 75 as an example, 75<=75 and 60<=75 70<=75(lower and equall)
//, so the span is 4 include the currrent one
void stockSpan(int* input, int len){
    Stack* stack;
    initStack(&stack, sizeof(int), NULL, NULL);

    
}

int main(){
    int input[] = {100, 80, 60, 70, 60, 75, 85};
    int len = sizeof(input)/sizeof(int);
    stockSpan(input, len);
}