Tut 07 – Rosetree y Heaps
===

- [Tut 07 – Rosetree y Heaps](#tut-07--rosetree-y-heaps)
- [Objetivos de la clase](#objetivos-de-la-clase)
- [Rosetree (árbol n-ario)](#rosetree-árbol-n-ario)
  - [¿Qué es un rosetree?](#qué-es-un-rosetree)
  - [Representación en C++](#representación-en-c)
  - [Recorridos y recursión](#recorridos-y-recursión)
  - [Ejemplos donde aparece naturalmente](#ejemplos-donde-aparece-naturalmente)
- [Heaps](#heaps)
  - [¿Qué es un heap?](#qué-es-un-heap)
  - [Representación sobre un arreglo](#representación-sobre-un-arreglo)
  - [Primitivas](#primitivas)
    - [insert (sift-up)](#insert-sift-up)
    - [extractMin / extractMax (sift-down)](#extractmin--extractmax-sift-down)
    - [heapify / buildHeap](#heapify--buildheap)
  - [Heapsort](#heapsort)
  - [El heap como cola de prioridad](#el-heap-como-cola-de-prioridad)
  - [Repaso de complejidades](#repaso-de-complejidades)
  - [La STL: `std::priority_queue`](#la-stl-stdpriority_queue)



# Objetivos de la clase
- Entender qué es un rosetree (árbol n-ario) y cómo recorrerlo recursivamente.
- Reconocer situaciones de la vida real que se modelan naturalmente con un rosetree.
- Comprender la definición de heap (min-heap y max-heap) como árbol binario casi completo.
- Implementar un heap "a mano" sobre un `std::vector`, con `insert`, `extractMin`/`extractMax` y `buildHeap`.
- Entender heapsort y el uso del heap como cola de prioridad.
- Analizar la complejidad de cada primitiva del heap.



# Rosetree (árbol n-ario)

## ¿Qué es un rosetree?

Hasta ahora trabajamos sobre todo con árboles **binarios**, donde cada nodo tiene a lo sumo dos hijos. Un **rosetree** (también llamado árbol n-ario o *árbol general*) generaliza esa idea: cada nodo puede tener **cualquier cantidad de hijos**, desde cero hasta n.

> Un rosetree no tiene "hijo izquierdo" ni "hijo derecho": tiene una **colección ordenada de hijos**.

Es la estructura que usamos naturalmente cuando pensamos en jerarquías: una carpeta que contiene archivos y otras carpetas, un organigrama de una empresa, el árbol genealógico de un torneo, o el árbol de decisiones de un juego.

## Representación en C++

En Python uno podría representar un nodo con una lista de hijos sin pensarlo demasiado. En C++, como es un lenguaje de tipado estático, necesitamos definir explícitamente la estructura. Usamos un `struct` con un `std::vector` de punteros a los hijos:

```cpp
template <typename T>
struct Rosetree {
    T valor;
    std::vector<Rosetree<T>*> hijos;
};
```

> ¿Por qué `std::vector<Rosetree<T>*>` y no `std::vector<Rosetree<T>>`? Porque el tipo `Rosetree<T>` se está definiendo a sí mismo (es un tipo recursivo). El compilador necesita conocer el tamaño exacto de la estructura, y un vector de punteros tiene tamaño fijo (son direcciones de memoria), mientras que un vector de "Rosetree por valor" tendría tamaño indefinido.

Crear un nodo hoja y agregarle hijos es directo:

```cpp
Rosetree<std::string>* raiz = new Rosetree<std::string>{"Documentos", {}};
Rosetree<std::string>* hijo1 = new Rosetree<std::string>{"Fotos", {}};
Rosetree<std::string>* hijo2 = new Rosetree<std::string>{"Tesis.pdf", {}};

raiz->hijos.push_back(hijo1);
raiz->hijos.push_back(hijo2);
```

## Recorridos y recursión

Un rosetree se recorre de forma muy parecida a un árbol binario, solo que en vez de "visitar izquierda y derecha" hay que **recorrer el vector de hijos**. La receta general de cualquier función recursiva sobre un rosetree es:

1. **Caso base**: el nodo es `nullptr` (árbol vacío) o no tiene hijos (es una hoja).
2. **Caso recursivo**: procesar el nodo actual y combinar el resultado de aplicar la misma función a cada uno de sus hijos, recorriendo el `std::vector<Rosetree<T>*>` con un `for`.

Por ejemplo, contar la cantidad de nodos de un rosetree:

```cpp
int contarNodos(Rosetree<int>* nodo) {
    if (nodo == nullptr) {
        return 0;
    }
    int total = 1; // me cuento a mí mismo
    for (Rosetree<int>* hijo : nodo->hijos) {
        total += contarNodos(hijo);
    }
    return total;
}
```

Calcular la altura es análogo, pero en vez de sumar hay que quedarse con el **máximo** entre los hijos:

```cpp
int altura(Rosetree<int>* nodo) {
    if (nodo == nullptr) {
        return 0;
    }
    if (nodo->hijos.empty()) {
        return 1; // una hoja tiene altura 1
    }
    int alturaMax = 0;
    for (Rosetree<int>* hijo : nodo->hijos) {
        alturaMax = std::max(alturaMax, altura(hijo));
    }
    return 1 + alturaMax;
}
```

> Pregunta para pensar: en un árbol binario la recursión hace dos llamados (izquierda y derecha). En un rosetree, ¿cuántos llamados recursivos se hacen? ¿Depende del nodo?

> Pregunta para pensar: ¿cómo cambiaría `contarNodos` si quisiéramos contar solamente las **hojas** del árbol?

## Ejemplos donde aparece naturalmente

El rosetree no es una curiosidad teórica: aparece todo el tiempo en problemas reales.

| Ejemplo | Nodo | Hijos |
|---|---|---|
| Sistema de archivos | Carpeta o archivo | Subcarpetas y archivos que contiene |
| Organigrama de una empresa | Empleado | Sus reportes directos |
| Árbol de decisión de un juego | Estado del juego | Cada jugada posible desde ese estado |
| Árbol sintáctico de una expresión | Operador o subexpresión | Sus operandos |
| Comentarios anidados (foro, redes sociales) | Comentario | Respuestas a ese comentario |

> Tip: cuando en un enunciado aparece la palabra "jerarquía", "carpeta", "subordinados" o "anidado", es una buena pista de que conviene modelar el problema con un rosetree en vez de forzarlo a un árbol binario.



# Heaps

## ¿Qué es un heap?

Un **heap** es una estructura de datos pensada para responder eficientemente una pregunta muy puntual: *¿cuál es el elemento de mínima (o máxima) prioridad que tengo guardado?*

Se implementa como un **árbol binario casi completo**: todos los niveles están completamente llenos, excepto posiblemente el último, que se llena **de izquierda a derecha**. Esta forma tan regular es justamente lo que permite representarlo de manera compacta con un simple `std::vector`, sin necesidad de punteros.

Además de la forma, un heap cumple la **propiedad de heap**:

- **Min-heap**: el valor de cada nodo es **menor o igual** que el de sus hijos. La raíz es siempre el mínimo.
- **Max-heap**: el valor de cada nodo es **mayor o igual** que el de sus hijos. La raíz es siempre el máximo.

> Un heap **no está totalmente ordenado**: solo garantiza la relación entre un nodo y sus hijos directos. Dos elementos que no tienen relación de ancestro-descendiente pueden estar en cualquier orden entre sí.

> Pregunta para pensar: si un min-heap tiene la propiedad de que un padre es menor que sus hijos, ¿dónde se encuentra el elemento máximo del heap? ¿Se puede encontrar en O(1)?

## Representación sobre un arreglo

Como el heap es un árbol *casi completo*, podemos numerar sus nodos por niveles (0, 1, 2, ...) y guardarlos en un `std::vector` en ese mismo orden, sin usar punteros. Indexando desde 0, las relaciones padre-hijo quedan:

| Relación | Fórmula (índice `i`) |
|---|---|
| Padre de `i` | `(i - 1) / 2` |
| Hijo izquierdo de `i` | `2 * i + 1` |
| Hijo derecho de `i` | `2 * i + 2` |

```cpp
class MinHeap {
private:
    std::vector<int> datos;

    int padre(int i)     { return (i - 1) / 2; }
    int hijoIzq(int i)   { return 2 * i + 1; }
    int hijoDer(int i)   { return 2 * i + 2; }

    void siftUp(int i);
    void siftDown(int i);

public:
    bool empty() const { return datos.empty(); }
    int size() const { return static_cast<int>(datos.size()); }

    int getMin() const { return datos[0]; }
    void insert(int valor);
    int extractMin();
};
```

> Tip: no hace falta guardar punteros a "padre" o "hijos": toda la estructura del árbol está implícita en la posición dentro del vector. Por eso el heap es tan compacto en memoria.

## Primitivas

### insert (sift-up)

Para insertar un nuevo valor:

1. Se agrega al **final** del vector (siguiente posición libre del árbol casi completo). O(1) amortizado gracias a `push_back`.
2. Puede violar la propiedad de heap con respecto a su padre, así que "sube" intercambiándose con él mientras sea menor (en un min-heap). A esto se lo llama **sift-up** o **heapUp**.

```cpp
void MinHeap::siftUp(int i) {
    while (i > 0 && datos[padre(i)] > datos[i]) {
        std::swap(datos[padre(i)], datos[i]);
        i = padre(i);
    }
}

void MinHeap::insert(int valor) {
    datos.push_back(valor);
    siftUp(size() - 1);
}
```

Como la altura del árbol es O(log n), el elemento sube a lo sumo O(log n) niveles: **insert es O(log n)**.

### extractMin / extractMax (sift-down)

Para extraer el mínimo (la raíz):

1. Se guarda el valor de la raíz para devolverlo al final.
2. Se mueve el **último elemento** del vector a la posición de la raíz y se achica el vector en uno.
3. Ese elemento probablemente viole la propiedad de heap, así que "baja" intercambiándose con el **menor de sus dos hijos**, mientras sea mayor que alguno de ellos. A esto se lo llama **sift-down** o **heapDown**.

```cpp
void MinHeap::siftDown(int i) {
    int n = size();
    while (true) {
        int menor = i;
        int izq = hijoIzq(i);
        int der = hijoDer(i);

        if (izq < n && datos[izq] < datos[menor]) menor = izq;
        if (der < n && datos[der] < datos[menor]) menor = der;

        if (menor == i) break; // ya cumple la propiedad de heap

        std::swap(datos[i], datos[menor]);
        i = menor;
    }
}

int MinHeap::extractMin() {
    int minimo = datos[0];
    datos[0] = datos.back();
    datos.pop_back();
    if (!datos.empty()) {
        siftDown(0);
    }
    return minimo;
}
```

Al igual que el insert, el elemento baja a lo sumo la altura del árbol: **extractMin es O(log n)**.

> Pregunta para pensar: en `siftDown`, ¿por qué hay que comparar con el **menor** de los dos hijos y no alcanza con comparar con cualquiera de los dos?

### heapify / buildHeap

Si ya tenemos un `std::vector<int>` con `n` elementos desordenados y queremos convertirlo en un heap válido, hay varias estrategias posibles:

| Estrategia | Complejidad |
|---|---|
| Insertar los `n` elementos uno por uno con `insert` | O(n log n) |
| Hacer `siftUp` desde la posición 0 hasta la n-1 | O(n log n) |
| Hacer `siftDown` desde la posición 0 hasta la n-1 | ❌ No funciona: los subárboles de abajo todavía no son heaps válidos |
| Hacer `siftDown` desde el **último nodo con hijos** hasta la raíz | **O(n), óptimo** |

La versión óptima aprovecha que las hojas ya son heaps válidos por definición (no tienen hijos), así que alcanza con arreglar los nodos internos, empezando por los de más abajo:

```cpp
void buildHeap(std::vector<int>& datos) {
    int n = static_cast<int>(datos.size());
    int ultimoNoHoja = n / 2 - 1;

    for (int i = ultimoNoHoja; i >= 0; i--) {
        siftDown(datos, i, n);
    }
}
```

> ¿Por qué esto es O(n) y no O(n log n)? Porque la mayoría de los nodos están en los niveles inferiores del árbol, y esos nodos hacen `siftDown` de muy pocos niveles (las hojas, de hecho, no hacen ninguno). Solo unos pocos nodos, cerca de la raíz, bajan hasta O(log n) niveles. Al sumar el trabajo de todos los niveles, la serie converge a O(n).

## Heapsort

Una vez que sabemos construir un heap en O(n) y extraer el máximo en O(log n), **heapsort** sale casi gratis:

1. Construir un **max-heap** a partir del arreglo. O(n).
2. Repetir n veces: intercambiar la raíz (el máximo) con el último elemento del heap "activo", achicar el heap en uno, y hacer `siftDown` desde la raíz. O(log n) cada vez.

```cpp
void siftDownMax(std::vector<int>& v, int i, int n) {
    while (true) {
        int mayor = i;
        int izq = 2 * i + 1;
        int der = 2 * i + 2;

        if (izq < n && v[izq] > v[mayor]) mayor = izq;
        if (der < n && v[der] > v[mayor]) mayor = der;

        if (mayor == i) break;

        std::swap(v[i], v[mayor]);
        i = mayor;
    }
}

void heapsort(std::vector<int>& v) {
    int n = static_cast<int>(v.size());

    // 1. buildHeap (max-heap), O(n)
    for (int i = n / 2 - 1; i >= 0; i--) {
        siftDownMax(v, i, n);
    }

    // 2. extraer el máximo n veces
    for (int fin = n - 1; fin > 0; fin--) {
        std::swap(v[0], v[fin]); // el máximo va a su posición final
        siftDownMax(v, 0, fin);  // el heap activo ahora tiene tamaño fin
    }
}
```

La complejidad total es **O(n log n)**, con la ventaja de que ordena **in-place** (usa O(1) memoria extra), a diferencia de mergesort.

> Pregunta para pensar: ¿heapsort es un algoritmo de ordenamiento estable? Es decir, ¿dos elementos iguales conservan su orden relativo original?

## El heap como cola de prioridad

Una **cola de prioridad** (*priority queue*) es un TAD (tipo abstracto de datos) que permite:

- agregar elementos con una prioridad asociada,
- extraer siempre el elemento de mayor (o menor) prioridad.

El heap es la implementación clásica de una cola de prioridad, porque ofrece exactamente esas dos operaciones en O(log n). Se usa, entre otras cosas, en:

- **Algoritmos de grafos**: Dijkstra, Prim, A*.
- **Simulaciones de eventos discretos**: procesar siempre el próximo evento en el tiempo.
- **Sistemas operativos**: planificadores que eligen el próximo proceso según su prioridad.
- **Compresión de Huffman**: combinar siempre los dos nodos de menor frecuencia.

## Repaso de complejidades

| Primitiva | Complejidad |
|---|---|
| `build` (heap vacío) | O(1) |
| `getMin` / `getMax` | O(1) |
| `insert` | O(log n) |
| `extractMin` / `extractMax` | O(log n) |
| `buildHeap` (heapify) | O(n) |
| `heapsort` | O(n log n) |

## La STL: `std::priority_queue`

C++ ya trae un heap implementado en la librería estándar: `std::priority_queue`. Por defecto es un **max-heap**:

```cpp
#include <queue>

std::priority_queue<int> cola;
cola.push(5);
cola.push(1);
cola.push(9);

std::cout << cola.top() << "\n"; // 9
cola.pop();
std::cout << cola.top() << "\n"; // 5
```

Para convertirlo en un **min-heap**, se le indica un comparador `std::greater<int>`:

```cpp
std::priority_queue<int, std::vector<int>, std::greater<int>> colaMin;
```

> Tip: en los ejercicios y parciales suele pedirse implementar el heap "a mano" para entender cómo funciona por dentro, pero en código de uso general siempre conviene usar `std::priority_queue`.
