void inclui_fila(Fila **a, Cliente x){

    if(*a != NULL) inclui_fila(&(*a)->proximo, x);
    Fila *aux = (Fila *)malloc(sizeof(Fila));
    aux->cliente = x;
    aux->proximo = NULL;
    *a = aux;
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


void init_attendig(ARR_FILAS **arr, char key){

    if(*arr != NULL && (*arr)->posto != key) init_attendig(&(*arr)->proximo, key);
    if(*arr != NULL && (*arr)->posto == key){
        (*arr)->qtd_attendent++;
        return;
    }
    if(*arr == NULL) printf("FILA NAO ENCONTRADA\n");

}

void insert_element_by_key(ARR_FILAS **arr, const char key, Cliente x){

    if(*arr != NULL){
        if((*arr)->posto == key){
            inclui_fila(&(*arr)->current_posto, x);
        }else{
            insert_element_by_key(&(*arr)->proximo, key, x);
        }
    }
    if(*arr == NULL) printf("ERRO AO BUSCAR FILA COM A KEY: %c\n", key);
    
}


void print_fila(Fila **a){

    if(*a != NULL){
        printf("VETOR %c\n", (*a)->cliente.current_step);
        printf("ID >>> %d\n", (*a)->cliente.id);
        printf("SEQUENCE >>> %s\n", (*a)->cliente.sequence);
        printf("ARRIVAL TIME >>> %d\n", (*a)->cliente.arrival_time);
        printf("CURRENT_STEP >>> %c\n", (*a)->cliente.current_step);
        print_fila(&(*a)->proximo);
    }

}

void print_super_fila(ARR_FILAS **arr){

    if(*arr != NULL){
        print_fila(&(*arr)->current_posto);
        print_super_fila(&(*arr)->proximo);
    }

}