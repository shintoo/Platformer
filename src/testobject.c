#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include "object.h"
#include "spritesheet.h"
#include "texture.h"

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480

SDL_Window * MakeWindow(int w, int h);
SDL_Renderer * MakeRenderer(SDL_Window *window);

int main(void) {
	SDL_Window *window;
	SDL_Renderer *renderer;
	Texture *background;
	Object *object;
	int animation = 0;
	SDL_Event e;
	int frame = 1;
	bool running = true;

	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	window = MakeWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
	renderer = MakeRenderer(window);

	/* I have created a monster */
	object = New_Object(
		New_Spritesheet(
			New_Texture(
				renderer, /* The rendering context */
				"img/spritesheet.png" /* Path to spritesheet image */
			),
			4, /* The number of animations in the spritesheet */
			4, 4, 4, 4 /* How many frames are in each animation */
		),
		64, 64, 48, 80, /* The position x, y and size width, height of object */
		true, /* If the object has impermeable collision */
		0 /* The default sprite animation of the object */
	);

	background = New_Texture(renderer, "img/background.png");

	while (running) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_KEYDOWN) {
				switch(e.key.keysym.sym) {
					case SDLK_q:
						running = false;
					break;
					case SDLK_DOWN:
						animation = 0;
					break;
					case SDLK_LEFT:
						animation = 1;
					break;
					case SDLK_RIGHT:
						animation = 2;
					break;
					case SDLK_UP:
						animation = 3;
					break;
				}
			}
		}

		/* Clear the screen */
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		/* Render the background */
		Texture_Render(background, renderer, 0, 0);
		/* Render the object */
		Object_Render(object, renderer);
		SDL_RenderPresent(renderer);


		if (frame % 10 == 0) {
			Object_NextSprite(object);
		}
		Object_SetAnimation(object, animation);

		SDL_Delay(16);
		frame++;
	}

	Destroy_Texture(background);
	Destroy_Object(object);

	SDL_Quit();
	IMG_Quit();

	return 0;
}

SDL_Window * MakeWindow(int w, int h) {
	SDL_Window *ret = SDL_CreateWindow(
		"Platformer",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		w,
		h,
		SDL_WINDOW_SHOWN
	);

	if (!ret) {
		fprintf(stderr, "Could not create window\n");
		return NULL;
	}
	return ret;
}

SDL_Renderer * MakeRenderer(SDL_Window *window) {
	SDL_Renderer *ret = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

	if (!ret) {
		fprintf(stderr, "Could not create renderer");
		return NULL;
	}
	return ret;
}
