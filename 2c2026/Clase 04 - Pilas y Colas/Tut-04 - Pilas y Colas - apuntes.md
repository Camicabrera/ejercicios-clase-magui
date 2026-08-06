Tutorial 4 – Pilas y Colas
===

> **Ingeniería en Inteligencia Artificial** — **Algoritmos y Estructura de Datos**  
> **2C 2026** · Docente: **Magali Marijuan**

- [Tutorial 4 – Pilas y Colas](#tutorial-4--pilas-y-colas)
- [Objetivos de la clase](#objetivos-de-la-clase)
- [Pila (Stack): LIFO](#pila-stack-lifo)
  - [Operaciones de la pila](#operaciones-de-la-pila)
  - [Implementación de la pila sobre arreglo](#implementación-de-la-pila-sobre-arreglo)
  - [Implementación de la pila sobre lista enlazada](#implementación-de-la-pila-sobre-lista-enlazada)
  - [Repaso de complejidades (pila)](#repaso-de-complejidades-pila)
- [Cola (Queue): FIFO](#cola-queue-fifo)
  - [Operaciones de la cola](#operaciones-de-la-cola)
  - [Implementación de la cola sobre arreglo (buffer circular)](#implementación-de-la-cola-sobre-arreglo-buffer-circular)
  - [Implementación de la cola sobre lista enlazada](#implementación-de-la-cola-sobre-lista-enlazada)
  - [Repaso de complejidades (cola)](#repaso-de-complejidades-cola)
- [Arreglo vs lista enlazada: trade-offs](#arreglo-vs-lista-enlazada-trade-offs)
- [Casos de uso](#casos-de-uso)
  - [Balanceo y evaluación de expresiones](#balanceo-y-evaluación-de-expresiones)
  - [Deshacer y rehacer (undo/redo)](#deshacer-y-rehacer-undoredo)
  - [Colas de tareas](#colas-de-tareas)
  - [Adelanto: BFS usa cola, DFS usa pila](#adelanto-bfs-usa-cola-dfs-usa-pila)
- [std::stack y std::queue](#stdstack-y-stdqueue)
- [Resumen general de complejidades](#resumen-general-de-complejidades)



# Objetivos de la clase
- Entender las interfaces de **pila** (LIFO) y **cola** (FIFO) como TADs (tipos abstractos de datos).
- Implementar ambas estructuras sobre un arreglo (con redimensionamiento y buffer circular) y sobre una lista enlazada.
- Comparar los *trade-offs* de cada implementación.
- Reconocer casos de uso típicos: balanceo de expresiones, deshacer/rehacer, colas de tareas.
- Adelantar que estas estructuras son la base de los recorridos de grafos: BFS usa cola, DFS usa pila.



# Pila (Stack): LIFO

Una pila es una estructura donde el **último elemento en entrar es el primero en salir** (*Last In, First Out*). Pensala como una pila de platos: solo podés sacar (o agregar) el plato de arriba.

## Operaciones de la pila

| Operación | Descripción |
|-----------|-------------|
| `push(x)` | Agrega `x` en el tope de la pila |
| `pop()`   | Elimina y devuelve el elemento del tope |
| `top()`   | Devuelve el elemento del tope sin eliminarlo |
| `empty()` | Indica si la pila está vacía |

> **Pregunta para pensar:** ¿por qué una pila **no** tiene una operación para acceder al elemento del medio en O(1)? ¿Tiene sentido que la tuviera?

## Implementación de la pila sobre arreglo

Guardamos los elementos en un arreglo dinámico y un índice `tope` que indica la próxima posición libre. Cuando el arreglo se llena, pedimos uno más grande (típicamente el doble) y copiamos los elementos, igual que hace `std::vector` internamente.

```cpp
template <typename T>
class PilaArreglo {
private:
    T* datos;
    size_t capacidad;
    size_t cantidad;   // también funciona como índice de la próxima posición libre

    void redimensionar() {
        capacidad *= 2;
        T* nuevoArreglo = new T[capacidad];
        for (size_t i = 0; i < cantidad; i++) {
            nuevoArreglo[i] = datos[i];
        }
        delete[] datos;
        datos = nuevoArreglo;
    }

public:
    PilaArreglo() : datos(new T[1]), capacidad(1), cantidad(0) {}
    ~PilaArreglo() { delete[] datos; }

    void push(const T& valor) {
        if (cantidad == capacidad) {
            redimensionar();
        }
        datos[cantidad] = valor;
        cantidad++;
    }

    T pop() {
        // precondición: !empty()
        cantidad--;
        return datos[cantidad];
    }

    const T& top() const {
        // precondición: !empty()
        return datos[cantidad - 1];
    }

    bool empty() const { return cantidad == 0; }
};
```

> **Pregunta para pensar:** `redimensionar()` es O(n), pero decimos que `push` es "O(1) amortizado". ¿Por qué? *Pista:* pensar cuántas veces se redimensiona en n operaciones de `push`, sumando el costo total y dividiendo por n.

## Implementación de la pila sobre lista enlazada

Usamos una lista simplemente enlazada donde `push` y `pop` operan siempre sobre el `primero`. No hace falta puntero a `ultimo`.

```cpp
template <typename T>
class PilaLista {
private:
    Nodo<T>* tope;
    size_t cantidad;

public:
    PilaLista() : tope(nullptr), cantidad(0) {}

    ~PilaLista() {
        while (!empty()) pop();
    }

    void push(const T& valor) {
        tope = new Nodo<T>(valor, tope);   // el nuevo nodo pasa a ser el primero
        cantidad++;
    }

    T pop() {
        // precondición: !empty()
        Nodo<T>* viejoTope = tope;
        T valor = viejoTope->dato;
        tope = tope->siguiente;
        delete viejoTope;
        cantidad--;
        return valor;
    }

    const T& top() const {
        // precondición: !empty()
        return tope->dato;
    }

    bool empty() const { return tope == nullptr; }
};
```

## Repaso de complejidades (pila)

| Operación | Sobre arreglo | Sobre lista enlazada |
|-----------|----------------|------------------------|
| `push`    | O(1) amortizado | O(1) |
| `pop`     | O(1)            | O(1) |
| `top`     | O(1)            | O(1) |
| `empty`   | O(1)            | O(1) |

> Todas las operaciones de la pila son O(1) (amortizado en el caso del arreglo) en **ambas** implementaciones. La elección entre una y otra depende más de la localidad de cache y el uso de memoria que de la complejidad temporal.



# Cola (Queue): FIFO

Una cola es una estructura donde el **primer elemento en entrar es el primero en salir** (*First In, First Out*). Es la fila del banco: quien llega primero, se atiende primero.

## Operaciones de la cola

| Operación    | Descripción |
|--------------|-------------|
| `enqueue(x)` | Agrega `x` al final de la cola |
| `dequeue()`  | Elimina y devuelve el elemento del frente |
| `front()`    | Devuelve el elemento del frente sin eliminarlo |
| `empty()`    | Indica si la cola está vacía |

## Implementación de la cola sobre arreglo (buffer circular)

Si implementáramos la cola sobre un arreglo "ingenuo" (agregando al final y sacando del inicio corriendo todos los elementos), `dequeue` sería O(n). La solución es un **buffer circular**: dos índices, `frente` y `finalUso`, que "dan la vuelta" con módulo cuando llegan al final del arreglo.

```cpp
template <typename T>
class ColaArreglo {
private:
    T* datos;
    size_t capacidad;
    size_t frente;     // índice del primer elemento
    size_t cantidad;    // cantidad de elementos actuales

    void redimensionar() {
        size_t nuevaCapacidad = capacidad * 2;
        T* nuevoArreglo = new T[nuevaCapacidad];
        for (size_t i = 0; i < cantidad; i++) {
            // "desenrollamos" el buffer circular en el nuevo arreglo, en orden
            nuevoArreglo[i] = datos[(frente + i) % capacidad];
        }
        delete[] datos;
        datos = nuevoArreglo;
        capacidad = nuevaCapacidad;
        frente = 0;
    }

public:
    ColaArreglo() : datos(new T[1]), capacidad(1), frente(0), cantidad(0) {}
    ~ColaArreglo() { delete[] datos; }

    void enqueue(const T& valor) {
        if (cantidad == capacidad) {
            redimensionar();
        }
        size_t posicionInsercion = (frente + cantidad) % capacidad;
        datos[posicionInsercion] = valor;
        cantidad++;
    }

    T dequeue() {
        // precondición: !empty()
        T valor = datos[frente];
        frente = (frente + 1) % capacidad;   // avanza "circularmente"
        cantidad--;
        return valor;
    }

    const T& front() const {
        // precondición: !empty()
        return datos[frente];
    }

    bool empty() const { return cantidad == 0; }
};
```

> **Pregunta para pensar:** ¿por qué usamos `(frente + i) % capacidad` en vez de simplemente `frente + i`? Dibujá un buffer de capacidad 4 donde `frente = 2` y `cantidad = 3` para visualizarlo.

## Implementación de la cola sobre lista enlazada

Con una lista simplemente enlazada que mantiene punteros a `primero` **y** `ultimo`, `enqueue` inserta al final y `dequeue` elimina del inicio — ambas O(1), sin necesidad de módulo ni redimensionamiento.

```cpp
template <typename T>
class ColaLista {
private:
    Nodo<T>* primero;
    Nodo<T>* ultimo;
    size_t cantidad;

public:
    ColaLista() : primero(nullptr), ultimo(nullptr), cantidad(0) {}

    ~ColaLista() {
        while (!empty()) dequeue();
    }

    void enqueue(const T& valor) {
        Nodo<T>* nuevo = new Nodo<T>(valor, nullptr);
        if (ultimo == nullptr) {
            primero = ultimo = nuevo;
        } else {
            ultimo->siguiente = nuevo;
            ultimo = nuevo;
        }
        cantidad++;
    }

    T dequeue() {
        // precondición: !empty()
        Nodo<T>* viejoPrimero = primero;
        T valor = viejoPrimero->dato;
        primero = primero->siguiente;
        if (primero == nullptr) {
            ultimo = nullptr;   // quedó vacía
        }
        delete viejoPrimero;
        cantidad--;
        return valor;
    }

    const T& front() const {
        // precondición: !empty()
        return primero->dato;
    }

    bool empty() const { return primero == nullptr; }
};
```

## Repaso de complejidades (cola)

| Operación   | Sobre arreglo (buffer circular) | Sobre lista enlazada |
|-------------|-----------------------------------|------------------------|
| `enqueue`   | O(1) amortizado                   | O(1) |
| `dequeue`   | O(1)                               | O(1) |
| `front`     | O(1)                               | O(1) |
| `empty`     | O(1)                               | O(1) |

> **Punto clave:** sin buffer circular (es decir, con un arreglo donde `dequeue` corre todos los elementos una posición), `dequeue` sería O(n). El buffer circular es lo que permite que ambos extremos operen en O(1) sobre un arreglo.



# Arreglo vs lista enlazada: trade-offs

| Aspecto | Arreglo (con buffer circular) | Lista enlazada |
|---------|----------------------------------|------------------|
| Localidad de cache | Buena (memoria contigua) | Mala (nodos dispersos en el heap) |
| Memoria por elemento | Sin overhead (salvo capacidad reservada de más) | 1 puntero extra por nodo |
| Costo de redimensionar | O(n) ocasional, O(1) amortizado | Nunca hace falta redimensionar |
| Complejidad en el peor caso de una operación puntual | O(n) (justo cuando redimensiona) | O(1) siempre |
| Simplicidad de implementación | Requiere manejar índices y módulo | Más directa (reenlazar punteros) |

> **Pregunta para pensar:** si estás implementando una cola para un sistema en tiempo real donde **no podés tolerar** que una sola operación tarde más de lo esperado (por ejemplo, un buffer de audio), ¿elegirías la versión de arreglo o la de lista enlazada? ¿Por qué importa acá la diferencia entre "O(1) amortizado" y "O(1) en el peor caso"?



# Casos de uso

## Balanceo y evaluación de expresiones

Las pilas son la herramienta natural para todo lo que tenga estructura de "anidamiento": verificar que los paréntesis/llaves/corchetes de una expresión estén balanceados, o evaluar una expresión matemática escrita en notación postfija (RPN). Vas a resolver estos dos casos en los ejercicios.

## Deshacer y rehacer (undo/redo)

El botón de "deshacer" de cualquier editor de texto se implementa con **dos pilas**: una de acciones para deshacer y otra de acciones para rehacer. Cada acción nueva se apila en la primera; al hacer "deshacer", se saca de la primera pila y se apila en la segunda (y viceversa para "rehacer"). Es un uso directo del comportamiento LIFO: lo último que hiciste es lo primero que se deshace.

## Colas de tareas

Las colas modelan naturalmente cualquier situación de "atención por orden de llegada": una cola de impresión, una cola de solicitudes HTTP a procesar, o los mensajes de un sistema de *jobs* en background. El comportamiento FIFO garantiza que nadie se "cuela".

## Adelanto: BFS usa cola, DFS usa pila

Cuando veamos recorridos de grafos, vamos a ver que:

- **BFS** (*Breadth-First Search*, recorrido en anchura) usa una **cola**: procesa los nodos en el orden en que los descubre, capa por capa.
- **DFS** (*Depth-First Search*, recorrido en profundidad) usa una **pila** (a veces implícita, vía recursión): profundiza todo lo posible por un camino antes de retroceder.

> **Pregunta para pensar:** la recursión también usa una pila (la *call stack*). ¿Por qué DFS se puede escribir tanto con recursión como con una pila explícita, mientras que BFS casi nunca se escribe de forma recursiva?



# std::stack y std::queue

La biblioteca estándar de C++ ya provee estas estructuras en `<stack>` y `<queue>`, con la misma interfaz que implementamos acá:

```cpp
#include <stack>
#include <queue>

std::stack<int> pila;
pila.push(1);
pila.push(2);
std::cout << pila.top() << std::endl;   // 2
pila.pop();

std::queue<int> cola;
cola.push(1);       // en std::queue, "push" es el equivalente de enqueue
cola.push(2);
std::cout << cola.front() << std::endl; // 1
cola.pop();          // "pop" es el equivalente de dequeue
```

> Tanto `std::stack` como `std::queue` son **adaptadores de contenedor**: por dentro usan otro contenedor (por defecto `std::deque`) y solo exponen la interfaz restringida de pila o cola. En la materia las implementamos desde cero para entender qué hay "por debajo" de esa interfaz.



# Resumen general de complejidades

| Estructura | Operación | Complejidad |
|------------|-----------|-------------|
| Pila (arreglo)   | push / pop / top / empty | O(1) amortizado / O(1) / O(1) / O(1) |
| Pila (lista)      | push / pop / top / empty | O(1) / O(1) / O(1) / O(1) |
| Cola (arreglo, buffer circular) | enqueue / dequeue / front / empty | O(1) amortizado / O(1) / O(1) / O(1) |
| Cola (lista)      | enqueue / dequeue / front / empty | O(1) / O(1) / O(1) / O(1) |

> En ambas estructuras, la elección entre arreglo y lista enlazada no cambia la complejidad asintótica: cambia el *trade-off* entre localidad de cache, uso de memoria y garantías de peor caso.
