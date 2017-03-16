 int iniciarJogo(){

    // Flag que condicionará nosso looping
    int sair = 0;

    while (!sair)
    {
        // Verificamos se há eventos na fila
        while (!al_is_event_queue_empty(fila_eventos))
        {
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);
 
            //Evento clique do mouse
            if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
            {
                if (evento.mouse.x >= LARGURA_TELA - al_get_bitmap_width(botao_sair) - 10 &&
                    evento.mouse.x <= LARGURA_TELA - 10 && evento.mouse.y <= ALTURA_TELA - 10 &&
                    evento.mouse.y >= ALTURA_TELA - al_get_bitmap_height(botao_sair) - 10)
                {
                    sair = 1;
                }
            }
        }
 
 
        // Colorimos
        al_set_target_bitmap(botao_sair);
        al_clear_to_color(al_map_rgb(255, 0, 0));
 
        // Retangulo Sair
        al_set_target_bitmap(al_get_backbuffer(janela));
        al_draw_bitmap(botao_sair, LARGURA_TELA - al_get_bitmap_width(botao_sair) - 10,
                       ALTURA_TELA - al_get_bitmap_height(botao_sair) - 10, 0);
 
        // Atualiza a tela
        al_flip_display();
    }
    return 1;
}