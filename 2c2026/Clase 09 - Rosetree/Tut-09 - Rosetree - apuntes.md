Tutorial 9 – Rosetree
===

> **Ingeniería en Inteligencia Artificial** — **Algoritmos y Estructura de Datos**
> **2C 2026** · Docente: **Ing. Magali Marijuan**

- [Tutorial 9 – Rosetree](#tutorial-9--rosetree)
- [Objetivos de la clase](#objetivos-de-la-clase)
- [Rosetree (árbol n-ario)](#rosetree-árbol-n-ario)
  - [¿Qué es un rosetree?](#qué-es-un-rosetree)
  - [Representación en C++](#representación-en-c)
  - [Recorridos y recursión](#recorridos-y-recursión)
  - [Ejemplos donde aparece naturalmente](#ejemplos-donde-aparece-naturalmente)



# Objetivos de la clase
- Entender qué es un rosetree (árbol n-ario) y cómo recorrerlo recursivamente.
- Reconocer situaciones de la vida real que se modelan naturalmente con un rosetree.



# Rosetree (árbol n-ario)

## ¿Qué es un rosetree?

Hasta ahora trabajamos sobre todo con árboles **binarios**, donde cada nodo tiene a lo sumo dos hijos. Un **rosetree** (también llamado árbol n-ario o *árbol general*) generaliza esa idea: cada nodo puede tener **cualquier cantidad de hijos**, desde cero hasta n.

> Un rosetree no tiene "hijo izquierdo" ni "hijo derecho": tiene una **colección ordenada de hijos**.

Es la estructura que usamos naturalmente cuando pensamos en jerarquías: una carpeta que contiene archivos y otras carpetas, un organigrama de una empresa, el árbol genealógico de un torneo, o el árbol de decisiones de un juego.

## Representación en C++

En Python uno podría representar un nodo con una lista de hijos sin pensarlo demasiado. En C++, como es un lenguaje de tipado estático, necesitamos definir explícitamente la estructura. Usamos un `struct` con un `std::vector` de punteros a los hijos:

```cpp
template <typename T>
struct Rosetree {
    T valor;
    std::vector<Rosetree<T>*> hijos;
};
```

> ¿Por qué `std::vector<Rosetree<T>*>` y no `std::vector<Rosetree<T>>`? Porque el tipo `Rosetree<T>` se está definiendo a sí mismo (es un tipo recursivo). El compilador necesita conocer el tamaño exacto de la estructura, y un vector de punteros tiene tamaño fijo (son direcciones de memoria), mientras que un vector de "Rosetree por valor" tendría tamaño indefinido.

Crear un nodo hoja y agregarle hijos es directo:

```cpp
Rosetree<std::string>* raiz = new Rosetree<std::string>{"Documentos", {}};
Rosetree<std::string>* hijo1 = new Rosetree<std::string>{"Fotos", {}};
Rosetree<std::string>* hijo2 = new Rosetree<std::string>{"Tesis.pdf", {}};

raiz->hijos.push_back(hijo1);
raiz->hijos.push_back(hijo2);
```

## Recorridos y recursión

Un rosetree se recorre de forma muy parecida a un árbol binario, solo que en vez de "visitar izquierda y derecha" hay que **recorrer el vector de hijos**. La receta general de cualquier función recursiva sobre un rosetree es:

1. **Caso base**: el nodo es `nullptr` (árbol vacío) o no tiene hijos (es una hoja).
2. **Caso recursivo**: procesar el nodo actual y combinar el resultado de aplicar la misma función a cada uno de sus hijos, recorriendo el `std::vector<Rosetree<T>*>` con un `for`.

Por ejemplo, contar la cantidad de nodos de un rosetree:

```cpp
int contarNodos(Rosetree<int>* nodo) {
    if (nodo == nullptr) {
        return 0;
    }
    int total = 1; // me cuento a mí mismo
    for (Rosetree<int>* hijo : nodo->hijos) {
        total += contarNodos(hijo);
    }
    return total;
}
```

Calcular la altura es análogo, pero en vez de sumar hay que quedarse con el **máximo** entre los hijos:

```cpp
int altura(Rosetree<int>* nodo) {
    if (nodo == nullptr) {
        return 0;
    }
    if (nodo->hijos.empty()) {
        return 1; // una hoja tiene altura 1
    }
    int alturaMax = 0;
    for (Rosetree<int>* hijo : nodo->hijos) {
        alturaMax = std::max(alturaMax, altura(hijo));
    }
    return 1 + alturaMax;
}
```

> Pregunta para pensar: en un árbol binario la recursión hace dos llamados (izquierda y derecha). En un rosetree, ¿cuántos llamados recursivos se hacen? ¿Depende del nodo?

> Pregunta para pensar: ¿cómo cambiaría `contarNodos` si quisiéramos contar solamente las **hojas** del árbol?

## Ejemplos donde aparece naturalmente

El rosetree no es una curiosidad teórica: aparece todo el tiempo en problemas reales.

| Ejemplo | Nodo | Hijos |
|---|---|---|
| Sistema de archivos | Carpeta o archivo | Subcarpetas y archivos que contiene |
| Organigrama de una empresa | Empleado | Sus reportes directos |
| Árbol de decisión de un juego | Estado del juego | Cada jugada posible desde ese estado |
| Árbol sintáctico de una expresión | Operador o subexpresión | Sus operandos |
| Comentarios anidados (foro, redes sociales) | Comentario | Respuestas a ese comentario |

> Tip: cuando en un enunciado aparece la palabra "jerarquía", "carpeta", "subordinados" o "anidado", es una buena pista de que conviene modelar el problema con un rosetree en vez de forzarlo a un árbol binario.
