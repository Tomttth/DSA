#include<stdio.h>
#include<stdlib.h>
struct MinHeap
{
    int *arr;
    int capacity;
    int size;
};
struct MinHeap* createMinHeap(int capacity)
{
    struct MinHeap* heap =(struct MinHeap*)malloc(sizeof(struct MinHeap));
    heap->capacity = capacity;
    heap->size = 0;
    heap->arr =(int*)malloc(capacity*sizeof(int));
    return heap;
}
void swap(int *x,int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}
int parent(int i)
{
    return (i - 1)/2;
}
int leftChild(int i)
{
    return 2*i + 1;
}
int rightChild(int i)
{
    return 2*i + 2;
}
void insert(struct MinHeap* heap, int key)
{
  if(heap->size == heap->capacity)
  {
    printf("\nHeap Overflow. Cannot insert key %d",key);
    return;
  }
  int i = heap->size++;
  heap->arr[i] = key;
  while(i != 0 && heap->arr[parent(i)]>heap->arr[i])
  {
    swap(&heap->arr[i],&heap->arr[parent(i)]);
    i = parent(i);
  }
}
void minHeapify(struct MinHeap* heap,int i)
{
    int smallest = i;
    int left = leftChild(i);
    int right = rightChild(i);
    if(left < heap->size && heap->arr[left] < heap->arr[smallest])
    {
        smallest = left;
    }
    if(right < heap->size && heap->arr[right] < heap->arr[smallest])
    {
        smallest = right;
    }
    if(smallest != i)
    {
        swap(&heap->arr[i],&heap->arr[smallest]);
        minHeapify(heap,smallest);
    }
}
int extractMin(struct MinHeap * heap)
{
    if(heap->size<=0)
    {
        return __INT_MAX__;
    }
    if(heap->size == 1)
    {
        return heap->arr[--heap->size];
    }
    int root = heap->arr[0];
    heap->arr[0] = heap->arr[--heap->size];
    minHeapify(heap,0);
    return root;
}
int getMin(struct MinHeap *heap)
{
    if (heap->size <= 0) {
        return __INT_MAX__; 
    }
    return heap->arr[0];
}
void deleteElement(struct MinHeap * heap,int key)
{
    int index = -1;
    for(int i = 0;i<heap->size;i++)
    {
        if(heap->arr[i] == key)
        {
            index = i;
            break;
        }
    }
    if(index == -1)
    {
        printf("\nElement %d not found in the heap",key);
        return;
    }
    heap->arr[index] = heap->arr[heap->size-1];
    heap->size --;
    minHeapify(heap,index);
}
void displayHeap(struct MinHeap *heap)
{
    printf("\nMinHeap: ");
    for(int i = 0; i < heap->size; i++)
    {
        printf("%d ",heap->arr[i]);
    }
    printf("\n");
}
void freeMinHeap(struct MinHeap *heap)
{
  free(heap->arr);
  free(heap);
}
int main()
{  
    struct MinHeap *heap =createMinHeap(10);
    int choice = 0;
    do
    {
    printf("\n1.Insertion");
    printf("\n2.Extract Minimum");
    printf("\n3.Display");
    printf("\n4.Find Minimum");
    printf("\n5.Delete");
    printf("\n6.Exit");
    printf("\nEnter your choice: ");
    scanf("%d",&choice);
    switch(choice){
        case 1:{
            int a = 0;
            printf("\nEnter the element you want to insert: ");
            scanf("%d",&a);
            insert(heap,a);
            break;
        }
        case 2:{
            int min = extractMin(heap);
            if(min == __INT_MAX__){
                printf("\nThe heap is empty\n");
            }
            else
            {
                printf("Extracting the minimum element of heap %d",min);
            }
            
            break;
        }
        case 3:{
            printf("\nThe contents of MinHeap: ");
            displayHeap(heap);
            break;
        }
        case 4:{
            int min = getMin(heap);
            if(min == __INT_MAX__){
                printf("\nThe heap is empty\n");
            }
            else
            {
                printf("\nThe minumum element of heap is %d\n",min);
            }
            break;
        }
        case 5:{
            int key;
            printf("\nEnter the element you want to delete: ");
            scanf("%d",&key);
            deleteElement(heap,key);
            break;
        }
        case 6:{
            printf("\nExiting...");
            break;
        }
        default:{
            printf("\nYou have entered invalid choice");
        }
    }

    } while (choice != 6);
    freeMinHeap(heap);
    return 0;
    
}