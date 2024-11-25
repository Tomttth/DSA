#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

struct BinomialNode
{
    int key;
    int degree;
    struct BinomialNode *parent;
    struct BinomialNode *child;
    struct BinomialNode *sibling;
};
struct BinomialHeap
{
    struct BinomialNode *head;
};
struct BinomialHeap *createHeap();
struct BinomialNode *createNode(int key);
void linkBinomialTrees(struct BinomialNode *y, struct BinomialNode *z);
struct BinomialHeap *mergeHeaps(struct BinomialHeap *h1, struct BinomialHeap *h2);
struct BinomialHeap *unionHeaps(struct BinomialHeap *h1, struct BinomialHeap *h2);
void insert(struct BinomialHeap *heap, int key);
struct BinomialNode *findMinimum(struct BinomialHeap *heap);
void deleteMinimum(struct BinomialHeap *heap, int x);
void decreaseKey(struct BinomialHeap *heap, struct BinomialNode *node, int newKey);
void deleteNode(struct BinomialHeap *heap, struct BinomialNode *node);
void displayHeap(struct BinomialNode *heap);
void freeHeap(struct BinomialNode *node);
struct BinomialNode *searchNode(struct BinomialNode *node, int key);
struct BinomialHeap *createHeap()
{
    struct BinomialHeap *heap = (struct BinomialHeap *)malloc(sizeof(struct BinomialHeap));
    if(!heap)
    {
        fprintf(stderr,"\nMemory Allocation Failed");
        exit(1);
    }
    heap->head = NULL;
    return heap;
}
struct BinomialNode *createNode(int key)
{
    struct BinomialNode *node = (struct BinomialNode *)malloc(sizeof(struct BinomialNode));
    if(!node)
    {
        fprintf(stderr,"Memory Allocation Failed");
        exit(1);
    }
    node->key = key;
    node->degree = 0;
    node->parent = NULL;
    node->child = NULL;
    node->sibling = NULL;
    return node;
}
void linkBinomialTrees(struct BinomialNode *y, struct BinomialNode *z)
{
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree++;
}
struct BinomialHeap *mergeHeaps(struct BinomialHeap *h1, struct BinomialHeap *h2)
{
    if(!h1 || !h2)
    {
        return h1?h1:h2;
    }
    struct BinomialHeap *newHeap = createHeap();
    struct BinomialNode **pos = &newHeap->head;
    struct BinomialNode *h1Head = h1->head;
    struct BinomialNode *h2Head = h2->head;
    while (h1Head != NULL && h2Head != NULL)
    {
        if (h1Head->degree <= h2Head->degree)
        {
            *pos = h1Head;
            h1Head = h1Head->sibling;
        }
        else
        {
            *pos = h2Head;
            h2Head = h2Head->sibling;
        }
        pos = &(*pos)->sibling;
    }
    *pos = (h1Head != NULL) ? h1Head : h2Head;
    return newHeap;
}
struct BinomialHeap *unionHeaps(struct BinomialHeap *h1, struct BinomialHeap *h2)
{
    struct BinomialHeap *mergedHeap = mergeHeaps(h1, h2);
    if (!mergedHeap->head)
    {
        return mergedHeap;
    }
    struct BinomialNode *prev = NULL;
    struct BinomialNode *curr = mergedHeap->head;
    struct BinomialNode *next = curr->sibling;
    while (next != NULL)
    {
        if ((curr->degree != next->degree) || (next->sibling != NULL && next->sibling->degree == curr->degree))
        {
            prev = curr;
            curr = next;
        }
        else if (curr->key <= next->key)
        {
            curr->sibling = next->sibling;
            linkBinomialTrees(next, curr);
        }
        else
        {
            if (prev == NULL)
            {
                mergedHeap->head = next;
            }
            else
            {
                prev->sibling = next;
            }
            linkBinomialTrees(curr, next);
            curr = next;
        }
        next = curr->sibling;
    }
    return mergedHeap;
}
void insert(struct BinomialHeap *heap, int key)
{
    struct BinomialHeap *newHeap = createHeap();

    newHeap->head = createNode(key);
    struct BinomialHeap *result = unionHeaps(heap,newHeap);
    heap->head = result->head;
}
struct BinomialNode *findMinimum(struct BinomialHeap *heap)
{
    if(!heap || !heap->head)
    {
        return NULL;
    }
    struct BinomialNode *minNode = NULL;
    int minKey = INT_MAX;
    struct BinomialNode *curr = heap->head;
    while (curr != NULL)
    {
        if (curr->key < minKey)
        {
            minKey = curr->key;
            minNode = curr;
        }
        curr = curr->sibling;
    }
    return minNode;
}
void reverseChildren(struct BinomialNode *child, struct BinomialNode **reversedList)
{
    struct BinomialNode *prev = NULL;
    struct BinomialNode *current = child;
    while (current)
    {
        struct BinomialNode *next = current->sibling;
        current->parent = NULL;
        current->sibling = prev;
        prev = current;
        current = next;
    }
    *reversedList = prev;
}
void deleteMinimum(struct BinomialHeap *heap, int x)
{
    if (!heap || !heap->head)
    {
        printf("\nHeap is Empty");
        return;
    }
    struct BinomialNode *minNode = findMinimum(heap);
    if (!minNode)
    {
        return;
    }
    struct BinomialNode *prev = NULL;
    struct BinomialNode *curr = heap->head;
    while (curr != minNode)
    {
        prev = curr;
        curr = curr->sibling;
    }
    if (prev)
    {
        prev->sibling = minNode->sibling;
    }
    else
    {
        heap->head = minNode->sibling;
    }
    struct BinomialNode *reversedChildren = NULL;
    if (minNode->child)
    {
        reverseChildren(minNode->child, &reversedChildren);
    }
    struct BinomialHeap *newHeap = createHeap();
    newHeap->head = reversedChildren;
    struct BinomialHeap *result = unionHeaps(heap, newHeap);
    heap->head = result->head;
    if (x == 0)
    {
        printf("\nDeleted %d", minNode->key);
    }
    free(minNode);
    free(newHeap);
}
void decreaseKey(struct BinomialHeap *heap, struct BinomialNode *node, int newKey)
{
    if(!heap || !node || newKey > node->key)
    {
        printf("\nInvalid Operation");
        return;
    }
    node->key = newKey;
    struct BinomialNode *curr = node;
    struct BinomialNode *parent = node->parent;
    while (parent != NULL && curr->key < parent->key)
    {
        int temp = curr->key;
        curr->key = parent->key;
        parent->key = temp;
        curr = parent;
        parent = parent->parent;
    }
    printf("\nKey reduced successfully");
}
struct BinomialNode *searchNode(struct BinomialNode *node, int key)
{

