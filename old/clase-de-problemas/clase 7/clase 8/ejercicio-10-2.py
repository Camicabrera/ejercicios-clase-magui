def son_isomorfas(s1, s2):
    # TODO
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