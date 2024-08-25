#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"

char* invert_expression(const char* expression) {
    Stack* accumulator = create_stack();
    // validar en creación de stack en caso de que devolviera null x error
    
    int pos = 0;
    while(expression[pos]!= '\0') {
        if(expression[pos] == '(') {
            char my_character = ')';
            push(accumulator, &my_character);
        } else if (expression[pos] == ')') {
            char my_character = '(';
            push(accumulator, &my_character);
        } else {
            push(accumulator, (char*)&expression[pos]);
        }
        pos ++;
    }

    char* copy = malloc(sizeof(char) * (pos + 1));
    if(!copy) {
        free_stack(accumulator);
    }

    pos = 0;
    while(!is_stack_empty(accumulator)) {
        copy[pos] = * ((char*)pop(accumulator));
        pos ++;
    }

    free_stack(accumulator);
    copy[pos++] = '\0';

    return copy;
}

// TEST
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
