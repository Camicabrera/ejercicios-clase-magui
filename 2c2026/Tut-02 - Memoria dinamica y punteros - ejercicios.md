Tut 02 – Ejercicios de Memoria dinámica y punteros
===

A continuación hay una serie de ejercicios para practicar los conceptos vistos en el apunte: punteros, `new`/`delete`, `new[]`/`delete[]`, aritmética de punteros, structs en el heap, y detección de memory leaks.

> Recordá compilar siempre con los flags estrictos de la materia y correr Valgrind sobre cada ejercicio:
> `g++ -g -std=c++17 -Wall -Wextra -Wconversion -Werror -o ejercicio ejercicio.cpp`
> `valgrind -s --error-exitcode=1 --leak-check=full --show-leak-kinds=all --track-origins=yes ./ejercicio`



## Ejercicio 1 — Mi primer puntero

Escribí un programa que declare una variable `int`, un puntero a esa variable, imprima el valor, la dirección de memoria, y modifique el valor a través del puntero.

### Solución

```cpp
#include <iostream>

int main() {
    int numero = 15;
    int *p = &numero;

    std::cout << "Valor: " << numero << std::endl;
    std::cout << "Direccion: " << p << std::endl;

    *p = 100; // modificamos numero a traves del puntero

    std::cout << "Nuevo valor: " << numero << std::endl;

    return 0;
}
```



## Ejercicio 2 — Arreglo dinámico simple

Escribí un programa que le pida al usuario un tamaño `n`, reserve dinámicamente un arreglo de `n` enteros con `new[]`, lo llene con los cuadrados de `0` a `n-1`, lo imprima, y libere la memoria correctamente.

### Solución

```cpp
#include <iostream>

int main() {
    int n;
    std::cout << "Ingrese el tamanio del arreglo: ";
    std::cin >> n;

    int *arreglo = new int[n];

    for (int i = 0; i < n; i++) {
        arreglo[i] = i * i;
    }

    for (int i = 0; i < n; i++) {
        std::cout << arreglo[i] << std::endl;
    }

    delete[] arreglo; // liberamos con delete[] porque reservamos con new[]

    return 0;
}
```



## Ejercicio 3 — Modificar por puntero vs por referencia

Escribí dos versiones de una función que duplique el valor de un entero: una usando un puntero (`void duplicarPuntero(int *x)`) y otra usando una referencia (`void duplicarReferencia(int &x)`). Probá ambas desde `main`.

### Solución

```cpp
#include <iostream>

void duplicarPuntero(int *x) {
    *x = *x * 2; // hay que desreferenciar para acceder al valor
}

void duplicarReferencia(int &x) {
    x = x * 2; // la referencia se usa directamente, como si fuera la variable
}

int main() {
    int a = 5;
    int b = 5;

    duplicarPuntero(&a); // hay que pasar la direccion explicitamente
    duplicarReferencia(b); // se pasa la variable directamente

    std::cout << "a = " << a << std::endl; // 10
    std::cout << "b = " << b << std::endl; // 10

    return 0;
}
```

> Pregunta para pensar: ¿por qué `duplicarPuntero` necesita que le pasemos `&a` mientras que `duplicarReferencia` recibe `b` directamente?



## Ejercicio 4 — Struct en el heap

Definí un `struct Persona` con campos `std::string nombre` y `int edad`, con un constructor que reciba ambos valores y un destructor que imprima un mensaje de despedida. Creá una `Persona` en el heap con `new`, mostrá sus datos, y liberala.

### Solución

```cpp
#include <iostream>
#include <string>

struct Persona {
    std::string nombre;
    int edad;

    Persona(std::string nombreInicial, int edadInicial) {
        nombre = nombreInicial;
        edad = edadInicial;
    }

    ~Persona() {
        std::cout << "Chau, " << nombre << std::endl;
    }
};

int main() {
    Persona *p = new Persona("Ada", 21);

    std::cout << p->nombre << " tiene " << p->edad << " anios" << std::endl;

    delete p; // acá se ejecuta el destructor

    return 0;
}
```



## Ejercicio 5 — Recorrer con aritmética de punteros

Reescribí el recorrido de un arreglo dinámico de enteros usando **aritmética de punteros** en lugar de `[]` (es decir, usando `*(arreglo + i)` para leer y escribir).

### Solución

```cpp
#include <iostream>

int main() {
    int n = 5;
    int *arreglo = new int[n];

    for (int i = 0; i < n; i++) {
        *(arreglo + i) = i * 10; // equivalente a arreglo[i] = i * 10
    }

    for (int i = 0; i < n; i++) {
        std::cout << *(arreglo + i) << std::endl;
    }

    delete[] arreglo;

    return 0;
}
```

> Este ejercicio es puramente didáctico: en la práctica, siempre que puedan usen `arreglo[i]`, que es más legible. Pero entender que ambas notaciones son equivalentes ayuda a entender qué pasa "por debajo".



