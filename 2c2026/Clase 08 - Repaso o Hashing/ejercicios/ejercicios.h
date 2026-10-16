#ifndef EJERCICIOS_H
#define EJERCICIOS_H

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

// ============================================================================
// Tut 08 - Hashing
//
// Este archivo declara las funciones que tenés que implementar en
// "ejercicios.cpp".
//
// El programa de prueba está en "main.cpp": compilá con `make` y corré
// `./ejercicios` para ver qué ejercicios pasan y cuáles todavía fallan.
// Al final, el programa imprime una tabla que COMPARA las funciones de hash
// de la Parte 1 (colisiones y bucket más largo).
// ============================================================================

// Tipo "puntero a función de hash": cualquier función que reciba una clave y
// el tamaño de la tabla, y devuelva un índice en [0, m-1].
// Gracias a este tipo podemos pasar una función de hash como parámetro.
using FuncionHash = int (*)(const std::string& clave, int m);

// ============================================================================
// PARTE 1 — FUNCIONES DE HASH
// ============================================================================

// Ejercicio 1 — Hash por suma de caracteres
// Suma los códigos de todos los caracteres de la clave y aplica módulo m.
//   h("abc") = ('a' + 'b' + 'c') % m
// Es la función de hash más simple... y una de las peores: ¿qué pasa con
// "abc", "bca" y "cab"?
// Precondición: m > 0.
// Complejidad: O(k), donde k es el largo de la clave.
int hashSuma(const std::string& clave, int m);

// Ejercicio 2 — Hash polinomial (base 31)
// Recorre la clave acumulando: suma = suma * 31 + c, y al final aplica
// módulo m. Es la que vimos en los apuntes (la usa Java para los String).
// Ahora el ORDEN de los caracteres importa.
// Usá `unsigned long` para el acumulador: si se pasa del máximo, "da la
// vuelta" (overflow sin signo, que está bien definido en C++).
// Precondición: m > 0.
// Complejidad: O(k), donde k es el largo de la clave.
int hashPolinomial(const std::string& clave, int m);

// Ejercicio 3 — Hash djb2 (Dan Bernstein)
// Arranca con hash = 5381 y por cada carácter hace: hash = hash * 33 + c.
// Al final aplica módulo m. Es muy usada en la práctica por ser rápida y
// distribuir bien.
// Precondición: m > 0.
// Complejidad: O(k), donde k es el largo de la clave.
int hashDjb2(const std::string& clave, int m);

// Ejercicio 4 — Contar colisiones
// Dada una lista de claves (todas distintas), una tabla de tamaño m y una
// función de hash, devuelve cuántas claves cayeron en un bucket que YA
// estaba ocupado por otra clave.
// Ejemplo: si 5 claves caen en los buckets {2, 7, 2, 2, 4}, hay 2 colisiones
// (la segunda y la tercera vez que se usa el bucket 2).
// Equivalente: cantidad de claves - cantidad de buckets distintos usados.
// Complejidad: O(n), donde n es la cantidad de claves (sin contar el costo
// de calcular el hash de cada una).
int contarColisiones(const std::vector<std::string>& claves, int m, FuncionHash funcion);

// Ejercicio 5 — Bucket más largo
// Igual que el anterior, pero devuelve la cantidad de claves que tiene el
// bucket MÁS cargado. Si usáramos encadenamiento, es el largo de la lista
// más larga, o sea, el costo del peor caso de una búsqueda.
// Si no hay claves, devuelve 0.
// Complejidad: O(n + m).
int bucketMasLargo(const std::vector<std::string>& claves, int m, FuncionHash funcion);

// ============================================================================
// PARTE 2 — TABLA DE HASH CON ENCADENAMIENTO (CHAINING)
// ============================================================================

