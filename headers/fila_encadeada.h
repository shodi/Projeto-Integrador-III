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

Fila* remove_element(Fila *arr){
    if(arr->proximo == NULL){
        printf("ULTIMO ELEMENTO REMOVIDO DA FILA %d\n\n", arr->cliente.id);
        return NULL;
    }
    else{
        Fila *aux = (Fila *)malloc(sizeof(Fila));
        aux = arr->proximo;
        free(arr);
        return aux;
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

void print_client(Cliente x){

    printf("ID: %d\n", x.id);
    printf("DURATION: %d\n", x.duration);
    printf("TIME CURRENT STEP: %d\n", x.arrival_time_current_step);
    printf("SPENT_TIME: %d\n", x.spent_time);
    printf("IN PROCESS: ");
    x.in_process ? printf("TRUE\n") : printf("FALSE\n");
    printf("IS ATTENDING: ");
    x.is_attending ? printf("TRUE\n") : printf("FALSE\n");
    printf("CURRENT STEP: %c\n", x.current_step);
    printf("\n\n\n\n"); 

}

void insert_element_by_key(ARR_FILAS **arr, Fila **finalizado, const char key, Cliente x, int current_time){
    if((key == '\0' || key == '\n' || key == ' ')){
        goto fi;
    }
    if(*arr != NULL){
        if((*arr)->posto == key){
            Cliente aux = x;
            aux.duration = (*arr)->time_to_attend;
            aux.current_step = key;
            aux.arrival_time_current_step = current_time;
            inclui_fila(&(*arr)->current_posto, aux);
        }else{
            insert_element_by_key(&(*arr)->proximo, finalizado, key, x, current_time);
        }
    }
    if(*arr == NULL){
      fi:
        printf("FINALIZA ATENDIMENTO DO CLIENTE %d No step %c\n\n", x.id, x.current_step);
        inclui_fila(finalizado, x);
    }
}


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

int time_sum(Fila **arr, int current_time, int total_time){
    if(*arr != NULL){
        print_client((*arr)->cliente);
        int diff = current_time - (*arr)->cliente.arrival_time_current_step;
        total_time += diff;
        time_sum(&(*arr)->proximo, current_time, total_time);
    }
    return total_time;
}

void setting_avg_time(ARR_FILAS **arr, int current_time){
    if(*arr != NULL){
        printf("Fila: %c\n", (*arr)->posto);
        printf("Tempo de atendimento: %d\n", time_sum(&(*arr)->current_posto, current_time, 0));
        setting_avg_time(&(*arr)->proximo, current_time);
    }
}

int is_empty_queue(Fila **arr, int qtd_atendentes, int working_attendants){
    if(*arr != NULL){
        if((*arr)->cliente.is_attending) is_empty_queue(&(*arr)->proximo, qtd_atendentes, ++working_attendants);
        else is_empty_queue(&(*arr)->proximo, qtd_atendentes, ++working_attendants);
    }
    return working_attendants;
}

void search_for_empty_queue(ARR_FILAS **arr){
    if(*arr != NULL){
        printf("FILA: %c\n", (*arr)->posto);
        printf("QTD DE ATENDENTES LIVRES: %d\n", (*arr)->qtd_attendent - is_empty_queue(&(*arr)->current_posto, (*arr)->qtd_attendent, 0));
        search_for_empty_queue(&(*arr)->proximo);
    }
}