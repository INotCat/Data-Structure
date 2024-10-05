#include"deque_generic.c"

int* slidingWindowMax(int* arr, int len, int K) {
    Deque* deque = (Deque*)malloc(sizeof(Deque));
    deque = initDeque(sizeof(int), NULL, NULL);
    int* result = (int*)malloc((len-K+1) * sizeof(int));
    int resultIndex = 0;

    for (int i = 0; i < len; i++) {
        // Remove elements that are out of this window
        if (!isEmpty(deque) && *(int*)frontPeek(deque) <= i - K) {
            frontPop(deque);
        }

        // Remove all elements smaller than the current element from the rear
        while (!isEmpty(deque) && arr[*(int*)rearPeek(deque)] <= arr[i]) {
            rearPop(deque);
        }

        int* index = (int*)malloc(sizeof(int));  // Allocate memory for index
        *index = i;  // Store the current index value
        printf("%d", *index);
        rearPush(deque, index);
        printf("%d", *(int*)rearPeek(deque));

        // Print the maximum for the current window
        if (i >= K - 1) {
            result[resultIndex] = arr[*(int*)frontPeek(deque)];
            resultIndex++;
        }
    }
    freeDeque(deque);
    return result;
}

int main(){
    int arr[] = {8, 5, 10, 7, 9, 4, 15, 12, 90, 13};
    int K = 4 ;
    // int arr[] = {20, 10, 30};
    // int K = 1;
    int len = sizeof(arr)/sizeof(int);
    Deque* deque = (Deque*)malloc(sizeof(Deque));
    deque = initDeque(sizeof(int), NULL, NULL);
    int* result = slidingWindowMax(arr, len, K);
    for(int i=0; i<len-K; i++){
        printf("%d,",result[i]);
    }
}