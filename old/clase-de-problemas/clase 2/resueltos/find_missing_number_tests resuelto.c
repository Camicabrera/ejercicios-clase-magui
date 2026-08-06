#include <stdio.h>

int find_missing_number(int* nums, int numsSize) {
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] != i + 1) {
            return i + 1;
        }
    }
    return numsSize + 1; // Si no falta ninguno, entonces el siguiente número es el que falta
}

// TESTS
void run_tests() {
    int test1[] = {1, 2, 3, 5, 6};
    int size1 = sizeof(test1) / sizeof(test1[0]);
    printf("Prueba 1: Primer número faltante = %d (Esperado: 4) \n", find_missing_number(test1, size1));
    
    int test2[] = {1, 2, 3, 4, 5};
    int size2 = sizeof(test2) / sizeof(test2[0]);
    printf("Prueba 2: Primer número faltante = %d (Esperado: 6) \n", find_missing_number(test2, size2));
    
    int test3[] = {2, 3, 4, 5, 6};
    int size3 = sizeof(test3) / sizeof(test3[0]);
    printf("Prueba 3: Primer número faltante = %d (Esperado: 1) \n", find_missing_number(test3, size3));
    
    int test4[] = {3, 4, 5, 6, 7};
    int size4 = sizeof(test4) / sizeof(test4[0]);
    printf("Prueba 4: Primer número faltante = %d (Esperado: 1) \n", find_missing_number(test4, size4));
}

int main() {
    run_tests();
    return 0;
}
