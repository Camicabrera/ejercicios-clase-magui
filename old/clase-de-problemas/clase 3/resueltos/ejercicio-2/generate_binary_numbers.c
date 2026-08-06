#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void generate_binary_numbers(int n) {
    Queue* queue = create_queue();
    int* num = malloc(sizeof(int)); 
    *num = 1;
    enqueue(queue, num);  // Inicia con el número 1 en binario

    while (!is_queue_empty(queue)) {
        int* current = (int*) dequeue(queue);
        printf("%d ", *current);

        if (*current < n) {
            int* num0 = malloc(sizeof(int));
            int* num1 = malloc(sizeof(int));
            *num0 = (*current) * 10;
            *num1 = (*current) * 10 + 1;
            enqueue(queue, num0);     // Añade 0 al final
            enqueue(queue, num1);     // Añade 1 al final
        }

        free(current);
    }

    free_queue(queue);
}

int main() {
    generate_binary_numbers(0);
    printf("\n");
    generate_binary_numbers(16);
    printf("\n");
    generate_binary_numbers(2);
    return 0;
}