// Diccionario clave (string) -> valor (int) implementado "a mano".
// Cada bucket es un vector de pares (clave, valor) con todas las claves que
// colisionaron en ese índice.
// La función de hash es configurable (por defecto, hashPolinomial): en las
// pruebas usamos hashSuma a propósito para forzar colisiones.
struct TablaHash {
    std::vector<std::vector<std::pair<std::string, int>>> buckets;
    int cantidad;
    FuncionHash funcion;

    TablaHash(int m, FuncionHash f = hashPolinomial)
        : buckets(static_cast<size_t>(m)), cantidad(0), funcion(f) {}
};

// Ejercicio 6 — Insertar (encadenamiento)
// Inserta el par (clave, valor). Si la clave ya existía, actualiza su valor
// (y NO cambia la cantidad).
// Complejidad: O(1) esperado, O(n) peor caso.
void insertarEncadenada(TablaHash& tabla, const std::string& clave, int valor);

// Ejercicio 7 — Buscar (encadenamiento)
// Si la clave está, guarda su valor en `valor` y devuelve true.
// Si no está, devuelve false (y no modifica `valor`).
// Complejidad: O(1) esperado, O(n) peor caso.
bool buscarEncadenada(const TablaHash& tabla, const std::string& clave, int& valor);

// Ejercicio 8 — Borrar (encadenamiento)
// Borra la clave de la tabla. Devuelve true si estaba, false si no.
// Complejidad: O(1) esperado, O(n) peor caso.
bool borrarEncadenada(TablaHash& tabla, const std::string& clave);

// Ejercicio 9 — Factor de carga
// Devuelve α = cantidad de elementos / cantidad de buckets.
// Ojo con la división entera: convertí a double antes de dividir.
// Complejidad: O(1).
double factorDeCarga(const TablaHash& tabla);

// Ejercicio 10 — Rehash
// Cambia el tamaño de la tabla a `nuevoM` buckets y reinserta TODOS los
// elementos (su índice cambia porque cambió m). La cantidad de elementos y
// la función de hash se mantienen.
// Precondición: nuevoM > 0.
// Complejidad: O(n + m).
void rehash(TablaHash& tabla, int nuevoM);

// ============================================================================
// PARTE 3 — DIRECCIONAMIENTO ABIERTO (LINEAR PROBING)
// ============================================================================

enum class Estado { VACIO, OCUPADO, BORRADO };

struct Slot {
    std::string clave;
    int valor;
    Estado estado;

    Slot() : clave(""), valor(0), estado(Estado::VACIO) {}
};

// Todos los elementos viven directamente en el arreglo `slots`.
// Si la posición h(clave) está ocupada, se prueba (h + 1) % m, (h + 2) % m...
struct TablaAbierta {
    std::vector<Slot> slots;
    int cantidad;
    FuncionHash funcion;

    TablaAbierta(int m, FuncionHash f = hashPolinomial)
        : slots(static_cast<size_t>(m)), cantidad(0), funcion(f) {}
};

// Ejercicio 11 — Buscar (linear probing)
// Si la clave está, guarda su valor en `valor` y devuelve true.
// Sondea desde h(clave) y se detiene al encontrar la clave, al llegar a un
// slot VACIO, o después de recorrer los m slots.
// IMPORTANTE: un slot BORRADO NO corta la búsqueda (hay que seguir).
// Complejidad: O(1) esperado, O(m) peor caso.
bool buscarAbierta(const TablaAbierta& tabla, const std::string& clave, int& valor);

// Ejercicio 12 — Insertar (linear probing)
// Inserta el par (clave, valor). Si la clave ya existía, actualiza el valor.
// Si no existía, la guarda en el primer slot VACIO o BORRADO de la secuencia
// de sondeo. Devuelve true si pudo insertar/actualizar, false si la tabla
// está llena.
// Cuidado: antes de reutilizar un slot BORRADO hay que asegurarse de que la
// clave no esté más adelante en la secuencia (si no, quedaría duplicada).
// Complejidad: O(1) esperado, O(m) peor caso.
bool insertarAbierta(TablaAbierta& tabla, const std::string& clave, int valor);

