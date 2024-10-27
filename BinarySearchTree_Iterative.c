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
void inorder(struct Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
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
struct Node *insert(struct Node *root, int key)
{
    struct Node *node = createNode(key);
    if (root == NULL)
    {
        return node;
    }
    struct Node *parent = NULL;
    struct Node *current = root;
    while (current != NULL)
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
        else
        {
            free(node);
            return root;
        }
    }
    if (key > parent->data)
    {
        parent->right = node;
    }
    else
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
        if (key > current->data)
        {
            current = current->right;
        }
        else
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
        else
        {
            parent->right = child;
        }
    }
    else
    {
        struct Node *successorParent = current;
        struct Node *successor = current->right;
        while (successor->left != NULL)
        {
            successorParent = successor;
            successor = successor->left;
        }
        current->data = successor->data;
        if (successorParent->left == successor)
        {
            successorParent->left = successor->right;
        }
        else
        {
            successorParent->right = successor->right;
        }
    }
    free(current);
    return root;
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
        printf("\n4.Exit");
        printf("\nPlease enter your choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("\nYou have entered an non-integer");
            while (getchar() != '\n')
                ;
            choice = 0;
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
                root = insert(root, a);
            }
            break;
        }
        case 2:
        {
            int a = 0;
            printf("\nEnter the value to be deleted: ");
            if (scanf("%d", &a) != 1)
            {
                printf("\nYou have entered an non-integer");
                while (getchar() != '\n')
                    ;
            }
            else
            {
                root = delete (root, a);
            }
            break;
        }
        case 3:
        {
            printf("\nThe contents of the binary search tree are displayed below: ");
            inorder(root);
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