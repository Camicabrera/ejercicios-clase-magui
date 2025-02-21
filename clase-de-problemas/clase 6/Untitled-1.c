

nodo_t* segundo_siguiente(nodo_t* actual) { 
    
    List_t* lista = create_lista();
    segundo_siguiente_(actual->left, lista);
    
    node_t * current = lista->head;
    for(int i = 0; i < 2; i++) {
        if(current == NULL) return NULL;
        current = current -> next
    }
    return current;
}


void segundo_siguiente_(nodo_t* actual, List_t* lista) {
    if(nodo == NULL) return;
    segundo_siguiente_(actual->left);
    insert(lista, actual);
    segundo_siguiente_(actual->right);
}