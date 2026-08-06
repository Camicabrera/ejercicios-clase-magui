#include <stdio.h>
#include <stdlib.h>

void crearArreglo(int v, int a[], int* b) {
  
    *b = v;

    for (int i = 0; i < 8; i++) {
        a[i] = v;
    }

}

int* crearArregloDin(int n, int v) {
   int * a = malloc(sizeof(int)*n);
   for (int i = 0; i < n; i++) {
        *(a+i) = v;
    } 

    return a;
}

void mostrarMemoria(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("Elemento: %d, Dirección: %p\n", i, (void*)&arr[i]);
    }
}

int main() {
    printf("Ejemplo 1:\n");
    int a[8];
    int b = 2;
    crearArreglo(5, a, &b);

    printf("%d", b);

    for (int i = 0; i < 8; i++) {
        printf("%d",  a[i]);
    }

    printf("\nEjemplo 2:\n");
    int* arregloDinamico = crearArregloDin(6, 8);
    mostrarMemoria(arregloDinamico, 6);

    free(arregloDinamico);

    free(arregloDinamico);
    return 0;
}
