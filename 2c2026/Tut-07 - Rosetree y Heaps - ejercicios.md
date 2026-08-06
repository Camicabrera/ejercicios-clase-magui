Tut 07 – Rosetree y Heaps: Ejercicios
===

Estos ejercicios están pensados para practicar recursión sobre rosetrees y la implementación manual de heaps sobre un arreglo. Van de menor a mayor dificultad, así que se recomienda resolverlos en orden. Todo el código está en C++.

Vamos a asumir la siguiente definición de rosetree para los primeros ejercicios:

```cpp
template <typename T>
struct Rosetree {
    T valor;
    std::vector<Rosetree<T>*> hijos;
};
```



## Ejercicio 1: Contar nodos y calcular la altura

Escribir dos funciones recursivas sobre un `Rosetree<int>*`:

- `int contarNodos(Rosetree<int>* raiz)`: devuelve la cantidad total de nodos del árbol.
- `int altura(Rosetree<int>* raiz)`: devuelve la altura del árbol, entendida como la cantidad de nodos en el camino más largo desde la raíz hasta una hoja.

Si `raiz` es `nullptr`, ambas funciones deben devolver 0.

### Solución

```cpp
int contarNodos(Rosetree<int>* raiz) {
    if (raiz == nullptr) {
        return 0;
    }
    int total = 1; // el nodo actual
    for (Rosetree<int>* hijo : raiz->hijos) {
        total += contarNodos(hijo); // sumo los nodos de cada subárbol
    }
    return total;
}

int altura(Rosetree<int>* raiz) {
    if (raiz == nullptr) {
        return 0;
    }
    if (raiz->hijos.empty()) {
        return 1; // una hoja tiene altura 1
    }
    int alturaMax = 0;
    for (Rosetree<int>* hijo : raiz->hijos) {
        // me quedo con la altura del subárbol más alto
        alturaMax = std::max(alturaMax, altura(hijo));
    }
    return 1 + alturaMax; // sumo 1 por el nodo actual
}
```

La clave de ambas funciones es la misma: procesar el nodo actual y **recorrer el vector de hijos con un `for`**, combinando (sumando o tomando el máximo) los resultados recursivos.

Complejidad: **O(n)**, donde n es la cantidad de nodos, porque cada nodo se visita exactamente una vez.



## Ejercicio 2: Sumar los valores de un rosetree

Escribir `int sumarValores(Rosetree<int>* raiz)` que devuelva la suma de los valores de todos los nodos del árbol.

### Solución

```cpp
int sumarValores(Rosetree<int>* raiz) {
    if (raiz == nullptr) {
        return 0;
    }
    int suma = raiz->valor;
    for (Rosetree<int>* hijo : raiz->hijos) {
        suma += sumarValores(hijo);
    }
    return suma;
}
```

> Pregunta para pensar: ¿cómo modificarías esta función para que en lugar de sumar todos los valores, sume solamente los valores de las **hojas**?

Complejidad: **O(n)**.



## Ejercicio 3: Imprimir un rosetree con indentación

Escribir una función que imprima un `Rosetree<std::string>*` de forma similar al comando `tree` de una terminal, indentando según la profundidad del nodo:

```
Documentos
  Fotos
    vacaciones.jpg
  Tesis.pdf
```

### Solución

```cpp
void imprimirArbol(Rosetree<std::string>* nodo, int profundidad = 0) {
    if (nodo == nullptr) {
        return;
    }

    // imprimo la indentación correspondiente a la profundidad actual
    for (int i = 0; i < profundidad; i++) {
        std::cout << "  "; // dos espacios por nivel
    }
    std::cout << nodo->valor << "\n";

    // cada hijo se imprime un nivel más profundo
    for (Rosetree<std::string>* hijo : nodo->hijos) {
        imprimirArbol(hijo, profundidad + 1);
    }
}
```

> Tip: usar un parámetro con valor por defecto (`profundidad = 0`) evita tener que pasar explícitamente `0` la primera vez que se llama a la función desde afuera.

Complejidad: **O(n)**, ya que cada nodo se imprime una única vez.



## Ejercicio 4: Simular a mano inserciones y extracciones en un min-heap

Dado el siguiente min-heap representado como arreglo:

```
[2, 5, 4, 8, 7, 9]
```

a) Dibujar el árbol correspondiente y verificar que cumple la propiedad de heap.
b) Simular, paso a paso, el resultado de `insert(1)`.
c) A partir del heap obtenido en (b), simular `extractMin()` y mostrar el heap resultante.

