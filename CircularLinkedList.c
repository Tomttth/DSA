#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int data;
    struct Node *next;
};
struct Node *head = NULL;

struct Node *createNode(int data)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}
void insertAtFront(int data)
{
    struct Node *node = createNode(data);
    if (head == NULL)
    {
        head = node;
        node->next = head;
        return;
    }
    struct Node *temp = head;
    while (temp->next != head)
    {
        temp = temp->next;
    }
    temp->next = node;
    node->next = head;
    head = node;
}
void insertAtEnd(int data)
{
    struct Node *node = createNode(data);
    if (head == NULL)
    {
        head = node;
        node->next = head;
        return;
    }
    struct Node *temp = head;
    while (temp->next != head)
    {
        temp = temp->next;
    }
    temp->next = node;
    node->next = head;
}
void insertAtPosition(int position, int data)
{
    struct Node *node = createNode(data);
    if (position < 1)
    {
        printf("\nInvalid Position");
        free(node);
        return;
    }
    if (position == 1)
    {
        insertAtFront(data);
        return;
    }
    struct Node *temp = head;
    int i = 0;
    for (i = 1; i < position - 1 && temp->next != head; i++)
    {
        temp = temp->next;
    }
    if (temp->next == head && i < position - 1)
    {
        printf("\nThe position is greater than the linked list");
        free(node);
        return;
    }
    node->next = temp->next;
    temp->next = node;
}
void deleteFromFront()
{
    if (head == NULL)
    {
        printf("\nThe LinkedList is Empty");
        return;
    }
    if (head->next == head)
    {
        free(head);
        head = NULL;
        return;
    }
    struct Node *temp = head;
    struct Node *trav = temp;
    printf("\nDeleting %d from Circular Linked List",head->data);
    while (temp->next != trav)
    {
        temp = temp->next;
    }
    head = head->next;
    temp->next = head;
    free(trav);
}
void deleteFromEnd()
{
    if (head == NULL)
    {
        printf("\nThe LinkedList is Empty");
        return;
    }
    if (head->next == head)
    {
        printf("\nDeleting %d from Circular Linked list",head->data);
        head = NULL;
        return;
    }
    struct Node *temp = head;
    struct Node *prev = NULL;
    while (temp->next != head)
    {
        prev = temp;
        temp = temp->next;
    }
    printf("\nDeleting %d from circular linked list",temp->data);
    prev->next = head;
    free(temp);
}
void display()
{
    struct Node *temp = head;
    if (head == NULL)
    {
        printf("\nThe given linked list is empty");
        return;
    }
    printf("\n");
    do
    {
        if (temp->next == head)
        {
            printf("%d", temp->data);
            break;
        }
        printf("%d->", temp->data);
        temp = temp->next;
    } while (temp != head);
}
int main()
{
    int choice = 0;
    do
    {
        printf("\n1.Insertion in the front of the circular linked list");
        printf("\n2.Insertion at the end of the circular linked list");
        printf("\n3.Insertion at specific position in circular linked list");
        printf("\n4.Deletion from front of circular linked list");
        printf("\n5.Deletion from end of the circular linked list");
        printf("\n6.Displaying the contents of the circular linked list"); 
        printf("\n7.Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            int a = 0;
            printf("\nEnter the element to be inserted at the front of the circular linked list: ");
            scanf("%d", &a);
            insertAtFront(a);
            break;
        }
        case 2:
        {
            int a = 0;
            printf("\nEnter the element to be inserted at the end of the circular linked list: ");
            scanf("%d", &a);
            insertAtEnd(a);
            break;
        }
        case 3:
        {
            int pos = 0;
            int a = 0;
            printf("\nEnter the position where you want to insert element: ");
            scanf("%d", &pos);
            printf("\nEnter the element you want to insert in circular linked list: ");
            scanf("%d", &a);
            insertAtPosition(pos, a);
            break;
        }
        case 4:
        {
            printf("\nDeleting the first element from circular linked list: ");
            deleteFromFront();
            break;
        }
        case 5:
        {
            printf("\nDeleting the last element from circular linked list: ");
            deleteFromEnd();
            break;
        }
        case 6:
        {
            printf("\nDisplaying the contents of circular linked list: ");
            display();
            break;
        }
        case 7:
        {
            printf("\nExiting...");
            break;
        }
        default:
        {
            printf("\nYou have entered invalid choice");
        }
        }
    } while (choice != 7);
    return 0;
}