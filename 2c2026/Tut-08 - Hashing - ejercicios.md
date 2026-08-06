Tut 08 – Hashing: Ejercicios
===

Estos ejercicios cubren la implementación manual de tablas de hash (con chaining y con open addressing) y problemas clásicos que se resuelven de forma mucho más eficiente usando hashing. Están ordenados de menor a mayor dificultad. Todo el código está en C++.



## Ejercicio 1: Tabla de hash con chaining

Implementar una tabla de hash genérica para claves y valores enteros, resolviendo colisiones con **encadenamiento**, con las operaciones `insertar`, `buscar` y `borrar`.

### Solución

```cpp
class HashTableChaining {
private:
    std::vector<std::vector<std::pair<int, int>>> tabla;

    int indice(int clave) const {
        // el módulo puede dar negativo si clave es negativa; nos aseguramos que no
        int m = static_cast<int>(tabla.size());
        return ((clave % m) + m) % m;
    }

public:
    HashTableChaining(int m) : tabla(m) {}

    void insertar(int clave, int valor) {
        int i = indice(clave);
        for (auto& par : tabla[i]) {
            if (par.first == clave) {
                par.second = valor; // ya existía, actualizo el valor
                return;
            }
        }
        tabla[i].push_back({clave, valor}); // clave nueva, la agrego al final de la lista
    }

    bool buscar(int clave, int& valorEncontrado) const {
        int i = indice(clave);
        for (const auto& par : tabla[i]) {
            if (par.first == clave) {
                valorEncontrado = par.second;
                return true;
            }
        }
        return false;
    }

    bool borrar(int clave) {
        int i = indice(clave);
        auto& lista = tabla[i];
        for (size_t j = 0; j < lista.size(); j++) {
            if (lista[j].first == clave) {
                lista.erase(lista.begin() + j); // O(k) donde k es el tamaño de la lista
                return true;
            }
        }
        return false;
    }
};
```

Complejidad esperada de las tres operaciones: **O(1)**, siempre que la función de hash reparta bien las claves y el factor de carga se mantenga controlado (en la práctica, rehasheando cuando crece demasiado).



## Ejercicio 2: Tabla de hash con open addressing (linear probing)

Implementar una tabla de hash de tamaño fijo para enteros, resolviendo colisiones con **linear probing**. Hay que soportar `insertar`, `buscar` y `borrar`, usando un estado `BORRADO` (tombstone) para no romper las cadenas de sondeo.

### Solución

```cpp
enum class Estado { VACIO, OCUPADO, BORRADO };

struct Slot {
    int clave = 0;
    Estado estado = Estado::VACIO;
};

class HashTableOpenAddressing {
private:
    std::vector<Slot> tabla;

    int hash(int clave) const {
        int m = static_cast<int>(tabla.size());
        return ((clave % m) + m) % m;
    }

public:
    HashTableOpenAddressing(int m) : tabla(m) {}

    bool insertar(int clave) {
        int m = static_cast<int>(tabla.size());
        int primerBorrado = -1; // reaprovechamos la primera lápida que encontremos

        for (int i = 0; i < m; i++) {
            int pos = (hash(clave) + i) % m;

            if (tabla[pos].estado == Estado::OCUPADO && tabla[pos].clave == clave) {
                return false; // ya estaba insertada
            }
            if (tabla[pos].estado == Estado::BORRADO && primerBorrado == -1) {
                primerBorrado = pos;
            }
            if (tabla[pos].estado == Estado::VACIO) {
                int destino = (primerBorrado != -1) ? primerBorrado : pos;
                tabla[destino] = {clave, Estado::OCUPADO};
                return true;
            }
        }
        return false; // tabla llena
    }

    bool buscar(int clave) const {
        int m = static_cast<int>(tabla.size());
        for (int i = 0; i < m; i++) {
            int pos = (hash(clave) + i) % m;
            if (tabla[pos].estado == Estado::VACIO) {
                return false; // corte: si hay un vacío real, la clave no puede estar más adelante
            }
            if (tabla[pos].estado == Estado::OCUPADO && tabla[pos].clave == clave) {
                return true;
            }
        }
        return false;
    }

    bool borrar(int clave) {
        int m = static_cast<int>(tabla.size());
        for (int i = 0; i < m; i++) {
            int pos = (hash(clave) + i) % m;
            if (tabla[pos].estado == Estado::VACIO) {
                return false;
            }
            if (tabla[pos].estado == Estado::OCUPADO && tabla[pos].clave == clave) {
                tabla[pos].estado = Estado::BORRADO; // lápida, no VACIO
                return true;
            }
        }
        return false;
    }
};
```

> Pregunta para pensar: ¿por qué `buscar` puede cortar apenas encuentra una posición `VACIO`, pero no puede cortar al encontrar una posición `BORRADO`?



## Ejercicio 3: Contar frecuencias de palabras

Dado un texto (un `std::vector<std::string>` con las palabras ya separadas), contar cuántas veces aparece cada palabra.

### Solución

