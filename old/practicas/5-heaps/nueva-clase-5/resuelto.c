/**
 * Práctica 5 - Pilas, Colas y Heaps (RESUELTO)
 * ===============================================
 *
 * Compilar:  make resuelto
 * Ejecutar:  ./resuelto
 * Valgrind:  valgrind --leak-check=full ./resuelto
 */

#include "testing.h"

/* ========================================================================
 * ESTRUCTURAS
 * ======================================================================== */

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

// Min-Heap como array dinámico
//
// En un heap con array, el árbol se almacena nivel por nivel:
//
//        10            array: [10, 30, 20, 50, 70]
//       /  \           índice:  0   1   2   3   4
//     30    20
//    /  \              Para el elemento en posición i:
//  50    70              - Padre:       (i - 1) / 2
//                        - Hijo izq:    2 * i + 1
//                        - Hijo der:    2 * i + 2
//
typedef struct {
    int* data;      // array dinámico de elementos
    int size;       // cantidad actual de elementos
    int capacity;   // capacidad del array
} Heap;

/* ========================================================================
 * FUNCIONES AUXILIARES
 * ======================================================================== */

Stack* stack_create(void) {
    Stack* s = malloc(sizeof(Stack));
    if (!s) return NULL;
    s->top = NULL;
    s->size = 0;
    return s;
}

void stack_destroy(Stack* s) {
    if (!s) return;
    Node* current = s->top;
    while (current) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    free(s);
}

int stack_empty(Stack* s) {
    return s == NULL || s->size == 0;
}

int stack_top(Stack* s) {
    if (stack_empty(s)) return -1;
    return s->top->data;
}

Queue* queue_create(void) {
    Queue* q = malloc(sizeof(Queue));
    if (!q) return NULL;
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    return q;
}

void queue_destroy(Queue* q) {
    if (!q) return;
    Node* current = q->front;
    while (current) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    free(q);
}

int queue_empty(Queue* q) {
    return q == NULL || q->size == 0;
}

int queue_front(Queue* q) {
    if (queue_empty(q)) return -1;
    return q->front->data;
}

Heap* heap_create(void) {
    Heap* h = malloc(sizeof(Heap));
    if (!h) return NULL;
    h->data = malloc(sizeof(int) * 16);
    if (!h->data) { free(h); return NULL; }
    h->size = 0;
    h->capacity = 16;
    return h;
}

void heap_destroy(Heap* h) {
    if (!h) return;
    free(h->data);
    free(h);
}

int heap_min(Heap* h) {
    if (!h || h->size == 0) return -1;
    return h->data[0];
}

/* ========================================================================
 * EJERCICIO 1: Apilar (Push)
 * ========================================================================
 *
 * Apilar = insertar al principio de la lista enlazada.
 *
 *   Antes:  top -> [3] -> [2] -> [1] -> NULL
 *   stack_push(5):
 *   Después: top -> [5] -> [3] -> [2] -> [1] -> NULL
 *
 * El nuevo nodo "envuelve" al tope anterior. Es O(1).
 */

int stack_push(Stack* s, int data) {
    if (!s) return -1;

    Node* new_node = malloc(sizeof(Node));
    if (!new_node) return -1;

    new_node->data = data;
    new_node->next = s->top;  // El next del nuevo es el top actual
    s->top = new_node;         // El nuevo nodo pasa a ser el top
    s->size++;
    return 0;
}

/* ========================================================================
 * EJERCICIO 2: Desapilar (Pop)
 * ========================================================================
 *
 * Desapilar = quitar el primer nodo de la lista.
 *
 *   Antes:  top -> [5] -> [3] -> [2] -> [1] -> NULL
 *   stack_pop():
 *   Después: top -> [3] -> [2] -> [1] -> NULL   (devuelve 5)
 *
 * Hay que liberar el nodo que sacamos. Es O(1).
 */

int stack_pop(Stack* s) {
    if (stack_empty(s)) return -1;

    Node* old = s->top;
    int data = old->data;
    s->top = old->next;  // El top pasa al siguiente
    free(old);            // Liberamos el nodo viejo
    s->size--;
    return data;
}

