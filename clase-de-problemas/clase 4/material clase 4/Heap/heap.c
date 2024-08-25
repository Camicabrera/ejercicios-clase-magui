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
    // TODO
}

int extract_top(Heap* heap) {
    // TODO
}

void heapify_up(Heap* heap, int index) {
    // TODO
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
