#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
};
struct Node *newNode(int key)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    if(!node)
    {
        fprintf(stderr,"Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}
struct Node *insert(struct Node *node, int key)
{
    if (node == NULL)
    {
        return newNode(key);
    }
    if (node->key == key)
    {
        return node;
    }
    if (node->key < key)
    {
        node->right = insert(node->right, key);
    }
    else
    {
        node->left = insert(node->left, key);
    }
    return node;
}
void inorder(struct Node *root)
{
   if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}
void freeTree(struct Node* node)
{
    if(node != NULL)
    {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}
struct Node* getSuccessor(struct Node* curr)
{
    curr = curr->right;
    while(curr != NULL && curr->left != NULL)
    {
        curr = curr->left;
    }
    return curr;
}
struct Node* delNode(struct Node* root,int x)
{
    if(root == NULL)
    {
        return root;
    }
    if(root->key > x)
    {
        root->left = delNode(root->left,x);
    }
    else if(root->key < x)
    {
        root->right = delNode(root->right,x);
    }
    else
    {
        if(root->left == NULL)
        {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        if(root->right == NULL)
        {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        struct Node* succ = getSuccessor(root);
        root->key = succ->key;
        root->right = delNode(root->right,succ->key);
    }
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
        printf("\n3.Inorder Traversal");
        printf("\n4.Exit");
        printf("\nEnter your choice: ");
        if(scanf("%d",&choice)!=1)
        {
          printf("\nInvalid Input. Please enter an Integer:\n");
          while(getchar()!='\n');
          choice = 0;
          continue;
        }
        switch (choice)
        {
        case 1:
        {
            int a = 0;
            printf("\nEnter the value you want to insert: ");
            scanf("%d", &a);
            root = insert(root,a);
            break;
        }
        case 2:
        {
            int a = 0;
            printf("\nEnter the value you want to delete: ");
            if(scanf("%d",&a)!= 1)
            {
                printf("\nInvalid Input. Please enter an integer.\n");
                while(getchar()!='\n');
            }
            else
            {
            root = delNode(root,a);
            }
            break;
        }
        case 3:{
            printf("\nThe Contents of Binary Search Tree: ");
            inorder(root);
            printf("\n");
            break;
        }
        case 4:{
            printf("\nExiting...");
            break;
        }
        default:{
            printf("\nYou have entered wrong choice");
        }
        }
    } while (choice != 4);
    freeTree(root);
    return 0;
}
