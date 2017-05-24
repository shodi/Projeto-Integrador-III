#include <stdlib.h>
#include <string.h>
#include "../headers/structs.h"
#include "../headers/fila_encadeada.h"
#define SETUP_QTD_LINE 8

Config *SETUP = NULL;
FILE *CLIENT_FILE;
ARR_FILAS *ARRAY_CLIENTES = NULL;
Fila *CLIENTES_FIN = NULL;
bool FINISHED_READING = false;
int QTD_CLIENTES = 0;
Cliente *AWAITING = NULL;

char *slice_str_with_end(const char * str, size_t start, size_t end){

    const size_t len = strlen(str);
    char *buffer = (char *)malloc(len * sizeof(char));
    size_t j = 0;
    for ( size_t i = start; i <= end; ++i ) {
        buffer[j++] = str[i];
    }
    buffer[j] = 0;

    return buffer;
}

char next_step(const char *sequence, const char current_step){
    int i = 0;
hlp:if(sequence[i] != current_step){
        i++;
        goto hlp;
    }
    return sequence[i + 1];
}

int find_arrival_position(char *str){

    int i = 0;
    s1: if(str[i] != 'C'){
        i++;
        goto s1;
    }
    return i + 1;
}

int set_arrival_time(char *str, int *helper){
    int i = find_arrival_position(str);
    int aux = i;
    s2: if(str[i] != 'A'){
        i++;
        goto s2;
    }
    *helper = i;
    return atoi(slice_str_with_end(str, aux, i + 1));
}   

char* slice_str(const char * str, size_t start){  
    
    const size_t len = strlen(str);
    char *buffer = (char *)malloc(len * sizeof(char));
    size_t j = 0;
    size_t i = start;
hlp:if(str[i] != '\n'){
        buffer[j++] = str[i];
        ++i;
        goto hlp;
    }
    buffer[j] = 0;
    return buffer;
}

size_t find_marker(const char *str){

    int i = 0;
ck: if( str[i] == ':') return i;
    i++;
    goto ck;

}

void set_time_to_attend(ARR_FILAS **arr, const char *str){
    if(*arr != NULL){
        if((*arr)->posto == str[0]){
            (*arr)->time_to_attend = atoi(slice_str_with_end(str, 1, find_marker(str)));
            (*arr)->label = slice_str_with_end(str, find_marker(str) + 1, strlen(str) - 1);
        }
        else set_time_to_attend(&(*arr)->proximo, str);
    }
}

void _posto_setup(char *str){
    set_time_to_attend(&ARRAY_CLIENTES, str);
}

int get_string_length(const char *a){

    int i = 0;
s1: if(a[i] != '\0'){
        i++;
        goto s1;
    }
    return i - 1;
}

void _relacao_de_postos(Config *setup, char *str){

    int i = 0;
    setup->relation = str;
    ARR_FILAS **helper;
hlp:if(setup->relation[i] != '\0'){
        helper = &ARRAY_CLIENTES;
        init_filas(&ARRAY_CLIENTES, setup->relation[i]);
        i++;
        ARRAY_CLIENTES = *helper;
        goto hlp;
    }

}

void _relacao_de_atendimento(Config *setup, char *str){

    int i = 0;
    setup->attending = str;
hlp:if(setup->attending[i] != '\0'){
        init_attendig(&ARRAY_CLIENTES, setup->attending[i]);
        i++;
        goto hlp;
    }
}

bool check_subqueue_status(Fila **arr, int counter){
    if(*arr != NULL){
        if((*arr)->cliente.in_process) check_subqueue_status(&(*arr)->proximo, counter + 1);
        else return false;
    }
    return !counter ? false : true;
}

bool check_queue_status(ARR_FILAS **arr, int counter){
    if(*arr != NULL){
        if(check_subqueue_status(&(*arr)->current_posto, 0)) check_queue_status(&(*arr)->proximo, counter + 1);
        else return false;
    }
    return !counter ? false : true;
}

bool check_if_finished(Fila **arr){
    if(FINISHED_READING){
        Fila *aux = *arr;
        int i = 0;
    hlp:if((aux) != NULL){
            aux = aux->proximo;
            i++;
            goto hlp;
        }
        if(i == 0) return false;
        return i == QTD_CLIENTES ? true : false;
    }
    return false;
}

