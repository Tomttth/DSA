#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

struct MaxHeap
{
    int *array;
    int capacity;
    int size;
};
struct MaxHeap *createMaxHeap(int capacity)
{
    struct MaxHeap *heap = (struct MaxHeap *)malloc(sizeof(struct MaxHeap));
    heap->capacity = capacity;
    heap->size = 0;
    heap->array = (int *)malloc(capacity * sizeof(int));
    return heap;
}
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}
int parent(int i)
{
    return (i - 1) / 2;
}
int leftChild(int i)
{
    return (2 * i + 1);
}
int rightChild(int i)
{
    return (2 * i + 2);
}
void resizeHeap(struct MaxHeap *heap)
{
    heap->capacity *= 2;
    heap->array = (int *)realloc(heap->array, heap->capacity * sizeof(int));
    if (!heap->array)
    {
        printf("\nMemory Allocation Failed");
        exit(EXIT_FAILURE);
    }
}
void insert(struct MaxHeap *heap, int data)
{
    if (heap->size == heap->capacity)
    {
        printf("\nResizing heap to double capacity");
        resizeHeap(heap);
    }
    int i = heap->size++;
    heap->array[i] = data;
    while (i != 0 && heap->array[parent(i)] < heap->array[i])
    {
        swap(&heap->array[parent(i)], &heap->array[i]);
        i = parent(i);
    }
}
void display(struct MaxHeap *heap)
{
    for (int i = 0; i < heap->size; i++)
    {
        printf("%d ", heap->array[i]);
    }
    printf("\n");
}
void maxHeapify(struct MaxHeap *heap, int i)
{
    while (leftChild(i) < heap->size)
    {
        int largest = i;
        int left = leftChild(i);
        int right = rightChild(i);
        if (left < heap->size && heap->array[left] > heap->array[largest])
        {
            largest = left;
        }
        if (right < heap->size && heap->array[right] > heap->array[largest])
        {
            largest = right;
        }
        if (largest != i)
        {
            swap(&heap->array[i], &heap->array[largest]);
            i = largest;
        }
        else
        {
            break;
        }
    }
}
void delete(struct MaxHeap *heap, int data)
{
    if (heap->size == 0)
    {
        printf("\nHeap Underflow");
        return;
    }
    if (heap->size == 1)
    {
        printf("\nDeleting %d from heap", heap->array[--heap->size]);
        return;
    }
    else
    {
        int target = -1;
        for (int i = 0; i < heap->size; i++)
        {
            if (heap->array[i] == data)
            {
                target = i;
                break;
            }
        }
        if (target == -1)
        {
            printf("\nThe element is not found in the maximum heap");
            return;
        }
        printf("\nThe element %d is successfully deleted", heap->array[target]);
        heap->array[target] = heap->array[--heap->size];
        maxHeapify(heap, target);
    }
}
void findMax(struct MaxHeap *heap)
{
    if (heap->size == 0)
    {
        printf("\nHeap Underflow");
        return;
    }
    printf("\nThe maximum element in heap is: %d", heap->array[0]);
}
void extractMax(struct MaxHeap *heap)
{
    if (heap->size == 0)
    {
        printf("\nHeap Underflow");
        return;
    }
    printf("\nExtracting maximum element %d from heap", heap->array[0]);
    heap->array[0] = heap->array[--heap->size];
    maxHeapify(heap, 0);
}
void freeheap(struct MaxHeap **heap)
{
    free((*heap)->array);
    (*heap)->array = NULL;
    free(*heap);
    *heap = NULL;
}
int main()
{
    int choice = 0, data = 0;
    struct MaxHeap *heap = createMaxHeap(100);
    do
    {
        printf("\n1.Insertion");
        printf("\n2.Deletion");
        printf("\n3.Find Max");
        printf("\n4.Extract Max");
        printf("\n5.Display");
        printf("\n6.Exit");
        printf("\nEnter your choice: ");
        if (scanf("%d", &choice) != 1)
        {

            printf("\nYou have entered an non-integer");
            choice = 0;
            while (getchar() != '\n')
                ;
            continue;
        }
        switch (choice)
        {
        case 1:
        {
            int a = 0;
            printf("\nEnter the value to be inserted: ");
            if (scanf("%d", &a) != 1)
            {
                printf("\nYou have entered an non-integer");
                while (getchar() != '\n')
                    ;
            }
            else
            {
                insert(heap, a);
            }
            break;
        }
        case 2:
        {
            int a = 0;
            printf("\nEnter the element to be deleted: ");
            if (scanf("%d", &a) != 1)
            {
                printf("\nYou have entered an non-integer element");
                while (getchar() != '\n')
                    ;
            }
            else
            {
                delete (heap, a);
            }
            break;
        }
        case 3:
        {
            findMax(heap);
            break;
        }
        case 4:
        {
            extractMax(heap);
            break;
        }
        case 5:
        {
            printf("\nThe contents of maximum heap are displayed below: ");
            display(heap);
            break;
        }
        case 6:
        {
            printf("\nThanks for using the max heap program");
            break;
        }
        default:
        {
            printf("\nYou have entered an invalid choice");
        }
        }

    } while (choice != 6);
    freeheap(&heap);
    return 0;
}