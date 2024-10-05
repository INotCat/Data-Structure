#include"stack_generic.c"
typedef struct {
    char* CatName;
    int CatAge;
} CatInfo;


void printCatInfo(void* data){
    printf("[StudentName: %s,", ((CatInfo*)data)->CatName);
    printf("StudentAge: %d] ->", ((CatInfo*)data)->CatAge);
}


void freeCatInfo(void* data){
    if(IS_NULL(data)) return;
    CatInfo* cat = (CatInfo*)data;
    free(cat->CatName); 
    free(cat);  
    cat == NULL;
}

CatInfo* adoptCat(const char* name, int age) {
    CatInfo* cat = (CatInfo*)malloc(sizeof(CatInfo));
    if (!cat) return NULL; 
    cat->CatName = strdup(name);
    if (!cat->CatName) { 
        free(cat);
        cat = NULL;
        return NULL;
    }
    cat->CatAge = age;
    return cat;
}

int main(){
    Stack stack;

    CatInfo* Cat1 = adoptCat("Vanilla", 10);
    CatInfo* Cat2 = adoptCat("Sky", 20);
    CatInfo* Cat3 = adoptCat("ButterQ", 30);
    CatInfo* Cat4 = adoptCat("Capybara", 40);
    CatInfo* Cat5 = adoptCat("Stupidolphin",50);

    initStack(&stack, sizeof(CatInfo), printCatInfo, freeCatInfo);
    printf("Push start\n");
    push(&stack, Cat1);
    push(&stack, Cat2);
    push(&stack, Cat3);
    push(&stack, Cat4);
    push(&stack, Cat5);
    printStack(&stack);

    printf("\n\n\n");
    printf("Peek start\n");
    CatInfo topValue;
    peek(&stack, &topValue); printCatInfo(&topValue);
    peek(&stack, &topValue); printCatInfo(&topValue);
    peek(&stack, &topValue); printCatInfo(&topValue);
    peek(&stack, &topValue); printCatInfo(&topValue);
    peek(&stack, &topValue); printCatInfo(&topValue);
    printStack(&stack);

    printf("\n\n\n");
    printf("Pop start\n");
    CatInfo poppedValue;
    pop(&stack, &poppedValue);
    pop(&stack, &poppedValue);
    pop(&stack, &poppedValue);
    pop(&stack, &poppedValue);
    printf("popping is done\n\n");
    printStack(&stack);
}