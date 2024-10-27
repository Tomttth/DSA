#include <stdio.h>
#include <stdlib.h>
struct Node
{
    struct Node *left;
    struct Node *right;
    int data;
};
struct Node *createNode(int data)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->left = NULL;
    node->right = NULL;
    node->data = data;
    return node;
}
int height(struct Node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    int l = height(root->left);
    int r = height(root->right);
    return (l > r ? l + 1 : r + 1);
}
struct Node *insert(struct Node *root, int data)
{
    struct Node *node = createNode(data);
    if (root == NULL)
    {
        return node;
    }
    struct Node *parent = NULL;
    struct Node *current = root;
    while (current != NULL)
    {
        parent = current;

        if (data > current->data)
        {
            current = current->right;
        }
        else if (data < current->data)
        {
            current = current->left;
        }
        else
        {
            free(node);
            return root;
        }
    }
    if (data > parent->data)
    {
        parent->right = node;
    }
    else if (data < parent->data)
    {
        parent->left = node;
    }
    return root;
}
struct Node *delete(struct Node *root, int key)
{
    struct Node *parent = NULL;
    struct Node *current = root;
    while (current != NULL && current->data != key)
    {
        parent = current;
        if (key > parent->data)
        {
            current = current->right;
        }
        else if (key < parent->data)
        {
            current = current->left;
        }
    }
    if (current == NULL)
    {
        return root;
    }
    if (current->left == NULL || current->right == NULL)
    {
        struct Node *child = (current->left != NULL) ? current->left : current->right;
        if (parent == NULL)
        {
            free(current);
            return child;
        }
        if (current == parent->left)
        {
            parent->left = child;
        }
        else if (current == parent->right)
        {
            parent->right = child;
        }
        free(current);
    }
    else
    {
        struct Node *succParent = current;
        struct Node *succCurrent = current->right;
        while (succCurrent->left != NULL)
        {
            succParent = succCurrent;
            succCurrent = succCurrent->left;
        }
        current->data = succCurrent->data;
        if (succParent->left == succCurrent)
        {
            succParent->left = succCurrent->right;
        }
        else
        {
            succParent->right = succCurrent->right;
        }
        free(current);
    }
    return root;
}
void freeTree(struct Node *root)
{
    if (root != NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
void display(struct Node *root)
{
    struct Node **stack = (struct Node **)malloc(100 * sizeof(struct Node *));
    int top = -1;
    struct Node *current = root;
    while (current != NULL || top != -1)
    {
        while (current != NULL)
        {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        printf("%d ", current->data);
        current = current->right;
    }
    free(stack);
}
int main()
{
    int choice = 0;
    struct Node *root = NULL;
    do
    {
        printf("\n1.Insertion");
        printf("\n2.Deletion");
        printf("\n3.Display");
        printf("\n4.Height of BinarySearchTree");
        printf("\n5.Exit");
        printf("\nEnter your choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("\nYou have entered an non-integer");
            while (getchar() != '\n')
                ;
            continue;
        }
        switch (choice)
        {
        case 1:
        {
            int a = 0;
            printf("\nEnter the number you want to insert: ");
            if (scanf("%d", &a) != 1)
            {
                printf("\nYou have entered an non-integer");
                while (getchar() != '\n')
                    ;
            }
            else
            {
                root = insert(root, a);
            }
            break;
        }
        case 2:
        {
            int a = 0;
            printf("\nEnter the number you want to delete: ");
            if (scanf("%d", &a) != 1)
            {
                while (getchar() != '\n')
                    ;
            }
            else
            {
                root = delete(root, a);
            }
            break;
        }
        case 3:
        {
            printf("\nInorder traversal of the binary search tree are shown below: ");
            display(root);
            printf("\n");
            break;
        }
        case 4:{
            printf("\nThe height of the binary search tree is %d",height(root));
            break;
        }
        case 5:
        {
            printf("\nExiting");
            break;
        }
        default:
        {
            printf("\nYou have entered wrong choice");
        }
        }
    } while (choice != 5);
    freeTree(root);
    return 0;
}