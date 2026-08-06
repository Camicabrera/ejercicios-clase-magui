Tut 12 – Ejercicios: Programación dinámica y NP
===

Estos ejercicios practican el diseño de soluciones de programación dinámica: identificar el estado, escribir la recurrencia, e implementarla tanto top-down (memoización) como bottom-up (tabulación) en C++. El último ejercicio es conceptual, sobre P y NP.

> Tip general: para cada ejercicio, antes de mirar la solución, escribí en una hoja **cuál es el estado** y **cuál es la recurrencia**. Si podés responder esas dos preguntas, el código sale casi solo.


## Ejercicio 1 - Fibonacci con memoización (top-down)

Implementar el cálculo del n-ésimo número de Fibonacci usando **memoización** (top-down), evitando la recomputación exponencial de la versión recursiva ingenua.

### Solución

```cpp
#include <vector>
#include <iostream>

int fibMemo(int n, std::vector<int>& memo) {
    if (n <= 1) return n; // caso base

    if (memo[n] != -1) return memo[n]; // ya calculado, lo reutilizo

    memo[n] = fibMemo(n - 1, memo) + fibMemo(n - 2, memo);
    return memo[n];
}

int fibonacci(int n) {
    std::vector<int> memo(n + 1, -1); // -1 = "no calculado todavía"
    return fibMemo(n, memo);
}

int main() {
    std::cout << fibonacci(30) << "\n"; // 832040, instantáneo
    return 0;
}
```

Costo: **O(n)** en tiempo y en memoria (cada subproblema `fibMemo(k)` se calcula una única vez).


## Ejercicio 2 - Fibonacci con tabulación (bottom-up)

Implementar el mismo cálculo, pero de forma **iterativa** (sin recursión), llenando una tabla de abajo hacia arriba.

### Solución

```cpp
#include <vector>
#include <iostream>

int fibonacciTabulado(int n) {
    if (n <= 1) return n;

    std::vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2]; // dp[i] solo depende de los dos anteriores
    }
    return dp[n];
}

int main() {
    std::cout << fibonacciTabulado(30) << "\n"; // 832040
    return 0;
}
```

> Como `dp[i]` solo depende de `dp[i-1]` y `dp[i-2]`, se podría optimizar la memoria a `O(1)` guardando solo los dos últimos valores. Esa optimización se llama **rolling array** y es un paso extra frecuente después de escribir la versión tabulada básica.


## Ejercicio 3 - Mochila 0/1

Dados `n` objetos con peso y valor, y una capacidad `W`, elegir un subconjunto de objetos (sin fraccionar) que **maximice el valor total** sin superar `W`.

### Solución

Estado: `(i, cap)` = "máximo valor posible considerando los objetos desde `i` en adelante, con `cap` de capacidad disponible".

```cpp
#include <vector>
#include <algorithm>
#include <iostream>

int mochila01(int capacidad, const std::vector<int>& peso, const std::vector<int>& valor) {
    int n = (int)peso.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(capacidad + 1, 0));
    // dp[i][cap]: máximo valor usando objetos desde i en adelante, con capacidad cap

    for (int i = n - 1; i >= 0; i--) {
        for (int cap = 0; cap <= capacidad; cap++) {
            if (peso[i] > cap) {
                dp[i][cap] = dp[i + 1][cap]; // no entra, no lo puedo llevar
            } else {
                int noLoLlevo = dp[i + 1][cap];
                int loLlevo = valor[i] + dp[i + 1][cap - peso[i]];
                dp[i][cap] = std::max(noLoLlevo, loLlevo);
            }
        }
    }
    return dp[0][capacidad];
}

int main() {
    std::vector<int> peso  = {2, 3, 4, 5};
    std::vector<int> valor = {3, 4, 5, 6};
    std::cout << mochila01(5, peso, valor) << "\n"; // 7 (objetos de peso 2 y 3)
    return 0;
}
```

Costo: **O(n * W)** en tiempo y memoria (pseudo-polinomial).


## Ejercicio 4 - Subsecuencia común más larga (LCS)

Dadas dos strings, encontrar la longitud de su **subsecuencia común más larga**.

### Solución

Estado: `(i, j)` = "longitud de la LCS entre el sufijo de `A` desde `i` y el sufijo de `B` desde `j`".

