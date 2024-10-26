#include<stdio.h>
#include<stdlib.h>
struct Node
{
    struct Node* left;
    struct Node* right;
    int data;
};
struct Node* createNode(int data)
{
    struct Node* node =(struct Node*)malloc(sizeof(struct Node));
    node->left = NULL;
    node->right = NULL;
    node->data = data;
    return node;
}
struct Node* insert(struct Node* root,int key)
{
    struct Node* node = createNode(key);
    if(root == NULL)
    {
        return node;
    }
    if(root->data == key)
    {
        return root;
    }
    if(key > root->data)
    {
        root->right = insert(root->right,key);
    }
    if(key < root->data)
    {
        root->left = insert(root->left,key);
    }
    return root;
}
void preorder(struct Node* root)
{   if(root != NULL)
   {
    printf("%d ",root->data);
    preorder(root->left);
    preorder(root->right);
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
struct Node* delete(struct Node* root, int key)
{
  if(root == NULL)
  {
    return root;
  }
  if(root->data > key)
  {
    root->left = delete(root->left,key);
  }
  else if(root->data < key)
  {
    root->right = delete(root->right,key);
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
    root->data = succ->data;
    root->right = delete(root->right,succ->data);

  }
  return root;
}
void freeTree(struct Node* root)
{
    if(root != NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
int main()
{
    struct Node* root = NULL;
    int choice = 0;
    do
    {
        
    printf("\n1.Insertion");
    printf("\n2.Deletion");
    printf("\n3.Preorder Traversal");
    printf("\n4.Exit");
    printf("\nEnter your choice: ");
    if(scanf("%d",&choice)!= 1)
    {
        printf("\nYou have entered non-integer choice");
        while(getchar() != '\n');
        choice = 0;
        continue;
    }
    switch(choice)
    {
        case 1: {
            printf("\nEnter the number you want to insert in Binary Search Tree: ");
            int a = 0;
            if(scanf("%d",&a) != 1)
            {
                printf("\nYou have entered non-integer ");
                while(getchar() != '\n');
            }
            else
            {
           root = insert(root,a);
            }
           break;
        }
        case 2:{
            printf("\nEnter the element you want to delete: ");
            int a = 0;
            if(scanf("%d",&a) != 1)
            {
                printf("\nYou have entered non-integer ");
                while(getchar()!='\n');
            }
            else
            {
            root = delete(root,a);
            }
            break;
        }
        case 3: {
            printf("\nThe contents of the binary tree are displayed below: ");
            preorder(root);
            printf("\n");
            break;
        }
        case 4:{
            printf("\nExiting...");
            break;
        }
        default:{
            printf("\nYou have entered wrong choice: ");
        }
    }
    } while (choice != 4);
    freeTree(root);
    return 0;
    
}
