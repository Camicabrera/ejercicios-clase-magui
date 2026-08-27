#include "ejercicios.h"

// ============================================================================
// Acá va TU código. Cada función tiene una cáscara con un "TODO": borrá el
// contenido de ejemplo y escribí la implementación.
// ============================================================================

// ----------------------------------------------------------------------------
// Ejercicio 1 — Pila sobre arreglo
// ----------------------------------------------------------------------------

PilaArreglo::PilaArreglo()
    : datos(new int[1]), capacidad(1), cantidad(0)
{
    // Ya está implementado. No hace falta que modifiques nada acá.
}

PilaArreglo::~PilaArreglo()
{
    // Ya está implementado: un solo arreglo que liberar.
    delete[] datos;
}

bool PilaArreglo::empty() const
{
    // Ya está implementado.
    return cantidad == 0;
}

size_t PilaArreglo::tamanio() const
{
    // Ya está implementado.
    return cantidad;
}

void PilaArreglo::redimensionar()
{
    // TODO: duplicar `capacidad`, reservar un arreglo nuevo con esa
    // capacidad, copiar los `cantidad` elementos existentes, liberar el
    // arreglo viejo y actualizar `datos`.
    (void)capacidad; // Silencia warning hasta que implementes la función
}

void PilaArreglo::push(int valor)
{
    // TODO: si el arreglo está lleno (cantidad == capacidad), redimensionar.
    // Después, agregar `valor` en la posición `cantidad` e incrementar
    // `cantidad`.
    (void)valor;
}

int PilaArreglo::pop()
{
    // TODO: decrementar `cantidad` y devolver el valor que quedó en esa
    // posición (el que era el tope).
    // Precondición: !empty()
    return 0;
}

int PilaArreglo::top() const
{
    // TODO: devolver el valor de la posición `cantidad - 1`.
    // Precondición: !empty()
    return 0;
}

// ----------------------------------------------------------------------------
// Ejercicio 2 — Cola sobre arreglo (buffer circular)
// ----------------------------------------------------------------------------

ColaArreglo::ColaArreglo()
    : datos(new int[1]), capacidad(1), frente(0), cantidad(0)
{
    // Ya está implementado. No hace falta que modifiques nada acá.
}

ColaArreglo::~ColaArreglo()
{
    // Ya está implementado: un solo arreglo que liberar.
    delete[] datos;
}

bool ColaArreglo::empty() const
{
    // Ya está implementado.
    return cantidad == 0;
}

size_t ColaArreglo::tamanio() const
{
    // Ya está implementado.
    return cantidad;
}

void ColaArreglo::redimensionar()
{
    // TODO: duplicar `capacidad`, reservar un arreglo nuevo con esa
    // capacidad y "desenrollar" el buffer circular viejo en el nuevo arreglo,
    // en orden, empezando desde `frente` (usando módulo sobre la capacidad
    // VIEJA). Liberar el arreglo viejo, actualizar `datos` y `capacidad`, y
    // dejar `frente` en 0 (ahora el primer elemento quedó en la posición 0).
    (void)capacidad; // Silencia warnings hasta que implementes la función
    (void)frente;
}

void ColaArreglo::enqueue(int valor)
{
    // TODO: si el arreglo está lleno (cantidad == capacidad), redimensionar.
    // Después, calcular la posición de inserción como
    // (frente + cantidad) % capacidad, guardar `valor` ahí, e incrementar
    // `cantidad`.
    (void)valor;
}

int ColaArreglo::dequeue()
{
    // TODO: guardar el valor en la posición `frente`, avanzar `frente`
    // circularmente ((frente + 1) % capacidad), decrementar `cantidad` y
    // devolver el valor guardado.
    // Precondición: !empty()
    return 0;
}

int ColaArreglo::front() const
{
    // TODO: devolver el valor en la posición `frente`.
    // Precondición: !empty()
    return 0;
}

// ----------------------------------------------------------------------------
// Ejercicio 3 — Pila sobre lista enlazada
// ----------------------------------------------------------------------------

PilaLista::PilaLista()
    : tope(nullptr), cantidad(0)
{
    // Ya está implementado. No hace falta que modifiques nada acá.
}

PilaLista::~PilaLista()
{
    // TODO: recorrer la pila haciendo pop() (o liberando nodo por nodo) hasta
    // que quede vacía.
}

bool PilaLista::empty() const
{
    // Ya está implementado.
    return tope == nullptr;
}

size_t PilaLista::tamanio() const
{
    // Ya está implementado.
    return cantidad;
}

void PilaLista::push(int valor)
{
    // TODO: crear un nuevo nodo cuyo `siguiente` sea el `tope` actual, y
    // hacer que ese nuevo nodo pase a ser el `tope`. Incrementar `cantidad`.
    (void)valor;
}

int PilaLista::pop()
{
    // TODO: guardar el dato del `tope`, actualizar `tope` para que apunte al
    // siguiente nodo, liberar el nodo viejo con delete, decrementar
    // `cantidad` y devolver el dato guardado.
    // Precondición: !empty()
    return 0;
}

