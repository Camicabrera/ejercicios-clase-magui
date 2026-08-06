#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *front;
    Node *rear;
    int size;
} Queue;

// Inicializar la cola
void initQueue(Queue *queue) {
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}

// Verificar si la cola está vacía
int isEmpty(Queue *queue) {
    return queue->size == 0;
}

// Obtener el tamaño de la cola
int len(Queue *queue) {
    return queue->size;
}

// Obtener el elemento en el frente de la cola
int front(Queue *queue) {
    if (isEmpty(queue)) {
        fprintf(stderr, "Error: La cola está vacía.\n");
        exit(EXIT_FAILURE);
    }
    return queue->front->data;
}

// Encolar un elemento
void enqueue(Queue *queue, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria para el nuevo nodo.\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = value;
    newNode->next = NULL;

    if (isEmpty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }

    queue->size++;
}

// Desencolar un elemento
int dequeue(Queue *queue) {
    if (isEmpty(queue)) {
        fprintf(stderr, "Error: La cola está vacía.\n");
        exit(EXIT_FAILURE);
    }

    Node *temp = queue->front;
    int dequeuedValue = temp->data;

    if (queue->front == queue->rear) {
        // Único elemento en la cola
        queue->front = NULL;
        queue->rear = NULL;
    } else {
        queue->front = temp->next;
    }

    free(temp);
    queue->size--;

    return dequeuedValue;
}

// Liberar la memoria de la cola
void freeQueue(Queue *queue) {
    while (queue->front != NULL) {
        Node *temp = queue->front;
        queue->front = temp->next;
        free(temp);
    }
    queue->rear = NULL;
    queue->size = 0;
}

int main() {
    Queue myQueue;
    initQueue(&myQueue);

    printf("La cola está vacía? %s\n", isEmpty(&myQueue) ? "Sí" : "No");
    printf("Tamaño de la cola: %d\n", len(&myQueue));

    enqueue(&myQueue, 10);
    enqueue(&myQueue, 20);
    enqueue(&myQueue, 30);

    printf("La cola está vacía? %s\n", isEmpty(&myQueue) ? "Sí" : "No");
    printf("Tamaño de la cola: %d\n", len(&myQueue));
    printf("Elemento en el frente de la cola: %d\n", front(&myQueue));

    printf("Elemento desencolado: %d\n", dequeue(&myQueue));

    freeQueue(&myQueue);

    return 0;
}
