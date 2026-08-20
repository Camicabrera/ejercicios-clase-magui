#include <iostream>
#include <string>

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
//
// Importante: además de estas pruebas, corré `make valgrind` para confirmar
// que tus implementaciones no tienen memory leaks ni accesos inválidos a
// memoria.
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

int main()
{
    // ========================================================================
    // Constructor, vacia() y tamanio()
    // ========================================================================
    {
        ListaSimple lista;
        chequear("Constructor - lista vacía", lista.vacia());
        chequear("Constructor - tamanio 0", lista.tamanio() == 0);
    }

    // ========================================================================
    // Ejercicio 1 — Insertar al inicio
    // ========================================================================
    {
        ListaSimple lista;
        lista.insertarAlInicio(10);
        chequear("Ej1 - insertarAlInicio (no vacía)", !lista.vacia());
        chequear("Ej1 - insertarAlInicio (tamanio 1)", lista.tamanio() == 1);

        lista.insertarAlInicio(20);
        lista.insertarAlInicio(30);
        chequear("Ej1 - insertarAlInicio (tamanio 3)", lista.tamanio() == 3);
    }

    // ========================================================================
    // Ejercicio 2 — Insertar al final
    // ========================================================================
    {
        ListaSimple lista;
        lista.insertarAlFinal(10);
        chequear("Ej2 - insertarAlFinal (no vacía)", !lista.vacia());
        chequear("Ej2 - insertarAlFinal (tamanio 1)", lista.tamanio() == 1);

        lista.insertarAlFinal(20);
        lista.insertarAlFinal(30);
        chequear("Ej2 - insertarAlFinal (tamanio 3)", lista.tamanio() == 3);
    }

    // ========================================================================
    // Ejercicio 3 — Buscar
    // ========================================================================
    {
        ListaSimple lista;
        lista.insertarAlFinal(10);
        lista.insertarAlFinal(20);
        lista.insertarAlFinal(30);

        chequear("Ej3 - buscar (existe primero)", lista.buscar(10));
        chequear("Ej3 - buscar (existe medio)", lista.buscar(20));
        chequear("Ej3 - buscar (existe ultimo)", lista.buscar(30));
        chequear("Ej3 - buscar (no existe)", !lista.buscar(99));
    }

    // ========================================================================
    // Ejercicio 4 — Frente
    // ========================================================================
    {
        ListaSimple lista;
        lista.insertarAlFinal(10);
        lista.insertarAlFinal(20);
        lista.insertarAlFinal(30);

        chequear("Ej4 - frente() es 10", lista.frente() == 10);

        lista.insertarAlInicio(5);
        chequear("Ej4 - frente() después de insertarAlInicio", lista.frente() == 5);
    }

    // ========================================================================
    // Ejercicio 5 — Final
    // ========================================================================
    {
        ListaSimple lista;
        lista.insertarAlFinal(10);
        lista.insertarAlFinal(20);
        lista.insertarAlFinal(30);

        chequear("Ej5 - final() es 30", lista.final() == 30);

        lista.insertarAlFinal(40);
        chequear("Ej5 - final() después de insertarAlFinal", lista.final() == 40);
    }

    // ========================================================================
    // Ejercicio 6 — Eliminar primero
    // ========================================================================
    {
        ListaSimple lista;
        lista.insertarAlFinal(10);
        lista.insertarAlFinal(20);
        lista.insertarAlFinal(30);

        lista.eliminarPrimero();
        chequear("Ej6 - eliminarPrimero (tamanio)", lista.tamanio() == 2);
        chequear("Ej6 - eliminarPrimero (frente)", lista.frente() == 20);

        lista.eliminarPrimero();
        lista.eliminarPrimero();
        chequear("Ej6 - eliminarPrimero (vacía)", lista.vacia());
    }

    // ========================================================================
    // Ejercicio 7 — Eliminar por valor
    // ========================================================================
    {
        ListaSimple lista;
        lista.insertarAlFinal(10);
        lista.insertarAlFinal(20);
        lista.insertarAlFinal(30);

        // Eliminar del medio
        bool eliminado = lista.eliminar(20);
        chequear("Ej7 - eliminar medio (retorno)", eliminado);
        chequear("Ej7 - eliminar medio (tamanio)", lista.tamanio() == 2);
        chequear("Ej7 - eliminar medio (no existe)", !lista.buscar(20));

        // Eliminar el primero
        eliminado = lista.eliminar(10);
        chequear("Ej7 - eliminar primero (retorno)", eliminado);
        chequear("Ej7 - eliminar primero (frente)", lista.frente() == 30);

        // Eliminar el único que queda
        eliminado = lista.eliminar(30);
        chequear("Ej7 - eliminar único (retorno)", eliminado);
        chequear("Ej7 - eliminar único (vacía)", lista.vacia());

        // Eliminar de lista vacía
        eliminado = lista.eliminar(99);
        chequear("Ej7 - eliminar inexistente (retorno)", !eliminado);
    }

    {
        // Caso especial: eliminar el último (pero no único)
        ListaSimple lista;
        lista.insertarAlFinal(10);
        lista.insertarAlFinal(20);
        lista.insertarAlFinal(30);

        bool eliminado = lista.eliminar(30);
        chequear("Ej7 - eliminar último (retorno)", eliminado);
        chequear("Ej7 - eliminar último (final)", lista.final() == 20);
    }

    // ========================================================================
    // Ejercicio 8 — Operador []
    // ========================================================================
    {
        ListaSimple lista;
        lista.insertarAlFinal(10);
        lista.insertarAlFinal(20);
        lista.insertarAlFinal(30);

        chequear("Ej8 - lista[0]", lista[0] == 10);
        chequear("Ej8 - lista[1]", lista[1] == 20);
        chequear("Ej8 - lista[2]", lista[2] == 30);

        // Modificar a través del operador
        lista[1] = 99;
        chequear("Ej8 - modificar con []", lista[1] == 99);
    }

    // ========================================================================
    // Propuesto 1 — Insertar en posición
    // ========================================================================
    {
        ListaSimple lista;
        lista.insertarEnPosicion(0, 30); // [30]
        chequear("P1 - insertarEnPosicion (en vacía)", lista.tamanio() == 1 && lista[0] == 30);

        lista.insertarEnPosicion(0, 10); // [10, 30]
        chequear("P1 - insertarEnPosicion (al inicio)", lista[0] == 10 && lista[1] == 30);

        lista.insertarEnPosicion(2, 40); // [10, 30, 40]
        chequear("P1 - insertarEnPosicion (al final)", lista[2] == 40);

        lista.insertarEnPosicion(1, 20); // [10, 20, 30, 40]
        chequear("P1 - insertarEnPosicion (medio)",
                 lista[0] == 10 && lista[1] == 20 && lista[2] == 30 && lista[3] == 40);
    }

    // ========================================================================
    // Propuesto 2 — Invertir
    // ========================================================================
    {
        ListaSimple lista;
        lista.insertarAlFinal(10);
        lista.insertarAlFinal(20);
        lista.insertarAlFinal(30);

        lista.invertir();
        chequear("P2 - invertir (orden)", lista[0] == 30 && lista[1] == 20 && lista[2] == 10);
        chequear("P2 - invertir (frente)", lista.frente() == 30);
        chequear("P2 - invertir (final)", lista.final() == 10);
    }

    {
        // Caso especial: invertir lista con un elemento
        ListaSimple lista;
        lista.insertarAlFinal(42);
        lista.invertir();
        chequear("P2 - invertir (un elemento)", lista[0] == 42);
    }

    {
        // Caso especial: invertir lista vacía (no debería fallar)
        ListaSimple lista;
        lista.invertir();
        chequear("P2 - invertir (vacía)", lista.vacia());
    }

    // ========================================================================
    // Destructor (Valgrind)
    // ========================================================================
    std::cout << "\nDestructor - revisar con `make valgrind` que no haya leaks"
              << std::endl;

    std::cout << "\nResultado: " << pruebasOk << "/" << totalPruebas
              << " pruebas pasadas." << std::endl;

    return 0;
}
