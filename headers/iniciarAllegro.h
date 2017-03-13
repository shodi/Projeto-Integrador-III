ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
ALLEGRO_BITMAP *botao_sair = NULL, *area_central = 0;
ALLEGRO_TIMER *timer;

// Tela
const int LARGURA_TELA = 640;
const int ALTURA_TELA = 480;

int velocidadeturno = 1;

int iniciarAllegro(){
    if (!al_init())
    {
        fprintf(stderr, "Falha ao inicializar a Allegro.\n");
        return -1;
    }

    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!janela)
    {
        fprintf(stderr, "Falha ao criar janela.\n");
        return -1;
    }

    timer = al_create_timer(1.0/60*velocidadeturno);
    if(!timer){
        fprintf(stderr, "Falha ao inicializar o Timer\n");
        return -1;
    }
    // Torna apto o uso de mouse na aplicação
    if (!al_install_mouse())
    {
        fprintf(stderr, "Falha ao inicializar o mouse.\n");
        al_destroy_display(janela);
        return -1;
    }
 
    // Atribui o cursor padrão do sistema para ser usado
    if (!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT))
    {
        fprintf(stderr, "Falha ao atribuir ponteiro do mouse.\n");
        al_destroy_display(janela);
        return -1;
    }
 
    // Alocamos o retângulo central da tela
    area_central = al_create_bitmap(LARGURA_TELA / 2, ALTURA_TELA / 2);
    if (!area_central)
    {
        fprintf(stderr, "Falha ao criar bitmap.\n");
        al_destroy_display(janela);
        return -1;
    }
 
    // Alocamos o botão para fechar a aplicação
    botao_sair = al_create_bitmap(100, 50);
    if (!botao_sair)
    {
        fprintf(stderr, "Falha ao criar botão de saída.\n");
        al_destroy_bitmap(area_central);
        al_destroy_display(janela);
        return -1;
    }
 
    fila_eventos = al_create_event_queue();
    if (!fila_eventos)
    {
        fprintf(stderr, "Falha ao inicializar o fila de eventos.\n");
        al_destroy_display(janela);
        return -1;
    }

    // Configura o título da janela
    al_set_window_title(janela, "BBC PI 3 - Sistema Autônomo");

     // Dizemos que vamos tratar os eventos vindos do mouse
    al_register_event_source(fila_eventos, al_get_mouse_event_source());

    return 1;
}

void destruirTudo(){
    // Desaloca os recursos utilizados na aplicação
    al_destroy_bitmap(botao_sair);
    al_destroy_bitmap(area_central);
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);
    al_destroy_timer(timer);
}