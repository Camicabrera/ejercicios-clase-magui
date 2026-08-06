Tut 11 – Ejercicios: Fuerza bruta, Backtracking y Greedy
===

A continuación hay una serie de ejercicios de dificultad creciente para practicar las tres estrategias vistas en el tutorial: fuerza bruta, backtracking y greedy. Para cada uno primero pensá tu propia solución en C++ antes de leer la solución propuesta.

> Tip general: antes de programar, identificá siempre **cuáles son las decisiones** que se toman paso a paso y **cuándo una decisión parcial deja de tener sentido** (eso es la poda).


## Ejercicio 1 - Generar todos los subconjuntos (fuerza bruta)

Escribir una función que reciba un `std::vector<int>` y devuelva **todos sus subconjuntos** (el conjunto potencia), como un `std::vector<std::vector<int>>`.

### Solución

```cpp
#include <iostream>
#include <vector>

void generarSubconjuntos(const std::vector<int>& elementos, int i,
                          std::vector<int>& parcial,
                          std::vector<std::vector<int>>& resultado) {
    if (i == (int)elementos.size()) {
        resultado.push_back(parcial); // copio la solución parcial completa
        return;
    }

    // No incluyo elementos[i]
    generarSubconjuntos(elementos, i + 1, parcial, resultado);

    // Incluyo elementos[i]
    parcial.push_back(elementos[i]);
    generarSubconjuntos(elementos, i + 1, parcial, resultado);
    parcial.pop_back(); // deshago para no arrastrar el elemento a otras ramas
}

std::vector<std::vector<int>> subconjuntos(const std::vector<int>& elementos) {
    std::vector<std::vector<int>> resultado;
    std::vector<int> parcial;
    generarSubconjuntos(elementos, 0, parcial, resultado);
    return resultado;
}

int main() {
    std::vector<int> v = {1, 2, 3};
    auto todos = subconjuntos(v);
    std::cout << "Cantidad de subconjuntos: " << todos.size() << "\n"; // 2^3 = 8
    return 0;
}
```

Costo: **O(2^n)** llamadas, cada una copiando hasta `n` elementos, así que **O(n * 2^n)** en total.


## Ejercicio 2 - Generar todas las permutaciones (fuerza bruta)

Escribir una función que reciba un `std::vector<int>` sin repetidos y devuelva **todas sus permutaciones**.

### Solución

```cpp
#include <iostream>
#include <vector>

void generarPermutaciones(std::vector<int>& elementos, int inicio,
                           std::vector<std::vector<int>>& resultado) {
    if (inicio == (int)elementos.size()) {
        resultado.push_back(elementos);
        return;
    }

    for (int i = inicio; i < (int)elementos.size(); i++) {
        std::swap(elementos[inicio], elementos[i]);
        generarPermutaciones(elementos, inicio + 1, resultado);
        std::swap(elementos[inicio], elementos[i]); // deshago el swap
    }
}

int main() {
    std::vector<int> v = {1, 2, 3};
    std::vector<std::vector<int>> resultado;
    generarPermutaciones(v, 0, resultado);
    std::cout << "Cantidad de permutaciones: " << resultado.size() << "\n"; // 3! = 6
    return 0;
}
```

Costo: **O(n!)** permutaciones, cada una tomando **O(n)** para construirse: **O(n * n!)**.


## Ejercicio 3 - N-reinas (backtracking con poda)

Dado un tablero de `n x n`, colocar `n` reinas de forma que **ninguna ataque a otra** (ni misma fila, ni misma columna, ni misma diagonal). Contar cuántas soluciones existen.

### Solución

Colocamos una reina por fila, y en cada fila probamos todas las columnas, podando las que generan un ataque con una reina ya puesta.

