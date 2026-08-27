#ifndef EJERCICIOS_H
#define EJERCICIOS_H

#include <cstddef>
#include <string>

// ============================================================================
// Tut 04 - Pilas y Colas
//
// Este archivo declara las clases y funciones que tenés que implementar en
// "ejercicios.cpp".
//
// El programa de prueba está en "main.cpp": compilá con `make` y corré
// `./ejercicios` para ver qué ejercicios pasan y cuáles todavía fallan.
//
// Importante: además de que los tests pasen, corré:
//     make valgrind
// para confirmar que no hay memory leaks ni accesos inválidos a memoria.
// ============================================================================

// ----------------------------------------------------------------------------
// Ejercicio 1 — Pila sobre arreglo
// ----------------------------------------------------------------------------
// Pila (LIFO) de enteros implementada sobre un arreglo dinámico que duplica
// su capacidad cuando se llena.
class PilaArreglo
{
private:
    int *datos;
    size_t capacidad;
    size_t cantidad;

    // Duplica la capacidad del arreglo interno y copia los elementos
    // existentes al nuevo arreglo.
    void redimensionar();

public:
    // Constructor: inicializa una pila vacía con capacidad 1.
    PilaArreglo();

    // Destructor: libera el arreglo interno.
    ~PilaArreglo();

    // Agrega `valor` al tope de la pila. Redimensiona si hace falta.
    void push(int valor);

    // Elimina y devuelve el elemento del tope.
    // Precondición: !empty()
    int pop();

    // Devuelve el elemento del tope sin eliminarlo.
    // Precondición: !empty()
    int top() const;

    // Indica si la pila está vacía.
    bool empty() const;

    // Devuelve la cantidad de elementos.
    size_t tamanio() const;
};

// ----------------------------------------------------------------------------
// Ejercicio 2 — Cola sobre arreglo (buffer circular)
// ----------------------------------------------------------------------------
// Cola (FIFO) de enteros implementada sobre un arreglo dinámico usando un
// buffer circular: los índices "dan la vuelta" con módulo cuando llegan al
// final del arreglo, para que enqueue y dequeue sean O(1).
class ColaArreglo
{
private:
    int *datos;
    size_t capacidad;
    size_t frente; // índice del primer elemento
    size_t cantidad;

    // Duplica la capacidad del arreglo interno, "desenrollando" el buffer
    // circular en el nuevo arreglo en el orden correcto.
    void redimensionar();

public:
    // Constructor: inicializa una cola vacía con capacidad 1.
    ColaArreglo();

    // Destructor: libera el arreglo interno.
    ~ColaArreglo();

    // Agrega `valor` al final de la cola. Redimensiona si hace falta.
    void enqueue(int valor);

    // Elimina y devuelve el elemento del frente.
    // Precondición: !empty()
    int dequeue();

    // Devuelve el elemento del frente sin eliminarlo.
    // Precondición: !empty()
    int front() const;

    // Indica si la cola está vacía.
    bool empty() const;

    // Devuelve la cantidad de elementos.
    size_t tamanio() const;
};

// ----------------------------------------------------------------------------
// Nodo para las implementaciones sobre lista enlazada
// ----------------------------------------------------------------------------
struct Nodo
{
    int dato;
    Nodo *siguiente;

    Nodo(int valor, Nodo *sig = nullptr) : dato(valor), siguiente(sig) {}
};

// ----------------------------------------------------------------------------
// Ejercicio 3 — Pila sobre lista enlazada
// ----------------------------------------------------------------------------
// Pila (LIFO) de enteros implementada sobre una lista simplemente enlazada.
// push y pop operan siempre sobre `tope`: no hace falta puntero al final.
class PilaLista
{
private:
    Nodo *tope;
    size_t cantidad;

public:
    // Constructor: inicializa una pila vacía.
    PilaLista();

    // Destructor: libera TODOS los nodos de la pila.
    ~PilaLista();

    // Agrega `valor` al tope de la pila.
    void push(int valor);

    // Elimina y devuelve el elemento del tope, liberando su nodo.
    // Precondición: !empty()
    int pop();

