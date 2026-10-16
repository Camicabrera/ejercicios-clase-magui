#include "ejercicios.h"
#include <unordered_set>

// ============================================================================
// Acá va TU código. Cada función tiene una cáscara con un "TODO": borrá el
// contenido de ejemplo y escribí la implementación.
//
// Los `(void)parametro;` que ves abajo están solo para que la cáscara
// compile sin advertencias antes de que la implementes. Cuando uses el
// parámetro en tu código, borrá la línea `(void)...` correspondiente.
//
// Ojo con -Wconversion: para pasar de char a número usá
// static_cast<unsigned char>(c), y para pasar entre int, size_t y
// unsigned long usá static_cast.
// ============================================================================

// ============================================================================
// PARTE 1 — FUNCIONES DE HASH
// ============================================================================

// Ejercicio 1 — Hash por suma de caracteres
int hashSuma(const std::string& clave, int m)
{
    // TODO: implementar hashSuma.
    // Recordá:
    //   - Acumulá en un `unsigned long` la suma de todos los caracteres.
    //   - Al final devolvé suma % m (convertido a int).
    (void)clave;
    (void)m;
    return 0;
}

// Ejercicio 2 — Hash polinomial (base 31)
int hashPolinomial(const std::string& clave, int m)
{
    // TODO: implementar hashPolinomial.
    // Recordá:
    //   - Arrancá con suma = 0 (unsigned long).
    //   - Por cada carácter c: suma = suma * 31 + c.
    //   - Al final devolvé suma % m (convertido a int).
    (void)clave;
    (void)m;
    return 0;
}

// Ejercicio 3 — Hash djb2 (Dan Bernstein)
int hashDjb2(const std::string& clave, int m)
{
    // TODO: implementar hashDjb2.
    // Recordá:
    //   - Arrancá con hash = 5381 (unsigned long).
    //   - Por cada carácter c: hash = hash * 33 + c.
    //   - Al final devolvé hash % m (convertido a int).
    (void)clave;
    (void)m;
    return 0;
}

// Ejercicio 4 — Contar colisiones
int contarColisiones(const std::vector<std::string>& claves, int m, FuncionHash funcion)
{
    // TODO: implementar contarColisiones.
    // Recordá:
    //   - Una función de hash pasada como parámetro se llama igual que
    //     cualquier otra: funcion(clave, m).
    //   - Llevá un std::vector<bool> de tamaño m que indique qué buckets ya
    //     están ocupados.
    //   - Si una clave cae en un bucket ocupado, es una colisión.
    (void)claves;
    (void)m;
    (void)funcion;
    return 0;
}

// Ejercicio 5 — Bucket más largo
int bucketMasLargo(const std::vector<std::string>& claves, int m, FuncionHash funcion)
{
    // TODO: implementar bucketMasLargo.
    // Recordá:
    //   - Llevá un std::vector<int> de tamaño m con la cantidad de claves
    //     que cayó en cada bucket.
    //   - Devolvé el máximo de esas cantidades.
    (void)claves;
    (void)m;
    (void)funcion;
    return 0;
}

// ============================================================================
// PARTE 2 — TABLA DE HASH CON ENCADENAMIENTO (CHAINING)
// ============================================================================

// Tip: te puede servir escribir una función auxiliar que calcule el índice
// de una clave: tabla.funcion(clave, cantidad de buckets).

// Ejercicio 6 — Insertar (encadenamiento)
void insertarEncadenada(TablaHash& tabla, const std::string& clave, int valor)
{
    // TODO: implementar insertarEncadenada.
    // Recordá:
    //   - Calculá el índice con tabla.funcion(clave, m).
    //   - Recorré la lista de ese bucket: si la clave ya está, actualizá
    //     el valor y terminá.
    //   - Si no está, agregá el par al final de la lista y aumentá
    //     tabla.cantidad.
    (void)tabla;
    (void)clave;
    (void)valor;
}

// Ejercicio 7 — Buscar (encadenamiento)
bool buscarEncadenada(const TablaHash& tabla, const std::string& clave, int& valor)
{
    // TODO: implementar buscarEncadenada.
    // Recordá:
    //   - Solo hace falta mirar la lista del bucket de la clave.
    //   - Si la encontrás, guardá el valor en `valor` y devolvé true.
    (void)tabla;
    (void)clave;
    (void)valor;
    return false;
}

// Ejercicio 8 — Borrar (encadenamiento)
bool borrarEncadenada(TablaHash& tabla, const std::string& clave)
{
    // TODO: implementar borrarEncadenada.
    // Recordá:
    //   - Buscá la clave en la lista de su bucket.
    //   - Si está, sacala de la lista (lista.erase(lista.begin() + j)),
    //     disminuí tabla.cantidad y devolvé true.
    (void)tabla;
    (void)clave;
    return false;
}

// Ejercicio 9 — Factor de carga
double factorDeCarga(const TablaHash& tabla)
{
    // TODO: implementar factorDeCarga.
    // Recordá: α = n / m, pero convertí ambos a double antes de dividir.
    (void)tabla;
    return -1.0;
}

// Ejercicio 10 — Rehash
void rehash(TablaHash& tabla, int nuevoM)
{
    // TODO: implementar rehash.
    // Recordá:
    //   - Guardá una copia de los buckets viejos.
    //   - Reemplazá los buckets por nuevoM listas vacías
    //     (tabla.buckets.assign(nuevoM, {})) y poné la cantidad en 0.
    //   - Reinsertá cada par de los buckets viejos con insertarEncadenada.
    (void)tabla;
    (void)nuevoM;
}

