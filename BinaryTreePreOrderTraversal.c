#include<stdio.h>
#include<stdlib.h>
struct Node
{
 int data;
 struct Node* left;
 struct Node* right;
};
struct Node* createNode(int data)
{
 struct Node* node =(struct Node*)malloc(sizeof(struct Node));
 node->left = NULL;
 node->right = NULL;
 node->data = data;
 return node;
}
struct Node* insert(struct Node* root, int key)
{
 if(root == NULL)
 {
  return createNode(key);
 }
 struct Node* queue[100];
 int front = 0, rear = 0;
 queue[rear++] = root;
 while(front < rear)
 {
  struct Node* temp = queue[front++];
  if(temp->left == NULL)
  {
   temp->left = createNode(key);
   break;
  }
  else
  {
  queue[rear++] = temp->left;
  }
  if(temp->right == NULL)
   { 
     temp->right = createNode(key);
     break;
   }
   else
   {
    queue[rear++] = temp->right;
   }
  }
  return root;
 }
 void printPreorder(struct Node* node)
 {
  if(node != NULL)
  {
  printf("%d ",node->data);
  printPreorder(node->left);
  printPreorder(node->right);
  }
 }
 int searchDFS(struct Node* root, int value)
 {
  if(root == NULL)
  {
   return 0;
  }
  if(root->data == value)
  {
   return 1;
  }
  int left_res = searchDFS(root->left,value);
  int right_res = searchDFS(root->right,value);
  return left_res || right_res;
 }
 struct Node* deleteNode(struct Node* root, int val)
 {
  if(root == NULL)
  {
   return NULL;
  }
  struct Node* queue[100];
  int front = 0, rear = 0;
  queue[rear++] = root;
  struct Node* target = NULL;
  while(front < rear)
  {
   struct Node* curr = queue[front++];

    if(curr->data == val)
    {
     target = curr;
     break;
    }
   if(curr->left)
   {
    queue[rear++] = curr->left;
   }
   if(curr->right)
   {
    queue[rear++] = curr->right;
   }
  }
   if(target == NULL)
   {
    return root;
   }
   struct Node* lastNode = NULL;
   struct Node* lastParent =NULL;
   struct Node* queue1[100];
   int front1 = 0, rear1 = 0;
   queue1[rear1++] = root;
   struct Node* parents[100];
   parents[rear1 - 1] = NULL;
   while(front1 < rear1)
   {
    struct Node* curr = queue1[front1];
    struct Node* parent = parents[front1++];
    lastNode = curr;
    lastParent = parent;
    if(curr->left)
    {
     queue1[rear1] = curr->left;
     parents[rear1++] = curr;
    }
    if(curr->right)
    {
     queue1[rear1] = curr->right;
     parents[rear1++] = curr;
     }
   }
   target->data = lastNode->data;
   if(lastParent)
   {
    if(lastParent->left == lastNode)
    {
     lastParent->left = NULL;
    }
    else
    {
     lastParent->right = NULL;
    }
    free(lastNode);
   }
   else
   {
    free(lastNode);
    return NULL;
   }
   return root;
  }
  int main()
  {
   struct Node* root = NULL;
   int choice = 0;
   do{
      printf("\n1.Insertion");
      printf("\n2.Deletion");
      printf("\n3.Searching an element");
      printf("\n4.Display preOrderTraversal");
      printf("\n5.Exit");
      printf("\nEnter your choice: ");
      if(scanf("%d",&choice) != 1)
      {
        printf("\nYou have entered an non-integer element");
        choice = 0;
        while(getchar() != '\n');
        continue;
      }
      switch(choice){
        case 1: {
                  int a =0;
                  printf("Enter the element you want to insert: ");
                  if(scanf("%d",&a) != 1)
                  {
                   printf("\nYou have entered an non-integer element");
                   while(getchar() != '\n');
                  }
                  else
                  {
                  root = insert(root,a);
                  }
                  break;
                }
       case 2: {
                int a = 0;
                printf("Enter the element you want to delete: ");
                if(scanf("%d",&a) != 1)
                {
                 printf("\nYou have entered an non-integer element");
                 while(getchar() != '\n');
                }
                else
                {
                root = deleteNode(root,a);
                }
                break;
               }
       case 3: {
                int a = 0;
                printf("Enter the element you want to search: ");
                if(scanf("%d",&a) != 1)
                {
                 printf("\nYou have entered an non-integer element");
                 while(getchar() != '\n');
                }
                else
                {
                int found = searchDFS(root,a);
                if(found == 0)
                {
                 printf("\nElement is not found in the binary tree");
                }
                else
                {
                 printf("\nElement %d is found in the binary tree",a);
                }
                }
                break;
               }
       case 4: {
                printf("\nThe contents of binary tree are listed below: ");
                printPreorder(root);
                printf("\n");
                break;
               }
       case 5: {
                printf("\nExiting...\n");
                break;
               }
       default: {
                 printf("\nYou have entered wrong choice");
                }
            }
   }while(choice != 5);
   return 0;
 }
   
  
   
   
