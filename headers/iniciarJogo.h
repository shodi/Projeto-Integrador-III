ALLEGRO_EVENT evento;

int MIN = 0, SEG = 0;
int TURNO = 0;

Fila *ARRAY_CLIENTES = NULL;

void carregarMenuInferior();
void carregarBackground();
void carregarFilas();

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
                        load_queue(&ARRAY_CLIENTES);
                        check_queue_status();
                        if(check_if_finish(&ARRAY_CLIENTES)){
                            printf("TERMINOU ESSA PORRA\n");
                            return 0;
                        }
                        print_fila(&FILA_A);
                        print_fila(&FILA_B);
                        print_fila(&FILA_C);
                        print_fila(&FILA_D);
                        print_fila(&FILA_E);

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
                    sair = true;
                }

        carregarBackground();
        carregarMenuInferior();
        carregarFilas();   

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
    al_draw_textf(FONT2, al_map_rgb(0, 0, 0), 60,  55, ALLEGRO_ALIGN_CENTRE, "%s", SETUP->A->flag);
    al_draw_bitmap(GUICHE1,  10,  80, 0);
    
    al_draw_textf(FONT, al_map_rgb(0, 0, 0), 185,  10, ALLEGRO_ALIGN_CENTRE, "5");    
    al_draw_filled_rectangle(135,50,235,80, al_map_rgb(0,255,0));
    al_draw_textf(FONT2, al_map_rgb(0, 0, 0), 185, 55, ALLEGRO_ALIGN_CENTRE, "%s", SETUP->A->flag);
    al_draw_bitmap(GUICHE2,  135, 80, 0);
    
    al_draw_textf(FONT, al_map_rgb(0, 0, 0), 315,  10, ALLEGRO_ALIGN_CENTRE, "5");    
    al_draw_filled_rectangle(265,50,365,80, al_map_rgb(0,255,0));
    al_draw_textf(FONT2, al_map_rgb(0, 0, 0), 315, 55, ALLEGRO_ALIGN_CENTRE, "%s", SETUP->B->flag);
    al_draw_bitmap(GUICHE3,  265, 80, 0);
    
    al_draw_textf(FONT, al_map_rgb(0, 0, 0), 445,  10, ALLEGRO_ALIGN_CENTRE, "5");    
    al_draw_filled_rectangle(395,50,495,80, al_map_rgb(0,255,0));
    al_draw_textf(FONT2, al_map_rgb(0, 0, 0), 445, 55, ALLEGRO_ALIGN_CENTRE, "%s", SETUP->B->flag);
    al_draw_bitmap(GUICHE4,  395, 80, 0);
    
    al_draw_textf(FONT, al_map_rgb(0, 0, 0), 575,  10, ALLEGRO_ALIGN_CENTRE, "5");    
    al_draw_filled_rectangle(525,50,625,80, al_map_rgb(0,255,0));
    al_draw_textf(FONT2, al_map_rgb(0, 0, 0), 575, 55, ALLEGRO_ALIGN_CENTRE, "%s", SETUP->C->flag);
    al_draw_bitmap(GUICHE5,   525, 80, 0);
    
    al_draw_textf(FONT, al_map_rgb(0, 0, 0), 705,  10, ALLEGRO_ALIGN_CENTRE, "5");    
    al_draw_filled_rectangle(655,50,755,80, al_map_rgb(0,255,0));
    al_draw_textf(FONT2, al_map_rgb(0, 0, 0), 705, 55, ALLEGRO_ALIGN_CENTRE, "%s", SETUP->D->flag);
    al_draw_bitmap(GUICHE6,  655, 80, 0);
    
    al_draw_textf(FONT, al_map_rgb(0, 0, 0), 835,  10, ALLEGRO_ALIGN_CENTRE, "5");    
    al_draw_filled_rectangle(785,50,885,80, al_map_rgb(0,255,0));
    al_draw_textf(FONT2, al_map_rgb(0, 0, 0), 835, 55, ALLEGRO_ALIGN_CENTRE, "%s", SETUP->D->flag);
    al_draw_bitmap(GUICHE7,  785, 80, 0);
    
    al_draw_textf(FONT, al_map_rgb(0, 0, 0), 965,  10, ALLEGRO_ALIGN_CENTRE, "5");    
    al_draw_filled_rectangle(915,50,1015,80, al_map_rgb(0,255,0));
    al_draw_textf(FONT2, al_map_rgb(0, 0, 0), 965, 55, ALLEGRO_ALIGN_CENTRE, "%s", SETUP->E->flag);
    al_draw_bitmap(GUICHE8,   915, 80, 0);

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

