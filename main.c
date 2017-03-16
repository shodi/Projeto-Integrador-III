// Os arquivos de cabeçalho
#include <allegro5/allegro.h> 
#include <stdio.h>
#include <stdlib.h>
#include "scripts/config.h"
#include "headers/iniciarAllegro.h"
#include "headers/iniciarJogo.h"

const char *CONFIG_FILE = NULL;
const char *CLIENT_LIST_FILE = NULL;

int main(int argc, char *argv[]){   
    
    if(argc < 2){
        printf("Passe o nome dos arquivos de configuracao por linha de comando conforme o manual\n");
        return -1;
    }

    CONFIG_FILE = argv[1];
    CLIENT_LIST_FILE = argv[2];

    SETUP = get_config(CONFIG_FILE);
    if(SETUP == NULL) return -1;
    iniciarAllegro();

    iniciarJogo();
    
    destruirTudo();

    return 0;
}

