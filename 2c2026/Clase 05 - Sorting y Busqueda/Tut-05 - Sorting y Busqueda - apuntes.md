Tutorial 5 – Sorting y Búsqueda
===

> **Ingeniería en Inteligencia Artificial** — **Algoritmos y Estructura de Datos**
> **2C 2026** · Docente: **Ing. Magali Marijuan**

- [Tutorial 5 – Sorting y Búsqueda](#tutorial-5--sorting-y-búsqueda)
- [Objetivos de la clase](#objetivos-de-la-clase)
- [Ordenamiento](#ordenamiento)
  - [Algoritmos elementales de ordenamiento](#algoritmos-elementales-de-ordenamiento)
    - [Bubble sort](#bubble-sort)
    - [Insertion sort](#insertion-sort)
    - [Selection sort](#selection-sort)
  - [Estabilidad en algoritmos de ordenamiento](#estabilidad-en-algoritmos-de-ordenamiento)
  - [Costo según la estructura de datos](#costo-según-la-estructura-de-datos)
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
- Repasar búsqueda lineal y binaria: precondiciones, invariantes y complejidad.



# Ordenamiento

Ordenar es uno de los problemas más estudiados en algoritmos: dado un conjunto de elementos, se busca reordenarlos según un criterio (por ejemplo, de menor a mayor).

En esta clase vamos a trabajar con `std::vector<T>`, que en C++ nos da acceso aleatorio a sus elementos en O(1), algo clave para entender el costo de cada algoritmo.

## Algoritmos elementales de ordenamiento

Estos algoritmos se llaman "elementales" porque son simples de programar, pero **no son eficientes** para conjuntos grandes de datos: todos tienen peor caso O(n²).

### Bubble sort

La idea es recorrer el vector varias veces, comparando elementos adyacentes y "burbujeando" el más grande hacia el final en cada pasada.

```
función bubbleSort(v):
    n ← longitud(v)
    para i desde 0 hasta n-1:
        huboSwap ← falso
        para j desde 0 hasta n-i-2:
            si v[j] > v[j+1]:
                intercambiar(v[j], v[j+1])
                huboSwap ← verdadero
        si no huboSwap:
            terminar    // ya está ordenado
```

> El corte con `huboSwap` es lo que hace que el **mejor caso** de bubble sort sea O(n): si el vector ya está ordenado, una sola pasada alcanza para darse cuenta.

### Insertion sort

La idea es construir el vector ordenado de a un elemento por vez: en cada paso, se toma el siguiente elemento y se lo "inserta" en la posición correcta dentro de la parte ya ordenada.

```
función insertionSort(v):
    n ← longitud(v)
    para i desde 1 hasta n-1:
        actual ← v[i]
        j ← i
        mientras j > 0 y v[j-1] > actual:
            v[j] ← v[j-1]
            j ← j - 1
        v[j] ← actual
```

> Insertion sort es muy eficiente cuando el vector está **casi ordenado**: en ese caso el `mientras` interno casi no itera y el costo se acerca a O(n).

### Selection sort

La idea es, en cada paso, buscar el **mínimo** de la parte no ordenada y colocarlo en su posición final mediante un único intercambio.

```
función selectionSort(v):
    n ← longitud(v)
    para i desde 0 hasta n-1:
        indiceMinimo ← i
        para j desde i+1 hasta n-1:
            si v[j] < v[indiceMinimo]:
                indiceMinimo ← j
        intercambiar(v[i], v[indiceMinimo])
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

```
estructura Alumno:
    nombre: string
    nota: entero
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

> En la práctica, para listas enlazadas se prefiere **merge sort** (que vamos a ver en la próxima clase), porque no necesita acceso aleatorio: solo recorre la lista secuencialmente para dividirla y combinarla.



# Búsqueda

## Búsqueda lineal

Recorre el vector elemento por elemento hasta encontrar (o no) lo buscado. No requiere ninguna precondición sobre el orden de los datos.

```
función busquedaLineal(v, buscado):
    para i desde 0 hasta longitud(v)-1:
        si v[i] == buscado:
            devolver i
    devolver -1    // no encontrado
```

## Búsqueda binaria

Aprovecha que el vector está **ordenado** para descartar, en cada paso, la mitad de los elementos que quedan por revisar.

```
función busquedaBinaria(v, buscado):
    // pre: v está ordenado
    izq ← 0
    der ← longitud(v) - 1

    mientras izq <= der:
        medio ← izq + (der - izq) / 2

        si v[medio] == buscado:
            devolver medio
        sino si v[medio] < buscado:
            izq ← medio + 1
        sino:
            der ← medio - 1

    devolver -1    // no encontrado
```

También se puede implementar de forma recursiva, ya que en definición es un Divide & Conquer donde no hace falta combinar (solo se sigue por una de las dos mitades):

```
función busquedaBinariaRec(v, buscado, izq, der):
    // pre: v está ordenado
    si izq > der:
        devolver -1    // caso base: no encontrado

    medio ← izq + (der - izq) / 2

    si v[medio] == buscado:
        devolver medio
    si v[medio] < buscado:
        devolver busquedaBinariaRec(v, buscado, medio + 1, der)
    sino:
        devolver busquedaBinariaRec(v, buscado, izq, medio - 1)
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

> Pregunta para pensar: si tuviéramos una lista enlazada ordenada y quisiéramos buscar eficientemente muchas veces, ¿qué estructura de datos elegirías en su lugar? *Este es exactamente el problema que motiva a los árboles de búsqueda binaria, que vemos más adelante.*
