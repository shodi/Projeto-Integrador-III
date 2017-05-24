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
    printf("SPENT_TIME: %d\n", x.spent_time);
    printf("IN PROCESS: ");
    x.in_process ? printf("TRUE\n") : printf("FALSE\n");
    printf("IS ATTENDING: ");
    x.is_attending ? printf("TRUE\n") : printf("FALSE\n");
    printf("CURRENT STEP: %c\n", x.current_step);
    printf("\n\n\n\n"); 

}

void insert_element_by_key(ARR_FILAS **arr, Fila **finalizado, const char key, Cliente x){
    if((key == '\0' || key == '\n' || key == ' ')){
        goto fi;
    }
    if(*arr != NULL){
        if((*arr)->posto == key){
            (*arr)->qtd_pessoas ++;
            Cliente aux = x;
            aux.duration = (*arr)->time_to_attend;
            aux.current_step = key;
            inclui_fila(&(*arr)->current_posto, aux);
        }else{
            insert_element_by_key(&(*arr)->proximo, finalizado, key, x);
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

int total_postos(ARR_FILAS **arr, int counter){

    if((*arr) != NULL){
        counter = total_postos(&(*arr)->proximo, counter + (*arr)->qtd_postos);
    }
    
    return counter;
    

}

int variedade_postos(ARR_FILAS **arr, int counter, char postoB){

    if((*arr) != NULL){

        if (postoB != (*arr)->posto){

            counter = variedade_postos(&(*arr)->proximo, counter + 1, (*arr)->posto);
            
        }
    }
    
    return counter;
    
} 

int verifica_atendente(Fila **a){

    int is_atend;
    
    if(*a != NULL){
        is_atend = ((*a)->cliente.is_attending);
        return is_atend;
    } 
    else return 0;

}

void detalhe_guiche(ARR_FILAS **arr, char **nome, int *is_atend, int *qtdPostosV, int *qtdAtendsV, int *qtsPessoas){

    if(*arr != NULL){
        *nome = ((*arr)->label);
        *is_atend = verifica_atendente(&(*arr)->current_posto);
        *qtdPostosV = ((*arr)->qtd_postos);
        *qtdAtendsV = ((*arr)->qtd_attendent);
        *qtsPessoas = ((*arr)->qtd_pessoas);
    }

}

//void detalhe_guiche(ARR_FILAS **arr, char **nome, int *qtd_postos, int *qtd_attendent, int *is_atend){

//    if(*arr != NULL){
//        *qtd_postos = ((*arr)->qtd_postos);
//        *qtd_attendent = ((*arr)->qtd_attendent);
//        *nome = ((*arr)->label);
//        *is_atend = verifica_atendente(&(*arr)->current_posto);
//   }

//}
