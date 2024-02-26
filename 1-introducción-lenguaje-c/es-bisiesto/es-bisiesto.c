 #include <stdio.h>

int esBisiesto(int anio) {
   return 1;
}

void realizarPrueba(int anio, int esperado) {
    int resultado = esBisiesto(anio);
    
    printf("Prueba para el año %d: ", anio);
    
    if (resultado == esperado) {
        printf("Aprobada\n");
    } else {
        printf("Falla la prueba\n");
    }
}

int main() {
    realizarPrueba(2000, 1); 
    realizarPrueba(2021, 0);  
    realizarPrueba(2100, 0);  
    realizarPrueba(2400, 1); 
    realizarPrueba(2024, 1); 

    return 0;
}