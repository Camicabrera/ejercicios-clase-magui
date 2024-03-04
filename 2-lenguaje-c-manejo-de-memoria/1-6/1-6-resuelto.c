#include <stdio.h>
#include <stdlib.h>

typedef struct Persona {
    int edad;
    char* nombre;
} Persona;

// Función para inicializar un arreglo de n personas utilizando malloc
Persona* inicializarPersonasMalloc(int n) {
    Persona* personas = (Persona*)malloc(n * sizeof(Persona));

    if (personas == NULL) {
        // Manejo de error: no se pudo asignar memoria
        fprintf(stderr, "Error al asignar memoria\n");
        exit(EXIT_FAILURE);
    }

    // Inicializar cada elemento del arreglo
    for (int i = 0; i < n; i++) {
        personas[i].edad = 0;  // Puedes inicializar la edad con un valor específico si lo deseas
        personas[i].nombre = NULL;  // Inicializar el nombre como NULL
    }

    return personas;
}

// Función para inicializar un arreglo de n personas utilizando calloc
Persona* inicializarPersonasCalloc(int n) {
    Persona* personas = (Persona*)calloc(n, sizeof(Persona));

    if (personas == NULL) {
        // Manejo de error: no se pudo asignar memoria
        fprintf(stderr, "Error al asignar memoria\n");
        exit(EXIT_FAILURE);
    }

    return personas;
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
