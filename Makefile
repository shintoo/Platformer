platformer:
	gcc -g -Wall -std=c11 src/testobjecttype.c src/objecttype.c src/spritesheet.c src/texture.c -lSDL2 -lSDL2_image -o test

