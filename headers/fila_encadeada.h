void inclui_fila(Fila **a, Cliente x){

    if(*a != NULL) inclui_fila(&(*a)->proximo, x);
    else{
        Fila *aux = (Fila *)malloc(sizeof(Fila));
        aux->cliente = x;
        aux->proximo = NULL;
        *a = aux;
    }
}

void print_fila(Fila **a){

    if(*a != NULL){
        printf("ID >>> %d\n", (*a)->cliente.id);
        printf("ARRIVAL TIME >>> %d\n\n", (*a)->cliente.arrival_time);
        print_fila(&(*a)->proximo);
    }

}