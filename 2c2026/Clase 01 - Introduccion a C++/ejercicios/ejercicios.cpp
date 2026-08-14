#include "ejercicios.h"
#include <cmath>

// ============================================================================
// Acá va TU código. Cada función tiene una cáscara con un "TODO": borrá el
// contenido de ejemplo y escribí la implementación.
//
// Los `(void)parametro;` que ves abajo están solo para que la cáscara
// compile sin advertencias antes de que la implementes. Cuando uses el
// parámetro en tu código, borrá la línea `(void)...` correspondiente.
// ============================================================================

// Ejercicio 1 — Hola, C++
std::string saludo(const std::string &nombre, int edad)
{
    // TODO: armar y devolver el saludo con el formato pedido.
    return "Hola " + nombre + ", tenes " + std::to_string(edad) + " anios.";
}

// Ejercicio 2 — Par o impar
bool esPar(int numero)
{
    // TODO: devolver true si numero es par.
    return numero % 2 == 0;
}

// Ejercicio 3 — Tabla de multiplicar
std::vector<int> tablaDeMultiplicar(int n)
{
    // TODO: llenar el vector con n*1, n*2, ..., n*10 y devolverlo.
    std::vector<int> tabla;
    for (int i = 1; i < 11; i++)
    {
        tabla.push_back(i * n);
    }
    return tabla;
}

// Ejercicio 4 — esPrimo
bool esPrimo(int n)
{
    // TODO: determinar si n es primo.
    if (n < 2)
    {
        return false;
    }

    int i = 2;
    while (i < n)
    {
        if (n % i == 0)
        {
            return false;
        }
        i++;
    }
    return true;
}

// Ejercicio 5 — swap por referencia
void swap(int &a, int &b)
{
    // TODO: intercambiar los valores de a y b.
    int tmp = a;
    a = b;
    b = tmp;
}

// Ejercicio 6 — Sobrecarga: maximo
int maximo(int a, int b)
{
    // TODO: devolver el mayor entre a y b.
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

double maximo(double a, double b)
{
    // TODO: devolver el mayor entre a y b.
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

// Ejercicio 7 — Promedio de un arreglo
double promedioArreglo(const int numeros[], int tamanio)
{
    // TODO: sumar los elementos y dividir por tamanio (ojo con la división entera).
    int total = 0;
    for (int i = 0; i < tamanio; i++)
    {
        total = total + numeros[i];
    }
    return total / tamanio;
}

// Ejercicio 8 — vector de notas
double promedio(const std::vector<double> &notas)
{
    // TODO: devolver el promedio de las notas.
    double total = 0.0;
    for (unsigned int i = 0; i < notas.size(); i++)
    {
        total = total + notas[i];
    }
    return total / double(notas.size());
}

double maxima(const std::vector<double> &notas)
{
    // TODO: devolver la nota más alta.
    double maxima = 0;
    for (unsigned int i = 0; i < notas.size(); i++)
    {
        if (notas[i] > maxima)
        {
            maxima = notas[i];
        }
    }
    return maxima;
}

// Ejercicio 9 — Contar vocales
int esVocal(const char &letra)
{
    return (letra == 'a' || letra == 'e' || letra == 'i' || letra == 'o' || letra == 'u');
}

int contarVocales(const std::string &texto)
{
    // TODO: contar vocales sin distinguir mayúsculas de minúsculas.
    int cantidadVocales = 0;
    for (unsigned int i = 0; i < texto.size(); i++)
    {
        cantidadVocales += esVocal(texto[i]);
    }
    return cantidadVocales;
}

// Propuesto 1 — invertir in-place
void invertir(std::vector<int> &v)
{
    // TODO: invertir el orden de los elementos sin crear otro vector.
    for (unsigned int i = 0; i < v.size() / 2; i++)
    {
        swap(v[i], v[v.size() - 1 - i]);
    }
}

// Propuesto 2 — contar palabras
int contarPalabras2(const std::string &oracion)
{
    // TODO: contar palabras separadas por un único espacio.
    int cantidadPalabras = 1;
    const char espacio = ' ';
    for (unsigned int i = 0; i < oracion.size(); i++)
    {
        if (oracion[i] == espacio)
        {
            cantidadPalabras++;
        }
    }
    return cantidadPalabras;
}

// Propuesto 3 — contar palabras extra
int contarPalabras(const std::string &oracion)
{
    // TODO: contar palabras separadas por un único espacio.
    int cantidadPalabras = 0;
    unsigned int i = 0;
    const char espacio = ' ';

    while (i < oracion.size())
    {
        if (oracion[i] == espacio)
        {
            i++;
        }
        else
        {
            while (i < oracion.size() && oracion[i] != espacio)
            {
                i++;
            }
            cantidadPalabras++;
        }
    }
    return cantidadPalabras;
}

// Ejercicio 10 — Clase Punto
Punto::Punto(double xInicial, double yInicial)
{
    // TODO: inicializar x e y con los valores recibidos.
    (void)xInicial;
    (void)yInicial;
}

double Punto::distanciaAlOrigen() const
{
    // TODO: devolver la distancia entre este punto y el origen (0, 0).
    return 0.0;
}

double Punto::distanciaA(const Punto &otro) const
{
    // TODO: devolver la distancia entre este punto y "otro".
    (void)otro;
    return 0.0;
}

// Ejercicio 11 — Clase Rectangulo
Rectangulo::Rectangulo(double baseInicial, double alturaInicial)
{
    // TODO: inicializar base y altura con los valores recibidos.
    (void)baseInicial;
    (void)alturaInicial;
}

double Rectangulo::area() const
{
    // TODO: devolver el área del rectángulo (base * altura).
    return 0.0;
}

double Rectangulo::perimetro() const
{
    // TODO: devolver el perímetro del rectángulo (2 * (base + altura)).
    return 0.0;
}

bool Rectangulo::esCuadrado() const
{
    // TODO: devolver true si el rectángulo es un cuadrado (base == altura).
    return false;
}
