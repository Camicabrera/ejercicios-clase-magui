# Ejercicios EXTRA - Tut 03 (Iteradores)

Ejercicios adicionales sobre iteradores para la lista simplemente enlazada.
Están en una carpeta separada (`ejercicios-extra/`) de los ejercicios base
(`ejercicios/`) a propósito: así podés bajar estos ejercicios nuevos con
`git pull` sin que se toque ni se pise el progreso que ya tenías en
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

**Iteradores** (`ListaIterable`, ejercicios 1 a 5): implementación de
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

4. Opcionalmente, corré Valgrind para confirmar que no hay accesos inválidos
   a memoria:

   ```bash
   make valgrind
   ```

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

> Tip: `begin()` y `end()` no van a andar hasta que también implementes
> `operator*`, `operator++` y `operator!=` del `Iterador`: los cinco
> ejercicios trabajan juntos para que funcione el `for (int x : lista)`.