```cpp
std::unordered_map<std::string, int> contarFrecuencias(const std::vector<std::string>& palabras) {
    std::unordered_map<std::string, int> frecuencias;
    for (const std::string& palabra : palabras) {
        frecuencias[palabra]++; // si no existía, unordered_map la crea con valor 0 y después suma 1
    }
    return frecuencias;
}
```

Complejidad: **O(n)** esperado, con n la cantidad de palabras (asumiendo que comparar/hashear cada palabra es O(longitud de la palabra), que en la práctica se trata como constante).



## Ejercicio 4: Two-sum

Dado un `std::vector<int> v` y un objetivo `k`, determinar si existen dos índices `i != j` tales que `v[i] + v[j] == k`.

### Solución

La solución ingenua prueba todos los pares en O(n²). Con una tabla de hash se resuelve en una sola pasada, en O(n):

```cpp
bool existeParSuma(const std::vector<int>& v, int k) {
    std::unordered_set<int> vistos;

    for (int x : v) {
        int complemento = k - x;
        if (vistos.count(complemento) > 0) {
            return true; // ya habíamos visto el complemento de x
        }
        vistos.insert(x);
    }
    return false;
}
```

La idea clave: en vez de buscar el par completo, por cada elemento `x` preguntamos "¿ya vi antes su complemento (`k - x`)?". Esa pregunta se responde en O(1) esperado con un `std::unordered_set`.

Complejidad: **O(n)** esperado, O(n) de memoria extra.



## Ejercicio 5: Detectar duplicados

Dado un `std::vector<int>`, determinar si hay algún valor repetido.

### Solución

```cpp
bool tieneDuplicados(const std::vector<int>& v) {
    std::unordered_set<int> vistos;
    for (int x : v) {
        if (vistos.count(x) > 0) {
            return true;
        }
        vistos.insert(x);
    }
    return false;
}
```

Complejidad: **O(n)** esperado, en lugar de O(n log n) si lo resolviéramos ordenando, o O(n²) comparando todos los pares.



## Ejercicio 6: Primer carácter que no se repite

Dado un `std::string`, encontrar el primer carácter que aparece **exactamente una vez**. Si no existe ninguno, devolver `'\0'`.

### Solución

Se hace en dos pasadas: una para contar frecuencias, y otra para encontrar el primer carácter con frecuencia 1 (recorriendo el string en su orden original, no el orden del hash).

```cpp
char primerNoRepetido(const std::string& s) {
    std::unordered_map<char, int> frecuencias;

    for (char c : s) {
        frecuencias[c]++;
    }

    for (char c : s) {
        if (frecuencias[c] == 1) {
            return c; // el primero, en el orden del string, con frecuencia 1
        }
    }

    return '\0'; // no hay ninguno
}
```

> Pregunta para pensar: ¿por qué hace falta una segunda pasada sobre el string en lugar de recorrer directamente el `unordered_map`? *Ayuda: pensar si un `unordered_map` preserva el orden de inserción.*

Complejidad: **O(n)**, con n el largo del string.



## Ejercicio 7: Agrupar anagramas

Dado un `std::vector<std::string>`, agrupar las palabras que son anagramas entre sí (misma multiplicidad de letras, en cualquier orden). Por ejemplo, `{"roma", "amor", "gato", "toga"}` debería agruparse en `{"roma", "amor"}` y `{"gato", "toga"}`.

### Solución

La idea es usar como **clave de hash** una forma canónica de cada palabra: por ejemplo, sus letras ordenadas alfabéticamente. Dos palabras son anagramas si y solo si su forma canónica coincide.

```cpp
std::vector<std::vector<std::string>> agruparAnagramas(const std::vector<std::string>& palabras) {
    std::unordered_map<std::string, std::vector<std::string>> grupos;

    for (const std::string& palabra : palabras) {
        std::string clave = palabra;
        std::sort(clave.begin(), clave.end()); // forma canónica: letras ordenadas
        grupos[clave].push_back(palabra);
    }

    std::vector<std::vector<std::string>> resultado;
    for (auto& [clave, grupo] : grupos) {
        resultado.push_back(grupo);
    }
    return resultado;
}
```

Complejidad: **O(n · L log L)**, donde n es la cantidad de palabras y L el largo máximo de una palabra (por el `sort` de cada una). El agrupamiento en sí, gracias al `unordered_map`, es O(1) esperado por palabra.



## Ejercicios propuestos

1. Adaptar la solución del ejercicio 2 (open addressing) para usar **quadratic probing** en lugar de linear probing, y agregar un `rehash()` que duplique el tamaño de la tabla cuando el factor de carga supere 0.7.
2. Implementar una **caché LRU** (*Least Recently Used*) de capacidad fija, combinando un `std::unordered_map` (para acceso O(1) por clave) con una lista doblemente enlazada (para saber cuál fue el elemento usado hace más tiempo). *Ayuda: el mapa guarda, para cada clave, un puntero/iterador al nodo correspondiente de la lista.*