/* ========================================================================
 * EJERCICIO 3: Encolar (Enqueue)
 * ========================================================================
 *
 * Encolar = agregar al final de la lista (por el rear).
 *
 *   Antes:  front -> [1] -> [2] -> [3] <- rear
 *   queue_enqueue(4):
 *   Después: front -> [1] -> [2] -> [3] -> [4] <- rear
 *
 * Caso especial: cola vacía → front y rear apuntan al mismo nodo.
 * Es O(1) porque tenemos puntero al rear.
 */

int queue_enqueue(Queue* q, int data) {
    if (!q) return -1;

    Node* new_node = malloc(sizeof(Node));
    if (!new_node) return -1;

    new_node->data = data;
    new_node->next = NULL;  // Es el último, no tiene next

    if (queue_empty(q)) {
        // Cola vacía: el nuevo es tanto front como rear
        q->front = new_node;
        q->rear = new_node;
    } else {
        // El rear actual apunta al nuevo, y actualizamos rear
        q->rear->next = new_node;
        q->rear = new_node;
    }

    q->size++;
    return 0;
}

/* ========================================================================
 * EJERCICIO 4: Desencolar (Dequeue)
 * ========================================================================
 *
 * Desencolar = quitar del principio de la lista (por el front).
 *
 *   Antes:  front -> [1] -> [2] -> [3] <- rear
 *   queue_dequeue():
 *   Después: front -> [2] -> [3] <- rear   (devuelve 1)
 *
 * Caso especial: si queda vacía, rear también debe ser NULL.
 * Es O(1).
 */

int queue_dequeue(Queue* q) {
    if (queue_empty(q)) return -1;

    Node* old = q->front;
    int data = old->data;
    q->front = old->next;  // El front pasa al siguiente

    if (q->front == NULL) {
        // La cola quedó vacía, rear también debe ser NULL
        q->rear = NULL;
    }

    free(old);
    q->size--;
    return data;
}

/* ========================================================================
 * EJERCICIO 5: Heap-up (recursivo)
 * ========================================================================
 *
 * Si el elemento en posición i es menor que su padre, los
 * intercambiamos y seguimos subiendo recursivamente.
 *
 * Caso base: i == 0 (es la raíz).
 * Caso recursivo: swap con el padre y llamar heap_up(h, padre).
 */

void heap_up(Heap* h, int i) {
    if (i == 0) return;  // Caso base: es la raíz

    int parent = (i - 1) / 2;

    if (h->data[i] < h->data[parent]) {
        // Intercambiar con el padre
        int tmp = h->data[i];
        h->data[i] = h->data[parent];
        h->data[parent] = tmp;

        // Seguir subiendo
        heap_up(h, parent);
    }
}

/* ========================================================================
 * EJERCICIO 6: Insertar en Min-Heap (Array)
 * ========================================================================
 *
 * Insertar al final del array y llamar a heap_up para restaurar
 * la propiedad de heap.
 */

int heap_insert(Heap* h, int data) {
    if (!h) return -1;

    // Si el array está lleno, duplicar la capacidad
    if (h->size == h->capacity) {
        int new_cap = h->capacity * 2;
        int* new_data = realloc(h->data, sizeof(int) * new_cap);
        if (!new_data) return -1;
        h->data = new_data;
        h->capacity = new_cap;
    }

    // Insertar al final
    h->data[h->size] = data;
    h->size++;

    // Restaurar propiedad de heap
    heap_up(h, h->size - 1);

    return 0;
}

/* ========================================================================
 * MAIN
 * ======================================================================== */

int main(void) {
    printf("Práctica 5: Pilas, Colas y Heaps (RESUELTO)\n");
    printf("=============================================\n");

    test_ejercicio_1();
    test_ejercicio_2();
    test_ejercicio_3();
    test_ejercicio_4();
    test_ejercicio_5();
    test_ejercicio_6();

    print_results();

    return tests_fail > 0 ? 1 : 0;
}
