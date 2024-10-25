#include<stdio.h>
#include<stdlib.h>
struct Queue
{
    int data;
    int size;
    int *array;
    int front;
    int rear;
};
struct Queue* createQueue()
{
    struct Queue* queue =(struct Queue*)malloc(sizeof(struct Queue));
    int n = 0;
    printf("\nEnter the size for the array: ");
    scanf("%d",&n);
    queue->size = n;
    queue->array =(int*)malloc(n * sizeof(int));
    queue->front = -1;
    queue->rear  = -1;
    return queue;
}
void insert(struct Queue *queue,int data)
{
    if(queue->rear >= queue->size - 1)
    {
      printf("\nQueue Overflow");
      return;
    }
    if(queue->rear == -1)
    {
        queue->front = 0;
    }
    queue->array[++queue->rear] = data;
}
int delete(struct Queue *queue)
{
    int x = queue->array[queue->front];
    if(queue->front == -1)
    {
        printf("\nQueue Underflow");
        return -1;
    }
    if(queue->front == queue->rear)
    {
        queue->front = -1;
        queue->rear = -1;
        return x;
    }
    queue->front = queue->front + 1;
    return x;
}
void display(struct Queue* queue)
{
   int x = queue->front;
   if(x == -1)
   {
    printf("\nQueue Underflow");
    return;
   }
   printf("\n");
   while(x<=queue->rear)
   {
    printf("%d",queue->array[x++]);
    if(x <=queue->rear)
    {
        printf(" -> ");
    }
   }
}
int main()
{
    struct Queue* queue = createQueue();
    int choice = 0;
    do{
        printf("\n1.Insertion");
        printf("\n2.Deletion");
        printf("\n3.Display");
        printf("\n4.Exit");
        printf("\nEnter your choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:{
                int a = 0;
                printf("\nEnter the element you want to insert: ");
                scanf("%d",&a);
                insert(queue,a);
                break;
            }
            case 2:{
                int x = delete(queue);
                if(x != -1)
                {
                    printf("\nElement %d is deleted ",x);
                }
                break;
            }
            case 3:{
                printf("\nThe contents of queue are displayed below: ");
                display(queue);
                break;
            }
            case 4:{
                printf("\nExiting...");
                break;
            }
            default:{
                printf("\nYou have entered wrong choice..");
            }
        }
    }while(choice!=4);
    free(queue->array);
    free(queue);
    return 0;
}