#include <stdlib.h>
#include <string.h>
#include "../headers/structs.h"
#include "../headers/fila_encadeada.h"
#define SETUP_QTD_LINE 8

Config *SETUP = NULL;

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

void _relacao_de_postos(char *str, Config *params){
    int i;
    for(i = 0; str[i] != '\0'; i++){
        switch(str[i]){
            case 'A':
                !params->A.qtd_postos ? params->A.qtd_postos = 1 : params->A.qtd_postos++;
                break;
            case 'B':
                !params->B.qtd_postos ? params->B.qtd_postos = 1 : params->B.qtd_postos++;
                break;
            case 'C':
                !params->C.qtd_postos ? params->C.qtd_postos = 1 : params->C.qtd_postos++;
                break;
            case 'D':
                !params->D.qtd_postos ? params->D.qtd_postos = 1 : params->D.qtd_postos++;
                break;
            default:
                !params->E.qtd_postos ? params->E.qtd_postos = 1 : params->E.qtd_postos++;
                break;
        }
    }
}

void _relacao_de_atendimento(char *str, Config *params){
    int i;
    for(i = 0; str[i] != '\0'; i++){
        switch(str[i]){
            case 'A':
                !params->A.qtd_atendentes ? params->A.qtd_atendentes = 1 : params->A.qtd_atendentes++;
                break;
            case 'B':
                !params->B.qtd_atendentes ? params->B.qtd_atendentes = 1 : params->B.qtd_atendentes++;
                break;
            case 'C':
                !params->C.qtd_atendentes ? params->C.qtd_atendentes = 1 : params->C.qtd_atendentes++;
                break;
            case 'D':
                !params->D.qtd_atendentes ? params->D.qtd_atendentes = 1 : params->D.qtd_atendentes++;
                break;
            default:
                !params->E.qtd_atendentes ? params->E.qtd_atendentes = 1 : params->E.qtd_atendentes++;
                break;
        }
    }
}

void _posto_setup(char *str, Config *params){
    switch(str[0]){
            case 'A':
                params->A.time_to_attend = str[1] - '0';
                params->A.flag = slice_str(str, 3);
                break;
            case 'B':
                params->B.time_to_attend = str[1] - '0';
                params->B.flag = slice_str(str, 3);
                break;
            case 'C':
                params->C.time_to_attend = str[1] - '0';
                params->C.flag = slice_str(str, 3);
                break;
            case 'D':
                params->D.time_to_attend = str[1] - '0';
                params->D.flag = slice_str(str, 3);
                break;
            default:
                params->E.time_to_attend = str[1] - '0';
                params->E.flag = slice_str(str, 3);
                break;
    }
}

Config* get_config(const char *file_name){

    FILE *fp;
    char *line;
    size_t len = 0;
    Config *setup = (Config *)malloc(sizeof(Config));
    int i;
    fp = fopen(file_name, "r");
    if(fp == NULL) printf("SOMETHING WENT WRONG WHILE OPENING THE ARCHIVE THAT LOADS THE CONFIG\n");    

    for(i = 0; i < SETUP_QTD_LINE; i++){
        getline(&line, &len, fp);
        switch(i){
            case 0:
                setup->qtd_atendentes = atoi(line);
                break;
            case 1:
                _relacao_de_postos(slice_str(line, 3), setup);
                break;
            case 2:
                _relacao_de_atendimento(slice_str(line, 3), setup);
                break;
            case 3:
                setup->time_to_change = atoi(slice_str(line, 6));
                break;
            default:
                _posto_setup(line, setup);
                break;          
        }
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

    while(getline(&line, &len, fp) != EOF && set_arrival_time(line, &first_step) >= value){
        if(set_arrival_time(line, &first_step) != value) continue;
        aux->id = atoi(slice_str_with_end(line, 1, find_arrival_position(line)));
        aux->arrival_time = set_arrival_time(line, &first_step);
        aux->sequence = slice_str_with_end(line, first_step, strlen(line));
        inclui_fila(&fila_de_clientes, *aux);
    }

    fclose(fp);
    if(line) free(line);
    return fila_de_clientes;
}