```cpp
#include <iostream>
#include <vector>

bool esValida(const std::vector<int>& columnas, int fila, int col) {
    for (int f = 0; f < fila; f++) {
        int c = columnas[f];
        if (c == col) return false;                      // misma columna
        if (std::abs(c - col) == std::abs(f - fila)) return false; // misma diagonal
    }
    return true;
}

void resolverNReinas(int n, int fila, std::vector<int>& columnas, int& soluciones) {
    if (fila == n) {
        soluciones++; // caso base: coloqué las n reinas sin conflictos
        return;
    }

    for (int col = 0; col < n; col++) {
        if (esValida(columnas, fila, col)) { // PODA
            columnas[fila] = col;             // tomo la decisión
            resolverNReinas(n, fila + 1, columnas, soluciones);
            // no hace falta "deshacer" columnas[fila]: se sobreescribe en la próxima iteración
        }
    }
}

int contarSolucionesNReinas(int n) {
    std::vector<int> columnas(n, -1);
    int soluciones = 0;
    resolverNReinas(n, 0, columnas, soluciones);
    return soluciones;
}

int main() {
    std::cout << "Soluciones para 8 reinas: " << contarSolucionesNReinas(8) << "\n"; // 92
    return 0;
}
```

> La poda en `esValida` es lo que hace viable este algoritmo: sin ella estaríamos probando las `n^n` formas de ubicar reinas en el tablero.


## Ejercicio 4 - Suma de subconjuntos (backtracking)

Dado un `std::vector<int>` y un `target`, determinar si existe algún subconjunto cuya suma sea exactamente `target`.

### Solución

```cpp
#include <iostream>
#include <vector>

bool sumaSubconjuntos(const std::vector<int>& elementos, int i, int sumaActual, int target) {
    if (sumaActual == target) return true;          // encontré una solución
    if (i == (int)elementos.size() || sumaActual > target) {
        return false; // PODA: me pasé del target, o no quedan elementos
    }

    // Rama 1: incluyo elementos[i]
    if (sumaSubconjuntos(elementos, i + 1, sumaActual + elementos[i], target)) return true;

    // Rama 2: no incluyo elementos[i]
    return sumaSubconjuntos(elementos, i + 1, sumaActual, target);
}

int main() {
    std::vector<int> v = {3, 34, 4, 12, 5, 2};
    std::cout << std::boolalpha;
    std::cout << sumaSubconjuntos(v, 0, 0, 9) << "\n";  // true (4 + 5)
    std::cout << sumaSubconjuntos(v, 0, 0, 100) << "\n"; // false
    return 0;
}
```

> La poda clave acá es `sumaActual > target`: si asumimos que todos los elementos son positivos, cortamos apenas nos pasamos, sin seguir agregando elementos inútilmente.


## Ejercicio 5 - Resolver un laberinto con backtracking

Dada una grilla de `n x m` con celdas libres (`0`) y bloqueadas (`1`), determinar si existe un camino desde `(0,0)` hasta `(n-1, m-1)` moviéndose en las 4 direcciones, sin pasar dos veces por la misma celda.

### Solución

```cpp
#include <iostream>
#include <vector>

bool resolverLaberinto(std::vector<std::vector<int>>& grilla,
                        std::vector<std::vector<bool>>& visitado,
                        int fila, int col) {
    int n = (int)grilla.size(), m = (int)grilla[0].size();

    // PODA: fuera de rango, bloqueada, o ya visitada
    if (fila < 0 || fila >= n || col < 0 || col >= m) return false;
    if (grilla[fila][col] == 1 || visitado[fila][col]) return false;

    if (fila == n - 1 && col == m - 1) return true; // llegué al destino

    visitado[fila][col] = true; // marco como parte del camino actual

    int dFila[] = {-1, 1, 0, 0};
    int dCol[]  = {0, 0, -1, 1};
    for (int d = 0; d < 4; d++) {
        if (resolverLaberinto(grilla, visitado, fila + dFila[d], col + dCol[d])) {
            return true; // encontré un camino, no hace falta seguir buscando
        }
    }

    visitado[fila][col] = false; // backtrack: esta celda no llevó a ninguna solución
    return false;
}

int main() {
    std::vector<std::vector<int>> grilla = {
        {0, 1, 0},
        {0, 0, 0},
        {1, 1, 0}
    };
    std::vector<std::vector<bool>> visitado(grilla.size(),
                                             std::vector<bool>(grilla[0].size(), false));
    std::cout << std::boolalpha << resolverLaberinto(grilla, visitado, 0, 0) << "\n"; // true
    return 0;
}
```

