Tut 12 – Programación dinámica y NP
===

> **Ingeniería en Inteligencia Artificial** — **Algoritmos y Estructura de Datos**  
> **2C 2026** · Docente: **Magali Marijuan**

- [Tut 12 – Programación dinámica y NP](#tut-12--programación-dinámica-y-np)
- [Objetivos de la clase](#objetivos-de-la-clase)
- [Programación dinámica](#programación-dinámica)
  - [¿Qué es la programación dinámica?](#qué-es-la-programación-dinámica)
  - [Relación con backtracking: memorizar el árbol de decisiones](#relación-con-backtracking-memorizar-el-árbol-de-decisiones)
  - [Top-down (memoización) vs bottom-up (tabulación)](#top-down-memoización-vs-bottom-up-tabulación)
  - [Ejemplo: Fibonacci](#ejemplo-fibonacci)
  - [Ejemplo: mochila 0/1](#ejemplo-mochila-01)
  - [Ejemplo: subsecuencia común más larga (LCS)](#ejemplo-subsecuencia-común-más-larga-lcs)
  - [Ejemplo: cambio de monedas](#ejemplo-cambio-de-monedas)
  - [Cómo identificar el estado y la recurrencia](#cómo-identificar-el-estado-y-la-recurrencia)
- [P y NP](#p-y-np)
  - [La clase P](#la-clase-p)
  - [La clase NP y la verificación en tiempo polinomial](#la-clase-np-y-la-verificación-en-tiempo-polinomial)
  - [NP-completo y reducciones](#np-completo-y-reducciones)
  - [Problemas NP-hard clásicos](#problemas-np-hard-clásicos)
  - [¿Por qué backtracking y heurísticas siguen siendo prácticos?](#por-qué-backtracking-y-heurísticas-siguen-siendo-prácticos)
- [Repaso general](#repaso-general)



# Objetivos de la clase

- Entender qué significa que un problema tenga **subestructura óptima** y **subproblemas superpuestos**.
- Ver la programación dinámica como una forma de **memorizar el árbol de decisiones** de un backtracking para no recomputar.
- Distinguir **top-down (memoización)** de **bottom-up (tabulación)**, e implementarlas en C++ con vectores/matrices.
- Practicar cómo identificar el **estado** y la **recurrencia** de un problema nuevo.
- Tener una idea intuitiva de las clases **P** y **NP**, qué es **NP-completo**, y por qué ciertos problemas (TSP, mochila, clique) son difíciles en la práctica.


# Programación dinámica

## ¿Qué es la programación dinámica?

La **programación dinámica** (PD) es una técnica para resolver problemas que cumplen dos condiciones:

1. **Subestructura óptima**: la solución óptima del problema se puede construir a partir de las soluciones óptimas de subproblemas más chicos.
2. **Subproblemas superpuestos**: al resolver el problema de forma recursiva (por ejemplo, con backtracking), los mismos subproblemas aparecen **una y otra vez**.

> Si un problema tiene subestructura óptima pero **no** tiene subproblemas superpuestos (cada subproblema aparece una sola vez), programación dinámica no aporta nada: ahí alcanza con recursión simple ("divide and conquer", como mergesort).

La idea central de PD es: **resolver cada subproblema una sola vez, guardar el resultado, y reutilizarlo** cada vez que se necesite de nuevo, en lugar de recalcularlo.


## Relación con backtracking: memorizar el árbol de decisiones

Muchos problemas de programación dinámica se pueden plantear primero como un backtracking (fuerza bruta con poda) que prueba todas las decisiones posibles en cada paso. El problema es que ese árbol de decisiones, muchas veces, tiene **ramas repetidas**: distintos caminos de decisiones llegan al **mismo subproblema**.

> Pregunta para pensar: en el árbol de llamadas recursivas de Fibonacci, `fib(5)` llama a `fib(3)` dos veces (una desde `fib(4)` y otra directamente). ¿Cuántas veces se recalcula `fib(2)`? ¿Y `fib(1)`?

La programación dinámica es, en esencia, **backtracking con memoria**: guardamos el resultado de cada subproblema (identificado por su **estado**) la primera vez que lo calculamos, y las próximas veces que aparece **lo reutilizamos** en lugar de recorrer de nuevo todo ese subárbol de decisiones.

```
Backtracking puro:         árbol de decisiones completo (con ramas repetidas)
Programación dinámica:     mismo árbol, pero cada subproblema se resuelve UNA sola vez
```


## Top-down (memoización) vs bottom-up (tabulación)

Hay dos formas equivalentes de implementar programación dinámica:

- **Top-down (memoización)**: se mantiene la recursión tal cual, pero antes de calcular un subproblema se chequea si ya está resuelto en una estructura de memoria (típicamente un `std::vector` o una matriz). Si ya está, se devuelve directamente; si no, se calcula y se guarda.
- **Bottom-up (tabulación)**: se elimina la recursión. Se arranca por los casos base y se van llenando **iterativamente** todos los subproblemas, en un orden tal que cuando necesitamos el resultado de un subproblema, ya lo calculamos antes.

| Aspecto                  | Top-down (memoización)                  | Bottom-up (tabulación)                |
| -------------------------- | ------------------------------------------ | ---------------------------------------- |
| Estructura                | Recursiva                                   | Iterativa (loops)                        |
| ¿Calcula todos los subproblemas? | Solo los que hacen falta                | Todos, en orden                          |
| Riesgo de stack overflow  | Sí, si la recursión es muy profunda         | No                                        |
| Más fácil de escribir a partir de | Un backtracking ya armado                | Requiere pensar el orden de evaluación   |

> Tip: una buena estrategia práctica es primero escribir la solución **top-down** (parte de un backtracking que ya funciona, agregándole memoria) y, una vez que anda, si hace falta, convertirla a **bottom-up** para evitar problemas de stack o ganar un poco más de performance.


## Ejemplo: Fibonacci

**Sin memoria** (fuerza bruta / backtracking puro), Fibonacci recalcula el mismo subproblema exponencialmente muchas veces:

```cpp
int fibSinMemo(int n) {
    if (n <= 1) return n;
    return fibSinMemo(n - 1) + fibSinMemo(n - 2); // O(2^n): recalcula todo el tiempo
}
```

**Top-down (memoización)**, usando un `std::vector<int>` para guardar los subproblemas ya resueltos:

```cpp
#include <vector>

int fibMemo(int n, std::vector<int>& memo) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n]; // ya lo resolví antes, lo reutilizo

    memo[n] = fibMemo(n - 1, memo) + fibMemo(n - 2, memo);
    return memo[n];
}

int fibonacci(int n) {
    std::vector<int> memo(n + 1, -1); // -1 = "todavía no calculado"
    return fibMemo(n, memo);
}
```

**Bottom-up (tabulación)**, sin recursión:

```cpp
#include <vector>

int fibonacciTabulado(int n) {
    std::vector<int> dp(n + 1);
    dp[0] = 0;
    if (n >= 1) dp[1] = 1;

    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2]; // el estado dp[i] depende de dos estados anteriores
    }
    return dp[n];
}
```

Ambas versiones bajan el costo de **O(2^n)** a **O(n)**.


## Ejemplo: mochila 0/1

Dados `n` objetos con peso y valor, y una capacidad `W`, elegir un subconjunto de objetos (cada uno **entero**, no fraccionable) que maximice el valor sin superar `W`.

El **estado** es `(i, capacidadRestante)`: "considerando los objetos desde `i` en adelante, con `capacidadRestante` de espacio libre, ¿cuál es el máximo valor que puedo obtener?".

La recurrencia (igual que en el backtracking de incluir/no incluir) es:

```
mochila(i, cap) = 0                                                             si i == n
mochila(i, cap) = mochila(i+1, cap)                                             si peso[i] > cap
mochila(i, cap) = max( mochila(i+1, cap),
                        valor[i] + mochila(i+1, cap - peso[i]) )                en otro caso
```

**Top-down (memoización)** con una matriz `std::vector<std::vector<int>>`:

```cpp
#include <vector>
#include <algorithm>

int mochilaMemo(int i, int cap, const std::vector<int>& peso, const std::vector<int>& valor,
                 std::vector<std::vector<int>>& memo) {
    if (i == (int)peso.size()) return 0;
    if (memo[i][cap] != -1) return memo[i][cap];

    int resultado;
    if (peso[i] > cap) {
        resultado = mochilaMemo(i + 1, cap, peso, valor, memo); // no entra, ni lo considero
    } else {
        int noLoLlevo = mochilaMemo(i + 1, cap, peso, valor, memo);
        int loLlevo = valor[i] + mochilaMemo(i + 1, cap - peso[i], peso, valor, memo);
        resultado = std::max(noLoLlevo, loLlevo);
    }

    memo[i][cap] = resultado;
    return resultado;
}

int mochila01(int capacidad, const std::vector<int>& peso, const std::vector<int>& valor) {
    int n = (int)peso.size();
    std::vector<std::vector<int>> memo(n + 1, std::vector<int>(capacidad + 1, -1));
    return mochilaMemo(0, capacidad, peso, valor, memo);
}
```

**Bottom-up (tabulación)**, llenando la matriz de atrás para adelante:

```cpp
#include <vector>
#include <algorithm>

int mochila01Tabulada(int capacidad, const std::vector<int>& peso, const std::vector<int>& valor) {
    int n = (int)peso.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(capacidad + 1, 0));

    for (int i = n - 1; i >= 0; i--) {
        for (int cap = 0; cap <= capacidad; cap++) {
            if (peso[i] > cap) {
                dp[i][cap] = dp[i + 1][cap];
            } else {
                dp[i][cap] = std::max(dp[i + 1][cap], valor[i] + dp[i + 1][cap - peso[i]]);
            }
        }
    }
    return dp[0][capacidad];
}
```

Costo: **O(n * W)** tanto en tiempo como en memoria (donde `W` es la capacidad). Esto se llama **pseudo-polinomial**: es polinomial en el *valor* de `W`, pero `W` puede requerir muy pocos bits para representarse, así que no es polinomial en el *tamaño de la entrada*.


## Ejemplo: subsecuencia común más larga (LCS)

Dadas dos strings `A` y `B`, encontrar la longitud de la **subsecuencia común más larga** (no necesariamente contigua, pero sí en el mismo orden relativo).

El **estado** es `(i, j)`: "la longitud de la LCS entre el sufijo de `A` desde `i` y el sufijo de `B` desde `j`".

```
lcs(i, j) = 0                                     si i == |A| o j == |B|
lcs(i, j) = 1 + lcs(i+1, j+1)                      si A[i] == B[j]
lcs(i, j) = max( lcs(i+1, j), lcs(i, j+1) )        si A[i] != B[j]
```

```cpp
#include <string>
#include <vector>
#include <algorithm>

int lcsTabulada(const std::string& A, const std::string& B) {
    int n = (int)A.size(), m = (int)B.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));

    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            if (A[i] == B[j]) {
                dp[i][j] = 1 + dp[i + 1][j + 1];
            } else {
                dp[i][j] = std::max(dp[i + 1][j], dp[i][j + 1]);
            }
        }
    }
    return dp[0][0];
}
```

Costo: **O(n * m)**, muchísimo mejor que la fuerza bruta de probar todas las subsecuencias (`O(2^n)`).


## Ejemplo: cambio de monedas

Dado un sistema de monedas (con valores arbitrarios) y un `target`, encontrar la **mínima cantidad de monedas** necesaria para completar exactamente ese monto (a diferencia del greedy del tutorial anterior, esto funciona para **cualquier** sistema de monedas).

El **estado** es el monto restante `m`: "mínima cantidad de monedas para completar `m`".

```
minMonedas(0) = 0
minMonedas(m) = 1 + min( minMonedas(m - moneda) )  para cada moneda <= m
minMonedas(m) = infinito                            si ninguna moneda entra o m < 0
```

```cpp
#include <vector>
#include <algorithm>
#include <climits>

int minMonedasTabulada(const std::vector<int>& monedas, int target) {
    std::vector<int> dp(target + 1, INT_MAX);
    dp[0] = 0; // caso base: completar 0 no necesita monedas

    for (int m = 1; m <= target; m++) {
        for (int moneda : monedas) {
            if (moneda <= m && dp[m - moneda] != INT_MAX) {
                dp[m] = std::min(dp[m], 1 + dp[m - moneda]);
            }
        }
    }
    return (dp[target] == INT_MAX) ? -1 : dp[target]; // -1 si no se puede completar
}

int main() {
    std::vector<int> monedas = {1, 3, 4};
    int resultado = minMonedasTabulada(monedas, 6);
    // resultado = 2 (3 + 3), a diferencia del greedy que daba 3 (4 + 1 + 1)
    return 0;
}
```

> Este es exactamente el caso donde greedy fallaba en el tutorial anterior. Programación dinámica sí garantiza el óptimo, porque **explora todas las combinaciones relevantes**, solo que sin recalcular subproblemas.


## Cómo identificar el estado y la recurrencia

Frente a un problema nuevo, la receta práctica para diseñar una solución de PD es:

1. **Plantear el backtracking**: ¿cuáles son las decisiones en cada paso? ¿cuál es el caso base?
2. **Identificar el estado**: ¿qué parámetros de la recursión determinan completamente el subproblema? (por ejemplo: el índice actual, la capacidad restante, el monto restante, etc.)
3. **Contar cuántos estados distintos hay**: eso determina el tamaño del vector/matriz de memoización.
4. **Escribir la recurrencia**: ¿cómo se arma la respuesta de un estado a partir de estados "más chicos"?
5. **Elegir el orden de evaluación** (si se va a hacer bottom-up): tiene que respetar que, al calcular un estado, los estados de los que depende ya estén calculados.

> Pregunta para pensar: en la mochila 0/1, el estado es `(i, cap)`. ¿Por qué no alcanza con que el estado sea solo `cap` (sin el índice `i`)?

| Problema             | Estado                       | Tamaño de la tabla       |
| --------------------- | ----------------------------- | -------------------------- |
| Fibonacci             | `n`                            | O(n)                       |
| Mochila 0/1           | `(i, capacidadRestante)`       | O(n * W)                   |
| LCS                   | `(i, j)`                       | O(n * m)                   |
| Cambio de monedas     | `montoRestante`                | O(target)                  |


# P y NP

## La clase P

La clase **P** ("Polynomial") agrupa a todos los problemas de decisión (respuesta sí/no) que se pueden **resolver** con un algoritmo cuyo tiempo de ejecución es **polinomial** en el tamaño de la entrada (por ejemplo `O(n)`, `O(n^2)`, `O(n^3 log n)`, etc.).

Todos los algoritmos que vimos en la materia hasta ahora que corren en tiempo polinomial (ordenar, buscar en un ABB, BFS/DFS, Dijkstra, Kruskal, Prim, la mayoría de nuestras soluciones de PD) están en **P**.

> Intuitivamente, P son los problemas "manejables": si `n` crece, el tiempo de ejecución crece de forma razonable.


## La clase NP y la verificación en tiempo polinomial

La clase **NP** ("Nondeterministic Polynomial") agrupa a los problemas de decisión para los cuales, **dada una solución candidata**, se puede **verificar en tiempo polinomial** si es correcta.

> Ojo con la confusión habitual: NP **no** significa "no polinomial". Significa que **verificar** una solución dada es polinomial, aunque **encontrarla** pueda no serlo.

Por ejemplo, para el problema del **clique** ("¿existe un subconjunto de `k` nodos todos conectados entre sí?"): si alguien nos **da** un subconjunto de `k` nodos, verificar que efectivamente forman un clique (revisar que todos los pares estén conectados) toma tiempo polinomial (`O(k^2)`), aunque **encontrar** ese subconjunto de entre todas las combinaciones posibles sea mucho más costoso.

Todo problema de **P** está también en **NP** (si lo puedo resolver rápido, en particular puedo verificar rápido una solución: la resuelvo yo mismo y comparo). La gran pregunta abierta de las ciencias de la computación es si **P = NP** o si **P ≠ NP** (es decir, si todo lo que se puede verificar rápido también se puede resolver rápido).

> Pregunta para pensar: ¿por qué "puedo resolverlo rápido" implica automáticamente "puedo verificarlo rápido", pero no al revés (al menos no que se sepa)?


## NP-completo y reducciones

Dentro de NP hay un subconjunto de problemas, los **NP-completos**, que son "los más difíciles de NP": si se encontrara un algoritmo polinomial para **cualquiera** de ellos, se podría resolver **todo NP** en tiempo polinomial (es decir, se demostraría que P = NP).

La herramienta para comparar la dificultad de dos problemas es la **reducción**: decimos que un problema `A` se **reduce** a un problema `B` si, con una transformación polinomial de la entrada, cualquier instancia de `A` se puede resolver usando un algoritmo para `B`.

El primer problema que se demostró NP-completo fue **SAT** (satisfacibilidad booleana: dado una fórmula lógica, ¿existe una asignación de verdad a sus variables que la haga verdadera?). A partir de SAT, se fueron demostrando NP-completos otros problemas **reduciendo SAT a ellos**:

```
SAT  --(reducción polinomial)-->  3-SAT  --(reducción polinomial)-->  Clique  --> ...
```

> Si podemos reducir un problema conocido como NP-completo (por ejemplo SAT) a un problema nuevo `X`, y además `X` está en NP, entonces `X` también es NP-completo. Esta es la técnica estándar para clasificar problemas nuevos.


## Problemas NP-hard clásicos

| Problema                        | Enunciado breve                                                             |
| ---------------------------------- | ------------------------------------------------------------------------------ |
| **TSP** (viajante de comercio)   | Encontrar el circuito de menor costo que visite todas las ciudades una vez     |
| **Mochila 0/1** (versión óptima) | Maximizar valor sujeto a una capacidad, con objetos enteros                     |
| **Clique**                       | Encontrar el subconjunto más grande de nodos todos conectados entre sí         |
| **Coloreo de grafos**            | Colorear los nodos con la menor cantidad de colores sin que dos vecinos compartan color |
| **SAT**                          | Determinar si una fórmula booleana tiene una asignación que la satisface       |

> La mochila 0/1 es un caso interesante: la solución de PD que vimos (`O(n * W)`) es **pseudo-polinomial**, no polinomial "de verdad", porque `W` puede ser exponencialmente grande respecto de la cantidad de bits necesarios para representarlo. Por eso la mochila 0/1 sigue clasificando como NP-hard en su formulación general.

Se dice que un problema es **NP-hard** si es "al menos tan difícil" como cualquier problema de NP (aunque el propio problema no necesariamente esté en NP, por ejemplo si es un problema de optimización y no de decisión). Un problema **NP-completo** es un problema NP-hard que además **sí está en NP**.


## ¿Por qué backtracking y heurísticas siguen siendo prácticos?

Que un problema sea NP-hard **no significa que no se pueda resolver nunca**: significa que no se conoce (ni se espera encontrar) un algoritmo que lo resuelva en el peor caso en tiempo polinomial para **todas** las instancias.

En la práctica, seguimos necesitando resolver instancias de TSP, mochila, coloreo de grafos, etc. Las herramientas más usadas son:

- **Backtracking con buena poda**: en instancias chicas o medianas, y con podas efectivas, puede resolver el problema exacto en tiempo razonable (como vimos con N-reinas o coloreo de grafos en el tutorial anterior).
- **Programación dinámica pseudo-polinomial**: cuando los parámetros del problema (como `W` en la mochila) no son demasiado grandes, PD da la solución exacta en tiempo aceptable.
- **Heurísticas y algoritmos de aproximación**: renunciamos a la garantía de encontrar el óptimo exacto, a cambio de una solución "suficientemente buena" en tiempo polinomial (por ejemplo, greedy aplicado a TSP no da el óptimo, pero da una solución razonable rápido).

> En definitiva: NP-hard nos dice que **no hay atajo garantizado**, pero backtracking, PD y heurísticas siguen siendo las herramientas con las que efectivamente se resuelven estos problemas todos los días en la práctica.


# Repaso general

| Concepto                  | Idea clave                                                                  |
| --------------------------- | -------------------------------------------------------------------------------- |
| Programación dinámica      | Backtracking + memoria: resolver cada subproblema una sola vez                    |
| Top-down                   | Recursión + memoización (vector/matriz de "ya calculado")                        |
| Bottom-up                  | Iterativo, se llena la tabla en el orden correcto                                 |
| Clase P                    | Se puede **resolver** en tiempo polinomial                                       |
| Clase NP                   | Se puede **verificar** una solución dada en tiempo polinomial                     |
| NP-completo                | El problema más difícil dentro de NP, todo NP se reduce a él                     |
| NP-hard                    | Al menos tan difícil como cualquier problema de NP (no necesariamente en NP)      |
| Reducción                  | Transformar (en tiempo polinomial) una instancia de un problema en otra          |

> Pregunta para pensar final: ¿por qué diríamos que "programación dinámica" y "backtracking con poda" están, en cierto sentido, en las dos puntas de un mismo espectro: exploración exhaustiva del árbol de decisiones, con distintas formas de evitar trabajo redundante?
