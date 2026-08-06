/**
 * Tests para Práctica 5 - Pilas, Colas y Heaps
 * ==============================================
 *
 * Este archivo contiene todos los tests. Los tests están diseñados para
 * correr incluso si las funciones no están implementadas (devuelven -1
 * o no hacen nada). Así podés ir implementando ejercicio por ejercicio.
 */

#include "testing.h"

int tests_total = 0;
int tests_ok = 0;
int tests_fail = 0;

/* ========================================================================
 * Declaraciones de funciones que los alumnos deben implementar
 * ======================================================================== */

// Estructuras
typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
    int size;
} Stack;

typedef struct {
    Node* front;
    Node* rear;
    int size;
} Queue;

typedef struct {
    int* data;
    int size;
    int capacity;
} Heap;

// Funciones auxiliares (implementadas en ejercicios.c)
extern Stack* stack_create(void);
extern void stack_destroy(Stack* s);
extern int stack_empty(Stack* s);
extern int stack_top(Stack* s);
extern Queue* queue_create(void);
extern void queue_destroy(Queue* q);
extern int queue_empty(Queue* q);
extern int queue_front(Queue* q);
extern Heap* heap_create(void);
extern void heap_destroy(Heap* h);
extern int heap_min(Heap* h);

// Funciones a implementar por los alumnos
extern int stack_push(Stack* s, int data);
extern int stack_pop(Stack* s);
extern int queue_enqueue(Queue* q, int data);
extern int queue_dequeue(Queue* q);
extern void heap_up(Heap* h, int i);
extern int heap_insert(Heap* h, int data);

/* ========================================================================
 * TEST EJERCICIO 1: Apilar
 * ======================================================================== */

void test_ejercicio_1(void) {
    SECCION("EJERCICIO 1: Apilar (Push)");

    Stack* s = stack_create();

    TEST("crear pila devuelve no-NULL");
    ASSERT_NOT_NULL(s);
    if (!s) return;

    TEST("pila nueva está vacía");
    ASSERT_TRUE(stack_empty(s));

    TEST("apilar primer elemento devuelve 0");
    int res = stack_push(s, 10);
    ASSERT_EQ_INT(0, res);

    if (res == 0) {
        TEST("tope después de apilar 10");
        ASSERT_EQ_INT(10, stack_top(s));

        TEST("tamaño después de apilar 1 elemento");
        ASSERT_EQ_INT(1, s->size);

        TEST("pila ya no está vacía");
        ASSERT_TRUE(!stack_empty(s));

        TEST("apilar segundo elemento");
        ASSERT_EQ_INT(0, stack_push(s, 20));

        TEST("tope después de apilar 20");
        ASSERT_EQ_INT(20, stack_top(s));

        TEST("tamaño después de apilar 2 elementos");
        ASSERT_EQ_INT(2, s->size);

        TEST("apilar tercer elemento");
        ASSERT_EQ_INT(0, stack_push(s, 30));

        TEST("tope después de apilar 30");
        ASSERT_EQ_INT(30, stack_top(s));

        TEST("tamaño después de apilar 3 elementos");
        ASSERT_EQ_INT(3, s->size);
    } else {
        printf("  (saltando tests de apilar - no implementado)\n");
    }

    stack_destroy(s);
}

/* ========================================================================
 * TEST EJERCICIO 2: Desapilar
 * ======================================================================== */

void test_ejercicio_2(void) {
    SECCION("EJERCICIO 2: Desapilar (Pop)");

    Stack* s = stack_create();
    if (!s) return;

    TEST("desapilar pila vacía devuelve -1");
    ASSERT_EQ_INT(-1, stack_pop(s));

    // Apilar algunos elementos para probar desapilar
    int ok = stack_push(s, 10);
    ok = ok == 0 ? stack_push(s, 20) : ok;
    ok = ok == 0 ? stack_push(s, 30) : ok;

    if (ok != 0) {
        printf("  (saltando tests de desapilar - apilar no implementado)\n");
        stack_destroy(s);
        return;
    }

    // Pila: top -> [30] -> [20] -> [10] -> NULL

    TEST("desapilar devuelve último apilado (30)");
    ASSERT_EQ_INT(30, stack_pop(s));

    TEST("tamaño después de desapilar");
    ASSERT_EQ_INT(2, s->size);

    TEST("tope después de desapilar");
    ASSERT_EQ_INT(20, stack_top(s));

    TEST("desapilar devuelve 20");
    ASSERT_EQ_INT(20, stack_pop(s));

    TEST("desapilar devuelve 10");
    ASSERT_EQ_INT(10, stack_pop(s));

    TEST("pila vacía después de desapilar todo");
    ASSERT_TRUE(stack_empty(s));

    TEST("tamaño es 0 después de vaciar");
    ASSERT_EQ_INT(0, s->size);

    TEST("desapilar pila ya vacía devuelve -1");
    ASSERT_EQ_INT(-1, stack_pop(s));

    stack_destroy(s);
}

