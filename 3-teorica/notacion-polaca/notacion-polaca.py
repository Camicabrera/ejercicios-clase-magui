def evaluar_notacion_polaca_inversa(expresion):
    pila = []
    operadores = set(["+","-","*","/"])
    for token in expresion.split():
        if token.isdigit():
            pila.append(int(token))
        elif token in operadores:
            operando1 = pila.pop()
            operando2 = pila.pop()


            if token == '+':
                pila.append(operando1 + operando2)
            elif token == '-':
                pila.append(operando2 - operando1)
            elif token == '*':
                pila.append(operando1 * operando2)
            elif token == '/':
                pila.append(operando2 / operando1)
    return pila[0]
    
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