#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// Función para crear un nuevo nodo
QueueNode* create_QueueNode(void* data) {
    QueueNode* new_node = (QueueNode*)malloc(sizeof(QueueNode));
    if (new_node == NULL) {
        fprintf(stderr, "Error: no se pudo asignar memoria para el nodo\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

// Función para crear una cola
Queue* create_queue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) {
        fprintf(stderr, "Error: no se pudo asignar memoria para la cola\n");
        exit(EXIT_FAILURE);
    }
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// Función para verificar si la cola está vacía
int is_queue_empty(Queue* queue) {
    return queue->front == NULL;
}

// Función para agregar un elemento al final de la cola
void enqueue(Queue* queue, void* data) {
    QueueNode* new_node = create_QueueNode(data);
    if (is_queue_empty(queue)) {
        queue->front = new_node;
        queue->rear = new_node;
    } else {
        new_node->prev = queue->rear;
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
}

// Función para eliminar un elemento del frente de la cola
void* dequeue(Queue* queue) {
    if (is_queue_empty(queue)) {
        return NULL; // Indicador de que la cola está vacía
    }

    QueueNode* temp = queue->front;
    void* data = temp->data;

    queue->front = queue->front->next;
    if (queue->front != NULL) {
        queue->front->prev = NULL;
    } else {
        queue->rear = NULL;
    }

    free(temp);
    return data;
}

// Función para ver el elemento en el frente de la cola sin eliminarlo
void* peek(Queue* queue) {
    if (is_queue_empty(queue)) {
        return NULL; // Indicador de que la cola está vacía
    }
    return queue->front->data;
}

// Función para liberar toda la memoria de la cola
void free_queue(Queue* queue) {
    while (!is_queue_empty(queue)) {
        dequeue(queue);
    }
    free(queue);
}