#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX 100
struct Node
{
    char data;
    struct Node* next;
};
struct Stack
{
    struct Node* top;
};
struct Node* createNode(char data)
{
    struct Node* node =(struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}
struct Stack* createStack()
{
    struct Stack* stack =(struct Stack*)malloc(sizeof(struct Stack));
    stack->top = NULL;
    return stack;
}
void push(struct Stack* stack,char data)
{
  struct Node* node = createNode(data);
  node->next = stack->top;
  stack->top = node;
}
char pop(struct Stack* stack)
{
    if(stack->top == NULL)
    {
        return '\0';
    }
    char data = stack->top->data;
    struct Node* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    return data;
}
char peek(struct Stack* stack)
{
    if(stack->top == NULL)
    {
        return '\0';
    }
    char data = stack->top->data;
    return data;
}
void display(struct Stack *stack)
{
    struct Node *temp = stack->top;
    if(stack->top == NULL)
    {
        printf("\nStack Underflow");
        return;
    }
    while(temp != NULL)
    {
       printf("%c",temp->data);
       if(temp->next != NULL)
       {
        printf(" -> ");
       }
       temp = temp->next;
    }
}
int precedence(char op)
{
    switch(op){
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
    for(int i = 0;infix[i]!='\0';i++)
    {
        char token = infix[i];
        if(isalnum(token))
        {
            postfix[j++] = token;
        }
        else if(token  == '+' || token == '-' || token == '*' || token == '/' || token == '^')
        {
            while(stack->top != NULL && (precedence(peek(stack))>precedence(token) || (precedence(peek(stack)) == precedence(token) && token != '^')))
            {
                postfix[j++] = pop(stack);
            }
            push(stack,token);
        }
        else if(token == '(')
        {
            push(stack,token);
        }
        else if(token == ')')
        {
            while(stack->top != NULL && peek(stack) != '(')
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
void reverse(char* str)
{
    int n = strlen(str);
    for(int i = 0 ;i < n/2; i++)
    {
      char temp = str[i];
     str[i] = str[n-i-1];
     str[n-i-1] = temp;
    }
    for(int i = 0; i < n;i++)
    {
        if(str[i] == '(')
        {
            str[i] = ')';
        }
        else if(str[i] == ')')
        {
            str[i] = '(';
        }
    }
}
int main()
{
    int n = 0;
    struct Stack *stack= createStack();
    char infix[MAX],postfix[MAX];
    printf("\nEnter the expression: ");
    fgets(infix,sizeof(infix),stdin);
    infix[strcspn(infix,"\n")] = '\0';
    reverse(infix);
    infixToPostfix(stack,infix,postfix);
    reverse(postfix);
    printf("\nPrefix Expression: %s",postfix);
    while(stack->top!=NULL)
    {
        pop(stack);
    }
    free(stack);
    return 0;
}

