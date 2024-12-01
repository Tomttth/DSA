#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
struct FibonacciNode
{
    int key;
    int degree;
    bool marked;
    struct FibonacciNode *parent;
    struct FibonacciNode *child;
    struct FibonacciNode *left;
    struct FibonacciNode *right;
};
struct FibonacciHeap
{
    struct FibonacciNode *min;
    int count;
};
struct FibonacciHeap *createFibonacciHeap();
struct FibonacciNode *createFibonacciNode(int key);
void insertNode(struct FibonacciHeap *heap, int key);
struct FibonacciNode *findMinimum(struct FibonacciHeap *heap);
void fibonacciLink(struct FibonacciNode *y, struct FibonacciNode *x);
struct FibonacciHeap *consolidate(struct FibonacciHeap *heap);
struct FibonacciNode *extractMin(struct FibonacciHeap *heap);
void cut(struct FibonacciHeap *heap, struct FibonacciNode *x, struct FibonacciNode *y);
void cascadingCut(struct FibonacciHeap *heap, struct FibonacciNode *y);
void decreaseKey(struct FibonacciHeap *heap, struct FibonacciNode *x, int newKey);
struct FibonacciNode *searchNode(struct FibonacciNode *root, int key);
void deleteNode(struct FibonacciHeap *heap, struct FibonacciNode *x);
void displayHeap(struct FibonacciNode *node);
void freeHeap(struct FibonacciNode *node);

struct FibonacciHeap *createFibonacciHeap()
{
    struct FibonacciHeap *heap = (struct FibonacciHeap *)malloc(sizeof(struct FibonacciHeap));
    if (!heap)
    {
        fprintf(stderr, "Memory Allocation Failed");
        exit(1);
    }
    heap->min = NULL;
    heap->count = 0;
    return heap;
}

struct FibonacciNode *createFibonacciNode(int key)
{
    struct FibonacciNode *node = (struct FibonacciNode *)malloc(sizeof(struct FibonacciNode));
    if (!node)
    {
        fprintf(stderr, "\nMemory Allocation Failed For Fibonacci Node\n");
        exit(1);
    }
    node->key = key;
    node->degree = 0;
    node->marked = false;
    node->parent = NULL;
    node->child = NULL;
    node->left = node;
    node->right = node;
    return node;
}

void insertNode(struct FibonacciHeap *heap, int key)
{
    struct FibonacciNode *node = createFibonacciNode(key);
    if (heap->min == NULL)
    {
        heap->min = node;
    }
    else
    {
        node->left = heap->min;
        node->right = heap->min->right;
        heap->min->right->left = node;
        heap->min->right = node;
        if (node->key < heap->min->key)
        {
            heap->min = node;
        }
    }
    heap->count++;
}

struct FibonacciNode *findMinimum(struct FibonacciHeap *heap)
{
    return heap->min;
}

void fibonacciLink(struct FibonacciNode *y, struct FibonacciNode *x)
{
    y->left->right = y->right;
    y->right->left = y->left;
    y->parent = x;
    if (x->child == NULL)
    {
        x->child = y;
        x->left = y;
        x->right = y;
    }
    else
    {
        y->left = x->child;
        y->right = x->child->right;
        x->child->right->left = y;
        x->child->right = y;
    }
    x->degree++;
    y->marked = false;
}

struct FibonacciHeap *consolidate(struct FibonacciHeap *heap)
{
    int max_degree = 0;
    int D = (int)(log(heap->count) / log(2)) + 1;
    struct FibonacciNode **A = calloc(D, sizeof(struct FibonacciNode *));
    struct FibonacciNode *current = heap->min;
    int root_count = 0;
    do
    {
        root_count++;
        current = current->right;
    } while (current != heap->min);
    while (root_count > 0)
    {
        struct FibonacciNode *x = heap->min;
        int d = x->degree;
        x->left->right = x->right;
        x->right->left = x->left;
        root_count--;
        while (A[d] != NULL)
        {
            struct FibonacciNode *y = A[d];
            if (x->key > y->key)
            {
                struct FibonacciNode *temp = x;
                x = y;
                y = temp;
            }
            fibonacciLink(y, x);
            A[d] = NULL;
            d++;
        }
        A[d] = x;
        current = heap->min;
    }
    heap->min = NULL;
    for (int i = 0; i < D; i++)
    {
        if (A[i] != NULL)
        {
            if (heap->min == NULL)
            {
                heap->min = A[i];
                A[i]->left = A[i];
                A[i]->right = A[i];
            }
            else
            {
                A[i]->left = heap->min;
                A[i]->right = heap->min->right;
                heap->min->right->left = A[i];
                heap->min->right = A[i];
                if (A[i]->key < heap->min->key)
                {
                    heap->min = A[i];
                }
            }
        }
    }
    free(A);
    return heap;
}

struct FibonacciNode *extractMin(struct FibonacciHeap *heap)
{
    struct FibonacciNode *z = heap->min;
    if (z != NULL)
    {
        if (z->child != NULL)
        {
            struct FibonacciNode *current = z->child;
            struct FibonacciNode *start = current;

            do
            {
                current->parent = NULL;
                current = current->right;
            } while (current != start);
            z->left->right = z->child;
            z->child->left = z->left;
            z->right->left = current->left;
            current->left->right = z->right;
        }
        z->left->right = z->right;
        z->right->left = z->left;
        if (z == z->right)
        {
            heap->min = NULL;
        }
        else
        {
            heap->min = z->right;
            consolidate(heap);
        }
        heap->count--;
    }
    return z;
}
void cut(struct FibonacciHeap *heap, struct FibonacciNode *x, struct FibonacciNode *y)
{
    if (y->child == x)
    {
        y->child = x->child;
    }
    x->left->right = x->right;
    x->right->left = x->left;
    y->degree--;
    x->parent = NULL;
    x->left = heap->min;
    x->right = heap->min->right;
    heap->min->right->left = x;
    heap->min->right = x;
    x->marked = false;
}