    // Devuelve el elemento del tope sin eliminarlo.
    // Precondición: !empty()
    int top() const;

    // Indica si la pila está vacía.
    bool empty() const;

    // Devuelve la cantidad de elementos.
    size_t tamanio() const;
};

// ----------------------------------------------------------------------------
// Ejercicio 4 — Cola sobre lista enlazada
// ----------------------------------------------------------------------------
// Cola (FIFO) de enteros implementada sobre una lista simplemente enlazada
// que mantiene punteros a `primero` y `ultimo`, para que enqueue y dequeue
// sean O(1) sin necesitar módulo ni redimensionamiento.
class ColaLista
{
private:
    Nodo *primero;
    Nodo *ultimo;
    size_t cantidad;

public:
    // Constructor: inicializa una cola vacía.
    ColaLista();

    // Destructor: libera TODOS los nodos de la cola.
    ~ColaLista();

    // Agrega `valor` al final de la cola.
    void enqueue(int valor);

    // Elimina y devuelve el elemento del frente, liberando su nodo.
    // Precondición: !empty()
    int dequeue();

    // Devuelve el elemento del frente sin eliminarlo.
    // Precondición: !empty()
    int front() const;

    // Indica si la cola está vacía.
    bool empty() const;

    // Devuelve la cantidad de elementos.
    size_t tamanio() const;
};

// ----------------------------------------------------------------------------
// Ejercicio 5 — Balanceo de expresiones
// ----------------------------------------------------------------------------
// Indica si una expresión tiene correctamente balanceados los símbolos
// (), [] y {} (cada símbolo de apertura cierra con el símbolo correspondiente
// y en el orden correcto). El resto de los caracteres se ignoran.
// Usá una PilaArreglo internamente.
//
// Ejemplos:
//   estaBalanceada("(a + [b - {c}]) * 2")  -> true
//   estaBalanceada("(a + [b)]")             -> false  (cierres cruzados)
//   estaBalanceada("(a + b")                -> false  (falta cerrar)
//   estaBalanceada("a + b)")                -> false  (cierre sin apertura)
bool estaBalanceada(const std::string &expresion);

// ----------------------------------------------------------------------------
// Ejercicio 6 — Evaluación de una expresión postfija (RPN)
// ----------------------------------------------------------------------------
// Evalúa una expresión matemática en notación postfija (los tokens —números
// u operadores— están separados por espacios), usando una PilaArreglo. Los
// operadores soportados son +, -, *, / y operan sobre enteros.
//
// Ejemplo: evaluarPostfija("2 3 4 * +") -> 14   (equivale a 2 + 3*4)
// Precondición: `expresion` es una expresión postfija válida.
int evaluarPostfija(const std::string &expresion);

// ----------------------------------------------------------------------------
// Propuesto 1 — Invertir una pila usando una cola auxiliar
// ----------------------------------------------------------------------------
// Invierte el orden de los elementos de `pila` (el que estaba en el tope
// queda en el fondo y viceversa), usando ÚNICAMENTE una ColaArreglo como
// estructura auxiliar.
void invertirPila(PilaArreglo &pila);

// ----------------------------------------------------------------------------
// Propuesto 2 — Cola implementada con dos pilas
// ----------------------------------------------------------------------------
// Implementación clásica de una cola (FIFO) usando dos pilas (LIFO) como
// estructura interna: `entrada` recibe los enqueue; cuando `salida` queda
// vacía, se vuelca todo el contenido de `entrada` a `salida` (invirtiéndolo),
// de forma que `salida` siempre tiene el frente de la cola en su tope.
class ColaConDosPilas
{
private:
    PilaArreglo entrada;
    PilaArreglo salida;

public:
    // Agrega `valor` al final de la cola.
    void enqueue(int valor);

    // Elimina y devuelve el elemento del frente.
    // Precondición: !empty()
    int dequeue();

    // Devuelve el elemento del frente sin eliminarlo.
    // Precondición: !empty()
    int front();

    // Indica si la cola está vacía.
    bool empty() const;

    // Devuelve la cantidad de elementos.
    size_t tamanio() const;
};

#endif
