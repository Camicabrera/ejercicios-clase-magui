// ============================================================================
// Ingeniería en Inteligencia Artificial - Algoritmos y Estructura de Datos
// 2C 2026 | Docente: Magali Marijuan
// ============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "ejercicios.h"

// ============================================================================
// Driver de pruebas.
//
// NO hace falta que edites este archivo: sirve para chequear tus soluciones.
// Compilá con `make` y corré `./ejercicios`. Cada línea muestra [PASA] o
// [FALLA] según si la función correspondiente ya funciona.
//
// Al principio va a fallar casi todo (las funciones son cáscaras vacías).
// A medida que las vayas implementando en "ejercicios.cpp", van a ir pasando.
// ============================================================================

static int totalPruebas = 0;
static int pruebasOk = 0;

static void chequear(const std::string &nombre, bool condicion) {
    totalPruebas++;
    if (condicion) {
        pruebasOk++;
        std::cout << "[PASA]  " << nombre << std::endl;
    } else {
        std::cout << "[FALLA] " << nombre << std::endl;
    }
}

// Comparación de doubles con tolerancia (evita problemas de redondeo).
static bool casiIgual(double a, double b) {
    return std::fabs(a - b) < 1e-9;
}

int main() {
    // Ejercicio 1
    chequear("Ej1 - saludo", saludo("Ada", 21) == "Hola Ada, tenes 21 anios.");

    // Ejercicio 2
    chequear("Ej2 - esPar(4)", esPar(4));
    chequear("Ej2 - esPar(7)", !esPar(7));

    // Ejercicio 3
    std::vector<int> tabla = tablaDeMultiplicar(5);
    chequear("Ej3 - tablaDeMultiplicar(5)",
             tabla.size() == 10u && tabla.front() == 5 && tabla.back() == 50);

    // Ejercicio 4
    chequear("Ej4 - esPrimo(7)", esPrimo(7));
    chequear("Ej4 - esPrimo(8)", !esPrimo(8));
    chequear("Ej4 - esPrimo(1)", !esPrimo(1));

    // Ejercicio 5
    int a = 3;
    int b = 8;
    swap(a, b);
    chequear("Ej5 - swap", a == 8 && b == 3);

    // Ejercicio 6
    chequear("Ej6 - maximo(int)", maximo(3, 7) == 7);
    chequear("Ej6 - maximo(double)", casiIgual(maximo(3.5, 2.1), 3.5));

    // Ejercicio 7
    int numeros[5] = {2, 4, 6, 8, 10};
    chequear("Ej7 - promedioArreglo", casiIgual(promedioArreglo(numeros, 5), 6.0));

    // Ejercicio 8
    std::vector<double> notas = {4.0, 6.0, 8.0};
    chequear("Ej8 - promedio", casiIgual(promedio(notas), 6.0));
    chequear("Ej8 - maxima", casiIgual(maxima(notas), 8.0));

    // Ejercicio 9
    chequear("Ej9 - contarVocales", contarVocales("Murcielago") == 5);

    // Propuesto 1
    std::vector<int> v = {1, 2, 3};
    invertir(v);
    chequear("P1  - invertir", v.size() == 3u && v[0] == 3 && v[1] == 2 && v[2] == 1);

    // Propuesto 2
    chequear("P2  - contarPalabras", contarPalabras("hola que tal") == 3);

    std::cout << "\nResultado: " << pruebasOk << "/" << totalPruebas
              << " pruebas pasadas." << std::endl;

    return 0;
}