```cpp
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

int lcs(const std::string& A, const std::string& B) {
    int n = (int)A.size(), m = (int)B.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));

    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            if (A[i] == B[j]) {
                dp[i][j] = 1 + dp[i + 1][j + 1]; // coinciden: avanzo en ambas strings
            } else {
                dp[i][j] = std::max(dp[i + 1][j], dp[i][j + 1]); // salteo un carácter de una de las dos
            }
        }
    }
    return dp[0][0];
}

int main() {
    std::cout << lcs("ABCBDAB", "BDCABA") << "\n"; // 4 (por ejemplo: BCBA)
    return 0;
}
```

Costo: **O(n * m)**.


## Ejercicio 5 - Cambio de monedas: mínimo número de monedas

Dado un sistema de monedas (valores arbitrarios) y un `target`, encontrar la **mínima cantidad de monedas** para completar exactamente ese monto, o determinar que no es posible.

### Solución

Estado: `m` = "mínima cantidad de monedas para completar el monto `m`".

```cpp
#include <vector>
#include <algorithm>
#include <climits>
#include <iostream>

int minMonedas(const std::vector<int>& monedas, int target) {
    std::vector<int> dp(target + 1, INT_MAX);
    dp[0] = 0; // completar 0 no requiere monedas

    for (int m = 1; m <= target; m++) {
        for (int moneda : monedas) {
            if (moneda <= m && dp[m - moneda] != INT_MAX) {
                dp[m] = std::min(dp[m], 1 + dp[m - moneda]);
            }
        }
    }
    return (dp[target] == INT_MAX) ? -1 : dp[target];
}

int main() {
    std::vector<int> monedas = {1, 3, 4};
    std::cout << minMonedas(monedas, 6) << "\n"; // 2 (3 + 3)

    std::vector<int> otroSistema = {2, 5};
    std::cout << minMonedas(otroSistema, 3) << "\n"; // -1 (no se puede completar 3)
    return 0;
}
```

Costo: **O(target * cantidadMonedas)**.


## Ejercicio 6 - Subsecuencia creciente más larga (LIS)

Dado un `std::vector<int>`, encontrar la longitud de la **subsecuencia creciente más larga** (no necesariamente contigua).

### Solución

Estado: `i` = "longitud de la subsecuencia creciente más larga que **termina** en la posición `i`".

```
lis(i) = 1 + max( lis(j) )  para todo j < i tal que v[j] < v[i]
lis(i) = 1                  si no existe ningún j que cumpla la condición
```

```cpp
#include <vector>
#include <algorithm>
#include <iostream>

int lis(const std::vector<int>& v) {
    int n = (int)v.size();
    std::vector<int> dp(n, 1); // toda posición tiene, como mínimo, una LIS de longitud 1 (ella misma)

    int mejor = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (v[j] < v[i]) {
                dp[i] = std::max(dp[i], 1 + dp[j]);
            }
        }
        mejor = std::max(mejor, dp[i]);
    }
    return mejor;
}

int main() {
    std::vector<int> v = {10, 9, 2, 5, 3, 7, 101, 18};
    std::cout << lis(v) << "\n"; // 4 (por ejemplo: 2, 3, 7, 101 o 2, 5, 7, 18)
    return 0;
}
```

Costo: **O(n^2)** con esta versión (existe una versión **O(n log n)** usando búsqueda binaria, que queda como desafío adicional).


## Ejercicio 7 - Distancia de edición (Levenshtein)

Dadas dos strings `A` y `B`, encontrar la **mínima cantidad de operaciones** (insertar, borrar o reemplazar un carácter) para transformar `A` en `B`.

### Solución

Estado: `(i, j)` = "distancia de edición entre el sufijo de `A` desde `i` y el sufijo de `B` desde `j`".

```
distancia(i, j) = |B| - j                                    si i == |A| (insertar el resto de B)
distancia(i, j) = |A| - i                                    si j == |B| (borrar el resto de A)
distancia(i, j) = distancia(i+1, j+1)                         si A[i] == B[j]
distancia(i, j) = 1 + min( distancia(i+1, j),    // borrar A[i]
                            distancia(i, j+1),    // insertar B[j]
                            distancia(i+1, j+1) ) // reemplazar A[i] por B[j]
                                                               si A[i] != B[j]
```

