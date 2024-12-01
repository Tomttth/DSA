#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define DEFAULT_CAPACITY 16

typedef struct
{
    int *elements;
    int size;
    int capacity;
} IntervalHeap;

IntervalHeap *createIntervalHeap();
void resizeHeap(IntervalHeap *heap);
void swap(int *a, int *b);
void fixUpMin(IntervalHeap *heap, int index);
void fixUpMax(IntervalHeap *heap, int index);
void fixDownMin(IntervalHeap *heap, int index);
void fixDownMax(IntervalHeap *heap, int index);
void insertElement(IntervalHeap *heap, int value);
int findMin(IntervalHeap *heap);
int findMax(IntervalHeap *heap);
void deleteMin(IntervalHeap *heap);
void deleteMax(IntervalHeap *heap);
void displayHeap(IntervalHeap *heap);
void freeHeap(IntervalHeap *heap);

IntervalHeap *createIntervalHeap()
{
    IntervalHeap *heap = (IntervalHeap *)malloc(sizeof(IntervalHeap));
    if (!heap)
    {
        fprintf(stderr, "Memeory Allocation failed for Heap");
        exit(1);
    }
    heap->elements = (int *)malloc(DEFAULT_CAPACITY * sizeof(int));
    if (!heap->elements)
    {
        fprintf(stderr, "\nMemory Allocation Failed for Heap");
        free(heap);
        exit(1);
    }
    heap->size = 0;
    heap->capacity = DEFAULT_CAPACITY;
    return heap;
}

void resizeHeap(IntervalHeap *heap)
{
    int newCapacity = heap->capacity * 2;
    int *newElements = (int *)realloc(heap->elements, newCapacity * sizeof(int));
    if (!newElements)
    {
        fprintf(stderr, "\nMemory Allocation Failed");
        exit(1);
    }
    heap->elements = newElements;
    heap->capacity = newCapacity;
}
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void fixUpMin(IntervalHeap *heap, int index)
{
    while (index > 0 && heap->elements[(index - 1) / 2] > heap->elements[index])
    {
        swap(&heap->elements[index], &heap->elements[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void fixUpMax(IntervalHeap *heap, int index)
{
    while (index > 0 && heap->elements[(index - 1) / 2] < heap->elements[index])
    {
        swap(&heap->elements[index], &heap->elements[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}
void fixDownMin(IntervalHeap *heap, int index)
{
    int minIndex = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    if (left < heap->size && heap->elements[left] < heap->elements[minIndex])
    {
        minIndex = left;
    }
    if (right < heap->size && heap->elements[right] < heap->elements[minIndex])
    {
        minIndex = right;
    }
    if (minIndex != index)
    {
        swap(&heap->elements[index], heap->elements[minIndex]);
        fixDownmin(heap, minIndex);
    }
}
void fixDownMax(IntervalHeap *heap, int index)
{
    int maxIndex = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    if (left < heap->size && heap->elements[left] > heap->elements[maxIndex])
    {
        maxIndex = left;
    }
    if (right < heap->size && heap->elements[right] > heap->elements[maxIndex])
    {
        maxIndex = right;
    }
    if (maxIndex != index)
    {
        swap(&heap->elements[index], &heap->elements[maxIndex]);
        fixDownMax(heap, maxIndex);
    }
}

void insertElement(IntervalHeap *heap, int value)
{
    if (heap->size == heap->capacity)
    {
        resizeHeap(heap);
    }
    heap->elements[heap->size] = value;
    if (heap->size == 0)
    {
        heap->size++;
        return;
    }
    if (heap->size == 1)
    {
        if (value < heap->elements[0])
        {
            swap(&heap->elements[0], &heap->elements[1]);
        }
        heap->size++;
        return;
    }
    heap->size++;
    int index = heap->size - 1;
    if (index % 2 == 0)
    {
        if (heap->elements[index] > heap->elements[index - 1])
        {
            swap(&heap->elements[index], &heap->elements[index - 1]);
        }
        fixUpMax(heap, index);
        fixUpMin(heap, index - 1);
    }
    else
    {
        if (heap->elements[index] < heap->elements[index - 1])
        {
            swap(&heap->elements[index], &heap->elements[index - 1]);
        }
        fixUpMin(heap, index);
        fixUpMax(heap, index - 1);
    }
}
int findMin(IntervalHeap *heap)
{
    if (heap->size == 0)
    {
        fprintf(stderr, "\nThe heap is empty");
        return INT_MIN;
    }
    return heap->elements[0];
}
int findMax(IntervalHeap *heap)
{
    if (heap->size == 0)
    {
        fprintf(stderr, "\nHeap is empty\n");
        return INT_MIN;
    }
    return heap->size > 1 ? heap->elements[1] : heap->elements[0];
}
void deleteMin(IntervalHeap *heap)
{
    if (heap->size == 0)
    {
        printf("\nHeap is Empty\n");
        return;
    }
    heap->elements[0] = heap->elements[heap->size - 1];
    heap->size--;
    if (heap->size > 0)
    {
        fixDownMin(heap, 0);
    }
}
void deleteMax(IntervalHeap *heap)
{
    if (heap->size == 0)
    {
        printf("\nHeap is Emepty");
        return;
    }
    if (heap->size == 1)
    {
        heap->size--;
        return;
    }
    heap->elements[1] = heap->elements[heap->size - 1];
    heap->size--;
    fixDownMax(heap, 1);
}
void displayHeap(IntervalHeap *heap)
{
    if (heap->size == 0)
    {
        printf("\nHeap is Emtpy");
        return;
    }
    printf("\nHeap Elements: ");
    for (int i = 0; i < heap->size; i++)
    {
        printf("%d", heap->elements[i]);
    }
    printf("\n");
}
void freeHeap(IntervalHeap *heap)
{
    free(heap->elements);
    free(heap);
}
int main()
{
    IntervalHeap *heap = createIntervalHeap();
    int choice, value;
    do
    {
        printf("\n1.Insert Element");
        printf("\n2.Find Maximum");
        printf("\n3.Find Minimum");
        printf("\n4.Delete Minimum");
        printf("\n5.Delete Maximum");
        printf("\n6.Display Heap");
        printf("\n7.Exit");
        printf("\nEnter your choice: ");
        if (scanf("%d", &choice != 1))
        {
            printf("\nInvalid Input. Please Enter a number: ");
            while (getchar() != '\n')
                ;
            continue;
        }
        switch (choice)
        {
        case 1:
        {
            printf("\nEnter the element to insert: ");
            if (scanf("%d", &value) != 1)
            {
                printf("\nYou have entered an non-integer.");
                while (getchar() != '\n')
                    ;
            }
            else
            {
                insertElement(heap, value);
                printf("\nElement %d inserted\n", value);
            }
            break;
        }
        case 2:
        {
            value = findMIn(heap);
            if (value != INT_MIN)
            {
                printf("\nMinimum Element: %d\n", value);
            }
            break;
        }
        case 3:
        {
            value = findMax(heap);
            if(value != INT_MIN)
            {
                printf("\nMaximum Element: %d\n", value);
            }
            break;
        }
        case 4:
        {
            deleteMin(heap);
            printf("\nMinimum Element Deleted");
            break;
        }
        case 5:
        {
            deleteMax(heap);
            printf("\nMaximum Element Deleted");
            break;
        }
        case 6:
        {
            displayHeap(heap);
            break;
        }
        case 7:
        {
            printf("\nExiting...");
            freeHeap(heap);
            break;
        }
        default:
        {
            printf("\nInvalid Choice. Try Again");
        }
        }
    } while (choice != 7);
    return 0;
}