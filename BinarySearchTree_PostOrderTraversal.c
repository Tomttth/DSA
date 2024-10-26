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
struct Node *insert(struct Node *root, int key)
{
    if (root == NULL)
    {
        return createNode(key);
    }
    if (root->data == key)
    {
        return root;
    }
    if (key < root->data)
    {
        root->left = insert(root->left, key);
    }
    if (key > root->data)
    {
        root->right = insert(root->right, key);
    }
    return root;
}
void postOrder(struct Node *root)
{
    if (root != NULL)
    {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}
struct Node *getSuccessor(struct Node *curr)
{

    curr = curr->right;
    while (curr != NULL && curr->left != NULL)
    {
        curr = curr->left;
    }
    return curr;
}
void freeTree(struct Node *root)
{
    if(root!=NULL)
    {
    freeTree(root->left);
    freeTree(root->right);
    free(root);
    }
}
struct Node *delete(struct Node *root, int data)
{
    if (root == NULL)
    {
        return root;
    }
    if (data > root->data)
    {
        root->right = delete (root->right, data);
    }
    else if (data < root->data)
    {
        root->left = delete (root->left, data);
    }
    else
    {
        if (root->left == NULL)
        {
            struct Node *temp = root->right;
            free(root);
            return temp;
        }
        if (root->right == NULL)
        {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }
        struct Node *succ = getSuccessor(root);
        root->data = succ->data;
        root->right = delete (root->right, succ->data);
        return root;
    }
}
int main()
{
    int choice = 0;
    struct Node *root = NULL;
    do
    {
        printf("\n1.Insertion");
        printf("\n2.Deletion");
        printf("\n3.Postorder Traversal");
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
            int a = 0;
            printf("\nEnter the element you want to insert: ");
            if (scanf("%d", &a) != 1)
            {
                printf("\nYou have entered an non-integer");
                while(getchar() != '\n');
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
            printf("\nEnter the element you want to delete: ");
            if (scanf("%d", &a) != 1)
            {
                printf("\nYou have entered an non-integer");
                while(getchar()!='\n');
            }
            else
            {
                root = delete (root, a);
            }
            break;
        }
        case 3:
        {
            printf("\nThe contents of the binary tree are listed below: ");
            postOrder(root);
            printf("\n");
            break;
        }
        case 4:
        {
            printf("\nExiting...\n");
            break;
        }
        default:
        {
            printf("\nYou have entered a wrong choice");
        }
        }
    } while (choice != 4);
    freeTree(root);
    return 0;
}