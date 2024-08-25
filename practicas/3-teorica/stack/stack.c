#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *top;
    int size;
} Stack;

// Inicializar la pila
void initStack(Stack *stack) {
    stack->top = NULL;
    stack->size = 0;
}

// Verificar si la pila está vacía
int isEmpty(Stack *stack) {
    return stack->size == 0;
}

// Obtener el tamaño de la pila
int len(Stack *stack) {
    return stack->size;
}

// Obtener el elemento en la cima de la pila
int top(Stack *stack) {
    if (isEmpty(stack)) {
        fprintf(stderr, "Error: La pila está vacía.\n");
        exit(EXIT_FAILURE);
    }
    return stack->top->data;
}

// Empujar un elemento a la pila
void push(Stack *stack, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria para el nuevo nodo.\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = value;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
}

// Sacar un elemento de la pila
int pop(Stack *stack) {
    if (isEmpty(stack)) {
        fprintf(stderr, "Error: La pila está vacía.\n");
        exit(EXIT_FAILURE);
    }

    Node *temp = stack->top;
    int poppedValue = temp->data;
    stack->top = temp->next;
    free(temp);
    stack->size--;

    return poppedValue;
}

// Liberar la memoria de la pila
void freeStack(Stack *stack) {
    while (stack->top != NULL) {
        Node *temp = stack->top;
        stack->top = temp->next;
        free(temp);
    }
    stack->size = 0;
}

int main() {
    Stack myStack;
    initStack(&myStack);

    printf("La pila está vacía? %s\n", isEmpty(&myStack) ? "Sí" : "No");
    printf("Tamaño de la pila: %d\n", len(&myStack));

    push(&myStack, 10);
    push(&myStack, 20);
    push(&myStack, 30);

    printf("La pila está vacía? %s\n", isEmpty(&myStack) ? "Sí" : "No");
    printf("Tamaño de la pila: %d\n", len(&myStack));
    printf("Elemento en la cima de la pila: %d\n", top(&myStack));

    printf("Elemento desapilado: %d\n", pop(&myStack));

    freeStack(&myStack);

    return 0;
}
