#include <stdio.h>
#include <string.h>

int main() {
    char buffer[5]; // Buffer de tamaño insuficiente
    strcpy(buffer, "123456"); // Esto causa un desbordamiento de búfer
    printf("%s\n", buffer); // Imprime más allá del tamaño del buffer
    return 0;
}

