/**
 * Práctica 5 - Pilas, Colas y Heaps
 * ===================================
 *
 * En esta práctica vas a implementar:
 *   - Ejercicio 1: Apilar (Pila como lista enlazada)
 *   - Ejercicio 2: Desapilar (Pila como lista enlazada)
 *   - Ejercicio 3: Encolar (Cola como lista enlazada)
 *   - Ejercicio 4: Desencolar (Cola como lista enlazada)
 *   - Ejercicio 5: Heap-up (restaurar propiedad de Min-Heap)
 *   - Ejercicio 6: Insertar en un Min-Heap (array dinámico)
 *
 * Los tests ya están escritos. Tu trabajo es completar las funciones
 * marcadas con TODO.
 *
 * Compilar:  make ejercicios
 * Ejecutar:  ./ejercicios
 * Valgrind:  make valgrind
 */

#include "testing.h"

/* ========================================================================
 * ESTRUCTURAS
 * ======================================================================== */

// Nodo para Pila y Cola (lista enlazada)
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Pila: el tope es el primer nodo de la lista
typedef struct {
    Node* top;
    int size;
} Stack;

// Cola: tiene frente (donde se desencola) y fondo (donde se encola)
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
 * FUNCIONES AUXILIARES (ya implementadas)
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
 * EJERCICIO 1: Apilar (Push) - Pila como lista enlazada
 * ========================================================================
 *
 * ENUNCIADO:
 * Implementá la función stack_push que agrega un elemento al tope de la pila.
 *
 * La pila se implementa como una lista enlazada donde el tope es el
 * primer nodo. Apilar = insertar al principio de la lista.
 *
 *   Antes:  top -> [3] -> [2] -> [1] -> NULL
 *   stack_push(5):
 *   Después: top -> [5] -> [3] -> [2] -> [1] -> NULL
 *
 *
 * Devuelve 0 si tuvo éxito, -1 si falló.
 */

int stack_push(Stack* s, int data) {
    Node* new_node = malloc(sizeof(Node));
    if(!new_node) return -1;

    new_node -> data = data;
    new_node->next = s->top;
    s->top = new_node;
    s->size ++;

    return 0;
}

/* ========================================================================
 * EJERCICIO 2: Desapilar (Pop) - Pila como lista enlazada
 * ========================================================================
 *
 * ENUNCIADO:
 * Implementá la función stack_pop que quita y devuelve el elemento
 * del tope de la pila.
 *
 * Desapilar = quitar el primer nodo de la lista.
 *
 *   Antes:  top -> [5] -> [3] -> [2] -> [1] -> NULL
 *   stack_pop():
 *   Después: top -> [3] -> [2] -> [1] -> NULL   (devuelve 5)
 *
 *
 * Devuelve el data del top, o -1 si la pila está vacía.
 */

int stack_pop(Stack* s) {
    if(stack_empty(s)) return -1;
    Node* aux = s -> top;
    s -> top = aux ->next;
    int data = aux->data;
    free(aux);
    s -> size --;
    return data;
}

/* ========================================================================
 * EJERCICIO 3: Encolar (Enqueue) - Cola como lista enlazada
 * ========================================================================
 *
 * ENUNCIADO:
 * Implementá la función queue_enqueue que agrega un elemento al fondo de la cola.
 *
 * La cola tiene dos punteros: front (donde se saca) y rear (donde se agrega).
 *
 *   Antes:  front -> [1] -> [2] -> [3] <- rear
 *   queue_enqueue(4):
 *   Después: front -> [1] -> [2] -> [3] -> [4] <- rear
 *
 * Caso especial: si la cola está vacía, el nuevo nodo es tanto front como rear.
 *
 *
 * Devuelve 0 si tuvo éxito, -1 si falló.
 */

