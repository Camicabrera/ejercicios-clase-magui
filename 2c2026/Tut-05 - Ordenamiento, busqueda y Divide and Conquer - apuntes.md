Tutorial 5 – Ordenamiento, búsqueda y Divide & Conquer
===

- [Tutorial 5 – Ordenamiento, búsqueda y Divide & Conquer](#tutorial-5--ordenamiento-búsqueda-y-divide--conquer)
- [Objetivos de la clase](#objetivos-de-la-clase)
- [Ordenamiento](#ordenamiento)
  - [Algoritmos elementales de ordenamiento](#algoritmos-elementales-de-ordenamiento)
    - [Bubble sort](#bubble-sort)
    - [Insertion sort](#insertion-sort)
    - [Selection sort](#selection-sort)
  - [Estabilidad en algoritmos de ordenamiento](#estabilidad-en-algoritmos-de-ordenamiento)
  - [Costo según la estructura de datos](#costo-según-la-estructura-de-datos)
- [Divide y Conquer](#divide-y-conquer)
  - [La idea general](#la-idea-general)
  - [Merge sort](#merge-sort)
    - [La función merge](#la-función-merge)
  - [Quick sort](#quick-sort)
    - [Partición (partition)](#partición-partition)
  - [El teorema maestro](#el-teorema-maestro)
    - [Enunciado general](#enunciado-general)
    - [Los tres casos](#los-tres-casos)
    - [Ejemplos aplicados](#ejemplos-aplicados)
- [Búsqueda](#búsqueda)
  - [Búsqueda lineal](#búsqueda-lineal)
  - [Búsqueda binaria](#búsqueda-binaria)
  - [Precondición e invariante](#precondición-e-invariante)
  - [Complejidad de las búsquedas](#complejidad-de-las-búsquedas)
  - [Cuándo conviene cada una](#cuándo-conviene-cada-una)



# Objetivos de la clase
- Repasar los algoritmos de ordenamiento elementales (bubble, insertion, selection) y su complejidad.
- Entender qué significa que un algoritmo de ordenamiento sea **estable**.
- Ver cómo cambia el costo de ordenar según la estructura de datos subyacente (vector vs lista).
- Incorporar la técnica de **Divide & Conquer** (dividir, resolver recursivamente y combinar).
- Implementar y analizar **merge sort** y **quick sort**.
- Aprender a usar el **teorema maestro** para resolver recurrencias de la forma `T(n) = a·T(n/b) + f(n)`.
- Repasar búsqueda lineal y binaria: precondiciones, invariantes y complejidad.



# Ordenamiento

Ordenar es uno de los problemas más estudiados en algoritmos: dado un conjunto de elementos, se busca reordenarlos según un criterio (por ejemplo, de menor a mayor).

En esta clase vamos a trabajar con `std::vector<T>`, que en C++ nos da acceso aleatorio a sus elementos en O(1), algo clave para entender el costo de cada algoritmo.

## Algoritmos elementales de ordenamiento

Estos algoritmos se llaman "elementales" porque son simples de programar, pero **no son eficientes** para conjuntos grandes de datos: todos tienen peor caso O(n²).

### Bubble sort

La idea es recorrer el vector varias veces, comparando elementos adyacentes y "burbujeando" el más grande hacia el final en cada pasada.

```cpp
template <typename T>
void bubbleSort(std::vector<T>& v) {
    size_t n = v.size();
    for (size_t i = 0; i < n; i++) {
        bool huboSwap = false;
        for (size_t j = 0; j + 1 < n - i; j++) {
            if (v[j] > v[j + 1]) {
                std::swap(v[j], v[j + 1]);
                huboSwap = true;
            }
        }
        if (!huboSwap) break;  // ya está ordenado, corto antes
    }
}
```

> El corte con `huboSwap` es lo que hace que el **mejor caso** de bubble sort sea O(n): si el vector ya está ordenado, una sola pasada alcanza para darse cuenta.

### Insertion sort

La idea es construir el vector ordenado de a un elemento por vez: en cada paso, se toma el siguiente elemento y se lo "inserta" en la posición correcta dentro de la parte ya ordenada.

```cpp
template <typename T>
void insertionSort(std::vector<T>& v) {
    size_t n = v.size();
    for (size_t i = 1; i < n; i++) {
        T actual = v[i];
        size_t j = i;
        while (j > 0 && v[j - 1] > actual) {
            v[j] = v[j - 1];
            j--;
        }
        v[j] = actual;
    }
}
```

> Insertion sort es muy eficiente cuando el vector está **casi ordenado**: en ese caso el `while` interno casi no itera y el costo se acerca a O(n).

### Selection sort

La idea es, en cada paso, buscar el **mínimo** de la parte no ordenada y colocarlo en su posición final mediante un único intercambio.

```cpp
template <typename T>
void selectionSort(std::vector<T>& v) {
    size_t n = v.size();
    for (size_t i = 0; i < n; i++) {
        size_t indiceMinimo = i;
        for (size_t j = i + 1; j < n; j++) {
            if (v[j] < v[indiceMinimo]) {
                indiceMinimo = j;
            }
        }
        std::swap(v[i], v[indiceMinimo]);
    }
}
```

> Pregunta para pensar: ¿por qué selection sort **siempre** hace O(n) comparaciones en cada pasada, incluso si el vector ya está ordenado? ¿Qué diferencia tiene esto respecto de bubble sort?

## Complejidad de los algoritmos elementales

| Algoritmo       | Mejor caso | Caso promedio | Peor caso | ¿Estable? |
| --------------- | ---------- | -------------- | --------- | --------- |
| Bubble sort     | O(n)       | O(n²)          | O(n²)     | Sí        |
| Insertion sort  | O(n)       | O(n²)          | O(n²)     | Sí        |
| Selection sort  | O(n²)      | O(n²)          | O(n²)     | No\*      |

\* Selection sort tal como está implementado arriba (con `std::swap`) **no es estable**, porque el intercambio puede alterar el orden relativo de elementos iguales. Existe una variante que sí es estable, pero requiere desplazar elementos en vez de intercambiar.

## Estabilidad en algoritmos de ordenamiento

> Un algoritmo de ordenamiento es **estable** si, ante dos elementos con la misma clave de comparación, preserva su orden relativo original.

Esto importa mucho cuando ordenamos **structs** por un campo, pero queremos conservar el orden de otro campo. Por ejemplo, si tenemos una lista de alumnos ordenados alfabéticamente y queremos reordenarla por nota, un algoritmo estable garantiza que, entre dos alumnos con la misma nota, se mantenga el orden alfabético previo.

```cpp
struct Alumno {
    std::string nombre;
    int nota;
};
```

> Pregunta para pensar: si tuvieras que ordenar una lista de pedidos por prioridad, pero conservar el orden de llegada entre pedidos de igual prioridad... ¿qué algoritmo elegirías?

## Costo según la estructura de datos

No es lo mismo ordenar un `std::vector` que una lista enlazada. La diferencia clave es el tipo de **acceso**:

| Estructura        | Acceso a la posición `i` | Insertar/borrar en el medio |
| ------------------ | ------------------------- | ---------------------------- |
| `std::vector`       | O(1) (acceso aleatorio)   | O(n) (hay que correr elementos) |
| Lista enlazada      | O(n) (acceso secuencial)  | O(1) si ya tenemos el puntero  |

Esto tiene consecuencias directas sobre los algoritmos que vimos:

- **Selection sort** necesita buscar el mínimo recorriendo la estructura: esa búsqueda es O(n) tanto en vector como en lista, así que el algoritmo no se ve muy afectado.
- **Insertion sort** en un vector necesita **correr** elementos para hacer lugar (O(n) en el peor caso), pero en una lista enlazada la inserción en sí es O(1) *una vez que encontramos la posición*; el costo entonces pasa a estar en la **búsqueda secuencial** de esa posición, que también es O(n).
- **Bubble sort** compara y swapea elementos adyacentes: funciona razonablemente bien en ambas estructuras, porque solo necesita acceso secuencial.

> En la práctica, para listas enlazadas se prefiere **merge sort** (que vamos a ver a continuación), porque no necesita acceso aleatorio: solo recorre la lista secuencialmente para dividirla y combinarla.



# Divide y Conquer

## La idea general

**Divide & Conquer** ("dividir para conquistar") es una técnica de diseño de algoritmos que consiste en tres pasos:

1. **Dividir** el problema en subproblemas más chicos (típicamente, del mismo tipo que el original).
2. **Conquistar** (resolver) cada subproblema recursivamente. El **caso base** de la recursión es un subproblema lo suficientemente chico como para resolverse directamente.
3. **Combinar** las soluciones de los subproblemas para construir la solución del problema original.

Esta estructura se refleja directamente en una **recurrencia**:

```
T(n) = a·T(n/b) + f(n)
```

donde:
- `a` = cantidad de subproblemas en los que se divide el problema.
- `n/b` = tamaño de cada subproblema (se divide el tamaño original por `b`).
- `f(n)` = costo de dividir el problema y combinar las soluciones (sin contar las llamadas recursivas).

> Esta misma recurrencia la vamos a usar más abajo con el **teorema maestro** para calcular la complejidad de merge sort y de la búsqueda binaria.

## Merge sort

Merge sort aplica Divide & Conquer directamente:

1. **Dividir**: partir el vector en dos mitades.
2. **Conquistar**: ordenar recursivamente cada mitad.
3. **Combinar**: mezclar (`merge`) las dos mitades ya ordenadas en un único vector ordenado.

```cpp
template <typename T>
void mergeSort(std::vector<T>& v, int izq, int der) {
    if (izq >= der) return;  // caso base: 0 o 1 elemento

    int medio = izq + (der - izq) / 2;

    mergeSort(v, izq, medio);       // ordeno mitad izquierda
    mergeSort(v, medio + 1, der);   // ordeno mitad derecha
    merge(v, izq, medio, der);      // combino ambas mitades
}
```

### La función merge

`merge` recibe dos sub-rangos **ya ordenados** (`[izq, medio]` y `[medio+1, der]`) y los combina en un único rango ordenado, usando un vector auxiliar.

```cpp
template <typename T>
void merge(std::vector<T>& v, int izq, int medio, int der) {
    std::vector<T> aux;
    aux.reserve(der - izq + 1);

    int i = izq;       // puntero a la mitad izquierda
    int j = medio + 1;  // puntero a la mitad derecha

    while (i <= medio && j <= der) {
        if (v[i] <= v[j]) {
            aux.push_back(v[i]);
            i++;
        } else {
            aux.push_back(v[j]);
            j++;
        }
    }

    while (i <= medio) aux.push_back(v[i++]);
    while (j <= der)   aux.push_back(v[j++]);

    for (int k = 0; k < (int)aux.size(); k++) {
        v[izq + k] = aux[k];
    }
}
```

> El uso de `<=` (y no `<`) en la comparación `v[i] <= v[j]` es lo que hace que merge sort sea **estable**: ante un empate, siempre se prioriza el elemento de la mitad izquierda, que apareció antes en el vector original.

`merge` cuesta O(n) porque recorre una sola vez ambos sub-rangos. Por lo tanto la recurrencia de merge sort es:

```
T(n) = 2·T(n/2) + O(n)
```

## Quick sort

Quick sort también es Divide & Conquer, pero divide el trabajo de otra manera:

1. **Dividir**: elegir un **pivot** y particionar el vector de forma que todos los elementos menores queden a su izquierda y todos los mayores a su derecha.
2. **Conquistar**: ordenar recursivamente la parte izquierda y la parte derecha del pivot.
3. **Combinar**: ¡no hace falta combinar nada! Una vez ordenadas ambas partes, el vector completo ya está ordenado.

```cpp
template <typename T>
void quickSort(std::vector<T>& v, int izq, int der) {
    if (izq >= der) return;  // caso base: 0 o 1 elemento

    int p = partition(v, izq, der);

    quickSort(v, izq, p - 1);
    quickSort(v, p + 1, der);
}
```

### Partición (partition)

Usamos el esquema de **Lomuto**, que elige como pivot el último elemento del rango:

```cpp
template <typename T>
int partition(std::vector<T>& v, int izq, int der) {
    T pivot = v[der];
    int i = izq - 1;  // límite de la zona "menor al pivot"

    for (int j = izq; j < der; j++) {
        if (v[j] < pivot) {
            i++;
            std::swap(v[i], v[j]);
        }
    }

    std::swap(v[i + 1], v[der]);
    return i + 1;  // posición final del pivot
}
```

> Pregunta para pensar: ¿por qué quick sort **no es estable** en general? Pensá qué pasa con dos elementos iguales cuando uno de ellos termina siendo swapeado con el pivot.

La complejidad de quick sort depende de qué tan "parejo" sea el particionamiento:

| Caso              | Partición típica            | Recurrencia               | Complejidad |
| ------------------ | ---------------------------- | -------------------------- | ------------ |
| Mejor/promedio     | Las dos partes son de tamaño similar | T(n) = 2·T(n/2) + O(n)  | O(n log n)   |
| Peor caso           | Una parte queda vacía (pivot siempre mínimo o máximo, ej. vector ya ordenado) | T(n) = T(n-1) + O(n) | O(n²)        |

> Elegir bien el pivot (por ejemplo, con la mediana de tres elementos, o un pivot aleatorio) es clave para evitar el peor caso en la práctica.

## El teorema maestro

El teorema maestro es una herramienta que nos permite resolver recurrencias de Divide & Conquer sin tener que desarrollar el árbol de recursión a mano cada vez.

### Enunciado general

Dada una recurrencia de la forma:

```
T(n) = a·T(n/b) + f(n)      con a ≥ 1, b > 1
```

se compara `f(n)` contra `n^(log_b a)` (el costo "puro" de las llamadas recursivas, sin combinar).

### Los tres casos

| Caso | Condición                                                          | Resultado                          |
| ---- | ------------------------------------------------------------------- | ------------------------------------ |
| 1    | `f(n) = O(n^(log_b a - ε))` para algún ε > 0 (f(n) crece **más lento**) | `T(n) = Θ(n^(log_b a))`             |
| 2    | `f(n) = Θ(n^(log_b a))` (f(n) crece **igual**)                       | `T(n) = Θ(n^(log_b a) · log n)`     |
| 3    | `f(n) = Ω(n^(log_b a + ε))` para algún ε > 0 **y** se cumple la condición de regularidad (f(n) crece **más rápido**) | `T(n) = Θ(f(n))`                    |

> Intuición: el teorema maestro compara "cuánto trabajo se hace repartiendo/combinando en cada nivel" (`f(n)`) contra "cuántas hojas tiene el árbol de recursión" (`n^(log_b a)`). Gana (domina la complejidad) el que sea asintóticamente mayor; si empatan, se agrega un factor `log n`.

### Ejemplos aplicados

**Merge sort:** `T(n) = 2·T(n/2) + O(n)` → `a = 2`, `b = 2`, `f(n) = n`.
- `n^(log_b a) = n^(log_2 2) = n^1 = n`.
- `f(n) = n = Θ(n^1)` → **Caso 2**.
- `T(n) = Θ(n log n)`.

**Búsqueda binaria:** `T(n) = T(n/2) + O(1)` → `a = 1`, `b = 2`, `f(n) = 1`.
- `n^(log_b a) = n^(log_2 1) = n^0 = 1`.
- `f(n) = 1 = Θ(n^0)` → **Caso 2**.
- `T(n) = Θ(log n)`.

**Un ejemplo de Caso 1:** `T(n) = 4·T(n/2) + n` → `a = 4`, `b = 2`, `f(n) = n`.
- `n^(log_b a) = n^(log_2 4) = n²`.
- `f(n) = n` crece más lento que `n²` → **Caso 1**.
- `T(n) = Θ(n²)`.

**Un ejemplo de Caso 3:** `T(n) = 2·T(n/2) + n²` → `a = 2`, `b = 2`, `f(n) = n²`.
- `n^(log_b a) = n`.
- `f(n) = n²` crece más rápido que `n` → **Caso 3**.
- `T(n) = Θ(n²)`.

> Pregunta para pensar: `T(n) = 2·T(n/2) + n log n` no encaja exactamente en ninguno de los tres casos clásicos (es un "caso límite" del Caso 2 extendido). ¿Qué resultado te parece razonable? *Ayuda: pensá el árbol de recursión nivel por nivel.*

> No todas las recurrencias son "del tipo Divide & Conquer". Por ejemplo, `T(n) = T(n-1) + n` (recursión que reduce de a 1 el tamaño) **no** se puede resolver con el teorema maestro porque no tiene la forma `a·T(n/b) + f(n)`. Hay que resolverla por sustitución o por el método del árbol de recursión: da `T(n) = O(n²)`.



# Búsqueda

## Búsqueda lineal

Recorre el vector elemento por elemento hasta encontrar (o no) lo buscado. No requiere ninguna precondición sobre el orden de los datos.

```cpp
template <typename T>
int busquedaLineal(const std::vector<T>& v, T buscado) {
    for (int i = 0; i < (int)v.size(); i++) {
        if (v[i] == buscado) return i;
    }
    return -1;  // no encontrado
}
```

## Búsqueda binaria

Aprovecha que el vector está **ordenado** para descartar, en cada paso, la mitad de los elementos que quedan por revisar.

```cpp
template <typename T>
int busquedaBinaria(const std::vector<T>& v, T buscado) {
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

    return -1;  // no encontrado
}
```

También se puede implementar de forma recursiva, ya que en definición es un Divide & Conquer donde no hace falta combinar (solo se sigue por una de las dos mitades):

```cpp
template <typename T>
int busquedaBinariaRec(const std::vector<T>& v, T buscado, int izq, int der) {
    if (izq > der) return -1;  // caso base: no encontrado

    int medio = izq + (der - izq) / 2;

    if (v[medio] == buscado) return medio;
    if (v[medio] < buscado) return busquedaBinariaRec(v, buscado, medio + 1, der);
    return busquedaBinariaRec(v, buscado, izq, medio - 1);
}
```

## Precondición e invariante

> **Precondición de búsqueda binaria:** el vector debe estar **ordenado**. Si no lo está, el algoritmo puede devolver un resultado incorrecto sin ningún aviso (no hay forma de detectarlo desde adentro del algoritmo).

El **invariante** que mantiene el ciclo `while` es: *si `buscado` está en el vector, entonces está en el rango `[izq, der]`*. En cada iteración se reduce ese rango a la mitad, sin perder nunca esa garantía.

> Pregunta para pensar: ¿por qué usamos `izq + (der - izq) / 2` en vez de `(izq + der) / 2` para calcular el medio? *Ayuda: pensá qué pasa con el desborde (overflow) de enteros cuando `izq` y `der` son muy grandes.*

## Complejidad de las búsquedas

| Algoritmo         | Precondición      | Mejor caso | Peor caso  |
| ------------------ | ------------------- | ---------- | ---------- |
| Búsqueda lineal    | Ninguna            | O(1)       | O(n)       |
| Búsqueda binaria   | Vector ordenado     | O(1)       | O(log n)   |

## Cuándo conviene cada una

- Si los datos **no están ordenados** y solo se va a buscar una vez, conviene la **búsqueda lineal**: ordenar solo para hacer una búsqueda no vale la pena (ordenar cuesta al menos O(n log n)).
- Si se van a hacer **muchas búsquedas** sobre el mismo conjunto de datos, puede convenir **ordenar una vez** (O(n log n)) y después buscar con **búsqueda binaria** (O(log n) cada una).
- Búsqueda binaria **requiere acceso aleatorio** a los elementos (como el que da `std::vector`). Sobre una lista enlazada, aunque esté ordenada, no se puede aprovechar la mitad del rango sin recorrerla secuencialmente, así que binaria pierde su ventaja.

> Pregunta para pensar: si tuviéramos una lista enlazada ordenada y quisiéramos buscar eficientemente muchas veces, ¿qué estructura de datos elegirías en su lugar? *Este es exactamente el problema que motiva a los árboles de búsqueda binaria, que vemos en el próximo tutorial.*
