Tut 08 – Hashing
===

> **Ingeniería en Inteligencia Artificial** — **Algoritmos y Estructura de Datos**  
> **2C 2026** · Docente: **Magali Marijuan**

- [Tut 08 – Hashing](#tut-08--hashing)
- [Objetivos de la clase](#objetivos-de-la-clase)
- [Idea de tabla de hash](#idea-de-tabla-de-hash)
  - [La función de hash](#la-función-de-hash)
    - [¿Qué hace buena a una función de hash?](#qué-hace-buena-a-una-función-de-hash)
    - [Uso del módulo](#uso-del-módulo)
- [Manejo de colisiones](#manejo-de-colisiones)
  - [Encadenamiento (chaining)](#encadenamiento-chaining)
  - [Direccionamiento abierto (open addressing)](#direccionamiento-abierto-open-addressing)
    - [Linear probing](#linear-probing)
    - [Quadratic probing](#quadratic-probing)
    - [Double hashing](#double-hashing)
- [Factor de carga y rehashing](#factor-de-carga-y-rehashing)
- [Complejidad esperada vs peor caso](#complejidad-esperada-vs-peor-caso)
- [Comparación con estructuras basadas en árbol](#comparación-con-estructuras-basadas-en-árbol)
- [La STL: `std::unordered_map` y `std::unordered_set`](#la-stl-stdunordered_map-y-stdunordered_set)



# Objetivos de la clase
- Entender la idea de tabla de hash y qué rol cumple una función de hash.
- Reconocer qué hace buena a una función de hash y por qué se usa el operador módulo.
- Comprender e implementar las dos grandes estrategias para resolver colisiones: encadenamiento y direccionamiento abierto (linear, quadratic y double hashing).
- Entender el factor de carga y cuándo/por qué conviene rehashear.
- Comparar la complejidad esperada y peor caso del hashing contra las estructuras basadas en árbol.



# Idea de tabla de hash

Muchas de las estructuras que vimos hasta ahora (listas, árboles) necesitan **recorrer** parte de la estructura para buscar un elemento: O(n) en una lista, O(log n) en un árbol balanceado. Una **tabla de hash** propone algo distinto: calcular directamente **en qué posición de un arreglo debería estar** un elemento, a partir de su clave.

La idea central es:

1. Reservamos un arreglo (la **tabla**) de tamaño fijo `m`.
2. Cada clave se transforma, mediante una **función de hash**, en un índice dentro de `[0, m-1]`.
3. Guardamos el elemento en esa posición del arreglo.

Si la función de hash reparte bien las claves, insertar, buscar y borrar cuestan, en promedio, **O(1)**.

> Pregunta para pensar: si tuviéramos un arreglo con una posición para cada clave posible (por ejemplo, un arreglo de 256 posiciones para guardar caracteres), ¿haría falta una función de hash? ¿Qué pasa cuando las claves posibles son, por ejemplo, todos los strings?

## La función de hash

Una **función de hash** `h(clave)` toma una clave (un entero, un string, un objeto) y devuelve un índice dentro del rango de la tabla.

```cpp
int hash(const std::string& clave, int m) {
    unsigned long suma = 0;
    for (char c : clave) {
        suma = suma * 31 + static_cast<unsigned long>(c);
    }
    return static_cast<int>(suma % static_cast<unsigned long>(m));
}
```

### ¿Qué hace buena a una función de hash?

- **Determinística**: la misma clave siempre debe producir el mismo índice.
- **Rápida de calcular**: idealmente O(1) respecto del tamaño de la tabla (aunque puede depender del tamaño de la clave, como en un string).
- **Buena distribución**: debe repartir las claves lo más uniformemente posible entre todas las posiciones de la tabla, para minimizar colisiones.
- **Efecto avalancha**: pequeños cambios en la clave (por ejemplo, cambiar un solo carácter) deberían producir índices muy distintos.

> Una **colisión** ocurre cuando dos claves distintas producen el mismo índice: `h(clave1) == h(clave2)` con `clave1 != clave2`. Las colisiones son inevitables (por el [principio del palomar](https://es.wikipedia.org/wiki/Principio_del_palomar): si hay más claves posibles que posiciones en la tabla, tarde o temprano dos claves van a "chocar"), así que toda tabla de hash necesita una estrategia para resolverlas.

### Uso del módulo

Casi siempre la función de hash se calcula en dos pasos: primero se convierte la clave en un número entero grande (a veces llamado *hash code*), y después se aplica el operador módulo (`%`) para llevarlo al rango `[0, m-1]` de la tabla:

```cpp
int indice = hashCode(clave) % m;
```

> Tip: conviene que `m` sea un número **primo**. Si `m` no es primo y las claves (o sus hash codes) comparten factores comunes con `m`, la distribución de índices puede volverse mucho peor de lo esperado, concentrando las claves en pocas posiciones.



# Manejo de colisiones

## Encadenamiento (chaining)

La idea más directa: en vez de guardar **un** elemento por posición, cada posición de la tabla guarda una **lista** (o un `std::vector`) con todos los elementos que colisionaron en ese índice.

```cpp
template <typename K, typename V>
class HashTableChaining {
private:
    std::vector<std::vector<std::pair<K, V>>> tabla;
    int cantidad;

    int indice(const K& clave) const {
        return static_cast<int>(std::hash<K>{}(clave) % tabla.size());
    }

public:
    HashTableChaining(int m) : tabla(m), cantidad(0) {}

    void insertar(const K& clave, const V& valor) {
        int i = indice(clave);
        for (auto& par : tabla[i]) {
            if (par.first == clave) {
                par.second = valor; // ya existía: actualizo
                return;
            }
        }
        tabla[i].push_back({clave, valor});
        cantidad++;
    }

    bool buscar(const K& clave, V& valorEncontrado) const {
        int i = indice(clave);
        for (const auto& par : tabla[i]) {
            if (par.first == clave) {
                valorEncontrado = par.second;
                return true;
            }
        }
        return false;
    }

    bool borrar(const K& clave) {
        int i = indice(clave);
        auto& lista = tabla[i];
        for (size_t j = 0; j < lista.size(); j++) {
            if (lista[j].first == clave) {
                lista.erase(lista.begin() + j);
                cantidad--;
                return true;
            }
        }
        return false;
    }
};
```

> Con encadenamiento, la tabla nunca "se llena": siempre se puede insertar un elemento más, aunque eso vaya degradando el rendimiento si las listas se hacen muy largas.

## Direccionamiento abierto (open addressing)

En esta estrategia, **todos los elementos viven directamente en el arreglo** (no hay listas). Cuando una posición ya está ocupada, se busca otra posición libre siguiendo una **secuencia de sondeo** (*probing*).

```cpp
enum class Estado { VACIO, OCUPADO, BORRADO };

struct Slot {
    int clave;
    int valor;
    Estado estado = Estado::VACIO;
};
```

> El estado `BORRADO` (también llamado *tombstone* o lápida) es fundamental: si al borrar simplemente marcáramos la posición como `VACIO`, romperíamos la cadena de sondeo para búsquedas futuras de otras claves que hubieran colisionado y pasado "por encima" de esa posición.

### Linear probing

Si la posición `h(clave)` está ocupada, se prueba la siguiente, y la siguiente, y así sucesivamente (con vuelta circular al principio de la tabla):

```
posición(clave, i) = (h(clave) + i) % m,   i = 0, 1, 2, ...
```

```cpp
int buscarPosicion(const std::vector<Slot>& tabla, int clave) {
    int m = static_cast<int>(tabla.size());
    int i = 0;
    while (i < m) {
        int pos = (hash(clave, m) + i) % m;
        if (tabla[pos].estado == Estado::VACIO) {
            return pos; // clave no está, pero acá se podría insertar
        }
        if (tabla[pos].estado == Estado::OCUPADO && tabla[pos].clave == clave) {
            return pos; // encontrada
        }
        i++;
    }
    return -1; // tabla llena, no está
}
```

> El linear probing es simple y aprovecha bien la localidad de la memoria caché, pero sufre de **agrupamiento primario** (*primary clustering*): las posiciones ocupadas tienden a formar bloques largos y consecutivos, lo que empeora el tiempo de búsqueda.

### Quadratic probing

Para evitar el agrupamiento primario, se prueba con saltos que crecen **cuadráticamente**:

```
posición(clave, i) = (h(clave) + i²) % m,   i = 0, 1, 2, ...
```

```cpp
int pos = (hash(clave, m) + i * i) % m;
```

Reduce el agrupamiento primario, aunque introduce un problema distinto llamado **agrupamiento secundario** (claves que colisionan en el mismo `h(clave)` siguen exactamente la misma secuencia de sondeo).

### Double hashing

Se usa una **segunda función de hash** para determinar el salto entre un intento y el siguiente, lo que distribuye mucho mejor las colisiones:

```
posición(clave, i) = (h1(clave) + i * h2(clave)) % m,   i = 0, 1, 2, ...
```

```cpp
int pos = (h1(clave, m) + i * h2(clave, m)) % m;
```

> Para que double hashing recorra **todas** las posiciones de la tabla (y no entre en un ciclo corto), `h2(clave)` nunca debe dar 0, y conviene que `m` sea primo.

## Factor de carga y rehashing

El **factor de carga** (*load factor*) se define como:

```
α = cantidad de elementos guardados / tamaño de la tabla (n / m)
```

| Estrategia | Factor de carga típico |
|---|---|
| Encadenamiento | puede superar 1 (varios elementos por posición) |
| Direccionamiento abierto | siempre menor a 1 (una sola clave por posición) |

Cuando `α` supera cierto umbral (por ejemplo, 0.7), el rendimiento empieza a degradarse: en chaining las listas se alargan, y en direccionamiento abierto las secuencias de sondeo se hacen cada vez más largas.

La solución es el **rehashing**: se crea una tabla nueva, más grande (típicamente el doble), y se **reinsertan todos los elementos** aplicando la función de hash con el nuevo tamaño `m`.

```cpp
void rehash() {
    std::vector<std::vector<std::pair<K, V>>> tablaVieja = tabla;
    tabla.assign(tabla.size() * 2, {});
    cantidad = 0;
    for (auto& lista : tablaVieja) {
        for (auto& par : lista) {
            insertar(par.first, par.second);
        }
    }
}
```

> El rehashing es O(n), pero al duplicar el tamaño cada vez, el costo se **amortiza**: en promedio, insertar sigue siendo O(1) amortizado, del mismo modo que ocurre con la reserva de memoria de un `std::vector`.

## Complejidad esperada vs peor caso

| Operación | Caso promedio | Peor caso |
|---|---|---|
| `insertar` | O(1) | O(n) |
| `buscar` | O(1) | O(n) |
| `borrar` | O(1) | O(n) |

El **peor caso** ocurre cuando la función de hash distribuye mal las claves (o directamente todas las claves colisionan en el mismo índice): ahí la tabla de hash degenera en, esencialmente, una lista.

> Pregunta para pensar: ¿por qué decimos que el caso promedio es O(1) "esperado" y no simplemente O(1) a secas? ¿Qué tiene que cumplirse para que esa afirmación sea válida?

## Comparación con estructuras basadas en árbol

| Estructura | Búsqueda (promedio) | Búsqueda (peor caso) | ¿Mantiene orden? |
|---|---|---|---|
| Tabla de hash | O(1) | O(n) | No |
| Árbol binario de búsqueda (sin balancear) | O(log n) | O(n) | Sí |
| Árbol balanceado (AVL, rojo-negro) | O(log n) | O(log n) | Sí |

La tabla de hash gana en velocidad promedio, pero **no preserva ningún orden** entre las claves: no se puede recorrerla de menor a mayor, ni pedir "el siguiente elemento" de forma eficiente. Cuando el problema necesita ese orden (rangos, mínimo/máximo, recorrido ordenado), conviene un árbol balanceado en lugar de una tabla de hash.

> Tip: si un enunciado pide buscar, insertar o borrar por clave sin importar el orden, pensar primero en una tabla de hash. Si además pide "el menor mayor que X", "los elementos entre A y B" o recorrer todo ordenado, ahí conviene un árbol.

## La STL: `std::unordered_map` y `std::unordered_set`

C++ ya trae tablas de hash implementadas en la librería estándar, con encadenamiento por dentro:

```cpp
#include <unordered_map>
#include <unordered_set>

std::unordered_map<std::string, int> edades;
edades["Ana"] = 21;
edades["Beto"] = 23;

if (edades.find("Ana") != edades.end()) {
    std::cout << edades["Ana"] << "\n"; // 21
}

std::unordered_set<int> vistos;
vistos.insert(5);
bool estaRepetido = vistos.count(5) > 0; // true
```

> Tip: en los ejercicios y parciales suele pedirse implementar la tabla de hash "a mano" para entender el manejo de colisiones, pero en código de uso general siempre conviene usar `std::unordered_map` / `std::unordered_set`. Si en cambio se necesita orden, existen `std::map` y `std::set`, que están implementados con árboles balanceados (O(log n)).