/* ========================================================================
 * TEST EJERCICIO 3: Encolar
 * ======================================================================== */

void test_ejercicio_3(void) {
    SECCION("EJERCICIO 3: Encolar (Enqueue)");

    Queue* q = queue_create();

    TEST("crear cola devuelve no-NULL");
    ASSERT_NOT_NULL(q);
    if (!q) return;

    TEST("cola nueva está vacía");
    ASSERT_TRUE(queue_empty(q));

    TEST("encolar primer elemento devuelve 0");
    int res = queue_enqueue(q, 10);
    ASSERT_EQ_INT(0, res);

    if (res == 0) {
        TEST("frente después de encolar 10");
        ASSERT_EQ_INT(10, queue_front(q));

        TEST("tamaño después de encolar 1 elemento");
        ASSERT_EQ_INT(1, q->size);

        TEST("cola ya no está vacía");
        ASSERT_TRUE(!queue_empty(q));

        TEST("encolar segundo elemento");
        ASSERT_EQ_INT(0, queue_enqueue(q, 20));

        TEST("frente sigue siendo 10 (FIFO)");
        ASSERT_EQ_INT(10, queue_front(q));

        TEST("tamaño después de encolar 2 elementos");
        ASSERT_EQ_INT(2, q->size);

        TEST("encolar tercer elemento");
        ASSERT_EQ_INT(0, queue_enqueue(q, 30));

        TEST("frente sigue siendo 10");
        ASSERT_EQ_INT(10, queue_front(q));

        TEST("tamaño después de encolar 3 elementos");
        ASSERT_EQ_INT(3, q->size);
    } else {
        printf("  (saltando tests de encolar - no implementado)\n");
    }

    queue_destroy(q);
}

/* ========================================================================
 * TEST EJERCICIO 4: Desencolar
 * ======================================================================== */

void test_ejercicio_4(void) {
    SECCION("EJERCICIO 4: Desencolar (Dequeue)");

    Queue* q = queue_create();
    if (!q) return;

    TEST("desencolar cola vacía devuelve -1");
    ASSERT_EQ_INT(-1, queue_dequeue(q));

    // Encolar algunos elementos
    int ok = queue_enqueue(q, 10);
    ok = ok == 0 ? queue_enqueue(q, 20) : ok;
    ok = ok == 0 ? queue_enqueue(q, 30) : ok;

    if (ok != 0) {
        printf("  (saltando tests de desencolar - encolar no implementado)\n");
        queue_destroy(q);
        return;
    }

    // Cola: front -> [10] -> [20] -> [30] <- rear

    TEST("desencolar devuelve primero encolado (10)");
    ASSERT_EQ_INT(10, queue_dequeue(q));

    TEST("tamaño después de desencolar");
    ASSERT_EQ_INT(2, q->size);

    TEST("frente después de desencolar");
    ASSERT_EQ_INT(20, queue_front(q));

    TEST("desencolar devuelve 20");
    ASSERT_EQ_INT(20, queue_dequeue(q));

    TEST("desencolar devuelve 30");
    ASSERT_EQ_INT(30, queue_dequeue(q));

    TEST("cola vacía después de desencolar todo");
    ASSERT_TRUE(queue_empty(q));

    TEST("tamaño es 0 después de vaciar");
    ASSERT_EQ_INT(0, q->size);

    TEST("frente es NULL después de vaciar");
    ASSERT_NULL(q->front);

    TEST("fondo es NULL después de vaciar");
    ASSERT_NULL(q->rear);

    TEST("desencolar cola ya vacía devuelve -1");
    ASSERT_EQ_INT(-1, queue_dequeue(q));

    queue_destroy(q);
}

