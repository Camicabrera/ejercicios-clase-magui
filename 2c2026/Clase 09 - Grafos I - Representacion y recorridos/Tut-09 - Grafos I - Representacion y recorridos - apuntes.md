Tut 09 – Grafos I: Representación y recorridos
===

> **Ingeniería en Inteligencia Artificial** — **Algoritmos y Estructura de Datos**  
> **2C 2026** · Docente: **Ing. Magali Marijuan**

- [Tut 09 – Grafos I: Representación y recorridos](#tut-09--grafos-i-representación-y-recorridos)
- [Objetivos de la clase](#objetivos-de-la-clase)
- [¿Qué es un grafo?](#qué-es-un-grafo)
  - [Vocabulario básico](#vocabulario-básico)
  - [Tipos de grafos](#tipos-de-grafos)
- [Representaciones de un grafo](#representaciones-de-un-grafo)
  - [Matriz de adyacencia](#matriz-de-adyacencia)
  - [Lista de adyacencia](#lista-de-adyacencia)
  - [Matriz vs lista: ¿cuál uso?](#matriz-vs-lista-cuál-uso)
- [Recorridos de grafos](#recorridos-de-grafos)
  - [BFS (Breadth-First Search)](#bfs-breadth-first-search)
  - [DFS (Depth-First Search)](#dfs-depth-first-search)
- [Aplicaciones de los recorridos](#aplicaciones-de-los-recorridos)
  - [Componentes conexas](#componentes-conexas)
  - [Detección de ciclos](#detección-de-ciclos)
  - [Orden topológico](#orden-topológico)
  - [Distancia mínima en grafos no ponderados](#distancia-mínima-en-grafos-no-ponderados)
- [Complejidad general](#complejidad-general)



# Objetivos de la clase
- Entender qué es un grafo y manejar su vocabulario básico.
- Diferenciar grafos dirigidos/no dirigidos y ponderados/no ponderados.
- Comparar las dos representaciones clásicas: matriz de adyacencia y lista de adyacencia.
- Implementar BFS y DFS en C++.
- Usar los recorridos para resolver problemas típicos: componentes conexas, detección de ciclos, orden topológico y distancia mínima.



# ¿Qué es un grafo?

Un **grafo** es una estructura formada por un conjunto de **vértices** (o nodos) y un conjunto de **aristas** (o arcos) que conectan pares de vértices.

Formalmente, un grafo se define como un par `G = (V, E)` donde:
- `V` es el conjunto de vértices.
- `E` es el conjunto de aristas, cada una conectando dos vértices de `V`.

```
    A --- B
    |     |
    C --- D --- E
```

En este ejemplo, `V = {A, B, C, D, E}` y `E = {(A,B), (A,C), (B,D), (C,D), (D,E)}`.

> Los grafos modelan cualquier situación con **entidades y relaciones entre ellas**: redes sociales, mapas de rutas, dependencias entre tareas, circuitos eléctricos, links entre páginas web, etc.


## Vocabulario básico

| Término | Significado |
| --- | --- |
| Vértice / Nodo | Unidad básica del grafo. |
| Arista | Conexión entre dos vértices. |
| Grado | Cantidad de aristas incidentes a un vértice. |
| Grado de entrada (in-degree) | En grafos dirigidos: cantidad de aristas que **llegan** a un vértice. |
| Grado de salida (out-degree) | En grafos dirigidos: cantidad de aristas que **salen** de un vértice. |
| Camino | Secuencia de vértices donde cada par consecutivo está unido por una arista. |
| Ciclo | Camino que empieza y termina en el mismo vértice, sin repetir aristas. |
| Conexo | Un grafo no dirigido es conexo si existe un camino entre **todo par** de vértices. |
| Componente conexa | Subconjunto máximo de vértices mutuamente alcanzables entre sí. |

> Pregunta para pensar: ¿un grafo dirigido puede ser "conexo" de la misma manera que uno no dirigido? (Pista: pensar en la diferencia entre *conexo* y *fuertemente conexo*.)


## Tipos de grafos

| Criterio | Tipo | Descripción |
| --- | --- | --- |
| Dirección | **No dirigido** | Las aristas no tienen sentido: si `(u,v) ∈ E` entonces se puede ir de `u` a `v` y de `v` a `u`. |
| Dirección | **Dirigido** (digrafo) | Las aristas tienen sentido: `(u,v) ∈ E` no implica `(v,u) ∈ E`. |
| Peso | **No ponderado** | Todas las aristas "valen" lo mismo (peso 1 implícito). |
| Peso | **Ponderado** | Cada arista tiene un **peso** o **costo** asociado (por ejemplo, distancia en km). |

Ejemplos:
- Red de amistades en una red social → no dirigido, no ponderado.
- Seguidores en Twitter → dirigido, no ponderado (A sigue a B no implica que B siga a A).
- Rutas entre ciudades con distancias → no dirigido, ponderado.
- Vuelos entre aeropuertos con precios → dirigido, ponderado.

> Pregunta para pensar: ¿cómo representarías un grafo no dirigido usando las herramientas de un grafo dirigido?



# Representaciones de un grafo

Vamos a ver las dos formas estándar de representar un grafo en memoria. En la materia siempre vamos a numerar los vértices de `0` a `n-1`.

## Matriz de adyacencia

Es una matriz de `n x n` donde la posición `adj[u][v]` indica si existe (o el peso de) la arista entre `u` y `v`.

```cpp
#include <vector>

int n = 5; // cantidad de vertices
std::vector<std::vector<int>> adj(n, std::vector<int>(n, 0));

// agregar arista no dirigida entre u y v
void agregarArista(std::vector<std::vector<int>>& adj, int u, int v) {
    adj[u][v] = 1;
    adj[v][u] = 1; // si fuera dirigido, se omite esta línea
}
```

Para un grafo **ponderado**, en vez de guardar `0`/`1` se guarda el peso, y se suele usar un valor grande (`INF`) para representar "no hay arista":

```cpp
const int INF = 1e9;
std::vector<std::vector<int>> adj(n, std::vector<int>(n, INF));

void agregarAristaPonderada(std::vector<std::vector<int>>& adj, int u, int v, int peso) {
    adj[u][v] = peso;
    adj[v][u] = peso; // si fuera dirigido, se omite esta línea
}
```

## Lista de adyacencia

Para cada vértice se guarda **solo** la lista de sus vecinos. Es la representación que vamos a usar por defecto en la materia.

```cpp
#include <vector>

int n = 5;
std::vector<std::vector<int>> adj(n); // adj[u] = lista de vecinos de u

void agregarArista(std::vector<std::vector<int>>& adj, int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u); // si fuera dirigido, se omite esta línea
}
```

Para un grafo **ponderado**, cada vecino se guarda junto con el peso de la arista, usando `std::pair<int,int>` (destino, peso):

```cpp
#include <vector>
#include <utility>

int n = 5;
std::vector<std::vector<std::pair<int,int>>> adj(n); // adj[u] = {(v, peso), ...}

void agregarAristaPonderada(std::vector<std::vector<std::pair<int,int>>>& adj, int u, int v, int peso) {
    adj[u].push_back({v, peso});
    adj[v].push_back({u, peso}); // si fuera dirigido, se omite esta línea
}
```

## Matriz vs lista: ¿cuál uso?

| Operación | Matriz de adyacencia | Lista de adyacencia |
| --- | --- | --- |
| Espacio | O(V²) | O(V + E) |
| ¿Existe arista (u,v)? | O(1) | O(grado(u)) |
| Recorrer vecinos de u | O(V) | O(grado(u)) |
| Agregar una arista | O(1) | O(1) |
| Conviene cuando... | el grafo es **denso** (E cercano a V²) | el grafo es **disperso** (E << V²), la mayoría de los casos reales |

> Tip: en la práctica, casi todos los problemas de la materia trabajan con grafos dispersos (E = O(V)), así que **la lista de adyacencia es la representación por defecto**. Vamos a usar la matriz solo cuando necesitemos consultar "¿existe la arista (u,v)?" muy seguido, o en algoritmos de flujo que la necesitan para el grafo residual.

> Pregunta para pensar: si el grafo tiene 100.000 vértices pero solo 100.000 aristas, ¿cuánta memoria ocuparía la matriz de adyacencia comparada con la lista?



# Recorridos de grafos

Un **recorrido** visita todos los vértices alcanzables desde un vértice inicial, sin repetir ninguno. Los dos recorridos clásicos son BFS y DFS.

## BFS (Breadth-First Search)

BFS explora el grafo **por niveles**: primero visita todos los vecinos directos del inicio, luego los vecinos de esos vecinos, y así sucesivamente. Se implementa con una **cola** (`std::queue`).

```cpp
#include <vector>
#include <queue>

std::vector<int> bfs(const std::vector<std::vector<int>>& adj, int inicio) {
    int n = adj.size();
    std::vector<int> distancia(n, -1); // -1 = no visitado
    std::queue<int> cola;

    distancia[inicio] = 0;
    cola.push(inicio);

    while (!cola.empty()) {
        int actual = cola.front();
        cola.pop();

        for (int vecino : adj[actual]) {
            if (distancia[vecino] == -1) {
                distancia[vecino] = distancia[actual] + 1;
                cola.push(vecino);
            }
        }
    }
    return distancia;
}
```

> El vector `distancia` cumple doble función: marca qué vértices ya fueron visitados (`-1` = no visitado) y guarda la distancia mínima en **cantidad de aristas** desde el inicio.

> Pregunta para pensar: ¿por qué BFS garantiza que la primera vez que se llega a un vértice es con la distancia mínima?

## DFS (Depth-First Search)

DFS explora **en profundidad**: avanza por un camino hasta que no puede más, y recién ahí retrocede (*backtrack*) para probar otro camino. Se puede implementar de forma recursiva (usa el stack de llamadas) o iterativa (con una pila explícita `std::stack`).

### DFS recursivo

```cpp
#include <vector>

void dfs(const std::vector<std::vector<int>>& adj, int actual, std::vector<bool>& visitado) {
    visitado[actual] = true;
    // acá procesamos 'actual', por ejemplo imprimirlo

    for (int vecino : adj[actual]) {
        if (!visitado[vecino]) {
            dfs(adj, vecino, visitado);
        }
    }
}
```

### DFS iterativo (con pila)

```cpp
#include <vector>
#include <stack>

void dfsIterativo(const std::vector<std::vector<int>>& adj, int inicio) {
    int n = adj.size();
    std::vector<bool> visitado(n, false);
    std::stack<int> pila;

    pila.push(inicio);

    while (!pila.empty()) {
        int actual = pila.top();
        pila.pop();

        if (visitado[actual]) continue; // puede quedar duplicado en la pila
        visitado[actual] = true;
        // acá procesamos 'actual'

        for (int vecino : adj[actual]) {
            if (!visitado[vecino]) {
                pila.push(vecino);
            }
        }
    }
}
```

> El orden de visita de la versión iterativa puede diferir del de la versión recursiva, porque la pila invierte el orden de inserción de los vecinos.

> Pregunta para pensar: ¿qué pasaría en la versión recursiva de DFS si no usáramos el vector `visitado`? ¿En qué casos el programa nunca terminaría?



# Aplicaciones de los recorridos

## Componentes conexas

Un grafo no dirigido puede estar formado por varias "islas" desconectadas entre sí: las **componentes conexas**. Para contarlas, recorremos todos los vértices y cada vez que encontramos uno no visitado, lanzamos un BFS/DFS desde ahí (eso cubre toda su componente) y sumamos un contador.

```cpp
#include <vector>
#include <queue>

int contarComponentes(const std::vector<std::vector<int>>& adj) {
    int n = adj.size();
    std::vector<bool> visitado(n, false);
    int componentes = 0;

    for (int v = 0; v < n; v++) {
        if (!visitado[v]) {
            componentes++;
            // BFS desde v, marcando todo lo alcanzable como visitado
            std::queue<int> cola;
            cola.push(v);
            visitado[v] = true;
            while (!cola.empty()) {
                int actual = cola.front();
                cola.pop();
                for (int vecino : adj[actual]) {
                    if (!visitado[vecino]) {
                        visitado[vecino] = true;
                        cola.push(vecino);
                    }
                }
            }
        }
    }
    return componentes;
}
```

## Detección de ciclos

**En grafo no dirigido:** durante un DFS, si encontramos un vecino ya visitado que **no es el padre** del vértice actual, hay un ciclo (si fuera el padre, es simplemente la arista por la que vinimos).

```cpp
bool dfsCicloNoDirigido(const std::vector<std::vector<int>>& adj, int actual, int padre, std::vector<bool>& visitado) {
    visitado[actual] = true;

    for (int vecino : adj[actual]) {
        if (!visitado[vecino]) {
            if (dfsCicloNoDirigido(adj, vecino, actual, visitado)) return true;
        } else if (vecino != padre) {
            return true; // vecino visitado que no es el padre -> ciclo
        }
    }
    return false;
}
```

**En grafo dirigido:** no alcanza con "visitado o no", porque un vecino visitado en otra rama no implica ciclo. Hace falta distinguir si el vecino está **en el camino actual** (ancestro en la recursión). Usamos 3 estados: `0` = no visitado, `1` = en proceso (en la pila de recursión), `2` = terminado.

```cpp
bool dfsCicloDirigido(const std::vector<std::vector<int>>& adj, int actual, std::vector<int>& estado) {
    estado[actual] = 1; // en proceso

    for (int vecino : adj[actual]) {
        if (estado[vecino] == 1) return true;              // ancestro en el camino actual -> ciclo
        if (estado[vecino] == 0 && dfsCicloDirigido(adj, vecino, estado)) return true;
    }

    estado[actual] = 2; // terminado
    return false;
}
```

> Pregunta para pensar: ¿por qué en el grafo dirigido no alcanza con un simple vector de `bool visitado`, como en el caso no dirigido?

## Orden topológico

Un **orden topológico** es un ordenamiento de los vértices de un **DAG** (grafo dirigido acíclico) tal que para toda arista `(u,v)`, `u` aparece antes que `v`. Solo tiene sentido si el grafo no tiene ciclos.

**Algoritmo de Kahn** (basado en BFS): se calculan los grados de entrada de todos los vértices, se encolan los que tienen grado de entrada `0`, y a medida que se procesan se "eliminan" sus aristas salientes (decrementando el grado de entrada de sus vecinos).

```cpp
#include <vector>
#include <queue>

std::vector<int> ordenTopologicoKahn(const std::vector<std::vector<int>>& adj) {
    int n = adj.size();
    std::vector<int> gradoEntrada(n, 0);

    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) gradoEntrada[v]++;
    }

    std::queue<int> cola;
    for (int v = 0; v < n; v++) {
        if (gradoEntrada[v] == 0) cola.push(v);
    }

    std::vector<int> orden;
    while (!cola.empty()) {
        int actual = cola.front();
        cola.pop();
        orden.push_back(actual);

        for (int vecino : adj[actual]) {
            gradoEntrada[vecino]--;
            if (gradoEntrada[vecino] == 0) cola.push(vecino);
        }
    }

    // si orden.size() != n, el grafo tenía un ciclo (no existe orden topológico)
    return orden;
}
```

> Tip: Kahn nos regala gratis la detección de ciclos: si al final `orden.size() < n`, quiere decir que quedaron vértices con grado de entrada positivo atrapados en un ciclo.

También existe una variante con **DFS**: se hace un DFS normal y, cuando un vértice termina de procesar a todos sus vecinos (post-orden), se apila. Al final, desapilar todo da el orden topológico invertido.

## Distancia mínima en grafos no ponderados

Como vimos, **BFS calcula automáticamente la distancia mínima** (en cantidad de aristas) desde el vértice de inicio hacia todos los demás, porque procesa los vértices exactamente en orden creciente de distancia.

> Pregunta para pensar: ¿por qué esto **no** funciona igual si el grafo es ponderado? (Esto motiva a Dijkstra, que vamos a ver en la próxima clase.)



# Complejidad general

Tanto BFS como DFS visitan cada vértice una vez y recorren cada arista una vez (o dos, si es no dirigido), por lo que ambos son:

| Recorrido | Con lista de adyacencia | Con matriz de adyacencia |
| --- | --- | --- |
| BFS | O(V + E) | O(V²) |
| DFS | O(V + E) | O(V²) |

> Con matriz de adyacencia, recorrer los vecinos de un vértice cuesta O(V) (hay que revisar toda la fila), aunque el vértice tenga pocos vecinos reales. Por eso, para recorridos, **la lista de adyacencia es siempre mejor o igual**.

> Pregunta para pensar: si el grafo tiene 10 vértices y 9 aristas (por ejemplo, un árbol), ¿tiene sentido usar matriz de adyacencia?
