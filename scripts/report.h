void __print_group_info__(Group_info **arr, FILE *report, int counter){
    if((*arr)->anterior != NULL && !counter) __print_group_info__(&(*arr)->anterior, report, counter);
    else if(*arr != NULL){
        fprintf(report, "SEQUENCE: %s", (*arr)->sequence);
        fprintf(report, "TOTAL_TIME: %d\n", (*arr)->total_time);
        fprintf(report, "QTD CLIENTES: %d\n", (*arr)->qtd_clientes);
        fprintf(report, "AVG_TIME: %.2lf\n\n", (*arr)->avg_time);
        if((*arr)->proximo != NULL) __print_group_info__(&(*arr)->proximo, report, ++counter);
    }
    return;
}

void insert_to_group(Group_info **init_info, Cliente client){
    if(*init_info == NULL){
        Group_info *aux = (Group_info *)malloc(sizeof(Group_info));
        aux->proximo = NULL;
        aux->anterior = NULL;
        aux->sequence = client.sequence;
        aux->qtd_clientes = 1;
        aux->total_time = client.spent_time;
        aux->avg_time = aux->total_time / (double) aux->qtd_clientes;
        *init_info = aux;
        return;
    }
hlp:if(*init_info != NULL){
        if(strcmp((*init_info)->sequence, client.sequence) == 0){
            (*init_info)->qtd_clientes++;
            (*init_info)->total_time += client.spent_time;
            (*init_info)->avg_time = (*init_info)->total_time / (double) (*init_info)->qtd_clientes;
            return;
        }
    }
    if((*init_info)->proximo != NULL){
        if(strcmp((*init_info)->proximo->sequence, client.sequence) == 0){
            (*init_info)->proximo->qtd_clientes++;
            (*init_info)->proximo->total_time += client.spent_time;
            (*init_info)->proximo->avg_time = (*init_info)->proximo->total_time / (double) (*init_info)->proximo->qtd_clientes;
            return;
        }else{
            *init_info = (*init_info)->proximo;
            goto hlp;
        }
    }
    else if((*init_info)->proximo == NULL){
        Group_info *aux = (Group_info *)malloc(sizeof(Group_info));
        aux->proximo = NULL;
        aux->anterior = *init_info;
        aux->sequence = client.sequence;
        aux->qtd_clientes = 1;
        aux->total_time = client.spent_time;
        aux->avg_time = aux->total_time / (double) aux->qtd_clientes;
        (*init_info)->proximo = aux;
        return;
    }
}

double __get_avg_time(Relatorio *self, Fila *arr){
    Fila *aux = arr;
    int total_time = 0;
    int total_clients = 0;
con:if(arr != NULL){
        total_time += arr->cliente.spent_time;
        total_clients++;
        arr = arr->proximo;
        goto con;
    }
    arr = aux;
    self->avg_time = total_time / (double) total_clients;
    return self->avg_time;
}

void __get_group_avg_time(Relatorio *self, Fila *aux){

    // Fila *aux = arr;
con:if(aux != NULL){
        insert_to_group(&(self->route_avg_time), aux->cliente);
        aux = aux->proximo;
        goto con;
    }
    FILE *report = fopen("/tmp/report.txt", "w+");
    __print_group_info__(&(self)->route_avg_time, report, ~EOF);     
    fclose(report);

}

Relatorio* new_report(){
    Relatorio *report = (Relatorio *)malloc(sizeof(Relatorio));
    report->route_avg_time = NULL;
    report->get_general_average_time = &__get_avg_time;
    report->get_group_avg_time = &__get_group_avg_time;
    return report;
}

void generate_report(){
    Relatorio *report = new_report();

    report->get_group_avg_time(report, CLIENTES_FIN);
    report->get_general_average_time(report, CLIENTES_FIN);
    FILE *fp = fopen("/tmp/report.txt", "a");
    fprintf(fp, "TEMPO MEDIO DE ATENDIMENTO: %.2lf\n", report->avg_time);
    fclose(fp);
    free(report);
    
}