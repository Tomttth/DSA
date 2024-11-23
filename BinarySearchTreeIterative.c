#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define EMPTY -1

int tree[MAX_SIZE];

void initializeTree()
{
    for (int i = 0; i < MAX_SIZE; i++)
    {

        tree[i] = EMPTY;
    }
}
void insert(int data)
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (tree[i] == data)
        {
            printf("\nElement %d already exists in the tree", data);
            return;
        }
        if (tree[i] == EMPTY)
        {
            tree[i] = data;
            printf("\nInserted %d at index %d\n", data, i);
            return;
        }
    }
    printf("\nTree is full, cannot insert %d\n", data);
}
void preorder(int index)
{
    if (index >= MAX_SIZE || tree[index] == EMPTY)
    {
        return;
    }
    printf("%d ", tree[index]);
    preorder(2 * index + 1);
    preorder(2 * index + 2);
}
int search(int data)
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (tree[i] == data)
        {
            return i;
        }
    }
    return -1;
}
void delete(int data)
{
    int index = search(data);
    if (index == -1)
    {
        printf("%d not found in the tree \n", data);
        return;
    }
    int lastIndex = -1;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (tree[i] != EMPTY)
        {
            lastIndex = i;
        }
    }
    if (lastIndex == -1)
    {
        printf("\nThe tree is empty cannot delete %d\n", data);
        return;
    }
    printf("\nDeleting %d from index %d \n", data, index);
    tree[index] = tree[lastIndex];
    tree[lastIndex] = EMPTY;
}
int main()
{
    initializeTree();
    int choice = 0, data = 0;
    do
    {
        printf("\n1.Insertion");
        printf("\n2.Deletion");
        printf("\n3.Search");
        printf("\n4.Preorder Traversal");
        printf("\n5.Exit");
        printf("\nEnter your choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("\nYou have entered an non-integer choice");
            choice = 0;
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
                printf("\nYou have entered an non-integer");
                while (getchar() != '\n')
                    ;
            }
            else
            {
                insert(data);
            }
            break;
        }
        case 2:
        {
            printf("\nEnter the element to delete: ");
            if (scanf("%d", &data) != 1)
            {
                printf("\nYou have entered an non-integer");
                while (getchar() != '\n')
                    ;
            }
            else
            {
                delete (data);
            }
            break;
        }
        case 3:
        {
            printf("\nEnter the element to search: ");
            if (scanf("%d", &data) != 1)
            {
                printf("\nYou have entered an non-integer element");
                while (getchar() != '\n')
                    ;
            }
            else
            {
                int index = search(data);
                if (index != -1)
                {
                    printf("\nElement %d found at index %d", data, index);
                }
                else
                {
                    printf("\nElement %d not found", data);
                }
            }
            break;
        }
        case 4:
        {
            printf("Preorder Traversal: ");
            if (tree[0] == EMPTY)
            {
                printf("\nThe Tree is Empty.\n");
            }
            else
            {
                preorder(0);
                printf("\n");
            }
            break;
        }
        case 5:
        {
            printf("Exiting...\n");
            break;
        }
        default:
        {
            printf("\nYou have entered an invalid choice");
        }
        }
    } while (choice != 5);
    return 0;
}
