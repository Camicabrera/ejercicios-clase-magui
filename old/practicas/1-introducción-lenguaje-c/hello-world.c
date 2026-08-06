// #include <stdio.h>

// int main() {
//     printf("Hello, World!\n");
//     return 0;
// }


#include <stdio.h>

int main() {
    int numeros[5] = {1, 2, 3, 4, 5};

    int entero = 1;
    long no_entero = 10;

    entero = no_entero;
    
    for (int i = 0; i <= 5; i++) {
        printf("%d\n", numeros[i]);
    }

    return 0;
}

