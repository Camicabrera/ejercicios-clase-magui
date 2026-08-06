Tutorial 3 – Listas enlazadas e iteradores: Ejercicios
===

A continuación hay una serie de ejercicios sobre listas enlazadas, de dificultad creciente. Se asume la implementación de `Nodo<T>` y `ListaSimple<T>` (o `ListaDoble<T>`, según corresponda) vista en el apunte de la clase. Todas las soluciones son código C++ manual, sin usar `std::list`.

> Antes de mirar la solución, intentá resolver el ejercicio en papel dibujando los nodos y las flechas. La mayoría de los errores de listas enlazadas se evitan dibujando el "antes" y el "después" de cada operación.



## Ejercicio 1: Recorrer y contar

Escribí una función que reciba el `primero` de una lista simplemente enlazada de enteros y devuelva la cantidad de elementos **pares**.

```cpp
int contarPares(Nodo<int>* primero);
```

### Solución

```cpp
int contarPares(Nodo<int>* primero) {
    int contador = 0;
    Nodo<int>* actual = primero;

    while (actual != nullptr) {
        if (actual->dato % 2 == 0) {
            contador++;
        }
        actual = actual->siguiente;   // avanzamos SIEMPRE, haya matcheado o no
    }

    return contador;
}
```

Es el patrón base de recorrido: un puntero `actual` que arranca en `primero` y avanza con `actual = actual->siguiente` hasta llegar a `nullptr`. Complejidad: **O(n)**.



## Ejercicio 2: Invertir una lista

Escribí una función que invierta una lista simplemente enlazada **in-place** (sin crear nodos nuevos ni usar una estructura auxiliar), devolviendo el nuevo primer nodo.

```cpp
Nodo<int>* invertir(Nodo<int>* primero);
```

### Solución

```cpp
Nodo<int>* invertir(Nodo<int>* primero) {
    Nodo<int>* anterior = nullptr;
    Nodo<int>* actual = primero;

    while (actual != nullptr) {
        Nodo<int>* siguienteGuardado = actual->siguiente; // lo guardamos antes de pisarlo
        actual->siguiente = anterior;                      // damos vuelta el puntero
        anterior = actual;                                  // avanzamos "anterior"
        actual = siguienteGuardado;                         // avanzamos "actual"
    }

    return anterior;   // al terminar, "anterior" es el nuevo primero
}
```

> **Pregunta para pensar:** ¿por qué hace falta guardar `actual->siguiente` en una variable auxiliar **antes** de modificar `actual->siguiente`? ¿Qué pasaría si no lo hiciéramos?

Complejidad: **O(n)** en tiempo, **O(1)** en memoria extra (solo tres punteros).



## Ejercicio 3: Detectar un ciclo (algoritmo de Floyd)

Dada una lista simplemente enlazada que **podría** tener un ciclo (por un bug, el `siguiente` de algún nodo apunta a un nodo anterior en vez de a `nullptr`), escribí una función que detecte si existe un ciclo, sin usar memoria extra proporcional a `n`.

```cpp
bool tieneCiclo(Nodo<int>* primero);
```

### Solución

Usamos el algoritmo de **la tortuga y la liebre**: dos punteros que recorren la lista a distinta velocidad. Si hay un ciclo, la liebre (que avanza de a dos) eventualmente "da la vuelta" y se encuentra con la tortuga (que avanza de a uno). Si no hay ciclo, la liebre llega a `nullptr` primero.

```cpp
bool tieneCiclo(Nodo<int>* primero) {
    Nodo<int>* tortuga = primero;
    Nodo<int>* liebre = primero;

    while (liebre != nullptr && liebre->siguiente != nullptr) {
        tortuga = tortuga->siguiente;           // avanza 1 paso
        liebre = liebre->siguiente->siguiente;  // avanza 2 pasos

        if (tortuga == liebre) {
            return true;   // se encontraron: hay ciclo
        }
    }

    return false;   // la liebre llegó al final: no hay ciclo
}
```

> **Pregunta para pensar:** ¿por qué la condición del `while` chequea `liebre != nullptr && liebre->siguiente != nullptr` y no solamente `liebre != nullptr`? ¿Qué pasaría si no chequeáramos `liebre->siguiente`?

