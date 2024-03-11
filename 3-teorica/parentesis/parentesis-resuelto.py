def validar_resultado(resultado, expected):
    if(resultado == expected): 
        return "Passed"
    return "Failed"

def validar_parentesis(secuencia):
    stack = []

    for char in secuencia:
        if char == '(':
            stack.append(char)
        elif char == ')':
            if not stack or stack.pop() != '(':
                return False
        else:
            continue;
    return not stack  

# Ejemplos
print(validar_resultado(validar_parentesis("()"),True))       # True
print(validar_resultado(validar_parentesis("(()())"), True))   # True
print(validar_resultado(validar_parentesis(")(())"), False))     # False
print(validar_resultado(validar_parentesis("())"), False))   
print(validar_resultado(validar_parentesis("("), False))  