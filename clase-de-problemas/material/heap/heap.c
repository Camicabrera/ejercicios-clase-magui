#include "heap.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    int size;
    int capacity;
    int is_min_heap; // 1 para min-heap, 0 para max-heap
} Heap;


void insert_heap(Heap* heap, int value) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        int* new_data = (int*)realloc(heap->data, heap->capacity * sizeof(int));
        if (new_data == NULL) {
            fprintf(stderr, "Error: no se pudo reasignar memoria para los datos del heap.\n");
            return;
        }
        heap->data = new_data;
    }
    heap->data[heap->size++] = value;
    heapify_up(heap, heap->size - 1);
}

int extract_top(Heap* heap) {
    if (heap->size == 0) {
        return -1;
    }
    int top = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    heapify_down(heap, 0);
    return top;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int compare(Heap* heap, int i, int j) {
    if (heap->is_min_heap) {
        return heap->data[i] > heap->data[j];
    } else {
        return heap->data[i] < heap->data[j];
    }
}

void heapify_up(Heap* heap, int index) {
    int parent = (index - 1) / 2;
    if (index && compare(heap, parent, index)) {
        swap(&heap->data[index], &heap->data[parent]);
        heapify_up(heap, parent);
    }
}

void heapify_down(Heap* heap, int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;

    if (left < heap->size && compare(heap, smallest, left)) {
        smallest = left;
    }
    if (right < heap->size && compare(heap, smallest, right)) {
        smallest = right;
    }
    if (smallest != index) {
        swap(&heap->data[index], &heap->data[smallest]);
        heapify_down(heap, smallest);
    }
}

Heap* create_heap(int capacity, int is_min_heap) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    if (heap == NULL) {
        fprintf(stderr, "Error: no se pudo asignar memoria para el heap.\n");
        return NULL;
    }
    heap->data = (int*)malloc(capacity * sizeof(int));
    if (heap->data == NULL) {
        fprintf(stderr, "Error: no se pudo asignar memoria para los datos del heap.\n");
        free(heap);
        return NULL;
    }
    heap->size = 0;
    heap->capacity = capacity;
    heap->is_min_heap = is_min_heap;
    return heap;
}
