#ifndef EJERCICIOS_H
#define EJERCICIOS_H

#include <cstddef>

// ============================================================================
// Tut 03 - Listas enlazadas e iteradores
//
// Este archivo declara la estructura de la lista simplemente enlazada que
// tenés que implementar en "ejercicios.cpp".
//
// El programa de prueba está en "main.cpp": compilá con `make` y corré
// `./ejercicios` para ver qué ejercicios pasan y cuáles todavía fallan.
//
// Importante: además de que los tests pasen, corré:
//     make valgrind
// para confirmar que no hay memory leaks ni accesos inválidos a memoria.
// ============================================================================

// ----------------------------------------------------------------------------
// Estructura del nodo
// ----------------------------------------------------------------------------
// El nodo es la unidad básica de la lista. Guarda un dato entero y un puntero
// al siguiente nodo (o nullptr si es el último).
struct Nodo
{
    int dato;
    Nodo *siguiente;

    // Constructor: inicializa el dato y el puntero siguiente
    Nodo(int valor, Nodo *sig = nullptr)
        : dato(valor), siguiente(sig) {}
};

// ----------------------------------------------------------------------------
// Clase ListaSimple
// ----------------------------------------------------------------------------
// Lista simplemente enlazada de enteros, con punteros al primero y al último,
// más un contador de elementos.
class ListaSimple
{
private:
    Nodo *primero;
    Nodo *ultimo;
    size_t largo;

public:
    // Constructor: inicializa una lista vacía.
    // Debe dejar primero y ultimo en nullptr, y largo en 0.
    ListaSimple();

    // Destructor: libera TODOS los nodos de la lista.
    // Si no se implementa correctamente, Valgrind reportará memory leaks.
    ~ListaSimple();

    // Devuelve true si la lista está vacía (no tiene nodos).
    bool vacia() const;

    // Devuelve la cantidad de elementos en la lista.
    size_t tamanio() const;

    // Ejercicio 1 — Insertar al inicio
    // Crea un nuevo nodo con el valor dado y lo inserta al principio de la
    // lista. Si la lista estaba vacía, el nuevo nodo es tanto el primero
    // como el último.
    void insertarAlInicio(int valor);

    // Ejercicio 2 — Insertar al final
    // Crea un nuevo nodo con el valor dado y lo inserta al final de la lista.
    // Si la lista estaba vacía, el nuevo nodo es tanto el primero como el
    // último.
    void insertarAlFinal(int valor);

    // Ejercicio 3 — Buscar un elemento
    // Devuelve true si el valor está en algún nodo de la lista, false si no.
    // No modifica la lista.
    bool buscar(int valor) const;

    // Ejercicio 4 — Obtener el primer elemento
    // Devuelve una referencia al dato del primer nodo.
    // Precondición: la lista no está vacía.
    int &frente();
    const int &frente() const;

    // Ejercicio 5 — Obtener el último elemento
    // Devuelve una referencia al dato del último nodo.
    // Precondición: la lista no está vacía.
    int &final();
    const int &final() const;

    // Ejercicio 6 — Eliminar el primer elemento
    // Elimina el primer nodo de la lista y libera su memoria.
    // Si la lista queda vacía, actualiza tanto primero como ultimo a nullptr.
    // Precondición: la lista no está vacía.
    void eliminarPrimero();

    // Ejercicio 7 — Eliminar por valor
    // Busca el primer nodo que contenga el valor dado y lo elimina.
    // Devuelve true si encontró y eliminó el nodo, false si el valor no estaba.
    // Debe manejar correctamente los casos:
    //   - Eliminar el único elemento
    //   - Eliminar el primero (pero hay más)
    //   - Eliminar el último (pero hay más)
    //   - Eliminar uno del medio
    bool eliminar(int valor);

    // Ejercicio 8 — Obtener elemento en posición i
    // Devuelve una referencia al dato del nodo en la posición i (0-indexado).
    // Precondición: i < tamanio()
    int &operator[](size_t i);
    const int &operator[](size_t i) const;

    // Propuesto 1 — Insertar en posición
    // Inserta un nuevo nodo con el valor dado en la posición i (0-indexado).
    // Si i == 0, es equivalente a insertarAlInicio.
    // Si i == tamanio(), es equivalente a insertarAlFinal.
    // Precondición: i <= tamanio()
    void insertarEnPosicion(size_t i, int valor);

    // Propuesto 2 — Invertir la lista
    // Invierte el orden de los nodos in-place (sin crear nodos nuevos).
    // Después de llamar a este método, el que era el último pasa a ser el
    // primero y viceversa.
    void invertir();
};

#endif