Complejidad: **O(n)** en tiempo, **O(1)** en memoria (a diferencia de una solución con un `set` de nodos visitados, que sería O(n) en memoria).



## Ejercicio 4: Concatenar dos listas

Escribí una función que reciba los primeros nodos de dos listas simplemente enlazadas y las una en una sola, dejando los elementos de la segunda a continuación de los de la primera. No hay que crear nodos nuevos: solo reenlazar.

```cpp
Nodo<int>* concatenar(Nodo<int>* primeraLista, Nodo<int>* segundaLista);
```

### Solución

```cpp
Nodo<int>* concatenar(Nodo<int>* primeraLista, Nodo<int>* segundaLista) {
    if (primeraLista == nullptr) {
        return segundaLista;   // la primera estaba vacía
    }

    Nodo<int>* actual = primeraLista;
    while (actual->siguiente != nullptr) {   // buscamos el último nodo de la primera
        actual = actual->siguiente;
    }

    actual->siguiente = segundaLista;   // lo enlazamos con el inicio de la segunda
    return primeraLista;
}
```

> Si nuestra clase `ListaSimple<T>` guarda un puntero `ultimo`, esta operación se vuelve **O(1)**: `ultimo->siguiente = otraLista.primero` y actualizar `ultimo` y `largo`. Sin ese puntero, hay que recorrer para encontrar el final: **O(n)**.



## Ejercicio 5: Eliminar duplicados

Dada una lista simplemente enlazada **no ordenada**, eliminá los nodos con valores repetidos, dejando solo la primera aparición de cada valor.

```cpp
void eliminarDuplicados(Nodo<int>* primero);
```

### Solución

Usamos un `std::unordered_set` auxiliar para recordar qué valores ya vimos (esto no rompe la regla de "no usar `std::list`": el `set` no es la estructura que estamos implementando, solo una herramienta auxiliar).

```cpp
#include <unordered_set>

void eliminarDuplicados(Nodo<int>* primero) {
    if (primero == nullptr) return;

    std::unordered_set<int> vistos;
    vistos.insert(primero->dato);

    Nodo<int>* actual = primero;
    while (actual->siguiente != nullptr) {
        if (vistos.count(actual->siguiente->dato) > 0) {
            // ya lo vimos: hay que saltear (y liberar) el nodo siguiente
            Nodo<int>* aBorrar = actual->siguiente;
            actual->siguiente = aBorrar->siguiente;
            delete aBorrar;
        } else {
            vistos.insert(actual->siguiente->dato);
            actual = actual->siguiente;
        }
    }
}
```

> **Pregunta para pensar:** ¿cómo resolverías este mismo ejercicio si no pudieras usar memoria auxiliar (es decir, en O(1) de espacio)? *Pista:* ¿qué complejidad en tiempo estarías dispuesto a pagar a cambio?

Complejidad: **O(n)** en tiempo (en promedio, gracias al `unordered_set`), **O(n)** en memoria auxiliar.



## Ejercicio 6: Insertar ordenado

Escribí una función que inserte un valor en una lista simplemente enlazada que **ya está ordenada de forma creciente**, de manera que quede ordenada después de insertar.

```cpp
Nodo<int>* insertarOrdenado(Nodo<int>* primero, int valor);
```

### Solución

```cpp
Nodo<int>* insertarOrdenado(Nodo<int>* primero, int valor) {
    Nodo<int>* nuevo = new Nodo<int>(valor, nullptr);

    // Caso borde: insertar al inicio (lista vacía o el valor es el menor)
    if (primero == nullptr || valor <= primero->dato) {
        nuevo->siguiente = primero;
        return nuevo;
    }

    // Buscamos el nodo anterior a la posición donde va el nuevo valor
    Nodo<int>* actual = primero;
    while (actual->siguiente != nullptr && actual->siguiente->dato < valor) {
        actual = actual->siguiente;
    }

    nuevo->siguiente = actual->siguiente;
    actual->siguiente = nuevo;
    return primero;
}
```

Complejidad: **O(n)**, porque en el peor caso (insertar al final) hay que recorrer toda la lista.



