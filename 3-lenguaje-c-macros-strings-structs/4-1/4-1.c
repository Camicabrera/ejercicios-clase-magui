#include <stdio.h>

typedef struct Persona { 
    char nombre[4];
    int edad;
} Persona;

char* masGrande(Persona** personas, int n) {
// TODO
    return "Juan";
}

int main(){

    Persona** lista_de_personas = malloc(size_of(Persona*) * 3);

    for(int i = 0; i< 3; i++) {
        lista_de_personas[i] = calloc(size_of(Persona));
    }

    lista_de_personas[0]->nombre = "maga";
    lista_de_personas[0]->edad = 27;

    lista_de_personas[1]->nombre = "gian";
    lista_de_personas[1]->edad = 37;

    lista_de_personas[2]->nombre = "juan";
    lista_de_personas[2]->edad = 10;


    char * mas_grande = masGrande(lista_de_personas);
    printf("%s", mas_grande);
    return 0;
}