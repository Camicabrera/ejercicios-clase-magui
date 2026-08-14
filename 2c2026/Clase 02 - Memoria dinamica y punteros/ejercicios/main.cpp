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
//
// Importante: además de estas pruebas, corré `make valgrind` para confirmar
// que tus implementaciones no tienen memory leaks ni accesos inválidos a
// memoria. Fijate que, como varias funciones devuelven punteros, siempre
// chequeamos que no sean `nullptr` antes de usarlos: así, mientras una
// función esté sin implementar, vas a ver `[FALLA]` en vez de que el
// programa se cuelgue.
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
    // Ejercicio 1
    int a = 5;
    duplicarPuntero(&a);
    chequear("Ej1 - duplicarPuntero", a == 10);

    // Ejercicio 2
    int b = 5;
    duplicarReferencia(b);
    chequear("Ej2 - duplicarReferencia", b == 10);

    // Ejercicio 3
    int *cuadrados = crearArregloDeCuadrados(5);
    chequear("Ej3 - crearArregloDeCuadrados (no nulo)", cuadrados != nullptr);
    if (cuadrados != nullptr)
    {
        chequear("Ej3 - crearArregloDeCuadrados (valores)",
                 cuadrados[0] == 0 && cuadrados[1] == 1 && cuadrados[2] == 4 &&
                     cuadrados[3] == 9 && cuadrados[4] == 16);
        delete[] cuadrados;
    }

    // Ejercicio 4
    int datos[4] = {1, 2, 3, 4};
    chequear("Ej4 - sumarArregloPuntero", sumarArregloPuntero(datos, 4) == 10);

    // Ejercicio 5
    int valores[3] = {1, 2, 3};
    duplicarValores(valores, 3);
    chequear("Ej5 - duplicarValores",
             valores[0] == 2 && valores[1] == 4 && valores[2] == 6);

    // Ejercicio 6
    personasDestruidas = 0;
    Persona *persona = crearPersona("Ada", 21);
    chequear("Ej6 - crearPersona (no nulo)", persona != nullptr);
    if (persona != nullptr)
    {
        chequear("Ej6 - Persona::nombre", persona->nombre == "Ada");
        chequear("Ej6 - Persona::edad", persona->edad == 21);
        delete persona;
        chequear("Ej6 - destructor de Persona", personasDestruidas == 1);
    }

    // Ejercicio 7
    int *original = new int[3]{1, 2, 3};
    int *conAgregado = agregarElemento(original, 3, 4);
    chequear("Ej7 - agregarElemento (no nulo)", conAgregado != nullptr);
    if (conAgregado != nullptr)
    {
        chequear("Ej7 - agregarElemento (valores)",
                 conAgregado[0] == 1 && conAgregado[1] == 2 &&
                     conAgregado[2] == 3 && conAgregado[3] == 4);
        delete[] conAgregado;
    }

    // Ejercicio 8
    std::vector<int> valoresCadena = {10, 20, 30};
    Nodo *cadena = crearCadena(valoresCadena);
    chequear("Ej8 - crearCadena (no nula)", cadena != nullptr);
    if (cadena != nullptr)
    {
        chequear("Ej8 - crearCadena (orden)",
                 cadena->valor == 10 &&
                     cadena->siguiente != nullptr && cadena->siguiente->valor == 20 &&
                     cadena->siguiente->siguiente != nullptr &&
                     cadena->siguiente->siguiente->valor == 30 &&
                     cadena->siguiente->siguiente->siguiente == nullptr);
        chequear("Ej8 - sumarCadena", sumarCadena(cadena) == 60);
        liberarCadena(cadena);
    }

    // Propuesto 1 — Matriz dinámica
    // La matriz se arma acá mismo (con `new`) solo para poder probar
    // liberarMatriz. Su correctitud se termina de confirmar con
    // `make valgrind`: liberar memoria correctamente no se puede chequear
    // con un simple booleano.
    int filasMatriz = 3;
    int **matriz = new int *[static_cast<std::size_t>(filasMatriz)];
    for (int i = 0; i < filasMatriz; i++)
    {
        matriz[i] = new int[static_cast<std::size_t>(filasMatriz)];
        for (int j = 0; j < filasMatriz; j++)
        {
            matriz[i][j] = i * filasMatriz + j;
        }
    }
    liberarMatriz(matriz, filasMatriz);
    std::cout << "P1  - liberarMatriz (revisar con make valgrind)" << std::endl;

    std::cout << "\nResultado: " << pruebasOk << "/" << totalPruebas
              << " pruebas pasadas." << std::endl;

    return 0;
}
