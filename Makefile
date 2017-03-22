CC=gcc
BASIC=-lallegro -lallegro_main
CFLAGS=-lallegro_image -lallegro_font -lallegro_primitives -lallegro_ttf -lallegro_audio -lallegro_acodec
FLAGS=-lm -pedantic -W -Wall
LIB=pkg-config –cflags –libs allegro-5
main:
	$(CC) main.c -o main.exe $(FLAGS) $($(LIB)) $(BASIC) $(CFLAGS)
run:
	./main.exe scripts/setup.txt scripts/helper.txt
