Tutorial 6 – Ejercicios de Árboles: ABB, AVL y Trie
===

En esta guía practicamos recorridos, propiedades estructurales, ABB, balanceo AVL y Trie. Todos los ejercicios usan C++ con recursión sobre `struct`s de nodos.

> Antes de arrancar: la mayoría de estos ejercicios se resuelven con el mismo patrón recursivo: caso base = árbol vacío (`nullptr`), caso recursivo = combinar el resultado de los subárboles.



## Ejercicio 1 - Implementar los cuatro recorridos

Dado el `struct` de árbol binario de abajo, implementá `preOrder`, `inOrder`, `postOrder` y `bfs`, cada uno devolviendo un `std::vector<int>` con las claves en el orden correspondiente.

```cpp
struct Nodo {
    int clave;
    Nodo* izquierdo;
    Nodo* derecho;
    Nodo(int c) : clave(c), izquierdo(nullptr), derecho(nullptr) {}
};
```

### Solución

```cpp
#include <vector>
#include <queue>

void preOrder(Nodo* raiz, std::vector<int>& res) {
    if (raiz == nullptr) return;
    res.push_back(raiz->clave);       // primero el nodo
    preOrder(raiz->izquierdo, res);
    preOrder(raiz->derecho, res);
}

void inOrder(Nodo* raiz, std::vector<int>& res) {
    if (raiz == nullptr) return;
    inOrder(raiz->izquierdo, res);
    res.push_back(raiz->clave);       // el nodo va en el medio
    inOrder(raiz->derecho, res);
}

void postOrder(Nodo* raiz, std::vector<int>& res) {
    if (raiz == nullptr) return;
    postOrder(raiz->izquierdo, res);
    postOrder(raiz->derecho, res);
    res.push_back(raiz->clave);       // el nodo va al final
}

std::vector<int> bfs(Nodo* raiz) {
    std::vector<int> res;
    if (raiz == nullptr) return res;

    std::queue<Nodo*> cola;
    cola.push(raiz);

    while (!cola.empty()) {
        Nodo* actual = cola.front();
        cola.pop();
        res.push_back(actual->clave);

        if (actual->izquierdo) cola.push(actual->izquierdo);
        if (actual->derecho)   cola.push(actual->derecho);
    }

    return res;
}
```

Los cuatro recorren cada nodo una sola vez: **O(n)**.



## Ejercicio 2 - Altura y cantidad de nodos

Implementá `altura(raiz)` (la cantidad de nodos en el camino más largo desde la raíz hasta una hoja) y `cantidadNodos(raiz)`.

### Solución

```cpp
int altura(Nodo* raiz) {
    if (raiz == nullptr) return 0;  // árbol vacío: altura 0
    return 1 + std::max(altura(raiz->izquierdo), altura(raiz->derecho));
}

int cantidadNodos(Nodo* raiz) {
    if (raiz == nullptr) return 0;
    return 1 + cantidadNodos(raiz->izquierdo) + cantidadNodos(raiz->derecho);
}
```

Ambas funciones visitan cada nodo una vez: **O(n)**.



## Ejercicio 3 - Contar hojas

Implementá `cantidadHojas(raiz)`, que cuenta los nodos que **no tienen hijos**.

### Solución

```cpp
int cantidadHojas(Nodo* raiz) {
    if (raiz == nullptr) return 0;

    // Un nodo es hoja si no tiene ni hijo izquierdo ni derecho
    if (raiz->izquierdo == nullptr && raiz->derecho == nullptr) {
        return 1;
    }

    return cantidadHojas(raiz->izquierdo) + cantidadHojas(raiz->derecho);
}
```

> Notá que el caso base del árbol vacío (`raiz == nullptr`) devuelve `0`, y el caso "es hoja" es un segundo caso base distinto: hay que tener cuidado de no confundirlos.



## Ejercicio 4 - Validar si un árbol es ABB

Dado un árbol binario genérico, determiná si cumple la propiedad de ABB (para cada nodo, todo lo del subárbol izquierdo es menor y todo lo del subárbol derecho es mayor).

> Un error común es comparar solo contra el padre inmediato (`izquierdo->clave < raiz->clave`); eso **no alcanza**, porque la propiedad debe cumplirse contra **todos** los ancestros, no solo el padre directo.

### Solución

