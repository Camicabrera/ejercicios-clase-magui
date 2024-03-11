from collections import deque

class TwoQueueStack:
    def __init__(self):
        self.queue1 = deque()
        self.queue2 = deque()

    def push(self, value):
        # TODO
        return 0

    def pop(self):
        # TODO
        return 0
        

    def is_empty(self):
        # TODO
        return 0

    def size(self):
        # TODO
        return 0

# Ejemplo de uso
stack = TwoQueueStack()
stack.push(10)
stack.push(20)
stack.push(30)

print("¿La pila está vacía?", stack.is_empty())
print("Tamaño de la pila:", stack.size())

print("Elemento desapilado:", stack.pop())

print("¿La pila está vacía?", stack.is_empty())
print("Tamaño de la pila:", stack.size())
