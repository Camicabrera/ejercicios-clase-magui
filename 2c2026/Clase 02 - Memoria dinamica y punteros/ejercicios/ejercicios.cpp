#include "ejercicios.h"

// ============================================================================
// Acá va TU código. Cada función tiene una cáscara con un "TODO": borrá el
// contenido de ejemplo y escribí la implementación.
//
// Los `(void)parametro;` que ves abajo están solo para que la cáscara
// compile sin advertencias antes de que la implementes. Cuando uses el
// parámetro en tu código, borrá la línea `(void)...` correspondiente.
// ============================================================================

// Ejercicio 1 — Mi primer puntero
void duplicarPuntero(int *x)
{
    // TODO: duplicar el valor apuntado por x.
    (void)x;
}

// Ejercicio 2 — Puntero vs referencia
void duplicarReferencia(int &x)
{
    // TODO: duplicar x (recibido por referencia).
    (void)x;
}

// Ejercicio 3 — Arreglo dinámico con new[]
int *crearArregloDeCuadrados(int n)
{
    // TODO: reservar un arreglo de n enteros con new[] y llenarlo con los
    // cuadrados de 0 a n-1.
    (void)n;
    return nullptr;
}

// Ejercicio 4 — Aritmética de punteros (lectura)
int sumarArregloPuntero(const int *arreglo, int tamanio)
{
    // TODO: sumar los tamanio elementos de arreglo usando *(arreglo + i).
    (void)arreglo;
    (void)tamanio;
    return 0;
}

// Ejercicio 5 — Aritmética de punteros (escritura)
void duplicarValores(int *arreglo, int tamanio)
{
    // TODO: duplicar cada elemento in-place usando *(arreglo + i) = ...
    (void)arreglo;
    (void)tamanio;
}

// Ejercicio 6 — Struct en el heap: constructor y destructor
int personasDestruidas = 0;

Persona::Persona(const std::string &nombreInicial, int edadInicial)
{
    // TODO: inicializar nombre y edad con los valores recibidos.
    (void)nombreInicial;
    (void)edadInicial;
}

Persona::~Persona()
{
    // TODO: incrementar personasDestruidas para avisar que este objeto murió.
}

Persona *crearPersona(const std::string &nombre, int edad)
{
    // TODO: reservar una Persona en el heap con new, usando el constructor,
    // y devolver el puntero.
    (void)nombre;
    (void)edad;
    return nullptr;
}

// Ejercicio 7 — Redimensionar un arreglo dinámico
int *agregarElemento(int *arreglo, int tamanioActual, int nuevoElemento)
{
    // TODO: crear un nuevo arreglo de tamaño (tamanioActual + 1), copiar los
    // elementos viejos, agregar nuevoElemento al final, liberar el arreglo
    // viejo, y devolver el nuevo.
    (void)arreglo;
    (void)tamanioActual;
    (void)nuevoElemento;
    return nullptr;
}

// Ejercicio 8 — Lista enlazada dinámica
Nodo *crearCadena(const std::vector<int> &valores)
{
    // TODO: crear un nodo por cada valor de `valores` (en el mismo orden),
    // enlazarlos con `siguiente`, y devolver un puntero al primero.
    (void)valores;
    return nullptr;
}

int sumarCadena(const Nodo *cabeza)
{
    // TODO: recorrer la cadena sumando los valores de cada nodo.
    (void)cabeza;
    return 0;
}

void liberarCadena(Nodo *cabeza)
{
    // TODO: liberar TODOS los nodos de la cadena, uno por uno.
    (void)cabeza;
}

// Propuesto 1 — Matriz dinámica
void liberarMatriz(int **matriz, int filas)
{
    // TODO: liberar cada fila (con delete[]) y después el arreglo de
    // punteros (también con delete[]).
    (void)matriz;
    (void)filas;
}
