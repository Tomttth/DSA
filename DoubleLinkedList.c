#include<stdio.h>
#include<stdlib.h>
struct Node
{
 int data;
 struct Node* prev;
 struct Node* next;
};
struct Node* head = NULL;
struct Node* createNode(int data)
{
 struct Node* node = (struct Node*)malloc(sizeof(struct Node));
 node->data = data;
 node->prev = NULL;
 node->next = NULL;
 return node;
}
void insertAtFront(int data)
{
 struct Node* node = createNode(data);
 if(head == NULL)
 {
  node->next = head; 
  head = node;
  return;
 }
 head->prev = node;
 node->next = head;
 head = node;
}
void insertAtEnd(int data)
{
 struct Node* node = createNode(data);
 if(head == NULL)
 {
  node->next = head;
  head = node;
  return;
 }
 struct Node* temp = head;
 struct Node* prev = NULL;
 while(temp!=NULL)
 {
  prev = temp;
  temp = temp->next;
 }
 node->prev = prev;
 prev->next = node;
}
void insertAtPosition(int position, int data)
{
 struct Node* node = createNode(data);
 if(position<=0)
 {
  printf("\nInvalid position");
  free(node);
  return;
 }
 if(position == 1)
 {
  node->next = head;
  if(head!=NULL)
  {
  head->prev = node;
  }
  head = node;
  return;
 }
 struct Node* temp = head;
 for(int i = 1;i < position-1 && temp!=NULL; i++)
 {
  temp = temp->next;
 }
 if(temp == NULL)
 {
   printf("\nThe position is out of the bounds");
   free(node);
   return;
 }
 if(temp->next == NULL)
 {
  node->prev = temp;
  temp->next = node;

  return;
 }
 else
 {
 struct Node* nextNode = temp->next;
 temp->next = node;
 node->prev = temp;
 node->next = nextNode;
 if(nextNode!=NULL)
 {
  nextNode->prev = node;
 }
 }
}
void deleteFromFront()
{
 if(head == NULL)
 {
  printf("\nThe Link List is Empty");
  return;
 }
 printf("\nThe element %d is deleted",head->data);
 struct Node* temp = head;
 head = head->next;
 if(head!=NULL)
 {
  head->prev = NULL;
 }
 free(temp);
}
void deleteFromEnd()
{
 if(head == NULL)
 {
  printf("\nThe Link List is Empty");
  return;
 }
 if(head->next == NULL)
 {
  free(head);
  head = NULL;
  return;
 }
 struct Node* temp = head;
 struct Node* prev = NULL;
 while(temp!=NULL)
 {
  prev = temp;
  temp = temp->next;
 }
  printf("\nLast Element: %d\n",prev->data);
  prev->prev->next = NULL;
  free(temp);
}
  
void display()
{
 struct Node* temp = head;
 if(temp == NULL)
 {
  printf("\nDoubleLnkedList Underflow");
  return;
 }
 while(temp!=NULL)
 {
  if(temp->next == NULL)
  {
   printf("%d\n",temp->data);
  }
  else
  {
   printf("%d->",temp->data);
  }
  temp=temp->next;
 }
}
 
int main()
{
  int choice = 0;
  do
  {
    printf("\n1.Insertion in the front of the linked list");
    printf("\n2.Insertion in the end of the linked list");
    printf("\n3.Insertion in a given position of linked list");
    printf("\n4.Deleting the element from the front");
    printf("\n5.Deleting the element from the end");
    printf("\n6.Displaying the contents of the Double Linked List");
    printf("\n7.Exiting...");
    printf("\nEnter your choice: ");
    scanf("%d",&choice);
    switch(choice){
      case 1: {
        int a = 0;
        printf("\nEnter the value to be inserted in the front of the Linked List: ");
        scanf("%d",&a);
        insertAtFront(a);
        break;
      }
      case 2:{
        int a = 0;
        printf("\nEnter the value to be inserted in the end of the Linked List: ");
        scanf("%d",&a);
        insertAtEnd(a);
        break;
      }
      case 3:{
        int pos = 0;
        int a  = 0;
        printf("\nEnter the postion where you want to insert element: ");
        scanf("%d",&pos);
        printf("\nEnter the element you want to insert in the given %d pos: ",pos);
        scanf("%d",&a);
        insertAtPosition(pos,a);
        break;
      }
      case 4:{
        deleteFromFront();
        break;
      }
      case 5:{
        deleteFromEnd();
        break;
      }
      case 6:{
        printf("\nThe contents of Double Linked List are shown below: ");
        display();
        break;
      }
      case 7:{
        printf("\nExiting...");
        break;
      }
      default:{
        printf("\nYou have entered invalid choice");
        break;
      }
    }
  } while (choice != 7);
 
}

