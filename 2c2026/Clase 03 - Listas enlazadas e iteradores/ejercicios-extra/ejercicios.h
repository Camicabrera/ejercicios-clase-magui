#ifndef EJERCICIOS_EXTRA_H
#define EJERCICIOS_EXTRA_H

#include <cstddef>

// ============================================================================
// Tut 03 - Listas enlazadas e iteradores (EXTRA)
//
// Ejercicios adicionales sobre iteradores para la lista simplemente
// enlazada. Son independientes de la carpeta "ejercicios/": no hace falta
// haber terminado esos ejercicios para encarar estos.
//
// El programa de prueba está en "main.cpp": compilá con `make` y corré
// `./ejercicios-extra` para ver qué ejercicios pasan y cuáles todavía fallan.
// ============================================================================

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

        // Ejercicio 1 — Desreferenciar
        // Devuelve una referencia al dato del nodo actual.
        // Precondición: el iterador no es end() (actual != nullptr).
        int &operator*();

        // Ejercicio 2 — Avanzar (prefijo)
        // Mueve el iterador a la siguiente posición y devuelve *this.
        Iterador &operator++();

        // Ejercicio 3 — Comparar
        // Devuelve true si los dos iteradores apuntan a nodos distintos.
        bool operator!=(const Iterador &otro) const;
    };

    // Ejercicio 4 — begin()
    // Devuelve un iterador apuntando al primer elemento.
    Iterador begin() const;

    // Ejercicio 5 — end()
    // Devuelve un iterador que representa "después del último elemento"
    // (Iterador(nullptr)). No apunta a un elemento válido.
    Iterador end() const;
};

#endif
