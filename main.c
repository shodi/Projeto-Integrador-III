#include <allegro5/allegro.h> 
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/events.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include "scripts/config.h"
#include "headers/iniciarAllegro.h"
#include "headers/iniciarJogo.h"
#include "scripts/report.h"

const char *CONFIG_FILE = NULL;
const char *CLIENT_LIST_FILE = NULL;

int main(int argc, char *argv[]){   
    
    if(argc < 2){
        printf("Passe o nome dos arquivos de configuracao por linha de comando conforme o manual\n");
        return -1;
    }

    system("kill -9 $(ps aux | grep /tmp/report.txt | grep -v grep | awk '{print $2}')");

    CONFIG_FILE = argv[1];
    CLIENT_LIST_FILE = argv[2];

    SETUP = get_config(CONFIG_FILE);
    if(SETUP == NULL) return -1;
    
    iniciarAllegro();

    if(!iniciarJogo(CLIENT_LIST_FILE)) printf("ATENDIMENTO ENCERRADO\n\n");
    
    destruirTudo();

    if(SETUP) free(SETUP);
    if(ARRAY_CLIENTES) free(ARRAY_CLIENTES);
    generate_report();
    if(CLIENTES_FIN) free(CLIENTES_FIN);
    system("xdg-open /tmp/report.txt");

    return 0;
}

