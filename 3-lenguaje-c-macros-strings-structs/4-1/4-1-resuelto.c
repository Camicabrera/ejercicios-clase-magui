#include <stdio.h>

int maximo(int* arr, int size) {
    if (size <= 0) {
        return -1;
    }

    int max = arr[0];

    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    return max;
}

void realizarPruebaMaximo(int* arr, int size, int esperado) {
    int resultado = maximo(arr, size);

    printf("Prueba para el arreglo: [");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    printf("Resultado esperado: %d\n", esperado);
    printf("Resultado obtenido: %d\n", resultado);

    if (resultado == esperado) {
        printf("Prueba aprobada\n");
    } else {
        printf("Prueba fallida\n");
    }

    printf("\n");
}

int main () {

    int arrMaximo1[] = {3, 7, 1, 8, 4};
    realizarPruebaMaximo(arrMaximo1, 5, 8);


    int arrMaximo2[] = {-5, -2, -8, -1};
    realizarPruebaMaximo(arrMaximo2, 4, -1);
}