void cascadingCut(struct FibonacciHeap *heap, struct FibonacciNode *y)
{
    struct FibonacciNode *z = y->parent;
    if (z != NULL)
    {
        if (!y->marked)
        {
            y->marked = true;
        }
        else
        {
            cut(heap, y, z);
            cascadingCut(heap, z);
        }
    }
}

void decreaseKey(struct FibonacciHeap *heap, struct FibonacciNode *x, int newKey)
{
    if (newKey > x->key)
    {
        printf("\nNew key is greater than current key\n");
        return;
    }
    x->key = newKey;
    struct FibonacciNode *y = x->parent;
    if (y != NULL && x->key < y->key)
    {
        cut(heap, x, y);
        cascadingCut(heap, y);
    }
    if (x->key < heap->min->key)
    {
        heap->min = x;
    }
}

struct FibonacciNode *searchNode(struct FibonacciNode *root, int key)
{
    if (root == NULL)
    {
        return NULL;
    }
    struct FibonacciNode *current = root;
    do
    {
        if (current->key == key)
        {
            return current;
        }
        if (current->child != NULL)
        {
            struct FibonacciNode *found = searchNode(current->child, key);
            if (found)
            {
                return found;
            }
        }
        current = current->right;
    } while (current != root);
    return NULL;
}

void deleteNode(struct FibonacciHeap *heap, struct FibonacciNode *x)
{
    decreaseKey(heap, x, INT_MIN);
    extractMin(heap);
}

void displayHeap(struct FibonacciNode *node)
{
    if (node == NULL)
    {
        return;
    }
    struct FibonacciNode *current = node;
    do
    {

        printf("Key: %d, Degree: %d ", current->key, current->degree);
        if (current->child)
        {
            printf("\nChildren: ");
            displayHeap(current->child);
        }
        printf("\n");
        current = current->right;
    } while (current != node);
}
void freeHeap(struct FibonacciNode *node)
{
    if (node == NULL)
    {
        return;
    }
    struct FibonacciNode *current = node;
    do
    {
        struct FibonacciNode *temp = current;
        current = current->right;
        if (temp->child)
        {
            freeHeap(temp->child);
        }
        free(temp);
    } while (current != node);
}

int main()
{
    struct FibonacciHeap *heap = createFibonacciHeap();
    int choice, data;
    do
    {
        printf("\n1.Insert");
        printf("\n2.Extract Minimum");
        printf("\n3.Find Minimum");
        printf("\n4.Decrease Key");
        printf("\n5.Delete Node");
        printf("\n6.Display Heap");
        printf("\n7.Exit");
        printf("\nEnter your choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid Input. Please try again!\n");
            while (getchar() != '\n')
                ;
            continue;
        }
        switch (choice)
        {
        case 1:
        {
            printf("\nEnter key to insert: ");
            if (scanf("%d", &data) != 1)
            {
                printf("\nYou have entered an non-integer");
                while (getchar() != '\n')
                    ;
            }
            else
            {
                insertNode(heap, data);
                printf("\nInserted %d\n", data);
            }
            break;
        }
        case 2:
        {
            struct FibonacciNode *min = extractMin(heap);
            if (min)
            {
                printf("\nExtracted Minimum: %d\n", min->key);
                free(min);
            }
            else
            {
                printf("\nHeap is Empty");
            }
            break;
        }
        case 3:
        {
            struct FibonacciNode *min = findMinimum(heap);
            if (min)
            {
                printf("\nMinimum Key: %d\n", min->key);
            }
            else
            {
                printf("\nHeap is Empty");
            }
            break;
        }
        case 4:
        {
            int key, newKey;
            printf("\nEnter node key to decrease: ");
            if (scanf("%d", &key) != 1)
            {
                printf("\nYou have entered an non-integer");
                while (getchar() != '\n')
                    ;
            }
            else
            {
                struct FibonacciNode *node = searchNode(heap->min, key);
                if (node)
                {
                    printf("\nEnter new key: ");
                    if (scanf("%d", &newKey) != 1)
                    {
                        printf("\nYou have entered an non-integer");
                        while (getchar() != '\n')
                            ;
                    }
                    else
                    {
                        decreaseKey(heap, node, newKey);
                        printf("\nKey decreased successfully");
                    }
                }
                else
                {
                    printf("\nKey not found");
                }
            }
            break;
        }
        case 5:
        {
            printf("\nEnter key to delete: ");
            if (scanf("%d", &data) != 1)
            {
                printf("\nYou have entered an non-integer");
                while (getchar() != '\n')
                    ;
            }
            else
            {
                struct FibonacciNode *node = searchNode(heap->min, data);
                if (node)
                {
                    deleteNode(heap, node);
                    printf("\nNode deleted successfully");
                }
                else
                {
                    printf("\nNode not found");
                }
            }
            break;
        }
        case 6:
        {
            if (heap->min)
            {
                printf("\nFibonacci Heap Contents: ");
                displayHeap(heap->min);
            }
            else
            {
                printf("\nHeap is Empty");
            }
            break;
        }
        case 7:
        {
            if (heap->min)
            {
                freeHeap(heap->min);
            }
            free(heap);
            printf("\nExiting...");
            break;
        }
        default:
        {
            printf("\nInvalid choice. Try again.\n");
        }
        }
    } while (choice != 7);
    return 0;
}