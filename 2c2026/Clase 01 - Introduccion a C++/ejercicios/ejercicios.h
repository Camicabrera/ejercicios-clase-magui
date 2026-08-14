#ifndef EJERCICIOS_H
#define EJERCICIOS_H

#include <string>
#include <vector>

// ============================================================================
// Tut 01 - Introducción a C++
//
// Este archivo declara las funciones que tenés que implementar en
// "ejercicios.cpp". Acá NO se escribe el cuerpo de las funciones: solo se
// declara su firma (qué reciben y qué devuelven).
//
// El programa de prueba está en "main.cpp": compilá con `make` y corré
// `./ejercicios` para ver qué ejercicios pasan y cuáles todavía fallan.
// ============================================================================

// Ejercicio 1 — Hola, C++
// Devuelve un saludo con el formato exacto:
//     "Hola <nombre>, tenes <edad> anios."
// Ejemplo: saludo("Ada", 21)  ->  "Hola Ada, tenes 21 anios."
std::string saludo(const std::string &nombre, int edad);

// Ejercicio 2 — Par o impar
// Devuelve true si `numero` es par, y false si es impar. (Usá el operador %.)
bool esPar(int numero);

// Ejercicio 3 — Tabla de multiplicar
// Devuelve un vector con la tabla de `n` del 1 al 10:
//     { n*1, n*2, n*3, ..., n*10 }   (10 elementos)
std::vector<int> tablaDeMultiplicar(int n);

// Ejercicio 4 — esPrimo
// Devuelve true si `n` es un número primo, y false en caso contrario.
// Recordá: los números menores a 2 no son primos.
bool esPrimo(int n);

// Ejercicio 5 — swap por referencia
// Intercambia los valores de `a` y `b`. Como se reciben por referencia,
// los cambios se ven reflejados en las variables originales de quien la llama.
void swap(int &a, int &b);

// Ejercicio 6 — Sobrecarga: maximo
// Dos versiones con el mismo nombre: el compilador elige según los tipos.
// Cada una devuelve el mayor de los dos valores.
int maximo(int a, int b);
double maximo(double a, double b);

// Ejercicio 7 — Promedio de un arreglo
// Recibe un arreglo de enteros y su tamaño, y devuelve el promedio.
// Cuidado con la división entera: el resultado es un double.
double promedioArreglo(const int numeros[], int tamanio);

// Ejercicio 8 — vector de notas
// promedio: devuelve el promedio de las notas.
// maxima:   devuelve la nota más alta.
// (Podés asumir que el vector no está vacío.)
double promedio(const std::vector<double> &notas);
double maxima(const std::vector<double> &notas);

// Ejercicio 9 — Contar vocales
// Devuelve cuántas vocales (a, e, i, o, u) tiene `texto`, sin distinguir
// mayúsculas de minúsculas.
int contarVocales(const std::string &texto);

// Propuesto 1 — invertir in-place
// Invierte el orden de los elementos de `v` SIN crear otro vector.
void invertir(std::vector<int> &v);

// Propuesto 2 — contar palabras
// Devuelve la cantidad de palabras de `oracion`, asumiendo que están
// separadas por un único espacio. Ejemplo: "hola que tal" -> 3.
int contarPalabras(const std::string &oracion);

// Ejercicio 10 — Clase Punto
// Representa un punto en el plano. Implementá el constructor y los métodos
// en "ejercicios.cpp", usando la sintaxis Punto::nombreDelMetodo(...) { ... }
class Punto
{
public:
    double x;
    double y;

    // Constructor: inicializa x e y con los valores recibidos.
    Punto(double xInicial, double yInicial);

    // Devuelve la distancia entre este punto y el origen (0, 0).
    double distanciaAlOrigen() const;

    // Devuelve la distancia entre este punto y `otro`.
    double distanciaA(const Punto &otro) const;
};

// Ejercicio 11 — Clase Rectangulo
// Representa un rectángulo a partir de su base y su altura.
class Rectangulo
{
public:
    double base;
    double altura;

    // Constructor: inicializa base y altura con los valores recibidos.
    Rectangulo(double baseInicial, double alturaInicial);

    // Devuelve el área del rectángulo (base * altura).
    double area() const;

    // Devuelve el perímetro del rectángulo (2 * (base + altura)).
    double perimetro() const;

    // Devuelve true si el rectángulo es un cuadrado (base == altura).
    bool esCuadrado() const;
};

#endif
