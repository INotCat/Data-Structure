#include"deque_generic.c"

int main(){
    Deque* deque = initDeque(sizeof(int), NULL, NULL);
    int a = 2;
    frontPush(deque, &a);
    int p = *(int*)frontPeek(deque);
    printf("%d", p);
    printf("%ld",size(deque));
    frontPop(deque);
    printf("%ld",size(deque));
}