typedef struct cliente{

    int id;
    int arrival_time;
    char *sequence;

}Cliente;

typedef struct posto{

    int time_to_attend;
    int qtd_postos;
    int qtd_atendentes;
    char *flag;

}Posto;

typedef struct config{

    int qtd_atendentes;
    int time_to_change;
    Posto A;
    Posto B;
    Posto C;
    Posto D;
    Posto E;

}Config;