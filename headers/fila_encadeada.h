void inclui_fila(Fila **a, Cliente x){

    if(*a != NULL) inclui_fila(&(*a)->proximo, x);
    else{
        Fila *aux = (Fila *)malloc(sizeof(Fila));
        aux->cliente = x;
        aux->proximo = NULL;
        *a = aux;
    }
}