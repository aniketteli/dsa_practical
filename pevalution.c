#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "postfix.h"

#define STACK_SIZE 100

typedef struct
{
    double data[STACK_SIZE];
    int top;
} Stack;

void initializeStack(Stack *stack)
{
    stack->top = -1;
}

int isEmpty(Stack *stack)
{
    return stack->top == -1;
}

int isFull(Stack *stack)
{
    return stack->top == STACK_SIZE - 1;
}

void push(Stack *stack, double value)
{
    if (isFull(stack))
    {
        printf("Stack is full. Cannot push more elements.\n");
        exit(EXIT_FAILURE);
    }
    stack->data[++(stack->top)] = value;
}

double pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack is empty. Cannot pop more elements.\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[(stack->top)--];
}

double evaluatePostfixExpression(char *expression)
{
    Stack stack;
    initializeStack(&stack);

    char *token = strtok(expression, " ");

    while (token != NULL)
    {
        if (isdigit(token[0]))
        {
            push(&stack, atof(token));
        }
        else if (strlen(token) == 1 && strchr("+-*/", token[0]))
        {
            double operand2 = pop(&stack);
            double operand1 = pop(&stack);
            double result;

            switch (token[0])
            {
            case '+':
                result = operand1 + operand2;
                break;
            case '-':
                result = operand1 - operand2;
                break;
            case '*':
                result = operand1 * operand2;
                break;
            case '/':
                if (operand2 == 0)
                {
                    printf("Error: Division by zero\n");
                    exit(EXIT_FAILURE);
                }
                result = operand1 / operand2;
                break;
            }

            push(&stack, result);
        }
        else
        {
            printf("Invalid token in expression: %s\n", token);
            exit(EXIT_FAILURE);
        }
        token = strtok(NULL, " ");
    }

    if (stack.top == 0)
    {
        return stack.data[0];
    }
    else
    {
        printf("Invalid expression\n");
        exit(EXIT_FAILURE);
    }
}