> Notar el `visitado[fila][col] = false;` al final: es el paso de **backtrack** propiamente dicho. Si no lo hiciéramos, una celda que no funcionó para un camino quedaría marcada como visitada para siempre, incluso para caminos que pasan por otro lado y sí podrían usarla.


## Ejercicio 6 - Coloreo de grafos con backtracking

Dado un grafo no dirigido (representado como matriz de adyacencia) y un número `k` de colores, determinar si se puede colorear cada nodo con uno de los `k` colores de forma que **ningún par de nodos adyacentes tenga el mismo color**.

### Solución

```cpp
#include <iostream>
#include <vector>

bool colorValido(const std::vector<std::vector<int>>& grafo,
                  const std::vector<int>& color, int nodo, int c) {
    for (int vecino = 0; vecino < (int)grafo.size(); vecino++) {
        if (grafo[nodo][vecino] == 1 && color[vecino] == c) {
            return false; // un vecino ya tiene ese color
        }
    }
    return true;
}

bool colorearGrafo(const std::vector<std::vector<int>>& grafo, int k,
                    std::vector<int>& color, int nodo) {
    int n = (int)grafo.size();
    if (nodo == n) return true; // coloreé todos los nodos sin conflictos

    for (int c = 0; c < k; c++) {
        if (colorValido(grafo, color, nodo, c)) { // PODA
            color[nodo] = c;
            if (colorearGrafo(grafo, k, color, nodo + 1)) return true;
            color[nodo] = -1; // backtrack
        }
    }
    return false;
}

int main() {
    // Grafo: triángulo (0-1-2) + nodo 3 conectado solo a 0
    std::vector<std::vector<int>> grafo = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 0},
        {1, 0, 0, 0}
    };
    std::vector<int> color(grafo.size(), -1);
    std::cout << std::boolalpha << colorearGrafo(grafo, 3, color, 0) << "\n"; // true, necesita 3 colores
    return 0;
}
```

> Este problema (**graph coloring**) es NP-completo en general: no se conoce un algoritmo polinomial para resolverlo para cualquier `k` y cualquier grafo. Backtracking con poda es, en la práctica, de las mejores herramientas disponibles.


## Ejercicio 7 - Cambio de monedas con greedy (¿y cuándo falla?)

Dado un sistema de monedas y un monto `target`, usar una estrategia greedy (elegir siempre la moneda más grande posible) para dar el cambio con la menor cantidad de monedas. Mostrar un caso donde esta estrategia **no** da el óptimo.

### Solución

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int cambioGreedy(std::vector<int> monedas, int target) {
    std::sort(monedas.rbegin(), monedas.rend()); // de mayor a menor
    int cantidad = 0;
    for (int m : monedas) {
        while (target >= m) {
            target -= m;
            cantidad++;
        }
    }
    return (target == 0) ? cantidad : -1; // -1 si no se pudo completar exacto
}

