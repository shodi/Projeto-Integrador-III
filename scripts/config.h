#include <stdlib.h>
#include <string.h>
#include "../headers/structs.h"
#include "../headers/fila_encadeada.h"
#define SETUP_QTD_LINE 8

Config *SETUP = NULL;
ARR_FILAS *ARRAY_CLIENTES = NULL;

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
    size_t i;
    for ( i = start; str[i] != '\n' ; ++i ) {
        buffer[j++] = str[i];
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
        if((*arr)->posto == str[0]) (*arr)->time_to_attend = atoi(slice_str_with_end(str, 1, find_marker(str)));
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


void set_attending(Fila **arr, int qtd_atendentes){
    if(*arr != NULL){
        if(qtd_atendentes > 0){
            if((*arr)->cliente.is_attending != true){
                (*arr)->cliente.is_attending = true;
            }
            set_attending(&(*arr)->proximo, qtd_atendentes - 1);
        }
    }
}

void set_all_queues_attending(ARR_FILAS **arr){

    if(*arr != NULL){
        set_attending(&(*arr)->current_posto, (*arr)->time_to_attend);
        set_all_queues_attending(&(*arr)->proximo);
    }

}

void update_subqueue_values(ARR_FILAS **super, Fila **arr){
    if(*arr != NULL){
        (*arr)->cliente.spent_time++;
        if((*arr)->cliente.is_attending) (*arr)->cliente.duration --;
        if((*arr)->cliente.duration == 0){
            printf("\n\n\nPLAU PLAU PLAU\n\n\n");
            char _next = next_step((*arr)->cliente.sequence, (*arr)->cliente.current_step);
            (*arr)->cliente.is_attending = false;
            insert_element_by_key(super, _next, (*arr)->cliente);
            remove_element(*arr);
            // set_to_inicial_position(arr);
            print_fila(arr);    
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

Fila *get_client(const char *file_name, int value){

    Fila *fila_de_clientes = NULL;
    Cliente *aux = (Cliente *)malloc(sizeof(Cliente));

    FILE *fp;
    char *line;
    size_t len = 0;
    int first_step;

    fp = fopen(file_name, "r");
    if(fp == NULL) printf("SOMETHING WENT WRONG WHILE OPENING THE ARCHIVE THAT LOADS THE CLIENT\n");

    while(getline(&line, &len, fp) != EOF){
        if(set_arrival_time(line, &first_step) != value) continue;
        aux->is_attending = false;
        aux->in_process = true;
        aux->duration = -1;
        aux->spent_time = 0;
        aux->id = atoi(slice_str_with_end(line, 1, find_arrival_position(line)));
        aux->arrival_time = set_arrival_time(line, &first_step);
        aux->sequence = slice_str_with_end(line, first_step, strlen(line));
        aux->current_step = aux->sequence[0];
        inclui_fila(&fila_de_clientes, *aux);
    }

    fclose(fp);
    if(line) free(line);
    return fila_de_clientes;
}