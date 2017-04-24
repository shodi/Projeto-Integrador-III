void inclui_fila(Fila **a, Cliente x){

    if(*a == NULL){
        Fila *aux = (Fila *)malloc(sizeof(Fila));
        aux->cliente = x;
        aux->proximo = NULL;
        *a = aux;
        return;
    }
    else if((*a)->proximo != NULL) inclui_fila(&(*a)->proximo, x);
    else if((*a)->proximo == NULL){
        Fila *aux = (Fila *)malloc(sizeof(Fila));
        aux->cliente = x;
        aux->proximo = NULL;
        (*a)->proximo = aux;
        return;
    }
}

void print_FDE(Fila **arr, int counter){
    if((*arr)->proximo != NULL) print_FDE(&(*arr)->proximo, counter + 1);
}

void init_filas(ARR_FILAS **arr, char key){
    
    if(*arr != NULL && (*arr)->posto != key) init_filas(&(*arr)->proximo, key);
    if(*arr != NULL && (*arr)->posto == key){
        (*arr)->qtd_postos++;
        return;
    } 
    if(*arr == NULL){
        ARR_FILAS *aux = (ARR_FILAS *)malloc(sizeof(ARR_FILAS));
        aux->proximo = NULL;
        aux->current_posto = NULL;
        aux->posto = key;
        aux->qtd_postos = 1;
        aux->qtd_attendent = 0;
        *arr = aux;
    }

}

int remove_element(Fila *arr){
    if(arr == NULL) return 0;    
    else{
        arr = arr->proximo;
        return 1;
    }
}

void init_attendig(ARR_FILAS **arr, char key){

    if(*arr != NULL && (*arr)->posto != key) init_attendig(&(*arr)->proximo, key);
    if(*arr != NULL && (*arr)->posto == key){
        (*arr)->qtd_attendent++;
        return;
    }
    if(*arr == NULL) printf("FILA NAO ENCONTRADA\n");

}

void insert_element_by_key(ARR_FILAS **arr, Fila **finalizado, const char key, Cliente x){
    if(*arr != NULL){
        if((*arr)->posto == key){
            Cliente aux = x;
            aux.duration = (*arr)->time_to_attend;
            aux.current_step = key;
            inclui_fila(&(*arr)->current_posto, aux);
        }else{
            insert_element_by_key(&(*arr)->proximo, finalizado, key, x);
        }
    }
    if(*arr == NULL){
        printf("REMOVE CLIENTE ID: %d\n", x.id);
        inclui_fila(finalizado, x);
    }
} // fazer isso retornar algo pra funcao principal para poder transferir o cliente pra fila de finalizados


void print_fila(Fila **a){
    
    if(*a != NULL){
        printf("VETOR %c\n", (*a)->cliente.current_step);
        printf("ID >>> %d\n", (*a)->cliente.id);
        printf("IS_ATTENDING >>> %d\n", (*a)->cliente.is_attending);
        printf("DURATION >>> %d\n", (*a)->cliente.duration);
        printf("SEQUENCE >>> %s\n", (*a)->cliente.sequence);
        printf("ARRIVAL TIME >>> %d\n", (*a)->cliente.arrival_time);
        printf("CURRENT_STEP >>> %c\n", (*a)->cliente.current_step);
        printf("SPENT TIME >>> %d\n", (*a)->cliente.spent_time);
        print_fila(&(*a)->proximo);
    }

}

void print_super_fila(ARR_FILAS **arr){

    if(*arr != NULL){
        printf("CURRENT FILA %c\n", (*arr)->posto);
        printf("QTD_POSTOS: %d\n", (*arr)->qtd_postos);
        printf("QTD_ATENDENTES: %d\n", (*arr)->qtd_attendent);
        printf("TIME TO ATTEND: %d\n\n\n\n\n", (*arr)->time_to_attend);
        print_fila(&(*arr)->current_posto);
        printf("\n\n\n\n");
        print_super_fila(&(*arr)->proximo);
    }

}