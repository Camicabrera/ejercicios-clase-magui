Tut 09 – Ejercicios de Grafos I
===

En esta guía vamos a practicar representación de grafos con `std::vector<std::vector<int>>` (lista de adyacencia) y sus dos recorridos clásicos, BFS y DFS, aplicados a problemas típicos de parciales. Todos los ejercicios asumen vértices numerados de `0` a `n-1`.

> Tip: antes de programar cualquier ejercicio de grafos, preguntate: ¿es dirigido o no dirigido? ¿ponderado o no ponderado? ¿conexo o puede tener varias componentes? Esas respuestas determinan el algoritmo a usar.



## Ejercicio 1 — Implementar BFS

Implementar una función que, dado un grafo no dirigido (lista de adyacencia) y un vértice de inicio, devuelva un `std::vector<int>` con el orden en que BFS visita los vértices.

### Solución

```cpp
#include <vector>
#include <queue>

std::vector<int> bfsOrden(const std::vector<std::vector<int>>& adj, int inicio) {
    int n = adj.size();
    std::vector<bool> visitado(n, false);
    std::vector<int> orden;
    std::queue<int> cola;

    visitado[inicio] = true;
    cola.push(inicio);

    while (!cola.empty()) {
        int actual = cola.front();
        cola.pop();
        orden.push_back(actual); // registramos el orden de visita

        for (int vecino : adj[actual]) {
            if (!visitado[vecino]) {
                visitado[vecino] = true; // marcamos ni bien se encola (no al desencolar)
                cola.push(vecino);
            }
        }
    }
    return orden;
}
```

Marcamos `visitado[vecino] = true` en el momento de encolar (no de desencolar), para evitar encolar el mismo vértice varias veces desde distintos vecinos.



## Ejercicio 2 — Implementar DFS recursivo

Implementar DFS recursivo que devuelva el orden de visita, partiendo de un vértice inicial.

### Solución

```cpp
#include <vector>

void dfsAux(const std::vector<std::vector<int>>& adj, int actual, std::vector<bool>& visitado, std::vector<int>& orden) {
    visitado[actual] = true;
    orden.push_back(actual);

    for (int vecino : adj[actual]) {
        if (!visitado[vecino]) {
            dfsAux(adj, vecino, visitado, orden);
        }
    }
}

std::vector<int> dfsOrden(const std::vector<std::vector<int>>& adj, int inicio) {
    int n = adj.size();
    std::vector<bool> visitado(n, false);
    std::vector<int> orden;

    dfsAux(adj, inicio, visitado, orden);
    return orden;
}
```

Usamos una función auxiliar (`dfsAux`) para no tener que reconstruir el vector `visitado` en cada llamada recursiva.



## Ejercicio 3 — Contar componentes conexas

Dado un grafo **no dirigido** que puede no ser conexo, contar cuántas componentes conexas tiene.

### Solución

```cpp
#include <vector>
#include <queue>

int contarComponentes(const std::vector<std::vector<int>>& adj) {
    int n = adj.size();
    std::vector<bool> visitado(n, false);
    int componentes = 0;

    for (int v = 0; v < n; v++) {
        if (visitado[v]) continue; // ya pertenece a una componente ya contada

        componentes++;
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
    return componentes;
}
```

La clave es el `for` externo: recorremos **todos** los vértices por si el grafo no es conexo, y cada vez que encontramos uno sin visitar, lanzamos un BFS que cubre toda su componente.



## Ejercicio 4 — Detectar ciclo en grafo no dirigido

Dado un grafo no dirigido, determinar si contiene al menos un ciclo.

### Solución

```cpp
#include <vector>

bool dfsCiclo(const std::vector<std::vector<int>>& adj, int actual, int padre, std::vector<bool>& visitado) {
    visitado[actual] = true;

    for (int vecino : adj[actual]) {
        if (!visitado[vecino]) {
            if (dfsCiclo(adj, vecino, actual, visitado)) return true;
        } else if (vecino != padre) {
            // llegamos a un vecino visitado que no es por donde vinimos -> ciclo
            return true;
        }
    }
    return false;
}

bool tieneCiclo(const std::vector<std::vector<int>>& adj) {
    int n = adj.size();
    std::vector<bool> visitado(n, false);

    for (int v = 0; v < n; v++) {
        if (!visitado[v]) {
            if (dfsCiclo(adj, v, -1, visitado)) return true;
        }
    }
    return false;
}
```

