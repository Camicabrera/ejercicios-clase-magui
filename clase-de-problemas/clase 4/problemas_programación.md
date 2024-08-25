# Clase IV
*Algoritmos y estructuras de datos*

## Problema 1: Top K

*Ejercicio 8.2*

### Enunciado

Queremos una función top k que recibe un arreglo de números y un
valor k y devuelve los k mayores del arreglo. 

1. La primer implementación ordena el arreglo y busca los k mayores en las primeras k
posiciones. Indique el orden.
2. La segunda implementación usa un arreglo auxiliar de k elementos. Se recorre el arreglo de números y cada número se compara con los k en el arreglo auxiliar: si es mayor a alguno se saca el menor de ellos reemplazándolo por el nuevo. Indique el orden de esta implementación.
   
3. Realice una implementación cuyo orden sea O(n log k).


## Problema 2: Mantenimiento de Mediana Dinámica

*Ejercicio 8.6*

### Enunciado:
Estás desarrollando un sistema que necesita calcular la mediana de un conjunto de números en tiempo real. Inicialmente, el sistema está vacío, y los números se agregan uno por uno. Después de cada adición, debes devolver la mediana del conjunto actual.

La mediana es el valor que divide el conjunto de números en dos partes iguales: la mitad de los números son menores o iguales a la mediana y la otra mitad son mayores o iguales. Si el conjunto tiene un número impar de elementos, la mediana es el valor en la posición central. Si tiene un número par de elementos, la mediana es el promedio de los dos valores centrales.

### Ejemplo:

- Entrada: 6 5 2 1 7 5 3
- Salida: 5 3.5 2 3.5 5 4

- Explicación:
    - Después de agregar `5`, el conjunto es `[5]` y la mediana es `5`.
    - Después de agregar `2`, el conjunto es `[2, 5]` y la mediana es `(2 + 5) / 2 = 3.5`.
    - Después de agregar `1`, el conjunto es `[1, 2, 5]` y la mediana es `2`.
    - Después de agregar `7`, el conjunto es `[1, 2, 5, 7]` y la mediana es `(2 + 5) / 2 = 3.5`.
    - Después de agregar `5`, el conjunto es `[1, 2, 5, 5, 7]` y la mediana es `5`.
    - Después de agregar `3`, el conjunto es `[1, 2, 3, 5, 5, 7]` y la mediana es `(3 + 5) / 2 = 4`.