void carregarFilas(){
    //carregar fila 1
    switch (0)
    {
    //al_draw_bitmap(GUICHE1,  10,  80, 0);
        default:
        if ( 0 >= 9 ){ 
            al_draw_circle(60, 600, 15, al_map_rgb(0, 0, 0), 10);
        }        
        case 8: 
            al_draw_circle(60, 550, 15, al_map_rgb(0, 0, 0), 10);        
        case 7: 
            al_draw_circle(60, 500, 15, al_map_rgb(0, 0, 0), 10);        
        case 6: 
            al_draw_circle(60, 450, 15, al_map_rgb(0, 0, 0), 10);
        case 5: 
            al_draw_circle(60, 400, 15, al_map_rgb(0, 0, 0), 10);
        case 4: 
            al_draw_circle(60, 350, 15, al_map_rgb(0, 0, 0), 10);
        case 3: 
            al_draw_circle(60, 300, 15, al_map_rgb(0, 0, 0), 10);
        case 2:
            al_draw_circle(60, 250, 15, al_map_rgb(0, 0, 0), 10);
        case 1: 
            al_draw_circle(60, 200, 15, al_map_rgb(0, 0, 0), 10);
            break;
        case 0:
            al_draw_circle(60, 200, 15, al_map_rgb(190, 190, 190), 10);
    }     

    //carregar fila entre 1 e 2
    switch (0)
    {
    //al_draw_bitmap(GUICHE1,  10,  80, 0);
        default:
        if ( 0 >= 9 ){ 
            al_draw_circle(125, 600, 15, al_map_rgb(0, 0, 0), 10);
        }        
        case 8: 
            al_draw_circle(125, 550, 15, al_map_rgb(0, 0, 0), 10);        
        case 7: 
            al_draw_circle(125, 500, 15, al_map_rgb(0, 0, 0), 10);        
        case 6: 
            al_draw_circle(125, 450, 15, al_map_rgb(0, 0, 0), 10);
        case 5: 
            al_draw_circle(125, 400, 15, al_map_rgb(0, 0, 0), 10);
        case 4: 
            al_draw_circle(125, 350, 15, al_map_rgb(0, 0, 0), 10);
        case 3: 
            al_draw_circle(125, 300, 15, al_map_rgb(0, 0, 0), 10);
        case 2:
            al_draw_circle(125, 250, 15, al_map_rgb(0, 0, 0), 10);
        case 1: 
            al_draw_circle(125, 200, 15, al_map_rgb(0, 0, 0), 10);
            break;
        case 0:
            al_draw_circle(125, 200, 15, al_map_rgb(190, 190, 190), 10);
    }    

    // carregar fila 2
    switch (0)
    {
    //al_draw_bitmap(GUICHE2,  135, 80, 0);
        default:
        if ( 0 >= 9 ){ 
            al_draw_circle(185, 600, 15, al_map_rgb(0, 0, 0), 10);
        }        
        case 8: 
            al_draw_circle(185, 550, 15, al_map_rgb(0, 0, 0), 10);        
        case 7: 
            al_draw_circle(185, 500, 15, al_map_rgb(0, 0, 0), 10);        
        case 6: 
            al_draw_circle(185, 450, 15, al_map_rgb(0, 0, 0), 10);
        case 5: 
            al_draw_circle(185, 400, 15, al_map_rgb(0, 0, 0), 10);
        case 4: 
            al_draw_circle(185, 350, 15, al_map_rgb(0, 0, 0), 10);
        case 3: 
            al_draw_circle(185, 300, 15, al_map_rgb(0, 0, 0), 10);
        case 2:
            al_draw_circle(185, 250, 15, al_map_rgb(0, 0, 0), 10);
        case 1: 
            al_draw_circle(185, 200, 15, al_map_rgb(0, 0, 0), 10);
            break;
        case 0:
            al_draw_circle(185, 200, 15, al_map_rgb(190, 190, 190), 10);
    }    


    // carregar fila entre 2 e 3
    switch (0)
    {
    //al_draw_bitmap(GUICHE2,  135, 80, 0);
        default:
        if ( 0 >= 9 ){ 
            al_draw_circle(250, 600, 15, al_map_rgb(0, 0, 0), 10);
        }        
        case 8: 
            al_draw_circle(250, 550, 15, al_map_rgb(0, 0, 0), 10);        
        case 7: 
            al_draw_circle(250, 500, 15, al_map_rgb(0, 0, 0), 10);        
        case 6: 
            al_draw_circle(250, 450, 15, al_map_rgb(0, 0, 0), 10);
        case 5: 
            al_draw_circle(250, 400, 15, al_map_rgb(0, 0, 0), 10);
        case 4: 
            al_draw_circle(250, 350, 15, al_map_rgb(0, 0, 0), 10);
        case 3: 
            al_draw_circle(250, 300, 15, al_map_rgb(0, 0, 0), 10);
        case 2:
            al_draw_circle(250, 250, 15, al_map_rgb(0, 0, 0), 10);
        case 1: 
            al_draw_circle(250, 200, 15, al_map_rgb(0, 0, 0), 10);
            break;
        case 0:
            al_draw_circle(250, 200, 15, al_map_rgb(190, 190, 190), 10);
    }

    //carregar fila 3
    switch (0)
    {
    //al_draw_bitmap(GUICHE3,  265, 80, 0)
        default:
        if ( 0 >= 9 ){ 
            al_draw_circle(315, 600, 15, al_map_rgb(0, 0, 0), 10);
        }        
        case 8: 
            al_draw_circle(315, 550, 15, al_map_rgb(0, 0, 0), 10);        
        case 7: 
            al_draw_circle(315, 500, 15, al_map_rgb(0, 0, 0), 10);        
        case 6: 
            al_draw_circle(315, 450, 15, al_map_rgb(0, 0, 0), 10);
        case 5: 
            al_draw_circle(315, 400, 15, al_map_rgb(0, 0, 0), 10);
        case 4: 
            al_draw_circle(315, 350, 15, al_map_rgb(0, 0, 0), 10);
        case 3: 
            al_draw_circle(315, 300, 15, al_map_rgb(0, 0, 0), 10);
        case 2:
            al_draw_circle(315, 250, 15, al_map_rgb(0, 0, 0), 10);
        case 1: 
            al_draw_circle(315, 200, 15, al_map_rgb(0, 0, 0), 10);
            break;
        case 0:
            al_draw_circle(315, 200, 15, al_map_rgb(190, 190, 190), 10);    
    }    

    //carregar fila entre 3 e 4
    switch (0)
    {
    //al_draw_bitmap(GUICHE3,  265, 80, 0)
        default:
        if ( 0 >= 9 ){ 
            al_draw_circle(380, 600, 15, al_map_rgb(0, 0, 0), 10);
        }        
        case 8: 
            al_draw_circle(380, 550, 15, al_map_rgb(0, 0, 0), 10);        
        case 7: 
            al_draw_circle(380, 500, 15, al_map_rgb(0, 0, 0), 10);        
        case 6: 
            al_draw_circle(380, 450, 15, al_map_rgb(0, 0, 0), 10);
        case 5: 
            al_draw_circle(380, 400, 15, al_map_rgb(0, 0, 0), 10);
        case 4: 
            al_draw_circle(380, 350, 15, al_map_rgb(0, 0, 0), 10);
        case 3: 
            al_draw_circle(380, 300, 15, al_map_rgb(0, 0, 0), 10);
        case 2:
            al_draw_circle(380, 250, 15, al_map_rgb(0, 0, 0), 10);
        case 1: 
            al_draw_circle(380, 200, 15, al_map_rgb(0, 0, 0), 10);
            break;
        case 0:
            al_draw_circle(380, 200, 15, al_map_rgb(190, 190, 190), 10);    
    }    

    //carregar fila 4
    switch (0)
    {
    //al_draw_bitmap(GUICHE4,  395, 80, 0);
        default:
        if ( 0 >= 9 ){ 
            al_draw_circle(445, 600, 15, al_map_rgb(0, 0, 0), 10);
        }        
        case 8: 
            al_draw_circle(445, 550, 15, al_map_rgb(0, 0, 0), 10);        
        case 7: 
            al_draw_circle(445, 500, 15, al_map_rgb(0, 0, 0), 10);        
        case 6: 
            al_draw_circle(445, 450, 15, al_map_rgb(0, 0, 0), 10);
        case 5: 
            al_draw_circle(445, 400, 15, al_map_rgb(0, 0, 0), 10);
        case 4: 
            al_draw_circle(445, 350, 15, al_map_rgb(0, 0, 0), 10);
        case 3: 
            al_draw_circle(445, 300, 15, al_map_rgb(0, 0, 0), 10);
        case 2:
            al_draw_circle(445, 250, 15, al_map_rgb(0, 0, 0), 10);
        case 1: 
            al_draw_circle(445, 200, 15, al_map_rgb(0, 0, 0), 10);
            break;
        case 0:
            al_draw_circle(445, 200, 15, al_map_rgb(190, 190, 190), 10);    
    }

    //carregar fila entre 4 e 5
    switch (0)
    {
    //al_draw_bitmap(GUICHE4,  395, 80, 0);
        default:
        if ( 0 >= 9 ){ 
            al_draw_circle(510, 600, 15, al_map_rgb(0, 0, 0), 10);
        }        
        case 8: 
            al_draw_circle(510, 550, 15, al_map_rgb(0, 0, 0), 10);        
        case 7: 
            al_draw_circle(510, 500, 15, al_map_rgb(0, 0, 0), 10);        
        case 6: 
            al_draw_circle(510, 450, 15, al_map_rgb(0, 0, 0), 10);
        case 5: 
            al_draw_circle(510, 400, 15, al_map_rgb(0, 0, 0), 10);
        case 4: 
            al_draw_circle(510, 350, 15, al_map_rgb(0, 0, 0), 10);
        case 3: 
            al_draw_circle(510, 300, 15, al_map_rgb(0, 0, 0), 10);
        case 2:
            al_draw_circle(510, 250, 15, al_map_rgb(0, 0, 0), 10);
        case 1: 
            al_draw_circle(510, 200, 15, al_map_rgb(0, 0, 0), 10);
            break;
        case 0:
            al_draw_circle(510, 200, 15, al_map_rgb(190, 190, 190), 10);    
    }    

    //carregar fila 5
    switch (0)
    {
    //al_draw_bitmap(GUICHE5,   525, 80, 0);
                default:
        if ( 0 >= 9 ){ 
            al_draw_circle(575, 600, 15, al_map_rgb(0, 0, 0), 10);
        }        
        case 8: 
            al_draw_circle(575, 550, 15, al_map_rgb(0, 0, 0), 10);        
        case 7: 
            al_draw_circle(575, 500, 15, al_map_rgb(0, 0, 0), 10);        
        case 6: 
            al_draw_circle(575, 450, 15, al_map_rgb(0, 0, 0), 10);
        case 5: 
            al_draw_circle(575, 400, 15, al_map_rgb(0, 0, 0), 10);
        case 4: 
            al_draw_circle(575, 350, 15, al_map_rgb(0, 0, 0), 10);
        case 3: 
            al_draw_circle(575, 300, 15, al_map_rgb(0, 0, 0), 10);
        case 2:
            al_draw_circle(575, 250, 15, al_map_rgb(0, 0, 0), 10);
        case 1: 
            al_draw_circle(575, 200, 15, al_map_rgb(0, 0, 0), 10);
            break;
        case 0:
            al_draw_circle(575, 200, 15, al_map_rgb(190, 190, 190), 10);
    }    

    //carregar fila entre 5 e 6
    switch (0)
    {
    //al_draw_bitmap(GUICHE5,   525, 80, 0);
                default:
        if ( 0 >= 9 ){ 
            al_draw_circle(640, 600, 15, al_map_rgb(0, 0, 0), 10);
        }        
        case 8: 
            al_draw_circle(640, 550, 15, al_map_rgb(0, 0, 0), 10);        
        case 7: 
            al_draw_circle(640, 500, 15, al_map_rgb(0, 0, 0), 10);        
        case 6: 
            al_draw_circle(640, 450, 15, al_map_rgb(0, 0, 0), 10);
        case 5: 
            al_draw_circle(640, 400, 15, al_map_rgb(0, 0, 0), 10);
        case 4: 
            al_draw_circle(640, 350, 15, al_map_rgb(0, 0, 0), 10);
        case 3: 
            al_draw_circle(640, 300, 15, al_map_rgb(0, 0, 0), 10);
        case 2:
            al_draw_circle(640, 250, 15, al_map_rgb(0, 0, 0), 10);
        case 1: 
            al_draw_circle(640, 200, 15, al_map_rgb(0, 0, 0), 10);
            break;
        case 0:
            al_draw_circle(640, 200, 15, al_map_rgb(190, 190, 190), 10);
    }    

    //carregar fila 6
    switch (0)
    {
    //al_draw_bitmap(GUICHE6,  655, 80, 0);
        default:
        if ( 0 >= 9 ){ 
            al_draw_circle(705, 600, 15, al_map_rgb(0, 0, 0), 10);
        }        
        case 8: 
            al_draw_circle(705, 550, 15, al_map_rgb(0, 0, 0), 10);        
        case 7: 
            al_draw_circle(705, 500, 15, al_map_rgb(0, 0, 0), 10);        
        case 6: 
            al_draw_circle(705, 450, 15, al_map_rgb(0, 0, 0), 10);
        case 5: 
            al_draw_circle(705, 400, 15, al_map_rgb(0, 0, 0), 10);
        case 4: 
            al_draw_circle(705, 350, 15, al_map_rgb(0, 0, 0), 10);
        case 3: 
            al_draw_circle(705, 300, 15, al_map_rgb(0, 0, 0), 10);
        case 2:
            al_draw_circle(705, 250, 15, al_map_rgb(0, 0, 0), 10);
        case 1: 
            al_draw_circle(705, 200, 15, al_map_rgb(0, 0, 0), 10);
            break;
        case 0:
            al_draw_circle(705, 200, 15, al_map_rgb(190, 190, 190), 10);
    }

    //carregar fila entre 6 e 7
    switch (0)
    {
    //al_draw_bitmap(GUICHE6,  655, 80, 0);
        default:
        if ( 0 >= 9 ){ 
            al_draw_circle(770, 600, 15, al_map_rgb(0, 0, 0), 10);
        }        
        case 8: 
            al_draw_circle(770, 550, 15, al_map_rgb(0, 0, 0), 10);        
        case 7: 
            al_draw_circle(770, 500, 15, al_map_rgb(0, 0, 0), 10);        
        case 6: 
            al_draw_circle(770, 450, 15, al_map_rgb(0, 0, 0), 10);
        case 5: 
            al_draw_circle(770, 400, 15, al_map_rgb(0, 0, 0), 10);
        case 4: 
            al_draw_circle(770, 350, 15, al_map_rgb(0, 0, 0), 10);
        case 3: 
            al_draw_circle(770, 300, 15, al_map_rgb(0, 0, 0), 10);
        case 2:
            al_draw_circle(770, 250, 15, al_map_rgb(0, 0, 0), 10);
        case 1: 
            al_draw_circle(770, 200, 15, al_map_rgb(0, 0, 0), 10);
            break;
        case 0:
            al_draw_circle(770, 200, 15, al_map_rgb(190, 190, 190), 10);
    }

    //carregar fila 7
    switch (0)
    {
    //al_draw_bitmap(GUICHE7,  785, 80, 0);
        default:
        if ( 0 >= 9 ){ 
            al_draw_circle(835, 600, 15, al_map_rgb(0, 0, 0), 10);
        }        
        case 8: 
            al_draw_circle(835, 550, 15, al_map_rgb(0, 0, 0), 10);        
        case 7: 
            al_draw_circle(835, 500, 15, al_map_rgb(0, 0, 0), 10);        
        case 6: 
            al_draw_circle(835, 450, 15, al_map_rgb(0, 0, 0), 10);
        case 5: 
            al_draw_circle(835, 400, 15, al_map_rgb(0, 0, 0), 10);
        case 4: 
            al_draw_circle(835, 350, 15, al_map_rgb(0, 0, 0), 10);
        case 3: 
            al_draw_circle(835, 300, 15, al_map_rgb(0, 0, 0), 10);
        case 2:
            al_draw_circle(835, 250, 15, al_map_rgb(0, 0, 0), 10);
        case 1: 
            al_draw_circle(835, 200, 15, al_map_rgb(0, 0, 0), 10);
            break;
        case 0:
            al_draw_circle(835, 200, 15, al_map_rgb(190, 190, 190), 10);
    }  

    //carregar fila entre 7 e 8
    switch (0)
    {
    //al_draw_bitmap(GUICHE7,  785, 80, 0);
        default:
        if ( 0 >= 9 ){ 
            al_draw_circle(900, 600, 15, al_map_rgb(0, 0, 0), 10);
        }        
        case 8: 
            al_draw_circle(900, 550, 15, al_map_rgb(0, 0, 0), 10);        
        case 7: 
            al_draw_circle(900, 500, 15, al_map_rgb(0, 0, 0), 10);        
        case 6: 
            al_draw_circle(900, 450, 15, al_map_rgb(0, 0, 0), 10);
        case 5: 
            al_draw_circle(900, 400, 15, al_map_rgb(0, 0, 0), 10);
        case 4: 
            al_draw_circle(900, 350, 15, al_map_rgb(0, 0, 0), 10);
        case 3: 
            al_draw_circle(900, 300, 15, al_map_rgb(0, 0, 0), 10);
        case 2:
            al_draw_circle(900, 250, 15, al_map_rgb(0, 0, 0), 10);
        case 1: 
            al_draw_circle(900, 200, 15, al_map_rgb(0, 0, 0), 10);
            break;
        case 0:
            al_draw_circle(900, 200, 15, al_map_rgb(190, 190, 190), 10);
    }    

    //carregar fila 8
    switch (0)
    {
    //al_draw_bitmap(GUICHE8,   915, 80, 0);
        default:
        if ( 0 >= 9 ){ 
            al_draw_circle(970, 600, 15, al_map_rgb(0, 0, 0), 10);
        }        
        case 8: 
            al_draw_circle(970, 550, 15, al_map_rgb(0, 0, 0), 10);        
        case 7: 
            al_draw_circle(970, 500, 15, al_map_rgb(0, 0, 0), 10);        
        case 6: 
            al_draw_circle(970, 450, 15, al_map_rgb(0, 0, 0), 10);
        case 5: 
            al_draw_circle(970, 400, 15, al_map_rgb(0, 0, 0), 10);
        case 4: 
            al_draw_circle(970, 350, 15, al_map_rgb(0, 0, 0), 10);
        case 3: 
            al_draw_circle(970, 300, 15, al_map_rgb(0, 0, 0), 10);
        case 2:
            al_draw_circle(970, 250, 15, al_map_rgb(0, 0, 0), 10);
        case 1: 
            al_draw_circle(970, 200, 15, al_map_rgb(0, 0, 0), 10);
            break;
        case 0:
            al_draw_circle(970, 200, 15, al_map_rgb(190, 190, 190), 10);       

    }
    
}
