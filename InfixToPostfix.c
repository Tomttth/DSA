#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100
struct Node
{
    char data;
    struct Node *next;
};
struct Stack
{
    struct Node *top;
};
struct Stack *createStack()
{
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->top = NULL;
    return stack;
}
struct Node *createNode(char data)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}
void push(struct Stack *stack, char data)
{
    struct Node *node = createNode(data);
    node->next = stack->top;
    stack->top = node;
}
char pop(struct Stack *stack)
{
    if (stack->top == NULL)
    {
        printf("\nStack Underflow");
        return '\0';
    }
    char x = stack->top->data;
    struct Node* node = stack->top;
    stack->top = stack->top->next;
    free(node);
    return x;
}
char peek(struct Stack *stack)
{
    if (stack->top == NULL)
    {
        printf("\nStack Underflow");
        return '\0';
    }
    char x = stack->top->data;
    return x;
}
void display(struct Stack *stack)
{
    struct Node *temp = stack->top;
    if (stack->top == NULL)
    {
        printf("\nStack Underflow");
        return;
    }
    while (temp != NULL)
    {
        printf("%c", temp->data);
        if (temp->next != NULL)
        {
            printf(" -> ");
        }
        temp = temp->next;
    }
    printf("\n");
}
int precedence(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    }
    return 0;
}
void infixToPostfix(struct Stack *stack, char *infix, char *postfix)
{
    int j = 0;
    for (int i = 0; infix[i] != '\0'; i++)
    {
        char token = infix[i];
        if (isalnum(token))
        {
            postfix[j++] = token;
        }
        else if (token == '+' || token == '-' || token == '*' || token == '/' || token == '^')
        {
            while(stack->top != NULL && (precedence(peek(stack))>precedence(token) || (precedence(peek(stack)) == precedence(token) && token != '^')))
            {
                postfix[j++] = pop(stack);
            }
            push(stack, token);
        }
        else if (token == '(')
        {
            push(stack, token);
        }
        else if (token == ')')
        {
            while (stack->top != NULL && peek(stack) != '(')
            {
                postfix[j++] = pop(stack);
            }
            pop(stack);
        }
    }
    while(stack->top != NULL)
    {
        postfix[j++] = pop(stack);
    }
    postfix[j] = '\0';
}
int main()
{
    struct Stack *stack = createStack();
    char infix[MAX], postfix[MAX];
    printf("\nEnter the expression: ");
    fgets(infix, sizeof(infix), stdin);
    infix[strcspn(infix, "\n")] = '\0';

    infixToPostfix(stack, infix, postfix);
    printf("\nPostfix Expresssion: %s",postfix);
    while(stack->top != NULL)
    {
        pop(stack);
    }
    free(stack);
    return 0;
}