#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Función para encontrar el máximo producto de una subcadena de longitud k
int max_product_of_substring(const char* str, int k) {
    int max_product = 0;

    // Punteros para recorrer la cadena
    const char* end = str + strlen(str);
    const char* ptr = str;

    // Verificar si k es mayor que la longitud de la cadena
    if (k > end - ptr) return 0;

    // Iterar sobre todas las subcadenas de longitud k
    while (ptr + k <= end) {
        int product = 1;
        for (const char* sub_ptr = ptr; sub_ptr < ptr + k; ++sub_ptr) {
            product *= (*sub_ptr - '0'); // Convertir carácter a entero
        }
        if (product > max_product) {
            max_product = product;
        }
        ptr++;
    }

    return max_product;
}

// Función para imprimir los resultados de las pruebas
void run_tests() {
    char* str1 = "123456789";
    int k1 = 3;
    printf("Input: %s, k = %d\n", str1, k1);
    printf("Output: %d\n", max_product_of_substring(str1, k1));
    printf("Expected Output: 504\n");
    printf("\n");

    char* str2 = "11111";
    int k2 = 2;
    printf("Input: %s, k = %d\n", str2, k2);
    printf("Output: %d\n", max_product_of_substring(str2, k2));
    printf("Expected Output: 1\n");
    printf("\n");

    char* str3 = "987654321";
    int k3 = 4;
    printf("Input: %s, k = %d\n", str3, k3);
    printf("Output: %d\n", max_product_of_substring(str3, k3));
    printf("Expected Output: 3024\n");
    printf("\n");

    char* str4 = "0000";
    int k4 = 1;
    printf("Input: %s, k = %d\n", str4, k4);
    printf("Output: 0\n");
    printf("Expected Output: 0\n");
    printf("\n");
}

int main() {
    run_tests();
    return 0;
}
