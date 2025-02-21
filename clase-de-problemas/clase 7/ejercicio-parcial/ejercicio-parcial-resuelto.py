def calcular_puntajes(jugadores):
    # Paso 1: Contar cuántos jugadores eligieron cada número
    frecuencia = {}
    for jugador in jugadores:
        for num in jugador:
            if num in frecuencia:
                frecuencia[num] += 1
            else:
                frecuencia[num] = 1

    # Inicializar puntajes para cada jugador
    puntajes = [0] * len(jugadores)
    
    # Paso 2: Calcular puntajes para cada jugador
    for i, jugador in enumerate(jugadores):
        for num in jugador:
            if frecuencia[num] == 1:  # Solo lo eligió este jugador
                puntajes[i] += 3
            elif frecuencia[num] == 2:  # Lo eligió este jugador y otro más
                puntajes[i] += 1

    return puntajes


def test_ejemplo():
    jugadores = [{1, 3, 5, 7}, {2, 4, 7, 8}, {1, 4, 7, 9}]
    resultado = calcular_puntajes(jugadores)
    assert resultado == [7, 7, 5], f"Resultado esperado: [7, 7, 5], obtenido: {resultado}"

def test_todos_distintos():
    jugadores = [{1, 2, 3}, {4, 5, 6}, {7, 8, 9}]
    resultado = calcular_puntajes(jugadores)
    assert resultado == [9, 9, 9], f"Resultado esperado: [9, 9, 9], obtenido: {resultado}"

def test_todos_iguales():
    jugadores = [{1, 2, 3}, {1, 2, 3}, {1, 2, 3}]
    resultado = calcular_puntajes(jugadores)
    assert resultado == [0, 0, 0], f"Resultado esperado: [0, 0, 0], obtenido: {resultado}"

def test_un_conjunto_vacio():
    jugadores = [{1, 2, 3}, {1, 2, 3}, set()]
    resultado = calcular_puntajes(jugadores)
    assert resultado == [3, 3, 0], f"Resultado esperado: [3, 3, 0], obtenido: {resultado}"

# Ejecutar las pruebas
test_ejemplo()
test_todos_distintos()
test_todos_iguales()
test_un_conjunto_vacio()

print("Todas las pruebas pasaron correctamente.")
