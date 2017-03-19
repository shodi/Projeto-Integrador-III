ALLEGRO_EVENT evento;

int MIN = 0, SEG = 0;
int TURNO = 0;

Fila *ARRAY_CLIENTES = NULL;

void carregarMenuInferior();
void carregarBackground();

int iniciarJogo(const char *CLIENT_LIST_FILE){
    bool sair = false;
    Fila *new_client = NULL;

    while (!sair){
        al_start_timer(TIMER);

        while (!al_is_event_queue_empty(FILA_EVENTOS)){            
            al_wait_for_event(FILA_EVENTOS, &evento); 
            if(evento.type == ALLEGRO_EVENT_TIMER){
                SEG++;
                if(SEG == 60){
                    MIN++;
                    SEG = 0;
                }
                if(0 == SEG % 10){
                    TURNO++;
                    new_client = get_client(CLIENT_LIST_FILE, TURNO);
                    while(new_client != NULL){
                        printf("ID: %d\n", new_client->cliente.id);
                        printf("ARRIVAL TIME: %d\n", new_client->cliente.arrival_time);
                        new_client = new_client->proximo;  
                    }
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
                    if(evento.mouse.x >= 100 && evento.mouse.x <= 200 &&
                        evento.mouse.y >= 300 && evento.mouse.y <= 400){
                        al_set_timer_speed(TIMER,1.0);

                    }
                }
                if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                    if(evento.mouse.x >= 200 && evento.mouse.x <= 300 &&
                        evento.mouse.y >= 300 && evento.mouse.y <= 400){
                        al_set_timer_speed(TIMER,0.5);

                    }
                } 
                if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
                    if(evento.mouse.x >= 300 && evento.mouse.x <= 400 &&
                        evento.mouse.y >= 300 && evento.mouse.y <= 400){
                        al_set_timer_speed(TIMER,0.33);

                    }
                } 
            }

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
    al_draw_filled_rectangle(100,300,200,400, al_map_rgb(255,0,0));
    al_draw_filled_rectangle(200,300,300,400, al_map_rgb(0,255,0));
    al_draw_filled_rectangle(300,300,400,400, al_map_rgb(0,0,255));

    al_draw_text(FONT, al_map_rgb(255, 0, 0), 580, 420, ALLEGRO_ALIGN_CENTRE, "Sair");
    //relogio
    al_draw_textf(FONT, al_map_rgb(255, 0, 0), 580, 20, ALLEGRO_ALIGN_CENTRE, "%d:%d",MIN, SEG);
    al_draw_textf(FONT, al_map_rgb(0, 0, 200), 300, 20, ALLEGRO_ALIGN_CENTRE, "%d",TURNO);    
    }

void carregarBackground(){  
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_draw_bitmap(BACKGROUND, 0, 0, 0);
}