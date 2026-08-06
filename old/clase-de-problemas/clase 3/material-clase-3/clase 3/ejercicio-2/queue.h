#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdio.h>

// Estructura de nodo para la cola
typedef struct QueueNode {
    void* data;
    struct QueueNode* next;
    struct QueueNode* prev;
} QueueNode;

// Estructura para la cola
typedef struct {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// Funciones para manejar la cola
Queue* create_queue();
void enqueue(Queue* queue, void* data);
void* dequeue(Queue* queue);
void* front(Queue* queue);
int is_queue_empty(Queue* queue);
void free_queue(Queue* queue);

#endif // QUEUE_H
