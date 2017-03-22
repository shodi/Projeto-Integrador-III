typedef struct cliente{

    int id;
    bool is_attending;
    int arrival_time;
    char *sequence;
    char current_step;

}Cliente;

typedef struct posto{

    int time_to_attend;
    int qtd_postos;
    int attending_client_id;
    int qtd_atendentes;
    char *flag;

}Posto;

typedef struct config{

    int qtd_atendentes;
    int time_to_change;
    Posto *A;
    Posto *B;
    Posto *C;
    Posto *D;
    Posto *E;

}Config;

typedef struct fila{

    struct fila *proximo;
    Cliente cliente;

}Fila;