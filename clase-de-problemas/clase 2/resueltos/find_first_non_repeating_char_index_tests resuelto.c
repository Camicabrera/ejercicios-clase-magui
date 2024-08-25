#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Función para encontrar el índice del primer carácter no repetido
int find_first_non_repeating_char_index(const char* str) {
    int count[256] = {0}; // Array para contar las ocurrencias de cada carácter
    int length = (int) strlen(str);

    // Contar las ocurrencias de cada carácter
    for (int i = 0; i < length; i++) {
        count[(unsigned char)str[i]]++;
    }

    // Encontrar el primer carácter no repetido
    for (int i = 0; i < length; i++) {
        if (count[(unsigned char)str[i]] == 1) {
            return i;
        }
    }

    return -1; // Si no hay ningún carácter no repetido
}

// Función para imprimir los resultados de las pruebas
void run_tests() {
    char* str1 = "([{}])";
    int index1 = find_first_non_repeating_char_index(str1);
    printf("Input: %s\n", str1);
    printf("Output: %d\n", index1);
    printf("Expected Output: -1\n");
    printf("\n");

    char* str2 = "swiss";
    int index2 = find_first_non_repeating_char_index(str2);
    printf("Input: %s\n", str2);
    printf("Output: %d\n", index2);
    printf("Expected Output: 0\n");
    printf("\n");

    char* str3 = "aabbccde";
    int index3 = find_first_non_repeating_char_index(str3);
    printf("Input: %s\n", str3);
    printf("Output: %d\n", index3);
    printf("Expected Output: 6\n");
    printf("\n");

    char* str4 = "aabbcc";
    int index4 = find_first_non_repeating_char_index(str4);
    printf("Input: %s\n", str4);
    printf("Output: %d\n", index4);
    printf("Expected Output: -1\n");
    printf("\n");
}

int main() {
    run_tests();
    return 0;
}
