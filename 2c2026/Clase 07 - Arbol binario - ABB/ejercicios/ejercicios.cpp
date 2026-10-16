#include "ejercicios.h"
#include <algorithm>  // para std::max
<<<<<<< HEAD
#include <climits>
=======
>>>>>>> upstream/main

// ============================================================================
// Acá va TU código. Cada función tiene una cáscara con un "TODO": borrá el
// contenido de ejemplo y escribí la implementación.
//
// Los `(void)parametro;` que ves abajo están solo para que la cáscara
// compile sin advertencias antes de que la implementes. Cuando uses el
// parámetro en tu código, borrá la línea `(void)...` correspondiente.
// ============================================================================

// ============================================================================
// RECORRIDOS DE ÁRBOLES BINARIOS
// ============================================================================

// Ejercicio 1 — Preorder
void preorder(NodoAB<int>* nodo, std::vector<int>& resultado)
{
    // TODO: implementar preorder.
    // Recordá:
    //   - Si el nodo es nulo, no hay nada que hacer (caso base).
    //   - Primero agregar el valor del nodo actual al resultado.
    //   - Luego recorrer recursivamente el subárbol izquierdo.
    //   - Finalmente recorrer recursivamente el subárbol derecho.
    (void)nodo;
    (void)resultado;
<<<<<<< HEAD
    if (nodo==nullptr){
        return;
    }
    resultado.push_back(nodo->valor);
    preorder(nodo->izq,resultado);
    preorder(nodo->der,resultado);

=======
>>>>>>> upstream/main
}

// Ejercicio 2 — Inorder
void inorder(NodoAB<int>* nodo, std::vector<int>& resultado)
{
    // TODO: implementar inorder.
    // Recordá:
    //   - Si el nodo es nulo, no hay nada que hacer (caso base).
    //   - Primero recorrer recursivamente el subárbol izquierdo.
    //   - Luego agregar el valor del nodo actual al resultado.
    //   - Finalmente recorrer recursivamente el subárbol derecho.
<<<<<<< HEAD
    
    if (nodo==nullptr){
        return;
    }
    inorder(nodo->izq,resultado);
    resultado.push_back(nodo->valor);
    inorder(nodo->der,resultado);
=======
    (void)nodo;
    (void)resultado;
>>>>>>> upstream/main
}

// Ejercicio 3 — Postorder
void postorder(NodoAB<int>* nodo, std::vector<int>& resultado)
{
    // TODO: implementar postorder.
    // Recordá:
    //   - Si el nodo es nulo, no hay nada que hacer (caso base).
    //   - Primero recorrer recursivamente el subárbol izquierdo.
    //   - Luego recorrer recursivamente el subárbol derecho.
    //   - Finalmente agregar el valor del nodo actual al resultado.
    (void)nodo;
    (void)resultado;
<<<<<<< HEAD
    if (nodo==nullptr){
        return;
    }
    postorder(nodo->izq,resultado);
    postorder(nodo->der,resultado);
    resultado.push_back(nodo->valor);
    
=======
>>>>>>> upstream/main
}

// ============================================================================
// PROPIEDADES DEL ÁRBOL
// ============================================================================

// Ejercicio 4 — Altura
int altura(NodoAB<int>* nodo)
{
    // TODO: implementar altura.
    // Recordá:
    //   - Si el nodo es nulo, la altura es 0.
    //   - Si no, la altura es 1 + el máximo entre la altura del subárbol
    //     izquierdo y la altura del subárbol derecho.
<<<<<<< HEAD
    
    if (nodo==nullptr)
        return 0;
    return 1 + std::max(altura(nodo->der),altura(nodo->izq));
=======
    (void)nodo;
    return 0;
>>>>>>> upstream/main
}

