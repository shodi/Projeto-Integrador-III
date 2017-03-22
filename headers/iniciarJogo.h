ALLEGRO_EVENT evento;

int MIN = 0, SEG = 0;
int TURNO = 0;

Fila *ARRAY_CLIENTES = NULL;

void carregarMenuInferior();
void carregarBackground();

int iniciarJogo(const char *CLIENT_LIST_FILE){
    bool sair = false;
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
                if(0 == SEG % 1){
                    TURNO++;
                    new_client = get_client(CLIENT_LIST_FILE, TURNO);
                    while(new_client){
                        new_client->cliente.current_step = new_client->cliente.sequence[0];
                        inclui_fila(&ARRAY_CLIENTES, new_client->cliente);
                        new_client = new_client->proximo;
                    }
                    print_fila(&ARRAY_CLIENTES);
                    new_client = NULL;
                }
            }
            
            if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){                                
                if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(BOTAO_SAIR) - 10 &&
                    evento.mouse.x <= LARGURA_TELA - 10 && evento.mouse.y <= ALTURA_TELA - 10 &&
                    evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(BOTAO_SAIR) - 10){
                    sair = true;
                } 
                if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                    if(evento.mouse.x >= 60 && evento.mouse.x <= 100 &&
                        evento.mouse.y >= 600 && evento.mouse.y <= 700){
                        al_start_timer(TIMER);
                        al_set_timer_speed(TIMER,1.0);

                    }
                }
                if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                    if(evento.mouse.x >= 120 && evento.mouse.x <= 170 &&
                        evento.mouse.y >= 600 && evento.mouse.y <= 700){
                        al_start_timer(TIMER);
                        al_set_timer_speed(TIMER,0.5);

                    }
                } 
                if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                    if(evento.mouse.x >= 230 && evento.mouse.x <= 300 &&
                        evento.mouse.y >= 600 && evento.mouse.y <= 700){
                        al_start_timer(TIMER);
                        al_set_timer_speed(TIMER,0.33);

                    }
                    if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                    if(evento.mouse.x >= 10 && evento.mouse.x <= 50 &&
                        evento.mouse.y >= 600 && evento.mouse.y <= 700){
                        al_stop_timer(TIMER);

                    }
                }
                } 
            }

        }
        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                    sair = true;
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

    // guichês
    al_draw_textf(FONT, al_map_rgb(0, 0, 0), 60,  10,  ALLEGRO_ALIGN_CENTRE, "5");    
    al_draw_filled_rectangle(10,50,110,80, al_map_rgb(0,255,0));
    al_draw_textf(FONT, al_map_rgb(0, 0, 0), 60,  55, ALLEGRO_ALIGN_CENTRE, "%s", SETUP->A->flag);
    al_draw_bitmap(GUICHEA1,  10,  80, 0);
    
    al_draw_textf(FONT, al_map_rgb(0, 0, 0), 185,  10, ALLEGRO_ALIGN_CENTRE, "5");    
    al_draw_filled_rectangle(135,50,235,80, al_map_rgb(0,255,0));
    al_draw_textf(FONT, al_map_rgb(0, 0, 0), 185, 55, ALLEGRO_ALIGN_CENTRE, "%s", SETUP->A->flag);
    al_draw_bitmap(GUICHEA2,  135, 80, 0);
    
    al_draw_textf(FONT, al_map_rgb(0, 0, 0), 315,  10, ALLEGRO_ALIGN_CENTRE, "5");    
    al_draw_filled_rectangle(265,50,365,80, al_map_rgb(0,255,0));
    al_draw_textf(FONT, al_map_rgb(0, 0, 0), 315, 55, ALLEGRO_ALIGN_CENTRE, "%s", SETUP->B->flag);
    al_draw_bitmap(GUICHEB1,  265, 80, 0);
    
    al_draw_textf(FONT, al_map_rgb(0, 0, 0), 445,  10, ALLEGRO_ALIGN_CENTRE, "5");    
    al_draw_filled_rectangle(395,50,495,80, al_map_rgb(0,255,0));
    al_draw_textf(FONT, al_map_rgb(0, 0, 0), 445, 55, ALLEGRO_ALIGN_CENTRE, "%s", SETUP->B->flag);
    al_draw_bitmap(GUICHEB2,  395, 80, 0);
    
    al_draw_textf(FONT, al_map_rgb(0, 0, 0), 575,  10, ALLEGRO_ALIGN_CENTRE, "5");    
    al_draw_filled_rectangle(525,50,625,80, al_map_rgb(0,255,0));
    al_draw_textf(FONT, al_map_rgb(0, 0, 0), 575, 55, ALLEGRO_ALIGN_CENTRE, "%s", SETUP->C->flag);
    al_draw_bitmap(GUICHEC,   525, 80, 0);
    
    al_draw_textf(FONT, al_map_rgb(0, 0, 0), 705,  10, ALLEGRO_ALIGN_CENTRE, "5");    
    al_draw_filled_rectangle(655,50,755,80, al_map_rgb(0,255,0));
    al_draw_textf(FONT, al_map_rgb(0, 0, 0), 705, 55, ALLEGRO_ALIGN_CENTRE, "%s", SETUP->D->flag);
    al_draw_bitmap(GUICHED1,  655, 80, 0);
    
    al_draw_textf(FONT, al_map_rgb(0, 0, 0), 835,  10, ALLEGRO_ALIGN_CENTRE, "5");    
    al_draw_filled_rectangle(785,50,885,80, al_map_rgb(0,255,0));
    al_draw_textf(FONT, al_map_rgb(0, 0, 0), 835, 55, ALLEGRO_ALIGN_CENTRE, "%s", SETUP->D->flag);
    al_draw_bitmap(GUICHED2,  785, 80, 0);
    
    al_draw_textf(FONT, al_map_rgb(0, 0, 0), 965,  10, ALLEGRO_ALIGN_CENTRE, "5");    
    al_draw_filled_rectangle(915,50,1015,80, al_map_rgb(0,255,0));
    al_draw_textf(FONT, al_map_rgb(0, 0, 0), 965, 55, ALLEGRO_ALIGN_CENTRE, "%s", SETUP->E->flag);
    al_draw_bitmap(GUICHEE,   915, 80, 0);

    //botões de controle
    al_draw_filled_rectangle(0,640,1080,720, al_map_rgb(255,255,255));
    al_draw_bitmap(PAUSEBTTN,      10, 650, 0);
    al_draw_bitmap(PLAYBTTN,       60, 650, 0);
    al_draw_bitmap(TWOTIMESBTTN,   120, 650, 0);
    al_draw_bitmap(THREETIMESBTTN, 230, 650, 0);

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