def find_max_satisfied_children(greed, cookie):

    # HINT: se pueden ordenar los arreglos 
    satisfied_children = 0
    return satisfied_children

# Tests
# Caso 1: Un niño puede ser satisfecho
assert find_max_satisfied_children([1, 2, 3], [1, 1]) == 1

# Caso 2: Todos los niños pueden ser satisfechos
assert find_max_satisfied_children([1, 2], [1, 2, 3]) == 2

# Caso 3: Ningún niño puede ser satisfecho
assert find_max_satisfied_children([4, 5, 6], [1, 2, 3]) == 0

# Caso 4: Cada niño recibe una cookie que satisface su necesidad
assert find_max_satisfied_children([1, 2, 3], [3, 2, 1]) == 3

# Caso 5: Algunos niños no reciben cookies
assert find_max_satisfied_children([1, 2, 3, 4], [1, 2]) == 2

print("Todos los tests pasaron.")
