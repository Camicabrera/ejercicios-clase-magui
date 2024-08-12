#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Estructura para una pila
typedef struct {
    char *array;
    int top;
    int capacity;
} stack;

// Funciones para manejar la pila
stack* create_stack(int capacity) {
    stack* s = (stack*)malloc(sizeof(stack));
    s->capacity = capacity;
    s->top = -1;
    s->array = (char*)malloc(s->capacity * sizeof(char));
    return s;
}

int is_full(stack* s) {
    return s->top == s->capacity - 1;
}

int is_empty(stack* s) {
    return s->top == -1;
}

void push(stack* s, char item) {
    if (is_full(s)) return;
    s->array[++s->top] = item;
}

char pop(stack* s) {
    if (is_empty(s)) return '\0';
    return s->array[s->top--];
}

char peek(stack* s) {
    if (is_empty(s)) return '\0';
    return s->array[s->top];
}

// Función para invertir una expresión matemática
char* invert_expression(const char* expression) {
    int length = strlen(expression);
    char* result = (char*)malloc((length + 1) * sizeof(char));
    stack* s = create_stack(length);
    int index = 0;

    for (int i = 0; i < length; i++) {
        char ch = expression[i];
        if (ch == '(') {
            push(s, ch);
        } else if (ch == ')') {
            while (!is_empty(s) && peek(s) != '(') {
                result[index++] = pop(s);
            }
            pop(s); // Remove '('
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (!is_empty(s) && peek(s) != '(') {
                result[index++] = pop(s);
            }
            push(s, ch);
        } else {
            result[index++] = ch;
        }
    }

    while (!is_empty(s)) {
        result[index++] = pop(s);
    }

    result[index] = '\0';
    free(s->array);
    free(s);
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
