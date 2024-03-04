#include <stdio.h>
#include <stdlib.h>

void crearArreglo(int v) {
    int arr[8];

    for (int i = 0; i < 8; i++) {
        arr[i] = v;
    }

    printf("Arreglo Estático: [");
    for (int i = 0; i < 8; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

int* crearArregloDin(int n, int v) {
    int* arr = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        arr[i] = v;
    }

    return arr;
}

void mostrarMemoria(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("Elemento: %d, Dirección: %p\n", i, (void*)&arr[i]);
    }
}

int main() {
    printf("Ejemplo 1:\n");
    crearArreglo(5);

    printf("\nEjemplo 2:\n");
    int* arregloDinamico = crearArregloDin(6, 8);
    mostrarMemoria(arregloDinamico, 6);

    free(arregloDinamico);

    return 0;
}
