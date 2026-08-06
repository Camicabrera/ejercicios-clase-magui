Tut 10 – Ejercicios de Grafos II
===

En esta guía practicamos los algoritmos clásicos sobre grafos ponderados: Árbol Generador Mínimo (Kruskal y Prim), caminos mínimos (Dijkstra y Bellman-Ford) y flujo máximo (Edmonds-Karp). Todos los ejercicios asumen vértices numerados de `0` a `n-1` y usan `std::vector` para representar el grafo.

> Tip: antes de elegir el algoritmo, preguntate: ¿el grafo es dirigido o no dirigido? ¿tiene pesos negativos? ¿necesito la distancia desde un solo origen o entre todos los pares?



## Ejercicio 1 — Implementar Union-Find (DSU)

Implementar una estructura `DSU` con las operaciones `find` (con path compression) y `unir` (con union by rank), que va a ser la base para Kruskal.

### Solución

```cpp
#include <vector>

struct DSU {
    std::vector<int> padre, rango;

    DSU(int n) : padre(n), rango(n, 0) {
        for (int i = 0; i < n; i++) padre[i] = i; // cada elemento arranca siendo su propia raíz
    }

    int find(int x) {
        if (padre[x] != x) {
            padre[x] = find(padre[x]); // path compression
        }
        return padre[x];
    }

    bool unir(int x, int y) {
        int raizX = find(x);
        int raizY = find(y);
        if (raizX == raizY) return false; // ya estaban unidos

        if (rango[raizX] < rango[raizY]) {
            padre[raizX] = raizY;
        } else if (rango[raizX] > rango[raizY]) {
            padre[raizY] = raizX;
        } else {
            padre[raizY] = raizX;
            rango[raizX]++; // solo sube el rango cuando ambos árboles tenían la misma altura
        }
        return true;
    }
};
```

El `rango` funciona como una cota superior de la altura del árbol: al unir dos árboles de distinta altura, el más bajo cuelga del más alto y el rango no cambia; solo se incrementa cuando ambos tenían el mismo rango.



## Ejercicio 2 — Implementar Kruskal

Usando el `DSU` del ejercicio anterior, implementar Kruskal para calcular el peso total del AGM de un grafo no dirigido conexo.

### Solución

```cpp
#include <vector>
#include <algorithm>

struct Arista {
    int u, v, peso;
};

int kruskal(int n, std::vector<Arista> aristas) {
    std::sort(aristas.begin(), aristas.end(), [](const Arista& a, const Arista& b) {
        return a.peso < b.peso; // orden ascendente por peso
    });

    DSU dsu(n);
    int pesoTotal = 0;
    int aristasUsadas = 0;

    for (const Arista& a : aristas) {
        if (dsu.unir(a.u, a.v)) { // si unir tuvo éxito, la arista no cierra un ciclo
            pesoTotal += a.peso;
            aristasUsadas++;
            if (aristasUsadas == n - 1) break; // AGM completo, no hace falta seguir
        }
    }
    return pesoTotal;
}
```

Ordenar las aristas es lo que domina la complejidad: O(E log E). El resto del algoritmo es casi lineal gracias al DSU.



## Ejercicio 3 — Implementar Prim con `priority_queue`

Implementar Prim para calcular el peso total del AGM, partiendo de un grafo representado con lista de adyacencia ponderada.

### Solución

