#include <stdio.h>

// Escribir la función que dado n P N devuelve la suma de todos los números
// impares menores que n.

// En O(n)
int sumaImparesMenoresQueN(int n) {
    int suma = 0;

    for (int i = 1; i < n; i += 2) {
        suma += i; /
    }

    return suma;
}

// // En O(1)
// int sumaImparesMenoresQueN(int n) {
//     return (n * n) / 4; 
// }

int main() {
    int n;
    printf("Ingrese un numero: ");
    scanf("%d", &n);

    int resultado = sumaImparesMenoresQueN(n);
    printf("La suma de los numeros impares menores que %d es: %d\n", n, resultado);

    return 0;
}