```cpp
#include <climits>

bool esABBrec(Nodo* raiz, long long minimo, long long maximo) {
    if (raiz == nullptr) return true;  // árbol vacío: es válido

    if (raiz->clave <= minimo || raiz->clave >= maximo) {
        return false;  // la clave viola el rango permitido por algún ancestro
    }

    return esABBrec(raiz->izquierdo, minimo, raiz->clave) &&
           esABBrec(raiz->derecho, raiz->clave, maximo);
}

bool esABB(Nodo* raiz) {
    return esABBrec(raiz, LLONG_MIN, LLONG_MAX);
}
```

Cada llamada recursiva **acota** el rango válido de claves: el subárbol izquierdo hereda `maximo = raiz->clave`, y el subárbol derecho hereda `minimo = raiz->clave`. Complejidad: **O(n)**.



## Ejercicio 5 - Insertar y buscar en un ABB

Implementá `insertar(raiz, clave)` y `buscar(raiz, clave)` para un ABB de enteros (sin duplicados).

### Solución

```cpp
Nodo* insertar(Nodo* raiz, int clave) {
    if (raiz == nullptr) return new Nodo(clave);

    if (clave < raiz->clave) {
        raiz->izquierdo = insertar(raiz->izquierdo, clave);
    } else if (clave > raiz->clave) {
        raiz->derecho = insertar(raiz->derecho, clave);
    }
    // si clave == raiz->clave, no hacemos nada (no hay duplicados)

    return raiz;
}

Nodo* buscar(Nodo* raiz, int clave) {
    if (raiz == nullptr || raiz->clave == clave) return raiz;

    if (clave < raiz->clave) return buscar(raiz->izquierdo, clave);
    return buscar(raiz->derecho, clave);
}
```

Costo amortizado O(log n) si el árbol está razonablemente balanceado; O(n) en el peor caso (árbol degenerado).



## Ejercicio 6 - Mínimo y máximo de un ABB

Implementá `minimo(raiz)` y `maximo(raiz)` en un ABB, **sin** recorrer todo el árbol.

### Solución

```cpp
int minimo(Nodo* raiz) {
    // El mínimo de un ABB siempre está en el extremo izquierdo
    while (raiz->izquierdo != nullptr) {
        raiz = raiz->izquierdo;
    }
    return raiz->clave;
}

int maximo(Nodo* raiz) {
    // El máximo siempre está en el extremo derecho
    while (raiz->derecho != nullptr) {
        raiz = raiz->derecho;
    }
    return raiz->clave;
}
```

Gracias a la propiedad de orden del ABB, no hace falta comparar contra todos los nodos: alcanza con "bajar" siempre por el mismo lado. Costo: O(altura), que en un árbol balanceado es O(log n).



## Ejercicio 7 - Balancear un caso AVL (a mano y en código)

Partiendo de un ABB vacío, insertá en orden las claves `30, 20, 10`.

a) Dibujá el árbol después de cada inserción e indicá cuándo se desbalancea.
b) Identificá qué rotación corresponde y aplicala a mano.
c) Contá cuántas rotaciones hicieron falta en total.

### Solución

**Inserto 30:**
```
30
```
Balanceado (único nodo).

**Inserto 20:**
```
  30
  /
20
```
Factor de balance de `30` es `-1` (altura izq 1, altura der 0). Sigue dentro del rango `[-1, 1]`: balanceado.

**Inserto 10:**
```
    30
    /
  20
  /
10
```
Factor de balance de `30` ahora es `-2` (altura izq 2, altura der 0): **desbalanceado**.

El camino de desbalanceo es `30 (Z) -> 20 (Y) -> 10 (X)`, y `10` es hijo izquierdo de `20`, que es hijo izquierdo de `30`: es el caso **Izquierda-Izquierda**. Se resuelve con **una rotación derecha sobre 30**:

```
     20
    /  \
  10    30
```

Rotaciones necesarias: **1** (una rotación simple).

```cpp
// Aplicando el código de balanceo del apunte teórico:
NodoAVL<int>* raiz = new NodoAVL<int>(30);
raiz->izquierdo = new NodoAVL<int>(20);
raiz->izquierdo->izquierdo = new NodoAVL<int>(10);
// factorBalance(raiz) == -2 → desbalanceado hacia la izquierda
// factorBalance(raiz->izquierdo) == -1 (no es > 0) → no hace falta rotación previa
// se aplica directamente rotacionDerecha(raiz)
raiz = rotacionDerecha(raiz);  // raiz ahora es el nodo con clave 20
```