/* ========================================================================
 * TEST EJERCICIO 5: Heap-up
 * ======================================================================== */

void test_ejercicio_5(void) {
    SECCION("EJERCICIO 5: Heap-up");

    Heap* h = heap_create();
    if (!h) return;

    // Armamos un array a mano: [10, 30, 20, 50, 5]
    // El 5 en posición 4 viola la propiedad de heap.
    // Después de heap_up(h, 4) debería quedar [5, 10, 20, 50, 30]
    h->data[0] = 10;
    h->data[1] = 30;
    h->data[2] = 20;
    h->data[3] = 50;
    h->data[4] = 5;
    h->size = 5;

    heap_up(h, 4);

    TEST("heap_up sube el 5 a la raíz");
    ASSERT_EQ_INT(5, h->data[0]);

    TEST("heap_up: posición 1 queda 10");
    ASSERT_EQ_INT(10, h->data[1]);

    TEST("heap_up: posición 2 queda 20 (no se tocó)");
    ASSERT_EQ_INT(20, h->data[2]);

    TEST("heap_up: posición 3 queda 50 (no se tocó)");
    ASSERT_EQ_INT(50, h->data[3]);

    TEST("heap_up: posición 4 queda 30");
    ASSERT_EQ_INT(30, h->data[4]);

    // Caso: elemento ya está en su lugar (no necesita subir)
    // Array: [5, 10, 20, 50, 30], heap_up(h, 3) con 50
    // 50 > 10 (padre) → no hace nada
    heap_up(h, 3);

    TEST("heap_up no mueve elemento que ya cumple propiedad");
    ASSERT_EQ_INT(50, h->data[3]);

    TEST("heap_up no afecta al padre cuando no hace swap");
    ASSERT_EQ_INT(10, h->data[1]);

    // Caso: heap_up en la raíz (caso base)
    heap_up(h, 0);

    TEST("heap_up en raíz no cambia nada");
    ASSERT_EQ_INT(5, h->data[0]);

    heap_destroy(h);
}

/* ========================================================================
 * TEST EJERCICIO 6: Insertar en Heap
 * ======================================================================== */

void test_ejercicio_6(void) {
    SECCION("EJERCICIO 6: Insertar en Min-Heap");

    Heap* h = heap_create();

    TEST("crear heap devuelve no-NULL");
    ASSERT_NOT_NULL(h);
    if (!h) return;

    TEST("insertar en heap vacío devuelve 0");
    int res = heap_insert(h, 50);
    ASSERT_EQ_INT(0, res);

    if (res == 0) {
        TEST("mínimo después de insertar 50");
        ASSERT_EQ_INT(50, heap_min(h));

        TEST("tamaño después de insertar 1 elemento");
        ASSERT_EQ_INT(1, h->size);

        TEST("insertar 30 (menor que raíz)");
        ASSERT_EQ_INT(0, heap_insert(h, 30));

        TEST("mínimo ahora es 30 (heap-up)");
        ASSERT_EQ_INT(30, heap_min(h));

        TEST("tamaño después de insertar 2 elementos");
        ASSERT_EQ_INT(2, h->size);

        TEST("insertar 70 (mayor que raíz)");
        ASSERT_EQ_INT(0, heap_insert(h, 70));

        TEST("mínimo sigue siendo 30");
        ASSERT_EQ_INT(30, heap_min(h));

        TEST("insertar 10 (nuevo mínimo)");
        ASSERT_EQ_INT(0, heap_insert(h, 10));

        TEST("mínimo ahora es 10");
        ASSERT_EQ_INT(10, heap_min(h));

        TEST("insertar 20");
        ASSERT_EQ_INT(0, heap_insert(h, 20));

        TEST("mínimo sigue siendo 10");
        ASSERT_EQ_INT(10, heap_min(h));

        TEST("tamaño final es 5");
        ASSERT_EQ_INT(5, h->size);

        // Verificar propiedad de heap: padre <= hijos
        TEST("propiedad de heap: raíz <= hijo izquierdo");
        ASSERT_TRUE(h->data[0] <= h->data[1]);

        TEST("propiedad de heap: raíz <= hijo derecho");
        ASSERT_TRUE(h->data[0] <= h->data[2]);
    } else {
        printf("  (saltando tests de heap - no implementado)\n");
    }

    heap_destroy(h);
}
