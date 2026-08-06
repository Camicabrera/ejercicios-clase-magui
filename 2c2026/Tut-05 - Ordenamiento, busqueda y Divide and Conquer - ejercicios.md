Tutorial 5 – Ejercicios de Ordenamiento, búsqueda y Divide & Conquer
===

En esta guía practicamos merge sort, quick sort, el teorema maestro y variantes de búsqueda binaria. Todos los ejercicios están pensados para resolverse con `std::vector` en C++.

> Antes de arrancar: repasá la recurrencia `T(n) = a·T(n/b) + f(n)` y los tres casos del teorema maestro. Los vamos a usar constantemente para justificar la complejidad de cada solución.



## Ejercicio 1 - Implementar `merge`

Implementá la función `merge(v, izq, medio, der)` que combina dos sub-rangos ya ordenados (`[izq, medio]` y `[medio+1, der]`) de un `std::vector<int>` en un único rango ordenado.

### Solución

```cpp
#include <vector>

void merge(std::vector<int>& v, int izq, int medio, int der) {
    std::vector<int> aux;
    aux.reserve(der - izq + 1);

    int i = izq;
    int j = medio + 1;

    // Mientras haya elementos en ambas mitades, elijo el menor
    while (i <= medio && j <= der) {
        if (v[i] <= v[j]) {   // <= (no <) para que la mezcla sea estable
            aux.push_back(v[i]);
            i++;
        } else {
            aux.push_back(v[j]);
            j++;
        }
    }

    // Vuelco lo que quedó sin procesar de cada mitad
    while (i <= medio) aux.push_back(v[i++]);
    while (j <= der)   aux.push_back(v[j++]);

    // Copio el resultado de vuelta al vector original
    for (int k = 0; k < (int)aux.size(); k++) {
        v[izq + k] = aux[k];
    }
}
```

`merge` recorre cada mitad una sola vez, por lo tanto su costo es **O(n)**, con `n = der - izq + 1`.



## Ejercicio 2 - Implementar merge sort completo

Usando la función `merge` del ejercicio anterior, implementá `mergeSort(v, izq, der)` que ordene el vector completo.

### Solución

```cpp
void mergeSort(std::vector<int>& v, int izq, int der) {
    if (izq >= der) return;  // caso base: 0 o 1 elemento, ya está ordenado

    int medio = izq + (der - izq) / 2;

    mergeSort(v, izq, medio);       // divido y conquisto la mitad izquierda
    mergeSort(v, medio + 1, der);   // divido y conquisto la mitad derecha
    merge(v, izq, medio, der);      // combino ambas mitades ordenadas
}

// Función auxiliar para llamarlo más cómodo desde afuera
void mergeSort(std::vector<int>& v) {
    if (!v.empty()) mergeSort(v, 0, (int)v.size() - 1);
}
```

La recurrencia es `T(n) = 2·T(n/2) + O(n)`. Por el teorema maestro (`a=2, b=2, f(n)=n`, Caso 2), `T(n) = Θ(n log n)`.



## Ejercicio 3 - Partición de quicksort

Implementá `partition(v, izq, der)` usando el esquema de Lomuto (pivot = último elemento del rango), y usala para armar `quickSort`.

### Solución

```cpp
int partition(std::vector<int>& v, int izq, int der) {
    int pivot = v[der];
    int i = izq - 1;  // último índice de la zona "< pivot"

    for (int j = izq; j < der; j++) {
        if (v[j] < pivot) {
            i++;
            std::swap(v[i], v[j]);
        }
    }

    std::swap(v[i + 1], v[der]);  // ubico el pivot en su posición final
    return i + 1;
}

void quickSort(std::vector<int>& v, int izq, int der) {
    if (izq >= der) return;

    int p = partition(v, izq, der);

    quickSort(v, izq, p - 1);
    quickSort(v, p + 1, der);
}
```

> Notá que después de `partition`, el elemento en la posición `p` queda en su posición **definitiva** dentro del vector ordenado: todo lo que está a su izquierda es menor, y todo lo que está a su derecha es mayor o igual.



## Ejercicio 4 - Búsqueda binaria clásica

