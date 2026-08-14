#ifndef EJERCICIOS_H
#define EJERCICIOS_H

#include <string>
#include <vector>

// ============================================================================
// Tut 02 - Memoria dinámica y punteros
//
// Este archivo declara las funciones y clases que tenés que implementar en
// "ejercicios.cpp". Acá NO se escribe el cuerpo: solo se declara la firma.
//
// El programa de prueba está en "main.cpp": compilá con `make` y corré
// `./ejercicios` para ver qué ejercicios pasan y cuáles todavía fallan.
//
// Importante: en esta clase vas a trabajar con memoria dinámica (`new` /
// `delete`). Además de que los tests pasen, corré:
//     make valgrind
// para confirmar que no hay memory leaks ni accesos inválidos a memoria.
// ============================================================================

// Ejercicio 1 — Mi primer puntero
// Duplica el valor apuntado por `x` (es decir, hace `*x = *x * 2`).
void duplicarPuntero(int *x);

// Ejercicio 2 — Puntero vs referencia
// Igual que el ejercicio anterior, pero recibiendo `x` por referencia en
// lugar de por puntero.
void duplicarReferencia(int &x);

// Ejercicio 3 — Arreglo dinámico con new[]
// Reserva un arreglo dinámico de `n` enteros con `new[]` y lo llena con los
// cuadrados de 0 a n-1: { 0, 1, 4, 9, ... }.
// Quien llama a esta función es responsable de liberar la memoria con
// `delete[]` cuando termine de usarla.
int *crearArregloDeCuadrados(int n);

// Ejercicio 4 — Aritmética de punteros (lectura)
// Devuelve la suma de los `tamanio` elementos de `arreglo`, accediendo con
// aritmética de punteros (`*(arreglo + i)`) en lugar de `arreglo[i]`.
int sumarArregloPuntero(const int *arreglo, int tamanio);

// Ejercicio 5 — Aritmética de punteros (escritura)
// Duplica in-place cada uno de los `tamanio` elementos de `arreglo`, usando
// aritmética de punteros para escribir (`*(arreglo + i) = ...`).
void duplicarValores(int *arreglo, int tamanio);

// Ejercicio 6 — Struct en el heap: constructor y destructor
// Contador global: se incrementa cada vez que se destruye una Persona.
// Sirve para que "main.cpp" pueda verificar que tu destructor se ejecutó.
extern int personasDestruidas;

class Persona
{
public:
    std::string nombre;
    int edad;

    // Constructor: inicializa nombre y edad con los valores recibidos.
    Persona(const std::string &nombreInicial, int edadInicial);

    // Destructor: debe incrementar `personasDestruidas` en 1.
    ~Persona();
};

// Reserva una Persona en el heap (con `new`) usando el constructor de arriba,
// y devuelve el puntero. Quien llama es responsable de hacer `delete`.
Persona *crearPersona(const std::string &nombre, int edad);

// Ejercicio 7 — Redimensionar un arreglo dinámico
// Devuelve un NUEVO arreglo dinámico de tamaño `tamanioActual + 1`, con
// todos los elementos de `arreglo` más `nuevoElemento` al final. Además,
// libera (con `delete[]`) el arreglo viejo recibido por parámetro.
int *agregarElemento(int *arreglo, int tamanioActual, int nuevoElemento);

// Ejercicio 8 — Lista enlazada dinámica
struct Nodo
{
    int valor;
    Nodo *siguiente;
};

// Crea una cadena de nodos enlazados en el heap, uno por cada valor de
// `valores`, en el mismo orden, y devuelve un puntero al primer nodo
// (o `nullptr` si `valores` está vacío).
Nodo *crearCadena(const std::vector<int> &valores);

// Devuelve la suma de los valores de todos los nodos de la cadena que
// empieza en `cabeza`.
int sumarCadena(const Nodo *cabeza);

// Libera TODOS los nodos de la cadena que empieza en `cabeza` (sin memory
// leaks).
void liberarCadena(Nodo *cabeza);

// Propuesto 1 — Matriz dinámica
// Libera correctamente una matriz de `filas` filas creada como un arreglo de
// punteros (`int **matriz`, donde cada `matriz[i]` fue reservado por
// separado con `new int[columnas]`).
void liberarMatriz(int **matriz, int filas);

#endif
