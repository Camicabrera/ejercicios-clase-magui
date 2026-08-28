#include <iostream>
#include <string>
#include <vector>

#include "ejercicios.h"

// ============================================================================
// Driver de pruebas.
//
// NO hace falta que edites este archivo: sirve para chequear tus soluciones.
// Compilá con `make` y corré `./ejercicios-extra`. Cada línea muestra [PASA]
// o [FALLA] según si la función correspondiente ya funciona.
// ============================================================================

static int totalPruebas = 0;
static int pruebasOk = 0;

static void chequear(const std::string &nombre, bool condicion)
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

static bool mismoContenido(const std::vector<int> &a, const std::vector<int> &b)
{
    return a == b;
}

int main()
{
    // ========================================================================
    // Iteradores
    // ========================================================================
    {
        ListaIterable lista;
        lista.insertarAlFinal(10);
        lista.insertarAlFinal(20);
        lista.insertarAlFinal(30);

        // Ejercicio 4/5 — begin() / end()
        ListaIterable::Iterador it = lista.begin();
        ListaIterable::Iterador fin = lista.end();
        chequear("Ej4/5 - begin() != end() (lista no vacía)", it != fin);

        // Ejercicio 1 — operator*
        chequear("Ej1 - *begin() es el primer elemento", *it == 10);

        // Ejercicio 2 — operator++
        ++it;
        chequear("Ej2 - ++it avanza al segundo elemento", *it == 20);

        ++it;
        chequear("Ej2 - ++it avanza al tercer elemento", *it == 30);

        ++it;
        chequear("Ej3 - it == end() después del último", !(it != fin));
    }

    // Ejercicios 1..5 combinados — for basado en rango
    {
        ListaIterable lista;
        lista.insertarAlFinal(1);
        lista.insertarAlFinal(2);
        lista.insertarAlFinal(3);

        std::vector<int> recorrido;
        for (int x : lista)
        {
            recorrido.push_back(x);
        }

        std::vector<int> esperado = {1, 2, 3};
        chequear("Ej1-5 - for basado en rango", mismoContenido(recorrido, esperado));
    }

    {
        // for basado en rango sobre lista vacía: no debería entrar al cuerpo.
        ListaIterable lista;
        int iteraciones = 0;
        for (int x : lista)
        {
            (void)x;
            iteraciones++;
        }
        chequear("Ej1-5 - for basado en rango (lista vacía)", iteraciones == 0);
    }

    std::cout << "\nResultado: " << pruebasOk << "/" << totalPruebas
              << " pruebas pasadas." << std::endl;

    return 0;
}
