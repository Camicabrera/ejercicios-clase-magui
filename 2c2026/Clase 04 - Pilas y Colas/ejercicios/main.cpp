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
    // Ejercicio 1 — Pila sobre arreglo
    // ========================================================================
    {
        PilaArreglo pila;
        chequear("Ej1 - constructor vacía", pila.empty());
        chequear("Ej1 - constructor tamanio 0", pila.tamanio() == 0);

        pila.push(10);
        chequear("Ej1 - push (no vacía)", !pila.empty());
        chequear("Ej1 - push (tamanio 1)", pila.tamanio() == 1);
        chequear("Ej1 - top() tras push", pila.top() == 10);

        pila.push(20);
        pila.push(30);
        chequear("Ej1 - top() es el último push", pila.top() == 30);
        chequear("Ej1 - tamanio 3", pila.tamanio() == 3);

        int valor = pila.pop();
        chequear("Ej1 - pop() devuelve el tope", valor == 30);
        chequear("Ej1 - pop() reduce tamanio", pila.tamanio() == 2);
        chequear("Ej1 - top() tras pop", pila.top() == 20);
    }

    {
        // Muchos push para forzar varias redimensiones.
        PilaArreglo pila;
        const int n = 1000;
        for (int i = 0; i < n; i++)
        {
            pila.push(i);
        }
        chequear("Ej1 - redimensionar (tamanio)", pila.tamanio() == static_cast<size_t>(n));

        bool ordenCorrecto = true;
        for (int i = n - 1; i >= 0; i--)
        {
            if (pila.pop() != i)
            {
                ordenCorrecto = false;
                break;
            }
        }
        chequear("Ej1 - redimensionar (orden LIFO preservado)", ordenCorrecto);
        chequear("Ej1 - redimensionar (vacía al final)", pila.empty());
    }

    {
        // Caso especial: vaciar completamente con pop() y volver a pushear
        // (la capacidad interna no debería quedar en un estado corrupto).
        PilaArreglo pila;
        pila.push(1);
        pila.pop();
        chequear("Ej1 - vacía tras único pop", pila.empty());

        pila.push(2);
        chequear("Ej1 - push tras vaciar", pila.top() == 2 && pila.tamanio() == 1);
    }

    // ========================================================================
    // Ejercicio 2 — Cola sobre arreglo (buffer circular)
    // ========================================================================
    {
        ColaArreglo cola;
        chequear("Ej2 - constructor vacía", cola.empty());
        chequear("Ej2 - constructor tamanio 0", cola.tamanio() == 0);

        cola.enqueue(10);
        chequear("Ej2 - enqueue (no vacía)", !cola.empty());
        chequear("Ej2 - front() tras enqueue", cola.front() == 10);

        cola.enqueue(20);
        cola.enqueue(30);
        chequear("Ej2 - front() sigue siendo el primero", cola.front() == 10);
        chequear("Ej2 - tamanio 3", cola.tamanio() == 3);

        int valor = cola.dequeue();
        chequear("Ej2 - dequeue() devuelve el frente", valor == 10);
        chequear("Ej2 - dequeue() reduce tamanio", cola.tamanio() == 2);
        chequear("Ej2 - front() tras dequeue", cola.front() == 20);
    }

    {
        // Alternar enqueue/dequeue para forzar que el buffer "de la vuelta"
        // y para forzar redimensiones.
        ColaArreglo cola;
        for (int i = 0; i < 5; i++)
        {
            cola.enqueue(i);
        }
        for (int i = 0; i < 3; i++)
        {
            cola.dequeue();
        }
        // Quedan [3, 4] en la cola; agregamos más para dar la vuelta.
        for (int i = 5; i < 10; i++)
        {
            cola.enqueue(i);
        }

        bool ordenCorrecto = true;
        for (int i = 3; i < 10; i++)
        {
            if (cola.dequeue() != i)
            {
                ordenCorrecto = false;
                break;
            }
        }
        chequear("Ej2 - buffer circular (orden FIFO preservado)", ordenCorrecto);
        chequear("Ej2 - buffer circular (vacía al final)", cola.empty());
    }

    {
        // Caso trampa: forzar una redimensión mientras el buffer está "dado
        // vuelta" (frente != 0), para verificar que el desenrollado copia los
        // elementos en el orden correcto y no solo desde el índice 0.
        ColaArreglo cola;
        cola.enqueue(1); // capacidad 1 -> llena, cantidad 1
        cola.enqueue(2); // redimensiona a capacidad 2; [1, 2], frente 0
        cola.dequeue();  // frente pasa a 1; queda [2] lógicamente
        cola.enqueue(3); // entra en la posición 0 (da la vuelta); [3, 2] físico
        cola.enqueue(4); // fuerza redimensionar con frente == 1

        bool ordenCorrecto = true;
        for (int i = 2; i <= 4; i++)
        {
            if (cola.dequeue() != i)
            {
                ordenCorrecto = false;
                break;
            }
        }
        chequear("Ej2 - redimensionar con buffer dado vuelta", ordenCorrecto);
    }

    {
        // Caso especial: vaciar con dequeue() y volver a enqueue.
        ColaArreglo cola;
        cola.enqueue(1);
        cola.dequeue();
        chequear("Ej2 - vacía tras único dequeue", cola.empty());

        cola.enqueue(2);
        chequear("Ej2 - enqueue tras vaciar", cola.front() == 2 && cola.tamanio() == 1);
    }

    // ========================================================================
    // Ejercicio 3 — Pila sobre lista enlazada
    // ========================================================================
    {
        PilaLista pila;
        chequear("Ej3 - constructor vacía", pila.empty());
        chequear("Ej3 - constructor tamanio 0", pila.tamanio() == 0);

        pila.push(10);
        pila.push(20);
        pila.push(30);
        chequear("Ej3 - top() es el último push", pila.top() == 30);
        chequear("Ej3 - tamanio 3", pila.tamanio() == 3);

        chequear("Ej3 - pop() LIFO (1)", pila.pop() == 30);
        chequear("Ej3 - pop() LIFO (2)", pila.pop() == 20);
        chequear("Ej3 - pop() LIFO (3)", pila.pop() == 10);
        chequear("Ej3 - vacía tras popear todo", pila.empty());
    }

    {
        // Caso especial: vaciar completamente con pop() y volver a pushear.
        PilaLista pila;
        pila.push(1);
        pila.pop();
        chequear("Ej3 - vacía tras único pop", pila.empty());

        pila.push(2);
        chequear("Ej3 - push tras vaciar", pila.top() == 2 && pila.tamanio() == 1);
    }

    // ========================================================================
    // Ejercicio 4 — Cola sobre lista enlazada
    // ========================================================================
    {
        ColaLista cola;
        chequear("Ej4 - constructor vacía", cola.empty());
        chequear("Ej4 - constructor tamanio 0", cola.tamanio() == 0);

        cola.enqueue(10);
        cola.enqueue(20);
        cola.enqueue(30);
        chequear("Ej4 - front() es el primer enqueue", cola.front() == 10);
        chequear("Ej4 - tamanio 3", cola.tamanio() == 3);

        chequear("Ej4 - dequeue() FIFO (1)", cola.dequeue() == 10);
        chequear("Ej4 - dequeue() FIFO (2)", cola.dequeue() == 20);
        chequear("Ej4 - dequeue() FIFO (3)", cola.dequeue() == 30);
        chequear("Ej4 - vacía tras dequeue de todo", cola.empty());
    }

    {
        // Caso especial: enqueue después de vaciar la cola.
        ColaLista cola;
        cola.enqueue(1);
        cola.dequeue();
        chequear("Ej4 - vacía tras único dequeue", cola.empty());

        cola.enqueue(2);
        chequear("Ej4 - enqueue tras vaciar", cola.front() == 2 && cola.tamanio() == 1);
    }

    // ========================================================================
    // Ejercicio 5 — Balanceo de expresiones
    // ========================================================================
    {
        chequear("Ej5 - balanceada simple", estaBalanceada("(a + b)"));
        chequear("Ej5 - balanceada anidada", estaBalanceada("(a + [b - {c}]) * 2"));
        chequear("Ej5 - balanceada vacía", estaBalanceada(""));
        chequear("Ej5 - balanceada sin símbolos", estaBalanceada("abc"));
        chequear("Ej5 - balanceada grupos consecutivos", estaBalanceada("()[]{}"));
        chequear("Ej5 - balanceada anidado del mismo tipo", estaBalanceada("((()))"));

        chequear("Ej5 - no balanceada (cruzados)", !estaBalanceada("(a + [b)]"));
        chequear("Ej5 - no balanceada (falta cerrar)", !estaBalanceada("(a + b"));
        chequear("Ej5 - no balanceada (cierre sin apertura)", !estaBalanceada("a + b)"));
        chequear("Ej5 - no balanceada (solo apertura)", !estaBalanceada("((("));
        chequear("Ej5 - no balanceada (un solo cierre)", !estaBalanceada(")"));
        chequear("Ej5 - no balanceada (un solo apertura)", !estaBalanceada("("));
        chequear("Ej5 - no balanceada (cierre de tipo distinto al abrir)",
                 !estaBalanceada("{(})"));
    }

    // ========================================================================
    // Ejercicio 6 — Evaluación de una expresión postfija
    // ========================================================================
    {
        chequear("Ej6 - suma simple", evaluarPostfija("2 3 +") == 5);
        chequear("Ej6 - precedencia (2 + 3*4)", evaluarPostfija("2 3 4 * +") == 14);
        chequear("Ej6 - resta", evaluarPostfija("10 4 -") == 6);
        chequear("Ej6 - division entera", evaluarPostfija("20 4 /") == 5);
        chequear("Ej6 - un solo numero", evaluarPostfija("42") == 42);
        chequear("Ej6 - expresion mas larga",
                 evaluarPostfija("5 1 2 + 4 * + 3 -") == 14);
        chequear("Ej6 - resultado negativo", evaluarPostfija("3 5 -") == -2);
        chequear("Ej6 - division trunca hacia cero", evaluarPostfija("7 2 /") == 3);
        chequear("Ej6 - multiplicacion por cero", evaluarPostfija("5 0 *") == 0);
        chequear("Ej6 - orden de operandos en resta anidada",
                 evaluarPostfija("8 4 2 / 2 * -") == 4);
    }

    // ========================================================================
    // Propuesto 1 — Invertir una pila con una cola auxiliar
    // ========================================================================
    {
        PilaArreglo pila;
        pila.push(1);
        pila.push(2);
        pila.push(3); // tope a fondo: 3, 2, 1

        invertirPila(pila);
        // tope a fondo esperado: 1, 2, 3
        chequear("P1 - invertirPila (tope)", pila.pop() == 1);
        chequear("P1 - invertirPila (medio)", pila.pop() == 2);
        chequear("P1 - invertirPila (fondo)", pila.pop() == 3);
        chequear("P1 - invertirPila (vacía al final)", pila.empty());
    }

    {
        // Caso especial: invertir pila vacía (no debería fallar).
        PilaArreglo pila;
        invertirPila(pila);
        chequear("P1 - invertirPila (vacía)", pila.empty());
    }

    {
        // Caso especial: un solo elemento (debe quedar igual).
        PilaArreglo pila;
        pila.push(42);
        invertirPila(pila);
        chequear("P1 - invertirPila (un elemento)", pila.pop() == 42 && pila.empty());
    }

    // ========================================================================
    // Propuesto 2 — Cola implementada con dos pilas
    // ========================================================================
    {
        ColaConDosPilas cola;
        chequear("P2 - constructor vacía", cola.empty());
        chequear("P2 - constructor tamanio 0", cola.tamanio() == 0);

        cola.enqueue(10);
        cola.enqueue(20);
        cola.enqueue(30);
        chequear("P2 - front() es el primer enqueue", cola.front() == 10);
        chequear("P2 - tamanio 3", cola.tamanio() == 3);

        chequear("P2 - dequeue() FIFO (1)", cola.dequeue() == 10);

        // Intercalar enqueue/dequeue para forzar el volcado entre pilas.
        cola.enqueue(40);
        chequear("P2 - dequeue() FIFO (2)", cola.dequeue() == 20);
        chequear("P2 - dequeue() FIFO (3)", cola.dequeue() == 30);
        chequear("P2 - dequeue() FIFO (4)", cola.dequeue() == 40);
        chequear("P2 - vacía tras dequeue de todo", cola.empty());
    }

    {
        // Caso trampa: alternar enqueue/dequeue de a uno, lo que fuerza un
        // volcado entre pilas en cada dequeue (salida siempre queda vacía).
        ColaConDosPilas cola;
        bool ordenCorrecto = true;
        for (int i = 0; i < 5; i++)
        {
            cola.enqueue(i);
            if (cola.dequeue() != i)
            {
                ordenCorrecto = false;
            }
        }
        chequear("P2 - alternar enqueue/dequeue (volcado constante)", ordenCorrecto);
        chequear("P2 - vacía tras alternar", cola.empty());
    }

    {
        // front() no debe consumir el elemento.
        ColaConDosPilas cola;
        cola.enqueue(7);
        cola.front();
        chequear("P2 - front() no consume", cola.front() == 7 && cola.tamanio() == 1);
    }

    // ========================================================================
    // Propuesto 3 — Pila con mínimo en O(1)
    // ========================================================================
    {
        PilaConMinimo pila;
        chequear("P3 - constructor vacía", pila.empty());

        pila.push(5);
        chequear("P3 - minimo() con un elemento", pila.minimo() == 5);

        pila.push(2);
        pila.push(8);
        chequear("P3 - minimo() tras push mayores", pila.minimo() == 2);
        chequear("P3 - top() sigue siendo el último push", pila.top() == 8);

        pila.push(1);
        chequear("P3 - minimo() actualizado con un nuevo mínimo", pila.minimo() == 1);

        chequear("P3 - pop() del nuevo mínimo", pila.pop() == 1);
        chequear("P3 - minimo() vuelve al anterior tras pop", pila.minimo() == 2);

        pila.pop(); // saca el 8
        chequear("P3 - minimo() no cambia si no se saca el mínimo", pila.minimo() == 2);

        pila.pop(); // saca el 2 (el mínimo)
        chequear("P3 - minimo() vuelve a 5 tras sacar el mínimo", pila.minimo() == 5);
        chequear("P3 - tamanio 1", pila.tamanio() == 1);
    }

    {
        // Caso especial: empujar valores repetidos iguales al mínimo.
        PilaConMinimo pila;
        pila.push(3);
        pila.push(3);
        chequear("P3 - minimo con repetidos", pila.minimo() == 3);

        pila.pop();
        chequear("P3 - minimo tras sacar uno de los repetidos", pila.minimo() == 3);

        pila.pop();
        chequear("P3 - vacía tras sacar todos los repetidos", pila.empty());
    }

    {
        // Caso especial: vaciar completamente y volver a pushear (la pila de
        // mínimos no debería quedar en un estado corrupto).
        PilaConMinimo pila;
        pila.push(5);
        pila.pop();
        chequear("P3 - vacía tras único pop", pila.empty());

        pila.push(10);
        chequear("P3 - minimo tras vaciar y pushear", pila.minimo() == 10);
    }

    // ========================================================================
    // Propuesto 4 — Conversión de infija a postfija
    // ========================================================================
    {
        chequear("P4 - suma simple", infijaAPostfija("3 + 4") == "3 4 +");
        chequear("P4 - precedencia (3 + 4*2)",
                 infijaAPostfija("3 + 4 * 2") == "3 4 2 * +");
        chequear("P4 - parentesis", infijaAPostfija("( 3 + 4 ) * 2") == "3 4 + 2 *");
        chequear("P4 - asociatividad izquierda resta",
                 infijaAPostfija("8 - 4 - 2") == "8 4 - 2 -");
        chequear("P4 - asociatividad izquierda division",
                 infijaAPostfija("8 / 4 / 2") == "8 4 / 2 /");
        chequear("P4 - parentesis anidados",
                 infijaAPostfija("( ( 1 + 2 ) * 3 )") == "1 2 + 3 *");

        // Verificación cruzada: evaluar el resultado postfijo debe dar el
        // mismo valor que evaluar la expresión infija "a mano".
        chequear("P4 - round-trip con evaluarPostfija (1)",
                 evaluarPostfija(infijaAPostfija("2 + 3 * 4")) == 14);
        chequear("P4 - round-trip con evaluarPostfija (2)",
                 evaluarPostfija(infijaAPostfija("( 2 + 3 ) * 4")) == 20);
        chequear("P4 - round-trip con evaluarPostfija (3, asociatividad izquierda)",
                 evaluarPostfija(infijaAPostfija("10 - 2 - 3")) == 5);
    }

    // ========================================================================
    // Propuesto 5 — Sistema de deshacer/rehacer
    // ========================================================================
    {
        EditorDeshacerRehacer editor(0);
        chequear("P5 - estado inicial", editor.estado() == 0);
        chequear("P5 - no puede deshacer al inicio", !editor.puedeDeshacer());
        chequear("P5 - no puede rehacer al inicio", !editor.puedeRehacer());

        editor.aplicar(1);
        editor.aplicar(2);
        editor.aplicar(3);
        chequear("P5 - estado tras aplicar acciones", editor.estado() == 3);
        chequear("P5 - puede deshacer", editor.puedeDeshacer());

        chequear("P5 - deshacerAccion (1)", editor.deshacerAccion() == 2);
        chequear("P5 - deshacerAccion (2)", editor.deshacerAccion() == 1);
        chequear("P5 - puede rehacer tras deshacer", editor.puedeRehacer());

        chequear("P5 - rehacerAccion (1)", editor.rehacerAccion() == 2);
        chequear("P5 - estado tras rehacer", editor.estado() == 2);

        // Aplicar una acción nueva debe invalidar el historial de rehacer.
        editor.aplicar(99);
        chequear("P5 - aplicar invalida el rehacer", !editor.puedeRehacer());
        chequear("P5 - estado tras aplicar nueva accion", editor.estado() == 99);

        chequear("P5 - deshacer tras aplicar nueva accion", editor.deshacerAccion() == 2);
        chequear("P5 - puede deshacer hasta el estado inicial", editor.deshacerAccion() == 1);
        chequear("P5 - deshacer hasta el estado 0", editor.deshacerAccion() == 0);
        chequear("P5 - ya no puede deshacer más", !editor.puedeDeshacer());
    }

    {
        // Caso trampa: deshacer y rehacer intercalados varias veces seguidas.
        EditorDeshacerRehacer editor(0);
        editor.aplicar(1);
        editor.aplicar(2);

        chequear("P5 - intercalado: deshacer (1)", editor.deshacerAccion() == 1);
        chequear("P5 - intercalado: rehacer (1)", editor.rehacerAccion() == 2);
        chequear("P5 - intercalado: deshacer (2)", editor.deshacerAccion() == 1);
        chequear("P5 - intercalado: deshacer (3)", editor.deshacerAccion() == 0);
        chequear("P5 - intercalado: no puede deshacer más", !editor.puedeDeshacer());
        chequear("P5 - intercalado: rehacer (2)", editor.rehacerAccion() == 1);
        chequear("P5 - intercalado: rehacer (3)", editor.rehacerAccion() == 2);
        chequear("P5 - intercalado: no puede rehacer más", !editor.puedeRehacer());
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
