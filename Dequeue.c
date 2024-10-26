#include<stdio.h>
#include<stdlib.h>
struct Node
{
    int data;
    struct Node* next;
};
struct Dequeue
{
  struct Node* front;
  struct Node* rear;  
};
struct Node* createNode(int data)
{
    struct Node* node =(struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}
struct Dequeue* createDequeue()
{
    struct Dequeue* dequeue =(struct Dequeue*)malloc(sizeof(struct Dequeue));
    dequeue->front = NULL;
    dequeue->rear = NULL;
    return dequeue;
}
void insertInEnd(struct Dequeue* dequeue,int data)
{
    struct Node* node = createNode(data);
    if(dequeue->front == NULL)
    {
        dequeue->front = node;
        dequeue->rear = node;
        return;
    }
    dequeue->rear->next = node;
    dequeue->rear = node;
}
void insertInFront(struct Dequeue* dequeue,int data)
{
    struct Node* node = createNode(data);
    if(dequeue->front == NULL)
    {
        dequeue->front = node;
        dequeue->rear = node;
        return;
    }
    node->next = dequeue->front;
    dequeue->front = node;
}
int deleteFromFront(struct Dequeue* dequeue)
{
    if(dequeue->front == NULL)
    {
        printf("\nDequeue Underflow");
        return -1;
    }
    int x = dequeue->front->data;
    struct Node* temp = dequeue->front;
    dequeue->front = dequeue->front->next;
    free(temp);
    if(dequeue->front == NULL)
    {
      dequeue->front = NULL;
      dequeue->rear = NULL; 
    }
    return x;
}
int deleteFromEnd(struct Dequeue* dequeue)
{
    if(dequeue->rear == NULL)
    {
        printf("\nDequeue Underflow");
        return -1;
    }
    int x = dequeue->rear->data;
    if(dequeue->front == dequeue->rear)
    {
        free(dequeue->rear);
        dequeue->front = NULL;
        dequeue->rear = NULL;
        return x;
    }
    struct Node* temp = dequeue->front;
    while(temp->next != dequeue->rear)
    {
      temp = temp->next;
    }
    free(dequeue->rear);
    dequeue->rear = temp;
    dequeue->rear->next = NULL;
    return x;
    
}
void display(struct Dequeue* dequeue)
{
    struct Node* temp = dequeue->front;
    if(temp == NULL)
    {
        printf("\nDequeue Underflow");
        return;
    }
    while(temp!=dequeue->rear->next)
    {
        printf("%d",temp->data);
        if(temp->next != dequeue->rear->next)
        {
          printf(" -> ");
        }
        temp = temp->next;
    }
}
int main()
{
    struct Dequeue* dequeue = createDequeue();
    int choice = 0;
    do{
        printf("\n1.Insert In Front of Dequeue");
        printf("\n2.Insert in End of Dequeue");
        printf("\n3.Display");
        printf("\n4.Delete From Front of Dequeue");
        printf("\n5.Delete From End of Dequeue");
        printf("\n6.Exit");
        printf("\nEnter your choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:{
                int n = 0;
                printf("\nEnter the element you want to insert in front of Dequeue: ");
                scanf("%d",&n);
                insertInFront(dequeue,n);
                break;
            }
            case 2:{
                int n = 0;
                printf("\nEnter the element you want to insert in end of Dequeue: ");
                scanf("%d",&n);
                insertInEnd(dequeue,n);
                break;
            }
            case 3:{
                printf("\nThe elements of the dequeue are listed below: ");
                display(dequeue);
                break;
            }
            case 4:{
                int x = deleteFromFront(dequeue);
                if(x != -1)
                {
                    printf("\nElement %d is deleted",x);
                }
                break;
            }
            case 5:{
                int x = deleteFromEnd(dequeue);
                if(x != -1)
                {
                    printf("\nElement %d is deleted",x);
                }
                break;
            }
            case 6:{
                printf("\nExiting...");
                break;
            }
            default:{
                printf("\nYou have entered wrong choice");
            }
        }
    }while(choice != 6);
    while(dequeue->front != NULL)
    {
        deleteFromFront(dequeue);
    }
    free(dequeue);
    return 0;
}