> Si en cambio hubiéramos insertado `30, 10, 20` (en ese orden), el desbalanceo sería **Izquierda-Derecha**: haría falta primero una rotación izquierda sobre el hijo (`10`) y después una rotación derecha sobre la raíz (`30`), es decir, **2 rotaciones** para el mismo resultado final.



## Ejercicio 8 - Trie para autocompletado y conteo de prefijos

Implementá `contarPalabrasConPrefijo(raiz, prefijo)`, que devuelva cuántas palabras insertadas en el Trie empiezan con `prefijo`.

*Sugerencia: agregá un contador `cantidadPalabras` en cada nodo, que se incrementa cada vez que una inserción pasa por él.*

### Solución

```cpp
struct NodoTrie {
    std::array<NodoTrie*, 26> hijos;
    bool esFinDePalabra;
    int cantidadPalabras;  // cuántas palabras insertadas pasan por este nodo

    NodoTrie() : esFinDePalabra(false), cantidadPalabras(0) {
        hijos.fill(nullptr);
    }
};

void insertarTrie(NodoTrie* raiz, const std::string& palabra) {
    NodoTrie* actual = raiz;
    actual->cantidadPalabras++;  // la raíz "contiene" todas las palabras

    for (char c : palabra) {
        int indice = c - 'a';
        if (actual->hijos[indice] == nullptr) {
            actual->hijos[indice] = new NodoTrie();
        }
        actual = actual->hijos[indice];
        actual->cantidadPalabras++;
    }

    actual->esFinDePalabra = true;
}

int contarPalabrasConPrefijo(NodoTrie* raiz, const std::string& prefijo) {
    NodoTrie* actual = raiz;

    for (char c : prefijo) {
        int indice = c - 'a';
        if (actual->hijos[indice] == nullptr) return 0;  // no hay ninguna palabra con ese prefijo
        actual = actual->hijos[indice];
    }

    return actual->cantidadPalabras;
}
```

Costo: **O(L)**, con `L` el largo del prefijo, sin importar cuántas palabras haya almacenadas en el Trie. Este mismo contador es la base para implementar un autocompletado: una vez ubicado el nodo del prefijo, se puede hacer un DFS desde ahí para listar todas las palabras que lo extienden.



## Ejercicio 9 - Ancestro común más bajo (LCA) en un ABB

Dado un ABB y dos claves `a` y `b` que **sí** están en el árbol, encontrá su **LCA** (Lowest Common Ancestor): el nodo más profundo que es ancestro de ambos.

> A diferencia de un árbol binario genérico (donde el LCA requiere buscar en ambos subárboles y combinar resultados), en un **ABB** se puede resolver aprovechando la propiedad de orden, sin explorar todo el árbol.

### Solución

```cpp
Nodo* lca(Nodo* raiz, int a, int b) {
    if (raiz == nullptr) return nullptr;

    // Si ambas claves son menores que la raíz, el LCA está en el subárbol izquierdo
    if (a < raiz->clave && b < raiz->clave) {
        return lca(raiz->izquierdo, a, b);
    }

    // Si ambas claves son mayores que la raíz, el LCA está en el subárbol derecho
    if (a > raiz->clave && b > raiz->clave) {
        return lca(raiz->derecho, a, b);
    }

    // Si no caen ambas del mismo lado, la raíz actual es el punto de divergencia:
    // es el LCA (esto incluye el caso a == raiz->clave o b == raiz->clave)
    return raiz;
}
```

La intuición es que el LCA es el **primer nodo en el que `a` y `b` "se separan"**: mientras ambas claves estén del mismo lado, hay que seguir bajando por ese lado; en cuanto se separan (o alguna coincide con el nodo actual), encontramos el LCA. Costo: O(altura), es decir O(log n) en un árbol balanceado y O(n) en el peor caso.



## Ejercicios propuestos

1. Implementá `esBalanceado(raiz)` para un árbol binario genérico, que determine si **todos** los nodos cumplen el invariante AVL (factor de balance en `{-1, 0, 1}`). Intentá que la solución sea O(n) y no O(n²) (pensá qué información conviene devolver desde cada llamada recursiva además de un booleano).
2. Extendé el Trie del Ejercicio 8 para soportar **borrado** de palabras (`borrarTrie(raiz, palabra)`), liberando los nodos que queden sin ninguna palabra que los use (es decir, con `cantidadPalabras == 0` después del borrado).