// Ejercicio 5 — Tamaño
int tamanio(NodoAB<int>* nodo)
{
    // TODO: implementar tamanio.
    // Recordá:
    //   - Si el nodo es nulo, el tamaño es 0.
    //   - Si no, el tamaño es 1 + tamaño del subárbol izquierdo + tamaño
    //     del subárbol derecho.
<<<<<<< HEAD
    
    if (nodo==nullptr){
        return 0;
    }
    return 1+tamanio(nodo->izq)+tamanio(nodo->der);
=======
    (void)nodo;
    return 0;
>>>>>>> upstream/main
}

// ============================================================================
// OPERACIONES DE ABB
// ============================================================================

// Ejercicio 6 — Búsqueda en ABB
NodoAB<int>* buscar(NodoAB<int>* nodo, int valor)
{
    // TODO: implementar búsqueda en ABB.
    // Recordá:
    //   - Si el nodo es nulo, el valor no está (devolver nullptr).
    //   - Si el valor es igual al del nodo, lo encontramos (devolver nodo).
    //   - Si el valor es menor, buscar en el subárbol izquierdo.
    //   - Si el valor es mayor, buscar en el subárbol derecho.
<<<<<<< HEAD
    if (nodo==nullptr) return nullptr;
    if (nodo->valor ==valor) return nodo;
    if (nodo->valor > valor) return buscar (nodo->izq,valor);
    if (nodo->valor <valor) return buscar(nodo->der,valor);
=======
    (void)nodo;
    (void)valor;
>>>>>>> upstream/main
    return nullptr;
}

// Ejercicio 7 — Inserción en ABB
NodoAB<int>* insertar(NodoAB<int>* nodo, int valor)
{
    // TODO: implementar inserción en ABB.
    // Recordá:
    //   - Si el nodo es nulo, crear un nuevo nodo con el valor.
    //   - Si el valor es menor, insertar en el subárbol izquierdo y
    //     actualizar nodo->izq.
    //   - Si el valor es mayor, insertar en el subárbol derecho y
    //     actualizar nodo->der.
    //   - Si el valor es igual, no hacer nada (no permitimos duplicados).
    //   - Devolver el nodo (puede ser el nuevo nodo si era nulo).
    (void)nodo;
    (void)valor;
<<<<<<< HEAD
    if (nodo==nullptr){
        NodoAB<int>* nuevo= new NodoAB<int>(valor);
        return nuevo;
    }
    if (valor < nodo->valor){
        nodo->izq= insertar(nodo->izq,valor);
    }
    if (valor>nodo->valor){
        nodo->der=insertar(nodo->der,valor);
    }
    return nodo;
=======
    return nullptr;
>>>>>>> upstream/main
}

// Ejercicio 8 — Mínimo en ABB
NodoAB<int>* minimo(NodoAB<int>* nodo)
{
    // TODO: implementar mínimo en ABB.
    // Recordá:
    //   - El mínimo está en el nodo más a la izquierda.
    //   - Mientras haya hijo izquierdo, avanzar hacia la izquierda.
<<<<<<< HEAD
    if(nodo->izq==nullptr){
        return nodo;
    }
    return minimo(nodo->izq);

=======
    (void)nodo;
    return nullptr;
>>>>>>> upstream/main
}

// Ejercicio 9 — Máximo en ABB
NodoAB<int>* maximo(NodoAB<int>* nodo)
{
    // TODO: implementar máximo en ABB.
    // Recordá:
    //   - El máximo está en el nodo más a la derecha.
    //   - Mientras haya hijo derecho, avanzar hacia la derecha.
<<<<<<< HEAD
    if (nodo->der ==nullptr){
        return nodo;
    }
    return maximo(nodo->der);
}

// Ejercicio 10 — Eliminación en ABB
NodoAB<int>* eliminar(NodoAB<int>* nodo, int valor){
=======
    (void)nodo;
    return nullptr;
}