Recorremos todas las componentes (por si el grafo no es conexo) y en cada DFS llevamos el `padre` para no confundir la arista de ida con un ciclo real.



## Ejercicio 5 — Detectar ciclo en grafo dirigido

Dado un grafo dirigido, determinar si contiene al menos un ciclo.

### Solución

```cpp
#include <vector>

bool dfsCicloDirigido(const std::vector<std::vector<int>>& adj, int actual, std::vector<int>& estado) {
    estado[actual] = 1; // 1 = en proceso (en la pila de recursión actual)

    for (int vecino : adj[actual]) {
        if (estado[vecino] == 1) return true; // es un ancestro en el camino actual -> ciclo
        if (estado[vecino] == 0 && dfsCicloDirigido(adj, vecino, estado)) return true;
    }

    estado[actual] = 2; // 2 = terminado
    return false;
}

bool tieneCicloDirigido(const std::vector<std::vector<int>>& adj) {
    int n = adj.size();
    std::vector<int> estado(n, 0); // 0 = no visitado, 1 = en proceso, 2 = terminado

    for (int v = 0; v < n; v++) {
        if (estado[v] == 0) {
            if (dfsCicloDirigido(adj, v, estado)) return true;
        }
    }
    return false;
}
```

A diferencia del caso no dirigido, acá **no alcanza** con `visitado`/`no visitado`: un vecino visitado en una rama anterior del DFS no implica ciclo. Por eso usamos 3 estados.



## Ejercicio 6 — Orden topológico (Kahn)

Dado un DAG (grafo dirigido acíclico) que representa dependencias entre tareas (`u -> v` significa "u debe hacerse antes que v"), devolver un orden válido para realizar las tareas. Si el grafo tiene un ciclo, devolver un vector vacío.

### Solución

```cpp
#include <vector>
#include <queue>

std::vector<int> ordenTopologico(const std::vector<std::vector<int>>& adj) {
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

    if ((int)orden.size() != n) {
        return {}; // no se pudieron ordenar todos los vértices -> había un ciclo
    }
    return orden;
}
```

Si al final `orden` no incluye a todos los vértices, es porque quedaron vértices con grado de entrada positivo, atrapados en un ciclo: por eso devolvemos un vector vacío.



## Ejercicio 7 — Verificar si un grafo es bipartito

Un grafo es **bipartito** si sus vértices se pueden dividir en dos conjuntos de forma que toda arista una un vértice de un conjunto con uno del otro (equivalente a poder "pintarlo" con 2 colores sin que dos vecinos compartan color).

### Solución

```cpp
#include <vector>
#include <queue>

bool esBipartito(const std::vector<std::vector<int>>& adj) {
    int n = adj.size();
    std::vector<int> color(n, -1); // -1 = sin color, 0 o 1 = colores

    for (int inicio = 0; inicio < n; inicio++) {
        if (color[inicio] != -1) continue; // ya coloreado en una componente anterior

        color[inicio] = 0;
        std::queue<int> cola;
        cola.push(inicio);

        while (!cola.empty()) {
            int actual = cola.front();
            cola.pop();

            for (int vecino : adj[actual]) {
                if (color[vecino] == -1) {
                    color[vecino] = 1 - color[actual]; // color opuesto al actual
                    cola.push(vecino);
                } else if (color[vecino] == color[actual]) {
                    return false; // dos vecinos con el mismo color -> no es bipartito
                }
            }
        }
    }
    return true;
}
```

Hacemos BFS "pintando" cada vecino con el color opuesto al actual. Si en algún momento un vecino ya coloreado tiene el **mismo** color que el vértice actual, el grafo no es bipartito. Recorremos todas las componentes por si el grafo no es conexo.