// ============================================================================
// PARTE 3 — DIRECCIONAMIENTO ABIERTO (LINEAR PROBING)
// ============================================================================

// Tip: las tres operaciones necesitan "encontrar la posición de una clave".
// Escribí una función auxiliar que devuelva esa posición (o -1 si no está)
// y usala en buscar, insertar y borrar.

// Ejercicio 11 — Buscar (linear probing)
bool buscarAbierta(const TablaAbierta& tabla, const std::string& clave, int& valor)
{
    // TODO: implementar buscarAbierta.
    // Recordá:
    //   - Probá las posiciones (h + i) % m para i = 0, 1, ..., m - 1.
    //   - VACIO: la clave no está, cortá.
    //   - OCUPADO con la misma clave: encontrada.
    //   - BORRADO u OCUPADO con otra clave: seguí sondeando.
    (void)tabla;
    (void)clave;
    (void)valor;
    return false;
}

// Ejercicio 12 — Insertar (linear probing)
bool insertarAbierta(TablaAbierta& tabla, const std::string& clave, int valor)
{
    // TODO: implementar insertarAbierta.
    // Recordá:
    //   - Primero fijate si la clave ya está (¡aunque haya lápidas antes!):
    //     si está, actualizá el valor y devolvé true.
    //   - Si no está, recorré la secuencia de sondeo y usá el primer slot
    //     que NO esté OCUPADO (VACIO o BORRADO). Aumentá tabla.cantidad.
    //   - Si recorriste los m slots y estaban todos ocupados, devolvé false.
    (void)tabla;
    (void)clave;
    (void)valor;
    return false;
}

// Ejercicio 13 — Borrar (linear probing)
bool borrarAbierta(TablaAbierta& tabla, const std::string& clave)
{
    // TODO: implementar borrarAbierta.
    // Recordá:
    //   - Buscá la posición de la clave.
    //   - Si está, marcá el slot como Estado::BORRADO (no VACIO),
    //     disminuí tabla.cantidad y devolvé true.
    (void)tabla;
    (void)clave;
    return false;
}

// ============================================================================
// PARTE 4 — USANDO DICCIONARIOS DE LA STL
// ============================================================================

// Ejercicio 14 — Contar palabras
std::unordered_map<std::string, int> contarPalabras(const std::vector<std::string>& palabras)
{
    // TODO: implementar contarPalabras.
    // Recordá: conteo[palabra]++ funciona aunque la palabra no esté todavía
    // (operator[] la crea con valor 0).
    (void)palabras;
    return {};
}

// Ejercicio 15 — Primer repetido
int primerRepetido(const std::vector<int>& v)
{
    // TODO: implementar primerRepetido.
    // Recordá:
    //   - Usá un std::unordered_set<int> con los elementos ya vistos.
    //   - Si el elemento actual ya estaba (vistos.count(x) > 0), es el
    //     primer repetido.
    (void)v;
    return -2;
}

// Ejercicio 16 — Dos suma
bool dosSuma(const std::vector<int>& v, int objetivo)
{
    // TODO: implementar dosSuma.
    // Recordá:
    //   - Recorré el vector guardando en un unordered_set lo que ya viste.
    //   - Para cada x, si (objetivo - x) ya está en el set, encontraste el par.
    //   - Insertá x en el set DESPUÉS de preguntar (así no usás el mismo
    //     elemento dos veces).
    (void)v;
    (void)objetivo;
    return false;
}

// Ejercicio 17 — Anagramas
bool sonAnagramas(const std::string& a, const std::string& b)
{
    // TODO: implementar sonAnagramas.
    // Recordá:
    //   - Si tienen distinto largo, no pueden ser anagramas.
    //   - Sumá 1 por cada letra de `a` y restá 1 por cada letra de `b` en un
    //     std::unordered_map<char, int>. ¿Qué tiene que pasar al final?
    (void)a;
    (void)b;
    return false;
}

// ============================================================================
// EJERCICIOS PROPUESTOS
// ============================================================================

// Propuesto 1 — Primer carácter único
char primerCaracterUnico(const std::string& s)
{
    // TODO: implementar primerCaracterUnico.
    // Pista: dos pasadas. En la primera contás, en la segunda buscás el
    // primero con cuenta 1.
    (void)s;
    return '?';
}

// Propuesto 2 — Subarreglos con suma k
int subarreglosConSumaK(const std::vector<int>& v, int k)
{
    // TODO: implementar subarreglosConSumaK.
    // Pista:
    //   - std::unordered_map<int, int> prefijos; prefijos[0] = 1;
    //   - Llevá la suma acumulada. En cada paso, sumá al total cuántas
    //     veces apareció (suma - k) como suma prefija, y después registrá
    //     la suma actual.
    (void)v;
    (void)k;
    return -1;
}

// Propuesto 3 — Secuencia consecutiva más larga
int secuenciaConsecutivaMasLarga(const std::vector<int>& v)
{
    // TODO: implementar secuenciaConsecutivaMasLarga.
    // Pista:
    //   - Meté todos los números en un std::unordered_set<int>.
    //   - Para cada x del set que sea inicio de secuencia (x - 1 no está),
    //     contá cuántos x + 1, x + 2, ... están.
    //   - ¿Por qué esto es O(n) y no O(n²)?
    (void)v;
    return -1;
}