```cpp
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

int distanciaEdicion(const std::string& A, const std::string& B) {
    int n = (int)A.size(), m = (int)B.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));

    // Casos base: transformar un sufijo vacío de A en el resto de B (solo inserciones)
    for (int j = 0; j <= m; j++) dp[n][j] = m - j;
    // Casos base: transformar el resto de A en un sufijo vacío de B (solo borrados)
    for (int i = 0; i <= n; i++) dp[i][m] = n - i;

    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            if (A[i] == B[j]) {
                dp[i][j] = dp[i + 1][j + 1];
            } else {
                int borrar = dp[i + 1][j];
                int insertar = dp[i][j + 1];
                int reemplazar = dp[i + 1][j + 1];
                dp[i][j] = 1 + std::min({borrar, insertar, reemplazar});
            }
        }
    }
    return dp[0][0];
}

int main() {
    std::cout << distanciaEdicion("caballo", "cebolla") << "\n"; // 4
    return 0;
}
```

Costo: **O(n * m)**.


## Ejercicio 8 - Conceptual: ¿por qué el TSP es NP-hard?

Explicar, en términos intuitivos (sin una demostración formal), por qué el **problema del viajante de comercio (TSP)** se considera NP-hard, y por qué esto no impide que en la práctica se resuelvan instancias razonablemente grandes.

### Solución (discusión)

**¿Por qué es NP-hard?** El TSP (encontrar el circuito de costo mínimo que visita todas las ciudades exactamente una vez) se puede reducir desde problemas ya conocidos como NP-completos, como el **ciclo hamiltoniano** (¿existe un circuito que visite cada nodo exactamente una vez?, sin importar el costo): dado un grafo, se construye una instancia de TSP donde las aristas del grafo original tienen costo 1 y las que no existen tienen un costo muy alto (por ejemplo, mayor a `n`). Si la solución óptima de TSP tiene costo `n` (la cantidad de nodos), entonces existe un ciclo hamiltoniano en el grafo original; si el óptimo es mayor, no existe. Como el ciclo hamiltoniano es NP-completo, y lo pudimos reducir (en tiempo polinomial) a una instancia de TSP, TSP es al menos tan difícil: es **NP-hard**.

Además, la única forma conocida de garantizar la solución **óptima** exacta de TSP para una instancia arbitraria es, en esencia, probar (con distinto grado de poda) las `(n-1)!/2` rutas posibles: no se conoce ningún algoritmo polinomial que lo resuelva siempre de forma óptima.

**¿Por qué igual se resuelve en la práctica?**

- Para instancias **chicas o medianas**, backtracking con poda (o programación dinámica tipo Held-Karp, que baja el costo a `O(n^2 * 2^n)`, mucho mejor que `n!` pero igual exponencial) alcanza para resolver el óptimo exacto en tiempo razonable.
- Para instancias **grandes**, se usan **heurísticas y algoritmos de aproximación** (por ejemplo, vecino más cercano, o algoritmos basados en el árbol de tendido mínimo) que no garantizan el óptimo, pero dan soluciones "suficientemente buenas" en tiempo polinomial.
- En muchos casos reales, las instancias tienen estructura adicional (por ejemplo, cumplen la desigualdad triangular) que permite algoritmos de aproximación con garantías teóricas sobre qué tan lejos del óptimo pueden estar.

> La lección general es la misma que cerramos en la sección de P y NP: que un problema sea NP-hard no significa "imposible de resolver en la práctica", significa que no hay garantía de un algoritmo exacto rápido para **todas** las instancias. Backtracking, PD pseudo-polinomial y heurísticas siguen siendo, en conjunto, las herramientas con las que se ataca este tipo de problemas.


## Ejercicios propuestos

1. Optimizar el Ejercicio 6 (LIS) para que corra en **O(n log n)** en lugar de O(n^2), usando búsqueda binaria sobre un vector auxiliar que mantiene el menor valor final posible para cada longitud de subsecuencia encontrada hasta el momento.
2. Elegir un problema NP-hard que no se haya visto en la clase (por ejemplo, **subset sum** con el objetivo de decisión, o **vertex cover**) y explicar, con el mismo estilo que el Ejercicio 8, desde qué problema conocido se podría reducir para demostrar que es NP-hard.
