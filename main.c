#include <allegro5/allegro.h> 
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/events.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "headers/iniciarAllegro.h"
#include "headers/iniciarJogo.h"
 
int main(void)
{   
    iniciarAllegro();

    iniciarJogo();
    
    destruirTudo();

    return 0;
}

