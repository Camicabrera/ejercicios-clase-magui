#ifndef EJERCICIOS_H
#define EJERCICIOS_H

#include <vector>

// ============================================================================
// Tut 05 - Sorting y Búsqueda
//
// Este archivo declara las funciones de ordenamiento y búsqueda que tenés que
// implementar en "ejercicios.cpp".
//
// El programa de prueba está en "main.cpp": compilá con `make` y corré
// `./ejercicios` para ver qué ejercicios pasan y cuáles todavía fallan.
// ============================================================================

// ============================================================================
// ALGORITMOS DE ORDENAMIENTO
// ============================================================================
// Todas las funciones de ordenamiento deben ordenar el vector IN-PLACE
// (modificando el vector original, sin crear uno nuevo).
// El orden es de menor a mayor.

// Ejercicio 1 — Bubble Sort
// Recorre el vector comparando elementos adyacentes. Si están en orden
// incorrecto, los intercambia. Repite hasta que no haya más intercambios.
// Optimización: si en una pasada no hubo ningún intercambio, el vector ya
// está ordenado y se puede terminar antes.
// Complejidad: O(n²) en el peor caso, O(n) en el mejor caso (ya ordenado).
void bubbleSort(std::vector<int>& v);

// Ejercicio 2 — Insertion Sort
// Construye el vector ordenado de a un elemento por vez. Para cada elemento,
// lo "inserta" en la posición correcta dentro de la parte ya ordenada,
// desplazando los elementos mayores hacia la derecha.
// Complejidad: O(n²) en el peor caso, O(n) en el mejor caso (ya ordenado).
void insertionSort(std::vector<int>& v);

// Ejercicio 3 — Selection Sort
// En cada iteración, busca el mínimo de la parte no ordenada y lo intercambia
// con el primer elemento de esa parte.
// Complejidad: O(n²) siempre (incluso si ya está ordenado).
void selectionSort(std::vector<int>& v);

// ============================================================================
// ALGORITMOS DE BÚSQUEDA
// ============================================================================
// Todas las funciones de búsqueda devuelven el ÍNDICE donde se encuentra el
// elemento buscado, o -1 si no está en el vector.

// Ejercicio 4 — Búsqueda Lineal
// Recorre el vector secuencialmente hasta encontrar el elemento o llegar al
// final. No requiere que el vector esté ordenado.
// Complejidad: O(n).
int busquedaLineal(const std::vector<int>& v, int buscado);

// Ejercicio 5 — Búsqueda Binaria (iterativa)
// Aprovecha que el vector está ORDENADO para descartar la mitad de los
// elementos en cada paso. Usa un ciclo while.
// Precondición: el vector debe estar ordenado de menor a mayor.
// Complejidad: O(log n).
int busquedaBinaria(const std::vector<int>& v, int buscado);

// Ejercicio 6 — Búsqueda Binaria (recursiva)
// Igual que la anterior, pero implementada con recursión.
// Los parámetros izq y der indican el rango [izq, der] donde buscar.
// Para buscar en todo el vector, llamar con izq=0 y der=v.size()-1.
// Precondición: el vector debe estar ordenado de menor a mayor.
// Complejidad: O(log n).
int busquedaBinariaRec(const std::vector<int>& v, int buscado, int izq, int der);

// ============================================================================
// EJERCICIOS PROPUESTOS
// ============================================================================

// Propuesto 1 — Verificar si está ordenado
// Devuelve true si el vector está ordenado de menor a mayor, false en caso
// contrario. Un vector vacío o con un solo elemento se considera ordenado.
// Complejidad: O(n).
bool estaOrdenado(const std::vector<int>& v);

// Propuesto 2 — Encontrar el mínimo
// Devuelve el ÍNDICE del elemento mínimo del vector.
// Precondición: el vector no está vacío.
// Complejidad: O(n).
int indiceMinimo(const std::vector<int>& v);

// Propuesto 3 — Contar ocurrencias
// Devuelve cuántas veces aparece el valor buscado en el vector.
// Complejidad: O(n).
int contarOcurrencias(const std::vector<int>& v, int buscado);

// Propuesto 4 — Encontrar duplicados
// Devuelve true si el vector contiene al menos un elemento repetido.
// Pista: podés ordenar una copia del vector y buscar elementos adyacentes
// iguales, o usar otro enfoque.
// Complejidad: O(n²) con fuerza bruta, O(n log n) ordenando primero.
bool tieneDuplicados(const std::vector<int>& v);

#endif
