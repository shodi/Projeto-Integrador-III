double get_avg_time(Relatorio *self, Fila *arr){
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

    self->avg_time = (double) total_time / (double) total_clients;
    return self->avg_time;
}

Relatorio* new_report(){
    Relatorio *report = (Relatorio *)malloc(sizeof(Relatorio));
    report->get_average_time = &get_avg_time;
    return report;
}

void generate_report(){
    Relatorio *report = new_report();

    report->get_average_time(report, CLIENTES_FIN);
    printf("TEMPO MEDIO DE ATENDIMENTO: %.2lf\n", report->avg_time);
    free(report);
    
}