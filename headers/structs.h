typedef struct cliente{

    int id;
    int duration;
    int spent_time;
    bool in_process;
    bool is_attending;
    int arrival_time;
    int arrival_time_current_step;
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

}Config;

typedef struct fila{

    struct fila *proximo;
    Cliente cliente;

}Fila;

typedef struct fila_de_filas{

    struct fila_de_filas *proximo;
    Fila *current_posto;
    char posto;
    char *label;
    double avg_time;
    int qtd_postos;
    int qtd_attendent;
    int time_to_attend;

}ARR_FILAS;

typedef struct grupo_de_informacoes{
    struct grupo_de_informacoes *anterior;
    struct grupo_de_informacoes *proximo;
    const char *sequence;
    int qtd_clientes;
    double avg_time;
    int total_time;
}Group_info;

typedef struct relatorio{

    Group_info *route_avg_time;
    double avg_time;
    double (*get_general_average_time) (struct relatorio*, Fila *);
    void (*get_group_avg_time) (struct relatorio *, Fila *);

}Relatorio;