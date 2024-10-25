#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int data;
    struct Node *next;
};
struct Stack
{
    struct Node *top;
};
struct Node *createNode(int data)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}
void push(struct Stack *stack, int data)
{

    struct Node *node = createNode(data);
    node->next = stack->top;
    stack->top = node;
}
void peek(struct Stack *stack)
{
    if (stack->top == NULL)
    {
        printf("\nStack Underflow");
        return;
    }
    printf("\nThe element on top is %d", stack->top->data);
}
int pop(struct Stack *stack)
{
    if (stack->top == NULL)
    {
        printf("\nStack Underflow");
        return -1;
    }
    struct Node *node = stack->top;
    int x = node->data;
    if (stack->top->next == NULL)
    {
        stack->top = NULL;
        return x;
    }
    stack->top = stack->top->next;
    free(node);
    return x;
}
void display(struct Stack *stack)
{
    struct Node *temp = stack->top;
    printf("\n");
    if (temp == NULL)
    {
        printf("\nThe Stack is Empty");
        return;
    }
    while (temp != NULL)
    {
        if (temp->next == NULL)
        {
            printf("%d", temp->data);
            break;
        }
        printf("%d->", temp->data);
        temp = temp->next;
    }
}
int main()
{
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->top = NULL;
    int a = 0;
    int c = 0;
    do
    {
        printf("\nEnter your choice: ");
        printf("\n1.Push");
        printf("\n2.Peek");
        printf("\n3.Pop");
        printf("\n4.Display");
        printf("\n5.Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &c);

        switch (c)
        {
        case 1:
        {
            printf("\nEnter the element you want to insert in stack: ");
            scanf("%d", &a);
            push(stack, a);
            break;
        }
        case 2:
        {
            peek(stack);
            break;
        }
        case 3:
        {
            int x = pop(stack);
            if (x != -1)
            {
                printf("\n%d is deleted from stack", x);
            }
            break;
        }
        case 4:
        {
            printf("\nDisplaying the contents of stack: ");
            display(stack);
            break;
        }
        case 5:
        {
            printf("Exiting...");
            while (stack->top != NULL)
            {
                pop(stack);
            }
            free(stack);
            break;
        }
        default:
        {
            printf("You have entered wrong choice...");
            break;
        }
        }
    } while (c >= 1 && c <= 4);
}