Después, verificar la simulación ejecutando el código.

### Solución

**a)** El árbol queda así (índices entre paréntesis):

```
            2(0)
          /      \
       5(1)      4(2)
      /    \     /
   8(3)   7(4) 9(5)
```

Cada nodo es menor o igual que sus hijos, así que es un min-heap válido.

**b)** `insert(1)`: se agrega `1` al final → `[2, 5, 4, 8, 7, 9, 1]`. El nuevo elemento está en la posición 6; su padre es `(6-1)/2 = 2`, que vale `4`. Como `1 < 4`, se intercambian: `[2, 5, 1, 8, 7, 9, 4]`. El elemento ahora está en la posición 2; su padre es `(2-1)/2 = 0`, que vale `2`. Como `1 < 2`, se intercambian de nuevo: `[1, 5, 2, 8, 7, 9, 4]`. Como ya llegó a la raíz, el sift-up termina.

**c)** `extractMin()` sobre `[1, 5, 2, 8, 7, 9, 4]`: se guarda `1` como resultado, se mueve el último elemento (`4`) a la raíz y se achica el arreglo → `[4, 5, 2, 8, 7, 9]`. Se hace sift-down desde la raíz: los hijos de la posición 0 son `5` (pos 1) y `2` (pos 2); el menor es `2`, y como `4 > 2`, se intercambian → `[2, 5, 4, 8, 7, 9]`. La posición actual es 2, cuyo único hijo es `9` (pos 5); como `4 < 9`, no hay más intercambios. El resultado es `[2, 5, 4, 8, 7, 9]` (¡el heap original!) y `extractMin()` devuelve `1`.

```cpp
int main() {
    MinHeap h;
    for (int v : {2, 5, 4, 8, 7, 9}) {
        h.insert(v); // ver ejercicio 5 para construir directamente con buildHeap
    }
    h.insert(1);
    std::cout << h.extractMin() << "\n"; // imprime 1
    return 0;
}
```

> Pregunta para pensar: ¿el resultado de simular `insert` uno por uno da siempre el mismo arreglo interno que hacer `buildHeap` sobre todos los elementos juntos? ¿Por qué sí o por qué no?



## Ejercicio 5: Construir un heap con `buildHeap`

Dado el arreglo `std::vector<int> v = {9, 4, 7, 1, 8, 2, 5};`, implementar `buildHeap` (heapify óptimo, O(n)) que lo transforme **in-place** en un min-heap válido.

### Solución

```cpp
void siftDown(std::vector<int>& v, int i, int n) {
    while (true) {
        int menor = i;
        int izq = 2 * i + 1;
        int der = 2 * i + 2;

        if (izq < n && v[izq] < v[menor]) menor = izq;
        if (der < n && v[der] < v[menor]) menor = der;

        if (menor == i) break; // ya cumple la propiedad de heap
        std::swap(v[i], v[menor]);
        i = menor;
    }
}

void buildHeap(std::vector<int>& v) {
    int n = static_cast<int>(v.size());
    // el último nodo con hijos está en la posición n/2 - 1
    for (int i = n / 2 - 1; i >= 0; i--) {
        siftDown(v, i, n);
    }
}

int main() {
    std::vector<int> v = {9, 4, 7, 1, 8, 2, 5};
    buildHeap(v);
    for (int x : v) std::cout << x << " ";
    std::cout << "\n";
    return 0;
}
```

> Recordar: aplicar `siftDown` **desde el primer nodo hasta el último** no funciona, porque los subárboles de abajo todavía no serían heaps válidos cuando se los usa. Hay que ir de abajo hacia arriba.

Complejidad: **O(n)**.



## Ejercicio 6: Heapsort

Implementar `heapsort(std::vector<int>& v)` que ordene el vector de menor a mayor, usando un max-heap y sin memoria auxiliar (in-place).