void set_attending(Fila **arr, int qtd_atendentes){
    if(*arr != NULL){
        if(qtd_atendentes > 0){
            if((*arr)->cliente.duration > 0 ){
                // printf("CLIENT ID: %d\nDURATION: %d\nCURRENT STEP: %c\n", (*arr)->cliente.id, (*arr)->cliente.duration, (*arr)->cliente.current_step);
                (*arr)->cliente.is_attending = true;
                set_attending(&(*arr)->proximo, qtd_atendentes - 1);
            }else{
                set_attending(&(*arr)->proximo, qtd_atendentes);
            }
        }
    }
}

void set_all_queues_attending(ARR_FILAS **arr){

    if(*arr != NULL){
        set_attending(&(*arr)->current_posto, (*arr)->qtd_attendent);
        set_all_queues_attending(&(*arr)->proximo);
    }

}

void update_subqueue_values(ARR_FILAS **super, Fila **arr){
    s1:if(*arr != NULL){
        // if((*arr)->cliente.id == 2)
        //     print_client((*arr)->cliente);
        (*arr)->cliente.spent_time++;
        if((*arr)->cliente.is_attending) (*arr)->cliente.duration--;
        if((*arr)->cliente.duration == 0){
            char _next = next_step((*arr)->cliente.sequence, (*arr)->cliente.current_step);
            (*arr)->cliente.is_attending = false;
            insert_element_by_key(super, &CLIENTES_FIN, _next, (*arr)->cliente);
            (*super)->qtd_pessoas --;
            *arr = remove_element(*arr);
            if(*arr == NULL) goto s1;
        }
        update_subqueue_values(super, &(*arr)->proximo);
    }
    // if(*arr == NULL) return;
}

void update_queues(ARR_FILAS **arr){
    if(*arr != NULL){
        update_subqueue_values(arr, &(*arr)->current_posto);
        update_queues(&(*arr)->proximo);
    }
}

Config* get_config(const char *file_name){

    FILE *fp;
    char *line;
    size_t len = 0;
    Config *setup = (Config *)malloc(sizeof(Config));

    int i = 0;
    fp = fopen(file_name, "r");
    if(fp == NULL) printf("SOMETHING WENT WRONG WHILE OPENING THE ARCHIVE THAT LOADS THE CONFIG\n");    

get:if(getline(&line, &len, fp) != EOF){
        switch(i){
            case 0:
                setup->qtd_atendentes = atoi(line);
                break;
            case 1:
                _relacao_de_postos(setup, slice_str(line, 3));
                break;
            case 2:
                _relacao_de_atendimento(setup, slice_str(line, 3));
                break;
            case 3:
                setup->time_to_change = atoi(slice_str(line, 6));
                break;
            default:
                _posto_setup(line);
                break;          
        }
        i++;
        goto get;
    }

    if(line) free(line);
    fclose(fp); 
    return setup;
}

Fila *get_client(const char *file_name, int current_time){

    Fila *fila_de_clientes = NULL;
    if(AWAITING != NULL){
        if(AWAITING->arrival_time != current_time)
            goto fim;
        else{
            printf("INCLUINDO CLIENTE %d NA FILA\n", AWAITING->id);
            inclui_fila(&fila_de_clientes, *AWAITING);
            QTD_CLIENTES++;
            free(AWAITING);
            AWAITING = NULL;
        }
    } 
     
    if(!FINISHED_READING){
        if(!CLIENT_FILE){
            CLIENT_FILE = fopen(file_name, "r");
            if(!CLIENT_FILE)
                printf("SOMETHING WENT WRONG WHILE OPENING THE ARCHIVE THAT LOADS THE CLIENT\n");
        }
        char *line;
        size_t len = 0;
        int first_step;
        
        aux:if(getline(&line, &len, CLIENT_FILE) == EOF){
            printf("FIM DA LEITURA\n"); 
            FINISHED_READING = true;
            if(line) free(line);
            fclose(CLIENT_FILE);
            goto fim;
        }
        
        AWAITING = (Cliente *)malloc(sizeof(Cliente));
        AWAITING->is_attending = false;
        AWAITING->in_process = true;
        AWAITING->duration = -1;
        AWAITING->spent_time = 0;
        AWAITING->id = atoi(slice_str_with_end(line, 1, find_arrival_position(line)));
        AWAITING->arrival_time = set_arrival_time(line, &first_step);
        AWAITING->sequence = slice_str_with_end(line, first_step, strlen(line));
        AWAITING->current_step = AWAITING->sequence[0];
        if(AWAITING->arrival_time == current_time){
            printf("INCLUINDO CLIENTE %d NA FILA\n", AWAITING->id);
            inclui_fila(&fila_de_clientes, *AWAITING);
            QTD_CLIENTES++;
            free(AWAITING);
            AWAITING = NULL;
            goto aux;
        }
        
        
    }
    fim:return fila_de_clientes;
}