```cpp
#include <vector>
#include <queue>
#include <utility>

int prim(const std::vector<std::vector<std::pair<int,int>>>& adj) { // adj[u] = {(v, peso), ...}
    int n = adj.size();
    std::vector<bool> enArbol(n, false);
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<>> pq;

    pq.push({0, 0}); // arrancamos desde el vértice 0 con "costo de entrada" 0
    int pesoTotal = 0;

    while (!pq.empty()) {
        auto [peso, u] = pq.top();
        pq.pop();

        if (enArbol[u]) continue; // descartamos entradas obsoletas
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

Usamos `std::greater<>` para que la `priority_queue` sea un **heap de mínimos** (por defecto es de máximos), de forma que siempre desencolemos la arista más barata disponible.



## Ejercicio 4 — Implementar Dijkstra con `priority_queue`

Dado un grafo dirigido ponderado con pesos no negativos, calcular la distancia mínima desde un vértice `origen` a todos los demás.

### Solución

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

        if (d > dist[u]) continue; // ya teníamos algo mejor para u, descartamos

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

La línea `if (d > dist[u]) continue;` es clave para la eficiencia: como la misma clave puede quedar en la cola más de una vez (con distinta distancia), esta línea descarta las versiones obsoletas sin afectar la corrección.



## Ejercicio 5 — Implementar Bellman-Ford con detección de ciclo negativo

Dado un grafo dirigido ponderado (que puede tener pesos negativos), calcular las distancias mínimas desde un origen y determinar si existe un ciclo negativo alcanzable.

### Solución

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

    // relajamos todas las aristas V-1 veces
    for (int i = 0; i < n - 1; i++) {
        for (const auto& a : aristas) {
            if (dist[a.u] < INF && dist[a.u] + a.peso < dist[a.v]) {
                dist[a.v] = dist[a.u] + a.peso;
            }
        }
    }

    // ronda extra: si todavía se puede relajar, hay ciclo negativo
    for (const auto& a : aristas) {
        if (dist[a.u] < INF && dist[a.u] + a.peso < dist[a.v]) {
            return false;
        }
    }
    return true;
}
```

Un camino mínimo real nunca visita más de `V - 1` aristas (si no repite vértices), por eso `V - 1` rondas de relajación alcanzan para converger. Si una ronda extra todavía mejora alguna distancia, la única explicación es un ciclo negativo alcanzable.



## Ejercicio 6 — Aplicar Dijkstra a una red de rutas

Una empresa de logística tiene `n` depósitos (numerados de `0` a `n-1`) conectados por rutas en un solo sentido, cada una con un costo de combustible. Dado el depósito de salida `origen`, calcular el costo mínimo para llegar a cada uno de los demás depósitos, y determinar cuál es el depósito **más caro** de alcanzar.

### Solución

```cpp
#include <vector>
#include <limits>

// reutilizamos la función 'dijkstra' del ejercicio 4
std::pair<int, long long> depositoMasCaro(const std::vector<std::vector<std::pair<int,int>>>& adj, int origen) {
    std::vector<long long> costos = dijkstra(adj, origen);

    int depositoElegido = -1;
    long long costoMaximo = -1;
    const long long INF = std::numeric_limits<long long>::max();

    for (int v = 0; v < (int)costos.size(); v++) {
        if (costos[v] == INF) continue; // depósito inalcanzable, lo ignoramos
        if (costos[v] > costoMaximo) {
            costoMaximo = costos[v];
            depositoElegido = v;
        }
    }
    return {depositoElegido, costoMaximo}; // {indice del deposito, costo}
}
```

Este ejercicio muestra el patrón típico de un problema "de aplicación": la parte algorítmica (Dijkstra) ya la tenemos resuelta, y lo que hay que resolver es cómo **traducir el enunciado** (depósitos, rutas, costo de combustible) a un grafo ponderado, y qué hacer con el resultado (`std::vector<long long>` de distancias) para responder la pregunta concreta.

> Pregunta para pensar: si en vez de "el más caro de alcanzar" te pidieran "la ruta completa hacia el más caro", ¿qué tendrías que agregarle a Dijkstra? (Pista: mirar el ejercicio de camino más corto de la clase anterior.)



## Ejercicio 7 — Calcular flujo máximo con Edmonds-Karp

Dada una red de flujo representada con una matriz de capacidades, y los vértices `fuente` y `sumidero`, calcular el flujo máximo entre ambos.

### Solución

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
                if (v == sumidero) return true;
                visitado[v] = true;
                cola.push(v);
            }
        }
    }
    return false;
}

