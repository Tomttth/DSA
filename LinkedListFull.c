#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int data;
    struct Node *next;
} *head = NULL;
void insertAfterFront(int data)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = data;
    node->next = head;
    head = node;
}
void append(int data)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    if (head == NULL)
    {
        head = node;
        return;
    }
    struct Node *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = node;
}
void display()
{
    struct Node *temp = head;
    if(temp == NULL)
    {
        printf("\nThe LinkedList is empty");
    }
    while (temp != NULL)
    {
        printf("%d", temp->data);
        temp = temp->next;
        if(temp != NULL)
        {
            printf(" -> ");
        }
    }
    printf("\n");
}
void insertAfterNode(int position, int data)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    struct Node *temp = head;
    if(position <= 0)
    {
        printf("\nInvalid Position");
        return;
    }
    if (position == 1)
    {
        node->next = head;
        head = node;
        return;
    }
    for (int i = 1; i < position-1 && temp != NULL; i++)
    {
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("The position is greater than size of list");
        free(node);
        return;
    }
    node->next = temp->next;
    temp->next = node;
}
void deleteNode()
{
    if (head == NULL)
    {
        printf("The Linked List is Empty");
        return;
    }
    if (head->next == NULL)
    {
        printf("The element %d is deleted", head->data);
        head = NULL;
        return;
    }
    struct Node *temp = head;
    printf("\nThe element %d is deleted", head->data);
    head = head->next;
    free(temp);
}
int main()
{
    int a = 0;
    int choice = 0;
    int pos = 0;
    do
    {
        printf("\n1.Insertion at the front of the linked list");
        printf("\n2.Insertion at the end of the linked list");
        printf("\n3.Insertion in a specific position of linked list");
        printf("\n4.Deletion of the linked list");
        printf("\n5.Displaying Linked List");
        printf("\n6.Exit...");
        printf("\nEnter your choice: ");
        scanf(" %d", &choice);
        switch (choice)
        {
        case 1:
        {
            printf("\nEnter the value to be inserted in LInked List: ");
            scanf("%d", &a);
            insertAfterFront(a);
            break;
        }
        case 2:
        {
            printf("\nEnter the value to be inserted at the end of the Linked List: ");
            scanf("%d", &a);
            append(a);
            break;
        }
        case 3:
        {
            printf("\nEnter the position in the linked list where the element should be inserted: ");
            scanf("%d", &pos);
            printf("\nEnter the element to be inserted in the linked list: ");
            scanf("%d", &a);
            insertAfterNode(pos, a);
            break;
        }
        case 4:
        {
            deleteNode();
            break;
        }
        case 5:
        {
            printf("\nThe contents of the linked list are displayed below: ");
            display();
            break;
        }
        case 6:
        {
            printf("\nExiting...");
            break;
        }
        default:
        {
            printf("\nYou have entered wrong choice");
        }
        }
    } while (choice != 6);
    return 0;
}
