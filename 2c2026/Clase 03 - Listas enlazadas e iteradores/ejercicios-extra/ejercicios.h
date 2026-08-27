#ifndef EJERCICIOS_EXTRA_H
#define EJERCICIOS_EXTRA_H

#include <cstddef>
#include <vector>

// ============================================================================
// Tut 03 - Listas enlazadas e iteradores (EXTRA)
//
// Ejercicios adicionales sobre lista doblemente enlazada, lista circular e
// iteradores. Son independientes de la carpeta "ejercicios/": no hace falta
// haber terminado esos ejercicios para encarar estos.
//
// El programa de prueba está en "main.cpp": compilá con `make` y corré
// `./ejercicios-extra` para ver qué ejercicios pasan y cuáles todavía fallan.
//
// Importante: además de que los tests pasen, corré:
//     make valgrind
// para confirmar que no hay memory leaks ni accesos inválidos a memoria.
// ============================================================================

// ----------------------------------------------------------------------------
// Lista doblemente enlazada
// ----------------------------------------------------------------------------
// A diferencia del nodo simple, cada nodo conoce al siguiente Y al anterior.
struct NodoDoble
{
    int dato;
    NodoDoble *siguiente;
    NodoDoble *anterior;

    NodoDoble(int valor, NodoDoble *sig = nullptr, NodoDoble *ant = nullptr)
        : dato(valor), siguiente(sig), anterior(ant) {}
};

class ListaDoble
{
private:
    NodoDoble *primero;
    NodoDoble *ultimo;
    size_t largo;

public:
    // Constructor: inicializa una lista vacía.
    ListaDoble();

    // Ejercicio D1 — Destructor
    // Libera TODOS los nodos de la lista. Si no se implementa correctamente,
    // Valgrind reportará memory leaks.
    ~ListaDoble();

    bool vacia() const;
    size_t tamanio() const;

    // Ejercicio D2 — Insertar al inicio
    // Igual que en la lista simple, pero acordate de actualizar también el
    // puntero `anterior` del que era el primero.
    void insertarAlInicio(int valor);

    // Ejercicio D3 — Insertar al final
    // Acordate de enlazar `anterior` del nuevo nodo con el viejo `ultimo`.
    void insertarAlFinal(int valor);

    // Ejercicio D4 — Eliminar al inicio
    // Precondición: la lista no está vacía.
    void eliminarAlInicio();

    // Ejercicio D5 — Eliminar al final
    // Gracias al puntero `anterior`, esta operación es O(1) (a diferencia de
    // la lista simple, donde era O(n)).
    // Precondición: la lista no está vacía.
    void eliminarAlFinal();

    // Ejercicio D6 — Buscar un elemento
    // Devuelve true si el valor está en algún nodo de la lista.
    bool buscar(int valor) const;

    // Ejercicio D7 — Recorrido hacia atrás
    // Devuelve un vector con los elementos de la lista en orden inverso
    // (del último al primero), recorriendo con el puntero `anterior`.
    std::vector<int> aVectorInverso() const;
};

// ----------------------------------------------------------------------------
// Lista circular
// ----------------------------------------------------------------------------
// El último nodo, en lugar de apuntar a nullptr, apunta al primero. Guardamos
// el puntero a `ultimo` (no a `primero`): como `ultimo->siguiente` es el
// primero, podemos acceder a ambos extremos en O(1).
struct NodoCircular
{
    int dato;
    NodoCircular *siguiente;

    NodoCircular(int valor, NodoCircular *sig = nullptr)
        : dato(valor), siguiente(sig) {}
};

class ListaCircular
{
private:
    NodoCircular *ultimo; // ultimo->siguiente es el primero

public:
    // Constructor: inicializa una lista vacía (ultimo en nullptr).
    ListaCircular();

    // Ejercicio C1 — Destructor
    // Ojo: no podés recorrer hasta encontrar nullptr (¡nunca lo hay!). Hay
    // que cortar cuando volvés al nodo de partida. Usá un `do-while`.
    ~ListaCircular();

    bool vacia() const;

    // Ejercicio C2 — Insertar al inicio
    // El nuevo nodo pasa a ser ultimo->siguiente, sin modificar quién es
    // `ultimo` (salvo que la lista estuviera vacía).
    void insertarAlInicio(int valor);

    // Ejercicio C3 — Insertar al final
    // El nuevo nodo pasa a ser `ultimo`.
    void insertarAlFinal(int valor);

    // Ejercicio C4 — Buscar un elemento
    bool buscar(int valor) const;

    // Ejercicio C5 — Recorrido completo
    // Devuelve un vector con todos los elementos, empezando por el primero
    // (ultimo->siguiente). La condición de corte es volver al nodo de
    // partida, no llegar a nullptr.
    std::vector<int> aVector() const;
};

// ----------------------------------------------------------------------------
// Iteradores
// ----------------------------------------------------------------------------
// Lista simplemente enlazada con soporte para el for basado en rango
// (`for (int x : lista)`), a través de una clase Iterador anidada.
struct Nodo
{
    int dato;
    Nodo *siguiente;

    Nodo(int valor, Nodo *sig = nullptr) : dato(valor), siguiente(sig) {}
};

class ListaIterable
{
private:
    Nodo *primero;
    Nodo *ultimo;
    size_t largo;

public:
    // Ya implementados: sirven para armar listas de prueba para el iterador.
    ListaIterable();
    ~ListaIterable();
    bool vacia() const;
    size_t tamanio() const;
    void insertarAlFinal(int valor);

    // Clase anidada que representa "una posición dentro del recorrido".
    class Iterador
    {
    private:
        Nodo *actual;

    public:
        Iterador(Nodo *nodo) : actual(nodo) {}

        // Ejercicio I1 — Desreferenciar
        // Devuelve una referencia al dato del nodo actual.
        // Precondición: el iterador no es end() (actual != nullptr).
        int &operator*();

        // Ejercicio I2 — Avanzar (prefijo)
        // Mueve el iterador a la siguiente posición y devuelve *this.
        Iterador &operator++();

        // Ejercicio I3 — Comparar
        // Devuelve true si los dos iteradores apuntan a nodos distintos.
        bool operator!=(const Iterador &otro) const;
    };

    // Ejercicio I4 — begin()
    // Devuelve un iterador apuntando al primer elemento.
    Iterador begin() const;

    // Ejercicio I5 — end()
    // Devuelve un iterador que representa "después del último elemento"
    // (Iterador(nullptr)). No apunta a un elemento válido.
    Iterador end() const;
};

#endif
