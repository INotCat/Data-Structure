#include<stdio.h>
#include "stack_array.h"
#include<string.h>
int isPair(char p1, char p2){
    return (p1 == '(' && p2 == ')') 
           || (p1 == '[' && p2 == ']') 
           || (p1 == '{' && p2 == '}');

}

int isBalancedParenthesis(const char* textBuffer){
    Stack stack;
    initStack(&stack, 50);

    //char textBuffer[] = "{[(10+1)*5]-3/2}";
    int textLen = strlen(textBuffer);
    //int textLen = sizeof(textBuffer)/sizeof(char);

    char poppedValue;
    int balanced = 1;//set default flag as true for balance

    for(int i=0; i<textLen; i++){
        if(textBuffer[i] == '(' || textBuffer[i] == '[' || textBuffer[i] == '{' ){
            push(&stack, textBuffer[i]);
        }
            
        else if(textBuffer[i] == ')' || textBuffer[i] == ']' || textBuffer[i] == '}'){
            if(pop(&stack, &poppedValue) == -1 || !isPair(poppedValue, textBuffer[i])){
                balanced = 0;
                break;
            }
        }
    }

    if(balanced && isEmpty(&stack)){
        printf("Balanced\n");
        return 0;
    }
    else{
        printf("Unbalanced\n");
        return -1;
    }
}


int main(){
    //test parenthesis
    isBalancedParenthesis("{[(10+1)*5]-3/2}");

    //test merge
    Stack *s1;
    Stack *s2;
    initStack(s1,2);
    push(s1, 'a');

    initStack(s2, 20);
    for(int i=0; i<10; i++){
        push(s2, 'b');
    }

    merge(s1,s2);
    printf("size of stack:%d, size of capacity:%d\n", size(s1), s1->capacity);
    displayStack(s1);
    return 0;
}

