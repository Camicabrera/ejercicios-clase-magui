#include <stdio.h>

// Escribir la función que dado n P N devuelve si es primo. Recuerden que un
// número es primo si los únicos divisores que tiene son 1 y el mismo.

int esPrimo(int n) {
return 0;
}

void realizarPrueba(int n, int esperado) {
    int resultado = esPrimo(n);
    
    printf("Prueba para el numero %d: ", n);
    
    if (resultado == esperado) {
        printf("Aprobada\n");
    } else {
        printf("Falla la prueba\n");
    }
}

int main() {
    
    realizarPrueba(1, 0);  
    realizarPrueba(2, 1); 
    realizarPrueba(7, 1);   
    realizarPrueba(10, 0);  
    realizarPrueba(13, 1); 
    realizarPrueba(25, 0); 

    return 0;
}
