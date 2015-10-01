#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

enum {UP, DOWN, LEFT, RIGHT};

typedef enum {/* PUT TYPES IN HERE */} EntityType;

typedef struct _texture {
	SDL_Texture *texture;
	int width; /* Texture width */
	int height; /* Texture height */
} Texture;

typedef struct _sprite {
	Texture *spritesheet; /* Spritesheet texture loaded from an image */
	SDL_Rect sprite;
} Sprite;

typedef struct _object {
	
	struct _size {
		int width;
		int height;
	} hitbox;
	struct _loc { /* Location of the character on the renderer */
		int x;
		int y;
	} location;
} Object;	

typedef struct _entity {
	EntityType type;
	Object *object;
	struct _dir { /* Direction of the character's movement */
		int x;
		int y;
	} direction;
	int speed; /* The amount that Direction.x and y changes */
} Entity;

typedef struct _character {
	Entity *entity; 
	int health;
} Character;

typedef struct _world {
	Entity *entities; /* List of entities in the world */
	int entity_count; /* Count of entities */
	int width; /* width of world */
	int height; /* height of world */
} World;

typedef struct _game {
	SDL_Window *Window; /* The window that will be rendered to */
	SDL_Renderer *Renderer; /* The renderer for the window */
	World *worlds;
} Game;

/* Initializes the SDL environment */
bool Initialize(void);

/* ------------TEXTURE FUNCTIONS---------- */

/* Create a new Texture from an image */
Texture * New_Texture(char *path, int width, int height);

/* ------------ SPRITE FUNCTIONS ---------- */
Sprite * New_Sprite(Texture *spritesheet, int width, int height);

void Spritesheet_Destroy(Spritesheet *s);

/* -------------- WORLD FUNCTIONS ----------------- */

/* Create a new world of a specified size */
World * New_World(char *path);




/* Refresh the world - entity positions etc */
int World_Refresh((void);

/* Destroy a world */
void World_Destroy(World *w);

/* ------------GAME FUNCTIONS-------------- */
/* Creates a new game and window */
Game * New_Game(char *title, int width, int height);

/* Sets the background of the game window to an image */
int Game_SetBackground(Game *g, char *path);

/* Render and display to window */
int Game_Refresh(Game *g);

/* Free everything in the game */
int Game_End(Game *g);

#endif
