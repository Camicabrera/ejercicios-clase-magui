#include "ejercicios.h"

// ============================================================================
// Acá va TU código. Cada función tiene una cáscara con un "TODO": borrá el
// contenido de ejemplo y escribí la implementación.
//
// Los `(void)parametro;` que ves abajo están solo para que la cáscara
// compile sin advertencias antes de que la implementes. Cuando uses el
// parámetro en tu código, borrá la línea `(void)...` correspondiente.
// ============================================================================

// ----------------------------------------------------------------------------
// Lista doblemente enlazada
// ----------------------------------------------------------------------------

ListaDoble::ListaDoble()
    : primero(nullptr), ultimo(nullptr), largo(0)
{
    // Ya implementado: no hace falta que modifiques nada acá.
}

// Ejercicio D1 — Destructor
ListaDoble::~ListaDoble()
{
    // TODO: recorrer la lista (con `siguiente`) y liberar cada nodo con delete.
    // Recordá guardar el puntero al siguiente ANTES de hacer delete del actual.
    (void)ultimo; // Silencia warning hasta que implementes las funciones
}

bool ListaDoble::vacia() const
{
    return primero == nullptr;
}

size_t ListaDoble::tamanio() const
{
    return largo;
}

// Ejercicio D2 — Insertar al inicio
void ListaDoble::insertarAlInicio(int valor)
{
    // TODO: crear un NodoDoble y ponerlo al principio de la lista.
    // Casos a considerar:
    //   - La lista estaba vacía (el nuevo es primero y último)
    //   - La lista ya tenía elementos (el viejo primero pasa a tener
    //     `anterior` apuntando al nuevo nodo)
    (void)valor;
}

// Ejercicio D3 — Insertar al final
void ListaDoble::insertarAlFinal(int valor)
{
    // TODO: crear un NodoDoble y ponerlo al final de la lista.
    // Casos a considerar:
    //   - La lista estaba vacía (el nuevo es primero y último)
    //   - La lista ya tenía elementos (enlazar `anterior` del nuevo con el
    //     viejo último, y el `siguiente` del viejo último con el nuevo)
    (void)valor;
}

// Ejercicio D4 — Eliminar al inicio
void ListaDoble::eliminarAlInicio()
{
    // TODO: eliminar el primer nodo y liberar su memoria.
    // Casos a considerar:
    //   - La lista tenía un solo elemento (queda vacía: primero y ultimo en
    //     nullptr)
    //   - La lista tenía más de un elemento (el nuevo primero debe quedar
    //     con `anterior` en nullptr)
    // Precondición: la lista no está vacía.
}

// Ejercicio D5 — Eliminar al final
void ListaDoble::eliminarAlFinal()
{
    // TODO: eliminar el último nodo y liberar su memoria, en O(1) usando el
    // puntero `anterior` (sin recorrer la lista).
    // Casos a considerar:
    //   - La lista tenía un solo elemento (queda vacía)
    //   - La lista tenía más de un elemento (el nuevo último debe quedar
    //     con `siguiente` en nullptr)
    // Precondición: la lista no está vacía.
}

// Ejercicio D6 — Buscar un elemento
bool ListaDoble::buscar(int valor) const
{
    // TODO: recorrer la lista (con `siguiente`) buscando el valor.
    (void)valor;
    return false;
}

// Ejercicio D7 — Recorrido hacia atrás
std::vector<int> ListaDoble::aVectorInverso() const
{
    // TODO: recorrer la lista de atrás para adelante (empezando en `ultimo`
    // y usando `anterior`) y devolver un vector con los datos en ese orden.
    return {};
}

// ----------------------------------------------------------------------------
// Lista circular
// ----------------------------------------------------------------------------

ListaCircular::ListaCircular()
    : ultimo(nullptr)
{
    // Ya implementado: no hace falta que modifiques nada acá.
}

// Ejercicio C1 — Destructor
ListaCircular::~ListaCircular()
{
    // TODO: si la lista está vacía, no hay nada que liberar.
    // Si no, recorré desde el primero (ultimo->siguiente) guardando el
    // puntero al siguiente antes de cada delete, y cortá cuando volvés a
    // llegar al nodo de partida (usá un `do-while`, NUNCA `actual != nullptr`).
}

bool ListaCircular::vacia() const
{
    return ultimo == nullptr;
}

// Ejercicio C2 — Insertar al inicio
void ListaCircular::insertarAlInicio(int valor)
{
    // TODO: crear un NodoCircular y ponerlo al principio de la lista.
    // Casos a considerar:
    //   - La lista estaba vacía (el nuevo nodo se apunta a sí mismo y pasa a
    //     ser `ultimo`)
    //   - La lista ya tenía elementos (el nuevo nodo se inserta entre
    //     `ultimo` y el viejo primero, sin modificar quién es `ultimo`)
    (void)valor;
}

// Ejercicio C3 — Insertar al final
void ListaCircular::insertarAlFinal(int valor)
{
    // TODO: crear un NodoCircular y ponerlo al final de la lista.
    // Casos a considerar:
    //   - La lista estaba vacía (el nuevo nodo se apunta a sí mismo y pasa a
    //     ser `ultimo`)
    //   - La lista ya tenía elementos (el nuevo nodo pasa a ser `ultimo`)
    (void)valor;
}

// Ejercicio C4 — Buscar un elemento
bool ListaCircular::buscar(int valor) const
{
    // TODO: recorrer la lista circular buscando el valor.
    // Ojo con la condición de corte: no es `actual != nullptr`.
    (void)valor;
    return false;
}

// Ejercicio C5 — Recorrido completo
std::vector<int> ListaCircular::aVector() const
{
    // TODO: recorrer la lista empezando por el primero (ultimo->siguiente) y
    // devolver un vector con todos los datos, en orden.
    // Ojo con la condición de corte: no es `actual != nullptr`.
    return {};
}

// ----------------------------------------------------------------------------
// Iteradores
// ----------------------------------------------------------------------------

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

// Ejercicio I1 — Desreferenciar
int &ListaIterable::Iterador::operator*()
{
    // TODO: devolver una referencia al dato del nodo actual.
    // Precondición: actual != nullptr (el iterador no es end()).
    static int dummy = 0;
    return dummy;
}

// Ejercicio I2 — Avanzar (prefijo)
ListaIterable::Iterador &ListaIterable::Iterador::operator++()
{
    // TODO: mover `actual` al siguiente nodo y devolver *this.
    return *this;
}

// Ejercicio I3 — Comparar
bool ListaIterable::Iterador::operator!=(const Iterador &otro) const
{
    // TODO: devolver true si `actual` es distinto del `actual` de `otro`.
    (void)actual; // Silencia warning hasta que implementes las funciones
    (void)otro;
    return false;
}

// Ejercicio I4 — begin()
ListaIterable::Iterador ListaIterable::begin() const
{
    // TODO: devolver un Iterador apuntando al primer nodo.
    return Iterador(nullptr);
}

// Ejercicio I5 — end()
ListaIterable::Iterador ListaIterable::end() const
{
    // TODO: devolver un Iterador que representa "después del último"
    // (Iterador(nullptr)).
    return Iterador(nullptr);
}
