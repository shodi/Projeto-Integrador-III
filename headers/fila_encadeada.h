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


int total_postos(ARR_FILAS **arr, int counter){

    if((*arr) != NULL){
        counter = total_postos(&(*arr)->proximo, counter + (*arr)->qtd_postos);
    }
    
    return counter;
    

}

int variedade_postos(ARR_FILAS **arr, int counter, char postoB){

    if((*arr) != NULL){

        printf("%c\n", postoB);
        if (postoB != (*arr)->posto){

            counter = variedade_postos(&(*arr)->proximo, counter + (*arr)->qtd_postos, (*arr)->posto);
            
        }
    }
    
    return counter;
    

}