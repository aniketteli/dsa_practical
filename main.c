#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "postfix.h"

int main() {
    char expression[100];
    
    printf("Enter a postfix expression: ");
    fgets(expression, sizeof(expression), stdin);

    // Remove trailing newline character if present
    if (expression[strlen(expression) - 1] == '\n') {
        expression[strlen(expression) - 1] = '\0';
    }

    double result = evaluatePostfixExpression(expression);
    printf("Result: %.2f\n", result);

    return 0;
}
