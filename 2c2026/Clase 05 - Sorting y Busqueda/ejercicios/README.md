# Ejercicios - Tut 05 (Sorting y Búsqueda)

Cáscara para resolver los ejercicios de la quinta clase: algoritmos de ordenamiento elementales y búsqueda.

## Archivos

- `ejercicios.h` — declaraciones de las funciones a implementar (con la descripción de cada una). **No hace falta modificarlo.**
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

4. **Opcional**: corré Valgrind para confirmar que no hay accesos inválidos
   a memoria (aunque en esta clase no usamos memoria dinámica explícita):

   ```bash
   make valgrind
   ```

5. Para borrar los archivos compilados:

   ```bash
   make clean
   ```

> Tip: los `(void)parametro;` en las cáscaras están solo para que el proyecto
> compile sin advertencias antes de que implementes cada función. Cuando
> empieces a usar ese parámetro, borrá la línea `(void)...`.

> Tip: si tu Mac es Apple Silicon (M1/M2/M3), `valgrind` no está disponible
> de forma nativa. En ese caso, usá:
>
> ```bash
> make docker-valgrind
> ```

## Sobre los ejercicios

Los ejercicios trabajan sobre `std::vector<int>`. Las funciones de ordenamiento
deben ordenar el vector **in-place** (sin crear un nuevo vector), mientras que
las de búsqueda devuelven el índice donde se encontró el elemento o -1 si no
está.

### Algoritmos de ordenamiento

- **Bubble sort**: recorrer el vector "burbujeando" el máximo hacia el final.
- **Insertion sort**: ir insertando cada elemento en su posición correcta dentro de la parte ya ordenada.
- **Selection sort**: buscar el mínimo de la parte no ordenada y ponerlo en su lugar.

### Algoritmos de búsqueda

- **Búsqueda lineal**: recorrer secuencialmente hasta encontrar (o no) el elemento.
- **Búsqueda binaria**: aprovechar que el vector está ordenado para descartar la mitad en cada paso.
