from collections import deque

class TwoQueueStack:
    def __init__(self):
        self.queue1 = deque()
        self.queue2 = deque()

    def push(self, value):
        # Si hay elementos en queue1, encolamos en queue1
        if self.queue1:
            self.queue1.append(value)
        else:
            # Si queue1 está vacía, encolamos en queue2
            self.queue2.append(value)

    def pop(self):
        if not self.queue1 and not self.queue2:
            raise IndexError("La pila está vacía")

        # Desencolamos de la cola no vacía y movemos los elementos a la otra cola
        if self.queue1:
            while len(self.queue1) > 1:
                self.queue2.append(self.queue1.popleft())
            return self.queue1.popleft()
        else:
            while len(self.queue2) > 1:
                self.queue1.append(self.queue2.popleft())
            return self.queue2.popleft()

    def is_empty(self):
        return not self.queue1 and not self.queue2

    def size(self):
        return len(self.queue1) + len(self.queue2)

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
