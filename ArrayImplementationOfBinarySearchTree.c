#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct ArrayBST
{
    int tree[MAX_SIZE];
    int size;
} ArrayBST;

void initBST(ArrayBST *bst)
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        bst->tree[i] = -1;
    }
    bst->size = 0;
}
void insert(ArrayBST *bst, int key)
{
    if (bst->size >= MAX_SIZE)
    {
        printf("Tree is full, cannot insert %d.\n", key);
        return;
    }
    int index = 0;
    while (index < MAX_SIZE)
    {
        if (bst->tree[index] == -1)
        {
            bst->tree[index] = key;
            bst->size++;
            return;
        }
        else if (key < bst->tree[index])
        {
            index = 2 * index + 1;
        }
        else if (key > bst->tree[index])
        {
            index = 2 * index + 2;
        }
        else
        {
            printf("\nThe element already exists");
            return;
        }
    }
    printf("\nTree structure issue, could not insert");
}
int search(ArrayBST *bst, int key)
{
    if (bst->size == 0)
    {
        printf("\nThe BST is Empty");
        return 0;
    }
    int index = 0;
    while (index < MAX_SIZE && bst->tree[index] != -1)
    {
        if (bst->tree[index] == key)
        {
            return 1;
        }
        else if (key < bst->tree[index])
        {
            index = 2 * index + 1;
        }
        else
        {
            index = 2 * index + 2;
        }
    }
    return 0;
}
void delete(ArrayBST *bst, int key)
{
    int index = 0;
    if (bst->size <= 0)
    {
        printf("\nThe Binary Search Tree is Empty");
        return;
    }
    while (index < MAX_SIZE && bst->tree[index] != -1 && bst->tree[index] != key)
    {
        if (key < bst->tree[index])
        {

            index = 2 * index + 1;
        }
        else
        {

            index = 2 * index + 2;
        }
    }
    if (index >= MAX_SIZE || bst->tree[index] == -1)
    {
        printf("\n%d Key not found in BST", key);
        return;
    }
    if ((2 * index + 1 >= MAX_SIZE || bst->tree[2 * index + 1] == -1) &&
        (2 * index + 2 >= MAX_SIZE || bst->tree[2 * index + 2] == -1))
    {
        bst->tree[index] = -1;
    }
    else if (2 * index + 1 >= MAX_SIZE || bst->tree[2 * index + 1] == -1)
    {
        bst->tree[index] = 2 * index + 2 < MAX_SIZE ? bst->tree[2 * index + 2] : -1;
        bst->tree[2 * index + 2] = -1;
    }
    else if (2 * index + 2 >= MAX_SIZE || bst->tree[2 * index + 2] == -1)
    {
        int childIndex = 2 * index + 1;

        bst->tree[index] = childIndex < MAX_SIZE ? bst->tree[childIndex] : -1;
        bst->tree[childIndex] = -1;
    }
    else
    {
        int successorParentIndex = index;
        int successorIndex = 2 * index + 2;
        while (successorIndex < MAX_SIZE && bst->tree[2 * successorIndex + 1] != -1)
        {
            successorParentIndex = successorIndex;
            successorIndex = 2 * successorIndex + 1;
        }
        bst->tree[index] = bst->tree[successorIndex];
        if (2 * successorIndex < MAX_SIZE && bst->tree[2 * successorIndex +2 ]!=-1)
        {
            bst->tree[successorIndex] = bst->tree[successorIndex * 2 + 2];
            bst->tree[successorIndex * 2 + 2] = -1;
        }
        else
        {
            bst->tree[successorIndex] = -1;
        }
    }
}
void inorder(ArrayBST *bst, int index)
{
    if (index < MAX_SIZE && bst->tree[index] != -1)
    {
        inorder(bst, 2 * index + 1);
        printf("%d ", bst->tree[index]);
        inorder(bst, 2 * index + 2);
    }
}
int main()
{
    ArrayBST *bst = malloc(sizeof(ArrayBST));
    initBST(bst);
    int choice = 0;
    do
    {
        printf("\n1.Insertion");
        printf("\n2.Deletion");
        printf("\n3.Search");
        printf("\n4.Display");
        printf("\n5.Exit");
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
                insert(bst, a);
            }
            break;
        }
        case 2:
        {
            int a = 0;
            printf("\nEnter the number to be deleted: ");
            if (scanf("%d", &a) != 1)
            {
                printf("\nYou have entered an non-integer");
                while (getchar() != '\n')
                    ;
            }
            else
            {
                delete (bst, a);
            }
            break;
        }
        case 3:
        {
            int a = 0;
            printf("\nEnter the element to be searched: ");
            if (scanf("%d", &a) != 1)
            {
                printf("\nYou have entered an non-integer");
                while (getchar() != '\n')
                    ;
            }
            else
            {
                int el = search(bst, a);
                if (el == 1)
                {
                    printf("\nElement %d is found", a);
                }
                else
                {
                    printf("\nElement %d is not found", a);
                }
            }
            break;
        }
        case 4:
        {
            printf("\nThe contents of binary search tree are displayed below: ");
            inorder(bst, 0);
            printf("\n");
            break;
        }
        case 5:
        {
            printf("\nExiting...");
            break;
        }
        default:
        {
            printf("\nYou have entered an invalid choice");
        }
        }
    } while (choice != 5);
    free(bst);
    return 0;
}