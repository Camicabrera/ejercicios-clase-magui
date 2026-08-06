Tut 01 – Ejercicios de Introducción a C++
===

A continuación hay una serie de ejercicios para practicar los conceptos vistos en el apunte: estructura básica de un programa, tipos primitivos, entrada/salida, estructuras de control, funciones (paso por valor/referencia y sobrecarga), arreglos, `std::vector` y `std::string`.

> Recordá compilar siempre con los flags estrictos de la materia:
> `g++ -g -std=c++17 -Wall -Wextra -Wconversion -Werror -o ejercicio ejercicio.cpp`



## Ejercicio 1 — Hola, C++

Escribí un programa que le pida al usuario su nombre y su edad, y luego imprima un saludo con ambos datos.

**Ejemplo de ejecución:**
```
Ingrese su nombre: Ada
Ingrese su edad: 21
Hola Ada, tenés 21 años.
```

### Solución

```cpp
#include <iostream>
#include <string>

int main() {
    std::string nombre;
    int edad;

    std::cout << "Ingrese su nombre: ";
    std::cin >> nombre;

    std::cout << "Ingrese su edad: ";
    std::cin >> edad;

    std::cout << "Hola " << nombre << ", tenes " << edad << " anios." << std::endl;

    return 0;
}
```

> Nota: `std::cin >> nombre` lee una sola palabra (corta en el primer espacio). Si quisiéramos leer un nombre compuesto, necesitaríamos `std::getline`.



## Ejercicio 2 — Par o impar

Escribí un programa que lea un número entero y diga si es par o impar, usando el operador módulo `%`.

### Solución

```cpp
#include <iostream>

int main() {
    int numero;

    std::cout << "Ingrese un numero: ";
    std::cin >> numero;

    if (numero % 2 == 0) {
        std::cout << numero << " es par" << std::endl;
    } else {
        std::cout << numero << " es impar" << std::endl;
    }

    return 0;
}
```



## Ejercicio 3 — Tabla de multiplicar

Escribí un programa que lea un número `n` y muestre su tabla de multiplicar del 1 al 10, usando un ciclo `for`.

### Solución

```cpp
#include <iostream>

int main() {
    int n;

    std::cout << "Ingrese un numero: ";
    std::cin >> n;

    for (int i = 1; i <= 10; i++) {
        std::cout << n << " x " << i << " = " << n * i << std::endl;
    }

    return 0;
}
```

> Pregunta para pensar: ¿cómo lo escribirían usando `while` en lugar de `for`?



## Ejercicio 4 — Función `esPrimo`

Escribí una función `bool esPrimo(int n)` que devuelva `true` si `n` es un número primo y `false` en caso contrario. Usála desde `main` para chequear un número ingresado por el usuario.

### Solución

```cpp
#include <iostream>

bool esPrimo(int n) {
    if (n < 2) {
        return false;
    }

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false; // encontramos un divisor: no es primo
        }
    }

    return true;
}

int main() {
    int numero;

    std::cout << "Ingrese un numero: ";
    std::cin >> numero;

    if (esPrimo(numero)) {
        std::cout << numero << " es primo" << std::endl;
    } else {
        std::cout << numero << " no es primo" << std::endl;
    }

    return 0;
}
```

> Complejidad: este chequeo recorre hasta la raíz cuadrada de `n`, así que su complejidad es **O(√n)** en lugar de O(n).



## Ejercicio 5 — `swap` por referencia

Escribí una función `void swap(int &a, int &b)` que intercambie los valores de dos variables enteras, y probala desde `main`.

### Solución

```cpp
#include <iostream>

void swap(int &a, int &b) {
    int aux = a;
    a = b;
    b = aux;
}

int main() {
    int x = 3;
    int y = 8;

    std::cout << "Antes: x=" << x << " y=" << y << std::endl;

    swap(x, y);

    std::cout << "Despues: x=" << x << " y=" << y << std::endl;

    return 0;
}
```

> Pregunta para pensar: ¿qué pasaría si `swap` recibiera los parámetros **por valor** (`void swap(int a, int b)`) en lugar de por referencia? Probalo y comprobá que `x` e `y` no cambian en `main`.



