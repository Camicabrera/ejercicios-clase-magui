# Ejercicios EXTRA - Tut 03 (Lista doble, lista circular e iteradores)

Ejercicios adicionales sobre lista doblemente enlazada, lista circular e
iteradores. Están en una carpeta separada (`ejercicios-extra/`) de los
ejercicios base (`ejercicios/`) a propósito: así podés bajar estos ejercicios
nuevos con `git pull` sin que se toque ni se pise el progreso que ya tenías en
`ejercicios/`.

## Archivos

- `ejercicios.h` — declaraciones de las clases a implementar (con la
  descripción de cada ejercicio). **No hace falta modificarlo.**
- `ejercicios.cpp` — **acá va tu código**: cada función tiene una cáscara con
  un `TODO`.
- `main.cpp` — programa de prueba que chequea tus soluciones. No hace falta
  modificarlo.
- `Makefile` — para compilar con los flags de la materia y correr Valgrind.

## Contenido

1. **Lista doblemente enlazada** (`ListaDoble`, ejercicios D1 a D7): destructor,
   inserción/eliminación al inicio y al final, búsqueda y recorrido hacia
   atrás usando el puntero `anterior`.
2. **Lista circular** (`ListaCircular`, ejercicios C1 a C5): destructor,
   inserción al inicio/final, búsqueda y recorrido completo, todo sin usar
   `nullptr` como condición de corte.
3. **Iteradores** (`ListaIterable`, ejercicios I1 a I5): implementación de
   `operator*`, `operator++`, `operator!=`, `begin()` y `end()` para que la
   lista soporte el `for` basado en rango (`for (int x : lista)`).

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
   ./ejercicios-extra
   ```

3. Vas a ver una lista de `[PASA]` / `[FALLA]`. Implementá cada función en
   `ejercicios.cpp` y volvé a correr `make run` hasta que pasen todas.

4. **Importante**, sobre todo en lista doble y lista circular: además de que
   los tests pasen, corré Valgrind para confirmar que tus implementaciones no
   tienen memory leaks ni accesos inválidos a memoria:

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

> Tip: si tu Mac es Apple Silicon (M1/M2/M3), `valgrind` no está disponible
> de forma nativa. En ese caso, usá:
>
> ```bash
> make docker-valgrind
> ```
>
> Necesitás tener Docker Desktop instalado y corriendo.

> Tip: el destructor de `ListaCircular` es el más delicado de esta carpeta.
> Como no hay `nullptr` al final, si el corte del recorrido está mal (por
> ejemplo, comparando contra `nullptr` en vez de contra el nodo de partida),
> el programa puede colgarse en un loop infinito o crashear. Probá primero
> con listas chicas y usá `make valgrind`/`make docker-valgrind` para
> confirmar que no quedan nodos sin liberar.