    if(!node)
    {
        return NULL;
    }
    if(node->key == key)
    {
        return node;
    }
    struct BinomialNode *result = searchNode(node->child, key);
    if(result)
    {
        return result;
    }
    return searchNode(node->sibling, key);
}

void deleteNode(struct BinomialHeap *heap, struct BinomialNode *node)
{
    if (!heap || !node)
    {
        printf("\nInvalid Operation");
        return;
    }
    decreaseKey(heap, node, INT_MIN);
    deleteMinimum(heap, 1);
}
void freeHeap(struct BinomialNode *node)
{
    if (node)
    {
        freeHeap(node->child);
        freeHeap(node->sibling);
        free(node);
    }
}
void displayHeap(struct BinomialNode *node)
{
    while (node)
    {
        printf("\nKey: %d, Degree: %d", node->key, node->degree);
        if (node->child)
        {
            printf("\nChildren of %d:",node->key);
            displayHeap(node->child);
        }
        node = node->sibling;
    }
}
int main()
{
    int choice = 0, data = 0;
    struct BinomialHeap *heap = createHeap();
    do
    {
        printf("\n1.Insertion");
        printf("\n2.Delete Minimum Node");
        printf("\n3.Find Minimum");
        printf("\n4.Display Heap");
        printf("\n5.Delete a Specific Node");
        printf("\n6.Exit");
        printf("\nEnter your choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("\nYou have entered an non-integer element");
            while (getchar() != '\n')
                ;
            continue;
        }
        switch (choice)
        {
        case 1:
        {
            printf("\nEnter the element to insert: ");
            if (scanf("%d", &data) != 1)
            {
                printf("\nYou have entered an non-invalid integer");
                while (getchar() != '\n')
                    ;
            }
            else
            {
                insert(heap, data);
            }
            break;
        }
        case 2:
        {
            deleteMinimum(heap, 0);
            break;
        }
        case 3:
        {
            struct BinomialNode *minNode = findMinimum(heap);
            if (minNode)
            {

                printf("\nThe minimum key is %d", minNode->key);
            }
            else
            {
                printf("\nThe heap is empty");
            }
            break;
        }
        case 4:
        {
            printf("\nThe contents of Binomial Heap is shown below: ");
            if(heap->head)
            {
            displayHeap(heap->head);
            }
            else
            {
                printf("\nHeap is Empty");
            }
            break;
        }
        case 5:
        {
            printf("\nEnter the node key to delete: ");
            if (scanf("%d", &data) != 1)
            {
                printf("\nYou have entered invalid integer");
                while (getchar() != '\n')
                    ;
            }
            else
            {
                struct BinomialNode *targetNode = searchNode(heap->head, data);

                if (targetNode)
                {
                    deleteNode(heap, targetNode);
                    printf("\nNode with key %d deleted successfully.", data);
                }
                else
                {
                    printf("\nNode with key %d not found", data);
                }
            }
            break;
        }
        case 6:
        {
            printf("\nExting...");
            freeHeap(heap->head);
            free(heap);
            break;
        }
        default:
        {
            printf("\nInvalid Choice. Please try again");
        }
        }

    } while (choice != 6);
    return 0;
}