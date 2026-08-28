#include "ejercicios.h"

// ============================================================================
// Acá va TU código. Cada función tiene una cáscara con un "TODO": borrá el
// contenido de ejemplo y escribí la implementación.
// ============================================================================

ListaIterable::ListaIterable()
    : primero(nullptr), ultimo(nullptr), largo(0)
{
    // Ya implementado.
}

ListaIterable::~ListaIterable()
{
    // Ya implementado.
    Nodo *actual = primero;
    while (actual != nullptr)
    {
        Nodo *siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

bool ListaIterable::vacia() const
{
    // Ya implementado.
    return primero == nullptr;
}

size_t ListaIterable::tamanio() const
{
    // Ya implementado.
    return largo;
}

void ListaIterable::insertarAlFinal(int valor)
{
    // Ya implementado.
    Nodo *nuevo = new Nodo(valor);
    if (ultimo == nullptr)
    {
        primero = nuevo;
        ultimo = nuevo;
    }
    else
    {
        ultimo->siguiente = nuevo;
        ultimo = nuevo;
    }
    largo++;
}

// Ejercicio 1 — Desreferenciar
int &ListaIterable::Iterador::operator*()
{
    // TODO: devolver una referencia al dato del nodo actual.
    // Precondición: actual != nullptr (el iterador no es end()).
    static int dummy = 0;
    return dummy;
}

// Ejercicio 2 — Avanzar (prefijo)
ListaIterable::Iterador &ListaIterable::Iterador::operator++()
{
    // TODO: mover `actual` al siguiente nodo y devolver *this.
    return *this;
}

// Ejercicio 3 — Comparar
bool ListaIterable::Iterador::operator!=(const Iterador &otro) const
{
    // TODO: devolver true si `actual` es distinto del `actual` de `otro`.
    (void)actual; // Silencia warning hasta que implementes las funciones
    (void)otro;
    return false;
}

// Ejercicio 4 — begin()
ListaIterable::Iterador ListaIterable::begin() const
{
    // TODO: devolver un Iterador apuntando al primer nodo.
    return Iterador(nullptr);
}

// Ejercicio 5 — end()
ListaIterable::Iterador ListaIterable::end() const
{
    // TODO: devolver un Iterador que representa "después del último"
    // (Iterador(nullptr)).
    return Iterador(nullptr);
}
