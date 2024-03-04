#include <stdio.h>
#include <stdlib.h>

typedef struct Persona {
    int edad;
    char* nombre;
} Persona;

// Función para inicializar un arreglo de n personas utilizando malloc
Persona* inicializarPersonasMalloc(int n) {
   // TODO
}

// Función para inicializar un arreglo de n personas utilizando calloc
Persona* inicializarPersonasCalloc(int n) {
    // TODO
}

int main() {
    int n = 5;  // Puedes ajustar el tamaño del arreglo según tus necesidades

    // Ejemplo de uso con malloc
    Persona* personasMalloc = inicializarPersonasMalloc(n);

    // Ejemplo de uso con calloc
    Persona* personasCalloc = inicializarPersonasCalloc(n);

    // Liberar la memoria asignada
    free(personasMalloc);
    free(personasCalloc);

    return 0;
}
