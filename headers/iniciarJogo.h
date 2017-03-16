 ALLEGRO_EVENT evento;

 void carregarMenuInferior();
 void carregarBackground();


    bool sair = false;
            //Evento clique do mouse
            if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){                                
                if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(BOTAO_SAIR) - 10 &&
                    evento.mouse.x <= LARGURA_TELA - 10 && evento.mouse.y <= ALTURA_TELA - 10 &&
                    evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(BOTAO_SAIR) - 10)
                {
                    sair = true;
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

    al_draw_text(FONT, al_map_rgb(255, 0, 0), 580, 420, ALLEGRO_ALIGN_CENTRE, "Sair");    
}

void carregarBackground(){  
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_draw_bitmap(BACKGROUND, 0, 0, 0);
}