Implementá `busquedaBinaria(v, buscado)` que devuelva el índice del elemento buscado, o `-1` si no está. El vector está ordenado de forma creciente.

### Solución

```cpp
int busquedaBinaria(const std::vector<int>& v, int buscado) {
    int izq = 0;
    int der = (int)v.size() - 1;

    while (izq <= der) {
        int medio = izq + (der - izq) / 2;

        if (v[medio] == buscado) {
            return medio;
        } else if (v[medio] < buscado) {
            izq = medio + 1;
        } else {
            der = medio - 1;
        }
    }

    return -1;
}
```

Complejidad: `T(n) = T(n/2) + O(1)` → por el teorema maestro, `T(n) = Θ(log n)`.



## Ejercicio 5 - `lower_bound` y primera/última ocurrencia

Dado un vector ordenado que puede tener **elementos repetidos**, implementá:

a) `lowerBound(v, x)`: el índice del primer elemento `>= x` (o `v.size()` si no existe).
b) `primeraOcurrencia(v, x)` y `ultimaOcurrencia(v, x)`: el índice de la primera y la última aparición de `x` (o `-1` si no está).

### Solución

```cpp
// Primer índice tal que v[i] >= x
int lowerBound(const std::vector<int>& v, int x) {
    int izq = 0;
    int der = (int)v.size();  // rango [izq, der)

    while (izq < der) {
        int medio = izq + (der - izq) / 2;
        if (v[medio] < x) {
            izq = medio + 1;
        } else {
            der = medio;  // v[medio] >= x, puede ser la respuesta
        }
    }

    return izq;
}

int primeraOcurrencia(const std::vector<int>& v, int x) {
    int idx = lowerBound(v, x);
    if (idx < (int)v.size() && v[idx] == x) return idx;
    return -1;
}

int ultimaOcurrencia(const std::vector<int>& v, int x) {
    // La última ocurrencia de x es "el lower_bound de x+1" menos uno
    int idx = lowerBound(v, x + 1) - 1;
    if (idx >= 0 && v[idx] == x) return idx;
    return -1;
}
```

> `lowerBound` es exactamente lo que hace `std::lower_bound` de la STL. La idea de buscar "la primera posición donde x+1 podría insertarse" para encontrar la última ocurrencia de `x` es un truco clásico: evita escribir un tercer binary search desde cero.



## Ejercicio 6 - Aplicar el teorema maestro

Para cada recurrencia, identificá `a`, `b` y `f(n)`, determiná qué caso del teorema maestro corresponde y dá la complejidad resultante.

a) `T(n) = 8·T(n/2) + n²`
b) `T(n) = 3·T(n/4) + n`
c) `T(n) = 2·T(n/2) + n log n`
d) `T(n) = T(n/2) + 1`

### Solución

**a)** `a=8, b=2, f(n)=n²`. `n^(log_2 8) = n³`. Como `n² = O(n^(3-ε))`, es **Caso 1**. `T(n) = Θ(n³)`.

**b)** `a=3, b=4, f(n)=n`. `log_4 3 ≈ 0.79`, entonces `n^(log_4 3) ≈ n^0.79`. Como `f(n) = n = Ω(n^(0.79+ε))` (crece más rápido) y cumple la condición de regularidad, es **Caso 3**. `T(n) = Θ(n)`.

**c)** `a=2, b=2, f(n) = n log n`. `n^(log_2 2) = n`. Acá `f(n) = n log n` no es `Θ(n)` estricto (crece un poco más rápido, pero no polinomialmente más rápido), por lo que **no encaja exactamente en ninguno de los tres casos clásicos**. Es un caso límite del Caso 2 extendido, y se resuelve por el método del árbol de recursión: da `T(n) = Θ(n log² n)`.

**d)** Es la recurrencia de búsqueda binaria: `a=1, b=2, f(n)=1`. `n^(log_2 1) = n^0 = 1`. Es **Caso 2**. `T(n) = Θ(log n)`.

> El ítem (c) es intencional: sirve para notar que el teorema maestro **no cubre todas las recurrencias posibles**, solo aquellas donde `f(n)` es polinomialmente mayor, menor o igual a `n^(log_b a)`.



