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
    if(!node)
    {
        fprintf(stderr,"Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->left = NULL;
    node->right = NULL;
    node->data = data;
    return node;
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
    else
    {
        parent->left = node;
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
struct Node *delete(struct Node *root, int key)
{
    struct Node *parent = NULL;
    struct Node *current = root;
    while (current != NULL && current->data != key)
    {
        parent = current;
        if (key > current->data)
        {
            current = current->right;
        }
        else if (key < current->data)
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
        free(succCurrent);
    }
    free(current);
    return root;
}
void levelOrderTraversal(struct Node *root)
{
    if (root == NULL)
    {
        return;
    }
    struct Node **queue = (struct Node **)malloc(100 * sizeof(struct Node *));
    if(!queue)
    {
        fprintf(stderr,"Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    int front = 0, rear = 0;
    queue[rear++] = root;
    while (front < rear)
    {
        struct Node *node = queue[front++];
        printf("%d ", node->data);
        if (node->left != NULL)
        {
            queue[rear++] = node->left;
        }
         if (node->right != NULL)
        {
            queue[rear++] = node->right;
        }
    }
    free(queue);
}
int main()
{
    struct Node *root = NULL;
    int choice = 0;
    do
    {
        printf("\n1.Insertion");
        printf("\n2.Deletion");
        printf("\n3.Level Order Traversal");
        printf("\n4.Exit");
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
            printf("\nEnter the element you want to insert: ");
            int a = 0;
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
            printf("\nEnter the element you want to delete in binary search tree: ");
            if (scanf("%d", &a) != 1)
            {
                printf("\nYou have entered an non-integer element");
                while (getchar() != '\n');
                    
            }
            else
            {
                root = delete(root, a);
            }
            break;
        }
        case 3:
        {
            printf("\nThe contents of Binary Search Tree are displayed below: ");
            levelOrderTraversal(root);
            printf("\n");
            break;
        }
        case 4:
        {
            printf("\nExiting...");
            break;
        }
        default:
        {
            printf("\nYou have entered wrong choice");
        }
        }
    } while (choice != 4);
    freeTree(root);
    return 0;
}