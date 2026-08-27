# Ejercicios - Tut 04 (Pilas y Colas)

Cáscara para resolver los ejercicios de la cuarta clase: implementación de pilas y colas (sobre arreglo y sobre lista enlazada), y algunos casos de uso clásicos.

## Archivos

- `ejercicios.h` — declaraciones de las clases/funciones a implementar (con la descripción de cada una). **No hace falta modificarlo.**
- `ejercicios.cpp` — **acá va tu código**: cada función tiene una cáscara con un `TODO`.
- `main.cpp` — programa de prueba que chequea tus soluciones. No hace falta modificarlo.
- `Makefile` — para compilar con los flags de la materia y correr Valgrind.

## Cómo trabajar

1. Compilá el proyecto:

   ```bash
   make
   ```

2. Corré las pruebas:

   ```bash
   make run
   ```

   o, equivalente:

   ```bash
   ./ejercicios
   ```

3. Vas a ver una lista de `[PASA]` / `[FALLA]`. Al principio falla casi todo,
   porque las funciones están vacías. Implementá cada función en
   `ejercicios.cpp` y volvé a correr `make run` hasta que pasen todas.

4. **Importante en esta clase**: además de que los tests pasen, corré
   Valgrind para confirmar que tus implementaciones no tienen memory leaks
   ni accesos inválidos a memoria:

   ```bash
   make valgrind
   ```

   Si ves algo como `All heap blocks were freed -- no leaks are possible`,
   tu manejo de memoria está bien. Si ves `definitely lost` o
   `Invalid read/write`, revisá tus `new`/`delete`.

5. Para borrar los archivos compilados:

   ```bash
   make clean
   ```

> Tip: los `(void)parametro;` en las cáscaras están solo para que el proyecto
> compile sin advertencias antes de que implementes cada función. Cuando
> empieces a usar ese parámetro, borrá la línea `(void)...`.

> Tip: si tu Mac es Apple Silicon (M1/M2/M3), `valgrind` no está disponible
> de forma nativa (ni siquiera instalándolo con Homebrew: no tiene soporte
> para esa arquitectura). En ese caso, usá:
>
> ```bash
> make docker-valgrind
> ```
>
> Este target compila una imagen mínima de Linux (Ubuntu) con g++, make y
> valgrind (ver `Dockerfile`), y corre `make clean && make valgrind` adentro
> del container, montando esta carpeta. Necesitás tener Docker Desktop
> instalado y corriendo.

## Ejercicios

1. **Pila sobre arreglo** (`PilaArreglo`): `push`, `pop`, `top`, con
   redimensionamiento (duplicar capacidad) cuando el arreglo se llena.
2. **Cola sobre arreglo** (`ColaArreglo`): `enqueue`, `dequeue`, `front`,
   usando un buffer circular (índices con módulo) para que ambos extremos
   sean O(1).
3. **Pila sobre lista enlazada** (`PilaLista`): igual que la de arreglo, pero
   sobre nodos enlazados (sin redimensionamiento).
4. **Cola sobre lista enlazada** (`ColaLista`): igual que la de arreglo, pero
   sobre nodos enlazados, manteniendo punteros a `primero` y `ultimo`.
5. **Balanceo de expresiones** (`estaBalanceada`): usa una pila para chequear
   que los `()`, `[]` y `{}` de una expresión estén correctamente anidados.
6. **Evaluación postfija / RPN** (`evaluarPostfija`): usa una pila para
   evaluar una expresión matemática escrita en notación postfija.

### Propuestos

1. **Invertir una pila con una cola auxiliar** (`invertirPila`): combina
   ambas estructuras vistas en la clase.
2. **Cola con dos pilas** (`ColaConDosPilas`): implementación clásica de una
   cola usando únicamente dos pilas como estructura interna.

## Estructuras de datos

Los ejercicios trabajan sobre pilas y colas de enteros. Las versiones sobre
lista enlazada reutilizan un `Nodo` simple:

```cpp
struct Nodo {
    int dato;
    Nodo* siguiente;
};
```

Las versiones sobre arreglo (`PilaArreglo` y `ColaArreglo`) manejan su propia
memoria dinámica con `new[]` / `delete[]`, así que también son un buen
repaso de la Clase 2.
