Tutorial 4 – Pilas y Colas: Ejercicios
===

A continuación hay una serie de ejercicios sobre pilas y colas, de dificultad creciente. Se asume disponible una implementación de `std::stack<T>` y `std::queue<T>` (o las versiones propias `PilaLista<T>` / `ColaLista<T>` del apunte de la clase); el enunciado de cada ejercicio aclara cuál conviene usar.

> Antes de mirar la solución, pensá qué invariante tenés que mantener en la pila o cola auxiliar. La mayoría de estos ejercicios se resuelven identificando bien esa invariante.



## Ejercicio 1: Balanceo de paréntesis, llaves y corchetes

Escribí una función que reciba un `std::string` con una expresión y determine si los símbolos `()`, `{}` y `[]` están correctamente balanceados (cada apertura tiene su cierre correspondiente, en el orden correcto, y no quedan símbolos sin cerrar).

```cpp
bool estaBalanceado(const std::string& expresion);
```

### Solución

```cpp
#include <stack>
#include <string>

bool estaBalanceado(const std::string& expresion) {
    std::stack<char> pila;

    for (char c : expresion) {
        if (c == '(' || c == '{' || c == '[') {
            pila.push(c);   // apertura: apilamos
        } else if (c == ')' || c == '}' || c == ']') {
            if (pila.empty()) {
                return false;   // cierre sin apertura correspondiente
            }

            char abierto = pila.top();
            pila.pop();

            bool coincide = (c == ')' && abierto == '(') ||
                             (c == '}' && abierto == '{') ||
                             (c == ']' && abierto == '[');
            if (!coincide) {
                return false;   // cierra un símbolo distinto al que corresponde
            }
        }
        // otros caracteres (letras, números, espacios) se ignoran
    }

    return pila.empty();   // si sobró algo apilado, quedó algo sin cerrar
}
```

> **Pregunta para pensar:** ¿por qué una pila es la estructura correcta acá y no una cola? Pensalo con el ejemplo `([)]`: ¿qué pasaría si usáramos FIFO en vez de LIFO para decidir qué apertura debe cerrar cada símbolo?

Complejidad: **O(n)**, recorriendo la expresión una sola vez.



## Ejercicio 2: Evaluación de expresión postfija (RPN)

Escribí una función que evalúe una expresión matemática en **notación polaca inversa** (RPN, *Reverse Polish Notation*), donde los operandos y operadores están separados por espacios. Por ejemplo, `"3 4 +"` equivale a `3 + 4 = 7`, y `"5 1 2 + 4 * + 3 -"` equivale a `5 + ((1 + 2) * 4) - 3 = 14`.

```cpp
int evaluarRPN(const std::string& expresion);
```

### Solución

```cpp
#include <stack>
#include <sstream>
#include <string>

int evaluarRPN(const std::string& expresion) {
    std::stack<int> pila;
    std::istringstream tokens(expresion);
    std::string token;

    while (tokens >> token) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            // el segundo operando fue apilado DESPUÉS que el primero
            int derecho = pila.top(); pila.pop();
            int izquierdo = pila.top(); pila.pop();

            int resultado = 0;
            if (token == "+") resultado = izquierdo + derecho;
            else if (token == "-") resultado = izquierdo - derecho;
            else if (token == "*") resultado = izquierdo * derecho;
            else resultado = izquierdo / derecho;

            pila.push(resultado);
        } else {
            pila.push(std::stoi(token));   // es un número: lo apilamos
        }
    }

    return pila.top();   // al final queda un solo valor: el resultado
}
```

> **Pregunta para pensar:** ¿por qué en la resta y la división el orden importa (`izquierdo - derecho` y no `derecho - izquierdo`)? Fijate cuál de los dos operandos apilaste primero.

Complejidad: **O(n)**, siendo n la cantidad de tokens.



## Ejercicio 3: Implementar una cola usando dos pilas

Implementá una cola (`enqueue`, `dequeue`, `front`, `empty`) usando **únicamente dos pilas** como estructura interna (no una lista enlazada ni un arreglo directamente).

```cpp
template <typename T>
class ColaConDosPilas {
    // enqueue, dequeue, front, empty
};
```

### Solución

La idea: una pila `entrada` recibe todos los `enqueue`. Cuando hay que hacer `dequeue` o `front` y la pila `salida` está vacía, "volcamos" todo `entrada` en `salida` (lo que invierte el orden, convirtiendo LIFO en FIFO).

```cpp
#include <stack>

template <typename T>
class ColaConDosPilas {
private:
    std::stack<T> entrada;
    std::stack<T> salida;

    void trasvasarSiHaceFalta() {
        if (salida.empty()) {
            while (!entrada.empty()) {
                salida.push(entrada.top());
                entrada.pop();
            }
        }
    }

public:
    void enqueue(const T& valor) {
        entrada.push(valor);
    }

    T dequeue() {
        // precondición: !empty()
        trasvasarSiHaceFalta();
        T valor = salida.top();
        salida.pop();
        return valor;
    }

    const T& front() {
        // precondición: !empty()
        trasvasarSiHaceFalta();
        return salida.top();
    }

    bool empty() const {
        return entrada.empty() && salida.empty();
    }
};
```

> **Pregunta para pensar:** ¿cuál es la complejidad de un `dequeue` individual en el peor caso? ¿Y la complejidad **amortizada** sobre una secuencia de n operaciones? *Pista:* cada elemento se traspasa de `entrada` a `salida` como máximo una vez en toda su vida.

