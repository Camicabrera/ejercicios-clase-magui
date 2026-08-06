# Problema: Subcadenas con Concatenación de Palabras
# Enunciado: Dado un string S y una lista de palabras L (todas de la misma longitud), 
# encuentra todas las posiciones iniciales de las subcadenas de S que son la 
# concatenación exacta de cada palabra en L exactamente una vez, 
# en cualquier orden.

# Entrada:
# S = "barfoothefoobarman"
# L = ["foo", "bar"]

# Salida:
# [0, 9]

# Explicación:
# Las subcadenas en posiciones 0 y 9 son "barfoo" y "foobar", que son la 
# concatenación de las palabras en L.

def encontrar_concatenaciones(s, palabras):
    if not s or not palabras or len(palabras) == 0:
        return []

    # Longitudes
    longitud_palabra = len(palabras[0])
    cantidad_palabras = len(palabras)
    longitud_total = longitud_palabra * cantidad_palabras

    # Diccionario con las frecuencias de las palabras
    cuenta_palabras = {}
    for palabra in palabras:
        if palabra in cuenta_palabras:
            cuenta_palabras[palabra] += 1
        else:
            cuenta_palabras[palabra] = 1

    # Resultado para almacenar las posiciones
    resultado = []

    # Recorrer el string con ventana deslizante
    for i in range(len(s) - longitud_total + 1):
        subcadena_actual = s[i:i + longitud_total]
        cuenta_actual = {}
        es_valida = True

        # Verificar las palabras en la subcadena
        for j in range(0, longitud_total, longitud_palabra):
            palabra = subcadena_actual[j:j + longitud_palabra]

            if palabra in cuenta_palabras:
                cuenta_actual[palabra] = cuenta_actual.get(palabra, 0) + 1

                # Si una palabra aparece más veces de lo permitido, no es válida
                if cuenta_actual[palabra] > cuenta_palabras[palabra]:
                    es_valida = False
                    break
            else:
                es_valida = False
                break

        # Si es válida, añadir la posición inicial al resultado
        if es_valida:
            resultado.append(i)

    return resultado


def test_encontrar_concatenaciones():
    # Caso 1: Ejemplo básico con dos ocurrencias
    S1 = "barfoothefoobarman"
    L1 = ["foo", "bar"]
    assert encontrar_concatenaciones(S1, L1) == [0, 9], "Caso 1 fallido"

    # Caso 2: Palabras sin coincidencias en el string
    S2 = "wordgoodgoodgoodbestword"
    L2 = ["word", "good", "best", "word"]
    assert encontrar_concatenaciones(S2, L2) == [], "Caso 2 fallido"

    # Caso 3: Todas las palabras están presentes, pero el orden importa
    S3 = "barfoofoobarthefoobarman"
    L3 = ["bar", "foo", "the"]
    assert encontrar_concatenaciones(S3, L3) == [6, 9, 12], "Caso 3 fallido"

    # Caso 4: Lista de palabras con subcadenas no repetidas
    S4 = "barfoothefoobar"
    L4 = ["foo", "bar"]
    assert encontrar_concatenaciones(S4, L4) == [0, 9], "Caso 4 fallido"

    # Caso 5: String vacío
    S5 = ""
    L5 = ["foo", "bar"]
    assert encontrar_concatenaciones(S5, L5) == [], "Caso 5 fallido"

    # Caso 6: Palabras vacías
    S6 = "barfoothefoobarman"
    L6 = []
    assert encontrar_concatenaciones(S6, L6) == [], "Caso 6 fallido"

    # Caso 7: String con todas las palabras del mismo tamaño
    S7 = "foobarfoo"
    L7 = ["foo", "bar"]
    assert encontrar_concatenaciones(S7, L7) == [0, 3], "Caso 7 fallido"

    # Caso 8: Todas las palabras tienen la misma frecuencia
    S8 = "wordgoodgoodgoodbestword"
    L8 = ["word", "good", "best", "good"]
    assert encontrar_concatenaciones(S8, L8) == [8], "Caso 8 fallido"

    # Caso 9: Un solo carácter repetido
    S9 = "aaaaaaaa"
    L9 = ["aa", "aa", "aa"]
    assert encontrar_concatenaciones(S9, L9) == [0, 1, 2], "Caso 9 fallido"

    print("Todos los casos pasaron exitosamente.")

# Llamar a la función de prueba
test_encontrar_concatenaciones()
