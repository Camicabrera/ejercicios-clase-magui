Tutorial 3 – Listas enlazadas e iteradores
===

> **Ingeniería en Inteligencia Artificial** — **Algoritmos y Estructura de Datos**  
> **2C 2026** · Docente: **Magali Marijuan**

- [Tutorial 3 – Listas enlazadas e iteradores](#tutorial-3--listas-enlazadas-e-iteradores)
- [Objetivos de la clase](#objetivos-de-la-clase)
- [El nodo: la unidad básica](#el-nodo-la-unidad-básica)
- [Lista simplemente enlazada](#lista-simplemente-enlazada)
  - [Implementación de la lista simple](#implementación-de-la-lista-simple)
  - [Insertar al inicio](#insertar-al-inicio)
  - [Insertar al final](#insertar-al-final)
  - [Buscar un elemento](#buscar-un-elemento)
  - [Recorrer la lista](#recorrer-la-lista)
  - [Tamaño de la lista](#tamaño-de-la-lista)
  - [Destructor: liberar todos los nodos](#destructor-liberar-todos-los-nodos)
  - [Repaso de complejidades (lista simple)](#repaso-de-complejidades-lista-simple)
- [Lista doblemente enlazada](#lista-doblemente-enlazada)
  - [Implementación de la lista doble](#implementación-de-la-lista-doble)
  - [Repaso de complejidades (lista doble)](#repaso-de-complejidades-lista-doble)
- [Lista circular](#lista-circular)
  - [Implementación de la lista circular](#implementación-de-la-lista-circular)
  - [Repaso de complejidades (lista circular)](#repaso-de-complejidades-lista-circular)
- [Iteradores](#iteradores)
  - [¿Qué es un iterador?](#qué-es-un-iterador)
  - [Implementando un iterador propio](#implementando-un-iterador-propio)
  - [¿Por qué desacoplar el recorrido de la estructura?](#por-qué-desacoplar-el-recorrido-de-la-estructura)
- [Comparación con arreglo y std::vector](#comparación-con-arreglo-y-stdvector)
- [Resumen general de complejidades](#resumen-general-de-complejidades)



# Objetivos de la clase
- Entender qué es un nodo y cómo se encadenan para formar una lista.
- Implementar a mano una lista simplemente enlazada: insertar, borrar, buscar, recorrer y destruir.
- Extender la implementación a listas doblemente enlazadas y circulares.
- Comprender qué es un iterador y por qué es una abstracción que desacopla el recorrido de una estructura de su representación interna.
- Comparar las listas enlazadas con el arreglo dinámico (`std::vector`) en términos de complejidad y uso de memoria.



# El nodo: la unidad básica

Una lista enlazada no es un bloque contiguo de memoria como un arreglo. Es una colección de **nodos** dispersos en el *heap*, donde cada nodo guarda un dato y **un puntero al siguiente nodo**.

```cpp
template <typename T>
struct Nodo {
    T dato;
    Nodo<T>* siguiente;

    Nodo(const T& valor, Nodo<T>* sig = nullptr)
        : dato(valor), siguiente(sig) {}
};
```

> **Pregunta para pensar:** si los nodos están dispersos en el heap, ¿por qué recorrer una lista enlazada suele ser más lento en la práctica que recorrer un `std::vector` del mismo tamaño, aunque ambos sean O(n)?

Cada nodo se reserva individualmente con `new` y debe liberarse individualmente con `delete`. Esta es la diferencia clave frente al arreglo: la lista **crece de a un nodo por vez**, sin necesidad de pedir un bloque más grande y copiar todo.



# Lista simplemente enlazada

**Invariante:** cada nodo conoce al siguiente. El último nodo apunta a `nullptr`.

## Implementación de la lista simple

```cpp
template <typename T>
class ListaSimple {
private:
    Nodo<T>* primero;
    Nodo<T>* ultimo;
    size_t largo;

public:
    ListaSimple() : primero(nullptr), ultimo(nullptr), largo(0) {}

    ~ListaSimple() {
        Nodo<T>* actual = primero;
        while (actual != nullptr) {
            Nodo<T>* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
    }

    size_t tamaño() const { return largo; }
    bool vacia() const { return largo == 0; }

    void insertarAlInicio(const T& valor);
    void insertarAlFinal(const T& valor);
    bool buscar(const T& valor) const;
    void imprimir() const;
};
```

> Guardamos un puntero `ultimo` y un contador `largo` por la misma razón que en C: sin ellos, insertar al final o pedir el tamaño serían operaciones O(n).

## Insertar al inicio

```cpp
template <typename T>
void ListaSimple<T>::insertarAlInicio(const T& valor) {
    Nodo<T>* nuevo = new Nodo<T>(valor, primero);
    primero = nuevo;
    if (ultimo == nullptr) {   // la lista estaba vacía
        ultimo = nuevo;
    }
    largo++;
}
```

## Insertar al final

```cpp
template <typename T>
void ListaSimple<T>::insertarAlFinal(const T& valor) {
    Nodo<T>* nuevo = new Nodo<T>(valor, nullptr);
    if (ultimo == nullptr) {   // la lista estaba vacía
        primero = nuevo;
    } else {
        ultimo->siguiente = nuevo;
    }
    ultimo = nuevo;
    largo++;
}
```

> **Pregunta para pensar:** ¿por qué `insertarAlFinal` es O(1) acá, pero sería O(n) si no tuviéramos el puntero `ultimo`?

## Buscar un elemento

```cpp
template <typename T>
bool ListaSimple<T>::buscar(const T& valor) const {
    Nodo<T>* actual = primero;
    while (actual != nullptr) {
        if (actual->dato == valor) return true;
        actual = actual->siguiente;
    }
    return false;
}
```

Para **borrar por valor** hay que recorrer con dos punteros (uno "anterior" y uno "actual"), porque en la lista simple no hay forma de ir hacia atrás una vez que encontramos el nodo:

```cpp
template <typename T>
bool ListaSimple<T>::eliminar(const T& valor) {
    Nodo<T>* anterior = nullptr;
    Nodo<T>* actual = primero;

    while (actual != nullptr && actual->dato != valor) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == nullptr) return false;  // no estaba

    if (anterior == nullptr) {
        primero = actual->siguiente;      // borramos el primero
    } else {
        anterior->siguiente = actual->siguiente;
    }
    if (actual == ultimo) {
        ultimo = anterior;                // borramos el último
    }

    delete actual;
    largo--;
    return true;
}
```

## Recorrer la lista

```cpp
template <typename T>
void ListaSimple<T>::imprimir() const {
    Nodo<T>* actual = primero;
    while (actual != nullptr) {
        std::cout << actual->dato << " ";
        actual = actual->siguiente;
    }
    std::cout << std::endl;
}
```

## Tamaño de la lista

Como guardamos `largo` como campo de la clase y lo actualizamos en cada inserción/borrado, `tamaño()` es simplemente devolver ese campo: **O(1)**.

> Si no lo guardáramos, habría que recorrer toda la lista contando nodos: O(n). Es el mismo *trade-off* que vimos con arreglos dinámicos: pagar un poco de memoria extra para ganar tiempo.

## Destructor: liberar todos los nodos

Este es uno de los errores más comunes en C++: si el destructor de la lista no libera **cada nodo** con `delete`, se produce un *memory leak*. No alcanza con que la lista misma se destruya (por ejemplo, al salir del scope o al hacer `delete lista`): sus nodos viven en el heap y nadie los libera automáticamente.

```cpp
~ListaSimple() {
    Nodo<T>* actual = primero;
    while (actual != nullptr) {
        Nodo<T>* siguiente = actual->siguiente;  // lo guardamos ANTES de liberar
        delete actual;
        actual = siguiente;
    }
}
```

> **¿Por qué guardamos `siguiente` antes de hacer `delete actual`?** Porque una vez que liberamos la memoria de `actual`, leer `actual->siguiente` es acceso a memoria inválida (comportamiento indefinido). Guardar el puntero antes es obligatorio.

> **Pregunta para pensar:** si el destructor de `ListaSimple<T>` no libera los nodos, ¿el programa se cae inmediatamente? ¿Cómo se detecta este tipo de error en la práctica? (Pensar en herramientas como `valgrind` o *sanitizers*.)

## Repaso de complejidades (lista simple)

| Operación         | Complejidad |
|--------------------|-------------|
| constructor        | O(1)        |
| destructor          | O(n)        |
| tamaño              | O(1)        |
| insertarAlInicio    | O(1)        |
| insertarAlFinal     | O(1)        |
| buscar              | O(n)        |
| eliminar (por valor)| O(n)        |
| obtener/modificar en posición i | O(n) |
| **eliminar el último** | **O(n)** |

> **Punto clave:** eliminar el último es O(n) porque necesitamos encontrar el *anteúltimo* nodo para que su `siguiente` pase a ser `nullptr`, y en la lista simple no hay forma de ir "hacia atrás".



# Lista doblemente enlazada

**Invariante:** cada nodo conoce al siguiente **y al anterior**.

## Implementación de la lista doble

```cpp
template <typename T>
struct NodoDoble {
    T dato;
    NodoDoble<T>* siguiente;
    NodoDoble<T>* anterior;

    NodoDoble(const T& valor)
        : dato(valor), siguiente(nullptr), anterior(nullptr) {}
};

template <typename T>
class ListaDoble {
private:
    NodoDoble<T>* primero;
    NodoDoble<T>* ultimo;
    size_t largo;

public:
    ListaDoble() : primero(nullptr), ultimo(nullptr), largo(0) {}

    ~ListaDoble() {
        NodoDoble<T>* actual = primero;
        while (actual != nullptr) {
            NodoDoble<T>* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
    }

    void insertarAlFinal(const T& valor) {
        NodoDoble<T>* nuevo = new NodoDoble<T>(valor);
        if (ultimo == nullptr) {
            primero = ultimo = nuevo;
        } else {
            nuevo->anterior = ultimo;
            ultimo->siguiente = nuevo;
            ultimo = nuevo;
        }
        largo++;
    }

    void eliminarAlFinal() {
        if (ultimo == nullptr) return;  // lista vacía
        NodoDoble<T>* viejo = ultimo;
        ultimo = ultimo->anterior;
        if (ultimo != nullptr) {
            ultimo->siguiente = nullptr;
        } else {
            primero = nullptr;          // quedó vacía
        }
        delete viejo;
        largo--;
    }
};
```

> El costo de tener el puntero `anterior` es memoria extra por nodo (un puntero más), pero a cambio ganamos poder recorrer en ambas direcciones y hacer `eliminarAlFinal` en O(1).

## Repaso de complejidades (lista doble)

| Operación             | Lista simple | Lista doble |
|------------------------|--------------|-------------|
| insertarAlInicio        | O(1)         | O(1)        |
| insertarAlFinal          | O(1)         | O(1)        |
| **eliminar el último**  | **O(n)**     | **O(1)**    |
| obtener/modificar en posición i | O(n) | O(n)        |
| recorrido hacia atrás   | ❌ imposible | ✅ O(n)     |

> **Pregunta para pensar:** si necesitás insertar y eliminar frecuentemente en ambos extremos de la estructura (por ejemplo, para implementar un `deque`), ¿lista simple, lista doble o `std::vector`? ¿Por qué?



# Lista circular

**Invariante:** el último nodo, en lugar de apuntar a `nullptr`, apunta al primero. No tiene un "fin" natural.

## Implementación de la lista circular

```cpp
template <typename T>
class ListaCircular {
private:
    Nodo<T>* ultimo;   // guardamos el ÚLTIMO; ultimo->siguiente es el primero
    size_t largo;

public:
    ListaCircular() : ultimo(nullptr), largo(0) {}

    void insertarAlFinal(const T& valor) {
        Nodo<T>* nuevo = new Nodo<T>(valor, nullptr);
        if (ultimo == nullptr) {
            nuevo->siguiente = nuevo;   // se apunta a sí mismo
            ultimo = nuevo;
        } else {
            nuevo->siguiente = ultimo->siguiente;  // apunta al viejo primero
            ultimo->siguiente = nuevo;
            ultimo = nuevo;
        }
        largo++;
    }

    void imprimir() const {
        if (ultimo == nullptr) return;
        Nodo<T>* primero = ultimo->siguiente;
        Nodo<T>* actual = primero;
        do {
            std::cout << actual->dato << " ";
            actual = actual->siguiente;
        } while (actual != primero);   // ¡corta al volver al inicio!
        std::cout << std::endl;
    }
};
```

> **Nota:** si guardamos el puntero a `ultimo` (en vez de a `primero`), tanto `insertarAlInicio` como `insertarAlFinal` quedan en O(1), porque `ultimo->siguiente` nos da el primero directamente.

> **Pregunta para pensar:** ¿qué pasa si al recorrer una lista circular usás la condición de corte `actual != nullptr` en vez de `actual != primero`? ¿Por qué es un error tan común?

## Repaso de complejidades (lista circular)

| Operación         | Complejidad |
|--------------------|-------------|
| constructor         | O(1)        |
| insertarAlInicio     | O(1)*       |
| insertarAlFinal      | O(1)*       |
| recorrido completo   | O(n)        |
| buscar               | O(n)        |

\* Siempre que se guarde el puntero a `ultimo`. Si se guardara el puntero a `primero` en su lugar, ambas pasan a ser O(n) porque habría que recorrer toda la lista para encontrar el último.



# Iteradores

## ¿Qué es un iterador?

Hasta ahora, para recorrer cualquiera de nuestras listas tuvimos que exponer el detalle interno: un puntero `Nodo<T>*` que el código externo mueve con `actual = actual->siguiente`. Esto tiene un problema: **quien recorre la lista necesita conocer su representación interna**.

Un **iterador** es un objeto que abstrae "la posición actual dentro de un recorrido", ofreciendo una interfaz uniforme sin importar cómo está implementada la estructura por dentro:

- `*it` → obtener el elemento actual.
- `++it` → avanzar al siguiente.
- `it != otro` → comparar posiciones (típicamente contra `end()`).

Es la misma idea detrás de un `for` de C++ con rango (`for (auto& x : contenedor)`) y de todos los iteradores de la STL (`std::vector<T>::iterator`, `std::list<T>::iterator`, etc.).

> **Pregunta para pensar:** si mañana cambiamos la implementación interna de `ListaSimple` (por ejemplo, para usar un arreglo en vez de nodos enlazados), ¿el código que hace `for (int x : lista)` tendría que cambiar?

## Implementando un iterador propio

Agregamos una clase anidada `Iterador` a `ListaSimple<T>` y los métodos `begin()` / `end()` para habilitar el `for` basado en rango:

```cpp
template <typename T>
class ListaSimple {
    // ... (declaración de Nodo, primero, ultimo, largo, como antes)
public:
    class Iterador {
    private:
        Nodo<T>* actual;

    public:
        Iterador(Nodo<T>* nodo) : actual(nodo) {}

        T& operator*() const {
            return actual->dato;
        }

        Iterador& operator++() {
            actual = actual->siguiente;
            return *this;
        }

        bool operator!=(const Iterador& otro) const {
            return actual != otro.actual;
        }
    };

    Iterador begin() const { return Iterador(primero); }
    Iterador end() const { return Iterador(nullptr); }
};
```

Con esto, recorrer la lista se ve exactamente igual que recorrer un `std::vector`:

```cpp
ListaSimple<int> lista;
lista.insertarAlFinal(1);
lista.insertarAlFinal(2);
lista.insertarAlFinal(3);

for (int x : lista) {
    std::cout << x << " ";
}
// también funciona "a mano":
for (auto it = lista.begin(); it != lista.end(); ++it) {
    std::cout << *it << " ";
}
```

> El compilador traduce `for (int x : lista)` exactamente al segundo `for`. El `for` basado en rango **no es magia**: solo requiere que la clase tenga `begin()` y `end()`, y que el tipo devuelto soporte `*`, `++` y `!=`.

## ¿Por qué desacoplar el recorrido de la estructura?

El iterador es una capa de abstracción entre **quien recorre** y **cómo está guardada** la información:

- El código que usa `for (auto& x : lista)` no sabe (ni le importa) si por dentro hay nodos enlazados, un arreglo o un árbol.
- Se puede cambiar la implementación interna de la estructura sin romper el código que la recorre, siempre que el iterador mantenga la misma interfaz.
- Permite escribir algoritmos genéricos (buscar, sumar, ordenar) que funcionan sobre **cualquier** contenedor que exponga iteradores — es exactamente lo que hace la STL con `std::find`, `std::sort`, `std::accumulate`, etc.

> **Pregunta para pensar:** ¿por qué `std::sort` funciona sobre `std::vector` pero no compila sobre un iterador de `std::list` (o de nuestra `ListaSimple`)? Pensarlo en términos de qué operaciones necesita `sort` (acceso aleatorio) contra las que ofrece un iterador de lista enlazada (solo avanzar de a uno).



# Comparación con arreglo y std::vector

| Operación                     | Lista enlazada | `std::vector` |
|--------------------------------|-----------------|----------------|
| acceso por índice (`v[i]`)     | O(n)            | O(1)           |
| insertar al inicio              | O(1)            | O(n)           |
| insertar al final               | O(1)            | O(1) amortizado|
| insertar en posición arbitraria (con iterador ya posicionado) | O(1) | O(n) |
| localidad de memoria (cache)    | mala (nodos dispersos en el heap) | buena (bloque contiguo) |
| memoria extra por elemento      | 1 o 2 punteros  | ninguna (solo puede sobrar capacidad reservada) |

> **En la práctica**, aunque muchas operaciones de la lista enlazada son "O(1) en el papel", `std::vector` suele ser más rápido en recorridos por la localidad de cache: acceder a memoria contigua genera muchos menos *cache misses* que saltar de nodo en nodo por el heap.

> **Pregunta para pensar:** ¿en qué escenario elegirías una lista enlazada por sobre un `std::vector` a pesar de esta desventaja de cache?



# Resumen general de complejidades

| Operación                | Lista simple | Lista doble | Lista circular |
|----------------------------|--------------|-------------|-----------------|
| insertarAlInicio            | O(1)         | O(1)        | O(1)*           |
| insertarAlFinal              | O(1)         | O(1)        | O(1)*           |
| eliminar el primero          | O(1)         | O(1)        | O(1)*           |
| eliminar el último            | O(n)         | O(1)        | O(n)            |
| buscar / obtener en posición i | O(n)       | O(n)        | O(n)            |
| recorrido hacia atrás         | ❌           | ✅           | ❌ (salvo circular doble) |

\* Solo si se guarda el puntero al último nodo.

> La STL ya provee `std::list` (lista doblemente enlazada) y `std::forward_list` (lista simplemente enlazada). En la materia las implementamos a mano para entender **cómo funcionan por dentro**, pero en código de producción normalmente usarías las versiones de la biblioteca estándar.