int PilaLista::top() const
{
    // TODO: devolver el dato del nodo `tope`.
    // Precondición: !empty()
    return 0;
}

// ----------------------------------------------------------------------------
// Ejercicio 4 — Cola sobre lista enlazada
// ----------------------------------------------------------------------------

ColaLista::ColaLista()
    : primero(nullptr), ultimo(nullptr), cantidad(0)
{
    // Ya está implementado. No hace falta que modifiques nada acá.
}

ColaLista::~ColaLista()
{
    // TODO: recorrer la cola haciendo dequeue() (o liberando nodo por nodo)
    // hasta que quede vacía.
    (void)ultimo; // Silencia warning hasta que implementes las funciones
}

bool ColaLista::empty() const
{
    // Ya está implementado.
    return primero == nullptr;
}

size_t ColaLista::tamanio() const
{
    // Ya está implementado.
    return cantidad;
}

void ColaLista::enqueue(int valor)
{
    // TODO: crear un nuevo nodo. Si la cola estaba vacía, `primero` y
    // `ultimo` pasan a ser ese nuevo nodo. Si no, enlazar el nuevo nodo
    // después de `ultimo` y actualizar `ultimo`. Incrementar `cantidad`.
    (void)valor;
}

int ColaLista::dequeue()
{
    // TODO: guardar el dato de `primero`, actualizar `primero` para que
    // apunte al siguiente nodo (si la cola queda vacía, `ultimo` también
    // debe quedar en nullptr), liberar el nodo viejo con delete, decrementar
    // `cantidad` y devolver el dato guardado.
    // Precondición: !empty()
    return 0;
}

int ColaLista::front() const
{
    // TODO: devolver el dato del nodo `primero`.
    // Precondición: !empty()
    return 0;
}

// ----------------------------------------------------------------------------
// Ejercicio 5 — Balanceo de expresiones
// ----------------------------------------------------------------------------

bool estaBalanceada(const std::string &expresion)
{
    // TODO: recorrer la expresión carácter por carácter.
    //   - Si es un símbolo de apertura ( ( [ { ), apilarlo.
    //   - Si es un símbolo de cierre ( ) ] } ), la pila no debe estar vacía
    //     y el tope debe ser el símbolo de apertura correspondiente; en ese
    //     caso, desapilarlo. Si no se cumple, la expresión no está
    //     balanceada.
    //   - Cualquier otro carácter se ignora.
    // Al final, la expresión está balanceada si y solo si la pila quedó
    // vacía (no quedaron aperturas sin cerrar).
    (void)expresion;
    return false;
}

// ----------------------------------------------------------------------------
// Ejercicio 6 — Evaluación de una expresión postfija (RPN)
// ----------------------------------------------------------------------------

int evaluarPostfija(const std::string &expresion)
{
    // TODO: separar `expresion` en tokens por espacios (podés usar un
    // std::istringstream). Por cada token:
    //   - Si es un número, apilarlo (podés convertirlo con std::stoi).
    //   - Si es un operador (+, -, *, /), desapilar dos operandos (el
    //     segundo desapilado es el operando izquierdo), aplicar la
    //     operación y apilar el resultado.
    // Al final, el resultado es el único valor que queda en la pila.
    (void)expresion;
    return 0;
}

// ----------------------------------------------------------------------------
// Propuesto 1 — Invertir una pila usando una cola auxiliar
// ----------------------------------------------------------------------------

void invertirPila(PilaArreglo &pila)
{
    // TODO: usando una única ColaArreglo auxiliar, invertir el orden de los
    // elementos de `pila`.
    // Pista: si vas desapilando `pila` y encolando cada valor en la cola
    // (en ese orden), y después vas desencolando y apilando de nuevo en
    // `pila`, el resultado queda invertido. Pensá por qué.
    (void)pila;
}

// ----------------------------------------------------------------------------
// Propuesto 2 — Cola implementada con dos pilas
// ----------------------------------------------------------------------------

void ColaConDosPilas::enqueue(int valor)
{
    // TODO: apilar `valor` en `entrada`.
    (void)valor;
}

int ColaConDosPilas::dequeue()
{
    // TODO: si `salida` está vacía, volcar todo el contenido de `entrada`
    // en `salida` (desapilando de una y apilando en la otra), lo que
    // invierte el orden. Después, desapilar y devolver el tope de `salida`.
    // Precondición: !empty()
    return 0;
}

int ColaConDosPilas::front()
{
    // TODO: igual que dequeue(), pero sin eliminar el elemento (usar top()
    // de `salida` en vez de pop()).
    // Precondición: !empty()
    return 0;
}

bool ColaConDosPilas::empty() const
{
    // TODO: la cola está vacía si y solo si AMBAS pilas están vacías.
    return true;
}

size_t ColaConDosPilas::tamanio() const
{
    // TODO: la cantidad total de elementos es la suma de los tamaños de
    // ambas pilas.
    return 0;
}