## Ejercicio 6 — Encontrar el memory leak

El siguiente programa tiene un memory leak. Encontralo, explicá por qué ocurre, y corregilo.

```cpp
#include <iostream>

int* crearArreglo(int n) {
    int *arreglo = new int[n];
    for (int i = 0; i < n; i++) {
        arreglo[i] = i;
    }
    return arreglo;
}

int main() {
    int *miArreglo = crearArreglo(10);

    for (int i = 0; i < 10; i++) {
        std::cout << miArreglo[i] << std::endl;
    }

    return 0; // ¿falta algo?
}
```

### Solución

El problema es que `crearArreglo` reserva memoria con `new[]` y la devuelve, pero en `main` nunca hacemos `delete[] miArreglo;`. Esa memoria queda reservada para siempre (memory leak), aunque el puntero `miArreglo` se destruya al terminar `main`.

```cpp
#include <iostream>

int* crearArreglo(int n) {
    int *arreglo = new int[n];
    for (int i = 0; i < n; i++) {
        arreglo[i] = i;
    }
    return arreglo;
}

int main() {
    int *miArreglo = crearArreglo(10);

    for (int i = 0; i < 10; i++) {
        std::cout << miArreglo[i] << std::endl;
    }

    delete[] miArreglo; // liberamos la memoria reservada dentro de crearArreglo

    return 0;
}
```

> Tip: cuando una función devuelve memoria reservada con `new`/`new[]`, es responsabilidad de quien la llama liberarla. Correr Valgrind sobre la versión original hubiera mostrado un mensaje de tipo "definitely lost".



## Ejercicio 7 — Evitar un dangling pointer

El siguiente código tiene un dangling pointer. Identificá el error y corregilo.

```cpp
#include <iostream>

int main() {
    int *p = new int(42);

    std::cout << *p << std::endl;

    delete p;

    std::cout << *p << std::endl; // ???

    return 0;
}
```

### Solución

Después de `delete p;`, la memoria a la que apuntaba `p` ya fue liberada. Volver a hacer `*p` accede a memoria inválida: es un **dangling pointer** y comportamiento indefinido.

```cpp
#include <iostream>

int main() {
    int *p = new int(42);

    std::cout << *p << std::endl;

    delete p;
    p = nullptr; // buena práctica: evita que el dangling pointer se use por error

    if (p != nullptr) {
        std::cout << *p << std::endl;
    } else {
        std::cout << "p ya no apunta a memoria valida" << std::endl;
    }

    return 0;
}
```

> Asignar `nullptr` después de cada `delete` no libera memoria (eso ya lo hizo `delete`), pero convierte un bug silencioso (dangling pointer) en uno fácil de detectar (acceso a `nullptr`).



## Ejercicio 8 — Redimensionar un arreglo dinámico

Escribí una función `int* agregarElemento(int *arreglo, int tamanioActual, int nuevoElemento)` que reciba un arreglo dinámico, su tamaño actual, y un nuevo elemento; devuelva un **nuevo** arreglo dinámico de tamaño `tamanioActual + 1` con todos los elementos originales más el nuevo al final, y libere el arreglo viejo.

### Solución

```cpp
#include <iostream>

int* agregarElemento(int *arreglo, int tamanioActual, int nuevoElemento) {
    int *nuevoArreglo = new int[tamanioActual + 1];

    for (int i = 0; i < tamanioActual; i++) {
        nuevoArreglo[i] = arreglo[i];
    }
    nuevoArreglo[tamanioActual] = nuevoElemento;

    delete[] arreglo; // liberamos el arreglo viejo, ya no lo necesitamos

    return nuevoArreglo;
}

int main() {
    int tamanio = 3;
    int *arreglo = new int[tamanio] {1, 2, 3};

    arreglo = agregarElemento(arreglo, tamanio, 4);
    tamanio++;

    for (int i = 0; i < tamanio; i++) {
        std::cout << arreglo[i] << std::endl;
    }

    delete[] arreglo; // liberamos el arreglo final

    return 0;
}
```

> Complejidad: cada vez que redimensionamos así, copiamos todos los elementos existentes, por lo que agregar un elemento de esta forma es **O(n)**. Esta es, justamente, la idea básica detrás de cómo funciona `std::vector` por dentro.



## Ejercicios propuestos

1. Escribí una función `void liberarMatriz(int **matriz, int filas)` que libere correctamente una matriz dinámica creada como un arreglo de punteros (`int **matriz = new int*[filas];`, donde cada `matriz[i]` fue reservado con `new int[columnas]`).
2. Escribí un programa que reserve dinámicamente un `struct Nodo` con un campo `int valor` y un campo `Nodo *siguiente`, arme una cadena de 5 nodos enlazados, la recorra imprimiendo los valores, y libere correctamente **todos** los nodos (sin memory leaks).
