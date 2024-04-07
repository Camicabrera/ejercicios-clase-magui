#include <stdio.h>

int main() {
    char input[50];
    printf("Ingrese su nombre: ");
    gets(input); // Vulnerable a inyección de código
    printf("Hola, %s!\n", input);
    return 0;
}
