#include <algorithm>
#include <cmath>
#include <iomanip>
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
// Al final se imprime una tabla que compara hashSuma, hashPolinomial y
// hashDjb2 sobre distintos conjuntos de claves (usa los Ejercicios 1 a 5).
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

// Función de hash "de juguete" usada en las pruebas: el índice es el largo
// de la clave. Así sabemos exactamente en qué bucket cae cada clave y podemos
// forzar colisiones (todas las claves del mismo largo chocan), sin depender
// de que tus funciones de hash ya estén implementadas.
static int hashLargo(const std::string& clave, int m)
{
    return static_cast<int>(clave.size() % static_cast<size_t>(m));
}

static bool enRango(int indice, int m)
{
    return indice >= 0 && indice < m;
}

// ============================================================================
// Comparación de funciones de hash
// ============================================================================

// Cantidad de colisiones esperada si la función de hash fuera "ideal"
// (cada clave cae en un bucket uniformemente al azar):
//   n - m * (1 - (1 - 1/m)^n)
static double colisionesEsperadas(int n, int m)
{
    double mm = static_cast<double>(m);
    double ocupadosEsperados = mm * (1.0 - std::pow(1.0 - 1.0 / mm, static_cast<double>(n)));
    return static_cast<double>(n) - ocupadosEsperados;
}

static void compararFunciones(const std::string& titulo, const std::vector<std::string>& claves, int m)
{
    struct Opcion {
        std::string nombre;
        FuncionHash funcion;
    };
    std::vector<Opcion> opciones = {
        {"hashSuma", hashSuma},
        {"hashPolinomial", hashPolinomial},
        {"hashDjb2", hashDjb2},
    };

    int n = static_cast<int>(claves.size());
    std::cout << "\n" << titulo << "  (n = " << n << ", m = " << m
              << ", α = " << std::fixed << std::setprecision(2)
              << static_cast<double>(n) / static_cast<double>(m) << ")\n";
    // (encabezado escrito a mano: setw cuenta bytes y los acentos ocupan 2)
    std::cout << "  función             colisiones  bucket más largo\n";
    for (const Opcion& op : opciones) {
        std::cout << "  " << std::left << std::setw(18) << op.nombre
                  << std::right << std::setw(12) << contarColisiones(claves, m, op.funcion)
                  << std::setw(18) << bucketMasLargo(claves, m, op.funcion) << "\n";
    }
    std::cout << "  " << std::left << std::setw(18) << "(hash ideal)"
              << std::right << std::setw(12) << std::setprecision(1) << colisionesEsperadas(n, m)
              << std::setw(18) << "-" << "\n";
}

static void imprimirComparacion()
{
    std::cout << "\n========================================================\n";
    std::cout << "COMPARACIÓN DE FUNCIONES DE HASH\n";
    std::cout << "========================================================\n";
    std::cout << "(Si todavía no implementaste los Ejercicios 1 a 5, vas a ver ceros.)\n";

    // 1) Nombres de usuario parecidos entre sí: "alumno0" ... "alumno999".
    std::vector<std::string> usuarios;
    for (int i = 0; i < 1000; i++) {
        usuarios.push_back("alumno" + std::to_string(i));
    }
    compararFunciones("Claves \"alumno0\" ... \"alumno999\"", usuarios, 1009);

    // 2) Todas las permutaciones de "abcdef": son anagramas entre sí.
    std::vector<std::string> anagramas;
    std::string s = "abcdef";
    do {
        anagramas.push_back(s);
    } while (std::next_permutation(s.begin(), s.end()));
    compararFunciones("Permutaciones de \"abcdef\" (anagramas)", anagramas, 1009);

    // 3) Mismas claves que (1), pero con m potencia de 2 en vez de primo.
    compararFunciones("Claves \"alumno0\" ... \"alumno999\", m NO primo", usuarios, 1024);

    std::cout << "\nPreguntas para pensar:\n"
              << "  - ¿Por qué hashSuma es tan mala con los anagramas?\n"
              << "  - ¿Por qué hashSuma tiene un bucket tan largo con \"alumnoN\"? (pista:\n"
              << "    ¿qué rango de valores puede tomar la suma de 7 a 9 caracteres?)\n"
              << "  - ¿Cómo se comparan hashPolinomial y hashDjb2 con el hash ideal?\n"
              << "  - ¿Qué pasa con las mismas claves cuando m es 1024 en vez de 1009?\n";
}

