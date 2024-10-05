#define IS_NULL(ptr) !(ptr)

//array-represented heap for int type data
typedef struct MaxHeap {
    int* harr;
    int capacity;
    int heap_size;
} MaxHeap;

//private funciton for internal usage
static void swap(int*,int*);
static void maxHeapify(MaxHeap* heap, int i);
static void increaseKey(MaxHeap* heap, int i, int new_val);
static void resizeHeap(MaxHeap* heap);

//public 
void insertKey(MaxHeap* heap, int k);
void deleteKey(MaxHeap* heap, int i);

int extractMax(MaxHeap* heap);
int getmax(MaxHeap* heap);

void printMaxHeap(MaxHeap* heap);