### Solución

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

    // 1. construir el max-heap, O(n)
    for (int i = n / 2 - 1; i >= 0; i--) {
        siftDownMax(v, i, n);
    }

    // 2. extraer el máximo repetidamente y colocarlo al final
    for (int fin = n - 1; fin > 0; fin--) {
        std::swap(v[0], v[fin]); // el máximo actual va a su posición definitiva
        siftDownMax(v, 0, fin);  // el heap "activo" ahora tiene tamaño fin
    }
}
```

Complejidad: **O(n log n)** en todos los casos (mejor, peor y promedio), con **O(1)** de memoria extra.



## Ejercicio 7: Los k elementos más grandes

Dado un `std::vector<int>` de n elementos y un entero k, obtener los k elementos más grandes usando un heap, en O(n log k).

### Solución

La idea es mantener un **min-heap de tamaño k**: recorremos todos los elementos y, si el heap todavía no tiene k elementos, insertamos directamente. Si ya tiene k elementos, comparamos el nuevo valor contra el mínimo del heap (la raíz); si el nuevo valor es mayor, descartamos el mínimo actual e insertamos el nuevo.

```cpp
std::vector<int> kMasGrandes(const std::vector<int>& v, int k) {
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

    for (int x : v) {
        if (static_cast<int>(minHeap.size()) < k) {
            minHeap.push(x);
        } else if (x > minHeap.top()) {
            minHeap.pop();  // saco el menor de los k que tenía guardados
            minHeap.push(x);
        }
    }

    std::vector<int> resultado;
    while (!minHeap.empty()) {
        resultado.push_back(minHeap.top());
        minHeap.pop();
    }
    return resultado; // quedan los k más grandes, de menor a mayor
}
```

> ¿Por qué usar un **min-heap** para buscar los máximos? Porque el heap nunca crece más allá de tamaño k: en todo momento la raíz es el "peor" de los k candidatos actuales, y es justamente el que conviene poder consultar y descartar en O(log k).

Complejidad: **O(n log k)**, mucho mejor que ordenar todo el arreglo (O(n log n)) cuando k es chico.



## Ejercicio 8: Mediana de un stream con dos heaps

Se reciben números uno a la vez (un *stream*) y en todo momento hay que poder responder cuál es la **mediana** de todos los números recibidos hasta el momento, en O(log n) por cada número nuevo.

### Solución

La idea clásica es mantener **dos heaps** que dividen los datos en dos mitades balanceadas:

- un **max-heap** con la mitad **menor** de los elementos (`izquierda`),
- un **min-heap** con la mitad **mayor** de los elementos (`derecha`),

manteniendo siempre que `izquierda.size()` sea igual a `derecha.size()`, o a lo sumo uno más. Así, la mediana siempre está en la raíz de alguno de los dos heaps (o es el promedio de ambas raíces).

```cpp
class MedianaStream {
private:
    std::priority_queue<int> izquierda; // max-heap: mitad menor
    std::priority_queue<int, std::vector<int>, std::greater<int>> derecha; // min-heap: mitad mayor

public:
    void agregar(int valor) {
        // 1. insertar en el heap que corresponda según el valor
        if (izquierda.empty() || valor <= izquierda.top()) {
            izquierda.push(valor);
        } else {
            derecha.push(valor);
        }

        // 2. rebalancear para que las mitades difieran en a lo sumo 1 elemento
        if (izquierda.size() > derecha.size() + 1) {
            derecha.push(izquierda.top());
            izquierda.pop();
        } else if (derecha.size() > izquierda.size() + 1) {
            izquierda.push(derecha.top());
            derecha.pop();
        }
    }

    double mediana() const {
        if (izquierda.size() == derecha.size()) {
            return (izquierda.top() + derecha.top()) / 2.0;
        }
        // el heap más grande tiene el elemento del medio
        return izquierda.size() > derecha.size() ? izquierda.top() : derecha.top();
    }
};
```

Cada llamada a `agregar` hace a lo sumo un par de inserciones/extracciones de heap, todas O(log n); `mediana()` es O(1).

> Pregunta para pensar: ¿por qué no alcanza con un solo heap para resolver este problema en O(log n) por elemento?



## Ejercicios propuestos

1. Escribir `bool esHeapValido(const std::vector<int>& v)` que verifique, en O(n), si un arreglo cumple la propiedad de min-heap (es decir, si para todo nodo `i` que tenga hijos, `v[i] <= v[2i+1]` y, si existe, `v[i] <= v[2i+2]`).
2. Implementar `void eliminar(std::vector<int>& heap, int indice)` que elimine el elemento en una posición arbitraria de un min-heap (no necesariamente la raíz), manteniendo la propiedad de heap y sin reconstruir todo el arreglo desde cero. *Ayuda: pensar qué combinación de sift-up y sift-down puede llegar a hacer falta según el valor que quede en esa posición.*
