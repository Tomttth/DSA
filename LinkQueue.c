#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int data;
    struct Node *next;
};
struct Queue
{
    struct Node *front;
    struct Node *rear;
};
struct Queue *createQueue()
{
    struct Queue *queue = (struct Queue *)malloc(sizeof(struct Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}
struct Node *createNode(int data)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}
void insert(struct Queue *queue, int data)
{
    struct Node *node = createNode(data);
    if (queue->front == NULL)
    {
        queue->front = node;
        queue->rear = node;
        return;
    }
    queue->rear->next = node;
    queue->rear = node;
}
int delete(struct Queue *queue)
{
    if (queue->front == NULL)
    {
        printf("\nQueue Underflow");
        return -1;
    }
    struct Node *temp = queue->front;
    int x = temp->data;
    if (queue->front == queue->rear)
    {
        queue->front = NULL;
        queue->rear = NULL;
        return x;
    }
    queue->front = queue->front->next;
    return x;
}
void display(struct Queue *queue)
{
    printf("\nQueue Contents: ");
    struct Node *temp = queue->front;
    if (queue->front == NULL)
    {
        printf("\nQueue Underflow");
        return;
    }
    while (temp != NULL)
    {
        printf("%d", temp->data);
        temp = temp->next;
        if (temp != NULL)
        {
            printf(" -> ");
        }
    }
    printf("\n");
}
int main()
{
    struct Queue *queue = createQueue();
    int choice = 0;
    do
    {
        printf("\n1.Insert");
        printf("\n2.Delete");
        printf("\n3.Display");
        printf("\n4.Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            int a = 0;
            printf("\nEnter the element to be inserted: ");
            scanf("%d", &a);
            insert(queue, a);
            break;
        }
        case 2:
        {
            int x = delete (queue);
            if (x != -1)
            {
                printf("Deleteing element %d from front of queue", x);
            }
            break;
        }
        case 3:
        {
            printf("\nThe contents of the queue are displayed below: ");
            display(queue);
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
    while (queue->front != NULL)
    {
        delete (queue);
    }
    free(queue);
    return 0;
}