#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"

// Función para invertir una expresión matemática
char* invert_expression(const char* expression) {
    int length = (int)strlen(expression);
    char* result = (char*)malloc((length + 1) * sizeof(char));
    Stack* stack = create_stack();
    int index = 0;

    for (int i = 0; i < length; i++) {
        char ch = expression[i];
        if (ch == '(') {
            char* data = (char*)malloc(sizeof(char));
            *data = ')';
            push(stack, data);
        } else if (ch == ')') {
            char* data = (char*)malloc(sizeof(char));
            *data = '(';
            push(stack, data);
        } else {
            char* data = (char*)malloc(sizeof(char));
            *data = ch;
            push(stack, data);
        }
    }

    while (!is_stack_empty(stack)) {
        char* data = (char*)pop(stack);
        result[index++] = *data;
        free(data);
    }

    result[index] = '\0';
    free_stack(stack);
    return result;
}

// Función para imprimir los resultados de las pruebas
void run_tests() {
    char* expression1 = "3 + (2 * 5)";
    char* result1 = invert_expression(expression1);
    printf("Input: %s\n", expression1);
    printf("Output: %s\n", result1);
    printf("Expected Output: (5 * 2) + 3\n");
    printf("\n");
    free(result1);

    char* expression2 = "1 + (2 - (3 * 4))";
    char* result2 = invert_expression(expression2);
    printf("Input: %s\n", expression2);
    printf("Output: %s\n", result2);
    printf("Expected Output: ((4 * 3) - 2) + 1\n");
    printf("\n");
    free(result2);

    char* expression3 = "(3 + 2) * (5 - 4)";
    char* result3 = invert_expression(expression3);
    printf("Input: %s\n", expression3);
    printf("Output: %s\n", result3);
    printf("Expected Output: (4 - 5) * (2 + 3)\n");
    printf("\n");
    free(result3);
}

int main() {
    run_tests();
    return 0;
}
