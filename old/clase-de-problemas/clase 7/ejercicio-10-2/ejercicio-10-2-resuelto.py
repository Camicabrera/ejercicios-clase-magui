def son_isomorfas(s1, s2):
    # Si los strings no tienen la misma longitud, no pueden ser isomorfos
    if len(s1) != len(s2):
        return False

    # Diccionarios para mapear caracteres de s1 a s2 y viceversa
    mapeo_s1_a_s2 = {}
    mapeo_s2_a_s1 = {}

    # Recorrer ambos strings simultáneamente
    for c1, c2 in zip(s1, s2):
        # Verificar si ya hay un mapeo para c1 en s1 -> s2
        if c1 in mapeo_s1_a_s2:
            # Si el mapeo es inconsistente, no son isomorfos
            if mapeo_s1_a_s2[c1] != c2:
                return False
        else:
            # Crear un nuevo mapeo de c1 a c2
            mapeo_s1_a_s2[c1] = c2

        # Verificar si ya hay un mapeo para c2 en s2 -> s1
        if c2 in mapeo_s2_a_s1:
            # Si el mapeo es inconsistente, no son isomorfos
            if mapeo_s2_a_s1[c2] != c1:
                return False
        else:
            # Crear un nuevo mapeo de c2 a c1
            mapeo_s2_a_s1[c2] = c1

    # Si pasamos todas las comprobaciones, los strings son isomorfos
    return True

def test_son_isomorfas():
    # Caso 1: Strings isomorfos
    assert son_isomorfas("abca", "agha") == True, "Caso 1 fallido"

    # Caso 2: Strings no isomorfos (mapeo inconsistente)
    assert son_isomorfas("abca", "aghh") == False, "Caso 2 fallido"

    # Caso 3: Strings de diferente longitud (no pueden ser isomorfos)
    assert son_isomorfas("abc", "abcd") == False, "Caso 3 fallido"

    # Caso 4: Strings vacíos (consideramos que son isomorfos)
    assert son_isomorfas("", "") == True, "Caso 4 fallido"

    # Caso 5: Strings con un solo carácter (deben ser isomorfos)
    assert son_isomorfas("a", "b") == True, "Caso 5 fallido"

    # Caso 6: Strings con caracteres repetidos pero isomorfos
    assert son_isomorfas("aaaa", "bbbb") == True, "Caso 6 fallido"

    # Caso 7: Strings con mapeos incorrectos
    assert son_isomorfas("abba", "abab") == False, "Caso 7 fallido"

    # Caso 8: Strings con mapeos válidos pero diferentes caracteres
    assert son_isomorfas("paper", "title") == True, "Caso 8 fallido"

    print("Todos los casos pasaron exitosamente.")

test_son_isomorfas()