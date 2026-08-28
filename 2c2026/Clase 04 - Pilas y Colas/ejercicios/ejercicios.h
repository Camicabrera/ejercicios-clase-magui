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

// ----------------------------------------------------------------------------
// Propuesto 3 — Pila con mínimo en O(1)
// ----------------------------------------------------------------------------
// Pila que, además de las operaciones habituales, permite consultar el
// mínimo elemento almacenado en O(1) (no alcanza con recorrer la pila: hay
// que mantenerlo actualizado en cada push/pop).
// Pista: además de la pila de valores, mantené una segunda PilaArreglo con
// los mínimos "vigentes" en cada momento.
class PilaConMinimo
{
private:
    PilaArreglo valores;
    PilaArreglo minimos;

public:
    // Agrega `valor` al tope de la pila.
    void push(int valor);

    // Elimina y devuelve el elemento del tope.
    // Precondición: !empty()
    int pop();

    // Devuelve el elemento del tope sin eliminarlo.
    // Precondición: !empty()
    int top() const;

    // Devuelve el mínimo valor almacenado actualmente en la pila, en O(1).
    // Precondición: !empty()
    int minimo() const;

    // Indica si la pila está vacía.
    bool empty() const;

    // Devuelve la cantidad de elementos.
    size_t tamanio() const;
};

// ----------------------------------------------------------------------------
// Propuesto 4 — Conversión de infija a postfija (Shunting-yard)
// ----------------------------------------------------------------------------
// Convierte una expresión matemática en notación infija (con paréntesis y
// precedencia de operadores +, -, *, /) a su equivalente en notación
// postfija, usando una pila para los operadores.
//
// Tanto la expresión de entrada como la de salida tienen sus tokens
// (números, operadores y paréntesis) separados por espacios, igual que en
// `evaluarPostfija`.
//
// Ejemplos:
//   infijaAPostfija("3 + 4")             -> "3 4 +"
//   infijaAPostfija("3 + 4 * 2")         -> "3 4 2 * +"
//   infijaAPostfija("( 3 + 4 ) * 2")     -> "3 4 + 2 *"
// Precondición: `expresionInfija` es una expresión infija válida y
// balanceada, con un único dígito por número.
std::string infijaAPostfija(const std::string &expresionInfija);

// ----------------------------------------------------------------------------
// Propuesto 5 — Sistema de deshacer/rehacer (undo/redo)
// ----------------------------------------------------------------------------
// Modela el "deshacer/rehacer" de un editor (ver la sección "Casos de uso"
// del apunte) usando dos pilas: una de estados para deshacer y otra para
// rehacer. Cada estado es, para simplificar, un entero.
class EditorDeshacerRehacer
{
private:
    PilaArreglo deshacer;
    PilaArreglo rehacer;
    int estadoActual;

public:
    // Constructor: inicializa el editor con el estado inicial dado.
    EditorDeshacerRehacer(int estadoInicial);

    // Aplica una nueva acción que lleva al editor a `nuevoEstado`.
    // El estado anterior pasa a la pila de deshacer, y se descarta
    // cualquier historial de rehacer pendiente (una acción nueva invalida
    // los "rehacer" que hubiera).
    void aplicar(int nuevoEstado);

    // Deshace la última acción: vuelve al estado anterior (que pasa a la
    // pila de deshacer) y lo agrega a la pila de rehacer. Devuelve el
    // estado actual después de deshacer.
    // Precondición: puedeDeshacer()
    int deshacerAccion();

    // Rehace la última acción deshecha. Devuelve el estado actual después
    // de rehacer.
    // Precondición: puedeRehacer()
    int rehacerAccion();

    // Devuelve el estado actual del editor.
    int estado() const;

    // Indica si hay alguna acción para deshacer.
    bool puedeDeshacer() const;

    // Indica si hay alguna acción para rehacer.
    bool puedeRehacer() const;
};

#endif