## Ejercicio 7 - Contar inversiones con merge sort

Una **inversión** en un vector es un par de índices `(i, j)` con `i < j` pero `v[i] > v[j]` (están "desordenados" entre sí). Contar todas las inversiones comparando cada par cuesta O(n²). Implementá una solución **O(n log n)** modificando merge sort.

### Solución

La clave es que al hacer `merge`, cada vez que se toma un elemento de la mitad **derecha** antes que uno de la mitad **izquierda**, ese elemento forma una inversión con **todos** los elementos que quedan sin procesar en la mitad izquierda.

```cpp
long long merge_contando(std::vector<int>& v, int izq, int medio, int der) {
    std::vector<int> aux;
    aux.reserve(der - izq + 1);

    int i = izq;
    int j = medio + 1;
    long long inversiones = 0;

    while (i <= medio && j <= der) {
        if (v[i] <= v[j]) {
            aux.push_back(v[i]);
            i++;
        } else {
            // v[j] < v[i]: v[j] forma inversión con v[i] y con
            // todos los elementos que quedan entre i y medio
            inversiones += (medio - i + 1);
            aux.push_back(v[j]);
            j++;
        }
    }

    while (i <= medio) aux.push_back(v[i++]);
    while (j <= der)   aux.push_back(v[j++]);

    for (int k = 0; k < (int)aux.size(); k++) {
        v[izq + k] = aux[k];
    }

    return inversiones;
}

long long contarInversiones(std::vector<int>& v, int izq, int der) {
    if (izq >= der) return 0;

    int medio = izq + (der - izq) / 2;

    long long inv = 0;
    inv += contarInversiones(v, izq, medio);
    inv += contarInversiones(v, medio + 1, der);
    inv += merge_contando(v, izq, medio, der);

    return inv;
}
```

Como reutilizamos exactamente la estructura de merge sort, la complejidad sigue siendo `T(n) = 2·T(n/2) + O(n) = Θ(n log n)`.



## Ejercicio 8 - Buscar en un vector rotado

Un vector ordenado fue **rotado**: por ejemplo, `[4, 5, 6, 7, 0, 1, 2]` es `[0, 1, 2, 4, 5, 6, 7]` rotado. Implementá una búsqueda en `O(log n)` que encuentre un valor `x` en un vector rotado, sin ordenarlo primero.

### Solución

La idea: en cualquier partición por la mitad, **al menos una** de las dos mitades está "normalmente ordenada" (sin rotación interna). Se puede decidir en O(1) cuál mitad es la ordenada, y chequear si `x` cae en su rango para decidir hacia dónde seguir.

```cpp
int buscarEnRotado(const std::vector<int>& v, int x) {
    int izq = 0;
    int der = (int)v.size() - 1;

    while (izq <= der) {
        int medio = izq + (der - izq) / 2;

        if (v[medio] == x) return medio;

        if (v[izq] <= v[medio]) {
            // la mitad izquierda [izq, medio] está ordenada
            if (v[izq] <= x && x < v[medio]) {
                der = medio - 1;
            } else {
                izq = medio + 1;
            }
        } else {
            // la mitad derecha [medio, der] está ordenada
            if (v[medio] < x && x <= v[der]) {
                izq = medio + 1;
            } else {
                der = medio - 1;
            }
        }
    }

    return -1;
}
```

Sigue siendo `T(n) = T(n/2) + O(1) = Θ(log n)`, porque en cada paso se descarta la mitad, igual que en la búsqueda binaria clásica.



## Ejercicios propuestos

1. Implementá una versión de **insertion sort** que ordene un `std::vector<T>` usando un **comparador genérico** (`std::function<bool(const T&, const T&)>`), de forma que se pueda ordenar tanto de menor a mayor como de mayor a menor sin duplicar código.
2. Dado un vector ordenado con `n` elementos y `k` "vueltas" de rotación desconocidas, encontrá el **índice del mínimo** en O(log n) sin usar la búsqueda del ejercicio 8 (pensalo como un caso particular más simple).