// Ejercicio 10 — Eliminación en ABB
NodoAB<int>* eliminar(NodoAB<int>* nodo, int valor)
{
>>>>>>> upstream/main
    // TODO: implementar eliminación en ABB.
    // Recordá los tres casos:
    //   - Caso 1 (hoja): simplemente eliminar el nodo.
    //   - Caso 2 (un hijo): reemplazar el nodo por su único hijo.
    //   - Caso 3 (dos hijos): reemplazar el valor por el del sucesor
    //     inorder (mínimo del subárbol derecho) y luego eliminar el
    //     sucesor recursivamente.
    // No te olvides de liberar la memoria del nodo eliminado con delete.
<<<<<<< HEAD
    if (nodo == nullptr) return nullptr;   // el valor no estaba

    if (valor < nodo->valor){
        nodo->izq = eliminar(nodo->izq, valor);
    }
    else if (valor > nodo->valor){
        nodo->der = eliminar(nodo->der, valor);
    }
    else {
        // lo encontré
        if (nodo->izq != nullptr && nodo->der != nullptr){
            // caso 3: dos hijos
            NodoAB<int>* sucesor = minimo(nodo->der);
            nodo->valor = sucesor->valor;
            nodo->der = eliminar(nodo->der, sucesor->valor);
        }
        else {
            // caso 1 y 2: hoja o un hijo
            NodoAB<int>* hijo = (nodo->izq != nullptr) ? nodo->izq : nodo->der;
            delete nodo;
            return hijo;   // si era hoja, hijo es nullptr
        }
        return nodo;
    }
    
}
   
bool verificar(NodoAB<int>*nodo, int min, int max){
    if (nodo==nullptr){
        return true;
    }
    if (nodo->valor<max && nodo->valor>min){
        return verificar(nodo->izq,min,nodo->valor) && verificar(nodo->der,nodo->valor,max);
    }
    return false;
    
    
=======
    (void)nodo;
    (void)valor;
    return nullptr;
>>>>>>> upstream/main
}

// ============================================================================
// EJERCICIOS PROPUESTOS
// ============================================================================

// Propuesto 1 — Verificar si es ABB
bool esABB(NodoAB<int>* nodo)
{
    // TODO: implementar verificación de ABB.
    // Pista: usá una función auxiliar que reciba cotas (mínimo y máximo
    // permitidos) y verifique recursivamente que cada nodo esté dentro
    // del rango válido. Podés usar INT_MIN e INT_MAX como cotas iniciales.
<<<<<<< HEAD
    return verificar(nodo, INT_MIN, INT_MAX);
    
=======
    (void)nodo;
    return false;
>>>>>>> upstream/main
}

// Propuesto 2 — k-ésimo elemento en inorder
int kEsimoInorder(NodoAB<int>* nodo, int k)
{
    // TODO: implementar k-ésimo en inorder.
    // Pista: podés hacer un recorrido inorder que lleve un contador
    // (pasado por referencia) y se detenga cuando llegue a k.
    // Otra opción: usar una función auxiliar que devuelva cuántos nodos
    // procesó del subárbol y vaya acumulando.
    (void)nodo;
    (void)k;
    return -1;
}

// Propuesto 3 — Ancestro común más bajo (en ABB)
int ancestroComun(NodoAB<int>* nodo, int valor1, int valor2)
{
    // TODO: implementar ancestro común en ABB.
    // Recordá:
    //   - Si ambos valores son menores que el nodo actual, el LCA está
    //     en el subárbol izquierdo.
    //   - Si ambos valores son mayores que el nodo actual, el LCA está
    //     en el subárbol derecho.
    //   - Si los valores están "separados" (uno a cada lado) o uno de
    //     ellos es igual al nodo actual, entonces el nodo actual es el LCA.
    (void)nodo;
    (void)valor1;
    (void)valor2;
    return -1;
}

// Propuesto 4 — Liberar árbol
void liberarArbol(NodoAB<int>* nodo)
{
    // TODO: implementar liberación del árbol.
    // Recordá:
    //   - Hay que liberar los hijos ANTES que el padre (postorder).
    //   - Si el nodo es nulo, no hay nada que hacer.
    //   - Primero liberar recursivamente el subárbol izquierdo.
    //   - Luego liberar recursivamente el subárbol derecho.
    //   - Finalmente liberar el nodo actual con delete.
    (void)nodo;
}
