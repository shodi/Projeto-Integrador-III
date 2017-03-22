void inclui_fila(Fila **a, Cliente x){

    if(*a != NULL) inclui_fila(&(*a)->proximo, x);
    else{
        Fila *aux = (Fila *)malloc(sizeof(Fila));
        aux->cliente = x;
        aux->proximo = NULL;
        *a = aux;
    }
}

void print_fila(Fila **a, char flag){

    if(*a != NULL){
        printf("VETOR %c\n", flag);
        printf("ID >>> %d\n", (*a)->cliente.id);
        printf("ARRIVAL TIME >>> %d\n", (*a)->cliente.arrival_time);
        printf("CURRENT_STEP >>> %c\n", (*a)->cliente.current_step);    
        print_fila(&(*a)->proximo, flag);
    }

}