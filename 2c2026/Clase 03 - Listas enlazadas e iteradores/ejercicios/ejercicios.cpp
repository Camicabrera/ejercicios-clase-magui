#include "ejercicios.h"

// ============================================================================
// Acá va TU código. Cada función tiene una cáscara con un "TODO": borrá el
// contenido de ejemplo y escribí la implementación.
//
// Los `(void)parametro;` que ves abajo están solo para que la cáscara
// compile sin advertencias antes de que la implementes. Cuando uses el
// parámetro en tu código, borrá la línea `(void)...` correspondiente.
// ============================================================================

// Constructor: inicializa una lista vacía
ListaSimple::ListaSimple()
    : primero(nullptr), ultimo(nullptr), largo(0)
{
    // El constructor ya está implementado usando la lista de inicialización.
    // No hace falta que modifiques nada acá.
}

// Destructor: libera todos los nodos
ListaSimple::~ListaSimple()
{

    // TODO: recorrer la lista y liberar cada nodo con delete.
    // Recordá guardar el puntero al siguiente ANTES de hacer delete del actual.
    // Al final, primero, ultimo y largo deberían quedar en su estado inicial
    // (aunque técnicamente no importa porque el objeto se destruye).
   Nodo* actual= primero;
    while (actual!= nullptr){
        Nodo* siguiente = actual -> siguiente;
        delete actual;
        actual=siguiente;
    }    
    (void)ultimo;  // Silencia warning hasta que implementes las funciones
}

// Devuelve true si la lista está vacía
bool ListaSimple::vacia() const
{
    // Ya está implementado: la lista está vacía si no tiene primer elemento.
    return primero == nullptr;

}

// Devuelve la cantidad de elementos
size_t ListaSimple::tamanio() const
{
    // Ya está implementado: devolvemos el contador.
    return largo;
}

// Ejercicio 1 — Insertar al inicio
void ListaSimple::insertarAlInicio(int valor)
{
    // TODO: crear un nuevo nodo y ponerlo al principio de la lista.
    // Casos a considerar:
    //   - La lista estaba vacía (hay que actualizar también `ultimo`)
    //   - La lista ya tenía elementos
    Nodo* nodoNuevo= new Nodo(valor);
    if(vacia()){
        primero=nodoNuevo;
        ultimo=nodoNuevo;
    }
    else{
        Nodo* siguiente=primero; // creo nodo que apunte a donde apunta primero
         primero= nodoNuevo;
         nodoNuevo -> siguiente = siguiente;
    }
    largo ++;
    return;
}

// Ejercicio 2 — Insertar al final
void ListaSimple::insertarAlFinal(int valor)
{
    // TODO: crear un nuevo nodo y ponerlo al final de la lista.
    // Casos a considerar:
    //   - La lista estaba vacía (hay que actualizar también `primero`)
    //   - La lista ya tenía elementos
    Nodo* nodoNuevo= new Nodo(valor);
    if(vacia()){
        primero=nodoNuevo;
        ultimo=nodoNuevo;
    } 
    else{
        ultimo -> siguiente= nodoNuevo;
    }
    ultimo= nodoNuevo;
    largo++;
    (void)valor;
}

// Ejercicio 3 — Buscar un elemento
bool ListaSimple::buscar(int valor) const
{
    // TODO: recorrer la lista buscando el valor.
    // Devolver true si lo encontrás, false si llegás al final sin encontrarlo.
    Nodo* actual = primero;
    while (actual != nullptr){
        if (actual -> dato == valor){
            return true;
        }
        actual = actual ->siguiente;
    }
    return false;
}

// Ejercicio 4 — Obtener el primer elemento
int &ListaSimple::frente()
{
    // TODO: devolver el dato del primer nodo.
    // Precondición: la lista no está vacía.
    return primero ->dato;
}

const int &ListaSimple::frente() const
{
    // TODO: versión const de frente()

    return primero -> dato;
}

// Ejercicio 5 — Obtener el último elemento
int &ListaSimple::final()
{
    // TODO: devolver el dato del último nodo.
    // Precondición: la lista no está vacía.

    return ultimo -> dato;
}

const int &ListaSimple::final() const
{
    // TODO: versión const de final()
    return ultimo -> dato;
}

// Ejercicio 6 — Eliminar el primer elemento
void ListaSimple::eliminarPrimero()
{
    // TODO: eliminar el primer nodo y liberar su memoria.
    // Casos a considerar:
    //   - La lista tenía un solo elemento (queda vacía)
    //   - La lista tenía más de un elemento
    // Precondición: la lista no está vacía.
    Nodo* viejo= primero;
    primero = primero -> siguiente ;
    delete viejo;
    if (primero == nullptr){
        ultimo=nullptr;
    }
    largo--;


}

// Ejercicio 7 — Eliminar por valor
bool ListaSimple::eliminar(int valor)
{
    // TODO: buscar el primer nodo con el valor dado y eliminarlo.
    // Devolver true si lo encontraste y eliminaste, false si no estaba.
    // Casos a considerar:
    //   - El valor está en el primer nodo
    //   - El valor está en el último nodo
    //   - El valor está en un nodo del medio
    //   - El valor no está en la lista
    //   - La lista tiene un solo elemento y es el que hay que eliminar
    (void)valor;
    Nodo* actual = primero;
    Nodo* anterior= nullptr;
    while (actual != nullptr && actual -> dato != valor){
        anterior = actual;
        actual= actual -> siguiente;
    }
    if (actual == nullptr){
        return false;
    }


     if (anterior == nullptr) {
        primero = actual->siguiente;  
    } else {
        anterior->siguiente = actual->siguiente;  // salteo el nodo a borrar
    }

    if (actual == ultimo) {
        ultimo = anterior;  // era el último nodo
    }

    delete actual;
    largo--;
    return true;
}

// Ejercicio 8 — Obtener elemento en posición i
int &ListaSimple::operator[](size_t i)
{
    // TODO: recorrer la lista hasta la posición i y devolver el dato.
    // Precondición: i < tamanio()

    Nodo* actual= primero;
    for (size_t j=0;j<i;j++){
        actual= actual -> siguiente;
    }
    return actual -> dato;
}

const int &ListaSimple::operator[](size_t i) const
{
    // TODO: versión const de operator[]
    Nodo* actual= primero;
    for (size_t j=0;j<i;j++){
        actual= actual -> siguiente;
    }
    return actual -> dato;
}

// Propuesto 1 — Insertar en posición
void ListaSimple::insertarEnPosicion(size_t i, int valor)
{
    // TODO: insertar un nuevo nodo en la posición i.
    // Si i == 0, es insertarAlInicio.
    // Si i == tamanio(), es insertarAlFinal.
    // Precondición: i <= tamanio()
    (void)i;
    (void)valor;
}

// Propuesto 2 — Invertir la lista
void ListaSimple::invertir()
{
    // TODO: invertir el orden de los nodos in-place.
    // Pista: recorrer la lista cambiando los punteros `siguiente` para que
    // apunten al nodo anterior. Vas a necesitar 3 punteros auxiliares.
}
