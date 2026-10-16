# Ejercicios - Tut 08 (Hashing)

Cáscara para resolver los ejercicios de la octava clase: funciones de hash
(y cómo compararlas), tablas de hash implementadas a mano (encadenamiento y
direccionamiento abierto) y problemas que se resuelven usando diccionarios
(`std::unordered_map` / `std::unordered_set`).

## Archivos

- `ejercicios.h` — declaraciones de las funciones a implementar (con la descripción de cada una). **No hace falta modificarlo.**
- `ejercicios.cpp` — **acá va tu código**: cada función tiene una cáscara con un `TODO`.
- `main.cpp` — programa de prueba que chequea tus soluciones y compara las funciones de hash. No hace falta modificarlo.
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

4. Después del resumen de pruebas, el programa imprime una **tabla
   comparativa de las funciones de hash** (ver más abajo). Se completa a
   medida que implementás los Ejercicios 1 a 5.

5. **Opcional**: corré Valgrind para confirmar que no hay memory leaks ni
   accesos inválidos a memoria:

   ```bash
   make valgrind
   ```

6. Para borrar los archivos compilados:

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

### Parte 1 — Funciones de hash

Todas reciben una clave (`std::string`) y el tamaño de la tabla `m`, y
devuelven un índice en `[0, m-1]`.

- **hashSuma**: suma de los caracteres. Simple, pero muy mala.
- **hashPolinomial**: `suma = suma * 31 + c` (la de los apuntes).
- **hashDjb2**: `hash = hash * 33 + c`, arrancando en 5381.
- **contarColisiones**: cuántas claves cayeron en un bucket ya ocupado.
- **bucketMasLargo**: cuántas claves tiene el bucket más cargado.

Las dos últimas reciben la función de hash **como parámetro** (tipo
`FuncionHash`, un puntero a función). Así podemos medir cualquier función
con el mismo código.

#### Comparación

Con los Ejercicios 1 a 5 resueltos, `./ejercicios` imprime para cada función
de hash las colisiones y el bucket más largo sobre tres conjuntos de claves:

1. `"alumno0"` ... `"alumno999"` (claves muy parecidas entre sí), con `m = 1009` (primo).
2. Las 720 permutaciones de `"abcdef"` (todas anagramas entre sí), con `m = 1009`.
3. Las mismas claves que (1), pero con `m = 1024` (potencia de 2).

También muestra cuántas colisiones habría con un **hash ideal** (cada clave
en un bucket al azar), para tener una referencia. Mirá los resultados y
respondé las preguntas que aparecen al final.

### Parte 2 — Tabla de hash con encadenamiento

`TablaHash` es un diccionario `string -> int`: cada bucket es un vector de
pares `(clave, valor)`.

- **insertarEncadenada**, **buscarEncadenada**, **borrarEncadenada**.
- **factorDeCarga**: `α = n / m`.
- **rehash**: cambia la cantidad de buckets y reinserta todo.

### Parte 3 — Direccionamiento abierto (linear probing)

`TablaAbierta` guarda todo en un arreglo de `Slot`, cada uno con estado
`VACIO`, `OCUPADO` o `BORRADO` (lápida).

- **buscarAbierta**, **insertarAbierta**, **borrarAbierta**.

> Las pruebas de las Partes 2 y 3 usan una función de hash "de juguete"
> (`hashLargo`, el índice es el largo de la clave) para forzar colisiones y
> saber exactamente en qué posición tiene que quedar cada clave.

### Parte 4 — Usando diccionarios de la STL

Problemas que con dos `for` anidados son O(n²) y con una tabla de hash
pasan a ser O(n) esperado.

- **contarPalabras**: palabra -> cantidad de apariciones.
- **primerRepetido**: el primer elemento que aparece por segunda vez.
- **dosSuma**: ¿hay dos elementos que sumen `objetivo`?
- **sonAnagramas**: ¿tienen las mismas letras con las mismas cantidades?

### Ejercicios propuestos

- **primerCaracterUnico**: primer carácter que aparece una sola vez.
- **subarreglosConSumaK**: cuántos subarreglos contiguos suman `k` (sumas prefijas + diccionario).
- **secuenciaConsecutivaMasLarga**: largo de la secuencia de consecutivos más larga.

> Repasá los apuntes (`Tut-08 - Repaso o Hashing - apuntes.md`) para tener
> clara la idea de cada estrategia de colisiones antes de implementarla.
