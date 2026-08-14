# Ejercicios - Tut 02 (Memoria dinámica y punteros)

Cáscara para resolver los ejercicios de la segunda clase.

## Archivos

- `ejercicios.h` — declaraciones de las funciones/clases a implementar (con la descripción de cada una). **No hace falta modificarlo.**
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

> Tip: varias funciones de este archivo devuelven punteros (`int*`,
> `Persona*`, `Nodo*`). El driver de pruebas (`main.cpp`) siempre chequea que
> el puntero no sea `nullptr` antes de usarlo, así que mientras la función
> esté sin implementar vas a ver `[FALLA]` en vez de que el programa se
> cuelgue con un segmentation fault.

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
