void __make_header(FILE *report){
    fprintf(report, "<!DOCTYPE html>");
    fprintf(report, "<html lang=");
    fprintf(report, "%c",  34);
    fprintf(report, "en");
    fprintf(report, "%c",  34);
    fprintf(report, "><head><title>Relatório</title><meta charset=");
    fprintf(report, "%c",  34);
    fprintf(report, "utf-8");
    fprintf(report, "%c",  34);
    fprintf(report, "><meta name=");
    fprintf(report, "%c",  34);
    fprintf(report, "viewport");
    fprintf(report, "%c",  34);
    fprintf(report, " content=");
    fprintf(report, "%c",  34);
    fprintf(report, "width=device-width, initial-scale=1");
    fprintf(report, "%c",  34);
    fprintf(report, "><link rel=");
    fprintf(report, "%c",  34);
    fprintf(report, "stylesheet");
    fprintf(report, "%c",  34);
    fprintf(report, " href=");
    fprintf(report, "%c",  34);
    fprintf(report, "https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css");
    fprintf(report, "%c",  34);
    fprintf(report, "><script src=");
    fprintf(report, "%c",  34);
    fprintf(report, "https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js");
    fprintf(report, "%c",  34);
    fprintf(report, "></script><script src=");
    fprintf(report, "%c",  34);
    fprintf(report, "https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js");
    fprintf(report, "%c",  34);
    fprintf(report, "></script></head><body><div class=");
    fprintf(report, "%c",  34);
    fprintf(report, "container");
    fprintf(report, "%c",  34);
    fprintf(report, "><h2>Relatório da ultima execução</h2><table class=");
    fprintf(report, "%c",  34);
    fprintf(report, "table table-striped table-bordered");
    fprintf(report, "%c",  34);
    fprintf(report, "><thead><tr><th>Grupo</th><th>Quantidade de clientes</th><th>Tempo total</th><th>Tempo médio</th></tr></thead>");
    fprintf(report, "<tbody>");

}

void __print_group_info__(Group_info **arr, FILE *report, int counter){
    if((*arr)->anterior != NULL && !counter) __print_group_info__(&(*arr)->anterior, report, counter);
    else if(*arr != NULL){
        fprintf(report, "<tr>");
        fprintf(report, "<td><b>%s</b></td>", (*arr)->sequence);
        fprintf(report, "<td>%d</td>", (*arr)->qtd_clientes);
        fprintf(report, "<td>%d</td>", (*arr)->total_time);
        fprintf(report, "<td>%.2lf</td>", (*arr)->avg_time);
        fprintf(report, "</tr>");
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

void __get_group_avg_time(Relatorio *self, Fila *arr){

    Fila *aux = arr;
con:if(aux != NULL){
        insert_to_group(&(self->route_avg_time), aux->cliente);
    loop:if(self->route_avg_time->anterior != NULL) {self->route_avg_time = self->route_avg_time->anterior;goto loop;}
        aux = aux->proximo;
        goto con;
    }
    arr = aux;
    FILE *report = fopen("/tmp/report.html", "w+");
    __make_header(report);
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
    FILE *fp = fopen("/tmp/report.html", "a");
    fprintf(fp, "<tr><td colspan=");
    fprintf(fp, "%c",  34);
    fprintf(fp, "%c", 51);
    fprintf(fp, "%c",  34);
    fprintf(fp, "><b>TEMPO MEDIO DE ATENDIMENTO:</b></td><td>%.2lf</td>", report->avg_time);
    fprintf(fp, "</tbody></table></div></body></html>");
    fclose(fp);
    free(report);
    
}