## Ejercicio 7: Operaciones sobre lista doblemente enlazada

Sobre una `ListaDoble<T>` (con punteros `siguiente` y `anterior`), escribí dos funciones:

a) `insertarAntes(nodo, valor)`: inserta un nuevo nodo con `valor` inmediatamente antes de `nodo` (asumiendo `nodo` no es el primero).
b) `recorrerEnReversa()`: imprime los elementos de la lista de atrás hacia adelante, usando el puntero `ultimo` y los punteros `anterior`.

### Solución

```cpp
void ListaDoble<T>::insertarAntes(NodoDoble<T>* nodo, const T& valor) {
    NodoDoble<T>* nuevo = new NodoDoble<T>(valor);
    NodoDoble<T>* anteriorDeNodo = nodo->anterior;

    nuevo->siguiente = nodo;
    nuevo->anterior = anteriorDeNodo;

    nodo->anterior = nuevo;
    anteriorDeNodo->siguiente = nuevo;   // seguro porque asumimos que nodo no es el primero

    largo++;
}

void ListaDoble<T>::recorrerEnReversa() const {
    NodoDoble<T>* actual = ultimo;
    while (actual != nullptr) {
        std::cout << actual->dato << " ";
        actual = actual->anterior;   // ¡la gran ventaja de la lista doble!
    }
    std::cout << std::endl;
}
```

> **Pregunta para pensar:** ¿por qué `insertarAntes` es O(1) si ya tenemos el puntero al `nodo`, pero sería O(n) si solo tuviéramos el *valor* a buscar? ¿Qué parte del trabajo es O(1) y cuál es O(n)?

Complejidad: `insertarAntes` es **O(1)** (con el nodo ya localizado); `recorrerEnReversa` es **O(n)**, y solo es posible gracias al puntero `anterior` — en una lista simple sería imposible sin dar vuelta la lista primero.



## Ejercicio 8: Implementar un iterador propio

Extendé el iterador de `ListaSimple<T>` visto en el apunte para que también sirva con las funciones genéricas de `<algorithm>`. Concretamente, implementá una función `sumarElementos` que reciba dos iteradores (`begin` y `end`) y devuelva la suma de los elementos en ese rango, de forma completamente genérica (sin asumir que es una `ListaSimple`).

```cpp
template <typename Iterador>
int sumarElementos(Iterador inicio, Iterador fin);
```

### Solución

```cpp
template <typename Iterador>
int sumarElementos(Iterador inicio, Iterador fin) {
    int suma = 0;
    for (Iterador it = inicio; it != fin; ++it) {
        suma += *it;   // solo usamos *, ++ y != : la interfaz mínima de un iterador
    }
    return suma;
}
```

Uso con nuestra lista:

```cpp
ListaSimple<int> lista;
lista.insertarAlFinal(10);
lista.insertarAlFinal(20);
lista.insertarAlFinal(30);

int total = sumarElementos(lista.begin(), lista.end());   // 60
```

Y la misma función, sin cambiar una sola línea, funciona sobre un `std::vector`:

```cpp
std::vector<int> vector = {1, 2, 3, 4};
int total2 = sumarElementos(vector.begin(), vector.end());   // 10
```

> **Este es el punto central del ejercicio:** `sumarElementos` no sabe (ni le importa) si recorre nodos enlazados o un bloque contiguo de memoria. Mientras el tipo `Iterador` soporte `*`, `++` y `!=`, la función funciona. Esta es exactamente la idea detrás de los algoritmos genéricos de la STL (`std::accumulate`, `std::find`, `std::count`, etc.).

Complejidad: **O(n)**, independientemente del contenedor subyacente.



## Ejercicios propuestos

1. Escribí una función `Nodo<int>* mitad(Nodo<int>* primero)` que devuelva el nodo del medio de una lista simplemente enlazada, recorriéndola **una sola vez** (pista: usá la misma idea de dos punteros a distinta velocidad del ejercicio 3).
2. Implementá un `const_iterator` para `ListaSimple<T>` (que no permita modificar los elementos a través de `*it`) y agregá los métodos `cbegin()` / `cend()`, siguiendo la convención de la STL.
