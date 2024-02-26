 #include <stdio.h>

int esBisiesto(int anio) {
    // Un año es bisiesto si es divisible por 4, pero no por 100, a menos que también sea divisible por 400
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
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