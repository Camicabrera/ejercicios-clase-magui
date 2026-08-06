def evaluar_notacion_polaca_inversa(expresion):
    stack = []

    for elemento in expresion.split():
        if elemento.isdigit() or (elemento[0] == '-' and elemento[1:].isdigit()):
            # Si es un número (positivo o negativo), lo agregamos a la pila
            stack.append(int(elemento))
        else:
            # Es un operador, realizamos la operación con los dos últimos operandos en la pila
            if len(stack) < 2:
                raise ValueError("Expresión no válida")

            operand2 = stack.pop()
            operand1 = stack.pop()

            if elemento == '+':
                resultado = operand1 + operand2
            elif elemento == '-':
                resultado = operand1 - operand2
            elif elemento == '*':
                resultado = operand1 * operand2
            elif elemento == '/':
                resultado = operand1 / operand2
            else:
                raise ValueError(f"Operador no reconocido: {elemento}")

            # Agregamos el resultado de la operación a la pila
            stack.append(resultado)

    # Al final, el resultado debe estar en la pila
    if len(stack) != 1:
        raise ValueError("Expresión no válida")

    return stack[0]

# Ejemplos
expresion_polaca_1 = "3 4 + 2 *"
resultado_1 = evaluar_notacion_polaca_inversa(expresion_polaca_1)
print(f"Resultado de la expresión '{expresion_polaca_1}': {resultado_1}")

expresion_polaca_2 = "5 2 * 8 + 4 -"
resultado_2 = evaluar_notacion_polaca_inversa(expresion_polaca_2)
print(f"Resultado de la expresión '{expresion_polaca_2}': {resultado_2}")

expresion_polaca_3 = "10 2 / 3 +"
resultado_3 = evaluar_notacion_polaca_inversa(expresion_polaca_3)
print(f"Resultado de la expresión '{expresion_polaca_3}': {resultado_3}")

expresion_polaca_4 = "15 7 3 * -"
resultado_4 = evaluar_notacion_polaca_inversa(expresion_polaca_4)
print(f"Resultado de la expresión '{expresion_polaca_4}': {resultado_4}")