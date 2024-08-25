#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int* data;
    int size;
    int capacity;
    int is_min_heap; // 1 para min-heap, 0 para max-heap
} Heap;

void swap(int* a, int* b);

int compare(Heap* heap, int i, int j);

void heapify_up(Heap* heap, int index);

void heapify_down(Heap* heap, int index);

Heap* create_heap(int capacity, int is_min_heap);

void insert_heap(Heap* heap, int value);

int extract_top(Heap* heap);

#endif // HEAP_H