## Ejercicio 6 — Sobrecarga: `maximo`

Escribí dos versiones de una función `maximo` que devuelva el mayor de dos valores: una que reciba dos `int` y otra que reciba dos `double`. Probá ambas desde `main`.

### Solución

```cpp
#include <iostream>

int maximo(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

double maximo(double a, double b) {
    if (a > b) {
        return a;
    }
    return b;
}

int main() {
    std::cout << maximo(3, 7) << std::endl;       // llama a la version con int
    std::cout << maximo(3.5, 2.1) << std::endl;   // llama a la version con double

    return 0;
}
```

> Este es un ejemplo de **sobrecarga**: el compilador elige qué versión de `maximo` usar según el tipo de los argumentos.



## Ejercicio 7 — Promedio de un arreglo

Escribí un programa que declare un arreglo estático de 5 enteros, los cargue con valores ingresados por el usuario, y calcule su promedio.

### Solución

```cpp
#include <iostream>

int main() {
    const int TAMANIO = 5;
    int numeros[TAMANIO];
    int suma = 0;

    for (int i = 0; i < TAMANIO; i++) {
        std::cout << "Ingrese el numero " << i << ": ";
        std::cin >> numeros[i];
        suma = suma + numeros[i];
    }

    double promedio = static_cast<double>(suma) / TAMANIO;

    std::cout << "El promedio es: " << promedio << std::endl;

    return 0;
}
```

> `static_cast<double>(suma)` convierte explícitamente `suma` a `double` antes de dividir, para evitar una división entera. Con el flag `-Wconversion` el compilador nos va a avisar si hacemos conversiones "peligrosas" sin ser explícitos.



## Ejercicio 8 — `std::vector` de notas

Usando `std::vector<double>`, escribí un programa que lea una cantidad `n` de notas ingresadas por el usuario, las guarde, y luego imprima el promedio y la nota máxima.

### Solución

```cpp
#include <iostream>
#include <vector>

int main() {
    int n;
    std::cout << "Cuantas notas va a ingresar? ";
    std::cin >> n;

    std::vector<double> notas;

    for (int i = 0; i < n; i++) {
        double nota;
        std::cout << "Ingrese la nota " << i << ": ";
        std::cin >> nota;
        notas.push_back(nota);
    }

    double suma = 0;
    double maxima = notas[0];

    for (int i = 0; i < notas.size(); i++) {
        suma = suma + notas[i];
        if (notas[i] > maxima) {
            maxima = notas[i];
        }
    }

    std::cout << "Promedio: " << suma / n << std::endl;
    std::cout << "Maxima: " << maxima << std::endl;

    return 0;
}
```

> Complejidad: recorrer el vector para sumar y buscar el máximo es **O(n)**, ya que visitamos cada elemento una única vez.



## Ejercicio 9 — Contar vocales con `std::string`

Escribí una función `int contarVocales(const std::string &texto)` que reciba un string por referencia constante y devuelva la cantidad de vocales (a, e, i, o, u) que contiene, sin distinguir mayúsculas de minúsculas.

### Solución

```cpp
#include <iostream>
#include <string>

int contarVocales(const std::string &texto) {
    int contador = 0;

    for (int i = 0; i < texto.size(); i++) {
        char c = texto[i];

        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
            contador++;
        }
    }

    return contador;
}

int main() {
    std::string texto;

    std::cout << "Ingrese un texto (sin espacios): ";
    std::cin >> texto;

    std::cout << "Cantidad de vocales: " << contarVocales(texto) << std::endl;

    return 0;
}
```

> `const std::string &texto` evita copiar el string completo (que puede ser costoso si es largo) y, gracias al `const`, garantiza que la función no lo va a modificar.



## Ejercicios propuestos

1. Escribí una función `void invertir(std::vector<int> &v)` que invierta el orden de los elementos de un `std::vector<int>` **in-place** (sin crear otro vector).
2. Escribí un programa que lea una oración completa con `std::getline` y cuente cuántas palabras tiene (asumiendo que las palabras están separadas por un único espacio).
