#include <stdio.h>
#include <stdlib.h>
struct Stack
{
    int top;
    int *array;
    int size;
};
struct Stack *createStack()
{
    int a = 0;
    printf("\nEnter the array size: ");
    scanf("%d", &a);
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->array = (int *)malloc(a * sizeof(int));
    stack->size = a;
    stack->top = -1;
    return stack;
}
void push(struct Stack *stack, int data)
{
    if (stack->top >= stack->size - 1)
    {
        printf("\nStack Overflow");
        return;
    }
    stack->array[++stack->top] = data;
}
void display(struct Stack *stack)
{
    int x = stack->top;
    if (stack->top == -1)
    {
        printf("\nStack Underflow");
        return;
    }
    while (x != -1)
    {
        printf("%d", stack->array[x--]);
        if(x != -1)
        {
            printf(" -> ");
        }
    }
    printf("\n");
}
int peek(struct Stack *stack)
{
    if (stack->top == -1)
    {
        printf("\nStack Underflow");
        return -1;
    }
    int x = stack->array[stack->top];
    return x;
}
int pop(struct Stack *stack)
{
    if (stack->top == -1)
    {
        printf("Stack Underflow");
        return -1;
    }
    int x = stack->array[stack->top];
    --stack->top;
    return x;
}
int main()
{
    int a = 0;
    struct Stack *stack = createStack();
    int choice;
    do
    {
        printf("\n1.Push");
        printf("\n2.Display");
        printf("\n3.Peek");
        printf("\n4.Pop");
        printf("\n5.Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            printf("\nEnter the element you want to insert: ");
            scanf("%d", &a);
            push(stack, a);
            break;
        }
        case 2:
        {
            printf("\nThe contents of the stack are listed below: ");
            display(stack);
            break;
        }
        case 3:
        {
            int x = peek(stack);
            if (x != -1)
            {
                printf("\nElement %d is at the top", x);
            }
            break;
        }
        case 4:
        {
            int x = pop(stack);
            if (x != -1)
            {
                printf("\nElement %d got deleted",x);
            }
            break;
        }
        case 5:
        {
            printf("\nExiting...");
            free(stack->array);
            free(stack);
            break;
        }
        default:
        {
            printf("\nYou have entered wrong choice");
        }
        }
    } while (choice != 5);
}