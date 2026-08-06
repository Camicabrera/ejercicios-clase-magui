Tutorial 6 – Árboles: ABB, AVL y Trie
===

> **Ingeniería en Inteligencia Artificial** — **Algoritmos y Estructura de Datos**  
> **2C 2026** · Docente: **Magali Marijuan**

- [Tutorial 6 – Árboles: ABB, AVL y Trie](#tutorial-6--árboles-abb-avl-y-trie)
- [Objetivos de la clase](#objetivos-de-la-clase)
- [Árboles binarios](#árboles-binarios)
  - [Definición recursiva](#definición-recursiva)
  - [Recorridos](#recorridos)
    - [Pre-order](#pre-order)
    - [In-order](#in-order)
    - [Post-order](#post-order)
    - [Recorrido por niveles (BFS)](#recorrido-por-niveles-bfs)
- [Árbol de Búsqueda Binaria (ABB)](#árbol-de-búsqueda-binaria-abb)
  - [Propiedad de orden](#propiedad-de-orden)
  - [Buscar](#buscar)
  - [Insertar](#insertar)
  - [Borrar](#borrar)
  - [Relación con la búsqueda binaria](#relación-con-la-búsqueda-binaria)
  - [Complejidades del ABB](#complejidades-del-abb)
- [AVL: árboles balanceados](#avl-árboles-balanceados)
  - [El problema del desbalanceo](#el-problema-del-desbalanceo)
  - [Factor de balance e invariante](#factor-de-balance-e-invariante)
  - [Rotaciones](#rotaciones)
    - [Rotación simple](#rotación-simple)
    - [Rotación doble](#rotación-doble)
  - [Complejidades del AVL](#complejidades-del-avl)
- [Trie](#trie)
  - [Estructura para strings y prefijos](#estructura-para-strings-y-prefijos)
  - [Insertar en un Trie](#insertar-en-un-trie)
  - [Buscar en un Trie](#buscar-en-un-trie)
  - [Trie vs ABB](#trie-vs-abb)
- [Estructuras compuestas](#estructuras-compuestas)
- [Resumen de complejidades](#resumen-de-complejidades)



# Objetivos de la clase
- Repasar la definición recursiva de árbol binario y sus recorridos.
- Entender el Árbol de Búsqueda Binaria (ABB): insertar, buscar y borrar.
- Ver el problema del desbalanceo y por qué motiva la aparición de los árboles AVL.
- Aprender el factor de balance, el invariante AVL y las rotaciones simples y dobles.
- Conocer el Trie como estructura especializada para strings y prefijos.
- Comparar costos entre ABB, AVL y Trie, y ver cuándo combinar estructuras.



# Árboles binarios

## Definición recursiva

Un **árbol binario** se define recursivamente como:

- El árbol vacío (`nullptr`), o
- Un **nodo** con una clave, un **subárbol izquierdo** (que es a su vez un árbol binario) y un **subárbol derecho** (que también es un árbol binario).

```cpp
template <typename T>
struct Nodo {
    T clave;
    Nodo<T>* izquierdo;
    Nodo<T>* derecho;

    Nodo(T c) : clave(c), izquierdo(nullptr), derecho(nullptr) {}
};
```

> Esta definición recursiva es la razón por la que **casi todas** las operaciones sobre árboles se escriben naturalmente como funciones recursivas: el caso base es el árbol vacío, y el caso recursivo delega en los subárboles.

## Recorridos

Recorrer un árbol significa visitar todos sus nodos en algún orden. Los tres recorridos clásicos son variantes de DFS (recorrido en profundidad) y difieren en **cuándo** se visita el nodo actual respecto de sus hijos.

### Pre-order

Visita: **Nodo, Izquierdo, Derecho**.

```cpp
template <typename T>
void preOrder(Nodo<T>* raiz, std::vector<T>& resultado) {
    if (raiz == nullptr) return;
    resultado.push_back(raiz->clave);
    preOrder(raiz->izquierdo, resultado);
    preOrder(raiz->derecho, resultado);
}
```

### In-order

Visita: **Izquierdo, Nodo, Derecho**.

```cpp
template <typename T>
void inOrder(Nodo<T>* raiz, std::vector<T>& resultado) {
    if (raiz == nullptr) return;
    inOrder(raiz->izquierdo, resultado);
    resultado.push_back(raiz->clave);
    inOrder(raiz->derecho, resultado);
}
```

> En un **ABB**, el recorrido in-order visita las claves en orden **creciente**. Esto no es casualidad: es consecuencia directa de la propiedad de orden del ABB (ver más abajo).

### Post-order

Visita: **Izquierdo, Derecho, Nodo**.

```cpp
template <typename T>
void postOrder(Nodo<T>* raiz, std::vector<T>& resultado) {
    if (raiz == nullptr) return;
    postOrder(raiz->izquierdo, resultado);
    postOrder(raiz->derecho, resultado);
    resultado.push_back(raiz->clave);
}
```

> Post-order es el recorrido natural para **destruir** un árbol (liberar memoria): hay que liberar los hijos antes que el nodo padre.

### Recorrido por niveles (BFS)

A diferencia de los anteriores, el recorrido por niveles **no es recursivo** de forma natural: se implementa con una **cola** (`std::queue`), visitando el árbol nivel por nivel.

```cpp
#include <queue>

template <typename T>
void bfs(Nodo<T>* raiz, std::vector<T>& resultado) {
    if (raiz == nullptr) return;

    std::queue<Nodo<T>*> cola;
    cola.push(raiz);

    while (!cola.empty()) {
        Nodo<T>* actual = cola.front();
        cola.pop();

        resultado.push_back(actual->clave);

        if (actual->izquierdo != nullptr) cola.push(actual->izquierdo);
        if (actual->derecho != nullptr)   cola.push(actual->derecho);
    }
}
```

Los cuatro recorridos visitan cada nodo exactamente una vez, por lo tanto todos cuestan **O(n)**.

> Pregunta para pensar: ¿por qué el recorrido por niveles usa una **cola** (FIFO) y el recorrido en profundidad usa (implícitamente, vía la recursión) una **pila** (LIFO)? ¿Qué pasaría si usaras una pila para hacer BFS?



# Árbol de Búsqueda Binaria (ABB)

## Propiedad de orden

Un ABB es un árbol binario que cumple, para **cada** nodo:

- Todas las claves del **subárbol izquierdo** son **menores** que la clave del nodo.
- Todas las claves del **subárbol derecho** son **mayores** que la clave del nodo.

```
        8
       / \
      3   10
     / \    \
    1   6    14
       / \   /
      4   7 13
```

```cpp
template <typename T>
struct NodoABB {
    T clave;
    NodoABB<T>* izquierdo;
    NodoABB<T>* derecho;

    NodoABB(T c) : clave(c), izquierdo(nullptr), derecho(nullptr) {}
};
```

## Buscar

```cpp
template <typename T>
NodoABB<T>* buscar(NodoABB<T>* raiz, T clave) {
    if (raiz == nullptr) return nullptr;
    if (raiz->clave == clave) return raiz;

    if (clave < raiz->clave) return buscar(raiz->izquierdo, clave);
    return buscar(raiz->derecho, clave);
}
```

En cada llamada descartamos **uno de los dos subárboles enteros**, igual que en la búsqueda binaria sobre un vector.

## Insertar

```cpp
template <typename T>
NodoABB<T>* insertar(NodoABB<T>* raiz, T clave) {
    if (raiz == nullptr) return new NodoABB<T>(clave);

    if (clave < raiz->clave) {
        raiz->izquierdo = insertar(raiz->izquierdo, clave);
    } else if (clave > raiz->clave) {
        raiz->derecho = insertar(raiz->derecho, clave);
    }
    // si clave == raiz->clave, no insertamos duplicados

    return raiz;
}
```

> Notá el patrón: la función recursiva **devuelve el árbol actualizado**, y quien la llama reasigna el puntero correspondiente (`raiz->izquierdo = insertar(...)`). Este patrón se repite en insertar, borrar y balancear.

## Borrar

Borrar un nodo tiene **tres casos** según la cantidad de hijos:

**Caso 1: el nodo es una hoja** (0 hijos). Se elimina directamente.

**Caso 2: el nodo tiene 1 hijo.** Se reemplaza el nodo por su único hijo.

**Caso 3: el nodo tiene 2 hijos.** Se busca el **sucesor in-order** (el mínimo del subárbol derecho, es decir, el elemento inmediatamente mayor), se copia su clave al nodo a borrar, y se borra el sucesor de su posición original (que, por ser el mínimo de un subárbol, tiene a lo sumo 1 hijo derecho, cayendo en el Caso 1 o 2).

```cpp
template <typename T>
T minimo(NodoABB<T>* raiz) {
    while (raiz->izquierdo != nullptr) {
        raiz = raiz->izquierdo;
    }
    return raiz->clave;
}

template <typename T>
NodoABB<T>* borrar(NodoABB<T>* raiz, T clave) {
    if (raiz == nullptr) return nullptr;

    if (clave < raiz->clave) {
        raiz->izquierdo = borrar(raiz->izquierdo, clave);
        return raiz;
    }
    if (clave > raiz->clave) {
        raiz->derecho = borrar(raiz->derecho, clave);
        return raiz;
    }

    // clave == raiz->clave: encontramos el nodo a borrar

    // Caso 1 y 2: 0 o 1 hijo
    if (raiz->izquierdo == nullptr) {
        NodoABB<T>* hijo = raiz->derecho;
        delete raiz;
        return hijo;
    }
    if (raiz->derecho == nullptr) {
        NodoABB<T>* hijo = raiz->izquierdo;
        delete raiz;
        return hijo;
    }

    // Caso 3: 2 hijos, busco el sucesor in-order
    T sucesor = minimo(raiz->derecho);
    raiz->clave = sucesor;
    raiz->derecho = borrar(raiz->derecho, sucesor);
    return raiz;
}
```

> Pregunta para pensar: en el Caso 3, ¿por qué también podríamos usar el **predecesor in-order** (el máximo del subárbol izquierdo) en vez del sucesor? ¿Cambiaría en algo la corrección del algoritmo?

## Relación con la búsqueda binaria

Un ABB balanceado es, conceptualmente, la versión "dinámica" de la búsqueda binaria sobre un vector ordenado: cada nodo actúa como el "elemento medio" de su subárbol, descartando la mitad del espacio de búsqueda en cada paso. La diferencia clave es que el ABB permite **insertar y borrar** en O(log n) (si está balanceado), mientras que un vector ordenado necesita O(n) para insertar o borrar (por tener que correr elementos).

## Complejidades del ABB

| Operación | Caso promedio (árbol balanceado) | Peor caso (árbol degenerado) |
| ---------- | ---------------------------------- | ------------------------------ |
| Buscar     | O(log n)                          | O(n)                           |
| Insertar   | O(log n)                          | O(n)                           |
| Borrar     | O(log n)                          | O(n)                           |
| Recorridos | O(n)                               | O(n)                           |

> El peor caso ocurre cuando el árbol **degenera en una lista enlazada**: por ejemplo, al insertar `1, 2, 3, 4, 5` en ese orden, cada nodo termina teniendo únicamente hijo derecho. Este es exactamente el problema que motiva los árboles **AVL**.



# AVL: árboles balanceados

## El problema del desbalanceo

Si insertamos claves ya ordenadas (crecientes o decrecientes) en un ABB común, el árbol se "estira" hacia un lado y pierde toda ventaja frente a una lista enlazada: todas las operaciones pasan a costar O(n).

```
Insertar 1, 2, 3, 4, 5 en orden en un ABB común:

1
 \
  2
   \
    3
     \
      4
       \
        5
```

> **Este es el problema que motiva a los árboles AVL** (Adelson-Velskii y Landis, 1962): garantizar que el árbol se mantenga balanceado sin importar el orden de inserción.

## Factor de balance e invariante

Cada nodo de un AVL guarda su **factor de balance**: la diferencia de altura entre su subárbol derecho y su subárbol izquierdo.

```cpp
template <typename T>
struct NodoAVL {
    T clave;
    NodoAVL<T>* izquierdo;
    NodoAVL<T>* derecho;
    int altura;  // altura del subárbol con raíz en este nodo

    NodoAVL(T c) : clave(c), izquierdo(nullptr), derecho(nullptr), altura(1) {}
};

int altura(NodoAVL<int>* nodo) {
    return nodo == nullptr ? 0 : nodo->altura;
}

int factorBalance(NodoAVL<int>* nodo) {
    if (nodo == nullptr) return 0;
    return altura(nodo->derecho) - altura(nodo->izquierdo);
}
```

> **Invariante AVL:** para **todo** nodo del árbol, el factor de balance debe estar en `{-1, 0, 1}`. Si después de un `insertar` o `borrar` algún nodo queda con factor de balance `-2` o `2`, hay que **rebalancear** con rotaciones.

## Rotaciones

Cuando se detecta un nodo desbalanceado `Z`, se identifica su hijo `Y` (en el camino hacia el desbalanceo) y el nieto `X` (también en ese camino), y se aplica una de cuatro rotaciones según la configuración de `Z`, `Y`, `X`.

### Rotación simple

**Caso Izquierda-Izquierda:** `X` es hijo izquierdo de `Y`, que es hijo izquierdo de `Z`. Se resuelve con una **rotación derecha** sobre `Z`.

```
        Z                Y
       / \             /   \
      Y   T4   -->    X     Z
     / \             / \   / \
    X   T3          T1 T2 T3 T4
   / \
  T1  T2
```

```cpp
NodoAVL<int>* rotacionDerecha(NodoAVL<int>* z) {
    NodoAVL<int>* y = z->izquierdo;
    NodoAVL<int>* t3 = y->derecho;

    y->derecho = z;
    z->izquierdo = t3;

    z->altura = 1 + std::max(altura(z->izquierdo), altura(z->derecho));
    y->altura = 1 + std::max(altura(y->izquierdo), altura(y->derecho));

    return y;  // y pasa a ser la nueva raíz de este subárbol
}
```

El caso simétrico, **Derecha-Derecha**, se resuelve con una **rotación izquierda** sobre `Z` (análoga, intercambiando izquierda por derecha).

### Rotación doble

**Caso Izquierda-Derecha:** `X` es hijo derecho de `Y`, que es hijo izquierdo de `Z`. Se resuelve con **dos** rotaciones: primero una rotación izquierda sobre `Y`, y después una rotación derecha sobre `Z` (con lo cual el caso se reduce al anterior).

```
      Z              Z              X
     / \            / \           /   \
    Y   T4  -->    X   T4  -->  Y     Z
   / \            / \          / \   / \
  T1  X          Y   T3      T1 T2 T3 T4
     / \        / \
    T2  T3     T1  T2
```

```cpp
NodoAVL<int>* rotacionIzquierda(NodoAVL<int>* z) {
    NodoAVL<int>* y = z->derecho;
    NodoAVL<int>* t2 = y->izquierdo;

    y->izquierdo = z;
    z->derecho = t2;

    z->altura = 1 + std::max(altura(z->izquierdo), altura(z->derecho));
    y->altura = 1 + std::max(altura(y->izquierdo), altura(y->derecho));

    return y;
}

NodoAVL<int>* balancear(NodoAVL<int>* z) {
    int fb = factorBalance(z);

    // Desbalanceado hacia la izquierda
    if (fb < -1) {
        if (factorBalance(z->izquierdo) > 0) {
            z->izquierdo = rotacionIzquierda(z->izquierdo);  // paso Izq-Der
        }
        return rotacionDerecha(z);  // Izq-Izq (o ya reducido a ese caso)
    }

    // Desbalanceado hacia la derecha
    if (fb > 1) {
        if (factorBalance(z->derecho) < 0) {
            z->derecho = rotacionDerecha(z->derecho);  // paso Der-Izq
        }
        return rotacionIzquierda(z);  // Der-Der (o ya reducido a ese caso)
    }

    return z;  // ya estaba balanceado
}
```

El caso simétrico, **Derecha-Izquierda**, se resuelve primero con una rotación derecha sobre `Y` y después una rotación izquierda sobre `Z`.

> Tanto `insertar` como `borrar` en un AVL se implementan igual que en un ABB, pero **al volver de la recursión** se actualiza la altura del nodo y se llama a `balancear`. Por eso el patrón `raiz = insertar(raiz->hijo, clave)` es tan importante: permite "reemplazar" el subárbol por su versión balanceada.

> Pregunta para pensar: ¿por qué el rebalanceo se hace "al volver" de la recursión (post-order) y no "al bajar" (pre-order)? *Ayuda: para decidir la rotación necesitás conocer la altura de los subárboles ya actualizados.*

## Complejidades del AVL

| Operación | Peor caso |
| ---------- | ---------- |
| Buscar     | O(log n)  |
| Insertar   | O(log n)  |
| Borrar     | O(log n)  |
| Recorridos | O(n)      |

> A diferencia del ABB, en el AVL **no existe un peor caso degenerado**: el invariante de balance garantiza que la altura del árbol siempre es O(log n), sin importar el orden de inserción.



# Trie

## Estructura para strings y prefijos

Un **Trie** (o árbol de prefijos) es una estructura especializada para almacenar **strings**, pensada para que las operaciones dependan del **largo de la clave** y no de la cantidad de elementos almacenados. Cada nodo representa un **prefijo**, y sus hijos representan los posibles caracteres siguientes.

```cpp
#include <array>

struct NodoTrie {
    std::array<NodoTrie*, 26> hijos;  // uno por cada letra 'a'..'z'
    bool esFinDePalabra;

    NodoTrie() : esFinDePalabra(false) {
        hijos.fill(nullptr);
    }
};
```

```
Insertando "sol", "sopa" y "sal":

              (raíz)
                |
                s
               / \
              o   a
             /|    \
            l p     l
            |  \    |
           (*)  a  (*)
                |
               (*)

(*) marca fin de palabra
```

## Insertar en un Trie

```cpp
void insertarTrie(NodoTrie* raiz, const std::string& palabra) {
    NodoTrie* actual = raiz;

    for (char c : palabra) {
        int indice = c - 'a';
        if (actual->hijos[indice] == nullptr) {
            actual->hijos[indice] = new NodoTrie();
        }
        actual = actual->hijos[indice];
    }

    actual->esFinDePalabra = true;
}
```

También se puede escribir de forma recursiva, consumiendo un carácter por llamada:

```cpp
NodoTrie* insertarTrieRec(NodoTrie* nodo, const std::string& palabra, size_t i) {
    if (nodo == nullptr) nodo = new NodoTrie();

    if (i == palabra.size()) {
        nodo->esFinDePalabra = true;
        return nodo;
    }

    int indice = palabra[i] - 'a';
    nodo->hijos[indice] = insertarTrieRec(nodo->hijos[indice], palabra, i + 1);
    return nodo;
}
```

## Buscar en un Trie

```cpp
bool buscarTrie(NodoTrie* raiz, const std::string& palabra) {
    NodoTrie* actual = raiz;

    for (char c : palabra) {
        int indice = c - 'a';
        if (actual->hijos[indice] == nullptr) return false;
        actual = actual->hijos[indice];
    }

    return actual->esFinDePalabra;
}
```

> Con una pequeña variante (sacando el chequeo de `esFinDePalabra` al final), esta misma función sirve para responder "¿existe alguna palabra con este prefijo?", que es la base de un autocompletado.

## Trie vs ABB

| Aspecto                       | ABB (balanceado)         | Trie                                  |
| ------------------------------ | ------------------------- | -------------------------------------- |
| Costo de buscar/insertar       | O(log n) comparaciones de strings completos | O(L), con L = largo de la clave |
| Costo de comparar una clave     | O(L) por cada comparación (hay que comparar el string entero) | No se "compara" el string entero: se consume un carácter por nivel |
| Búsqueda por prefijo            | Ineficiente (hay que recorrer y filtrar) | Natural y eficiente: alcanza con bajar por el prefijo |
| Uso de memoria                  | Un nodo por clave         | Puede compartir nodos entre claves con el mismo prefijo, pero cada nodo reserva espacio para el alfabeto completo |

> Un ABB con `n` strings de largo `L` cuesta **O(L log n)** para buscar (cada una de las `log n` comparaciones cuesta O(L) porque hay que comparar strings completos). Un Trie cuesta **O(L)**, independientemente de cuántas palabras haya almacenadas. Por eso el Trie es la estructura de preferencia cuando el dominio del problema es texto y hace falta trabajar con prefijos.

> Pregunta para pensar: ¿por qué el costo de un Trie **no depende** de la cantidad de elementos almacenados (`n`), a diferencia de todas las estructuras que vimos hasta ahora?



# Estructuras compuestas

En muchos problemas reales, ninguna estructura por sí sola alcanza para soportar **todos** los accesos que se necesitan de forma eficiente. Por ejemplo, si necesitamos:

- Buscar por clave en O(log n) o mejor, **y**
- Recorrer los elementos en orden de inserción, **y**
- Encontrar el mínimo en O(1),

puede convenir **combinar estructuras**: por ejemplo, un ABB (o una tabla de hash) para búsqueda por clave, más una lista enlazada para preservar el orden de inserción, con punteros cruzados entre ambas representaciones del mismo dato.

> La idea general es: **cada estructura optimiza un tipo de acceso**. Cuando un problema pide varios accesos eficientes distintos, la solución suele ser mantener el mismo conjunto de datos replicado (o enlazado) en más de una estructura, en vez de forzar a una sola estructura a hacer todo bien.



# Resumen de complejidades

| Estructura | Buscar    | Insertar  | Borrar    | Peor caso            |
| ----------- | --------- | --------- | --------- | ---------------------- |
| ABB         | O(log n)  | O(log n)  | O(log n)  | O(n) (árbol degenerado) |
| AVL         | O(log n)  | O(log n)  | O(log n)  | O(log n) (garantizado)  |
| Trie        | O(L)      | O(L)      | O(L)      | O(L), con L = largo de la clave |

> Pregunta para pensar: si tuvieras que elegir entre un ABB y un AVL para una aplicación donde se insertan y borran datos constantemente pero casi no se hacen búsquedas, ¿qué estructura elegirías y por qué? *Ayuda: pensá el costo de mantener el balanceo estricto del AVL frente al beneficio que aporta.*