## Ejercicio 8 — Camino más corto en grafo no ponderado

Dado un grafo no dirigido y no ponderado, y dos vértices `origen` y `destino`, devolver la secuencia de vértices del camino más corto entre ambos (o un vector vacío si no hay camino).

### Solución

```cpp
#include <vector>
#include <queue>
#include <algorithm>

std::vector<int> caminoMasCorto(const std::vector<std::vector<int>>& adj, int origen, int destino) {
    int n = adj.size();
    std::vector<int> distancia(n, -1);
    std::vector<int> padre(n, -1);
    std::queue<int> cola;

    distancia[origen] = 0;
    cola.push(origen);

    while (!cola.empty()) {
        int actual = cola.front();
        cola.pop();

        if (actual == destino) break; // ya encontramos el destino, podemos cortar

        for (int vecino : adj[actual]) {
            if (distancia[vecino] == -1) {
                distancia[vecino] = distancia[actual] + 1;
                padre[vecino] = actual;
                cola.push(vecino);
            }
        }
    }

    if (distancia[destino] == -1) return {}; // no hay camino

    // reconstruimos el camino siguiendo los padres, desde destino hacia origen
    std::vector<int> camino;
    for (int v = destino; v != -1; v = padre[v]) {
        camino.push_back(v);
    }
    std::reverse(camino.begin(), camino.end());
    return camino;
}
```

La clave nueva acá es el vector `padre`: además de la distancia, guardamos desde qué vértice llegamos a cada uno, y al final reconstruimos el camino recorriendo los padres hacia atrás.



## Ejercicio 9 — Contar islas en una grilla

Dada una grilla de `0`s y `1`s (`std::vector<std::vector<int>>` donde `1` = tierra y `0` = agua), contar la cantidad de "islas": grupos de `1`s conectados horizontal o verticalmente (no en diagonal).

### Solución

La idea es tratar la grilla como un grafo implícito: cada celda de tierra es un vértice, y hay una arista entre dos celdas de tierra adyacentes (arriba, abajo, izquierda, derecha). En vez de armar una lista de adyacencia explícita, calculamos los vecinos "al vuelo" con los desplazamientos `dx`, `dy`.

```cpp
#include <vector>

void dfsIsla(std::vector<std::vector<int>>& grilla, int fila, int columna) {
    int filas = grilla.size();
    int columnas = grilla[0].size();

    // fuera de rango o ya no es tierra (agua o ya visitada)
    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) return;
    if (grilla[fila][columna] != 1) return;

    grilla[fila][columna] = 0; // "hundimos" la celda para marcarla como visitada

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    for (int d = 0; d < 4; d++) {
        dfsIsla(grilla, fila + dx[d], columna + dy[d]);
    }
}

int contarIslas(std::vector<std::vector<int>> grilla) {
    int filas = grilla.size();
    int columnas = grilla[0].size();
    int islas = 0;

    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            if (grilla[f][c] == 1) {
                islas++;
                dfsIsla(grilla, f, c); // "apaga" toda la isla conectada a esta celda
            }
        }
    }
    return islas;
}
```

Recibimos la grilla **por copia** (no por referencia) para poder modificarla libremente sin afectar la grilla original del que llama a la función. Cada vez que encontramos una celda de tierra no visitada, contamos una isla nueva y usamos DFS para "apagar" (marcar como agua) toda la isla conectada.

> Pregunta para pensar: ¿cómo cambiaría la solución si las islas también se consideraran conectadas en diagonal?



## Ejercicios propuestos

1. Dado un grafo dirigido, determinar si existe al menos un camino entre cada par de vértices que tenga grado de salida 0 y algún vértice con grado de entrada 0 (es decir, si el DAG tiene una única "fuente" y un único "sumidero" alcanzables entre sí).
2. Dada una grilla de `0`s y `1`s, en vez de contar la cantidad de islas, devolver el **tamaño de la isla más grande** (cantidad de celdas de tierra conectadas).
