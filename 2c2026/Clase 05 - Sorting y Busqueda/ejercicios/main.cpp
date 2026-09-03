#include <iostream>
#include <string>
#include <vector>

#include "ejercicios.h"

// ============================================================================
// Driver de pruebas.
//
// NO hace falta que edites este archivo: sirve para chequear tus soluciones.
// Compilá con `make` y corré `./ejercicios`. Cada línea muestra [PASA] o
// [FALLA] según si la función correspondiente ya funciona.
//
// Al principio va a fallar casi todo (las funciones son cáscaras vacías).
// A medida que las vayas implementando en "ejercicios.cpp", van a ir pasando.
// ============================================================================

static int totalPruebas = 0;
static int pruebasOk = 0;

static void chequear(const std::string& nombre, bool condicion)
{
    totalPruebas++;
    if (condicion)
    {
        pruebasOk++;
        std::cout << "[PASA]  " << nombre << std::endl;
    }
    else
    {
        std::cout << "[FALLA] " << nombre << std::endl;
    }
}

// Helper para comparar vectores
static bool vectoresIguales(const std::vector<int>& a, const std::vector<int>& b)
{
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); i++)
    {
        if (a[i] != b[i]) return false;
    }
    return true;
}

int main()
{
    // ========================================================================
    // Ejercicio 1 — Bubble Sort
    // ========================================================================
    {
        std::vector<int> v = {5, 2, 8, 1, 9};
        std::vector<int> esperado = {1, 2, 5, 8, 9};
        bubbleSort(v);
        chequear("Ej1 - bubbleSort (caso general)", vectoresIguales(v, esperado));
    }
    {
        std::vector<int> v = {1, 2, 3, 4, 5};
        std::vector<int> esperado = {1, 2, 3, 4, 5};
        bubbleSort(v);
        chequear("Ej1 - bubbleSort (ya ordenado)", vectoresIguales(v, esperado));
    }
    {
        std::vector<int> v = {5, 4, 3, 2, 1};
        std::vector<int> esperado = {1, 2, 3, 4, 5};
        bubbleSort(v);
        chequear("Ej1 - bubbleSort (orden inverso)", vectoresIguales(v, esperado));
    }
    {
        std::vector<int> v = {};
        std::vector<int> esperado = {};
        bubbleSort(v);
        chequear("Ej1 - bubbleSort (vacío)", vectoresIguales(v, esperado));
    }
    {
        std::vector<int> v = {42};
        std::vector<int> esperado = {42};
        bubbleSort(v);
        chequear("Ej1 - bubbleSort (un elemento)", vectoresIguales(v, esperado));
    }

    // ========================================================================
    // Ejercicio 2 — Insertion Sort
    // ========================================================================
    {
        std::vector<int> v = {5, 2, 8, 1, 9};
        std::vector<int> esperado = {1, 2, 5, 8, 9};
        insertionSort(v);
        chequear("Ej2 - insertionSort (caso general)", vectoresIguales(v, esperado));
    }
    {
        std::vector<int> v = {1, 2, 3, 4, 5};
        std::vector<int> esperado = {1, 2, 3, 4, 5};
        insertionSort(v);
        chequear("Ej2 - insertionSort (ya ordenado)", vectoresIguales(v, esperado));
    }
    {
        std::vector<int> v = {5, 4, 3, 2, 1};
        std::vector<int> esperado = {1, 2, 3, 4, 5};
        insertionSort(v);
        chequear("Ej2 - insertionSort (orden inverso)", vectoresIguales(v, esperado));
    }
    {
        std::vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};
        std::vector<int> esperado = {1, 1, 2, 3, 4, 5, 6, 9};
        insertionSort(v);
        chequear("Ej2 - insertionSort (con duplicados)", vectoresIguales(v, esperado));
    }

    // ========================================================================
    // Ejercicio 3 — Selection Sort
    // ========================================================================
    {
        std::vector<int> v = {5, 2, 8, 1, 9};
        std::vector<int> esperado = {1, 2, 5, 8, 9};
        selectionSort(v);
        chequear("Ej3 - selectionSort (caso general)", vectoresIguales(v, esperado));
    }
    {
        std::vector<int> v = {1, 2, 3, 4, 5};
        std::vector<int> esperado = {1, 2, 3, 4, 5};
        selectionSort(v);
        chequear("Ej3 - selectionSort (ya ordenado)", vectoresIguales(v, esperado));
    }
    {
        std::vector<int> v = {5, 4, 3, 2, 1};
        std::vector<int> esperado = {1, 2, 3, 4, 5};
        selectionSort(v);
        chequear("Ej3 - selectionSort (orden inverso)", vectoresIguales(v, esperado));
    }
    {
        std::vector<int> v = {64, 25, 12, 22, 11};
        std::vector<int> esperado = {11, 12, 22, 25, 64};
        selectionSort(v);
        chequear("Ej3 - selectionSort (otro caso)", vectoresIguales(v, esperado));
    }

    // ========================================================================
    // Ejercicio 4 — Búsqueda Lineal
    // ========================================================================
    {
        std::vector<int> v = {5, 2, 8, 1, 9};
        chequear("Ej4 - busquedaLineal (existe al inicio)", busquedaLineal(v, 5) == 0);
        chequear("Ej4 - busquedaLineal (existe en medio)", busquedaLineal(v, 8) == 2);
        chequear("Ej4 - busquedaLineal (existe al final)", busquedaLineal(v, 9) == 4);
        chequear("Ej4 - busquedaLineal (no existe)", busquedaLineal(v, 99) == -1);
    }
    {
        std::vector<int> v = {};
        chequear("Ej4 - busquedaLineal (vector vacío)", busquedaLineal(v, 1) == -1);
    }
    {
        std::vector<int> v = {3, 1, 4, 1, 5};
        chequear("Ej4 - busquedaLineal (duplicado, devuelve primero)", busquedaLineal(v, 1) == 1);
    }

    // ========================================================================
    // Ejercicio 5 — Búsqueda Binaria (iterativa)
    // ========================================================================
    {
        std::vector<int> v = {1, 2, 5, 8, 9};  // ordenado
        chequear("Ej5 - busquedaBinaria (existe al inicio)", busquedaBinaria(v, 1) == 0);
        chequear("Ej5 - busquedaBinaria (existe en medio)", busquedaBinaria(v, 5) == 2);
        chequear("Ej5 - busquedaBinaria (existe al final)", busquedaBinaria(v, 9) == 4);
        chequear("Ej5 - busquedaBinaria (no existe, menor que todos)", busquedaBinaria(v, 0) == -1);
        chequear("Ej5 - busquedaBinaria (no existe, mayor que todos)", busquedaBinaria(v, 100) == -1);
        chequear("Ej5 - busquedaBinaria (no existe, en el medio)", busquedaBinaria(v, 6) == -1);
    }
    {
        std::vector<int> v = {};
        chequear("Ej5 - busquedaBinaria (vector vacío)", busquedaBinaria(v, 1) == -1);
    }
    {
        std::vector<int> v = {42};
        chequear("Ej5 - busquedaBinaria (un elemento, existe)", busquedaBinaria(v, 42) == 0);
        chequear("Ej5 - busquedaBinaria (un elemento, no existe)", busquedaBinaria(v, 1) == -1);
    }

    // ========================================================================
    // Ejercicio 6 — Búsqueda Binaria (recursiva)
    // ========================================================================
    {
        std::vector<int> v = {1, 2, 5, 8, 9};  // ordenado
        int n = static_cast<int>(v.size());
        chequear("Ej6 - busquedaBinariaRec (existe al inicio)",
                 busquedaBinariaRec(v, 1, 0, n - 1) == 0);
        chequear("Ej6 - busquedaBinariaRec (existe en medio)",
                 busquedaBinariaRec(v, 5, 0, n - 1) == 2);
        chequear("Ej6 - busquedaBinariaRec (existe al final)",
                 busquedaBinariaRec(v, 9, 0, n - 1) == 4);
        chequear("Ej6 - busquedaBinariaRec (no existe)",
                 busquedaBinariaRec(v, 6, 0, n - 1) == -1);
    }
    {
        std::vector<int> v = {};
        chequear("Ej6 - busquedaBinariaRec (vector vacío)",
                 busquedaBinariaRec(v, 1, 0, -1) == -1);
    }

    // ========================================================================
    // Propuesto 1 — Verificar si está ordenado
    // ========================================================================
    {
        std::vector<int> v1 = {1, 2, 3, 4, 5};
        std::vector<int> v2 = {5, 2, 8, 1, 9};
        std::vector<int> v3 = {};
        std::vector<int> v4 = {42};
        std::vector<int> v5 = {1, 1, 1, 1};

        chequear("P1 - estaOrdenado (ordenado)", estaOrdenado(v1));
        chequear("P1 - estaOrdenado (desordenado)", !estaOrdenado(v2));
        chequear("P1 - estaOrdenado (vacío)", estaOrdenado(v3));
        chequear("P1 - estaOrdenado (un elemento)", estaOrdenado(v4));
        chequear("P1 - estaOrdenado (todos iguales)", estaOrdenado(v5));
    }

    // ========================================================================
    // Propuesto 2 — Encontrar el mínimo
    // ========================================================================
    {
        std::vector<int> v1 = {5, 2, 8, 1, 9};
        std::vector<int> v2 = {1, 2, 3, 4, 5};
        std::vector<int> v3 = {5, 4, 3, 2, 1};
        std::vector<int> v4 = {42};

        chequear("P2 - indiceMinimo (caso general)", indiceMinimo(v1) == 3);
        chequear("P2 - indiceMinimo (mínimo al inicio)", indiceMinimo(v2) == 0);
        chequear("P2 - indiceMinimo (mínimo al final)", indiceMinimo(v3) == 4);
        chequear("P2 - indiceMinimo (un elemento)", indiceMinimo(v4) == 0);
    }

    // ========================================================================
    // Propuesto 3 — Contar ocurrencias
    // ========================================================================
    {
        std::vector<int> v = {1, 2, 3, 2, 1, 2, 4};
        chequear("P3 - contarOcurrencias (aparece 3 veces)", contarOcurrencias(v, 2) == 3);
        chequear("P3 - contarOcurrencias (aparece 2 veces)", contarOcurrencias(v, 1) == 2);
        chequear("P3 - contarOcurrencias (aparece 1 vez)", contarOcurrencias(v, 4) == 1);
        chequear("P3 - contarOcurrencias (no aparece)", contarOcurrencias(v, 99) == 0);
    }
    {
        std::vector<int> v = {};
        chequear("P3 - contarOcurrencias (vector vacío)", contarOcurrencias(v, 1) == 0);
    }

    // ========================================================================
    // Propuesto 4 — Encontrar duplicados
    // ========================================================================
    {
        std::vector<int> v1 = {1, 2, 3, 4, 5};
        std::vector<int> v2 = {1, 2, 3, 2, 5};
        std::vector<int> v3 = {};
        std::vector<int> v4 = {42};
        std::vector<int> v5 = {1, 1};

        chequear("P4 - tieneDuplicados (sin duplicados)", !tieneDuplicados(v1));
        chequear("P4 - tieneDuplicados (con duplicados)", tieneDuplicados(v2));
        chequear("P4 - tieneDuplicados (vacío)", !tieneDuplicados(v3));
        chequear("P4 - tieneDuplicados (un elemento)", !tieneDuplicados(v4));
        chequear("P4 - tieneDuplicados (dos iguales)", tieneDuplicados(v5));
    }

    // ========================================================================
    // Resumen
    // ========================================================================
    std::cout << "\nResultado: " << pruebasOk << "/" << totalPruebas
              << " pruebas pasadas." << std::endl;

    return 0;
}
