void __make_header(FILE *report){
    fprintf(report, 
        "<!DOCTYPE html>"\
        "<html lang=\"en\">"\
        "<head>"\
            "<title>Relatório</title>"\
            "<meta charset=\"utf-8\">"\
            "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"\
            "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css\">"\
            "<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js\"></script>"\
            "<script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js\"></script>"\
        "</head>"\
        "<body>"\
            "<div class=\"container\">"\
                "<h2>Relatório da ultima execução</h2>"\
                "<table class=\"table table-striped table-hover table-bordered\">"\
                    "<thead>"\
                        "<tr>"\
                            "<th>Grupo</th>"\
                            "<th>Quantidade de clientes</th>"\
                            "<th>Tempo total</th>"\
                            "<th>Tempo médio</th>"\
                        "</tr>"\
                    "</thead>"\
                    "<tbody>"\
                    );

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
    fprintf(fp, \
                    "<tr>" \
                        "<td colspan=\"3\"><b>TEMPO MEDIO DE ATENDIMENTO:</b></td>" \
                        "<td>%.2lf</td>" \
                    "</tr>" \
                "<tbody>" \
            "</table>" \
            "<h3><b>Tempo total de atendimento</b>: %d %s</h3>"
        "</div>" \
    "</body>" \
"</html>", report->avg_time, TURNO, TURNO > 1 ? "turnos" : "turno");
    fclose(fp);
    free(report);
    
}