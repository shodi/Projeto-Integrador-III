ALLEGRO_DISPLAY *JANELA = NULL;
ALLEGRO_EVENT_QUEUE *FILA_EVENTOS = NULL;
ALLEGRO_BITMAP *BOTAO_SAIR = NULL, 
               *AREA_CENTRAL = 0,  
               *BACKGROUND = NULL, 
               *GUICHE1 = NULL,
               *GUICHE2 = NULL,
               *GUICHE3 = NULL,
               *GUICHE4 = NULL,
               *GUICHE5 = NULL,
               *GUICHE6 = NULL,
               *GUICHE7 = NULL,
               *GUICHE8 = NULL,
               *PAUSEBTTN = NULL,
               *PLAYBTTN = NULL,
               *TWOTIMESBTTN = NULL,
               *THREETIMESBTTN = NULL;

ALLEGRO_TIMER *TIMER = 0;
ALLEGRO_FONT *FONT  = NULL,
             *FONT2 = NULL;

const int LARGURA_TELA = 1024;
const int ALTURA_TELA = 720;
const int tamanho = 300;

int VELOCIDADETURNO = 1;

bool iniciarAllegro(){
    if (!al_init()){
        fprintf(stderr, "Falha ao inicializar a Allegro.\n");
        return false;
    }

    if (!al_init_primitives_addon()) {
        fprintf(stderr,"Failed ao iniciar o allegro primitives.");
        return false;
    }
    // É uma função void, não tem como checar seu retorno
    al_init_font_addon();   

    if (!al_init_ttf_addon()) {
        fprintf(stderr,"Falha ao carregar o Addon de TFF.");
        return false;
    }

    if (!al_install_keyboard()) {
        fprintf(stderr,"Falha ao instalar o teclado");
        return false;
    }
    
    if (!al_init_image_addon()) {
        fprintf(stderr,"Falha ao iniciar o addon de imagens.");
        return false;
    }

    if (!al_install_mouse()){
        fprintf(stderr, "Falha ao inicializar o mouse.\n");
        return false;
    }

    // Criações p/ se usar durante a aplicação

    JANELA = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!JANELA){
        fprintf(stderr, "Falha ao criar JANELA.\n");
        return false;
    }

    TIMER = al_create_timer(1.0);
    if (!TIMER){
        fprintf(stderr, "Falha ao inicializar o Timer\n");
        return false;
    }

    if (!al_set_system_mouse_cursor(JANELA, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT)){
        fprintf(stderr, "Falha ao atribuir ponteiro do mouse.\n");
        return false;
    }

    AREA_CENTRAL = al_create_bitmap(LARGURA_TELA / 2, ALTURA_TELA / 2);
    if (!AREA_CENTRAL){
        fprintf(stderr, "Falha ao criar bitmap da area central.\n");
        return false;
    }
    
    BACKGROUND = al_create_bitmap(LARGURA_TELA,ALTURA_TELA);
    if(!BACKGROUND){
        fprintf(stderr, "Falha ao criar bitmap BACKGROUND\n");
        return false;
    }

    GUICHE1 = al_load_bitmap("headers/Images/guiche.png");
    GUICHE2 = al_load_bitmap("headers/Images/guiche.png");
    GUICHE3 = al_load_bitmap("headers/Images/guiche.png");
    GUICHE4 = al_load_bitmap("headers/Images/guiche.png");
    GUICHE5 = al_load_bitmap("headers/Images/guiche.png");
    GUICHE6 = al_load_bitmap("headers/Images/guiche.png");
    GUICHE7 = al_load_bitmap("headers/Images/guiche.png");
    GUICHE8 = al_load_bitmap("headers/Images/guiche.png");
    if (!GUICHE1 || !GUICHE2 || !GUICHE3 ||!GUICHE4 ||!GUICHE5 ||!GUICHE6 ||!GUICHE7 ||!GUICHE8){
        fprintf(stderr, "Falha ao criar bitmap GUICHE. \n");
        return false;
    }

    PAUSEBTTN = al_load_bitmap("headers/Images/pausebttn.png");
    PLAYBTTN = al_load_bitmap("headers/Images/playbttn.png");
    TWOTIMESBTTN = al_load_bitmap("headers/Images/2timesbttn.png");
    THREETIMESBTTN = al_load_bitmap("headers/Images/3timesbttn.png");
    if (!PAUSEBTTN || !PLAYBTTN || !TWOTIMESBTTN ||!THREETIMESBTTN){
        fprintf(stderr, "Falha ao criar bitmap BTTN. \n");
        return false;
    }

    BOTAO_SAIR = al_create_bitmap(100, 50);
    if (!BOTAO_SAIR){
        fprintf(stderr, "Falha ao criar botão de saída.\n");
        return false;
    } 

    FILA_EVENTOS = al_create_event_queue();
    if (!FILA_EVENTOS){
        fprintf(stderr, "Falha ao inicializar o fila de eventos.\n");
        return false;
    }

    FONT = al_load_font("fonts/Raleway-Medium.ttf", 30, 0);
    if (!FONT) {
        fprintf(stderr,"Falha ao carregar a fonte do texto.");
        return false;
    }

    FONT2 = al_load_font("fonts/Raleway-Medium.ttf", 11, 0);
    if (!FONT) {
        fprintf(stderr,"Falha ao carregar a fonte do texto.");
        return false;
    }

    al_set_window_title(JANELA, "BBC PI 3 - Sistema Autônomo");

    al_register_event_source(FILA_EVENTOS, al_get_mouse_event_source());
    al_register_event_source(FILA_EVENTOS,al_get_timer_event_source(TIMER));

    return true;
}

void destruirTudo(){
    al_destroy_bitmap(BOTAO_SAIR);
    al_destroy_bitmap(AREA_CENTRAL);
    al_destroy_bitmap(BACKGROUND);
    al_destroy_display(JANELA);
    al_destroy_event_queue(FILA_EVENTOS);
    al_destroy_timer(TIMER);
    al_destroy_font(FONT);
}