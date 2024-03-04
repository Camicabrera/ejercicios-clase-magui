#include <stdio.h>
#include <stdlib.h>

void crearArreglo(int v) {
   // TODO:
}

int* crearArregloDin(int n, int v) {
    // TODO:
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
