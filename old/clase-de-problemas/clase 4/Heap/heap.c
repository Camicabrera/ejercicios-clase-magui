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
    if(heap->capacity < heap->size - 1) {
        heap->data = (int *) realloc(heap->data, heap->capacity*2*sizeof(int));
        if(heap->data == NULL) {
            fprintf(stderr, "Error: no se pudo asignar memoria para el heap.\n");
            return;
        }
        heap->capacity *= 2;
    }
        heap->data[heap->size] = value;
        heapify_up(heap, heap->size);
        heap->size ++;
}

int extract_top(Heap* heap) {
    // TODO
    if(!heap->size) return NULL;

    swap(&heap->data[0], &heap->data[heap->size-1]);

    int top = heap->data[heap->size-1];
    heap->size --;

    heapfy_down(heap, 0);

    return top;
}

void heapify_up(Heap* heap, int index) {
    if(index == 1 || compare(heap, index, index / 2)) {
        return;
    }

    swap(&heap->data[index/2],&heap->data[index]);
    heapify_up(heap, index/2);
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