Complejidad: `enqueue` es O(1); `dequeue`/`front` son O(n) en el peor caso pero **O(1) amortizado**.



## Ejercicio 4: Pila que devuelve el mínimo en O(1)

Implementá una pila que, además de `push`, `pop`, `top` y `empty`, tenga una operación `obtenerMinimo()` que devuelva el menor elemento actualmente almacenado, **en O(1)**.

```cpp
template <typename T>
class PilaConMinimo {
    // push, pop, top, empty, obtenerMinimo
};
```

### Solución

La idea es mantener una **segunda pila auxiliar** que, en cada posición, guarda cuál es el mínimo considerando solo los elementos apilados hasta ese momento.

```cpp
#include <stack>

template <typename T>
class PilaConMinimo {
private:
    std::stack<T> pilaDatos;
    std::stack<T> pilaMinimos;   // pilaMinimos.top() == mínimo de pilaDatos en todo momento

public:
    void push(const T& valor) {
        pilaDatos.push(valor);

        if (pilaMinimos.empty() || valor <= pilaMinimos.top()) {
            pilaMinimos.push(valor);
        } else {
            pilaMinimos.push(pilaMinimos.top());   // repetimos el mínimo anterior
        }
    }

    void pop() {
        // precondición: !empty()
        pilaDatos.pop();
        pilaMinimos.pop();   // se desapilan "en paralelo"
    }

    const T& top() const {
        return pilaDatos.top();
    }

    const T& obtenerMinimo() const {
        // precondición: !empty()
        return pilaMinimos.top();
    }

    bool empty() const {
        return pilaDatos.empty();
    }
};
```

> **Pregunta para pensar:** `pilaMinimos` guarda un valor por cada `push`, incluso cuando ese valor repite el mínimo anterior. Esto usa O(n) de memoria extra. ¿Se te ocurre una variante que guarde menos elementos en `pilaMinimos` (por ejemplo, solo cuando el mínimo cambia)? ¿Qué información adicional necesitarías guardar en cada entrada?

Complejidad: `push`, `pop`, `top` y `obtenerMinimo` son todas **O(1)**.



## Ejercicio 5: Invertir una cola usando una pila

Escribí una función que reciba una `std::queue<T>` (por referencia) y la invierta **usando una única pila auxiliar**.

```cpp
template <typename T>
void invertirCola(std::queue<T>& cola);
```

### Solución

```cpp
#include <queue>
#include <stack>

template <typename T>
void invertirCola(std::queue<T>& cola) {
    std::stack<T> pila;

    // 1) Vaciamos la cola en la pila: el orden se invierte (FIFO -> LIFO)
    while (!cola.empty()) {
        pila.push(cola.front());
        cola.pop();
    }

    // 2) Vaciamos la pila de vuelta en la cola: se invierte OTRA vez
    while (!pila.empty()) {
        cola.push(pila.top());
        pila.pop();
    }
}
```

> **Pregunta para pensar:** si el primer paso invierte el orden y el segundo paso también lo invierte, ¿por qué el resultado final es la cola invertida y no la cola original? Seguí el ejemplo `[1, 2, 3]` paso a paso.

Complejidad: **O(n)** en tiempo, **O(n)** en memoria auxiliar (la pila).



## Ejercicio 6: Chequear palíndromo con pila y cola

Escribí una función que determine si un `std::string` es un palíndromo (se lee igual al derecho y al revés), usando **una pila y una cola** en simultáneo: cargá todos los caracteres en ambas estructuras y compará sacando de a uno de cada una.

```cpp
bool esPalindromo(const std::string& texto);
```

### Solución

```cpp
#include <stack>
#include <queue>
#include <string>

bool esPalindromo(const std::string& texto) {
    std::stack<char> pila;   // al desapilar, da los caracteres de ATRÁS hacia ADELANTE
    std::queue<char> cola;    // al desencolar, da los caracteres de ADELANTE hacia ATRÁS

    for (char c : texto) {
        pila.push(c);
        cola.push(c);
    }

    while (!pila.empty()) {
        char desdeElFinal = pila.top();  pila.pop();
        char desdeElInicio = cola.front(); cola.pop();

        if (desdeElFinal != desdeElInicio) {
            return false;
        }
    }

    return true;
}
```

> **Pregunta para pensar:** este algoritmo recorre el string dos veces "conceptualmente" (una para cargar, otra para comparar) y compara desde ambos extremos hacia el centro. ¿Cómo resolverías el mismo problema con **dos punteros de índice** sobre el string directamente, sin pila ni cola? ¿Cuál de las dos soluciones usa menos memoria?

Complejidad: **O(n)** en tiempo, **O(n)** en memoria auxiliar.



## Ejercicios propuestos

1. Implementá una **pila usando dos colas** (`std::queue<T>`), de forma simétrica al ejercicio 3. Pensá cuál de las dos operaciones (`push` o `pop`) te conviene hacer "costosa" (la que recorre y re-encola todo) para que la otra quede en O(1).
2. Dada una secuencia de operaciones `push` sobre una pila (por ejemplo, apilar los números `1, 2, 3, 4, 5` en ese orden) y una supuesta secuencia de salida de `pop` (por ejemplo, `4, 5, 3, 2, 1`), escribí una función que determine si esa secuencia de salida **es posible** de obtener intercalando `push` y `pop` sobre una pila, sin conocer de antemano en qué momento se hizo cada operación.
