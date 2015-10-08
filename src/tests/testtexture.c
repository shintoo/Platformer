#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include "texture.h"

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480

SDL_Window * MakeWindow(void);
SDL_Renderer * MakeRenderer(SDL_Window *window);

int main(void) {
	SDL_Window *window;
	SDL_Renderer *renderer;
	Texture *background;
	Texture *sprite;
	SDL_Event e;
	SDL_Rect screen = {0, 0, 640, 480};
	bool running = true;

	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	window = MakeWindow();
	renderer = MakeRenderer(window);

	sprite = New_Texture(renderer, "img/sprite.png");
	background = New_Texture(renderer, "img/background.png");

	while (running) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_KEYDOWN) {
				running = false;
			}
		}
		
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		Texture_Render(background, renderer, 0, 0);
		Texture_Render(sprite, renderer, screen.w / 2 - sprite->w / 2, screen.h / 2 - sprite->h / 2);

		SDL_RenderPresent(renderer);
	}

	Destroy_Texture(background);
	Destroy_Texture(sprite);

	SDL_Quit();
	IMG_Quit();

	return 0;
}

SDL_Window * MakeWindow(void) {
	SDL_Window *ret = SDL_CreateWindow(
		"Platformer",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
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
