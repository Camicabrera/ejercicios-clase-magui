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
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        personas[i].edad = 0;
        personas[i].nombre = NULL;
    }

    return personas;
}

// Función para inicializar un arreglo de n personas utilizando calloc
Persona* inicializarPersonasCalloc(int n) {
    Persona* personas = (Persona*)calloc(n, sizeof(Persona));

    if (personas == NULL) {
        // Manejo de error: no se pudo asignar memoria
        fprintf(stderr, "Error al asignar memoria\n");
        return NULL;
    }

    return personas;
}

int main() {
    int n = 5;

    Persona* personasMalloc = inicializarPersonasMalloc(n);
    if(!personasMalloc) return 1;

    Persona* personasCalloc = inicializarPersonasCalloc(n);
    if(!personasCalloc) return 1;


    free(personasMalloc);
    free(personasCalloc);

    return 0;
}
