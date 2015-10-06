CC=gcc
LDFLAGS= -lSDL2 -lSDL2_image
CFLAGS= -g -Wall -std=c11
SRC= src/character.c src/object.c src/spritesheet.c src/texture.c
MAIN= src/testcharacter.c
NAME= test

$(NAME):
	$(CC) $(CFLAGS) $(MAIN) -o $(NAME) $(SRC) $(LDFLAGS)

