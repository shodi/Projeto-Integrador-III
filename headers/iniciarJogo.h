ALLEGRO_EVENT evento;

int MIN = 0, SEG = 0;
int TURNO = 0, xGuiche = 0, xFila = 20;

//variaveis temporarias
int qtdPostos = 0;
int variedade = 0;
int qtdpessoas = 10;
char posto;

void carregarMenuInferior();
void carregarBackground();

int iniciarJogo(const char *CLIENT_LIST_FILE){
    int sair = 0;
    Fila *new_client = NULL;
    al_start_timer(TIMER);
    
    while (!sair){
        
        while (!al_is_event_queue_empty(FILA_EVENTOS)){            
            al_wait_for_event(FILA_EVENTOS, &evento); 
            if(evento.type == ALLEGRO_EVENT_TIMER){
                SEG++;
                if(SEG == 60){
                    MIN++;
                    SEG = 0;
                }
                new_client = get_client(CLIENT_LIST_FILE, TURNO);
                while(new_client){
                    insert_element_by_key(&ARRAY_CLIENTES, NULL, new_client->cliente.current_step, new_client->cliente);
                    new_client = new_client->proximo;
                }
                new_client = NULL;
                set_all_queues_attending(&ARRAY_CLIENTES);
                update_queues(&ARRAY_CLIENTES);
                // print_fila(&CLIENTES_FIN);
                // print_super_fila(&ARRAY_CLIENTES);
                // if(check_queue_status(&ARRAY_CLIENTES, 0)) return 0;
                TURNO++;
                if(check_if_finished(&CLIENTES_FIN)){printf("TEMPO TOTAL DE ATENDIMENTO: %d\n", TURNO); return 0;}
            
            }
            
            if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){                                
                if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(BOTAO_SAIR) - 10 &&
                    evento.mouse.x <= LARGURA_TELA - 10 && evento.mouse.y <= ALTURA_TELA - 10 &&
                    evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(BOTAO_SAIR) - 10){
                    sair = 1;
                } 

                if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                    if(evento.mouse.x >= 60 && evento.mouse.x <= 110 &&
                        evento.mouse.y >= 650 && evento.mouse.y <= 750){
                        al_start_timer(TIMER);
                        al_set_timer_speed(TIMER,1.0);

                    }
                }
                if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                    if(evento.mouse.x >= 120 && evento.mouse.x <= 190 &&
                        evento.mouse.y >= 650 && evento.mouse.y <= 750){
                        al_start_timer(TIMER);
                        al_set_timer_speed(TIMER,0.5);

                    }
                } 
                if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                    if(evento.mouse.x >= 200 && evento.mouse.x <= 300 &&
                        evento.mouse.y >= 650 && evento.mouse.y <= 750){
                        al_start_timer(TIMER);
                        al_set_timer_speed(TIMER,0.33);

                    }
                    if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                    if(evento.mouse.x >= 10 && evento.mouse.x <= 50 &&
                        evento.mouse.y >= 650 && evento.mouse.y <= 750){
                        al_stop_timer(TIMER);

                    }
                }
                } 
            }

        }
        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                    sair = 1;
                }

        carregarBackground();
        carregarMenuInferior();

        // Atualiza a tela
        al_flip_display();
    }
    return 0;
}

void carregarMenuInferior(){
    al_set_target_bitmap(BOTAO_SAIR);
    al_clear_to_color(al_map_rgb(0, 120, 0));
    al_set_target_bitmap(al_get_backbuffer(JANELA));
    al_draw_bitmap(BOTAO_SAIR, LARGURA_TELA - al_get_bitmap_width(BOTAO_SAIR) - 10,
        ALTURA_TELA - al_get_bitmap_height(BOTAO_SAIR) - 10, 0);


    char *nome = NULL;
    // int *qtd_postos = 0;
    // int *qtd_attendent = 0;
    int is_atend = 0;
    // guichês
    qtdPostos = total_postos(&ARRAY_CLIENTES, qtdPostos);
    for (int i = 0; i <= qtdPostos; ++i){

        //detalhe_guiche(&ARRAY_CLIENTES, nome, qtd_postos, qtd_attendent, is_atend);
        detalhe_guiche(&ARRAY_CLIENTES, &nome, &is_atend);
        al_draw_filled_rectangle(xGuiche, 65, (xGuiche+54),80, al_map_rgb(255,0,0));
        al_draw_textf(FONT2, al_map_rgb(1, 1, 1), (xGuiche+27), 65, ALLEGRO_ALIGN_CENTRE, "oie");    
        al_draw_bitmap(GUICHE, xGuiche, 80, 0);
        xGuiche += 1080/qtdPostos;

    }
    xGuiche = 0;
    qtdPostos = 0;
    
    // filas dos guichês
    variedade = variedade_postos(&ARRAY_CLIENTES, variedade, posto);
    for (int i = 0; i < variedade; ++i)
    {
        al_draw_filled_rectangle(xFila, 150, (xFila+14), (qtdpessoas+300), al_map_rgb(0,0,255));
        al_draw_textf(FONT, al_map_rgb(1, 1, 1), (xFila+7), (qtdpessoas+305), ALLEGRO_ALIGN_CENTRE, "%d",TURNO);    
        xFila += 1080/variedade;
    
    }
    variedade = 0;
    xFila = 20;

    //botões de controle
    al_draw_filled_rectangle(0,640,1080,720, al_map_rgb(255,255,255));
    al_draw_bitmap(PAUSEBTTN,      10, 650, 0);
    al_draw_bitmap(PLAYBTTN,       60, 650, 0);
    al_draw_bitmap(TWOTIMESBTTN,   120, 650, 0);
    al_draw_bitmap(THREETIMESBTTN, 200, 650, 0);

    //relogio
    al_draw_text(FONT, al_map_rgb(0, 0, 0), 400, 655, ALLEGRO_ALIGN_CENTRE, "Turno:");
    al_draw_textf(FONT, al_map_rgb(0, 0, 200), 480, 655, ALLEGRO_ALIGN_CENTRE, "%d",TURNO);    
    al_draw_text(FONT, al_map_rgb(0, 0, 0), 670, 655, ALLEGRO_ALIGN_CENTRE, "Tempo:");
    al_draw_textf(FONT, al_map_rgb(255, 0, 0), 790, 655, ALLEGRO_ALIGN_CENTRE, "%d:%d",MIN, SEG);
    }

void carregarBackground(){  
    al_clear_to_color(al_map_rgb(190, 190, 190));
    //al_draw_bitmap(BACKGROUND, 0, 0, 0);
}

