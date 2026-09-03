#include "ejercicios.h"
#include <algorithm>  // para std::swap

// ============================================================================
// Acá va TU código. Cada función tiene una cáscara con un "TODO": borrá el
// contenido de ejemplo y escribí la implementación.
//
// Los `(void)parametro;` que ves abajo están solo para que la cáscara
// compile sin advertencias antes de que la implementes. Cuando uses el
// parámetro en tu código, borrá la línea `(void)...` correspondiente.
// ============================================================================

// ============================================================================
// ALGORITMOS DE ORDENAMIENTO
// ============================================================================

// Ejercicio 1 — Bubble Sort
void bubbleSort(std::vector<int>& v)
{
    // TODO: implementar bubble sort.
    // Recordá:
    //   - Recorrer el vector comparando elementos adyacentes
    //   - Si v[j] > v[j+1], intercambiarlos
    //   - Optimización: si en una pasada no hubo intercambios, terminar
    (void)v;
}

// Ejercicio 2 — Insertion Sort
void insertionSort(std::vector<int>& v)
{
    // TODO: implementar insertion sort.
    // Recordá:
    //   - Para cada elemento desde la posición 1, "insertarlo" en la parte
    //     ya ordenada (posiciones 0 a i-1)
    //   - Desplazar hacia la derecha los elementos mayores
    (void)v;
}

// Ejercicio 3 — Selection Sort
void selectionSort(std::vector<int>& v)
{
    // TODO: implementar selection sort.
    // Recordá:
    //   - Para cada posición i, buscar el mínimo en [i, n-1]
    //   - Intercambiar v[i] con v[indiceMinimo]
    (void)v;
}

// ============================================================================
// ALGORITMOS DE BÚSQUEDA
// ============================================================================

// Ejercicio 4 — Búsqueda Lineal
int busquedaLineal(const std::vector<int>& v, int buscado)
{
    // TODO: implementar búsqueda lineal.
    // Recorrer el vector y devolver el índice si encontrás el elemento.
    // Si llegás al final sin encontrarlo, devolver -1.
    (void)v;
    (void)buscado;
    return -1;
}

// Ejercicio 5 — Búsqueda Binaria (iterativa)
int busquedaBinaria(const std::vector<int>& v, int buscado)
{
    // TODO: implementar búsqueda binaria iterativa.
    // Recordá:
    //   - Mantener dos índices: izq y der
    //   - Calcular medio = izq + (der - izq) / 2
    //   - Comparar v[medio] con buscado y ajustar izq o der
    //   - Terminar cuando izq > der (no encontrado) o cuando encontrás
    // Precondición: el vector está ordenado.
    (void)v;
    (void)buscado;
    return -1;
}

// Ejercicio 6 — Búsqueda Binaria (recursiva)
int busquedaBinariaRec(const std::vector<int>& v, int buscado, int izq, int der)
{
    // TODO: implementar búsqueda binaria recursiva.
    // Caso base: izq > der => devolver -1 (no encontrado)
    // Caso recursivo: calcular medio, comparar, y llamar recursivamente
    //                 con el rango reducido.
    // Precondición: el vector está ordenado.
    (void)v;
    (void)buscado;
    (void)izq;
    (void)der;
    return -1;
}

// ============================================================================
// EJERCICIOS PROPUESTOS
// ============================================================================

// Propuesto 1 — Verificar si está ordenado
bool estaOrdenado(const std::vector<int>& v)
{
    // TODO: recorrer el vector y verificar que cada elemento sea <= al siguiente.
    // Un vector vacío o con un solo elemento se considera ordenado.
    (void)v;
    return false;
}

// Propuesto 2 — Encontrar el mínimo
int indiceMinimo(const std::vector<int>& v)
{
    // TODO: recorrer el vector buscando el índice del elemento mínimo.
    // Precondición: el vector no está vacío.
    (void)v;
    return 0;
}

// Propuesto 3 — Contar ocurrencias
int contarOcurrencias(const std::vector<int>& v, int buscado)
{
    // TODO: contar cuántas veces aparece buscado en el vector.
    (void)v;
    (void)buscado;
    return 0;
}

// Propuesto 4 — Encontrar duplicados
bool tieneDuplicados(const std::vector<int>& v)
{
    // TODO: devolver true si hay algún elemento repetido.
    // Pista 1 (fuerza bruta): para cada elemento, buscar si aparece más adelante.
    // Pista 2 (más eficiente): ordenar una copia y buscar adyacentes iguales.
    (void)v;
    return false;
}
