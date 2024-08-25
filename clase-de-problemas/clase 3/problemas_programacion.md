# Clase III
*Algoritmos y estructuras de datos*

## Problema 1: Procesamiento de Eventos en Tiempo Real

En un sistema de monitoreo, los eventos ocurren en tiempo real y cada evento tiene un tiempo de vida limitado. A medida que los eventos llegan, es necesario mantener una lista de aquellos que aún son válidos, es decir, que no han expirado.

### Requisitos:
- Implementa un sistema que mantenga los eventos en una estructura de datos apropiada y elimine los eventos que ya han expirado.
- La estructura debe permitir agregar nuevos eventos, eliminar eventos expirados y consultar los eventos actuales de manera eficiente.

### Entrada:
Una serie de pares `(timestamp, duration)` que indican el momento en que ocurrió cada evento y la duración de su validez en segundos.

### Salida:
Los eventos que aún no han expirado después de procesar cada nuevo evento.

---

## Problema 2: Generar números binarios entre 1 y n 

Dado un número positivo n, generar de manera eficiente los números binarios entre 1 y n.

### Requisitos:
- El algoritmo debe ser eficiente y generar los números en tiempo lineal.

### Entrada:
Un número entero positivo n.

### Salida:
Una secuencia de números binarios, desde 1 hasta n.

### Ejemplo 
- Entrada: n = 16
- Salida: 1 10 11 100 101 110 111 1000 1001 1010 1011 1100 1101 1110 1111 10000

---