int edmondsKarp(std::vector<std::vector<int>> capacidad, int fuente, int sumidero) {
    int n = capacidad.size();
    std::vector<std::vector<int>> flujo(n, std::vector<int>(n, 0));
    std::vector<int> padre(n);
    int flujoMaximo = 0;

    while (bfsResidual(capacidad, flujo, fuente, sumidero, padre)) {
        int cuelloDeBotella = std::numeric_limits<int>::max();
        for (int v = sumidero; v != fuente; v = padre[v]) {
            int u = padre[v];
            cuelloDeBotella = std::min(cuelloDeBotella, capacidad[u][v] - flujo[u][v]);
        }

        for (int v = sumidero; v != fuente; v = padre[v]) {
            int u = padre[v];
            flujo[u][v] += cuelloDeBotella;
            flujo[v][u] -= cuelloDeBotella; // arista residual inversa, para poder "deshacer"
        }

        flujoMaximo += cuelloDeBotella;
    }
    return flujoMaximo;
}
```

Cada vuelta del `while` busca un camino aumentante con BFS y lo satura al máximo posible (el cuello de botella). El algoritmo termina cuando ya no queda ningún camino con capacidad residual disponible desde la fuente hasta el sumidero.



## Ejercicio 8 — Identificar el corte mínimo

Usando la red de flujo del ejercicio anterior, una vez calculado el flujo máximo, identificar las aristas que forman el **corte mínimo** (el conjunto de aristas de menor capacidad total que, al eliminarse, desconecta a la fuente del sumidero).

### Solución

```cpp
#include <vector>
#include <queue>

std::vector<std::pair<int,int>> cortesMinimos(std::vector<std::vector<int>> capacidad, int fuente, int sumidero) {
    int n = capacidad.size();
    std::vector<std::vector<int>> flujo(n, std::vector<int>(n, 0));
    std::vector<int> padre(n);

    // 1) corremos Edmonds-Karp hasta el final, igual que en el ejercicio 7
    while (bfsResidual(capacidad, flujo, fuente, sumidero, padre)) {
        int cuelloDeBotella = std::numeric_limits<int>::max();
        for (int v = sumidero; v != fuente; v = padre[v]) {
            int u = padre[v];
            cuelloDeBotella = std::min(cuelloDeBotella, capacidad[u][v] - flujo[u][v]);
        }
        for (int v = sumidero; v != fuente; v = padre[v]) {
            int u = padre[v];
            flujo[u][v] += cuelloDeBotella;
            flujo[v][u] -= cuelloDeBotella;
        }
    }

    // 2) BFS final sobre el grafo residual: qué vértices siguen siendo alcanzables desde la fuente
    std::vector<bool> alcanzable(n, false);
    std::queue<int> cola;
    cola.push(fuente);
    alcanzable[fuente] = true;

    while (!cola.empty()) {
        int u = cola.front();
        cola.pop();
        for (int v = 0; v < n; v++) {
            if (!alcanzable[v] && capacidad[u][v] - flujo[u][v] > 0) {
                alcanzable[v] = true;
                cola.push(v);
            }
        }
    }

    // 3) las aristas del corte mínimo son las originales que cruzan de "alcanzable" a "no alcanzable"
    std::vector<std::pair<int,int>> aristasDeCorte;
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (alcanzable[u] && !alcanzable[v] && capacidad[u][v] > 0) {
                aristasDeCorte.push_back({u, v});
            }
        }
    }
    return aristasDeCorte;
}
```

La clave del ejercicio es el paso 2: una vez que Edmonds-Karp termina (no hay más caminos aumentantes), el conjunto de vértices alcanzables desde la fuente **en el grafo residual** define un lado del corte mínimo. Por el teorema max-flow min-cut, la suma de capacidades de las aristas originales que cruzan de ese conjunto hacia el resto es exactamente igual al flujo máximo calculado.

> Pregunta para pensar: ¿por qué ninguna arista del corte mínimo puede tener capacidad residual disponible una vez que el algoritmo terminó?



## Ejercicios propuestos

1. Modificar Kruskal para que, además de devolver el peso total del AGM, devuelva la lista de aristas elegidas.
2. Dado un grafo con pesos posiblemente negativos, usar Bellman-Ford para determinar, para cada vértice, si su distancia mínima desde el origen es "infinitamente negativa" (es decir, si es alcanzable desde algún ciclo negativo).
