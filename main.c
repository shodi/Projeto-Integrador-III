// Os arquivos de cabeçalho
#include <allegro5/allegro.h> 
#include <stdio.h>
#include <stdlib.h>
#include "headers/iniciarAllegro.h"
#include "headers/iniciarJogo.h"

//Funções
void destruirTudo();
 
int main(void)
{   

    iniciarAllegro();

    iniciarJogo();
    
    destruirTudo();

    return 0;
}

