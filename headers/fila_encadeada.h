void set_to_inicial_position(Fila **arr){
    if(*arr != NULL){
        if((*arr)->anterior != NULL) *arr = (*arr)->anterior;
    }
}

void inclui_fila(Fila **a, Cliente x){

    if(*a == NULL){
        printf("CRIA\n");
        Fila *aux = (Fila *)malloc(sizeof(Fila));
        aux->cliente = x;
        aux->anterior = NULL;
        aux->proximo = NULL;
        *a = aux;
        return;
    }
    if((*a)->proximo != NULL) inclui_fila(&(*a)->proximo, x);
    else{
        printf("INSERE\n");
        Fila *aux = (Fila *)malloc(sizeof(Fila));
        aux->cliente = x;
        aux->proximo = NULL;
        aux->anterior = *a;
        (*a)->proximo = aux;
        return;
    }
}

void print_FDE(Fila **arr, int counter){

    printf("ITERATION: %d\nID: %d\n", counter, (*arr)->cliente.id);
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