#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include "objecttype.h"
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
	SDL_Event e;
	SDL_Rect Camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	int frame = 1;
	bool running = true;

	ObjectType *brickType;

	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	window = MakeWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
	renderer = MakeRenderer(window);

	/* Create a new type of object - the brick */
	brickType = New_ObjectType(
		New_Spritesheet(
			New_Texture(
				renderer,
				"src/img/brick.png"
			),
			1,
			20
		),
		true,
		64,
		64
	);

	/* Create a line of 10 bricks from (64, 256) to (640, 256) */
	for (int i = 0; i < 7; i++) { /*   x              y */
		ObjectType_AddObject(brickType, 64 + (64 * i), 256, 0, 0);
	}

	background = New_Texture(renderer, "src/img/sky.png");

	while (running) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_KEYDOWN) {
				switch(e.key.keysym.sym) {
					case SDLK_q:
						running = false;
					break;
					case SDLK_DOWN:
						Camera.y++;
					break;
					case SDLK_LEFT:
						Camera.x--;
					break;
					case SDLK_RIGHT:
						Camera.x++;
					break;
					case SDLK_UP:
						Camera.y--;
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
		for (int i = 0; i < 7; i++) {
			ObjectType_RenderObject(brickType, renderer, i);
		}


		if (frame % 10 == 0) {
			for (int i = 0; i < 7; i++) {
				ObjectType_ObjectNextSprite(brickType, i);
			}
		}

		SDL_RenderPresent(renderer);

		SDL_Delay(16);
		frame++;
	}

	Destroy_Texture(background);
	Destroy_ObjectType(brickType);

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
