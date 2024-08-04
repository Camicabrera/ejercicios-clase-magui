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

}

// Verificar si la cola está vacía
int isEmpty(Queue *queue) {

}

// Obtener el tamaño de la cola
int len(Queue *queue) {

}

// Obtener el elemento en el frente de la cola
int front(Queue *queue) {
  
}

// Encolar un elemento
void enqueue(Queue *queue, int value) {

}

// Desencolar un elemento
int dequeue(Queue *queue) {
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
  
}
