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
//
// Importante: además de estas pruebas, corré `make valgrind` para confirmar
// que tus implementaciones no tienen memory leaks ni accesos inválidos a
// memoria (fundamental en los ejercicios de lista doble y lista circular).
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
    // Lista doblemente enlazada
    // ========================================================================
    {
        ListaDoble lista;
        chequear("ListaDoble - constructor (vacia)", lista.vacia());
        chequear("ListaDoble - constructor (tamanio 0)", lista.tamanio() == 0);
    }

    // Ejercicio D2/D3 — insertar
    {
        ListaDoble lista;
        lista.insertarAlFinal(10);
        lista.insertarAlFinal(20);
        lista.insertarAlFinal(30);
        chequear("D2/D3 - insertarAlFinal (tamanio)", lista.tamanio() == 3);
        chequear("D2/D3 - insertarAlFinal (buscar 10)", lista.buscar(10));
        chequear("D2/D3 - insertarAlFinal (buscar 30)", lista.buscar(30));

        lista.insertarAlInicio(5);
        chequear("D2 - insertarAlInicio (tamanio)", lista.tamanio() == 4);
        chequear("D2 - insertarAlInicio (buscar 5)", lista.buscar(5));
    }

    // Ejercicio D4 — eliminar al inicio
    {
        ListaDoble lista;
        lista.insertarAlFinal(10);
        lista.insertarAlFinal(20);
        lista.insertarAlFinal(30);

        lista.eliminarAlInicio();
        chequear("D4 - eliminarAlInicio (tamanio)", lista.tamanio() == 2);
        chequear("D4 - eliminarAlInicio (10 ya no está)", !lista.buscar(10));

        lista.eliminarAlInicio();
        lista.eliminarAlInicio();
        chequear("D4 - eliminarAlInicio (vacía)", lista.vacia());
    }

    // Ejercicio D5 — eliminar al final
    {
        ListaDoble lista;
        lista.insertarAlFinal(10);
        lista.insertarAlFinal(20);
        lista.insertarAlFinal(30);

        lista.eliminarAlFinal();
        chequear("D5 - eliminarAlFinal (tamanio)", lista.tamanio() == 2);
        chequear("D5 - eliminarAlFinal (30 ya no está)", !lista.buscar(30));

        lista.eliminarAlFinal();
        lista.eliminarAlFinal();
        chequear("D5 - eliminarAlFinal (vacía)", lista.vacia());
    }

    // Ejercicio D6 — buscar
    {
        ListaDoble lista;
        lista.insertarAlFinal(10);
        lista.insertarAlFinal(20);
        chequear("D6 - buscar (existe)", lista.buscar(20));
        chequear("D6 - buscar (no existe)", !lista.buscar(99));
    }

    // Ejercicio D7 — recorrido hacia atrás
    {
        ListaDoble lista;
        lista.insertarAlFinal(10);
        lista.insertarAlFinal(20);
        lista.insertarAlFinal(30);

        std::vector<int> esperado = {30, 20, 10};
        chequear("D7 - aVectorInverso", mismoContenido(lista.aVectorInverso(), esperado));
    }

    {
        // Destructor de ListaDoble: revisar con `make valgrind`
        ListaDoble lista;
        lista.insertarAlFinal(1);
        lista.insertarAlFinal(2);
        lista.insertarAlFinal(3);
    }

    // ========================================================================
    // Lista circular
    // ========================================================================
    {
        ListaCircular lista;
        chequear("ListaCircular - constructor (vacia)", lista.vacia());
    }

    // Ejercicio C2/C3 — insertar
    {
        ListaCircular lista;
        lista.insertarAlFinal(10);
        lista.insertarAlFinal(20);
        lista.insertarAlFinal(30);
        chequear("C3 - insertarAlFinal (no vacía)", !lista.vacia());

        std::vector<int> esperado = {10, 20, 30};
        chequear("C3 - insertarAlFinal (orden)", mismoContenido(lista.aVector(), esperado));

        lista.insertarAlInicio(5);
        std::vector<int> esperadoConInicio = {5, 10, 20, 30};
        chequear("C2 - insertarAlInicio (orden)", mismoContenido(lista.aVector(), esperadoConInicio));
    }

    // Ejercicio C4 — buscar
    {
        ListaCircular lista;
        lista.insertarAlFinal(10);
        lista.insertarAlFinal(20);
        chequear("C4 - buscar (existe)", lista.buscar(20));
        chequear("C4 - buscar (no existe)", !lista.buscar(99));
    }

    // Ejercicio C5 — recorrido completo
    {
        ListaCircular lista;
        lista.insertarAlFinal(1);
        lista.insertarAlFinal(2);
        lista.insertarAlFinal(3);
        lista.insertarAlFinal(4);

        std::vector<int> esperado = {1, 2, 3, 4};
        chequear("C5 - aVector (orden completo)", mismoContenido(lista.aVector(), esperado));
    }

    {
        // Destructor de ListaCircular: revisar con `make valgrind`.
        // Es el caso más delicado: si el corte del recorrido está mal (por
        // ejemplo, comparando contra nullptr), esto puede colgarse o crashear.
        ListaCircular lista;
        lista.insertarAlFinal(1);
        lista.insertarAlFinal(2);
        lista.insertarAlFinal(3);
    }

    // ========================================================================
    // Iteradores
    // ========================================================================
    {
        ListaIterable lista;
        lista.insertarAlFinal(10);
        lista.insertarAlFinal(20);
        lista.insertarAlFinal(30);

        // Ejercicio I4/I5 — begin() / end()
        ListaIterable::Iterador it = lista.begin();
        ListaIterable::Iterador fin = lista.end();
        chequear("I3/I4 - begin() != end() (lista no vacía)", it != fin);

        // Ejercicio I1 — operator*
        chequear("I1 - *begin() es el primer elemento", *it == 10);

        // Ejercicio I2 — operator++
        ++it;
        chequear("I2 - ++it avanza al segundo elemento", *it == 20);

        ++it;
        chequear("I2 - ++it avanza al tercer elemento", *it == 30);

        ++it;
        chequear("I3 - it == end() después del último", !(it != fin));
    }

    // Ejercicio I1..I5 combinados — for basado en rango
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
        chequear("I1-I5 - for basado en rango", mismoContenido(recorrido, esperado));
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
        chequear("I1-I5 - for basado en rango (lista vacía)", iteraciones == 0);
    }

    std::cout << "\nResultado: " << pruebasOk << "/" << totalPruebas
              << " pruebas pasadas." << std::endl;

    return 0;
}