// Ejercicio 13 — Borrar (linear probing)
// Borra la clave marcando su slot como BORRADO (lápida / tombstone).
// NO lo marques como VACIO: eso cortaría la secuencia de sondeo de otras
// claves que colisionaron y quedaron "más adelante".
// Devuelve true si la clave estaba, false si no.
// Complejidad: O(1) esperado, O(m) peor caso.
bool borrarAbierta(TablaAbierta& tabla, const std::string& clave);

// ============================================================================
// PARTE 4 — USANDO DICCIONARIOS DE LA STL
// (std::unordered_map / std::unordered_set)
// ============================================================================

// Ejercicio 14 — Contar palabras
// Devuelve un diccionario palabra -> cantidad de apariciones.
// Ejemplo: {"a", "b", "a"} -> {"a": 2, "b": 1}
// Complejidad: O(n) esperado.
std::unordered_map<std::string, int> contarPalabras(const std::vector<std::string>& palabras);

// Ejercicio 15 — Primer repetido
// Devuelve el primer elemento que aparece por SEGUNDA vez al recorrer el
// vector de izquierda a derecha. Si no hay repetidos, devuelve -1.
// Ejemplo: {3, 1, 4, 1, 3} -> 1 (el 1 se repite antes que el 3).
// Pista: unordered_set con los elementos ya vistos.
// Complejidad: O(n) esperado (con dos for anidados sería O(n²)).
int primerRepetido(const std::vector<int>& v);

// Ejercicio 16 — Dos suma
// Devuelve true si existen dos posiciones DISTINTAS i, j tales que
// v[i] + v[j] == objetivo.
// Pista: para cada x, ¿ya vi a (objetivo - x)?
// Complejidad: O(n) esperado.
bool dosSuma(const std::vector<int>& v, int objetivo);

// Ejercicio 17 — Anagramas
// Devuelve true si `a` y `b` son anagramas (mismas letras con las mismas
// cantidades, en cualquier orden). Ejemplo: "roma" y "amor".
// Pista: contá las letras de cada una con un unordered_map<char, int>.
// Complejidad: O(k) esperado, con k el largo de las palabras.
bool sonAnagramas(const std::string& a, const std::string& b);

// ============================================================================
// EJERCICIOS PROPUESTOS
// ============================================================================

// Propuesto 1 — Primer carácter único
// Devuelve el primer carácter del string que aparece UNA sola vez.
// Si no hay ninguno, devuelve '\0'.
// Ejemplo: "abracadabra" -> 'c' (la 'd' también aparece una vez, pero
// la 'c' viene antes).
// Complejidad: O(k) esperado.
char primerCaracterUnico(const std::string& s);

// Propuesto 2 — Subarreglos con suma k
// Devuelve cuántos subarreglos CONTIGUOS (no vacíos) suman exactamente k.
// Ejemplo: {1, 1, 1}, k = 2 -> 2 ([1,1] en posiciones 0-1 y 1-2).
// Pista: sumas prefijas. Si la suma acumulada hasta j es S, todo prefijo
// anterior con suma S - k da un subarreglo que termina en j y suma k.
// Guardá en un unordered_map cuántas veces apareció cada suma prefija.
// Complejidad: O(n) esperado (la fuerza bruta es O(n²)).
int subarreglosConSumaK(const std::vector<int>& v, int k);

// Propuesto 3 — Secuencia consecutiva más larga
// Devuelve el largo de la secuencia más larga de números consecutivos que
// están en el vector (en cualquier orden).
// Ejemplo: {100, 4, 200, 1, 3, 2} -> 4 (la secuencia 1, 2, 3, 4).
// Pista: meté todo en un unordered_set. Solo empezá a contar desde un x tal
// que x - 1 NO esté en el set (es el inicio de una secuencia).
// Complejidad: O(n) esperado (ordenando sería O(n log n)).
int secuenciaConsecutivaMasLarga(const std::vector<int>& v);

#endif
