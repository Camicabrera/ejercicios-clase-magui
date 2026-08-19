// ============================================================================
// Ingeniería en Inteligencia Artificial - Algoritmos y Estructura de Datos
// 2C 2026 | Docente: Ing. Magali Marijuan
// ============================================================================

#include "ejercicios.h"

// ============================================================================
// Acá va TU código. Cada función tiene una cáscara con un "TODO": borrá el
// contenido de ejemplo y escribí la implementación.
//
// Los `(void)parametro;` que ves abajo están solo para que la cáscara
// compile sin advertencias antes de que la implementes. Cuando uses el
// parámetro en tu código, borrá la línea `(void)...` correspondiente.
// ============================================================================


// Ejercicio 1 — Hola, C++
std::string saludo(const std::string &nombre, int edad) {
    // TODO: armar y devolver el saludo con el formato pedido.
    (void)nombre;
    (void)edad;
    return "Hola " + nombre + ", tenes " + std::to_string(edad) + " anios.";
}



// Ejercicio 2 — Par o impar
bool esPar(int numero) {
    // TODO: devolver true si numero es par.
    (void)numero;
    if (numero%2 == 0){
        return true;
    }
    else{
        return false;
    }
}


// Ejercicio 3 — Tabla de multiplicar
std::vector<int> tablaDeMultiplicar(int n) {
    // TODO: llenar el vector con n*1, n*2, ..., n*10 y devolverlo.
    (void)n;
    return {n*1,n*2,n*3,n*4,n*5,n*6,n*7,n*8,n*9,n*10};
}


// Ejercicio 4 — esPrimo
bool esPrimo(int n) {
    // TODO: determinar si n es primo.
    (void)n;
    if (n <= 1) {
    return false;
    }
    for (int i=2;i<n-1;i++){
        if (n%i==0){
            return false;
        }
    }
    return true;
}


// Ejercicio 5 — swap por referencia
void swap(int &a, int &b) {
    // TODO: intercambiar los valores de a y b.
    (void)a;
    (void)b;

    int extra =a;
    a=b;
    b= extra;

}


// Ejercicio 6 — Sobrecarga: maximo
int maximo(int a, int b) {
    // TODO: devolver el mayor entre a y b.
    (void)a;
    (void)b;
    if (a>b){
        return a;
    }
    return b;
}

double maximo(double a, double b) {
    // TODO: devolver el mayor entre a y b.
    (void)a;
    (void)b;
    if (a>b){
        return a;
    }
    return b;


}


// Ejercicio 7 — Promedio de un arreglo
double promedioArreglo(const int numeros[], int tamanio) {
    // TODO: sumar los elementos y dividir por tamanio (ojo con la división entera).
    (void)numeros;
    (void)tamanio;
    double cuenta=0.0;
        for (int i=0;i<tamanio;i++){
        cuenta += numeros[i];
    }
    return (double) cuenta/tamanio;

}


// Ejercicio 8 — vector de notas
double promedio(const std::vector<double> &notas) {
    // TODO: devolver el promedio de las notas.
    (void)notas;
    double suma=0;
    double largo= (double) notas.size(); 

    for (int i=0; i< largo;i++){
        suma+=notas[i];
    }

    double resultado= suma/largo;
    return resultado;
}

double maxima(const std::vector<double> &notas) {
    // TODO: devolver la nota más alta.
    (void)notas;
    double maxima=0.0;
    double largo= (double) notas.size();
    for (int i=0; i<largo;i++){
        if (notas[i] > maxima){
            maxima= notas[i];
        }
    }
    return maxima;

}


// Ejercicio 9 — Contar vocales
int contarVocales(const std::string &texto) {
    // TODO: contar vocales sin distinguir mayúsculas de minúsculas.
    (void)texto;
    int suma=0;
    int largo=(int)texto.size();
    for (int i=0;i<largo;i++){
        if (texto[i]=='A' || texto[i]=='a'){
            suma ++;
        }
        else if (texto[i]=='E' || texto[i]=='e'){
            suma ++;
        }
        else if (texto[i]=='I' || texto[i]=='i'){
            suma ++;
        }
        else if (texto[i]=='O' || texto[i]=='o'){
            suma ++;
        }
        else if (texto[i]=='U' || texto[i]=='u'){
            suma ++;
        }
    }
    
    
    return suma;
}


// Propuesto 1 — invertir in-place
void invertir(std::vector<int> &v) {
    // TODO: invertir el orden de los elementos sin crear otro vector.
    (void)v;
    size_t i=0;
    size_t j=v.size()-1;
    while (i<j){
        int intermedio= v[i];
        v[i]=v[j];
        v[j]=intermedio;

        i++;
        j--;
    }
}


// Propuesto 2 — contar palabras
int contarPalabras(const std::string &oracion) {
    // TODO: contar palabras separadas por un único espacio.
    (void)oracion;
    int fin= (int)oracion.size();
    int palabras=0;

    for (int i=0; i<=fin;i++){
        if (i==fin){
            palabras ++;
        }
        else if (oracion[i]==' '){
            palabras++;
        }
    }
    return palabras;
}


// Ejercicio 10 — Clase Punto
Punto::Punto(double xInicial, double yInicial)
{
    // TODO: inicializar x e y con los valores recibidos.
    (void)xInicial;
    (void)yInicial;
    x = xInicial;
    y= yInicial;

}

double Punto::distanciaAlOrigen() const
{
    // TODO: devolver la distancia entre este punto y el origen (0, 0).
    
    return 0.0;
}

double Punto::distanciaA(const Punto &otro) const
{
    // TODO: devolver la distancia entre este punto y "otro".
    (void)otro;

    return 0.0;
}

// Ejercicio 11 — Clase Rectangulo
Rectangulo::Rectangulo(double baseInicial, double alturaInicial)
{
    // TODO: inicializar base y altura con los valores recibidos.
    (void)baseInicial;
    (void)alturaInicial;
}

double Rectangulo::area() const
{
    // TODO: devolver el área del rectángulo (base * altura).
    return 0.0;
}

double Rectangulo::perimetro() const
{
    // TODO: devolver el perímetro del rectángulo (2 * (base + altura)).
    return 0.0;
}

bool Rectangulo::esCuadrado() const
{
    // TODO: devolver true si el rectángulo es un cuadrado (base == altura).
    return false;
}
