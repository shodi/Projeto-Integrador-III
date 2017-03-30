typedef struct cliente{

    int id;
    int duration;
    int spent_time;
    bool in_process;
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
    char *relation;
    char *attending;
    // Posto *A;
    // Posto *B;
    // Posto *C;
    // Posto *D;
    // Posto *E;

}Config;

typedef struct fila{

    struct fila *proximo;
    struct fila *anterior;
    Cliente cliente;

}Fila;

typedef struct fila_de_filas{

    struct fila_de_filas *proximo;
    Fila *current_posto;
    char posto;
    char *label;
    int qtd_postos;
    int qtd_attendent;
    int time_to_attend;

}ARR_FILAS;