int main() {
    // Sistema estándar: greedy funciona bien
    std::vector<int> sistemaEstandar = {25, 10, 5, 1};
    std::cout << cambioGreedy(sistemaEstandar, 30) << "\n"; // 2 (25 + 5) -> óptimo

    // Sistema donde greedy FALLA
    std::vector<int> sistemaMalo = {1, 3, 4};
    std::cout << cambioGreedy(sistemaMalo, 6) << "\n"; // greedy: 4+1+1 = 3 monedas
                                                        // óptimo real: 3+3 = 2 monedas
    return 0;
}
```

> Con el sistema `{1, 3, 4}` y `target = 6`, greedy elige `4` primero (porque es la moneda más grande que entra) y termina necesitando 3 monedas, cuando la solución óptima usa solo 2. Para resolver este problema en general (cualquier sistema de monedas) hace falta **programación dinámica**, tema del próximo tutorial.


## Ejercicio 8 - Selección de actividades (greedy)

Dado un conjunto de actividades, cada una con un horario de inicio y fin, seleccionar la **mayor cantidad posible de actividades que no se superpongan** entre sí.

### Solución

La estrategia greedy correcta es: ordenar las actividades por **horario de fin** y elegir siempre la próxima actividad que empiece después (o al mismo tiempo) de que termine la última elegida.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

struct Actividad {
    int inicio, fin;
};

int seleccionarActividades(std::vector<Actividad> actividades) {
    std::sort(actividades.begin(), actividades.end(),
              [](const Actividad& a, const Actividad& b) {
                  return a.fin < b.fin; // ordeno por horario de fin
              });

    int cantidad = 0;
    int finUltima = -1;
    for (const auto& act : actividades) {
        if (act.inicio >= finUltima) { // no se superpone con la última elegida
            cantidad++;
            finUltima = act.fin;
        }
    }
    return cantidad;
}

int main() {
    std::vector<Actividad> actividades = {
        {1, 4}, {3, 5}, {0, 6}, {5, 7}, {3, 9}, {5, 9}, {6, 10}, {8, 11}, {8, 12}, {2, 14}, {12, 16}
    };
    std::cout << seleccionarActividades(actividades) << "\n"; // 4
    return 0;
}
```

> Elegir por **horario de fin** (y no por duración, ni por horario de inicio) es lo que garantiza el óptimo: siempre dejamos la mayor cantidad de tiempo libre posible para las actividades que siguen. Esta propiedad se puede demostrar con un argumento de intercambio.


## Ejercicio 9 - Mochila fraccional (greedy)

Dados `n` objetos, cada uno con un peso y un valor, y una mochila de capacidad `W`, elegir qué **fracción** de cada objeto llevar (se puede llevar una parte de un objeto) para **maximizar el valor total** sin superar `W`.

### Solución

La estrategia greedy correcta es ordenar los objetos por **relación valor/peso** de mayor a menor, y llenar la mochila tomando primero los de mejor relación (completos mientras entren, y una fracción del que no entra completo).

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

struct Objeto {
    double peso, valor;
};

double mochilaFraccional(std::vector<Objeto> objetos, double capacidad) {
    std::sort(objetos.begin(), objetos.end(),
              [](const Objeto& a, const Objeto& b) {
                  return (a.valor / a.peso) > (b.valor / b.peso); // mejor relación primero
              });

    double valorTotal = 0.0;
    for (const auto& obj : objetos) {
        if (capacidad <= 0) break;

        if (obj.peso <= capacidad) {
            // Entra completo
            valorTotal += obj.valor;
            capacidad -= obj.peso;
        } else {
            // Entra una fracción
            double fraccion = capacidad / obj.peso;
            valorTotal += obj.valor * fraccion;
            capacidad = 0;
        }
    }
    return valorTotal;
}

int main() {
    std::vector<Objeto> objetos = {{10, 60}, {20, 100}, {30, 120}};
    std::cout << mochilaFraccional(objetos, 50) << "\n"; // 240
    return 0;
}
```

> A diferencia de la mochila **0/1** (Ejercicio conceptual del próximo tutorial), acá greedy sí es óptimo porque **se puede fraccionar** el objeto: no hay ninguna decisión "todo o nada" que pueda arruinar la elección local.


## Ejercicios propuestos

1. Modificar el Ejercicio 3 (N-reinas) para que, en lugar de contar las soluciones, devuelva **una** solución válida como un `std::vector<int>` (o indique que no existe).
2. Adaptar el Ejercicio 6 (coloreo de grafos) para que, en lugar de decir si es posible colorear con `k` colores, encuentre el **mínimo** `k` para el cual el grafo es coloreable (probar backtracking con `k = 1, 2, 3, ...` hasta encontrar el primero que funcione).
