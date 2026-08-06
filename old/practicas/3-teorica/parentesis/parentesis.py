def validar_resultado(resultado, expected):
    if(resultado == expected): 
        return "Passed"
    return "Failed"

def validar_parentesis(secuencia):
    # TODO:
    return True

# Ejemplos
print(validar_resultado(validar_parentesis("()"),True))       # True
print(validar_resultado(validar_parentesis("(()())"), True))   # True
print(validar_resultado(validar_parentesis(")(())"), False))     # False
print(validar_resultado(validar_parentesis("())"), False))   