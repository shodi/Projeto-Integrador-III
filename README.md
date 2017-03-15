## Projeto Integrador III: Sistema Autônomo
#### Bacharelado em Ciências da Computação: 3º Semestre(2017)

Integrantes: Caio Luzano, Gustavo Diogo, Henrique Shodi e Luiz Frederico


##Linux
### Instalação

>sudo apt-get install liballegro5-dev

### Compilação

>gcc main.c -o main.exe -lm -pedantic -std=c99 -W -Wall $(pkg-config –cflags –libs allegro-5) -lallegro -lallegro_main -lallegro_image -lallegro_font -lallegro_primitives -lallegro_ttf -lallegro_audio -lallegro_acodec

*adicione as librarys que são utilizadas ao longo do projeto, estas são só um exemplo

> ./main &lt;arquivo de configuracao&gt; &lt;arquivo da fila&gt;

##Windows

>Windows é para otários, se vira ai
