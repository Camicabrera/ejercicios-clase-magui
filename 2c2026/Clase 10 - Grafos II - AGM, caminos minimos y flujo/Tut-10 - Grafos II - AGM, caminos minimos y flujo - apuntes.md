Tut 10 – Grafos II: AGM, caminos mínimos y flujo
===

> **Ingeniería en Inteligencia Artificial** — **Algoritmos y Estructura de Datos**  
> **2C 2026** · Docente: **Ing. Magali Marijuan**

- [Tut 10 – Grafos II: AGM, caminos mínimos y flujo](#tut-10--grafos-ii-agm-caminos-mínimos-y-flujo)
- [Objetivos de la clase](#objetivos-de-la-clase)
- [Árbol Generador Mínimo (AGM)](#árbol-generador-mínimo-agm)
  - [Motivación](#motivación)
  - [Union-Find (DSU)](#union-find-dsu)
  - [Kruskal](#kruskal)
  - [Prim](#prim)
  - [Kruskal vs Prim](#kruskal-vs-prim)
- [Caminos mínimos](#caminos-mínimos)
  - [Dijkstra](#dijkstra)
  - [Bellman-Ford](#bellman-ford)
  - [Floyd-Warshall (mención breve)](#floyd-warshall-mención-breve)
  - [Comparación de algoritmos de caminos mínimos](#comparación-de-algoritmos-de-caminos-mínimos)
- [Flujo máximo](#flujo-máximo)
  - [Red de flujo](#red-de-flujo)
  - [Ford-Fulkerson y Edmonds-Karp](#ford-fulkerson-y-edmonds-karp)
  - [Teorema max-flow min-cut](#teorema-max-flow-min-cut)
- [Resumen de complejidades](#resumen-de-complejidades)



# Objetivos de la clase
- Entender qué es un Árbol Generador Mínimo (AGM) y para qué sirve.
- Implementar Union-Find (DSU) con union by rank y path compression.
- Implementar Kruskal y Prim para calcular un AGM.
- Implementar Dijkstra para caminos mínimos con pesos no negativos.
- Implementar Bellman-Ford para pesos negativos y detección de ciclos negativos.
- Conocer Floyd-Warshall para caminos mínimos todos-contra-todos.
- Entender el concepto de red de flujo y calcular flujo máximo con Edmonds-Karp.
- Identificar qué algoritmos de esta clase son ejemplos de estrategia **greedy**.



# Árbol Generador Mínimo (AGM)

## Motivación

Dado un grafo **conexo, no dirigido y ponderado**, un **Árbol Generador Mínimo** (AGM, o *MST* por *Minimum Spanning Tree*) es un subconjunto de aristas que:
- conecta **todos** los vértices del grafo,
- no forma ciclos (es un árbol: tiene exactamente `V - 1` aristas),
- minimiza la suma de los pesos de las aristas elegidas.

> Ejemplos típicos: tender la menor cantidad de cable posible para conectar un conjunto de edificios, o diseñar una red eléctrica que llegue a todas las casas con el menor costo de cableado.

Existen dos algoritmos clásicos, **Kruskal** y **Prim**, y ambos son ejemplos de estrategia **greedy**: en cada paso toman la decisión localmente óptima, y se puede demostrar (propiedad de corte) que esa elección nunca los aleja del óptimo global.


## Union-Find (DSU)

Kruskal necesita una estructura que responda rápido a dos preguntas:
- **Find(x)**: ¿a qué conjunto (componente) pertenece `x`?
- **Union(x, y)**: unir los conjuntos de `x` e `y`.

Esta estructura se llama **Union-Find** o **DSU** (*Disjoint Set Union*). Con las optimizaciones de **union by rank** (unir siempre el árbol más chico bajo el más alto) y **path compression** (aplanar el camino en cada `Find`), el costo amortizado de cada operación es prácticamente O(1) — formalmente, O(α(n)), donde α es la función inversa de Ackermann, que crece tan lento que para cualquier `n` práctico es menor a 5.

```cpp
#include <vector>

struct DSU {
    std::vector<int> padre, rango;

    DSU(int n) : padre(n), rango(n, 0) {
        for (int i = 0; i < n; i++) padre[i] = i; // cada elemento arranca en su propio conjunto
    }

    int find(int x) {
        if (padre[x] != x) {
            padre[x] = find(padre[x]); // path compression: aplana el camino hacia la raíz
        }
        return padre[x];
    }

    bool unir(int x, int y) {
        int raizX = find(x);
        int raizY = find(y);
        if (raizX == raizY) return false; // ya estaban en el mismo conjunto -> formaría un ciclo

        // union by rank: el árbol más bajo cuelga del más alto
        if (rango[raizX] < rango[raizY]) {
            padre[raizX] = raizY;
        } else if (rango[raizX] > rango[raizY]) {
            padre[raizY] = raizX;
        } else {
            padre[raizY] = raizX;
            rango[raizX]++;
        }
        return true;
    }
};
```

> `unir` devuelve `false` cuando `x` e `y` ya estaban en el mismo conjunto: esa señal es justamente lo que usa Kruskal para detectar que agregar esa arista formaría un ciclo.

> Pregunta para pensar: ¿por qué path compression por sí solo (sin union by rank) ya mejora mucho la complejidad? ¿Y por qué conviene combinar ambas optimizaciones?


## Kruskal

Kruskal ordena todas las aristas por peso ascendente y las va agregando de a una, siempre que sus dos extremos **no** estén ya en el mismo conjunto del DSU (si lo estuvieran, agregar la arista formaría un ciclo).

```cpp
#include <vector>
#include <algorithm>

struct Arista {
    int u, v, peso;
};

int kruskal(int n, std::vector<Arista> aristas) {
    std::sort(aristas.begin(), aristas.end(), [](const Arista& a, const Arista& b) {
        return a.peso < b.peso;
    });

    DSU dsu(n);
    int pesoTotal = 0;
    int aristasUsadas = 0;

    for (const Arista& a : aristas) {
        if (dsu.unir(a.u, a.v)) {       // si unir tuvo éxito, no había ciclo
            pesoTotal += a.peso;
            aristasUsadas++;
            if (aristasUsadas == n - 1) break; // ya tenemos el AGM completo
        }
    }
    return pesoTotal;
}
```

> **Kruskal es greedy**: en cada paso elige la arista más barata disponible que no forme ciclo. La propiedad de corte garantiza que esa elección local siempre puede extenderse a un AGM óptimo.

**Complejidad:** O(E log E) por el ordenamiento de las aristas (las operaciones de DSU son casi O(1) amortizado, así que no dominan).


## Prim

Prim construye el AGM "haciendo crecer" un árbol desde un vértice arbitrario: en cada paso agrega la arista de menor peso que conecta el árbol actual con algún vértice todavía afuera. Se implementa eficientemente con `std::priority_queue`.

```cpp
#include <vector>
#include <queue>
#include <utility>

int prim(const std::vector<std::vector<std::pair<int,int>>>& adj) { // adj[u] = {(v, peso), ...}
    int n = adj.size();
    std::vector<bool> enArbol(n, false);

    // priority_queue de mínimos: con greater<> el tope siempre es el par de menor peso
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<>> pq;

    pq.push({0, 0}); // {peso, vertice} - arrancamos arbitrariamente desde el vértice 0
    int pesoTotal = 0;

    while (!pq.empty()) {
        auto [peso, u] = pq.top();
        pq.pop();

        if (enArbol[u]) continue; // puede haber quedado una entrada vieja en la cola
        enArbol[u] = true;
        pesoTotal += peso;

        for (auto [v, pesoArista] : adj[u]) {
            if (!enArbol[v]) {
                pq.push({pesoArista, v});
            }
        }
    }
    return pesoTotal;
}
```

> **Prim también es greedy**: en cada paso agrega la arista más barata que conecta el árbol parcial con el resto del grafo.

**Complejidad:** O(E log V) usando `priority_queue` (heap binario).


## Kruskal vs Prim

| Aspecto | Kruskal | Prim |
| --- | --- | --- |
| Estrategia | Greedy sobre las aristas ordenadas | Greedy sobre el crecimiento de un árbol |
| Estructura auxiliar | Union-Find (DSU) | `priority_queue` (heap) |
| Complejidad | O(E log E) | O(E log V) |
| Conviene cuando... | el grafo es disperso y las aristas se pueden ordenar fácilmente | el grafo es denso, o ya tenemos lista/matriz de adyacencia armada |

> Pregunta para pensar: si el grafo tiene pesos repetidos, ¿Kruskal y Prim siempre devuelven exactamente el mismo conjunto de aristas? ¿Qué es lo único que garantizan ambos que va a coincidir?



# Caminos mínimos

## Dijkstra

Calcula la distancia mínima desde un vértice **origen** hacia todos los demás, en grafos con pesos **no negativos**. Es un algoritmo **greedy**: en cada paso "confirma" definitivamente la distancia del vértice no confirmado más cercano al origen.

```cpp
#include <vector>
#include <queue>
#include <limits>
#include <utility>

std::vector<long long> dijkstra(const std::vector<std::vector<std::pair<int,int>>>& adj, int origen) {
    int n = adj.size();
    const long long INF = std::numeric_limits<long long>::max();
    std::vector<long long> dist(n, INF);

    std::priority_queue<std::pair<long long,int>, std::vector<std::pair<long long,int>>, std::greater<>> pq;

    dist[origen] = 0;
    pq.push({0, origen});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue; // entrada obsoleta: ya encontramos algo mejor para u

        for (auto [v, peso] : adj[u]) {
            if (dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}
```

> **Dijkstra no funciona con pesos negativos**: al confirmar la distancia mínima de un vértice de forma greedy, asume que ningún camino futuro puede mejorarla — algo que deja de ser cierto si hay pesos negativos en el grafo.

> Pregunta para pensar: ¿para qué sirve la línea `if (d > dist[u]) continue;`? ¿El algoritmo daría un resultado incorrecto si la sacáramos, o solo sería menos eficiente?

**Complejidad:** O(E log V) con `priority_queue`.


## Bellman-Ford

Bellman-Ford también calcula distancias mínimas desde un origen, pero **sí soporta pesos negativos**. La idea es relajar **todas** las aristas, `V - 1` veces. Si después de esas `V - 1` rondas todavía se puede relajar alguna arista, es porque existe un **ciclo negativo** alcanzable desde el origen.

```cpp
#include <vector>
#include <limits>

struct AristaDirigida {
    int u, v, peso;
};

// devuelve false si detecta un ciclo negativo alcanzable desde el origen
bool bellmanFord(int n, const std::vector<AristaDirigida>& aristas, int origen, std::vector<long long>& dist) {
    const long long INF = std::numeric_limits<long long>::max() / 2;
    dist.assign(n, INF);
    dist[origen] = 0;

    for (int i = 0; i < n - 1; i++) {
        for (const auto& a : aristas) {
            if (dist[a.u] < INF && dist[a.u] + a.peso < dist[a.v]) {
                dist[a.v] = dist[a.u] + a.peso;
            }
        }
    }

    // ronda V-esima: si todavía se puede relajar, hay un ciclo negativo
    for (const auto& a : aristas) {
        if (dist[a.u] < INF && dist[a.u] + a.peso < dist[a.v]) {
            return false;
        }
    }
    return true;
}
```

> Bellman-Ford **no es greedy**: no toma una decisión local irrevocable en cada paso, sino que relaja repetidamente todas las aristas hasta que las distancias convergen (o hasta detectar que nunca van a converger, por el ciclo negativo).

**Complejidad:** O(V · E).


## Floyd-Warshall (mención breve)

Cuando se necesitan las distancias mínimas entre **todos los pares** de vértices (no solo desde un origen), conviene usar **Floyd-Warshall**: programación dinámica sobre una matriz de distancias, probando para cada par `(i, j)` si pasar por un vértice intermedio `k` mejora la distancia.

```cpp
#include <vector>

void floydWarshall(std::vector<std::vector<long long>>& dist) { // dist[i][j] = peso de la arista (i,j), o INF
    int n = dist.size();

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}
```

> Soporta pesos negativos (aunque no ciclos negativos). Conviene cuando `V` es chico, típicamente hasta unos pocos cientos de vértices, porque su complejidad es cúbica.

**Complejidad:** O(V³).


## Comparación de algoritmos de caminos mínimos

| Algoritmo | Pesos negativos | Detecta ciclo negativo | Complejidad | Caso de uso |
| --- | --- | --- | --- | --- |
| Dijkstra | No | No | O(E log V) | Un origen, pesos ≥ 0 |
| Bellman-Ford | Sí | Sí | O(V · E) | Un origen, puede haber pesos negativos |
| Floyd-Warshall | Sí | Sí (diagonal negativa) | O(V³) | Todos contra todos, V chico |



# Flujo máximo

## Red de flujo

Una **red de flujo** es un grafo **dirigido** donde cada arista `(u, v)` tiene una **capacidad** máxima. Hay un vértice **fuente** `s` (de donde "sale" todo el flujo) y un vértice **sumidero** `t` (a donde "llega" todo el flujo).

Un **flujo** es una asignación de valores a las aristas que respeta dos reglas:
- **Restricción de capacidad**: el flujo por una arista no puede superar su capacidad.
- **Conservación de flujo**: para todo vértice que no sea `s` ni `t`, lo que entra debe ser igual a lo que sale.

El **flujo máximo** es el mayor valor total de flujo que puede salir de `s` y llegar a `t` sin violar ninguna de esas reglas.

> Ejemplos típicos: capacidad máxima de una red de tuberías, ancho de banda máximo entre dos routers en una red, cantidad máxima de mercadería que se puede transportar entre dos ciudades usando una red de rutas con capacidades limitadas.


## Ford-Fulkerson y Edmonds-Karp

La idea de **Ford-Fulkerson** es: mientras exista un **camino aumentante** (un camino de `s` a `t` en el **grafo residual**, es decir, con capacidad disponible), aumentar el flujo total en la cantidad del **cuello de botella** (la mínima capacidad residual a lo largo de ese camino).

El grafo residual también incluye, por cada arista `(u,v)` con flujo asignado, una arista "de vuelta" `(v,u)` que permite deshacer parte de ese flujo si conviene (esto es lo que le da al algoritmo la flexibilidad de corregir decisiones anteriores).

**Edmonds-Karp** es la implementación concreta de Ford-Fulkerson que busca el camino aumentante con **BFS** (el camino con menor cantidad de aristas), lo que garantiza una cota de complejidad de O(V · E²).

```cpp
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

bool bfsResidual(const std::vector<std::vector<int>>& capacidad, const std::vector<std::vector<int>>& flujo,
                  int fuente, int sumidero, std::vector<int>& padre) {
    int n = capacidad.size();
    std::vector<bool> visitado(n, false);
    std::queue<int> cola;

    cola.push(fuente);
    visitado[fuente] = true;
    padre[fuente] = -1;

    while (!cola.empty()) {
        int u = cola.front();
        cola.pop();

        for (int v = 0; v < n; v++) {
            int capacidadResidual = capacidad[u][v] - flujo[u][v];
            if (!visitado[v] && capacidadResidual > 0) {
                padre[v] = u;
                if (v == sumidero) return true; // llegamos al sumidero
                visitado[v] = true;
                cola.push(v);
            }
        }
    }
    return false; // no hay más caminos aumentantes
}

int edmondsKarp(std::vector<std::vector<int>> capacidad, int fuente, int sumidero) {
    int n = capacidad.size();
    std::vector<std::vector<int>> flujo(n, std::vector<int>(n, 0));
    std::vector<int> padre(n);
    int flujoMaximo = 0;

    while (bfsResidual(capacidad, flujo, fuente, sumidero, padre)) {
        // buscamos el cuello de botella (mínima capacidad residual) del camino encontrado
        int cuelloDeBotella = std::numeric_limits<int>::max();
        for (int v = sumidero; v != fuente; v = padre[v]) {
            int u = padre[v];
            cuelloDeBotella = std::min(cuelloDeBotella, capacidad[u][v] - flujo[u][v]);
        }

        // actualizamos el flujo a lo largo del camino, y el flujo inverso (para poder "deshacer")
        for (int v = sumidero; v != fuente; v = padre[v]) {
            int u = padre[v];
            flujo[u][v] += cuelloDeBotella;
            flujo[v][u] -= cuelloDeBotella;
        }

        flujoMaximo += cuelloDeBotella;
    }
    return flujoMaximo;
}
```

> Acá usamos **matriz** de capacidades (no lista de adyacencia), porque el algoritmo necesita poder consultar y actualizar la capacidad residual entre cualquier par de vértices de forma directa, incluyendo las aristas "de vuelta" que al principio no existían en el grafo original.

> Ford-Fulkerson **no es un algoritmo greedy en sentido estricto**: gracias a las aristas residuales inversas, puede "deshacer" flujo asignado en una iteración anterior si eso permite, en conjunto, lograr un flujo total mayor. Sin embargo, cada iteración sí elige de forma local el próximo camino aumentante a explotar.

> Pregunta para pensar: ¿por qué buscar el camino aumentante con BFS (Edmonds-Karp) da una cota de complejidad garantizada, mientras que Ford-Fulkerson genérico (por ejemplo, buscando con DFS) puede en teoría necesitar muchas más iteraciones?

**Complejidad:** O(V · E²) con Edmonds-Karp.


## Teorema max-flow min-cut

Un **corte** de la red es una partición de los vértices en dos conjuntos, uno que contiene a `s` y otro que contiene a `t`. La **capacidad del corte** es la suma de las capacidades de las aristas que van del conjunto de `s` al conjunto de `t`.

> **Teorema max-flow min-cut:** el valor del flujo máximo de `s` a `t` es exactamente igual a la capacidad del **corte mínimo** (el corte de menor capacidad posible entre todos los cortes que separan a `s` de `t`).

Intuitivamente, el corte mínimo representa el verdadero "cuello de botella" de toda la red: no importa cuántos caminos alternativos existan, el flujo nunca puede superar la capacidad total de ese conjunto de aristas que separa a la fuente del sumidero.

Una vez calculado el flujo máximo con Edmonds-Karp, se puede identificar el corte mínimo así: se corre un último BFS sobre el grafo residual final desde `s`; los vértices alcanzables forman un lado del corte, y los no alcanzables el otro. Las aristas originales que cruzan de un lado al otro son exactamente las aristas del corte mínimo.

> Pregunta para pensar: ¿por qué las aristas del corte mínimo tienen que estar "saturadas" (con flujo igual a su capacidad) en cualquier flujo máximo?



# Resumen de complejidades

| Algoritmo | Complejidad | ¿Es greedy? |
| --- | --- | --- |
| Kruskal | O(E log E) | Sí |
| Prim | O(E log V) | Sí |
| Dijkstra | O(E log V) | Sí |
| Bellman-Ford | O(V · E) | No (relajación iterativa) |
| Floyd-Warshall | O(V³) | No (programación dinámica) |
| Edmonds-Karp | O(V · E²) | Parcialmente (elige localmente, pero puede deshacer decisiones) |

> Tip para el parcial: si te preguntan "¿qué algoritmo usarías?", primero identificá el tipo de problema (AGM, camino mínimo desde un origen, todos-contra-todos, o flujo) y recién después fijate en las restricciones (pesos negativos, tamaño de V y E) para elegir el algoritmo concreto.