int queue_enqueue(Queue* q, int data) {
    Node* new_node = malloc(sizeof(Node));
    if(!new_node) return -1;

    new_node -> data = data;
    new_node -> next = NULL;

    if(queue_empty(q)) {
        q -> front = new_node;
    } else {
        q -> rear -> next = new_node;
    }
    q -> rear = new_node;
    q -> size ++;

    return 0;
}

/* ========================================================================
 * EJERCICIO 4: Desencolar (Dequeue) - Cola como lista enlazada
 * ========================================================================
 *
 * ENUNCIADO:
 * Implementá la función queue_dequeue que quita y devuelve el elemento
 * del frente de la cola.
 *
 *   Antes:  front -> [1] -> [2] -> [3] <- rear
 *   queue_dequeue():
 *   Después: front -> [2] -> [3] <- rear   (devuelve 1)
 *
 * Caso especial: si queda vacía después de desencolar, rear también debe ser NULL.
 *
 *
 * Devuelve el data del front, o -1 si la cola está vacía.
 */

int queue_dequeue(Queue* q) {
    if(queue_empty(q)) return -1;

    Node* aux = q -> front;
    int data = aux -> data;

    q -> front = aux -> next;
    free(aux);
    if( q -> front == NULL) q -> rear = NULL;
    q -> size --;
    return data;
}

/* ========================================================================
 * EJERCICIO 5: Heap-up (recursivo)
 * ========================================================================
 *
 * ENUNCIADO:
 * Implementá la función heap_up que restaura la propiedad de min-heap
 * "hacia arriba" de forma RECURSIVA.
 *
 * Dado un índice i en el array del heap, si el elemento en i es menor
 * que su padre, hay que intercambiarlos y seguir subiendo.
 *
 * Caso base: i == 0 (es la raíz, no tiene padre)
 * Caso recursivo: si h->data[i] < h->data[padre], intercambiar
 *                 y llamar heap_up(h, padre)
 *
 * Recordá: el padre del elemento en posición i está en (i - 1) / 2.
 *
 * Ejemplo:
 *   Array: [10, 30, 20, 50, 5]   heap_up(h, 4)
 *
 *   i=4, padre=1: 5 < 30? Sí → swap → [10, 5, 20, 50, 30]
 *                 heap_up(h, 1)
 *   i=1, padre=0: 5 < 10? Sí → swap → [5, 10, 20, 50, 30]
 *                 heap_up(h, 0)
 *   i=0: es la raíz → return (caso base)
 */

void heap_up(Heap* h, int i) {
    if(i == 0) return;

    int padre_pos = (i - 1) / 2;

    int padre = h -> data[padre_pos];
    int hijo = h -> data[i];

    if(hijo <= padre) {
        h -> data[padre_pos] = hijo;
        h -> data[i] = padre;
        heap_up(h, padre_pos);
    }

}

/* ========================================================================
 * EJERCICIO 6: Insertar en un Min-Heap (Array)
 * ========================================================================
 *
 * ENUNCIADO:
 * Implementá la función heap_insert que inserta un elemento en un
 * Min-Heap representado como array.
 *
 * Pasos:
 *   1. Si el array está lleno (h->size == h->capacity), agrandarlo
 *      con realloc al doble de capacidad
 *   2. Insertar el elemento al final del array (posición h->size)
 *   3. Incrementar h->size
 *   4. Llamar a heap_up para restaurar la propiedad de heap
 *
 * Devuelve 0 si tuvo éxito, -1 si falló.
 */

int heap_insert(Heap* h, int data) {
    if()
}

/* ========================================================================
 * MAIN
 * ======================================================================== */

int main(void) {
    printf("Práctica 5: Pilas, Colas y Heaps\n");
    printf("==================================\n");

    test_ejercicio_1();
    test_ejercicio_2();
    test_ejercicio_3();
    test_ejercicio_4();
    test_ejercicio_5();
    test_ejercicio_6();

    print_results();

    return tests_fail > 0 ? 1 : 0;
}
