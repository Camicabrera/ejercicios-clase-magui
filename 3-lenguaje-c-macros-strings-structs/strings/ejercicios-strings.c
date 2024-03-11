#define _GNU_SOURCE 
// ERROR: el compilador no ha encontrado una declaración explícita de la función getline. 
// Esto puede ocurrir porque el compilador no reconoce la función o porque no se ha incluido la cabecera adecuada.
#include <stdio.h>
#include <stdlib.h>

void ejercicio(const char *buffer, unsigned long len){
    int palabras = 0;
    printf("el largo recibido es: %lu \n", len);
    for(int i = 0; i <= len; i++) {
      if(buffer[i] == ' ' || buffer[i] == '\0') {
        palabras += 1;
      }
      if(buffer[i] == '\0' || (buffer[i+1] == '\0' && buffer[i] == ' ' )) break;
    }

    printf("la cantidad de palabras es: %d\n",palabras);
}

int main(int argc, char **argv) {
  char *buffer = NULL;
  size_t len;
  size_t read = getline(&buffer, &len, stdin);
  if (read != -1) {
    ejercicio(buffer, len);
  } else {
    printf("No se leyó ninguna línea\n");
  }

  free(buffer);
  return 0;
}
