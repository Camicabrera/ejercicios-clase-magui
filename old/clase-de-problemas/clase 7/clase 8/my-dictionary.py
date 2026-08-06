class Node:
    def __init__(self, clave=None, valor=None):
        self.key = clave
        self.value = valor
        self.was_deleted = False  # Marca si el nodo fue borrado

class MyDictionary:
    def __init__(self, capacity=10):
        self.capacity = capacity
        self.table = [None] * capacity  # Lista de nodos
        self.size = 0

    def hash(self, clave):
        return hash(clave) % self.capacity

    def insert(self, clave, valor):
        # Calculamos el hash de la clave
        index = self.hash(clave)

        for _ in range(self.capacity):
            node = self.table[index]

            # TODO

            # Sondeo lineal: movernos al siguiente índice
            index = (index + 1) % self.capacity

        # La tabla está llena
        return False

    def get_by_key(self, key):
        index = self.hash(key)

        for _ in range(self.capacity):
            node = self.table[index]

           # TODO

            # Sondeo lineal: movernos al siguiente índice
            index = (index + 1) % self.capacity

        return None

    def delete_by_key(self, key):
        # Calculamos el hash de la clave
        index = self.hash(key)

        for _ in range(self.capacity):
            node = self.table[index]

            # TODO

            # Sondeo lineal: movernos al siguiente índice
            index = (index + 1) % self.capacity

        return False  # No se encontró la clave

    def __len__(self):
        return self.size

    def __str__(self):
        elements = []
        for node in self.table:
            if node and not node.was_deleted:
                elements.append(f"{node.key}: {node.value}")
        return "{" + ", ".join(elements) + "}"

# Crear el diccionario
diccionario = MyDictionary()

# Insertar elementos
diccionario.insert("uno", 1)
diccionario.insert("dos", 2)
diccionario.insert("tres", 3)

# Obtener valores
print(diccionario.get_by_key("uno"))  # Imprime 1
print(diccionario.get_by_key("dos"))  # Imprime 2

# Eliminar un elemento
diccionario.delete_by_key("dos")

# Intentar obtener un valor eliminado
print(diccionario.get_by_key("dos"))  # Imprime None

# Mostrar el diccionario
print(diccionario)  # Imprime {uno: 1, tres: 3}

# Longitud del diccionario
print(len(diccionario))  # Imprime 2