int main()
{
    // ========================================================================
    // Ejercicio 1 — hashSuma
    // ========================================================================
    {
        // 'a' + 'b' + 'c' = 97 + 98 + 99 = 294
        chequear("Ej1 - hashSuma (\"abc\", m=1000)", hashSuma("abc", 1000) == 294);
        chequear("Ej1 - hashSuma (aplica módulo)", hashSuma("abc", 100) == 94);
        chequear("Ej1 - hashSuma (clave vacía)", hashSuma("", 13) == 0);
        chequear("Ej1 - hashSuma (anagramas colisionan)",
                 hashSuma("roma", 101) == hashSuma("amor", 101));
    }

    // ========================================================================
    // Ejercicio 2 — hashPolinomial
    // ========================================================================
    {
        // 97 * 31² + 98 * 31 + 99 = 96354
        chequear("Ej2 - hashPolinomial (\"abc\", m=1000000)", hashPolinomial("abc", 1000000) == 96354);
        // 98 * 31² + 99 * 31 + 97 = 97344
        chequear("Ej2 - hashPolinomial (el orden importa)", hashPolinomial("bca", 1000000) == 97344);
        chequear("Ej2 - hashPolinomial (clave vacía)", hashPolinomial("", 13) == 0);
        std::string larga(200, 'z');
        chequear("Ej2 - hashPolinomial (clave larga, resultado en rango)",
                 enRango(hashPolinomial(larga, 1009), 1009));
    }

    // ========================================================================
    // Ejercicio 3 — hashDjb2
    // ========================================================================
    {
        chequear("Ej3 - hashDjb2 (clave vacía = 5381)", hashDjb2("", 1000000) == 5381);
        // 5381 * 33 + 97 = 177670
        chequear("Ej3 - hashDjb2 (\"a\", m=1000000)", hashDjb2("a", 1000000) == 177670);
        // (177670 * 33 + 98) % 1000000 = 863208
        chequear("Ej3 - hashDjb2 (\"ab\", m=1000000)", hashDjb2("ab", 1000000) == 863208);
        std::string larga(200, 'z');
        chequear("Ej3 - hashDjb2 (clave larga, resultado en rango)",
                 enRango(hashDjb2(larga, 1009), 1009));
    }

    // ========================================================================
    // Ejercicio 4 — contarColisiones
    // ========================================================================
    {
        // Con hashLargo y m=10, los buckets son {1, 2, 2, 1, 3}: 2 colisiones.
        std::vector<std::string> claves = {"a", "bb", "cc", "d", "eee"};
        chequear("Ej4 - contarColisiones (ejemplo)", contarColisiones(claves, 10, hashLargo) == 2);
    }
    {
        std::vector<std::string> claves = {"a", "bb", "ccc"};
        chequear("Ej4 - contarColisiones (sin colisiones)", contarColisiones(claves, 10, hashLargo) == 0);
    }
    {
        std::vector<std::string> claves = {};
        chequear("Ej4 - contarColisiones (sin claves)", contarColisiones(claves, 10, hashLargo) == 0);
    }
    {
        std::vector<std::string> claves = {"aaa", "bbb", "ccc", "ddd"};
        chequear("Ej4 - contarColisiones (todas en el mismo bucket)",
                 contarColisiones(claves, 10, hashLargo) == 3);
    }

    // ========================================================================
    // Ejercicio 5 — bucketMasLargo
    // ========================================================================
    {
        std::vector<std::string> claves = {"a", "bb", "cc", "d", "eee", "ff"};
        chequear("Ej5 - bucketMasLargo (ejemplo)", bucketMasLargo(claves, 10, hashLargo) == 3);
    }
    {
        std::vector<std::string> claves = {};
        chequear("Ej5 - bucketMasLargo (sin claves)", bucketMasLargo(claves, 10, hashLargo) == 0);
    }
    {
        std::vector<std::string> claves = {"a", "bb", "ccc"};
        chequear("Ej5 - bucketMasLargo (sin colisiones)", bucketMasLargo(claves, 10, hashLargo) == 1);
    }

    // ========================================================================
    // Ejercicio 6 — insertarEncadenada
    // ========================================================================
    {
        TablaHash tabla(7, hashLargo);
        insertarEncadenada(tabla, "uno", 1);
        insertarEncadenada(tabla, "dos", 2);    // mismo largo que "uno": colisiona
        insertarEncadenada(tabla, "cuatro", 4);
        chequear("Ej6 - insertarEncadenada (cantidad)", tabla.cantidad == 3);
        chequear("Ej6 - insertarEncadenada (colisión en el mismo bucket)", tabla.buckets[3].size() == 2);
        chequear("Ej6 - insertarEncadenada (bucket correcto)", tabla.buckets[6].size() == 1);

        insertarEncadenada(tabla, "uno", 10);   // ya existía: actualiza
        chequear("Ej6 - insertarEncadenada (clave repetida no aumenta cantidad)", tabla.cantidad == 3);
        chequear("Ej6 - insertarEncadenada (clave repetida no duplica)", tabla.buckets[3].size() == 2);
    }

    // ========================================================================
    // Ejercicio 7 — buscarEncadenada
    // ========================================================================
    {
        TablaHash tabla(7, hashLargo);
        insertarEncadenada(tabla, "uno", 1);
        insertarEncadenada(tabla, "dos", 2);
        insertarEncadenada(tabla, "tres", 3);

        int valor = -1;
        chequear("Ej7 - buscarEncadenada (existe)", buscarEncadenada(tabla, "dos", valor) && valor == 2);
        valor = -1;
        chequear("Ej7 - buscarEncadenada (otra clave del mismo bucket)",
                 buscarEncadenada(tabla, "uno", valor) && valor == 1);
        valor = -1;
        chequear("Ej7 - buscarEncadenada (no existe)", !buscarEncadenada(tabla, "mil", valor) && valor == -1);

        insertarEncadenada(tabla, "uno", 10);
        chequear("Ej7 - buscarEncadenada (valor actualizado)",
                 buscarEncadenada(tabla, "uno", valor) && valor == 10);
    }
    {
        TablaHash tabla(5);
        int valor = -1;
        chequear("Ej7 - buscarEncadenada (tabla vacía)", !buscarEncadenada(tabla, "algo", valor));
    }

    // ========================================================================
    // Ejercicio 8 — borrarEncadenada
    // ========================================================================
    {
        TablaHash tabla(7, hashLargo);
        insertarEncadenada(tabla, "uno", 1);
        insertarEncadenada(tabla, "dos", 2);
        insertarEncadenada(tabla, "tres", 3);

        int valor = -1;
        chequear("Ej8 - borrarEncadenada (existe)", borrarEncadenada(tabla, "uno"));
        chequear("Ej8 - borrarEncadenada (cantidad)", tabla.cantidad == 2);
        chequear("Ej8 - borrarEncadenada (ya no se encuentra)", !buscarEncadenada(tabla, "uno", valor));
        chequear("Ej8 - borrarEncadenada (no afecta a la otra del bucket)",
                 buscarEncadenada(tabla, "dos", valor) && valor == 2);
        chequear("Ej8 - borrarEncadenada (borrar dos veces)", !borrarEncadenada(tabla, "uno"));
        chequear("Ej8 - borrarEncadenada (no existe)", !borrarEncadenada(tabla, "mil") && tabla.cantidad == 2);
    }

    // ========================================================================
    // Ejercicio 9 — factorDeCarga
    // ========================================================================
    {
        TablaHash tabla(4, hashLargo);
        chequear("Ej9 - factorDeCarga (tabla vacía)", factorDeCarga(tabla) == 0.0);
        insertarEncadenada(tabla, "a", 1);
        insertarEncadenada(tabla, "b", 2);
        insertarEncadenada(tabla, "cc", 3);
        chequear("Ej9 - factorDeCarga (3 / 4)", std::abs(factorDeCarga(tabla) - 0.75) < 1e-9);
        insertarEncadenada(tabla, "d", 4);
        insertarEncadenada(tabla, "e", 5);
        chequear("Ej9 - factorDeCarga (puede superar 1)", std::abs(factorDeCarga(tabla) - 1.25) < 1e-9);
    }

    // ========================================================================
    // Ejercicio 10 — rehash
    // ========================================================================
    {
        TablaHash tabla(2, hashLargo);
        std::vector<std::string> claves = {"a", "bb", "ccc", "dddd", "eeeee"};
        for (int i = 0; i < 5; i++) {
            insertarEncadenada(tabla, claves[static_cast<size_t>(i)], i);
        }
        rehash(tabla, 11);
        chequear("Ej10 - rehash (nuevo tamaño)", tabla.buckets.size() == 11);
        chequear("Ej10 - rehash (misma cantidad)", tabla.cantidad == 5);

        bool todasEnSuBucket = true;
        for (const std::string& clave : claves) {
            const auto& lista = tabla.buckets[clave.size()];
            if (lista.size() != 1 || lista[0].first != clave) todasEnSuBucket = false;
        }
        chequear("Ej10 - rehash (reubica cada clave en su nuevo bucket)", todasEnSuBucket);

        bool todasConSuValor = true;
        for (int i = 0; i < 5; i++) {
            int valor = -1;
            if (!buscarEncadenada(tabla, claves[static_cast<size_t>(i)], valor) || valor != i) {
                todasConSuValor = false;
            }
        }
        chequear("Ej10 - rehash (se conservan los valores)", todasConSuValor);
        chequear("Ej10 - rehash (baja el factor de carga)", factorDeCarga(tabla) < 0.5);
    }

    // ========================================================================
    // Ejercicio 11 — buscarAbierta
    // ========================================================================
    {
        // Armamos la tabla a mano para no depender de insertarAbierta.
        // Con hashLargo, "aaa", "bbb" y "ccc" quieren ir todas al slot 3.
        TablaAbierta tabla(7, hashLargo);
        tabla.slots[3].clave = "aaa"; tabla.slots[3].valor = 1; tabla.slots[3].estado = Estado::OCUPADO;
        tabla.slots[4].clave = "bbb"; tabla.slots[4].valor = 2; tabla.slots[4].estado = Estado::BORRADO;
        tabla.slots[5].clave = "ccc"; tabla.slots[5].valor = 3; tabla.slots[5].estado = Estado::OCUPADO;
        tabla.cantidad = 2;

        int valor = -1;
        chequear("Ej11 - buscarAbierta (en su posición)", buscarAbierta(tabla, "aaa", valor) && valor == 1);
        valor = -1;
        chequear("Ej11 - buscarAbierta (sigue sondeando y pasa el BORRADO)",
                 buscarAbierta(tabla, "ccc", valor) && valor == 3);
        valor = -1;
        chequear("Ej11 - buscarAbierta (lápida no cuenta como encontrada)",
                 !buscarAbierta(tabla, "bbb", valor) && valor == -1);
        chequear("Ej11 - buscarAbierta (no existe, corta en VACIO)", !buscarAbierta(tabla, "ddd", valor));
    }
    {
        // Tabla llena: la búsqueda de una clave ausente tiene que terminar.
        TablaAbierta tabla(3, hashLargo);
        for (size_t i = 0; i < 3; i++) {
            tabla.slots[i].clave = std::string(i, 'x');
            tabla.slots[i].estado = Estado::OCUPADO;
        }
        tabla.cantidad = 3;
        int valor = -1;
        chequear("Ej11 - buscarAbierta (tabla llena, no existe)", !buscarAbierta(tabla, "zz-no-esta", valor));
    }

    // ========================================================================
    // Ejercicio 12 — insertarAbierta
    // ========================================================================
    {
        TablaAbierta tabla(7, hashLargo);
        bool ok = insertarAbierta(tabla, "aaa", 1);
        ok = insertarAbierta(tabla, "bbb", 2) && ok;
        ok = insertarAbierta(tabla, "ccc", 3) && ok;
        chequear("Ej12 - insertarAbierta (devuelve true)", ok);
        chequear("Ej12 - insertarAbierta (cantidad)", tabla.cantidad == 3);
        chequear("Ej12 - insertarAbierta (linear probing: slots 3, 4, 5)",
                 tabla.slots[3].clave == "aaa" && tabla.slots[4].clave == "bbb" &&
                 tabla.slots[5].clave == "ccc" && tabla.slots[5].estado == Estado::OCUPADO);

        insertarAbierta(tabla, "bbb", 20);
        chequear("Ej12 - insertarAbierta (clave repetida actualiza)",
                 tabla.cantidad == 3 && tabla.slots[4].valor == 20);
    }
    {
        // Vuelta circular: con m = 5, "aaaa" va al 4 y "bbbb" tiene que ir al 0.
        TablaAbierta tabla(5, hashLargo);
        insertarAbierta(tabla, "aaaa", 1);
        insertarAbierta(tabla, "bbbb", 2);
        chequear("Ej12 - insertarAbierta (vuelta circular)",
                 tabla.slots[4].clave == "aaaa" && tabla.slots[0].clave == "bbbb");
    }
    {
        TablaAbierta tabla(3, hashLargo);
        insertarAbierta(tabla, "a", 1);
        insertarAbierta(tabla, "b", 2);
        insertarAbierta(tabla, "c", 3);
        chequear("Ej12 - insertarAbierta (tabla llena devuelve false)",
                 !insertarAbierta(tabla, "d", 4) && tabla.cantidad == 3);
    }
    {
        // Reutiliza el primer slot BORRADO de la secuencia.
        TablaAbierta tabla(7, hashLargo);
        tabla.slots[3].clave = "aaa"; tabla.slots[3].estado = Estado::BORRADO;
        tabla.slots[4].clave = "bbb"; tabla.slots[4].valor = 2; tabla.slots[4].estado = Estado::OCUPADO;
        tabla.cantidad = 1;
        insertarAbierta(tabla, "ddd", 4);
        chequear("Ej12 - insertarAbierta (reutiliza un slot BORRADO)",
                 tabla.slots[3].clave == "ddd" && tabla.slots[3].estado == Estado::OCUPADO &&
                 tabla.cantidad == 2);

        // Ahora "bbb" está DESPUÉS de una lápida: no tiene que duplicarse.
        tabla.slots[3].estado = Estado::BORRADO;
        tabla.cantidad = 1;
        insertarAbierta(tabla, "bbb", 20);
        chequear("Ej12 - insertarAbierta (no duplica una clave que está pasando la lápida)",
                 tabla.slots[3].estado == Estado::BORRADO && tabla.slots[4].valor == 20 &&
                 tabla.cantidad == 1);
    }

    // ========================================================================
    // Ejercicio 13 — borrarAbierta
    // ========================================================================
    {
        TablaAbierta tabla(7, hashLargo);
        insertarAbierta(tabla, "aaa", 1);
        insertarAbierta(tabla, "bbb", 2);
        insertarAbierta(tabla, "ccc", 3);

        chequear("Ej13 - borrarAbierta (existe)", borrarAbierta(tabla, "bbb"));
        chequear("Ej13 - borrarAbierta (cantidad)", tabla.cantidad == 2);
        chequear("Ej13 - borrarAbierta (deja una lápida, no VACIO)", tabla.slots[4].estado == Estado::BORRADO);

        int valor = -1;
        chequear("Ej13 - borrarAbierta (ya no se encuentra)", !buscarAbierta(tabla, "bbb", valor));
        chequear("Ej13 - borrarAbierta (\"ccc\" se sigue encontrando)",
                 buscarAbierta(tabla, "ccc", valor) && valor == 3);
        chequear("Ej13 - borrarAbierta (borrar dos veces)", !borrarAbierta(tabla, "bbb"));
        chequear("Ej13 - borrarAbierta (no existe)", !borrarAbierta(tabla, "zzz") && tabla.cantidad == 2);
    }

    // ========================================================================
    // Ejercicio 14 — contarPalabras
    // ========================================================================
    {
        std::vector<std::string> palabras = {"el", "gato", "y", "el", "perro", "y", "el", "loro"};
        std::unordered_map<std::string, int> esperado = {
            {"el", 3}, {"gato", 1}, {"y", 2}, {"perro", 1}, {"loro", 1}};
        chequear("Ej14 - contarPalabras (ejemplo)", contarPalabras(palabras) == esperado);
    }
    {
        std::vector<std::string> palabras = {};
        chequear("Ej14 - contarPalabras (vacío)", contarPalabras(palabras).empty());
    }

    // ========================================================================
    // Ejercicio 15 — primerRepetido
    // ========================================================================
    {
        chequear("Ej15 - primerRepetido ({3, 1, 4, 1, 3})", primerRepetido({3, 1, 4, 1, 3}) == 1);
        chequear("Ej15 - primerRepetido (sin repetidos)", primerRepetido({1, 2, 3}) == -1);
        chequear("Ej15 - primerRepetido (vacío)", primerRepetido({}) == -1);
        chequear("Ej15 - primerRepetido (negativos)", primerRepetido({-5, 2, -5}) == -5);
    }

    // ========================================================================
    // Ejercicio 16 — dosSuma
    // ========================================================================
    {
        chequear("Ej16 - dosSuma (existe)", dosSuma({2, 7, 11, 15}, 9));
        chequear("Ej16 - dosSuma (no existe)", !dosSuma({2, 7, 11, 15}, 10));
        chequear("Ej16 - dosSuma (no usar dos veces el mismo elemento)", !dosSuma({5, 1}, 10));
        chequear("Ej16 - dosSuma (elemento repetido)", dosSuma({5, 1, 5}, 10));
        chequear("Ej16 - dosSuma (vacío)", !dosSuma({}, 0));
    }

    // ========================================================================
    // Ejercicio 17 — sonAnagramas
    // ========================================================================
    {
        chequear("Ej17 - sonAnagramas (\"roma\", \"amor\")", sonAnagramas("roma", "amor"));
        chequear("Ej17 - sonAnagramas (distinto largo)", !sonAnagramas("roma", "ramos"));
        chequear("Ej17 - sonAnagramas (mismas letras, distintas cantidades)", !sonAnagramas("aab", "abb"));
        chequear("Ej17 - sonAnagramas (vacíos)", sonAnagramas("", ""));
    }

    // ========================================================================
    // Propuesto 1 — primerCaracterUnico
    // ========================================================================
    {
        chequear("P1 - primerCaracterUnico (\"abracadabra\")", primerCaracterUnico("abracadabra") == 'c');
        chequear("P1 - primerCaracterUnico (no hay)", primerCaracterUnico("aabb") == '\0');
        chequear("P1 - primerCaracterUnico (un solo carácter)", primerCaracterUnico("x") == 'x');
        chequear("P1 - primerCaracterUnico (vacío)", primerCaracterUnico("") == '\0');
    }

    // ========================================================================
    // Propuesto 2 — subarreglosConSumaK
    // ========================================================================
    {
        chequear("P2 - subarreglosConSumaK ({1, 1, 1}, 2)", subarreglosConSumaK({1, 1, 1}, 2) == 2);
        chequear("P2 - subarreglosConSumaK ({1, 2, 3}, 3)", subarreglosConSumaK({1, 2, 3}, 3) == 2);
        chequear("P2 - subarreglosConSumaK (con negativos)", subarreglosConSumaK({1, -1, 0}, 0) == 3);
        chequear("P2 - subarreglosConSumaK (vacío)", subarreglosConSumaK({}, 0) == 0);
    }

    // ========================================================================
    // Propuesto 3 — secuenciaConsecutivaMasLarga
    // ========================================================================
    {
        chequear("P3 - secuenciaConsecutivaMasLarga ({100, 4, 200, 1, 3, 2})",
                 secuenciaConsecutivaMasLarga({100, 4, 200, 1, 3, 2}) == 4);
        chequear("P3 - secuenciaConsecutivaMasLarga (con repetidos)",
                 secuenciaConsecutivaMasLarga({0, 3, 7, 2, 5, 8, 4, 6, 0, 1}) == 9);
        chequear("P3 - secuenciaConsecutivaMasLarga (todos iguales)",
                 secuenciaConsecutivaMasLarga({5, 5, 5}) == 1);
        chequear("P3 - secuenciaConsecutivaMasLarga (vacío)", secuenciaConsecutivaMasLarga({}) == 0);
    }

    // ========================================================================
    // Resumen
    // ========================================================================
    std::cout << "\nResultado: " << pruebasOk << "/" << totalPruebas
              << " pruebas pasadas." << std::endl;

    imprimirComparacion();

    if (pruebasOk == totalPruebas)
    {
        std::cout << "\nPara verificar que no hay memory leaks, corré: make valgrind" << std::endl;
    }

    return 0;
}
